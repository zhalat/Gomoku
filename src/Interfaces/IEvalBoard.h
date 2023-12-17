#pragma once
#include "Score.h"

class ThreatTracker;
class IBoard;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: EvalBoard
///
/// EvalBoard interface definition.
///
/// @par Full Description.
/// Provides api for checking
///////////////////////////////////////////////////////////////////////////////////////////
class IEvalBoard
{
   public:
    static constexpr uint32_t k_MILESTONE_SCORE {Score::THREAT_WINNER_SCORE / 2};
    static constexpr uint32_t k_BONUS_SCORE     {Score::THREAT_WINNER_SCORE / 100};

    virtual bool regularEval(const bool isMaxPlayer, IBoard::PositionXY & buildUpMove, int& stateScore) const = 0;

    virtual bool isWinner(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const = 0;
    virtual bool isLooser(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const = 0;
    virtual bool implicitWinner(const bool isMaxPlayer, IBoard::PositionXY & buildUpMove, int& stateScore) const = 0;
    virtual bool implicitLooser(const bool isMaxPlayer, IBoard::PositionXY & buildUpMove, int& stateScore) const = 0;

    virtual bool extendWinnerThreatMove(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const = 0;
    virtual bool extendWinnerActionMove(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const = 0;
    virtual void setBoards(const IBoard& board, const ThreatTracker& trackerHuman, const ThreatTracker& trackerCpu) = 0;
};