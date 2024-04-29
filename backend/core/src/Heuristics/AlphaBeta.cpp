#include <vector>
#include <algorithm>
#include <set>
#include "Threats/ThreatsBloodRelation.h"
#include "Heuristics/AlphaBeta.h"
#include "Exceptions.h"

//#define TREE_BROWSE_LOGGER

static void nBestMoveLogger(const uint32_t deep, ISearchTree::PriorityQueueScore & rPriorityQueueScore,
                            const ISearchTree::ScoreForMove scoreForMove);

void AlphaBeta::setStates(const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human)
{
    //actually we don't use originals (m_board_ab,m_cpu,m_human). Only for copy.
    m_board = &board;
    m_boardCpy = std::dynamic_pointer_cast<GomokuBoard>(m_board->clone());

    m_cpu   = &cpu;
    m_human = &human;
    m_cpuCpy.reset(new ThreatTracker(*m_cpu));
    m_humanCpy.reset(new ThreatTracker(*m_human));
    //that is not enough. Notice that m_cpuCpy, m_humanCpy are copies and they originals were set ot operate on original m_board_ab.
    //So here there is need to switch their board.
    m_cpuCpy->setBoard(*m_boardCpy.get());
    m_humanCpy->setBoard(*m_boardCpy.get());

    m_cpuCpy->mementoEnable();
    m_humanCpy->mementoEnable();
}

IBoard::PositionXY AlphaBeta::findBestMove(PriorityQueueScore& bestMove, const vector<IBoard::PositionXY>& initCandidates)
{
    if(!m_boardCpy or !m_cpuCpy or !m_humanCpy or m_depth==0)
    {
        throw game_except::General{"You must first provide valid state of board"};
    }
    vector<IBoard::PositionXY> initCandidatesCpy{initCandidates};

    Score::getInstance()->setBoard(*m_boardCpy);
    m_evalBoard->setBoards(*m_boardCpy.get(), *m_cpuCpy.get(), *m_humanCpy.get());
    m_boardCpy.get()->registerObserver(*m_evalBoard);

    if(not initCandidates.empty())
    {
        // Get extended fields for 2A, 3A, 3B, 3C.
        updateCand4ExtendGaps(initCandidatesCpy);

        // Get empty fields for 3ABC.
        updateCand4ThreeListGaps(initCandidatesCpy);
    }
    else
    {
        initCandidatesCpy = generateCand();
    }

    // No candidates means full board or error.
    const uint32_t avaliableCandidats = initCandidatesCpy.size();
    assert(avaliableCandidats);

    // When the board goes to limit, it is impossible to go deeper that number of vacant fields.
    const uint32_t currentDeepSearch = m_depth;
    m_depth                     = (avaliableCandidats < m_depth) ? avaliableCandidats : m_depth;

    vector<IBoard::PositionXY> treeTracker;

#if defined( TREE_BROWSE_LOGGER )
    m_treeLogger.NewRecord(TreeLogger::LOG_MINMAX_TREE_RECORD_FILE_NAME);
    m_treeLogger.NewRecord(TreeLogger::LOG_MINMAX_BOARD_RECORD_FILE_NAME);
#endif

    ScoreForMove retVal = gameTreeBrowsing(initCandidatesCpy, bestMove, treeTracker, MINUS_INFINITY, PLUS_INFINITY, true);

    m_depth = currentDeepSearch;
    Score::getInstance()->setBoard(*m_board);
    return retVal.m_move;
}

vector<IBoard::PositionXY> AlphaBeta::generateCand() const
{
    // Algorithm finds those fields which:
    // a) are vacant
    // b) adhere to not vacant field
    // c) extends 3A, 3B  and all 4th threats
    // See below - fields assigned with '+' will be returned.
    //	 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	|. . . . . . . . . . . . . . .|
    //	|. . . . . . . . . . . . . . .|
    //	|. . . . . . . . . . . . . . .|
    //	|. . + + + . . . . . . . . . .|
    //	|. . + O + + . . . . + . . . .|
    //	|. . + + X + . . + + . . . . .|
    //	|. . . + + + . + X + . . . . .|
    //	|. . . . . . + X + . . . . . .|
    //	|. . . . . + X + . . . . . . .|
    //	|. . . . . + + . . . . . . . .|
    //	|. . . . + . . . . . . . . . .|
    //	|. . . . . . . . . . . . . . .|
    vector<IBoard::PositionXY> neighbours;
    const uint32_t boardSize = m_boardCpy->getSize();

    const auto citr = m_boardCpy->getIterator();
    for(;citr->hasNext();)
    {
        if(IBoard::PLAYER_EMPTY != citr->getNext())
        {
            // GetNext() increments collection index to the next.
            // To take current index, decrementing is needed.
            const uint32_t index = citr->getIndex() - 1;
            vector<graph::Node> neighbors = m_boardCpy->getNeighborhood(IBoard::PositionXY(index/boardSize, index%boardSize));
            auto lambda = [&neighbours, &boardSize](graph::Node node)
            {
                neighbours.push_back(IBoard::PositionXY(node/boardSize, node%boardSize));
            };
            std::for_each(neighbors.begin(),neighbors.end(),lambda);
        }
    }

    // Remove not vacant position:
    for(auto pos = neighbours.begin(); pos != neighbours.end();)
    {
        if(m_boardCpy->getMove(*pos) != IBoard::PLAYER_EMPTY)
        {
            neighbours.erase(pos);
        }
        else
        {
            ++pos;
        }
    }

    // Get extended fields for 2A, 3A, 3C.
    std::vector<IBoard::PositionXY> exGaps;
    for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
    {
        const ThreatFinder::KindOfThreats kindOfThreat = ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i];
        m_cpuCpy->getExGaps(exGaps, kindOfThreat);
        m_humanCpy->getExGaps(exGaps, kindOfThreat);
    }

    //concatenate
    neighbours.insert(neighbours.end(), exGaps.begin(),exGaps.end());

    // Remove duplication:
    std::set<IBoard::PositionXY> unique(neighbours.begin(), neighbours.end());

    vector<IBoard::PositionXY> retVal(unique.begin(), unique.end());
    return retVal;
}

vector<IBoard::PositionXY> AlphaBeta::updateCand(const vector<IBoard::PositionXY>& candidates, IBoard::PositionXY position) const
{
    const uint32_t boardSize = m_boardCpy->getSize();
    VectorUniqueType gate;
    for(const auto el : candidates)
    {
        gate.insert(el.convert2Linear(boardSize));
    }

    // a. Get neighbors of current position
    vector<graph::Node> neighbors = m_boardCpy->getNeighborhood(position);
    vector<IBoard::PositionXY> retVal {candidates};
    for(const auto el: neighbors)
    {
        const IBoard::PositionXY xy = IBoard::PositionXY(el/boardSize, el%boardSize);

        if(not gate.isPresent(el) and m_boardCpy->getMove(xy) == IBoard::PLAYER_EMPTY)
        {
            retVal.push_back(xy);
        }
    }

    // b. Get extended fields for 2A, 3A, 3B, 3C.
    updateCand4ExtendGaps(retVal);

    // c. Remove current position, it has just been used.
    auto lambda = [&position](IBoard::PositionXY xy)
    {
        return position==xy;
    };
    auto newEnd = std::remove_if(retVal.begin(), retVal.end(),lambda);
    retVal.erase(newEnd, retVal.end());

    return retVal;
}

void AlphaBeta::updateCand4ExtendGaps(std::vector<IBoard::PositionXY>& candidates) const
{
    const uint32_t boardSize = m_boardCpy->getSize();
    VectorUniqueType gate;
    for(const auto el : candidates)
    {
        gate.insert(el.convert2Linear(boardSize));
    }

    std::vector<IBoard::PositionXY> exGaps;
    for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
    {
        const ThreatFinder::KindOfThreats kindOfThreat = ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i];
        m_cpuCpy->getExGaps(exGaps, kindOfThreat);
        m_humanCpy->getExGaps(exGaps, kindOfThreat);
    }

    // Add extended gap iif the place has not been added yet.
    for(const auto el : exGaps)
    {
        const auto value = el.convert2Linear(boardSize);
        if(not gate.isPresent(value))
            candidates.push_back(el);
    }
}

void AlphaBeta::updateCand4ThreeListGaps(std::vector<IBoard::PositionXY>& candidates) const
{
    const uint32_t boardSize = m_boardCpy->getSize();
    VectorUniqueType gate;
    for(const auto el : candidates)
    {
        gate.insert(el.convert2Linear(boardSize));
    }

    // Get threads' gaps.
    std::vector<IBoard::PositionXY> thread3ABCGaps;
    for(uint32_t i = 0; i < ThreatsBloodRelation::THREE_LIST_SIZE; ++i)
    {
        const ThreatFinder::KindOfThreats kindOfThreat = ThreatsBloodRelation::THREE_LIST[i];
        m_cpuCpy->getExGaps(thread3ABCGaps, kindOfThreat);
        m_humanCpy->getExGaps(thread3ABCGaps, kindOfThreat);
    }

    // Add extended gap iif the place has not been added yet.
    for(const auto el : thread3ABCGaps)
    {
        const auto value = el.convert2Linear(boardSize);
        if(not gate.isPresent(value))
            candidates.push_back(el);
    }
}

ISearchTree::ScoreForMove AlphaBeta::gameTreeBrowsing(
        vector<IBoard::PositionXY>& candidates, PriorityQueueScore& bestMovies,
        vector<IBoard::PositionXY> & treeTracker, int alpha, int beta,
        bool isMaximizingPlayer, const uint32_t deep)
{
#if defined( TREE_BROWSE_LOGGER )
    uint32_t logger = 0;
#endif

    // Termination condition checker.
    ScoreForMove leafScore;
    if (deep == m_depth)
    {
        m_evalBoard->regularEval(isMaximizingPlayer, leafScore.m_move, leafScore.m_score);
        leafScore.m_move = treeTracker.front();

        return leafScore;
    }

    if (isMaximizingPlayer)
    {
        ScoreForMove best = ScoreForMove{MINUS_INFINITY};

        if (m_evalBoard->extendWinnerThreatMove(true, leafScore.m_move, leafScore.m_score))
        {
            if (treeTracker.size())
            {
                leafScore.m_move = treeTracker.front();
            }
            // Log to n-best move.
            nBestMoveLogger(deep, bestMovies, leafScore);
            return leafScore;
        }
        else if (m_evalBoard->extendWinnerActionMove(true, leafScore.m_move, leafScore.m_score))
        {
            if(treeTracker.size())
            {
                leafScore.m_move = treeTracker.front();
            }
            // Log to n-best move.
            nBestMoveLogger(deep, bestMovies, leafScore);
            return leafScore;
        }
        else
        {
            for (const auto el: candidates)
            {
                assert(m_boardCpy->putMove(el, whoIsTurn()));
                treeTracker.push_back(el);
                m_cpuCpy->updateScore(el, m_humanCpy->getPlayer() == whoIsTurn(), ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                m_humanCpy->updateScore(el, m_cpuCpy->getPlayer() == whoIsTurn(), ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                switchPlayer();
                bool isGameOver = false;

                if (m_evalBoard->implicitLooser(true, leafScore.m_move, leafScore.m_score))
                {
                    leafScore.m_move = treeTracker.front();
                }
                else if (m_evalBoard->implicitWinner(true, leafScore.m_move, leafScore.m_score))
                {
                    leafScore.m_move = treeTracker.front();
                    isGameOver = true;
                }
                else
                {
                    // Create candidates list for next move.
                    vector<IBoard::PositionXY> nextCandidates = updateCand(candidates, el);

                    // Go one move deeper.
                    leafScore = gameTreeBrowsing(nextCandidates, bestMovies, treeTracker, alpha, beta, false, deep + 1);
                }

#if defined( TREE_BROWSE_LOGGER )
				++logger;
				ScoreForMove logScore;
                logScore.m_move = treeTracker.back();
                logScore.m_score = leafScore.m_score;
				m_treeLogger.AddEntryToRecord(deep, logger, logScore );
				m_treeLogger.AddEntryToRecord(deep, logger, *m_boardCpy );
                m_treeLogger.AddEntryToRecord(deep, logger, *m_cpuCpy );
                m_treeLogger.AddEntryToRecord(deep, logger, *m_humanCpy );
#endif
                nBestMoveLogger(deep, bestMovies, leafScore);
                best  = MAX(best, leafScore);
                alpha = MAX(alpha, best.m_score);

                if((beta < alpha) || isGameOver)
                {
                    m_boardCpy->removeMove(el);
                    treeTracker.pop_back();
                    m_cpuCpy->mementoRevert(1);
                    m_humanCpy->mementoRevert(1);
                    switchPlayer();
                    break;
                }
                else
                {
                    m_boardCpy->removeMove(el);
                    treeTracker.pop_back();
                    m_cpuCpy->mementoRevert(1);
                    m_humanCpy->mementoRevert(1);
                }

                switchPlayer();
            }

            return best;
        }
    }
    else
    {
        ScoreForMove best = ScoreForMove(PLUS_INFINITY);
        if(m_evalBoard->extendWinnerThreatMove(false, leafScore.m_move, leafScore.m_score))
        {
            if(treeTracker.size())
            {
                leafScore.m_move = treeTracker.front();
            }

            return leafScore;
        }
        else if(m_evalBoard->extendWinnerActionMove(false, leafScore.m_move, leafScore.m_score))
        {
            if(treeTracker.size())
            {
                leafScore.m_move = treeTracker.front();
            }

            return leafScore;
        }
        else
        {
            for(const auto el: candidates)
            {
                assert(m_boardCpy->putMove(el, whoIsTurn()));
                treeTracker.push_back(el);
                m_cpuCpy->updateScore(el, m_humanCpy->getPlayer() == whoIsTurn(),ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                m_humanCpy->updateScore(el, m_cpuCpy->getPlayer() == whoIsTurn(),ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                switchPlayer();

                bool isGameOver = false;

                if (m_evalBoard->implicitLooser(false, leafScore.m_move, leafScore.m_score))
                {
                    leafScore.m_move = treeTracker.front();
                }
                else if (m_evalBoard->implicitWinner(false, leafScore.m_move, leafScore.m_score))
                {
                    leafScore.m_move = treeTracker.front();
                    isGameOver = true;
                }
                else
                {
                    // Create candidates list for next move.
                    vector<IBoard::PositionXY> nextCandidates = updateCand(candidates, el);

                    // Go one move deeper.
                    leafScore = gameTreeBrowsing(nextCandidates, bestMovies, treeTracker, alpha, beta, true, deep + 1);
                }

#if defined( TREE_BROWSE_LOGGER )
				++logger;
				ScoreForMove logScore;
                logScore.m_move = treeTracker.back();
                logScore.m_score = leafScore.m_score;
				m_treeLogger.AddEntryToRecord(deep, logger, logScore );
				m_treeLogger.AddEntryToRecord(deep, logger, *m_boardCpy );
				m_treeLogger.AddEntryToRecord(deep, logger, *m_cpuCpy );
				m_treeLogger.AddEntryToRecord(deep, logger, *m_humanCpy );
#endif

                best = MIN(best, leafScore);
                beta = MIN(beta, best.m_score);

                if((beta < alpha) || isGameOver)
                {
                    m_boardCpy->removeMove(el);
                    treeTracker.pop_back();
                    m_cpuCpy->mementoRevert(1);
                    m_humanCpy->mementoRevert(1);
                    switchPlayer();
                    break;
                }
                else
                {
                    m_boardCpy->removeMove(el);
                    treeTracker.pop_back();
                    m_cpuCpy->mementoRevert(1);
                    m_humanCpy->mementoRevert(1);
                }

                switchPlayer();
            }

            return best;
        }

    }
}

void nBestMoveLogger(const uint32_t deep, ISearchTree::PriorityQueueScore & rPriorityQueueScore,
                            const ISearchTree::ScoreForMove scoreForMove)
{
    if(0 == deep)
    {
        rPriorityQueueScore.pushData(scoreForMove);
    }
}
