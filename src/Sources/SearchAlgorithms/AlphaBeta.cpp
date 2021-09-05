#include <vector>                    // For vector container.
#include <algorithm>                 // std::sort, uses in debbug mode.
#include <set>                       // For set container.
#include "AlphaBeta.hpp"             // For AlphaBeta declaration.
#include "IteratorIf.hpp"            // For iterator interface.
#include "ThreatsBloodRelation.hpp"  // For EXTENDED_NEIGHBORHOOD[].

// FORWARD REFERENCES
// <none>
//#define DEBBUG_MODE
#ifdef DEBBUG_MODE
static bool showboard          = false;
static Board::PositionXY refxy = Board::PositionXY(5, 10);
static uint32_t deepRef        = 0;
static uint32_t logger         = 0;
static bool LogStart           = true;
#endif

/// Converts vector xy to vector fieldPosition.
static void VctrXy2VctrPosition(const vector<Board::PositionXY> & rVctrXy, vector<Board::PositionField> & rVctrPos,
                                const uint32_t size);

/// Add move to n-best container. Log only those from depth == 0.
static void nBestMoveLogger(const uint32_t deep, SearchTreeAlgorithmIf::PriorityQueueScore & rPriorityQueueScore,
                            const SearchTreeAlgorithmIf::ScoreForMove scoreForMove);

/// Finds the best possible move.
Board::PositionXY AlphaBeta::FindBestMove(PriorityQueueScore & rBestMove,
                                          const vector<Board::PositionXY> & rInitCandidates)
{
    using namespace std;

    // Check that all necessary information was provided.
    assert(0 < m_DeepSearch);
    assert(NULL != m_pBoardScoreCpu);
    assert(NULL != m_pBoardScoreHuman);
    assert(Board::PLAYER_EMPTY != m_CurrentPlayerMove);

    // We want to have deep copy of BoardScore member to not modify original.
    BoardScoreCopy();
    m_pStateEvaluationIf->SetBoards(*m_pBoardScoreCpuCopy, *m_pBoardScoreHumanCopy);

    // Register StateEvaluation as an observer of m_pBoardCopy.
    const StateEvaluation * pStateEvaluation = static_cast<StateEvaluation *>(m_pStateEvaluationIf);
    static_cast<GomokuBoard *>(m_pBoardCopy)->RegisterObserver(*pStateEvaluation);

    // Generate list of candidate movies.
    const bool isInitCandidatesProvided = !rInitCandidates.empty();
    VectorUniqueType initCandidates;

    if(isInitCandidatesProvided)
    {
        vector<Board::PositionField> initCandidatesStl;
        VctrXy2VctrPosition(rInitCandidates, initCandidatesStl, m_pBoard->GetSize());
        initCandidates = initCandidatesStl;

        // Get extended fields for 2A, 3A, 3B, 3C.
        UpdateCand4ExtendGaps(initCandidates);

        // Get empty fields for 3ABC.
        UpdateCand4ThreeListGaps(initCandidates);
    }
    else
    {
        vector<Board::PositionField> initCandidatesStl = GenerateCand();
        initCandidates                                 = initCandidatesStl;
    }

    // No candidates means full board or error.
    const uint32_t avaliableCandidats = initCandidates.GetNumberOfElements();
    assert(avaliableCandidats);

    // When the board goes to limit, it is impossible to go deeper that number of vacant fields.
    const uint32_t currentDeepSearch = m_DeepSearch;
    m_DeepSearch                     = (avaliableCandidats < m_DeepSearch) ? avaliableCandidats : m_DeepSearch;

    vector<Board::PositionXY> treeTracker;

#if defined(DEBBUG_MODE)
    m_Logger.NewRecord(Logger::LOG_MINMAX_TREE_RECORD_FILE_NAME);
    m_Logger.NewRecord(Logger::LOG_MINMAX_BOARD_RECORD_FILE_NAME);
#endif

    ScoreForMove retVal = GameTreeBrowsing(initCandidates, rBestMove, treeTracker, MINUS_INFINITY, PLUS_INFINITY, true);

    m_DeepSearch = currentDeepSearch;

    return retVal.m_move;
}

/// Generate list of candidate moves.
vector<Board::PositionField> AlphaBeta::GenerateCand() const
{
    // Algorithm finds those fields which:
    // a) are vacant
    // b) adhere to not vacant field
    // c) extends 3A, 3B  and all 4th threats
    // See below - fields assigned with dot will be returned.
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

    vector<graph::Node> neighborhood;
    const Board & board = *m_pBoard;

    // Get neighborhoods:
    const auto citr = board.GetIterator();
    for(citr->SetToBase(); citr->HasNext();)
    {
        if(Board::PLAYER_EMPTY != citr->GetNext())
        {
            // GetNext() increments collection index to the next.
            // To take current index, decrementing is needed.
            const uint32_t index = citr->GetIndex() - 1;

            // Make some nasty conversions.
            const Board::PositionField field = static_cast<Board::PositionField>(index);
            const Board::PositionXY xy       = Board::PositionXY(board.GetSize(), field);

            // Get neighbors.
            vector<graph::Node> neighbors = board.GetNeighborhood(xy);

            // Concatenate vectors.
            neighborhood.insert(neighborhood.end(), neighbors.begin(), neighbors.end());
        }
    }

    // Remove not vacant position:
    for(auto pos = neighborhood.begin(); pos != neighborhood.end();)
    {
        const Board::PositionXY xy = Board::PositionXY(board.GetSize(), static_cast<Board::PositionField>(*pos));

        if(board.GetMove(xy) != Board::PLAYER_EMPTY)
        {
            // Remove position - iterator automatically points the next element.
            neighborhood.erase(pos);
        }
        else
        {
            ++pos;
        }
    }

    // Get extended fields for 2A, 3A, 3C.
    std::vector<Board::PositionField> exGaps;
    for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
    {
        const ThreatFinder::KindOfThreats kindOfThreat = ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i];
        m_pBoardScoreCpu->GetExGaps(exGaps, kindOfThreat);
        m_pBoardScoreHuman->GetExGaps(exGaps, kindOfThreat);
    }

    // Concatenate vectors.
    neighborhood.insert(neighborhood.end(), exGaps.begin(), exGaps.end());

    // Remove duplication:
    std::set<graph::Node> unique(neighborhood.begin(), neighborhood.end());

    vector<Board::PositionField> retVal(unique.begin(), unique.end());
    return retVal;
}

/// Generate list of candidate moves.
AlphaBeta::VectorUniqueType AlphaBeta::UpdateCand(const VectorUniqueType & rCandidates, const uint32_t position) const
{
    const Board & rBoard = *m_pBoardCopy;

    // a. Get neighbors of current position.
    const Board::Neighbours & rNeighbours = rBoard.GetNeighborhood(static_cast<Board::PositionField>(position));

    VectorUniqueType neighborhood = rCandidates;

    for(uint32_t k = 0; k < rNeighbours.m_NeighbourhoodSize; ++k)
    {
        const Board::PositionField data = rNeighbours.m_Neighbourhood[k];

        const bool isCandidateValid = (rBoard.GetMove(data) == Board::PLAYER_EMPTY) && (!neighborhood.IsPresent(data));

        if(isCandidateValid)
        {
            neighborhood.Insert(data);
        }
    }

    // b. Get extended fields for 2A, 3A, 3B, 3C.
    UpdateCand4ExtendGaps(neighborhood);

    // c. Remove current position, it has just been used.
    assert(true == neighborhood.Remove(position));

#if defined(DEBBUG_MODE)
    // Keep order. It helps for investigation while debbuging.
    vector<Board::PositionField> order;
    auto pIterator = neighborhood.GetIteratorBegin();

    for(; pIterator != neighborhood.GetIteratorEnd(); ++pIterator)
    {
        order.push_back(*pIterator);
    }
    std::sort(order.begin(), order.end());

    neighborhood.Clear();
    neighborhood = order;
#endif

    return neighborhood;
}

/// Get instance of Score.
AlphaBeta * AlphaBeta::GetInstance()
{
    static AlphaBeta alphaBeta{ SearchTreeAlgorithmIf::DEFAULT_DEPTH, "AlphaBeta" };
    return &alphaBeta;
}

/// Browses the game-tree to find best move.
SearchTreeAlgorithmIf::ScoreForMove AlphaBeta::GameTreeBrowsing(VectorUniqueType & rCandidates,
                                                                PriorityQueueScore & rBestMovesPriorityQueue,
                                                                vector<Board::PositionXY> & rTreeTracker, int alpha,
                                                                int beta, bool isMaximizingPlayer, const uint32_t deep)
{
    // Get singleton instance only once.
    static Score & rScore = *Score::GetInstance();

    // Termination condition checker.
    ScoreForMove leafScore;
    if(deep == m_DeepSearch)
    {
        m_pStateEvaluationIf->RegularEval(isMaximizingPlayer, leafScore.m_move, leafScore.m_score);
        leafScore.m_move = rTreeTracker.front();

        return leafScore;
    }

    MakeSnapshot(deep);

    if(isMaximizingPlayer)
    {
        ScoreForMove best = ScoreForMove(MINUS_INFINITY);

        if(m_pStateEvaluationIf->ExtendWinnerThreatMove(true, leafScore.m_move, leafScore.m_score))
        {
            if(rTreeTracker.size())
            {
                leafScore.m_move = rTreeTracker.front();
                RemoveSnapshot(deep);
            }
            else
            {
                // it means that none move has been put yet.
                RemoveSnapshot(deep);
            }

            // Log to n-best move.
            nBestMoveLogger(deep, rBestMovesPriorityQueue, leafScore);

            return leafScore;
        }
        else if(m_pStateEvaluationIf->ExtendWinnerActionMove(true, leafScore.m_move, leafScore.m_score))
        {
            if(rTreeTracker.size())
            {
                leafScore.m_move = rTreeTracker.front();
                RemoveSnapshot(deep);
            }
            else
            {
                // it means that none move has been put yet.
                RemoveSnapshot(deep);
            }

            // Log to n-best move.
            nBestMoveLogger(deep, rBestMovesPriorityQueue, leafScore);

            return leafScore;
        }
        else
        {
            // Recur for all candidates.
            for(VectorUniqueTypeIterator pIterator = rCandidates.GetIteratorBegin();
                pIterator != rCandidates.GetIteratorEnd();)
            {
                const Board::PositionField currentCandidat = *pIterator;
                ++pIterator;

                // Put new move into board and keep track & notify observers.
                const Board::PositionXY currentCandidatXY(m_pBoardCopy->GetSize(), currentCandidat);
                assert(m_pBoardCopy->PutMove(currentCandidat, WhoIsCurrentMove()));
                rTreeTracker.push_back(currentCandidatXY);

                rScore.UpdateScore(*m_pBoardScoreCpuCopy, currentCandidatXY);
                rScore.UpdateScore(*m_pBoardScoreHumanCopy, currentCandidatXY);

                SwitchPlayer();

#if defined(DEBBUG_MODE)
                // define global static: showboard/refxy/deepRef
                if(showboard || (refxy == currentCandidatXY && deepRef == deep))
                {
                    cout << *m_pBoardCopy << endl;

                    cout << "after human move:" << endl;
                    cout << "CPU:" << endl;
                    cout << *m_pBoardScoreCpuCopy << endl;
                    cout << "------" << endl;
                    cout << "HUMAN:" << endl;
                    cout << *m_pBoardScoreHumanCopy << endl;
                }
#endif

                bool isGameOver = false;

                if(m_pStateEvaluationIf->ImpliciteLooser(true, leafScore.m_move, leafScore.m_score))
                {
                    leafScore.m_move = rTreeTracker.front();
                }
                else if(m_pStateEvaluationIf->ImpliciteWinner(true, leafScore.m_move, leafScore.m_score))
                {
                    leafScore.m_move = rTreeTracker.front();
                    isGameOver       = true;
                }
                else
                {
                    // Create candidates list for next move.
                    VectorUniqueType nextCandidates = UpdateCand(rCandidates, currentCandidat);

                    // Go one move deeper.
                    leafScore = GameTreeBrowsing(nextCandidates, rBestMovesPriorityQueue, rTreeTracker, alpha, beta,
                                                 false, deep + 1);
                }

#if defined(DEBBUG_MODE)
                // define global static: LogStart
                if(LogStart)
                {
                    ++logger;

                    ScoreForMove log;
                    log.m_move  = rTreeTracker.back();
                    log.m_score = leafScore.m_score;

                    m_Logger.AddEntryToRecord(deep, logger, log);
                    m_Logger.AddEntryToRecord(deep, logger, *m_pBoardCopy);
                    m_Logger.AddEntryToRecord(deep, logger, *m_pBoardScoreCpuCopy);
                    m_Logger.AddEntryToRecord(deep, logger, *m_pBoardScoreHumanCopy);
                }
#endif

                // Log to n-best move.
                nBestMoveLogger(deep, rBestMovesPriorityQueue, leafScore);

                best  = MAX(best, leafScore);
                alpha = MAX(alpha, best.m_score);

                // Crawl thru tree.
                if(pIterator == rCandidates.GetIteratorEnd())
                {
                    // Go one level up in the tree.
                    RemoveSnapshot(deep);

                    if(deep > 0)
                    {
                        RetreiveSnapshot(deep - 1);
                    }
                    else
                    {
                        // all work done!
                    }

                    m_pBoardCopy->RemoveMove(rTreeTracker.back());
                    rTreeTracker.pop_back();
                }
                else if((beta < alpha) || isGameOver)
                {
                    // Go one level up in the tree.
                    RemoveSnapshot(deep);
                    if(deep > 0)
                    {
                        RetreiveSnapshot(deep - 1);
                    }

                    m_pBoardCopy->RemoveMove(rTreeTracker.back());
                    rTreeTracker.pop_back();

                    SwitchPlayer();

                    // There is no point browsing thru the rest moves.
                    break;
                }
                else
                {
                    // Undo move, and keep track.
                    m_pBoardCopy->RemoveMove(currentCandidatXY);
                    rTreeTracker.pop_back();

                    RetreiveSnapshot(deep);
                }

                SwitchPlayer();
            }

            return best;
        }
    }
    else
    {
        ScoreForMove best = ScoreForMove(PLUS_INFINITY);

        if(m_pStateEvaluationIf->ExtendWinnerThreatMove(false, leafScore.m_move, leafScore.m_score))
        {
            if(rTreeTracker.size())
            {
                leafScore.m_move = rTreeTracker.front();
                RemoveSnapshot(deep);
            }
            else
            {
                // it means that none move has been put yet.
                RemoveSnapshot(deep);
            }
            return leafScore;
        }
        else if(m_pStateEvaluationIf->ExtendWinnerActionMove(false, leafScore.m_move, leafScore.m_score))
        {
            if(rTreeTracker.size())
            {
                leafScore.m_move = rTreeTracker.front();
                RemoveSnapshot(deep);
            }
            else
            {
                // it means that none move has been put yet.
                RemoveSnapshot(deep);
            }
            return leafScore;
        }
        else
        {
            // Recur for all candidates.
            for(VectorUniqueTypeIterator pIterator = rCandidates.GetIteratorBegin();
                pIterator != rCandidates.GetIteratorEnd();)
            {
                const Board::PositionField currentCandidat = *pIterator;
                ++pIterator;

                // Put new move into board and keep track & notify observers.
                const Board::PositionXY currentCandidatXY(m_pBoardCopy->GetSize(), currentCandidat);
                assert(m_pBoardCopy->PutMove(currentCandidat, WhoIsCurrentMove()));
                rTreeTracker.push_back(currentCandidatXY);

                rScore.UpdateScore(*m_pBoardScoreCpuCopy, currentCandidatXY);
                rScore.UpdateScore(*m_pBoardScoreHumanCopy, currentCandidatXY);

                SwitchPlayer();

#if defined(DEBBUG_MODE)
                // define global static: showboard/refxy/deepRef
                if(showboard || (refxy == currentCandidatXY && deepRef == deep))
                {
                    cout << *m_pBoardCopy << endl;

                    cout << "after human move:" << endl;
                    cout << "CPU:" << endl;
                    cout << *m_pBoardScoreCpuCopy << endl;
                    cout << "------" << endl;
                    cout << "HUMAN:" << endl;
                    cout << *m_pBoardScoreHumanCopy << endl;
                }
#endif

                bool isGameOver = false;

                if(m_pStateEvaluationIf->ImpliciteLooser(false, leafScore.m_move, leafScore.m_score))
                {
                    leafScore.m_move = rTreeTracker.front();
                }
                else if(m_pStateEvaluationIf->ImpliciteWinner(false, leafScore.m_move, leafScore.m_score))
                {
                    leafScore.m_move = rTreeTracker.front();
                    isGameOver       = true;
                }
                else
                {
                    // Create candidates list for next move.
                    VectorUniqueType nextCandidates = UpdateCand(rCandidates, currentCandidat);

                    // Go one move deeper.
                    leafScore = GameTreeBrowsing(nextCandidates, rBestMovesPriorityQueue, rTreeTracker, alpha, beta,
                                                 true, deep + 1);
                }

#if defined(DEBBUG_MODE)
                // define global static: LogStart
                if(LogStart)
                {
                    ++logger;

                    ScoreForMove log;
                    log.m_move  = rTreeTracker.back();
                    log.m_score = leafScore.m_score;

                    m_Logger.AddEntryToRecord(deep, logger, log);
                    m_Logger.AddEntryToRecord(deep, logger, *m_pBoardCopy);
                    m_Logger.AddEntryToRecord(deep, logger, *m_pBoardScoreCpuCopy);
                    m_Logger.AddEntryToRecord(deep, logger, *m_pBoardScoreHumanCopy);
                }
#endif
                //===================================================================================

                best = MIN(best, leafScore);
                beta = MIN(beta, best.m_score);

                // Crawl thru tree.
                if(pIterator == rCandidates.GetIteratorEnd())
                {
                    // Go one level up in the tree.
                    RemoveSnapshot(deep);

                    if(deep > 0)
                    {
                        RetreiveSnapshot(deep - 1);
                    }
                    else
                    {
                        // all work done!
                    }

                    m_pBoardCopy->RemoveMove(rTreeTracker.back());
                    rTreeTracker.pop_back();
                }
                else if((beta < alpha) || isGameOver)
                {
                    // Go one level up in the tree.
                    RemoveSnapshot(deep);
                    if(deep > 0)
                    {
                        RetreiveSnapshot(deep - 1);
                    }

                    m_pBoardCopy->RemoveMove(rTreeTracker.back());
                    rTreeTracker.pop_back();

                    SwitchPlayer();

                    // There is no point browsing thru the rest moves.
                    break;
                }
                else
                {
                    // Undo move, and keep track.
                    m_pBoardCopy->RemoveMove(currentCandidatXY);
                    rTreeTracker.pop_back();

                    RetreiveSnapshot(deep);
                }

                SwitchPlayer();
            }

            return best;
        }
    }
}

/// Update candidate list for extended gaps.
void AlphaBeta::UpdateCand4ExtendGaps(VectorUniqueType & rCandidates) const
{
    // Get extended gaps.
    std::vector<Board::PositionField> exGaps;
    for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
    {
        const ThreatFinder::KindOfThreats kindOfThreat = ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i];
        m_pBoardScoreCpuCopy->GetExGaps(exGaps, kindOfThreat);
        m_pBoardScoreHumanCopy->GetExGaps(exGaps, kindOfThreat);
    }

    const uint32_t exGapsSize = exGaps.size();

    // Add extended gap iif the place has not been added yet.
    for(uint32_t i = 0; i < exGapsSize; ++i)
    {
        const Board::PositionField data = exGaps[i];
        const bool isNewCandidate       = !rCandidates.IsPresent(data);

        if(isNewCandidate)
        {
            rCandidates.Insert(data);
        }
    }
}

/// Update candidate list for gaps of 3ABC.
void AlphaBeta::UpdateCand4ThreeListGaps(VectorUniqueType & rCandidates) const
{
    // Get threads' gaps.
    std::vector<Board::PositionField> thread3ABCGaps;
    for(uint32_t i = 0; i < ThreatsBloodRelation::THREE_LIST_SIZE; ++i)
    {
        const ThreatFinder::KindOfThreats kindOfThreat = ThreatsBloodRelation::THREE_LIST[i];
        m_pBoardScoreCpuCopy->GetGapsNonUnique(thread3ABCGaps, kindOfThreat);
        m_pBoardScoreHumanCopy->GetGapsNonUnique(thread3ABCGaps, kindOfThreat);
    }

    const uint32_t thread3ABCGapsSize = thread3ABCGaps.size();

    // Add gaps gaps iif the place has not been added yet.
    for(uint32_t i = 0; i < thread3ABCGapsSize; ++i)
    {
        const Board::PositionField data = thread3ABCGaps[i];
        const bool isNewCandidate       = !rCandidates.IsPresent(data);

        if(isNewCandidate)
        {
            rCandidates.Insert(data);
        }
    }
}

/// Do deep copy of Board Score.
void AlphaBeta::BoardScoreCopy()
{
    assert(NULL != m_pBoardScoreCpu);
    assert(NULL != m_pBoardScoreHuman);

    // Delete previous state of game.
    delete m_pBoardScoreCpuCopy;
    delete m_pBoardScoreHumanCopy;
    delete m_pBoardCopy;

    // Do copy of m_pBoardScores.
    m_pBoardScoreCpuCopy   = new BoardScore(*m_pBoardScoreCpu);
    m_pBoardScoreHumanCopy = new BoardScore(*m_pBoardScoreHuman);
    assert(NULL != m_pBoardScoreCpuCopy);
    assert(NULL != m_pBoardScoreHumanCopy);

    // Then provide copy of Board.
    m_pBoardCopy = &m_pBoard->Clone();
    m_pBoardScoreCpuCopy->SetBoard(*m_pBoardCopy);
    m_pBoardScoreHumanCopy->SetBoard(*m_pBoardCopy);
}

/// Make snapshot on provided depth.
void AlphaBeta::MakeSnapshot(uint32_t depth)
{
    assert(NULL != m_pBoardScoreCpuCopy);
    assert(NULL != m_pBoardScoreHumanCopy);
    assert(NULL == m_SnapshotContainerCpu[depth]);
    assert(NULL == m_SnapshotContainerHuman[depth]);

    // Make snapshot of BoardScoreCopy for each player.
    m_SnapshotContainerCpu[depth]   = new BoardScore(*m_pBoardScoreCpuCopy);
    m_SnapshotContainerHuman[depth] = new BoardScore(*m_pBoardScoreHumanCopy);
    assert(NULL != m_SnapshotContainerCpu[depth]);
    assert(NULL != m_SnapshotContainerHuman[depth]);
}

/// Retrieve snapshot on provided depth.
void AlphaBeta::RetreiveSnapshot(uint32_t depth)
{
    assert(NULL != m_SnapshotContainerCpu[depth]);
    assert(NULL != m_SnapshotContainerHuman[depth]);
    *m_pBoardScoreCpuCopy   = *m_SnapshotContainerCpu[depth];
    *m_pBoardScoreHumanCopy = *m_SnapshotContainerHuman[depth];
}

/// Remove snapshot on provided depth.
void AlphaBeta::RemoveSnapshot(uint32_t depth)
{
    assert(NULL != m_SnapshotContainerCpu[depth]);
    assert(NULL != m_SnapshotContainerHuman[depth]);
    delete m_SnapshotContainerCpu[depth];
    delete m_SnapshotContainerHuman[depth];
    m_SnapshotContainerCpu[depth]   = NULL;
    m_SnapshotContainerHuman[depth] = NULL;
}

// Converts vector xy to vector fieldPosition.
static void VctrXy2VctrPosition(const vector<Board::PositionXY> & rVctrXy, vector<Board::PositionField> & rVctrPos,
                                const uint32_t boardSize)
{
    for(auto cit = rVctrXy.begin(); cit != rVctrXy.end(); ++cit)
    {
        const Board::PositionField data(boardSize, *cit);
        rVctrPos.push_back(data);
    }
}

/// Add move to n-best container. Log only those from depth == 0.
static void nBestMoveLogger(const uint32_t deep, SearchTreeAlgorithmIf::PriorityQueueScore & rPriorityQueueScore,
                            const SearchTreeAlgorithmIf::ScoreForMove scoreForMove)
{
    if(0 == deep)
    {
        rPriorityQueueScore.PushData(scoreForMove);
    }
}

/***************************************************************************
 *   Copyright (C) 2018 by Zbigniew Halat                                  *
 *   zby.halat@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/
