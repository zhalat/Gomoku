#pragma once

#include <iterator>        // For std::size()
#include "Board.hpp"       // For PositionXY declaration.
#include "SingleList.hpp"  // For SingleList definition.

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: OpenBook
///
/// OpenBook interface declaration.
///
/// @par Full Description.
/// Provide third move for white.
///////////////////////////////////////////////////////////////////////////////////////////
class OpenBook
{
   public:
    enum OpenGameType
    {
        DIRECT,
        INDIRECT,
        UNDEFINED
    };

    // Helpful containers to browsing best open game move.
    struct Crawling
    {
        Board::Direction m_Direction;
        uint32_t m_Shift;

        Crawling() : m_Direction(Board::DIRECTION_NONE), m_Shift(0) {}
        Crawling(const Board::Direction direction, const uint32_t shift) : m_Direction(direction), m_Shift(shift) {}

        bool operator==(const Crawling & el)
        {
            bool retVal{ false };

            if(this->m_Direction == el.m_Direction and this->m_Shift == el.m_Shift)
            {
                retVal = true;
            }

            return retVal;
        }

        bool operator!=(const Crawling & el) { return !(*this == el); }
    };

    struct CrawlingChain
    {
        char m_SpotName;
        Crawling m_CrawlingList[3];
    };

    struct Openings
    {
        // It's constituated by two first movement.
        Board::Direction m_MainDirection;
        CrawlingChain * m_pCrawlingChain;

        Openings(const Board::Direction direction, CrawlingChain * const pCrawlingChain) :
            m_MainDirection(direction), m_pCrawlingChain(pCrawlingChain)
        {}
    };

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: OpenBook::GetBestThirdWhiteMove
    //
    /// Provide best third move for white.
    ///
    /// @par Full Description
    /// Provide best third move for white.
    ///
    /// @param rBoard Gomoku board.
    ///
    /// @retval Best third move for white player.
    ///////////////////////////////////////////////////////////////////////
    static Board::PositionXY GetBestThirdWhiteMove(const Board & rBoard);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: OpenBook::GetBestSecondBlackMove
    //
    /// Provide best second move for black.
    ///
    /// @par Full Description
    /// Provide best second move for black.
    ///
    /// @param rBoard Gomoku board.
    ///
    /// @retval Best secong move for balck player.
    ///////////////////////////////////////////////////////////////////////
    static Board::PositionXY GetBestSecondBlackMove(const Board & rBoard);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: OpenBook::OpenGame
    //
    /// Check type of opening game.
    ///
    /// @par Full Description
    /// Check if game has direct vs indirect opening.
    ///
    /// @param rBoard Gomoku board.
    ///
    /// @retval Type of game opening.
    ///////////////////////////////////////////////////////////////////////
    static OpenGameType OpenGame(const Board & rBoard);

   private:
    // Prevent either copying or assigning (>= C++11).
    OpenBook(const OpenBook & rOpenBook) = delete;
    OpenBook & operator=(const OpenBook & rOpenBook) = delete;

    // Directions to find direct or indirect kind of opening game.
    static constexpr Board::Direction DIRECT_PATH[]   = { Board::UP, Board::RIGHT, Board::DOWN, Board::LEFT };
    static constexpr Board::Direction INDIRECT_PATH[] = { Board::UP_RIGHT, Board::DOWN_RIGHT, Board::DOWN_LEFT,
                                                          Board::UP_LEFT };
    static constexpr auto DIRECT_PATH_SIZE{ std::size(DIRECT_PATH) };
    static constexpr auto INDIRECT_PATH_SIZE{ std::size(INDIRECT_PATH) };

    // Containers for direct open game.
    static const Openings DIRECT_OPEN[];
    static CrawlingChain m_CrawlingChainUp[];
    static CrawlingChain m_CrawlingChainRight[];
    static CrawlingChain m_CrawlingChainDown[];
    static CrawlingChain m_CrawlingChainLeft[];

    // Containers for indirect open game.
    static const Openings INDIRECT_OPEN[];
    static CrawlingChain m_CrawlingChainUpRight[];
    static CrawlingChain m_CrawlingChainDownRight[];
    static CrawlingChain m_CrawlingChainDownLeft[];
    static CrawlingChain m_CrawlingChainUpLeft[];

    static const uint32_t CRAWLING_DIRECT_SIZE;
    static const uint32_t CRAWLING_INDIRECT_SIZE;
    static const uint32_t DIRECT_OPEN_SIZE;
    static const uint32_t INDIRECT_OPEN_SIZE;
};

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
