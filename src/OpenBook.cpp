#include <assert.h>
#include <cstdlib>
#include "OpenBook.h"

// Point beyond the board. Useful for initialization.
static const IBoard::PositionXY XY_OUT_OF_BOARD =
    IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD);

const OpenBook::Openings OpenBook::DIRECT_OPEN[] = { { IBoard::UP, OpenBook::m_crawlingChainUp },
                                                     { IBoard::RIGHT, OpenBook::m_crawlingChainRight },
                                                     { IBoard::DOWN, OpenBook::m_crawlingChainDown },
                                                     { IBoard::LEFT, OpenBook::m_crawlingChainLeft } };
const uint32_t OpenBook::DIRECT_OPEN_SIZE        = std::size(OpenBook::DIRECT_OPEN);

const OpenBook::Openings OpenBook::INDIRECT_OPEN[] = { { IBoard::UP_RIGHT, OpenBook::m_crawlingChainUpRight },
                                                       { IBoard::DOWN_RIGHT, OpenBook::m_crawlingChainDownRight },
                                                       { IBoard::DOWN_LEFT, OpenBook::m_crawlingChainDownLeft },
                                                       { IBoard::UP_LEFT, OpenBook::m_crawlingChainUpLeft } };
const uint32_t OpenBook::INDIRECT_OPEN_SIZE        = std::size(OpenBook::INDIRECT_OPEN);

// Letters point best movements for 'direct open game'.
// Notice that this is only one from four cases (UP case).
//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
// 0 |. . . . . . . . . . . . . . .|
// 1 |. . . . . . . . . . . . . . .|
// 2 |. . . . . . . . . . . . . . .|
// 3 |. . . . . . . . . . . . . . .|
// 4 |. . . . . . A . . . . . . . .|
// 5 |. . . . . B o C . . . . . . .|
// 6 |. . . . D . x . E . . . . . .|
// 7 |. . . . . . . . . . . . . . .|
// 8 |. . . . . . F . . . . . . . .|
// 9 |. . . . . . . . . . . . . . .|
OpenBook::CrawlingChain OpenBook::m_crawlingChainUp[] = {
    { 'A', { { IBoard::UP, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'B', { { IBoard::UP_LEFT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'C', { { IBoard::UP_RIGHT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'D', { { IBoard::LEFT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'E', { { IBoard::RIGHT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'F', { { IBoard::DOWN, 2 }, { IBoard::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_crawlingChainRight[] = {
    { 'A', { { IBoard::RIGHT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'B', { { IBoard::UP_RIGHT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'C', { { IBoard::DOWN_RIGHT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'D', { { IBoard::UP, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'E', { { IBoard::DOWN, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'F', { { IBoard::LEFT, 2 }, { IBoard::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_crawlingChainDown[] = {
    { 'A', { { IBoard::DOWN, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'B', { { IBoard::DOWN_RIGHT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'C', { { IBoard::DOWN_LEFT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'D', { { IBoard::RIGHT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'E', { { IBoard::LEFT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'F', { { IBoard::UP, 2 }, { IBoard::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_crawlingChainLeft[] = {
    { 'A', { { IBoard::LEFT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'B', { { IBoard::DOWN_LEFT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'C', { { IBoard::UP_LEFT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'D', { { IBoard::DOWN, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'E', { { IBoard::UP, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'F', { { IBoard::RIGHT, 2 }, { IBoard::DIRECTION_NONE, 0 } } }
};

const uint32_t OpenBook::CRAWLING_DIRECT_SIZE = std::size(m_crawlingChainUp);

// Letters point best movements for 'indirect open game'.
// Notice that this is only one from four cases (UP_RIGHT case).
//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
// 0 |. . . . . . . . . . . . . . .|
// 1 |. . . . . . . . . . . . . . .|
// 2 |. . . . . . . . . . . . . . .|
// 3 |. . . . . . . . . . . . . . .|
// 4 |. . . . . G H . . . . . . . .|
// 5 |. . . . . I . o . . . . . . .|
// 6 |. . . . . . x . J . . . . . .|
// 7 |. . . . M . . K L . . . . . .|
// 8 |. . . . . N . . . . . . . . .|
// 9 |. . . . . . . . . . . . . . .|
OpenBook::CrawlingChain OpenBook::m_crawlingChainUpRight[] = {
    { 'G', { { IBoard::LEFT, 1 }, { IBoard::UP, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'H', { { IBoard::UP, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'I', { { IBoard::LEFT, 1 }, { IBoard::UP, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'J', { { IBoard::RIGHT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'M', { { IBoard::DOWN_RIGHT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'K', { { IBoard::RIGHT, 2 }, { IBoard::DOWN, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'L', { { IBoard::DOWN, 1 }, { IBoard::LEFT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'N', { { IBoard::DOWN, 2 }, { IBoard::LEFT, 1 }, { IBoard::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_crawlingChainDownRight[] = {
    { 'G', { { IBoard::RIGHT, 2 }, { IBoard::UP, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'H', { { IBoard::RIGHT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'I', { { IBoard::RIGHT, 1 }, { IBoard::UP, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'J', { { IBoard::DOWN, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'M', { { IBoard::DOWN_LEFT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'K', { { IBoard::DOWN, 2 }, { IBoard::LEFT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'L', { { IBoard::UP, 2 }, { IBoard::LEFT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'N', { { IBoard::UP, 1 }, { IBoard::LEFT, 2 }, { IBoard::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_crawlingChainDownLeft[] = {
    { 'G', { { IBoard::RIGHT, 1 }, { IBoard::DOWN, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'H', { { IBoard::DOWN, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'I', { { IBoard::RIGHT, 1 }, { IBoard::DOWN, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'J', { { IBoard::LEFT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'M', { { IBoard::UP_LEFT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'K', { { IBoard::UP, 1 }, { IBoard::LEFT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'L', { { IBoard::UP, 1 }, { IBoard::RIGHT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'N', { { IBoard::UP, 2 }, { IBoard::RIGHT, 1 }, { IBoard::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_crawlingChainUpLeft[] = {
    { 'G', { { IBoard::LEFT, 2 }, { IBoard::DOWN, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'H', { { IBoard::LEFT, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'I', { { IBoard::LEFT, 1 }, { IBoard::DOWN, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'J', { { IBoard::UP, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'M', { { IBoard::UP_RIGHT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'K', { { IBoard::RIGHT, 1 }, { IBoard::UP, 2 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'L', { { IBoard::DOWN, 2 }, { IBoard::RIGHT, 1 }, { IBoard::DIRECTION_NONE, 0 } } },
    { 'N', { { IBoard::RIGHT, 2 }, { IBoard::DOWN, 1 }, { IBoard::DIRECTION_NONE, 0 } } }
};

const uint32_t OpenBook::CRAWLING_INDIRECT_SIZE = std::size(m_crawlingChainUpRight);

/// Provide best third move for white.
IBoard::PositionXY OpenBook::getBestThirdWhiteMove(const IBoard & board)
{
    IBoard::PositionXY retVal = XY_OUT_OF_BOARD;

    // Get the first move.
    IBoard::PositionXY xyFirst;
    const bool status = board.getFirstMove(xyFirst);
    assert(status);

    // Checks kind of open game.
    const bool isDirectOpen   = (OpenBook::DIRECT == openGame(board));
    const bool isInDirectOpen = (OpenBook::INDIRECT == openGame(board));

    if(isDirectOpen)
    {
        // Find out main direction.
        uint32_t index = DIRECT_PATH_SIZE;
        for(uint32_t i = 0; i < DIRECT_PATH_SIZE; ++i)
        {
            if(IBoard::k_NEIGHBOR_NOT_FOUND != board.neighbourDistance(xyFirst, DIRECT_PATH[i], board.getMove(xyFirst)))
            {
                index = i;
                break;
            }
        }
        assert(index < DIRECT_PATH_SIZE);

        const IBoard::Direction mainDirection = DIRECT_PATH[index];

        // Find chain associated with the main direction.
        Crawling * pCrawlingList = NULL;
        for(uint32_t i = 0; i < DIRECT_OPEN_SIZE; ++i)
        {
            if(mainDirection == DIRECT_OPEN[i].m_mainDirection)
            {
                // Draw lots to chose one of the open game letter: A,B,C,D,E,F. Don't matter which one.
                const uint32_t randomIndex = (rand() % CRAWLING_DIRECT_SIZE);
                pCrawlingList              = DIRECT_OPEN[i].m_crawlingChain[randomIndex].m_crawlingList;
                break;
            }
        }

        assert(NULL != pCrawlingList);

        IBoard::PositionXY xyCrawling = xyFirst;

        // Find out the position on board associated with letter that has just been drawn.
        Crawling endList{ IBoard::DIRECTION_NONE, 0 };
        for(; *pCrawlingList != endList; pCrawlingList++)
        {
            board.goDirection(xyCrawling, pCrawlingList->m_direction, pCrawlingList->m_shift);
            assert(board.isOnBoard(xyCrawling));
        }

        retVal = xyCrawling;
    }
    else if(isInDirectOpen)
    {
        // Find out main direction.
        uint32_t index = INDIRECT_PATH_SIZE;
        for(uint32_t i = 0; i < INDIRECT_PATH_SIZE; ++i)
        {
            if(IBoard::k_NEIGHBOR_NOT_FOUND != board.neighbourDistance(xyFirst, INDIRECT_PATH[i], board.getMove(xyFirst)))
            {
                index = i;
                break;
            }
        }
        assert(index < INDIRECT_PATH_SIZE);

        const IBoard::Direction mainDirection = INDIRECT_PATH[index];

        // Find chain associated with the main direction.
        Crawling * crawlingList = NULL;
        for(uint32_t i = 0; i < INDIRECT_OPEN_SIZE; ++i)
        {
            if(mainDirection == INDIRECT_OPEN[i].m_mainDirection)
            {
                // Draw lots to chose one of the open game letter: A,B,C,D,E,F. Don't matter which one.
                const uint32_t randomIndex = (rand() % CRAWLING_INDIRECT_SIZE);
                crawlingList              = INDIRECT_OPEN[i].m_crawlingChain[randomIndex].m_crawlingList;
                break;
            }
        }

        assert(NULL != crawlingList);

        IBoard::PositionXY xyCrawling = xyFirst;

        // Find out the position on board associated with letter that has just been drawn.
        Crawling endList{ IBoard::DIRECTION_NONE, 0 };
        for(; *crawlingList != endList; crawlingList++)
        {
            board.goDirection(xyCrawling, crawlingList->m_direction, crawlingList->m_shift);
            assert(board.isOnBoard(xyCrawling));
        }

        retVal = xyCrawling;
    }
    else
    {
        // means opening game is undefined.
    }

    return retVal;
}

// Provide best second move for black.
IBoard::PositionXY OpenBook::getBestSecondBlackMove(const IBoard & rBoard)
{
    // No dedicated opening-book for black.
    // Just choose randomly one of the following option

    // Direct opening(o -first move):
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . o . o . . . . . . .|
    // 3 |. . . . . . x . . . . . . . .|
    // 4 |. . . . . o . o . . . . . . .|

    static const IBoard::Direction direction[] = { IBoard::UP_RIGHT, IBoard::DOWN_RIGHT, IBoard::DOWN_LEFT,
                                                  IBoard::UP_LEFT };

    const uint32_t randomIndex = (rand() % std::size(direction));

    IBoard::PositionXY xy = XY_OUT_OF_BOARD;
    assert(rBoard.getLastMove(xy));
    assert(rBoard.canIGo(xy, direction[randomIndex]));
    rBoard.goDirection(xy, direction[randomIndex]);

    return xy;
}

/// Check if game has 'open direct' introduction.
OpenBook::OpenGameType OpenBook::openGame(const IBoard & rBoard)
{
    // Direct opening(x -first move):
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . x o . . . . . . .|
    // 4 |. . . . . . . . . . . . . . .|

    // Indirect opening(x -first move):
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . o . . . . . . .|
    // 3 |. . . . . . x . . . . . . . .|
    // 4 |. . . . . . . . . . . . . . .|

    // Moves on board to be able call this method.
    static const uint32_t minMoveOnBoard = 2;
    assert(minMoveOnBoard == rBoard.getMoveNumber());

    OpenBook::OpenGameType retVal = OpenBook::UNDEFINED;

    IBoard::PositionXY xyFirst;
    const bool status = rBoard.getFirstMove(xyFirst);
    assert(status);

    const IBoard::Player player = rBoard.getMove(xyFirst);

    for(uint32_t i = 0; i < DIRECT_PATH_SIZE; ++i)
    {
        if(IBoard::k_NEIGHBOR_NOT_FOUND != rBoard.neighbourDistance(xyFirst, DIRECT_PATH[i], player))
        {
            retVal = OpenBook::DIRECT;
            break;
        }
    }

    for(uint32_t i = 0; i < INDIRECT_PATH_SIZE; ++i)
    {
        if(IBoard::k_NEIGHBOR_NOT_FOUND != rBoard.neighbourDistance(xyFirst, INDIRECT_PATH[i], player))
        {
            // Open game cant be direct and indirect at the same time.
            assert(OpenBook::UNDEFINED == retVal);

            retVal = OpenBook::INDIRECT;
            break;
        }
    }

    return retVal;
}
