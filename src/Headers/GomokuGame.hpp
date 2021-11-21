/////////////////////////////////////////////////////////////////////////////////////////
/// @file GomokuGame.hpp
///
/// Gomoku game logic class declaration.
///
/// @par Full Description.
/// Gomoku game class declaration.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 25-Jun-2016 Initial revision.
/// - zhalat 17-Jan-2017 Change interface to be able playing external app via pipe.
/// - zhalat 20-Apr-2017 Interface for keeping input/output stream.
/// - zhalat 28-Oct-2017 Added GetInitCandidates().
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined(GOMOKU_GAME)
#define GOMOKU_GAME

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Logger.hpp"
#include "Board.hpp"
#include "TwoPlayerGame.hpp"

// FORWARD REFERENCES
// <none>

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Score
///
/// Gomoku game logic - user interface.
///
/// @par Full Description.
/// Gomoku game class declaration.
///////////////////////////////////////////////////////////////////////////////////////////
class GomokuGame : public TwoPlayersGame
{
   public:
    static constexpr uint32_t MIN_BOARD_SIZE     = 5;
    static constexpr uint32_t DEFAULT_BOARD_SIZE = 15;
    static constexpr uint32_t MAX_BOARD_SIZE     = 19;

    // After those moves number cpu can stop to be 	defensive.
    static constexpr uint32_t STOP_TO_BE_DEFENSIVE = 10;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::Init
    //
    /// Initialize of game.
    ///
    /// @par Full Description
    /// Setting basic parameter of the game.
    ///
    /// @param size        The board size.
    /// @param humanColor  Humans' name/sign.
    /// @param level       Level of the game.
    /// @param isRandomize If true  is enabled.
    /// @param maxTime     max time for cpu move.
    /// @param inStream    Input stream. std::cin is default.
    /// @param outStream   Output stream. std::cout is default.
    ///////////////////////////////////////////////////////////////////////
    virtual void Init(const uint32_t size, const Board::Player humanColor, const TwoPlayersGame::Level level,
                      const bool isRandomize, const uint32_t maxTime = 0, std::istream & inStream = std::cin,
                      std::ostream & outStream = std::cout);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: GomokuGame::Play
    //
    /// Starts game.
    ///
    /// @par Full Description
    ///
    /// Starts Gomoku game.
    ///////////////////////////////////////////////////////////////////////
    virtual void Play();

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::EndGame
    //
    /// Ends game.
    ///
    /// @par Full Description
    ///
    /// Ends game.
    ///////////////////////////////////////////////////////////////////////
    virtual bool EndGame();

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::RestartGame
    //
    /// Set board to initialize state.
    ///
    /// @par Full Description
    ///
    /// Set board to initialize state..
    ///////////////////////////////////////////////////////////////////////
    virtual void RestartGame();

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::GetUserMove
    //
    /// Fetch user move.
    ///
    /// @par Full Description
    /// Fetch user move from input stream.
    ///
    /// @retval True if success, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual Board::PositionXY GetUserMove() const;

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::ValidateMove
    //
    /// Validate move.
    ///
    /// @par Full Description
    /// Check if provided move can be applied on board.
    ///
    /// @param rXy Move to be validated.
    ///
    /// @retval True if move is valid, false otherwise.
    /////////////////////////////////////////////////////////////////////////////
    virtual bool ValidateMove(const Board::PositionXY & rXy) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::WinnerCheck
    //
    /// Check against winner.
    ///
    /// @par Full Description
    /// Check if player is winner.
    ///
    /// @param player   Player color for win checking.
    ///
    /// @return  true if winner, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool WinnerCheck(const Board::Player player) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::Stalemate
    //
    /// Check against stalemate.
    ///
    /// @par Full Description
    /// Check against stalemate.
    ///
    /// @return  true if stalemate, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool Stalemate() const;

    // Default constructor.
    GomokuGame() : pInputStream(NULL), pOutputStream(NULL) {}

    // Destructor.
    virtual ~GomokuGame() {}

   private:
    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: GomokuGame::SetSearchAlgorithm
    //
    /// Set searching algorithm.
    ///
    /// @par Full Description
    /// Set searching algorithm.
    ///////////////////////////////////////////////////////////////////////
    void SetSearchAlgorithm(const Level level);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: GomokuGame::GetBestMove
    //
    /// Get the best move.
    ///
    /// @par Full Description
    /// Depending on player level, searching for best move.
    ///////////////////////////////////////////////////////////////////////
    Board::PositionXY GetBestMove();

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: GomokuGame::GetInitCandidates
    //
    /// Provide initial candidates at specified depth.
    ///
    /// @par Full Description
    /// Set searching algorithm.
    ///
    /// @param rInitCandidates Initial best candidates.
    /// @param initDepht       Depth to search in the tree.
    ///////////////////////////////////////////////////////////////////////
    void GetInitCandidates(SearchTreeAlgorithmIf::PriorityQueueScore & rInitCandidates, const uint32_t initDepht) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: GomokuGame::RandomizeBestMove
    //
    /// Provide randomized move.
    ///
    /// @par Full Description
    /// Search thru n best move to get one of the best.
    ///
    /// @param nBestMoves 		Initial best candidates.
    /// @param diversityPercent Says how much % can be weaker comparing to top.
    ///////////////////////////////////////////////////////////////////////
    Board::PositionXY RandomizeBestMove(const SearchTreeAlgorithmIf::PriorityQueueScore & nBestMoves,
                                        const uint32_t diversityPercent) const;

    // Stream from/to data to be read/write.
    std::istream * pInputStream;
    std::ostream * pOutputStream;

    // Record game.
    Logger m_Logger;
};

#endif /* GOMOKU_GAME */

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
