#include <assert.h>      // For assert.
#include <cstdlib>       // For srand().
#include "OpenBook.hpp"  // For declaration.
#include "Board.hpp"     // For Board interface.

// Point beyond the board. Useful for initialization.
static const Board::PositionXY XY_OUT_OF_BOARD =
    Board::PositionXY(Board::PositionXY::INVALID_FIELD, Board::PositionXY::INVALID_FIELD);

const OpenBook::Openings OpenBook::DIRECT_OPEN[] = { { Board::UP, OpenBook::m_CrawlingChainUp },
                                                     { Board::RIGHT, OpenBook::m_CrawlingChainRight },
                                                     { Board::DOWN, OpenBook::m_CrawlingChainDown },
                                                     { Board::LEFT, OpenBook::m_CrawlingChainLeft } };
const uint32_t OpenBook::DIRECT_OPEN_SIZE        = std::size(OpenBook::DIRECT_OPEN);

const OpenBook::Openings OpenBook::INDIRECT_OPEN[] = { { Board::UP_RIGHT, OpenBook::m_CrawlingChainUpRight },
                                                       { Board::DOWN_RIGHT, OpenBook::m_CrawlingChainDownRight },
                                                       { Board::DOWN_LEFT, OpenBook::m_CrawlingChainDownLeft },
                                                       { Board::UP_LEFT, OpenBook::m_CrawlingChainUpLeft } };
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
OpenBook::CrawlingChain OpenBook::m_CrawlingChainUp[] = {
    { 'A', { { Board::UP, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'B', { { Board::UP_LEFT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'C', { { Board::UP_RIGHT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'D', { { Board::LEFT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'E', { { Board::RIGHT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'F', { { Board::DOWN, 2 }, { Board::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainRight[] = {
    { 'A', { { Board::RIGHT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'B', { { Board::UP_RIGHT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'C', { { Board::DOWN_RIGHT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'D', { { Board::UP, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'E', { { Board::DOWN, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'F', { { Board::LEFT, 2 }, { Board::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainDown[] = {
    { 'A', { { Board::DOWN, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'B', { { Board::DOWN_RIGHT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'C', { { Board::DOWN_LEFT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'D', { { Board::RIGHT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'E', { { Board::LEFT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'F', { { Board::UP, 2 }, { Board::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainLeft[] = {
    { 'A', { { Board::LEFT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'B', { { Board::DOWN_LEFT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'C', { { Board::UP_LEFT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'D', { { Board::DOWN, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'E', { { Board::UP, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'F', { { Board::RIGHT, 2 }, { Board::DIRECTION_NONE, 0 } } }
};

const uint32_t OpenBook::CRAWLING_DIRECT_SIZE = std::size(m_CrawlingChainUp);

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
OpenBook::CrawlingChain OpenBook::m_CrawlingChainUpRight[] = {
    { 'G', { { Board::LEFT, 1 }, { Board::UP, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'H', { { Board::UP, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'I', { { Board::LEFT, 1 }, { Board::UP, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'J', { { Board::RIGHT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'M', { { Board::DOWN_RIGHT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'K', { { Board::RIGHT, 2 }, { Board::DOWN, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'L', { { Board::DOWN, 1 }, { Board::LEFT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'N', { { Board::DOWN, 2 }, { Board::LEFT, 1 }, { Board::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainDownRight[] = {
    { 'G', { { Board::RIGHT, 2 }, { Board::UP, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'H', { { Board::RIGHT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'I', { { Board::RIGHT, 1 }, { Board::UP, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'J', { { Board::DOWN, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'M', { { Board::DOWN_LEFT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'K', { { Board::DOWN, 2 }, { Board::LEFT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'L', { { Board::UP, 2 }, { Board::LEFT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'N', { { Board::UP, 1 }, { Board::LEFT, 2 }, { Board::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainDownLeft[] = {
    { 'G', { { Board::RIGHT, 1 }, { Board::DOWN, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'H', { { Board::DOWN, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'I', { { Board::RIGHT, 1 }, { Board::DOWN, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'J', { { Board::LEFT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'M', { { Board::UP_LEFT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'K', { { Board::UP, 1 }, { Board::LEFT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'L', { { Board::UP, 1 }, { Board::RIGHT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'N', { { Board::UP, 2 }, { Board::RIGHT, 1 }, { Board::DIRECTION_NONE, 0 } } }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainUpLeft[] = {
    { 'G', { { Board::LEFT, 2 }, { Board::DOWN, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'H', { { Board::LEFT, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'I', { { Board::LEFT, 1 }, { Board::DOWN, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'J', { { Board::UP, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'M', { { Board::UP_RIGHT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'K', { { Board::RIGHT, 1 }, { Board::UP, 2 }, { Board::DIRECTION_NONE, 0 } } },
    { 'L', { { Board::DOWN, 2 }, { Board::RIGHT, 1 }, { Board::DIRECTION_NONE, 0 } } },
    { 'N', { { Board::RIGHT, 2 }, { Board::DOWN, 1 }, { Board::DIRECTION_NONE, 0 } } }
};

const uint32_t OpenBook::CRAWLING_INDIRECT_SIZE = std::size(m_CrawlingChainUpRight);

/// Provide best third move for white.
Board::PositionXY OpenBook::GetBestThirdWhiteMove(const Board & rBoard)
{
    Board::PositionXY retVal = XY_OUT_OF_BOARD;

    // Get the first move.
    Board::PositionXY xyFirst;
    const bool status = rBoard.GetFirstMove(xyFirst);
    assert(status);

    // Checks kind of open game.
    const bool isDirectOpen   = (OpenBook::DIRECT == OpenGame(rBoard));
    const bool isInDirectOpen = (OpenBook::INDIRECT == OpenGame(rBoard));

    if(isDirectOpen)
    {
        // Find out main direction.
        uint32_t index = DIRECT_PATH_SIZE;
        for(uint32_t i = 0; i < DIRECT_PATH_SIZE; ++i)
        {
            if(Board::NO_NEIGHBOR_FOUND != rBoard.NeighbourDistance(xyFirst, DIRECT_PATH[i], rBoard.GetMove(xyFirst)))
            {
                index = i;
                break;
            }
        }
        assert(index < DIRECT_PATH_SIZE);

        const Board::Direction mainDirection = DIRECT_PATH[index];

        // Find chain associated with the main direction.
        Crawling * pCrawlingList = NULL;
        for(uint32_t i = 0; i < DIRECT_OPEN_SIZE; ++i)
        {
            if(mainDirection == DIRECT_OPEN[i].m_MainDirection)
            {
                // Draw lots to chose one of the open game letter: A,B,C,D,E,F. Don't matter which one.
                const uint32_t randomIndex = (rand() % CRAWLING_DIRECT_SIZE);
                pCrawlingList              = DIRECT_OPEN[i].m_pCrawlingChain[randomIndex].m_CrawlingList;
                break;
            }
        }

        assert(NULL != pCrawlingList);

        Board::PositionXY xyCrawling = xyFirst;

        // Find out the position on board associated with letter that has just been drawn.
        Crawling endList{ Board::DIRECTION_NONE, 0 };
        for(; *pCrawlingList != endList; pCrawlingList++)
        {
            rBoard.GoDirection(xyCrawling, pCrawlingList->m_Direction, pCrawlingList->m_Shift);
            assert(rBoard.IsOnBoard(xyCrawling));
        }

        retVal = xyCrawling;
    }
    else if(isInDirectOpen)
    {
        // Find out main direction.
        uint32_t index = INDIRECT_PATH_SIZE;
        for(uint32_t i = 0; i < INDIRECT_PATH_SIZE; ++i)
        {
            if(Board::NO_NEIGHBOR_FOUND != rBoard.NeighbourDistance(xyFirst, INDIRECT_PATH[i], rBoard.GetMove(xyFirst)))
            {
                index = i;
                break;
            }
        }
        assert(index < INDIRECT_PATH_SIZE);

        const Board::Direction mainDirection = INDIRECT_PATH[index];

        // Find chain associated with the main direction.
        Crawling * pCrawlingList = NULL;
        for(uint32_t i = 0; i < INDIRECT_OPEN_SIZE; ++i)
        {
            if(mainDirection == INDIRECT_OPEN[i].m_MainDirection)
            {
                // Draw lots to chose one of the open game letter: A,B,C,D,E,F. Don't matter which one.
                const uint32_t randomIndex = (rand() % CRAWLING_INDIRECT_SIZE);
                pCrawlingList              = INDIRECT_OPEN[i].m_pCrawlingChain[randomIndex].m_CrawlingList;
                break;
            }
        }

        assert(NULL != pCrawlingList);

        Board::PositionXY xyCrawling = xyFirst;

        // Find out the position on board associated with letter that has just been drawn.
        Crawling endList{ Board::DIRECTION_NONE, 0 };
        for(; *pCrawlingList != endList; pCrawlingList++)
        {
            rBoard.GoDirection(xyCrawling, pCrawlingList->m_Direction, pCrawlingList->m_Shift);
            assert(rBoard.IsOnBoard(xyCrawling));
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
Board::PositionXY OpenBook::GetBestSecondBlackMove(const Board & rBoard)
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

    static const Board::Direction direction[] = { Board::UP_RIGHT, Board::DOWN_RIGHT, Board::DOWN_LEFT,
                                                  Board::UP_LEFT };

    const uint32_t randomIndex = (rand() % std::size(direction));

    Board::PositionXY xy = XY_OUT_OF_BOARD;
    assert(rBoard.GetLastMove(xy));
    assert(rBoard.CanIGo(xy, direction[randomIndex]));
    rBoard.GoDirection(xy, direction[randomIndex]);

    return xy;
}

/// Check if game has 'open direct' introduction.
OpenBook::OpenGameType OpenBook::OpenGame(const Board & rBoard)
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
    assert(minMoveOnBoard == rBoard.GetMoveNumber());

    OpenBook::OpenGameType retVal = OpenBook::UNDEFINED;

    Board::PositionXY xyFirst;
    const bool status = rBoard.GetFirstMove(xyFirst);
    assert(status);

    const Board::Player player = rBoard.GetMove(xyFirst);

    for(uint32_t i = 0; i < DIRECT_PATH_SIZE; ++i)
    {
        if(Board::NO_NEIGHBOR_FOUND != rBoard.NeighbourDistance(xyFirst, DIRECT_PATH[i], player))
        {
            retVal = OpenBook::DIRECT;
            break;
        }
    }

    for(uint32_t i = 0; i < INDIRECT_PATH_SIZE; ++i)
    {
        if(Board::NO_NEIGHBOR_FOUND != rBoard.NeighbourDistance(xyFirst, INDIRECT_PATH[i], player))
        {
            // Open game cant be direct and indirect at the same time.
            assert(OpenBook::UNDEFINED == retVal);

            retVal = OpenBook::INDIRECT;
            break;
        }
    }

    return retVal;
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
