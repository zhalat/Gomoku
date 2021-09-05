#pragma once

#include <assert.h>               // For assert.
#include "BoardScore.hpp"         // For Board Score.
#include "StateEvaluationIf.hpp"  // For StateEvaluationIf interface.
#include "ObserverIf.hpp"         // For Observer design pattern interface.

// FORWARD REFERENCES
class StateEvaluationTest;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: StateEvaluation
///
/// StateEvaluation class.
///
/// @par Full Description.
/// Estimate how good a board state is.
///////////////////////////////////////////////////////////////////////////////////////////
class StateEvaluation
    : public StateEvaluationIf
    , public Observer::ObserverIf
{
   public:
    /// Lists all heuristic actions.
    enum HeadShotAction
    {
        HEAD_SHOOT_4BC,
        HEAD_SHOOT_3A,
        HEAD_SHOOT_3AA,
        HEAD_SHOOT_DRAGON,
        HEAD_SHOOT_LIZARD,
        HEAD_SHOOT_DOUBLE_3A_ONE_STROKE,
        MITIGATION_DOUBLE_3A,
        MITIGATION_3A
    };

    static constexpr int HEAD_SHOT_ACTION_NUMBER = 8;

    typedef bool (StateEvaluation::*FuncPtr)(const bool, Board::PositionXY &, bool, const BoardScore *,
                                             const BoardScore *) const;
    // using FuncPtr = bool( StateEvaluation::* )( const bool, Board::PositionXY&, bool, const BoardScore*, const
    // BoardScore* ) const;

    /// The head shot action state.
    struct HeadShotActionState
    {
        bool m_IsUpToDate;
        bool m_IsPossible;
        Board::PositionXY m_StateMove;
        FuncPtr const m_pFuncPtr;

        void Clear() { m_IsUpToDate = false; }
    };

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluationIf::IsWinner
    //
    /// Check if there is a winner.
    ///
    /// @par Full Description
    /// Check if there is a winner.
    //
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up threat.
    /// @param rStateScore   A score assigned to the state.
    ///
    /// @retval True if game over, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool IsWinner(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const;

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
    virtual bool IsLooser(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const;

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
    virtual bool ImpliciteWinner(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const;

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
    virtual bool ImpliciteLooser(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const;

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
    virtual bool RegularEval(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluationIf::ExtendWinnerThreatMove
    //
    /// Finds existing winner-threat and make it better.
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
                                        int & rStateScore) const;

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
                                        int & rStateScore) const;

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
    virtual void SetBoards(const BoardScore & rBoardScoreCpu, const BoardScore & rBoardScoreHuman);

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: ObserverIf::Update
    //
    /// Fetching new data from Subject interface.
    ///
    /// @par Full Description
    /// Invoked by Subject. Fetching new data from Subject interface.
    /////////////////////////////////////////////////////////////////////////////
    virtual void Update() const;

    ////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::GetInstance
    //
    /// Get instance of StateEvaluation.
    ///
    /// @par Full Description
    /// Get instance of StateEvaluation.
    ///
    /// @return pointer to StateEvaluation instance.
    /////////////////////////////////////////////////////////////////////////////////////
    static StateEvaluation * GetInstance();

   private:
    /// Constructor.
    StateEvaluation() : m_pBoard(NULL), m_pBoardScoreCpu(NULL), m_pBoardScoreHuman(NULL)
    {
        // Nothing to do.
    }

    /// Private copy constructor - forbid copying.
    StateEvaluation(const StateEvaluation &) = delete;

    /// Private assign operator - forbid copying.
    StateEvaluation & operator=(const StateEvaluation &) = delete;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::HeadShotRun
    //
    /// Check if provided head shot is possible.
    /// It run specified head shot only if it's neccesary (board state was changed
    /// - observed subject).
    /// Use this method rather than invoking the single one.
    ///
    /// @param headShotAction Head shot name to check.
    /// @param isMaxPlayer    		 Indicate if state is evaluating from max player (cpu) perspective.
    /// @param rShotMove      		 A new move to build/mitigate action.
    /// @param checkWinnerCondition  A new move to build/mitigate action.
    ///
    /// @retval True if provided headshot is possible, false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    bool HeadShotRun(const HeadShotAction headShotAction, const bool isMaxPlayer, Board::PositionXY & rShotMove,
                     const bool checkWinnerCondition) const;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::IsHeadShot4BCPossible
    //
    /// Check if isMaxPlayer is possible to create headshot4BC.
    ///
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up action.
    ///
    /// @retval True if headshot 4BC is possible, false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    bool IsHeadShot4BCPossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                               const bool checkWinnerMoveCondition = true, const BoardScore * pCpuBoardScore = NULL,
                               const BoardScore * pHumanBoardScore = NULL) const;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::IsHeadShot3APossible
    //
    /// Check if isMaxPlayer is possible to create headshot3A.
    ///
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up action.
    ///
    /// @retval True if headshot 3A is possible, false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    bool IsHeadShot3APossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                              const bool checkWinnerMoveCondition = true, const BoardScore * pCpuBoardScore = NULL,
                              const BoardScore * pHumanBoardScore = NULL) const;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::IsHeadShot3AAPossible
    //
    /// Check if isMaxPlayer is possible to create headshot3AA.
    ///
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up action.
    ///
    /// @retval True if headshot 3AA is possible, false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    bool IsHeadShot3AAPossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                               const bool checkWinnerMoveCondition = true, const BoardScore * pCpuBoardScore = NULL,
                               const BoardScore * pHumanBoardScore = NULL) const;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::IsHeadShotDragonPossible
    //
    /// Check if isMaxPlayer is able to create 'Dragon' attack.
    /// You have two 3BC such located that after extending one 'Head Shoot 3A is possible'.
    ///
    /// @param isMaxPlayer    Indicate if state is evaluated from max player (cpu)
    ///					      perspective.
    /// @param rBuildDownMove A new move to build up action.
    ///
    /// @retval True if adversary isMaxPlayer is able to crate threat,
    ///         false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    bool IsHeadShotDragonPossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                  const bool checkWinnerMoveCondition = true, const BoardScore * pCpuBoardScore = NULL,
                                  const BoardScore * pHumanBoardScore = NULL) const;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::IsHeadShotLizardPossible
    //
    /// Check if isMaxPlayer is able to create 'Lizard' attack.
    /// You have two 3BC such located that after extending both 'Double 3A at one stroke'
    /// possible.
    ///
    /// @param isMaxPlayer    Indicate if state is evaluated from max player (cpu)
    ///					      perspective.
    /// @param rBuildDownMove A new move to build up action.
    ///
    /// @retval True if adversary isMaxPlayer is able to crate threat,
    ///         false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    bool IsHeadShotLizardPossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                  const bool checkWinnerMoveCondition = true, const BoardScore * pCpuBoardScore = NULL,
                                  const BoardScore * pHumanBoardScore = NULL) const;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::IsDouble3AOneStrokePossible
    //
    /// Check if isMaxPlayer is able to create double 3A threats.
    ///
    /// @param isMaxPlayer   Indicate if state is evaluating from max player (cpu)
    ///					     perspective.
    /// @param rBuildUpMove  A new move to build up action.
    ///
    /// @retval True if isMaxPlayer is able to crate double 3A threats, false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    bool IsDouble3AOneStrokePossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                     const bool checkWinnerMoveCondition = true,
                                     const BoardScore * pCpuBoardScore   = NULL,
                                     const BoardScore * pHumanBoardScore = NULL) const;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::IsDouble3AMitigationPossible
    //
    /// Check if !isMaxPlayer is able to mitigate the opponent double threats.
    /// Your state is 2x3A is being tried to be mitigated by opponent.
    ///
    /// @param isMaxPlayer    Indicate if state is evaluated from max player (cpu)
    ///					      perspective.
    /// @param rBuildDownMove A new move to build up action.
    ///
    /// @retval True if adversary isMaxPlayer is able to mitigate  isMaxPlayer threats,
    ///         false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    bool IsDouble3AMitigationPossible(const bool isMaxPlayer, Board::PositionXY & rBuildDownMove,
                                      const bool checkWinnerMoveCondition = true,
                                      const BoardScore * pCpuBoardScore   = NULL,
                                      const BoardScore * pHumanBoardScore = NULL) const;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::IsBlockAndAttack3APossible
    //
    /// Check if isMaxPlayer is able to mitigate my 3A threat and attack building its own 3A at one stone.
    /// Your state 3A is being tried to be mitigated by opponent 2A->3A or 3BC->4BC
    ///
    /// @param isMaxPlayer    Indicate if state is evaluated from max player (cpu)
    ///					      perspective.
    /// @param rBuildDownMove A new move to build up action.
    ///
    /// @retval True if adversary isMaxPlayer is able to mitigate  isMaxPlayer threats,
    ///         false otherwise.
    /////////////////////////////////////////////////////////////////////////////////////
    bool IsBlockAndAttack3APossible(const bool isMaxPlayer, Board::PositionXY & rBuildDownMove,
                                    const bool checkWinnerMoveCondition = true,
                                    const BoardScore * pCpuBoardScore   = NULL,
                                    const BoardScore * pHumanBoardScore = NULL) const;

    /////////////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: StateEvaluation::GetBonus
    //
    /// Adds extra points for good action. Action are not strong enough to be winner.
    ///
    /// @param isMaxPlayer    Indicate if state is evaluated from max player (cpu)
    ///					      perspective.
    /// @param rBuildDownMove A new move to build up action.
    ///
    /// @retval Bonus socre or 0 if good action not found.
    /////////////////////////////////////////////////////////////////////////////////////
    int GetBonus(const bool isMaxPlayer, Board::PositionXY & rBuildDownMove, const bool checkWinnerMoveCondition = true,
                 const BoardScore * pCpuBoardScore = NULL, const BoardScore * pHumanBoardScore = NULL) const;

    /// Head shot action state for max and min player.
    static HeadShotActionState m_HeadShotActionStateMaxConditionCheckerEnabled[HEAD_SHOT_ACTION_NUMBER];
    static HeadShotActionState m_HeadShotActionStateMinConditionCheckerEnabled[HEAD_SHOT_ACTION_NUMBER];
    static HeadShotActionState m_HeadShotActionStateMaxConditionCheckerDisabled[HEAD_SHOT_ACTION_NUMBER];
    static HeadShotActionState m_HeadShotActionStateMinConditionCheckerDisabled[HEAD_SHOT_ACTION_NUMBER];

    // Board state.
    mutable Board * m_pBoard;
    const BoardScore * m_pBoardScoreCpu;
    const BoardScore * m_pBoardScoreHuman;

    // For UT
    friend class TEST_StateEvaluationTest_IsHeadShot4BCPossibleTest1_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot4BCPossibleTest2_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot4BCPossibleTest3_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot4BCPossibleTest4_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot4BCPossibleTest5_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot4BCPossibleTest6_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot4BCPossibleTest7_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot4BCPossibleTest8_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot4BCPossibleTest9_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest1_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest2_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest3_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest4_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest5_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest6_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest7_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest8_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest9_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest10_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest11_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest12_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest13_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest14_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest15_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3APossibleTest16_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3AAPossibleTest1_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3AAPossibleTest2_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3AAPossibleTest3_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3AAPossibleTest4_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3AAPossibleTest5_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3AAPossibleTest6_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3AAPossibleTest7_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3AAPossibleTest8_Test;
    friend class TEST_StateEvaluationTest_IsHeadShot3AAPossibleTest9_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotDragonPossibleTest1_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotDragonPossibleTest2_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotDragonPossibleTest3_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotDragonPossibleTest4_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotDragonPossibleTest5_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotDragonPossibleTest6_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotDragonPossibleTest7_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotDragonPossibleTest8_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotLizardPossibleTest1_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotLizardPossibleTest2_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotLizardPossibleTest3_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotLizardPossibleTest4_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotLizardPossibleTest5_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotLizardPossibleTest6_Test;
    friend class TEST_StateEvaluationTest_IsHeadShotLizardPossibleTest7_Test;
    friend class TEST_StateEvaluationTest_IsDouble3AOneStrokePossibleTest1_Test;
    friend class TEST_StateEvaluationTest_IsDouble3AOneStrokePossibleTest2_Test;
    friend class TEST_StateEvaluationTest_IsDouble3AOneStrokePossibleTest3_Test;
    friend class TEST_StateEvaluationTest_IsDouble3AOneStrokePossibleTest4_Test;
    friend class TEST_StateEvaluationTest_IsDouble3AOneStrokePossibleTest5_Test;
    friend class TEST_StateEvaluationTest_IsDouble3AOneStrokePossibleTest6_Test;
    friend class TEST_StateEvaluationTest_IsDouble3AOneStrokePossibleTest7_Test;
    friend class TEST_StateEvaluationTest_IsDouble3AOneStrokePossibleTest8_Test;
    friend class TEST_StateEvaluationTest_IsDouble3AOneStrokePossibleTest9_Test;
    friend class TEST_StateEvaluationTest_IsDoubleThreatMitigationPossibleTest1_Test;
    friend class TEST_StateEvaluationTest_IsDoubleThreatMitigationPossibleTest2a_Test;
    friend class TEST_StateEvaluationTest_IsDoubleThreatMitigationPossibleTest2b_Test;
    friend class TEST_StateEvaluationTest_IsDoubleThreatMitigationPossibleTest3_Test;
    friend class TEST_StateEvaluationTest_IsDoubleThreatMitigationPossibleTest4_Test;
    friend class TEST_StateEvaluationTest_IsDoubleThreatMitigationPossibleTest5_Test;
    friend class TEST_StateEvaluationTest_IsDoubleThreatMitigationPossibleTest6_Test;
    friend class TEST_StateEvaluationTest_IsDoubleThreatMitigationPossibleTest7_Test;
    friend class TEST_StateEvaluationTest_IsDoubleThreatMitigationPossibleTest8_Test;
    friend class TEST_StateEvaluationTest_IsSingle3AThreatMitigationPossibleTest1_Test;
    friend class TEST_StateEvaluationTest_IsSingle3AThreatMitigationPossibleTest2_Test;
    friend class TEST_StateEvaluationTest_IsSingle3AThreatMitigationPossibleTest3_Test;
    friend class TEST_StateEvaluationTest_IsSingle3AThreatMitigationPossibleTest4_Test;
    friend class TEST_StateEvaluationTest_IsSingle3AThreatMitigationPossibleTest5_Test;
    friend class TEST_StateEvaluationTest_IsSingle3AThreatMitigationPossibleTest6_Test;
    friend class TEST_StateEvaluationTest_IsSingle3AThreatMitigationPossibleTest7_Test;
    friend class TEST_StateEvaluationTest_IsSingle3AThreatMitigationPossibleTest8_Test;
    friend class TEST_StateEvaluationTest_IsSingle3AThreatMitigationPossibleTest9_Test;
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
