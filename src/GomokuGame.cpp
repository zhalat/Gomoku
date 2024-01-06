#include <cstring>
#include <cstdlib>
#include <time.h>
#include <limits.h>
#include "Exceptions.h"
#include "GomokuGame.h"
#include "Spotter.h"
#include "Score.h"
#include "GomokuBoard.h"
#include "OpenBook.h"
#include "Heuristics/AlphaBeta.h"

using namespace std;

static const IBoard::PositionXY k_XY_OUT_OF_BOARD = IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD);

void GomokuGame::init(const uint32_t size, const IBoard::Player humanColor, const IGame::Level level,
                      const bool isRandomize, const uint32_t maxTime, std::istream & inStream, std::ostream & outStream)
{
    srand(time(NULL));

    m_computerColor = (humanColor == IBoard::PLAYER_A) ? IBoard::PLAYER_B : IBoard::PLAYER_A;
    m_humanColor    = humanColor;
    m_level = level;
    m_boardSize = size;
    m_isRandomize = isRandomize;
    m_maxTime     = maxTime;
    pInputStream  = &inStream;
    pOutputStream = &outStream;

    m_board= make_unique<GomokuBoard>(m_boardSize);
    m_spotterCpu = make_unique<Spotter>(m_computerColor);
    m_spotterHuman = make_unique<Spotter>(m_humanColor);
    m_trackerCpu = make_unique<ThreatTracker>(m_computerColor,*m_spotterCpu);
    m_trackerHuman = make_unique<ThreatTracker>(m_humanColor,*m_spotterHuman);
    m_trackerCpu->setBoard(*m_board);
    m_trackerHuman->setBoard(*m_board);
    setBoard(*m_board);
    m_engine = make_unique<AlphaBeta>(m_level, "AlphaBeta");
    m_engine->setStates(*m_board,*m_trackerCpu,*m_trackerHuman);
    m_engine->setInitialPlayer(m_computerColor);
}

void GomokuGame::setBoard(const IBoard& board)
{
    for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
    {
        Score::getInstance()->setBoard(board);
    }
}

void GomokuGame::play()
{
    // Keeps human move read from input stream.
    IBoard::PositionXY humanMove = k_XY_OUT_OF_BOARD;
    IBoard::PositionXY cpuMove   = k_XY_OUT_OF_BOARD;

    // 'x' means white - always starts.
    bool isComputerMove = (IBoard::PLAYER_A == m_computerColor) ? true : false;

    enum PlayStateMachine
    {
        PLAY_STATE_MACHINE_NONE,
        START,
        CPU_WHITE_FIRST_MOVE,
        CPU_WHITE_OPEN_BOOK_MOVE,
        CPU_BLACK_OPEN_BOOK_MOVE,
        CPU_AI_MOVE,
        HUMAN_MOVE,
        HUMAN_VALIDATION_MOVE,
        CHECK_WINNER,
        DISPLAY,
        GAME_OVER,
    };

    PlayStateMachine playStateMachine       = START;
    PlayStateMachine playStateMachineShadow = PLAY_STATE_MACHINE_NONE;
    bool isEnd                              = false;

    while(!isEnd)
    {
        switch(playStateMachine)
        {
            case START: {
                playStateMachineShadow = CHECK_WINNER;
                if(IBoard::Player::PLAYER_A == m_computerColor)
                {
                    // Don't display empty board when cpu starts.
                    playStateMachine = CHECK_WINNER;
                }
                else
                {
                    playStateMachine = DISPLAY;
                }
            }
            break;

            case CPU_WHITE_FIRST_MOVE: {
                // Put the first move on center of the board.
                const IBoard::PositionXY firstMove(m_board->getSize() / 2, m_board->getSize() / 2);
                cpuMove = firstMove;
                m_board->putMove(firstMove, m_computerColor);
                m_trackerCpu->updateScore(firstMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                m_trackerHuman->updateScore(firstMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                isComputerMove = false;

                playStateMachineShadow = CHECK_WINNER;
                playStateMachine       = DISPLAY;
            }
            break;

            case CPU_WHITE_OPEN_BOOK_MOVE: {
                assert(IBoard::PLAYER_A == m_computerColor);

                cpuMove = OpenBook::getBestThirdWhiteMove(*m_board);

                if(k_XY_OUT_OF_BOARD == cpuMove)
                {
                    // game is neither direct nor indirect.
                    //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
                    // 0 |. . . . . . . . . . . . . . .|
                    // 1 |. . . . . . . . . . . . . . .|
                    // 2 |. . . . . . . . . . . . . . .|
                    // 3 |. . . . . . . . . . . . . . .|
                    // 4 |. . . . . c . c . . . . . . .|
                    // 5 |. . . . c . . . c . . . . . .|
                    // 6 |. . . . . . x . . . . . . . .|
                    // 7 |. . . . c . . . c . . . . . .|
                    // 8 |. . . . . c . c . . . . . . .|
                    // 9 |. . . . . . . . . . . . . . .|
                    ISearchTree::PriorityQueueScore nBestMoves(1);
                    cpuMove = m_engine->findBestMove(nBestMoves);
                }

                m_board->putMove(cpuMove, m_computerColor);
                m_trackerCpu->updateScore(cpuMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                m_trackerHuman->updateScore(cpuMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                isComputerMove = false;

                playStateMachineShadow = CHECK_WINNER;
                playStateMachine       = DISPLAY;
            }
            break;

            case CPU_BLACK_OPEN_BOOK_MOVE: {
                assert(IBoard::PLAYER_B == m_computerColor);

                cpuMove = OpenBook::getBestSecondBlackMove(*m_board);

                m_board->putMove(cpuMove, m_computerColor);
                m_trackerCpu->updateScore(cpuMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                m_trackerHuman->updateScore(cpuMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                isComputerMove = false;

                playStateMachineShadow = CHECK_WINNER;
                playStateMachine       = DISPLAY;
            }
            break;

            case CPU_AI_MOVE: {
                cpuMove = getBestMove();

                m_board->putMove(cpuMove, m_computerColor);
                m_trackerCpu->updateScore(cpuMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                m_trackerHuman->updateScore(cpuMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                isComputerMove = false;

                playStateMachineShadow = CHECK_WINNER;
                playStateMachine       = DISPLAY;
            }
            break;

            case HUMAN_MOVE: {
                humanMove              = getUserMove();
                playStateMachineShadow = PLAY_STATE_MACHINE_NONE;
                playStateMachine       = HUMAN_VALIDATION_MOVE;
            }
            break;

            case HUMAN_VALIDATION_MOVE: {
                if(isMoveValid(humanMove))
                {
                    m_board->putMove(humanMove, m_humanColor);
                    m_trackerCpu->updateScore(humanMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                    m_trackerHuman->updateScore(humanMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                    humanMove = k_XY_OUT_OF_BOARD;

                    isComputerMove = true;

                    playStateMachineShadow = CHECK_WINNER;
                    playStateMachine       = DISPLAY;
                }
                else
                {
                    *pOutputStream << INVALID_MOVE_MSG << TERMINATOR_MSG;

                    playStateMachineShadow = PLAY_STATE_MACHINE_NONE;
                    playStateMachine       = HUMAN_MOVE;
                }

                pOutputStream->flush();
            }
            break;

            case CHECK_WINNER: {
                bool isCpuWhiteOpening = (isComputerMove && (2 == m_board->getMoveNumber()));
                bool isCpuBlackOpening = (isComputerMove && (1 == m_board->getMoveNumber()));
                bool isCpuFirstMove    = (isComputerMove && (0 == m_board->getMoveNumber()));

                if(isWinner(m_computerColor))
                {
                    *pOutputStream << LOOSER_MSG;
                    const ThreatFinder::ThreatLocation & rThreatLocation = m_trackerCpu->getThreatList(ThreatFinder::THREAT_WINNER).front();
                    for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS; ++i)
                    {
                        const IBoard::PositionXY rXy = rThreatLocation.m_threatDetails.m_myPawns[i];
                        *pOutputStream << WINNER_MOVIES_MARK << rXy;
                    }

                    playStateMachine       = GAME_OVER;
                    playStateMachineShadow = GAME_OVER;
                }
                else if(isWinner(m_humanColor))
                {
                    *pOutputStream << WINNER_MSG;
                    const ThreatFinder::ThreatLocation & rThreatLocation =m_trackerHuman->getThreatList(ThreatFinder::THREAT_WINNER).front();
                    for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS; ++i)
                    {
                        const IBoard::PositionXY rXy = rThreatLocation.m_threatDetails.m_myPawns[i];
                        *pOutputStream << WINNER_MOVIES_MARK << rXy;
                    }

                    playStateMachine       = GAME_OVER;
                    playStateMachineShadow = GAME_OVER;
                }
                else if(isStalemate())
                {
                    *pOutputStream << STALEMATE_MSG;

                    playStateMachine       = GAME_OVER;
                    playStateMachineShadow = GAME_OVER;
                }
                else if(isCpuWhiteOpening)
                {
                    playStateMachine = CPU_WHITE_OPEN_BOOK_MOVE;
                }
                else if(isCpuBlackOpening)
                {
                    playStateMachine = CPU_BLACK_OPEN_BOOK_MOVE;
                }
                else if(isCpuFirstMove)
                {
                    playStateMachine = CPU_WHITE_FIRST_MOVE;
                }
                else if(isComputerMove)
                {
                    playStateMachine = CPU_AI_MOVE;
                }
                else
                {
                    playStateMachine = HUMAN_MOVE;
                }

                *pOutputStream << TERMINATOR_MSG;
                pOutputStream->flush();

                playStateMachineShadow = PLAY_STATE_MACHINE_NONE;
            }
            break;

            case DISPLAY: {
                *pOutputStream << *m_board;

                IBoard::PositionXY lastMove = k_XY_OUT_OF_BOARD;

                if(m_board->getLastMove(lastMove))
                {
                    const bool isComputerMovePrint = !isComputerMove;

                    if(isComputerMovePrint)
                    {
                        *pOutputStream << LAST_CPU_MOVE_MSG << lastMove;
                    }
                    else
                    {
                        *pOutputStream << LAST_HUMAN_MOVE_MSG << lastMove;
                    }

                }

                pOutputStream->flush();

                playStateMachine = playStateMachineShadow;
            }
            break;

            case GAME_OVER: {
                isEnd = endGame();
                if(isEnd)
                {
                    // Bye bye.
                }
                else
                {
                    // Switch players color
                    IBoard::Player tmp = m_computerColor;
                    m_computerColor   = m_humanColor;
                    m_humanColor      = tmp;
                    isComputerMove    = (IBoard::PLAYER_A == m_computerColor) ? true : false;

                    restartGame();
                    playStateMachine       = START;
                    playStateMachineShadow = PLAY_STATE_MACHINE_NONE;
                }
            }
            break;

            default:
                assert(false);
        }
    }
}

bool GomokuGame::endGame()
{
    bool retVal              = true;
    std::string frontEndData = std::string();

    *pInputStream >> frontEndData;

    if(pInputStream->fail())
    {
        assert(false);
    }
    else
    {
        // GUI message parser.
        if(frontEndData == std::string(NEW_GAME))
        {
            pInputStream->clear();
            retVal = false;
        }
    }

    return retVal;
}

void GomokuGame::restartGame()
{
    m_board->resetInstance();
    m_trackerCpu->resetInstance();
    m_trackerHuman->resetInstance();
//    m_pBoardScoreCpu->SetPlayer(m_ComputerColor);
//    m_pBoardScoreHuman->SetPlayer(m_HumanColor);
    setBoard(*m_board);
    pOutputStream->clear();
    pInputStream->clear();
}

IBoard::PositionXY GomokuGame::getUserMove() const
{
    IBoard::PositionXY retVal = k_XY_OUT_OF_BOARD;
    uint32_t x               = 0;
    uint32_t y               = 0;

    while(true)
    {
        *pOutputStream << YOUR_MOVE_MSG << TERMINATOR_MSG;
        pOutputStream->flush();
        x = 0;
        y = 0;

        *pInputStream >> x;
        if(pInputStream->fail())
        {
            *pOutputStream << INVALID_PARAMETER_MSG << TERMINATOR_MSG;
            pInputStream->clear();
            // Ignore to the end of line
            pInputStream->ignore(INT_MAX, '\n');
            continue;
        }

        *pInputStream >> y;
        if(pInputStream->fail())
        {
            *pOutputStream << INVALID_PARAMETER_MSG << TERMINATOR_MSG;
            pInputStream->clear();
            // Ignore to the end of line
            pInputStream->ignore(INT_MAX, '\n');
            continue;
        }
        else
        {
            break;
        }

        pOutputStream->flush();
    }

    retVal = IBoard::PositionXY(x, y);
    return retVal;
}


bool GomokuGame::isMoveValid(const IBoard::PositionXY xy) const
{
    bool retVal = false;

    const bool isOnBoard = m_board->isOnBoard(xy);
    const bool isVacant  = ((isOnBoard) && (IBoard::PLAYER_EMPTY == m_board->getMove(xy)));

    // Position must be on board, vacant.
    retVal = (isOnBoard && isVacant);

    return retVal;
}

bool GomokuGame::isWinner(const IBoard::Player player) const
{
    bool retVal = false;

    if((m_trackerHuman->getPlayer() == player) &&
       (m_trackerHuman->getThreatList(ThreatFinder::THREAT_WINNER).size()))
    {
        retVal = true;
    }
    else if((m_trackerCpu->getPlayer() == player) &&
            (m_trackerCpu->getThreatList(ThreatFinder::THREAT_WINNER).size()))
    {
        retVal = true;
    }
    else
    {
        // nothing to do.
    }

    return retVal;
}

bool GomokuGame::isStalemate() const
{
    static const uint32_t maxFields = m_board->getSize() * m_board->getSize();
    const uint32_t moveOnBoard      = m_board->getMoveNumber();
    const bool isStalemate          = (moveOnBoard == maxFields);

    return isStalemate;
}

IBoard::PositionXY GomokuGame::getBestMove() const
{
    IBoard::PositionXY retVal = k_XY_OUT_OF_BOARD;

    if(BEGINNER == m_level)
    {
        m_engine->setDepth(2);
    }
    else if(INTERMEDIATE == m_level)
    {
        m_engine->setDepth(3);
    }
    else if(ADVANCED == m_level)
    {
        m_engine->setDepth(4);
    }
    else if(EXPERT == m_level)
    {
        m_engine->setDepth(5);
    }
    else
    {
        m_engine->setDepth(ISearchTree::k_DEFAULT_DEPTH);
    }

    const uint32_t maxCandidatesNumber = 20;
    ISearchTree::PriorityQueueScore nBestMove{maxCandidatesNumber};
    m_engine->setStates(*m_board, *m_trackerCpu, *m_trackerHuman);
    IBoard::PositionXY best = m_engine->findBestMove(nBestMove);
    retVal = best;

    assert(k_XY_OUT_OF_BOARD != retVal);
    return retVal;
}



