/////////////////////////////////////////////////////////////////////////////////////////
/// @file TwoPlayersGame.hpp
///
/// TwoPlayersGame interface declaration.
///
/// @par Full Description.
/// Abstract class for each 2 players boad game.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 17-Jul-2016 Initial revision.
/// - zhalat 07-Jan-2017 Change interface to be able play 'remotly' using .txt board.
/// - zhalat 21-Apr-2017 Code formating.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined(TWO_PLAYERS_GAME_HPP_)
#define TWO_PLAYERS_GAME_HPP_

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Board.hpp"
#include "SearchTreeAlgorithmIf.hpp"
#include "Score.hpp"

// FORWARD REFERENCES
class GomokuGameTest;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: TwoPlayersGame
///
/// TwoPlayersGame interface declaration.
///
/// @par Full Description.
/// Abstract class for each 2 players boad game.
///////////////////////////////////////////////////////////////////////////////////////////
class TwoPlayersGame
{
   public:
    // BackEnd -> GUI.
    static const constexpr char * TERMINATOR_MSG        = "\n##\n";
    static const constexpr char * WINNER_MSG            = "\n--->>Game over. You won.\n";
    static const constexpr char * LOOSER_MSG            = "\n--->>Game over. Computer won.\n";
    static const constexpr char * STALEMATE_MSG         = "\n--->>Game over. Stalemate.\n";
    static const constexpr char * YOUR_MOVE_MSG         = "\n--->>Your move:\n";
    static const constexpr char * LAST_CPU_MOVE_MSG     = "\n--->>Last cpu move:\n";
    static const constexpr char * LAST_HUMAN_MOVE_MSG   = "\n--->>Last human move:\n";
    static const constexpr char * INVALID_MOVE_MSG      = "\n!--->>Invalid move.\n";
    static const constexpr char * INVALID_PARAMETER_MSG = "\n!--->>Invalid parameter.\n";
    static const constexpr char * CHOOSING_COLOR_MSG    = "\n--->>Choose your color: x or o.\n";
    static const constexpr char * WINNER_MOVIES_MARK    = "w";

    // GUI -> BackEnd.
    static const constexpr char * NEW_GAME = "--->>NewGame.";

    enum Level
    {
        LEVEL_NONE   = 0,
        BEGINNER     = 1,
        INTERMEDIATE = 2,
        ADVANCED     = 3,

        // Must be the last
        LEVEL_LAST
    };

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::Init
    //
    /// Initialize of game.
    ///
    /// @par Full Description
    /// Setting basic parameter of the game.
    ///
    /// @param size       The board size.
    /// @param humanColor Humans' name/sign.
    /// @param level      Level of the game.
    /// @param isRandomize  If true isRandomize is enabled.
    /// @param maxTime    max time for cpu move.
    /// @param inStream   Input stream.
    /// @param outStream  Output stream.
    ///////////////////////////////////////////////////////////////////////
    virtual void Init(const uint32_t size, const Board::Player humanColor, const TwoPlayersGame::Level level,
                      const bool isRandomize, const uint32_t maxTime = 0, std::istream & inStream = std::cin,
                      std::ostream & outStream = std::cout) = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::Play
    //
    /// Starts game.
    ///
    /// @par Full Description
    ///
    /// Starts game.
    ///////////////////////////////////////////////////////////////////////
    virtual void Play() = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::EndGame
    //
    /// Ends game.
    ///
    /// @par Full Description
    ///
    /// Ends game.
    ///////////////////////////////////////////////////////////////////////
    virtual bool EndGame() = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::RestartGame
    //
    /// Set board to initialize state.
    ///
    /// @par Full Description
    ///
    /// Set board to initialize state..
    ///////////////////////////////////////////////////////////////////////
    virtual void RestartGame() = 0;

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
    virtual Board::PositionXY GetUserMove() const = 0;

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
    virtual bool ValidateMove(const Board::PositionXY & rXy) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: TwoPlayersGame::WinnerCheck
    //
    /// Check if player is winner.
    ///
    /// @par Full Description
    /// Check if player is winner.
    ///
    /// @param player   Player color for win checking.
    ///
    /// @return  true if winner, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool WinnerCheck(const Board::Player player) const = 0;

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
    virtual bool Stalemate() const = 0;

    /// Destructor.
    virtual ~TwoPlayersGame()
    {
#warning "Is it safe?? This points to singleton object if one remove it the other might still want get it."

        delete m_pBoard;
        delete m_pBoardScoreCpu;
        delete m_pBoardScoreHuman;
        m_pBoard           = NULL;
        m_pBoardScoreCpu   = NULL;
        m_pBoardScoreHuman = NULL;
        m_ComputerColor    = Board::PLAYER_EMPTY;
        m_HumanColor       = Board::PLAYER_EMPTY;
        m_pSearchAlgorithm = NULL;
        m_Size             = 0;
        m_Level            = LEVEL_NONE;
        m_IsRandomize      = false;
        m_MaxTime          = 0;
    };

    /// Constructor.
    TwoPlayersGame() :
        m_pBoard(NULL),
        m_pBoardScoreCpu(NULL),
        m_pBoardScoreHuman(NULL),
        m_ComputerColor(Board::PLAYER_EMPTY),
        m_HumanColor(Board::PLAYER_EMPTY),
        m_pSearchAlgorithm(NULL),
        m_Size(0),
        m_Level(LEVEL_NONE),
        m_IsRandomize(false),
        m_MaxTime(0){
            // None.
        };

   protected:
    // Board.
    Board * m_pBoard;

    // Pointers to human and computer score.
    BoardScore * m_pBoardScoreCpu;
    BoardScore * m_pBoardScoreHuman;

    // Computer/Human player color.
    Board::Player m_ComputerColor;
    Board::Player m_HumanColor;

    // Algorithm for searching best move.
    SearchTreeAlgorithmIf * m_pSearchAlgorithm;

    // Board size.
    uint32_t m_Size;
    Level m_Level;
    bool m_IsRandomize;

    // Max time for thinking in sec.
    uint32_t m_MaxTime;

    // Only for UT.
    friend GomokuGameTest;
};

#endif /* TWO_PLAYERS_GAME_HPP_ */

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
