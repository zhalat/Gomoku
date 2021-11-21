/////////////////////////////////////////////////////////////////////////////////////////
/// @file StateEvaluationIf.hpp
///
/// StateEvaluationIf interface declaration.
///
/// @par Full Description.
/// Abstract class for state evaluation.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 08-Aug-2017 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined(STATE_EVAL_HPP_)
#define STATE_EVAL_HPP_

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Board.hpp"  // For Board definitions.
#include "Score.hpp"

// FORWARD REFERENCES
// <none>

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: StateEvaluationIf
///
/// StateEvaluationIf interface definition.
///
/// @par Full Description.
/// Abstract class for state evaluation.
///////////////////////////////////////////////////////////////////////////////////////////
class StateEvaluationIf
{
   public:
    static const uint32_t MILESTONE_SCORE = (Score::THREAT_WINNER_SCORE / 2);
    static const uint32_t BONUS_SCORE     = (Score::THREAT_WINNER_SCORE / 100);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluationIf::IsWinner
    //
    /// Check if you are  winner.
    ///
    /// @par Full Description
    /// Check if you are  winner.
    //
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up threat.
    /// @param rStateScore   A score assigned to the state.
    ///
    /// @retval True if game over, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool IsWinner(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluationIf::IsLooser
    //
    /// Check if you are looser.
    ///
    /// @par Full Description
    /// Check if you are looser.
    //
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up threat.
    /// @param rStateScore   A score assigned to the state.
    ///
    /// @retval True if game over, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool IsLooser(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluationIf::ImpliciteWinner
    //
    /// Predict the winner.
    ///
    /// @par Full Description
    /// Quick evaluate board to find winner.
    ///
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up threat.
    /// @param rStateScore   A score assigned to the state.
    ///
    /// @retval True if implicit winner was found.
    /////////////////////////////////////////////////////////////////////////////////////
    virtual bool ImpliciteWinner(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluationIf::ImpliciteLooser
    //
    /// Predict the looser.
    ///
    /// @par Full Description
    /// Quick evaluate board to find looser.
    ///
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up threat.
    /// @param rStateScore   A score assigned to the state.
    ///
    /// @retval True if implicit winner was found.
    /////////////////////////////////////////////////////////////////////////////////////
    virtual bool ImpliciteLooser(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluationIf::RegularEval
    //
    /// Asses the board in regular manner.
    ///
    /// @par Full Description
    /// Asses the board in regular manner.
    ///
    /// @param isMaxPlayer Indicate if state is evaluating from max player (cpu)
    ///					   perspective.
    /// @param stateScore  Variable where score state is written.
    ///
    /// @retval True if bonus was added to score, false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    virtual bool RegularEval(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluationIf::ExtendWinnerThreatMove
    //
    /// Finds existing winner-threat nad make it better.
    ///
    /// @par Full Description
    /// Build up existing 4ABC threat to win.
    ///
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up threat.
    /// @param rStateScore   A score assigned to the state.
    ///
    /// @retval True if existing winner threat was found.
    /////////////////////////////////////////////////////////////////////////////////////
    virtual bool ExtendWinnerThreatMove(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                        int & rStateScore) const = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluationIf::ExtendWinnerActionMove
    //
    /// Finds existing winner-action and make it better.
    ///
    /// @par Full Description
    /// Finds existing winner-action and make it better.
    ///
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up action.
    /// @param rStateScore   A score assigned to the state.
    ///
    /// @retval True if extending action move was found, false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    virtual bool ExtendWinnerActionMove(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                        int & rStateScore) const = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluationIf::SetBoards
    //
    /// Set boards for evaluation.
    ///
    /// @param rBoardScoreCpu   CPU board score reference to evaluation score.
    /// @param rBoardScoreHuman Human board score reference to evaluation score.
    ///
    /// @par Full Description
    /// Set boards for evaluation.
    ///////////////////////////////////////////////////////////////////////
    virtual void SetBoards(const BoardScore & rBoardScoreCpu, const BoardScore & rBoardScoreHuman) = 0;
};

#endif /* STATE_EVAL_HPP_ */

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
