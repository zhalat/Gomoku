#pragma once
#include <gtest/gtest_prod.h>
#include <assert.h>
#include <memory>
#include <stack>
#include "Interfaces/IBoard.h"
#include "Interfaces/IEvalBoard.h"
#include "Interfaces/IObserver.h"

using namespace std;

class EvalBoard final
    : public IEvalBoard
    , public Observer::IObserver
{
   public:
    static constexpr uint32_t k_HEAD_SHOT_ACTION_NUMBER = 8;

    typedef bool (EvalBoard::*FuncPtr)(const bool, IBoard::PositionXY&, const IBoard&, const ThreatTracker&, const ThreatTracker&) const;
    enum HeadShotAction : uint8_t
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

    struct HeadShotActionState
    {
        bool m_isUpToDate;
        bool m_isPossible;
        IBoard::PositionXY m_stateMove;
        FuncPtr const m_pFuncPtr;
        void clear() { m_isPossible = false; }
    };

    void setBoards(const IBoard& board,  const ThreatTracker& trackerCpu,const ThreatTracker& trackerHuman) override;
    bool isWinner(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const override;
    bool isLooser(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const override;
    bool implicitWinner(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const override;
    bool implicitLooser(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const override;
    bool regularEval(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const override;
    bool extendWinnerThreatMove(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const override;
    bool extendWinnerActionMove(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const override;
    void update() const override;

    EvalBoard() =default;
    EvalBoard(const EvalBoard &&) = delete;
    EvalBoard(const EvalBoard &) = delete;
    EvalBoard & operator=(const EvalBoard &) = delete;
    EvalBoard & operator=(const EvalBoard &&) = delete;
    ~EvalBoard()=default;

private:
    bool headShotRun(const HeadShotAction headShotAction, const bool isMaxPlayer, IBoard::PositionXY & rShotMove) const;
    bool isHeadShot4BCPossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const;
    bool isHeadShot3APossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const;
    bool isHeadShot3AAPossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const;
    bool isHeadShotDragonPossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const;
    bool isHeadShotLizardPossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const;
    bool isDouble3AOneStrokePossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const;
    bool isDouble3AMitigationPossible(const bool isMaxPlayer, IBoard::PositionXY& buildDownMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const;
    bool isBlockAndAttack3APossible(const bool isMaxPlayer, IBoard::PositionXY& buildDownMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const;

    int getBonus(const bool isMaxPlayer, IBoard::PositionXY & buildDownMove) const;

    //utilities
    void createCopyState( const IBoard& board,
                          const ThreatTracker& mySt,
                          const ThreatTracker& adversarySt,
                          shared_ptr<IBoard>& boardCpy,
                          shared_ptr<ThreatTracker>& myStCpy,
                          shared_ptr<ThreatTracker>& adversaryStCpy) const;
    void backFromCopyState(const IBoard& board) const;

    /// Head shot action state for max and min player.
    static HeadShotActionState m_headShotActionStateMaxConditionCheckerEnabled[k_HEAD_SHOT_ACTION_NUMBER];
    static HeadShotActionState m_headShotActionStateMinConditionCheckerEnabled[k_HEAD_SHOT_ACTION_NUMBER];
    static HeadShotActionState m_headShotActionStateMaxConditionCheckerDisabled[k_HEAD_SHOT_ACTION_NUMBER];
    static HeadShotActionState m_headShotActionStateMinConditionCheckerDisabled[k_HEAD_SHOT_ACTION_NUMBER];

    // Board state.
    const IBoard* m_board{nullptr};
    const ThreatTracker* m_trackerCpu{nullptr};
    const ThreatTracker* m_trackerHuman{nullptr};

    FRIEND_TEST(HeadShot4BCTest, TestName);
    FRIEND_TEST(HeadShot3ATest, TestName);
    FRIEND_TEST(HeadShot3AATest, TestName);
    FRIEND_TEST(HeadShotDragonTest, TestName);
    FRIEND_TEST(HeadShotLizardTest, TestName);
    FRIEND_TEST(Double3AOneStrokeTest, TestName);
    FRIEND_TEST(Double3AMitigationTest, TestName);
    FRIEND_TEST(BlockAndAttack3ATest, TestName);
};
