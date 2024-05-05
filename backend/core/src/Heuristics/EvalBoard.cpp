#include <algorithm>
#include <assert.h>
#include <math.h>
#include <set>
#include "Threats/ThreatFinder.h"
#include "Threats/ThreatsBloodRelation.h"
#include "Heuristics/EvalBoard.h"
#include "DataContainers/VectorUnique.h"
#include "ThreatTracker.h"
#include "Score.h"

// FORWARD REFERENCES
/// Get first common element.
static IBoard::PositionXY FindCommonMove(const std::vector<IBoard::PositionXY> & rGapsA,
                                           const std::vector<IBoard::PositionXY> & rGapsB);

/// Get all common elements.
static std::vector<IBoard::PositionXY> FindCommonMovements(const std::vector<IBoard::PositionXY> & rGapsA,
                                                             const std::vector<IBoard::PositionXY> & rGapsB);

/// Evaluate score value taking offset into account.
static int ScoreEval(const IEvalBoard * const evalBoard, const int offset);

static const IBoard::PositionXY k_XY_OUT_OF_BOARD = IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD);

EvalBoard::HeadShotActionState EvalBoard::m_headShotActionStateMaxConditionCheckerEnabled[] = {
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot4BCPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot3APossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot3AAPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShotDragonPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShotLizardPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isDouble3AOneStrokePossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isDouble3AMitigationPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isBlockAndAttack3APossible },
};

EvalBoard::HeadShotActionState EvalBoard::m_headShotActionStateMinConditionCheckerEnabled[] = {
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot4BCPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot3APossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot3AAPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShotDragonPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShotLizardPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isDouble3AOneStrokePossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isDouble3AMitigationPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isBlockAndAttack3APossible },
};

EvalBoard::HeadShotActionState EvalBoard::m_headShotActionStateMaxConditionCheckerDisabled[] = {
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot4BCPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot3APossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot3AAPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShotDragonPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShotLizardPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isDouble3AOneStrokePossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isDouble3AMitigationPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isBlockAndAttack3APossible },
};

EvalBoard::HeadShotActionState EvalBoard::m_headShotActionStateMinConditionCheckerDisabled[] = {
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot4BCPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot3APossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShot3AAPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShotDragonPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isHeadShotLizardPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isDouble3AOneStrokePossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isDouble3AMitigationPossible },
    { false, false, k_XY_OUT_OF_BOARD, &EvalBoard::isBlockAndAttack3APossible },
};

bool EvalBoard::isWinner(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const
{
    bool retVal = false;
    int mySign  = 0;

    if(not m_board)
        return false;

    const ThreatTracker* tracker{nullptr};

    if(isMaxPlayer)
    {
        tracker = m_trackerCpu;
        mySign        = 1;
    }
    else
    {
        tracker = m_trackerHuman;
        mySign        = -1;
    }

    const bool isWinner = tracker->getNumberOf(ThreatFinder::THREAT_WINNER) >0;

    if(isWinner)
    {
        buildUpMove = k_XY_OUT_OF_BOARD;
        stateScore  = mySign * Score::THREAT_WINNER_SCORE;
        retVal       = true;
    }

    return retVal;
}

void EvalBoard::setBoards(const IBoard& board, const ThreatTracker& trackerCpu, const ThreatTracker& trackerHuman)
{
    m_board = &board;
    m_trackerCpu = &trackerCpu;
    m_trackerHuman   = &trackerHuman;
}

bool EvalBoard::isLooser(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const
{
    bool retVal       = false;
    int adversarySign = 0;

    const ThreatTracker* tracker{nullptr};

    if(isMaxPlayer)
    {
        tracker = m_trackerHuman;
        adversarySign   = -1;
    }
    else
    {
        tracker = m_trackerCpu;
        adversarySign   = 1;
    }

    const bool isWinner = tracker->getNumberOf(ThreatFinder::THREAT_WINNER) > 0;

    if(isWinner)
    {
        buildUpMove = k_XY_OUT_OF_BOARD;
        stateScore  = adversarySign * Score::THREAT_WINNER_SCORE;
        retVal       = true;
    }

    return retVal;
}

/// Predict the winner.
bool EvalBoard::implicitWinner(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const
{
    bool retVal = false;
    int mySign  = 0;
    IBoard::PositionXY temp;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = m_trackerCpu;
        adversaryState = m_trackerHuman;
        mySign               = 1;
    }
    else
    {
        myState        = m_trackerHuman;
        adversaryState = m_trackerCpu;
        mySign               = -1;
    }

    const bool isMyWinner = myState->getNumberOf(ThreatFinder::THREAT_WINNER) > 0;
    const bool isMy4A     = myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A);
    const bool isMy2x4BC  = ((myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
                              myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
                              myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C)) > 1);
    const bool isMy4ABC   = myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) ||
                            myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) ||
                            myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) ||
                            myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C);

    const bool isMy4BC = myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) ||
                         myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) ||
                         myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C);
    const bool isMy3A   = myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A);
    const bool isMy2x3A = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 1);

    const bool isAdversary3A   = adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_A);
    const bool isAdversary4ABC = adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) ||
                                 adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) ||
                                 adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) ||
                                 adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C);

    if(isMyWinner)
    {
        stateScore = mySign * Score::THREAT_WINNER_SCORE;
        retVal      = true;
    }
    else if(!isAdversary4ABC && isMy4A)
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isAdversary4ABC && isMy2x4BC)
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isAdversary4ABC && isMy4BC && isMy3A)
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;

        // Be careful when adversary has 3A and blocking your 4ABC extends its 3A->4A.
        if(isAdversary3A)
        {
            std::vector<IBoard::PositionXY> gaps3A;
            std::vector<IBoard::PositionXY> gaps4ABC;
            adversaryState->getGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);
            myState->getGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_AA);
            myState->getGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_B);
            myState->getGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_C);

            // Common gap means adversary's block->attack->win.
            retVal = (FindCommonMove(gaps3A, gaps4ABC) == k_XY_OUT_OF_BOARD) ? true : false;
        }
    }
    else if(!isAdversary4ABC && !isAdversary3A && isMy2x3A && !headShotRun(HEAD_SHOOT_4BC, !isMaxPlayer, temp) &&
            !headShotRun(HEAD_SHOOT_3A, !isMaxPlayer, temp) &&
            !headShotRun(HEAD_SHOOT_3AA, !isMaxPlayer, temp) &&
            !headShotRun(MITIGATION_3A, isMaxPlayer, temp))
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isAdversary4ABC && !isAdversary3A && isMy3A && !headShotRun(HEAD_SHOOT_4BC, !isMaxPlayer, temp) &&
            !headShotRun(HEAD_SHOOT_3A, !isMaxPlayer, temp) &&
            !headShotRun(HEAD_SHOOT_3AA, !isMaxPlayer, temp) &&
            ((headShotRun(HEAD_SHOOT_DOUBLE_3A_ONE_STROKE, isMaxPlayer, temp) &&
              !headShotRun(MITIGATION_3A, isMaxPlayer, temp) &&
              !headShotRun(MITIGATION_DOUBLE_3A, isMaxPlayer, temp)) ||
             headShotRun(HEAD_SHOOT_LIZARD, isMaxPlayer, temp)))
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isAdversary4ABC && isMy4ABC &&
            (headShotRun(HEAD_SHOOT_4BC, isMaxPlayer, temp) ||
             headShotRun(HEAD_SHOOT_3A, isMaxPlayer, temp) ||
             headShotRun(HEAD_SHOOT_3AA, isMaxPlayer, temp) ||
             headShotRun(HEAD_SHOOT_DRAGON, isMaxPlayer, temp)))
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;

        // Be careful when adversary has 3A and blocking your 4ABC extends its 3A->4A.
        if(isAdversary3A)
        {
            std::vector<IBoard::PositionXY> gaps3A;
            std::vector<IBoard::PositionXY> gaps4ABC;
            adversaryState->getGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);
            myState->getGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_AA);
            myState->getGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_B);
            myState->getGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_C);

            // Common gap means adversary's block->attack->win.
            retVal = (FindCommonMove(gaps3A, gaps4ABC) == k_XY_OUT_OF_BOARD) ? true : false;
        }
    }
    else if(!isAdversary4ABC && !isAdversary3A && isMy3A && !headShotRun(HEAD_SHOOT_4BC, !isMaxPlayer, temp) &&
            !headShotRun(HEAD_SHOOT_3A, !isMaxPlayer, temp) &&
            !headShotRun(HEAD_SHOOT_3AA, !isMaxPlayer, temp) &&
            !headShotRun(MITIGATION_3A, isMaxPlayer, temp) &&
            !headShotRun(HEAD_SHOOT_DRAGON, !isMaxPlayer, temp) &&
            (headShotRun(HEAD_SHOOT_4BC, isMaxPlayer, temp) ||
             headShotRun(HEAD_SHOOT_3A, isMaxPlayer, temp) ||
             headShotRun(HEAD_SHOOT_3AA, isMaxPlayer, temp) ||
             headShotRun(HEAD_SHOOT_DRAGON, isMaxPlayer, temp) ||
             headShotRun(HEAD_SHOOT_LIZARD, isMaxPlayer, temp)))
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else
    {
        stateScore = 0;
        retVal      = false;
    }

    return retVal;
}

bool EvalBoard::implicitLooser(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, int& stateScore) const
{
    bool retVal       = false;
    int adversarySign = 0;
    IBoard::PositionXY temp;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = m_trackerCpu;
        adversaryState = m_trackerHuman;
        adversarySign        = -1;
    }
    else
    {
        myState        = m_trackerHuman;
        adversaryState = m_trackerCpu;
        adversarySign        = 1;
    }

    const bool isAdversaryWinner = adversaryState->getNumberOf(ThreatFinder::THREAT_WINNER) > 0;
    const bool isAdversary4ABC   = adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) ||
                                   adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) ||
                                   adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) ||
                                   adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C);
    const bool isAdversary3A = adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_A);
    const bool isMy4BC       = adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) ||
                               adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) ||
                               adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C);
    const bool isMy3A = adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0;

    if(isAdversaryWinner)
    {
        stateScore = adversarySign * Score::THREAT_WINNER_SCORE;
        retVal      = true;
    }
    else if(isAdversary4ABC)
    {
        stateScore = adversarySign * Score::THREAT_WINNER_SCORE;
        retVal      = true;
    }
    else if(isAdversary3A && !isMy4BC)
    {
        stateScore = adversarySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(headShotRun(HEAD_SHOOT_4BC, !isMaxPlayer, temp))
    {
        stateScore = adversarySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(headShotRun(HEAD_SHOOT_3A, !isMaxPlayer, temp) ||
            headShotRun(HEAD_SHOOT_3AA, !isMaxPlayer, temp))
    {
        stateScore = adversarySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(headShotRun(HEAD_SHOOT_DOUBLE_3A_ONE_STROKE, !isMaxPlayer, temp) &&  // shall be also !isMy3A && ' the same as lizard'
            !headShotRun(MITIGATION_DOUBLE_3A, !isMaxPlayer, temp))
    {
        stateScore = adversarySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(headShotRun(HEAD_SHOOT_DRAGON, !isMaxPlayer, temp))
    {
        stateScore = adversarySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isMy3A && headShotRun(HEAD_SHOOT_LIZARD, !isMaxPlayer, temp))
    {
        stateScore = adversarySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else
    {
        stateScore = 0;
        retVal      = false;
    }

    return retVal;
}

bool EvalBoard::regularEval(const bool isMaxPlayer, IBoard::PositionXY &buildUpMove, int& stateScore) const
{
    stateScore = (static_cast<int>(m_trackerCpu->getScore() + getBonus(true, buildUpMove)) -
                   static_cast<int>(m_trackerHuman->getScore() + getBonus(false, buildUpMove)));

    return true;
}

bool EvalBoard::extendWinnerThreatMove(const bool isMaxPlayer, IBoard::PositionXY & buildUpMove,
                                             int & stateScore) const
{
    bool retVal       = false;
    int mySign        = 0;
    int adversarySign = 0;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = m_trackerCpu;
        adversaryState = m_trackerHuman;
        mySign               = 1;
        adversarySign        = -1;
    }
    else
    {
        myState        = m_trackerHuman;
        adversaryState = m_trackerCpu;
        mySign               = -1;
        adversarySign        = 1;
    }

    const bool isMy4ABC = myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) ||
                          myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) ||
                          myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C);
    const bool isMy4AA         = myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA);
    const bool isMy3A          = myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A);
    const bool isAdversary4ABC = adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) ||
                                 adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) ||
                                 adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) ||
                                 adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C);

    if(isMy4ABC)
    {
        // Find gaps for 4ABC.
        std::vector<IBoard::PositionXY> gaps4ABC;
        myState->getGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_A);
        myState->getGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_B);
        myState->getGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_C);

        // .xxxx. /o.xxxxo / oxx.xx*
        buildUpMove = gaps4ABC[0];
        stateScore  = mySign * Score::THREAT_WINNER_SCORE;
        retVal       = true;
    }
    else if(isMy4AA)
    {
        // Find gaps for 4ABC.
        std::vector<IBoard::PositionXY> gaps4ABC;
        myState->getGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_AA);

        // .xxx.x.
        buildUpMove =  gaps4ABC[1];
        stateScore  = mySign * Score::THREAT_WINNER_SCORE;
        retVal       = true;
    }
    else if(isMy3A && !isAdversary4ABC)
    {
        // Find gaps for 3A.
        std::vector<IBoard::PositionXY> gaps3A;
        myState->getGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);

        shared_ptr<IBoard> boardCopy = nullptr;
        shared_ptr<ThreatTracker> myStateCopy = nullptr;
        shared_ptr<ThreatTracker> adversaryStateCopy = nullptr;
        createCopyState(*m_board, *myState, *adversaryState, boardCopy, myStateCopy, adversaryStateCopy);
        myStateCopy->mementoEnable();

        for(auto iter = gaps3A.begin(); iter != gaps3A.end(); ++iter)
        {
            boardCopy->putMove(*iter, myState->getPlayer());
            myStateCopy->updateScore(*iter, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
            const bool isMy4A = myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_A);

            if(isMy4A)
            {
                buildUpMove = *iter;
                stateScore  = mySign * Score::THREAT_WINNER_SCORE;
                retVal       = true;
                break;
            }

            //revert move:
            boardCopy->removeMove(*iter);
            myStateCopy->mementoRevert(1);
        }

        backFromCopyState(*m_board);
    }

    return retVal;
}

bool EvalBoard::extendWinnerActionMove(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove,
                                             int& stateScore) const
{
    int retVal                              = false;
    int mySign                              = 0;
    int adversarySign                       = 0;
    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};
    IBoard::PositionXY buildUpTmp;

    if(isMaxPlayer)
    {
        myState        = m_trackerCpu;
        adversaryState = m_trackerHuman;
        mySign         = 1;
        adversarySign  = -1;
    }
    else
    {
        myState        = m_trackerHuman;
        adversaryState = m_trackerCpu;
        mySign         = -1;
        adversarySign  = 1;
    }

    const bool isAdversary4 = ( adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 or
                                adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 or
                                adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 or
                                adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0);

    if(isAdversary4)
        return false;

    const bool isAdversary3A = adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0;

    if(isHeadShot4BCPossible(isMaxPlayer,buildUpMove, *m_board, *m_trackerCpu, *m_trackerHuman))
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(isHeadShot3APossible(isMaxPlayer, buildUpMove, *m_board, *m_trackerCpu, *m_trackerHuman))
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(isHeadShot3AAPossible(isMaxPlayer, buildUpMove, *m_board, *m_trackerCpu, *m_trackerHuman))
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(isHeadShotDragonPossible(isMaxPlayer, buildUpMove, *m_board, *m_trackerCpu, *m_trackerHuman))
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isAdversary3A && isHeadShotLizardPossible(isMaxPlayer, buildUpMove, *m_board, *m_trackerCpu, *m_trackerHuman))
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else if( isDouble3AOneStrokePossible(isMaxPlayer, buildUpMove, *m_board, *m_trackerCpu, *m_trackerHuman) &&
             !isAdversary3A &&
             !isHeadShot3APossible(!isMaxPlayer, buildUpTmp, *m_board, *m_trackerCpu, *m_trackerHuman) &&
             !isHeadShot3AAPossible(!isMaxPlayer, buildUpTmp, *m_board, *m_trackerCpu, *m_trackerHuman) &&
             !isHeadShot4BCPossible(!isMaxPlayer, buildUpTmp, *m_board, *m_trackerCpu, *m_trackerHuman) &&
             !isHeadShotDragonPossible(!isMaxPlayer, buildUpTmp, *m_board, *m_trackerCpu, *m_trackerHuman))
    {
        stateScore = mySign * ScoreEval(this, k_MILESTONE_SCORE);
        retVal      = true;
    }
    else
    {}

    return retVal;
}

void EvalBoard::update() const
{
    // Boad state has changed. Clear state action.
    for(uint32_t i = 0; i < EvalBoard::k_HEAD_SHOT_ACTION_NUMBER; ++i)
    {
        m_headShotActionStateMinConditionCheckerEnabled[i].m_isUpToDate  = false;
        m_headShotActionStateMaxConditionCheckerEnabled[i].m_isUpToDate  = false;
        m_headShotActionStateMinConditionCheckerDisabled[i].m_isUpToDate = false;
        m_headShotActionStateMaxConditionCheckerDisabled[i].m_isUpToDate = false;
    }
}

bool EvalBoard::headShotRun(const HeadShotAction headShotAction, const bool isMaxPlayer,
                            IBoard::PositionXY & rShotMove) const
{
    bool retVal                                                 = false;
    const uint32_t index                                        = static_cast<uint32_t>(headShotAction);
    EvalBoard::HeadShotActionState * pHeadShotActionState = NULL;

    if(isMaxPlayer)
    {
        pHeadShotActionState = &m_headShotActionStateMaxConditionCheckerEnabled[index];
    }
    else if(isMaxPlayer)
    {
        pHeadShotActionState = &m_headShotActionStateMaxConditionCheckerDisabled[index];
    }
    else if(!isMaxPlayer)
    {
        pHeadShotActionState = &m_headShotActionStateMinConditionCheckerEnabled[index];
    }
    else if(!isMaxPlayer)
    {
        pHeadShotActionState = &m_headShotActionStateMinConditionCheckerDisabled[index];
    }
    else
    {
        assert(false);
    }

    if(pHeadShotActionState->m_isUpToDate)
    {
        // Don't run head shot function to save time. Get the previous result.
        retVal    = pHeadShotActionState->m_isPossible;
        rShotMove = pHeadShotActionState->m_stateMove;
    }
    else
    {
        // You have to run head shot function due to IBoard state changing.
        FuncPtr pFuncPtr = pHeadShotActionState->m_pFuncPtr;
        retVal           = (this->*pFuncPtr)(isMaxPlayer, rShotMove, *m_board, *m_trackerCpu, *m_trackerHuman);

        // Save result & mark as up to date.
        pHeadShotActionState->m_isPossible = retVal;
        pHeadShotActionState->m_stateMove  = rShotMove;
        pHeadShotActionState->m_isUpToDate = true;
    }

    return retVal;
}

bool EvalBoard::isHeadShot4BCPossible(const bool isMaxPlayer,
                                      IBoard::PositionXY& buildUpMove,
                                      const IBoard& board,
                                      const ThreatTracker& cpu,
                                      const ThreatTracker& human) const
{
    bool retVal = false;

    const ThreatTracker* myState        {nullptr};
    const ThreatTracker* adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = &cpu;
        adversaryState = &human;
    }
    else
    {
        myState        = &human;;
        adversaryState = &cpu;
    }

    // Head shoot is possible when you have: at least 2x 3BC.
    const bool isHeadShootPossibleStage1 =
        (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_AA) +
         myState->getNumberOf(ThreatFinder::THREAT_3_CASE_B) +
         myState->getNumberOf(ThreatFinder::THREAT_3_CASE_C)) > 1;

    if(isHeadShootPossibleStage1)
    {
        // Check if there are gaps common for 3BC threats.
        std::vector<IBoard::PositionXY> gaps3BC;
        myState->getGapsNonUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_AA);
        myState->getGapsNonUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_B);
        myState->getGapsNonUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_C);

        VectorUnique<uint32_t , GomokuBoard::k_MAX_GOMOKU_BOARD_SQARE_SIZE> gate;
        for(auto citer = gaps3BC.begin(); citer < gaps3BC.end(); ++citer)
        {
            bool isUnique = !gate.isPresent(citer->convert2Linear(board.getSize()));
            if(isUnique)
            {
                gate.insert(citer->convert2Linear(board.getSize()));
            }
            else
            {
                buildUpMove =  *citer;
                retVal       = true;
            }
        }
    }

    return retVal;
}

bool EvalBoard::isHeadShot3APossible(const bool isMaxPlayer,
                                     IBoard::PositionXY& buildUpMove,
                                     const IBoard& board,
                                     const ThreatTracker& cpu,
                                     const ThreatTracker& human) const
{
    bool retVal = false;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = &cpu;
        adversaryState = &human;
    }
    else
    {
        myState        = &human;;
        adversaryState = &cpu;
    }

    // Operate on copy instance.
    shared_ptr<IBoard> boardCopy = nullptr;
    shared_ptr<ThreatTracker> myStateCopy = nullptr;
    shared_ptr<ThreatTracker> adversaryStateCopy = nullptr;
    createCopyState(board, *myState, *adversaryState, boardCopy, myStateCopy, adversaryStateCopy);

    const uint32_t initMoveN = boardCopy->getMoveNumber();
    myStateCopy->mementoEnable();
    adversaryStateCopy->mementoEnable();

    // Head shoot is possible when you have: 2A && 3BC && opponent doesn't have 4ABC.
    const bool isMy2A   = myState->getNumberOf(ThreatFinder::THREAT_2_CASE_A) > 0;
    const bool isMy3BC  = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_AA) > 0 ||
                          myState->getNumberOf(ThreatFinder::THREAT_3_CASE_B) > 0 ||
                          myState->getNumberOf(ThreatFinder::THREAT_3_CASE_C) > 0);
    const bool isMy3A   = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC = (myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC = (adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                                  adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                                  adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                                  adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary3A = adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0;

    const uint32_t my4BCNumberOfThreatsInit =
        myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
        myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
        myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C);

    const bool isHeadShootPossibleStage1 = (isMy2A && isMy3BC && !isAdversary4ABC);
    if(isHeadShootPossibleStage1)
    {
        // Find common move for 2A && 3BC threats.
        std::vector<IBoard::PositionXY> gaps2A;
        std::vector<IBoard::PositionXY> gaps3BC;
        myStateCopy->getGapsUnique(gaps2A, ThreatFinder::THREAT_2_CASE_A);
        myStateCopy->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_AA);
        myStateCopy->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_B);
        myStateCopy->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_C);

        const std::vector<IBoard::PositionXY> commonMovements = FindCommonMovements(gaps3BC, gaps2A);
        for(auto iter = commonMovements.begin(); iter != commonMovements.end(); ++iter)
        {
            //revert to initial state
            const auto n = boardCopy->getMoveNumber() - initMoveN;
            boardCopy->removeNLastMove(n);
            myStateCopy->mementoRevert(n);
            adversaryStateCopy->mementoRevert(n);

            const IBoard::PositionXY newMove =*iter;

            // A new move must create my new 3A and 4BC.
            boardCopy->putMove(newMove, myStateCopy->getPlayer());
            myStateCopy->updateScore(newMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
            adversaryStateCopy->updateScore(newMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

            // Check out if my 3A and 4BC has been created.
            const uint32_t my4BCNumberOfThreatsStage1 =
                (myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
                 myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
                 myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_C));

            const bool isHeadShootPossibleStage2 =
                (my4BCNumberOfThreatsStage1 > my4BCNumberOfThreatsInit) &&
                (myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0);

            if(isHeadShootPossibleStage2)
            {
                if(isAdversary3A)
                {
                    // Find common move for my 4BC and adversary's 3A threat.
                    std::vector<IBoard::PositionXY> gaps4BC;
                    std::vector<IBoard::PositionXY> gaps3A;
                    myStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_AA);
                    myStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_B);
                    myStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_C);
                    adversaryStateCopy->getGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);

                    const IBoard::PositionXY commonMoveStage2 = FindCommonMove(gaps4BC, gaps3A);

                    if(commonMoveStage2 != k_XY_OUT_OF_BOARD)
                    {
                        boardCopy->putMove(commonMoveStage2, adversaryState->getPlayer());
                        myStateCopy->updateScore(commonMoveStage2, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                        adversaryStateCopy->updateScore(commonMoveStage2, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                        // Check if the move shut down my 4BC.
                        const uint32_t my4BCNumberOfThreatsStage2 =
                            (myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
                             myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
                             myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_C));

                        // Only adverary's 4A threat may shut down my attack. 4AA is not included.
                        // My 3A threat must exist.
                        const uint32_t adversary4ANumberOfThreatsStage2 =
                                adversaryStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_A);

                        const bool isMyAttackFail =
                            (((my4BCNumberOfThreatsStage2 < my4BCNumberOfThreatsStage1) &&
                              (adversary4ANumberOfThreatsStage2 > 0)) ||
                             (myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_A)) == 0);

                        if(isMyAttackFail)
                        {
                            retVal = false;
                        }
                        else
                        {
                            buildUpMove = newMove;
                            retVal       = true;
                        }
                    }
                    else
                    {
                        buildUpMove = newMove;
                        retVal       = true;
                    }
                }
                else
                {
                    buildUpMove = newMove;
                    retVal       = true;
                }
            }
            else
            {
                // It means that I am not able to crate either 4ABC or 3A. No death threat.
                retVal = false;
            }

            // Stop searching if found.
            if(retVal)
            {
                // Ensure that adversary is not able to shut down both 4BC and 3A at one stroke.
                // Like here: 'oxxx.x.xx' .Putting 'o' at first gap would shut down all the action.
                // This case might probably occurs while 4AB & 3A are on the same trend.

                const uint32_t my3ACNumberOfThreatsStage3 =
                        myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_A);
                const uint32_t my4BCNumberOfThreatsStage3 =
                    (myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
                            myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
                            myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_C));
                assert(my3ACNumberOfThreatsStage3 > 0);

                // Find the 4AB threat that has just been created at stage 1.
                std::vector<IBoard::PositionXY> gaps3A;
                std::vector<IBoard::PositionXY> gaps4BC;
                myStateCopy->getGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);
                myStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_AA);
                myStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_B);
                myStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_C);

                const std::vector<IBoard::PositionXY> commonMovements = FindCommonMovements(gaps4BC, gaps3A);

                for(auto iter = commonMovements.begin(); iter != commonMovements.end(); ++iter)
                {
                    const IBoard::PositionXY shutDownMove=*iter;
                    boardCopy->putMove(shutDownMove, adversaryState->getPlayer());
                    myStateCopy->updateScore(shutDownMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                    adversaryStateCopy->updateScore(shutDownMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                    // Check if one adversary move could shut down my action.
                    const uint32_t my3ACNumberOfThreatsStage4 =
                            myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_A);
                    const uint32_t my4BCNumberOfThreatsStage4 =
                        (myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
                                myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
                                myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_C));
                    const bool isShutDown = (my3ACNumberOfThreatsStage4 < my3ACNumberOfThreatsStage3) &&
                                            (my4BCNumberOfThreatsStage4 < my4BCNumberOfThreatsStage3);

                    if(isShutDown)
                    {
                        retVal = false;
                        break;
                    }
                }

                break;
            }
        }
    }
    backFromCopyState(board);
    return retVal;
}

bool EvalBoard::isHeadShot3AAPossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const
{
    bool retVal = false;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = &cpu;
        adversaryState = &human;
    }
    else
    {
        myState        = &human;;
        adversaryState = &cpu;
    }

    // Operate on copy instance.
    shared_ptr<IBoard> boardCopy = nullptr;
    shared_ptr<ThreatTracker> myStateCopy = nullptr;
    shared_ptr<ThreatTracker> adversaryStateCopy = nullptr;
    createCopyState(board, *myState, *adversaryState, boardCopy, myStateCopy, adversaryStateCopy);
    const uint32_t initMoveN = boardCopy->getMoveNumber();
    myStateCopy->mementoEnable();
    adversaryStateCopy->mementoEnable();

    // Head shoot is possible when you have: 2A && 3BC && opponent doesn't have 4ABC.
    const bool isMy2A   = myState->getNumberOf(ThreatFinder::THREAT_2_CASE_A) > 0;
    const bool isMy3BC  = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_AA) > 0 ||
                          myState->getNumberOf(ThreatFinder::THREAT_3_CASE_B) > 0 ||
                          myState->getNumberOf(ThreatFinder::THREAT_3_CASE_C) > 0);
    const bool isMy3A   = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC = (myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary3A = adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0;

    const uint32_t my4BCNumberOfThreatsInit =
        myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
        myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
        myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C);

    const bool isHeadShootPossibleStage1 = (isMy2A && isMy3BC && !isAdversary4ABC);

    if(isHeadShootPossibleStage1)
    {
        // Find common move for 2A && 3BC threats.
        std::vector<IBoard::PositionXY> gaps2A;
        std::vector<IBoard::PositionXY> gaps3BC;
        myState->getGapsUnique(gaps2A, ThreatFinder::THREAT_2_CASE_A);
        myState->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_AA);
        myState->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_B);
        myState->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_C);

        const std::vector<IBoard::PositionXY> commonMovements = FindCommonMovements(gaps3BC, gaps2A);

        for(auto iter = commonMovements.begin(); iter != commonMovements.end(); ++iter)
        {
            //revert to initial state
            const auto n = boardCopy->getMoveNumber() - initMoveN;
            boardCopy->removeNLastMove(n);
            myStateCopy->mementoRevert(n);
            adversaryStateCopy->mementoRevert(n);

            const IBoard::PositionXY newMove =*iter;

            // Check if its possible to crate 3AA by usage 3BC and 2A.
            boardCopy->putMove(newMove, myStateCopy->getPlayer());
            myStateCopy->updateScore(newMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
            adversaryStateCopy->updateScore(newMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

            const uint32_t my4BCNumberOfThreatsStage1 =
                (myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
                 myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
                 myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_C));

#warning "checkWinnerMoveCondition. Might not work when my 3A threat was already present on IBoard."
            const bool isHeadShootPossibleStage2 =
                (my4BCNumberOfThreatsStage1 > my4BCNumberOfThreatsInit) &&
                (myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_AA) > 0);

            if(isHeadShootPossibleStage2)
            {
                bool isAdversaryShutMyAttackStage2 = false;

                if(isAdversary3A)
                {
                    // Find common move for my 4BC and adversary's 3A threat.
                    std::vector<IBoard::PositionXY> gaps4BC;
                    std::vector<IBoard::PositionXY> gaps3A;
                    myStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_AA);
                    myStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_B);
                    myStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_C);
                    adversaryStateCopy->getGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);

                    const IBoard::PositionXY commonMoveStage2 = FindCommonMove(gaps4BC, gaps3A);

                    if(commonMoveStage2 != k_XY_OUT_OF_BOARD)
                    {
                        boardCopy->putMove(commonMoveStage2, adversaryState->getPlayer());
                        myStateCopy->updateScore(commonMoveStage2, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                        adversaryStateCopy->updateScore(commonMoveStage2, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                        // Check if the move shut down my 4BC.
                        const uint32_t my4BCNumberOfThreatsStage2 =
                            (myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
                             myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
                             myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_C));

                        // Only adversary's 4A threat may shut down my attack. 4AA is not included.
                        // My 3AA threat must exist.
                        const uint32_t adversary4ANumberOfThreatsStage2 =
                                adversaryStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_A);

                        isAdversaryShutMyAttackStage2 =
                            (((my4BCNumberOfThreatsStage2 < my4BCNumberOfThreatsStage1) &&
                              (adversary4ANumberOfThreatsStage2 > 0)) ||
                             (myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_AA)) == 0);
                    }
                }

                if(!isAdversaryShutMyAttackStage2)
                {
                    // Here we know that we have 3AA & 4BC and adversary is not able to shut down my 4BC by its 3A (if
                    // having it).

                    // Check if its possible to crate head shoot 3A using 3AA. But before that we must provide current
                    // copy board and copy tracker. Use switch2States() to inject data but remember to switch them back!

                    IBoard::PositionXY buildUpMoveTmp;
                    retVal = isHeadShot3APossible(true, buildUpMoveTmp, *boardCopy, *myStateCopy, *adversaryStateCopy);
                    if(retVal)
                        buildUpMove = newMove; //the one which lead us here
                }
            }
            else
            {
                // It means that I am not able to crate either 4ABC or 3A. No death threat.
                continue;
            }

            if(retVal)
            {
                break;
            }
        }
    }

    backFromCopyState(board);
    return retVal;
}

bool EvalBoard::isHeadShotDragonPossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const
{
    bool retVal = false;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = &cpu;
        adversaryState = &human;
    }
    else
    {
        myState        = &human;;
        adversaryState = &cpu;
    }

    // Operate on copy instance.
    shared_ptr<IBoard> boardCopy = nullptr;
    shared_ptr<ThreatTracker> myStateCopy = nullptr;
    shared_ptr<ThreatTracker> adversaryStateCopy = nullptr;
    createCopyState(board, *myState, *adversaryState, boardCopy, myStateCopy, adversaryStateCopy);
    const uint32_t initMoveN = boardCopy->getMoveNumber();
    myStateCopy->mementoEnable();
    adversaryStateCopy->mementoEnable();

    // Dragon shoot is possible when you have: 2x3BC opponent doesn't have 4ABC.
    const bool isMy2x3BC = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_AA) +
                            myState->getNumberOf(ThreatFinder::THREAT_3_CASE_B) +
                            myState->getNumberOf(ThreatFinder::THREAT_3_CASE_C)) > 1;
    const bool isMy3A    = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC  = (myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);

    const bool isHeadShootPossibleStage1 = (isMy2x3BC && !isAdversary4ABC);

    if(isHeadShootPossibleStage1)
    {
        // Find gap movies for 3BC threats.
        std::vector<IBoard::PositionXY> gaps3BC;
        myState->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_B);
        myState->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_C);
        myState->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_AA);

        for(auto iter = gaps3BC.begin(); iter != gaps3BC.end(); ++iter)
        {
            //revert to initial state
            const auto n = boardCopy->getMoveNumber() - initMoveN;
            boardCopy->removeNLastMove(n);
            myStateCopy->mementoRevert(n);
            adversaryStateCopy->mementoRevert(n);

            const IBoard::PositionXY newMove =*iter;

            // Put new move.
            boardCopy->putMove(newMove, myStateCopy->getPlayer());
            myStateCopy->updateScore(newMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
            adversaryStateCopy->updateScore(newMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

            // Head shot Dragon precedes 3A Head shot.
            IBoard::PositionXY buildUpMoveTmp;
            const bool isHeadShot3A = isHeadShot3APossible(true, buildUpMoveTmp, *boardCopy, *myStateCopy, *adversaryStateCopy);

            // Now we know that IsHeadShot3A is possible but we don't known if it was caused by newMove or existing one.
            // See IsHeadShotDragonPossibleTest7().
            bool isOK = false;
            if(isHeadShot3A)
            {
                // a.
                // Put HeadShot3A move and update threats.
                boardCopy->putMove(buildUpMoveTmp, myStateCopy->getPlayer());
                myStateCopy->updateScore(buildUpMoveTmp, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                adversaryStateCopy->updateScore(buildUpMoveTmp, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);


                // b.
                // Such newly created 3A threat must contain also 'newMove'.
                const ThreatFinder::ThreatLocation threatLocation =
                        myStateCopy->getThreatList(ThreatFinder::THREAT_3_CASE_A).back();

                for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS; ++i)
                {
                    const IBoard::PositionXY el = threatLocation.m_threatDetails.m_myPawns[i];
                    if(el == newMove)
                    {
                        buildUpMove=newMove;
                        isOK = true;
                        break;
                    }
                }
            }

            if(isOK)
            {
                retVal = true;
                break;
            }
            else
            {
                continue;
            }
        }
    }

    backFromCopyState(board);
    return retVal;
}

bool EvalBoard::isHeadShotLizardPossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const
{
    bool retVal = false;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = &cpu;
        adversaryState = &human;
    }
    else
    {
        myState        = &human;;
        adversaryState = &cpu;
    }

    // Operate on this IBoard instance.
    // Operate on copy instance.
    shared_ptr<IBoard> boardCopy = nullptr;
    shared_ptr<ThreatTracker> myStateCopy = nullptr;
    shared_ptr<ThreatTracker> adversaryStateCopy = nullptr;
    createCopyState(board, *myState, *adversaryState, boardCopy, myStateCopy, adversaryStateCopy);
    const uint32_t initMoveN = boardCopy->getMoveNumber();
    myStateCopy->mementoEnable();
    adversaryStateCopy->mementoEnable();

    // Lizard shoot is possible when you have: 2x3BC && 2A opponent doesn't have 4ABC.
    const uint32_t myNumberOf3BC = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_AA) +
                                    myState->getNumberOf(ThreatFinder::THREAT_3_CASE_B) +
                                    myState->getNumberOf(ThreatFinder::THREAT_3_CASE_C));
    const bool isMy2x3BC         = (myNumberOf3BC > 1);
    const bool isMy2A            = (myState->getNumberOf(ThreatFinder::THREAT_2_CASE_A) > 0);
    const bool isMy3A            = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC          = (myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);

    const bool isHeadShootPossibleStage1 = (isMy2x3BC && isMy2A && !isAdversary4ABC);

    if(isHeadShootPossibleStage1)
    {
        // a. Get gaps for each 3BC threat.
        static constexpr uint32_t maxGapSize                    = 2;
        IBoard::PositionXY xyGaps[myNumberOf3BC][maxGapSize] = {  };
        ThreatFinder::KindOfThreats kindOfThreats[] = { ThreatFinder::THREAT_3_CASE_AA, ThreatFinder::THREAT_3_CASE_B,
                                                        ThreatFinder::THREAT_3_CASE_C };

        uint32_t index = 0;
        for(uint32_t i = 0; i < NUMELEM(kindOfThreats); ++i)
        {
            // Get 3AABC threat list.
            const std::list<ThreatFinder::ThreatLocation> & theratList = myState->getThreatList(kindOfThreats[i]);

            for(auto iter = theratList.begin(); iter != theratList.end(); ++iter)
            {
                xyGaps[index][0]   = iter->m_threatDetails.m_gaps[0];
                xyGaps[index++][1] = iter->m_threatDetails.m_gaps[1];
            }
        }

        // b. Extend each 3BC threat and check if 'double 3A possible'.
        assert(myNumberOf3BC > 1);
        for(uint32_t i = 0; i < myNumberOf3BC - 1; ++i)
        {
            for(uint32_t j = 0; j < maxGapSize; ++j)
            {
                const IBoard::PositionXY newMove1 = xyGaps[i][j];

                for(uint32_t k = 0; k < maxGapSize; ++k)
                {
                    const IBoard::PositionXY newMove2 = xyGaps[i + 1][k];

                    //revert to initial state
                    const auto n = boardCopy->getMoveNumber() - initMoveN;
                    boardCopy->removeNLastMove(n);
                    myStateCopy->mementoRevert(n);
                    adversaryStateCopy->mementoRevert(n);


                    // Put new movies.
                    if(boardCopy->putMove(newMove1, myState->getPlayer()))
                    {
                        myStateCopy->updateScore(newMove1, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                        adversaryStateCopy->updateScore(newMove1, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                    }

                    if(boardCopy->putMove(newMove2, myState->getPlayer()))
                    {
                        myStateCopy->updateScore(newMove2, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                        adversaryStateCopy->updateScore(newMove2, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                    }

                    // Head shot Dragon precedes 3A Head shot.
                    const bool isDouble3APossible = isDouble3AOneStrokePossible(true, buildUpMove, *boardCopy, *myStateCopy, *adversaryStateCopy);

                    // Now we know that IsHeadShot3A is possible but we don't known if it was caused by newMove or
                    // existing one. See IsHeadShotDragonPossibleTest7().
                    bool isOK1 = false;
                    if(isDouble3APossible)
                    {
                        // a.
                        // Put Double3AOneStroke move and update threats.
                        boardCopy->putMove(buildUpMove, myState->getPlayer());
                        myStateCopy->updateScore(buildUpMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                        adversaryStateCopy->updateScore(buildUpMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                        // b.
                        // Such newly created 3A threat must contain also 'newMove'.
                        const ThreatFinder::ThreatLocation threatLocation =myStateCopy->getThreatList(ThreatFinder::THREAT_3_CASE_A).back();

                        for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS; ++i)
                        {
                            const IBoard::PositionXY el = threatLocation.m_threatDetails.m_myPawns[i];
                            if(el == newMove1 || el == newMove2)
                            {
                                isOK1 = true;
                                break;
                            }
                        }
                    }

                    bool isOK2 = false;
                    if(isOK1)
                    {
                        // You must be careful to avoid adversary's your 4BC mitigation by
                        // extending his 2A->3A.
                        std::vector<IBoard::PositionXY> my4BCgaps;
                        myStateCopy->getGapsUnique(my4BCgaps, ThreatFinder::THREAT_4_CASE_B);
                        myStateCopy->getGapsUnique(my4BCgaps, ThreatFinder::THREAT_4_CASE_C);
                        myStateCopy->getGapsUnique(my4BCgaps, ThreatFinder::THREAT_4_CASE_AA);

                        std::vector<IBoard::PositionXY> adversart2Agaps;
                        adversaryStateCopy->getGapsUnique(adversart2Agaps, ThreatFinder::THREAT_2_CASE_A);
                        const IBoard::PositionXY commonMove = FindCommonMove(my4BCgaps, adversart2Agaps);

                        if(k_XY_OUT_OF_BOARD == commonMove)
                        {
                            isOK2 = true;
                        }
                    }

                    if(isOK2)
                    {
                        buildUpMove = newMove1;
                        retVal       = true;
                        goto exit;
                    }
                }
            }
        }
    }

exit:

    backFromCopyState(board);
    return retVal;
}

bool EvalBoard::isDouble3AOneStrokePossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const
{
    bool retVal = false;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = &cpu;
        adversaryState = &human;
    }
    else
    {
        myState        = &human;;
        adversaryState = &cpu;
    }

    // Operate on copy instance.
    shared_ptr<IBoard> boardCopy = nullptr;
    shared_ptr<ThreatTracker> myStateCopy = nullptr;
    shared_ptr<ThreatTracker> adversaryStateCopy = nullptr;
    createCopyState(board, *myState, *adversaryState, boardCopy, myStateCopy, adversaryStateCopy);
    const uint32_t initMoveN = boardCopy->getMoveNumber();
    myStateCopy->mementoEnable();
    adversaryStateCopy->mementoEnable();

    //0. Extend:opponent doesn't have (3AA or 3B or 3C) which can, after extension, create 2A- why because it might lead to constant attack
    const bool isAdversary3AA = adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_AA) > 0;
    const bool isAdversary3B = adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_B) > 0;
    const bool isAdversary3C = adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_C) > 0;
    if(isAdversary3AA or isAdversary3B or isAdversary3C)
    {
        backFromCopyState(board);
        return  false;
    }

    // 1. Head shoot is possible when you have: at least 2x 2A and opponent neither have 3A nor 4ABC.
    const bool isMy3A   = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC = (myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary3A = adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0;

    const uint32_t my3A4ANumberOfThreatsInitStage0 =
        myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) +
        myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A);




    // 2. Check if head shot is possible.
    const bool isDouble3APossibleStage1 = (myState->getNumberOf(ThreatFinder::THREAT_2_CASE_A) > 1);

    if(isDouble3APossibleStage1)
    {
        // 3. Find duplicated gaps for 2A threat.
        std::vector<IBoard::PositionXY> duplicatedGaps2A;
        myState->getGapsDuplicated(duplicatedGaps2A, ThreatFinder::THREAT_2_CASE_A);

        // 3a. Go thru each gaps which are common (duplicated) and check if the move creates 2x3A threats.
        for(auto it1 = duplicatedGaps2A.begin(); it1 != duplicatedGaps2A.end(); ++it1)
        {
            //revert to initial state
            const auto n = boardCopy->getMoveNumber() - initMoveN;
            boardCopy->removeNLastMove(n);
            myStateCopy->mementoRevert(n);
            adversaryStateCopy->mementoRevert(n);

            const IBoard::PositionXY newMove1 =*it1;

            // Put move to create 3A.
            boardCopy->putMove(newMove1, myStateCopy->getPlayer());
            myStateCopy->updateScore(newMove1, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
            adversaryStateCopy->updateScore(newMove1, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

            // Count current number of 3A and 4A threats. Notice that it might happen that previous 3A -> 4A.
            const uint32_t my3A4ANumberOfThreatsCurrentStage2 = myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_A) +
                                                                myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_A);

            // A new move newMove1 must have created additional two 3A.
            const bool isDouble3APossibleStage2 =
                (my3A4ANumberOfThreatsCurrentStage2 >= (my3A4ANumberOfThreatsInitStage0 + 2));
            if(isDouble3APossibleStage2)
            {
                const uint32_t initMoveBeforeOpponent = boardCopy->getMoveNumber();
                buildUpMove = newMove1;
                retVal       = true;

                // 4. Its far probable that this move meets all requirements to create 2x3A.
                // But such case can be easily dismissed by adversary ...x.xx..x...
                // Check if adversary is able to shut down my attack.

                // 4a. Find duplicated gaps for 3A threat.
                std::vector<IBoard::PositionXY> duplicatedGaps3A;
                myStateCopy->getGapsDuplicated(duplicatedGaps3A, ThreatFinder::THREAT_3_CASE_A);

                for(auto it2 = duplicatedGaps3A.begin(); it2 != duplicatedGaps3A.end(); ++it2)
                {
                    // Revert board to the stage before opponent's move
                    const auto n = boardCopy->getMoveNumber() - initMoveBeforeOpponent;
                    boardCopy->removeNLastMove(n);
                    myStateCopy->mementoRevert(n);
                    adversaryStateCopy->mementoRevert(n);

                    // Put move to create 3A.
                    const IBoard::PositionXY adversaryMove = *it2;
                    boardCopy->putMove(adversaryMove, adversaryState->getPlayer());
                    myStateCopy->updateScore(adversaryMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                    adversaryStateCopy->updateScore(adversaryMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                    const uint32_t my3A4ANumberOfThreatsCurrentStage3 = myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_A) + myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_A);

                    // Adversary move must not shut down my both newly 3A threats.
                    // We can lost only one 3A.
                    const bool isDouble3APossibleStage3 =(my3A4ANumberOfThreatsCurrentStage3 + 1) >= my3A4ANumberOfThreatsCurrentStage2;

                    if(!isDouble3APossibleStage3)
                    {
                        retVal = false;
                        break;
                    }
                }
            }

            if(retVal)
            {
                break;
            }
        }
    }

    backFromCopyState(board);
    return retVal;
}

bool EvalBoard::isDouble3AMitigationPossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const
{
    bool retVal = false;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = &cpu;
        adversaryState = &human;
    }
    else
    {
        myState        = &human;;
        adversaryState = &cpu;
    }

    // Operate on copy instance.
    shared_ptr<IBoard> boardCopy = nullptr;
    shared_ptr<ThreatTracker> myStateCopy = nullptr;
    shared_ptr<ThreatTracker> adversaryStateCopy = nullptr;
    createCopyState(board, *myState, *adversaryState, boardCopy, myStateCopy, adversaryStateCopy);
    const uint32_t initMoveN = boardCopy->getMoveNumber();
    myStateCopy->mementoEnable();
    adversaryStateCopy->mementoEnable();

    const bool isMy4ABC = (myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const uint32_t adversary4ABCNumberOfThreatsInit =
        (adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) +
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C));
    const bool isAdversary4ABC = (adversary4ABCNumberOfThreatsInit > 0);
    const bool isAdversary3A   = (adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0);

    const uint32_t my3A4ANumberOfThreatsInit = myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) +
        myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A);

    // Mitigation is possible when you have 2x3A and adversary has 3BC.
    const bool isMy2x3A = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 1);
    const bool isAdversary3BC =
        (adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_AA) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_B) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_C) > 0);

    const bool is2x3AMitigationPossibleStage1 = (isMy2x3A && isAdversary3BC);
    const bool is2x3AMitigationPossibleStage2 = (isMy2x3A);

    if(is2x3AMitigationPossibleStage1)
    {
        // Check if there are common gaps for my 3A and adversary's 3BC.
        std::vector<IBoard::PositionXY> gaps3A;
        std::vector<IBoard::PositionXY> gaps3BC;
        myState->getGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);
        adversaryState->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_AA);
        adversaryState->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_B);
        adversaryState->getGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_C);

        const std::vector<IBoard::PositionXY> commonMovements = FindCommonMovements(gaps3A, gaps3BC);

        for(auto iter = commonMovements.begin(); iter != commonMovements.end(); ++iter)
        {
            //revert to initial state
            const auto n = boardCopy->getMoveNumber() - initMoveN;
            boardCopy->removeNLastMove(n);
            myStateCopy->mementoRevert(n);
            adversaryStateCopy->mementoRevert(n);

            const IBoard::PositionXY newMove1 =*iter;

            // Put adversary move
            buildUpMove = newMove1;
            boardCopy->putMove(newMove1, adversaryStateCopy->getPlayer());
            myStateCopy->updateScore(newMove1, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
            adversaryStateCopy->updateScore(newMove1, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

            const uint32_t adversary4ABCNumberOfThreatsCurrent =
                (adversaryStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_A) +
                adversaryStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
                adversaryStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
                adversaryStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_C));

            if(adversary4ABCNumberOfThreatsInit < adversary4ABCNumberOfThreatsCurrent)
            {
                // Check if adversary was able to mitigate one of my 3A threat.
                const uint32_t my3A4ANumberOfThreatsCurrent = myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_A) +
                                myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_A);
                const bool is2x3AMitigationPossibleStage2 = (my3A4ANumberOfThreatsCurrent == my3A4ANumberOfThreatsInit);

                if(!is2x3AMitigationPossibleStage2)
                {
                    // Adversary mitigated my 3A threat. Check if I can create another.
                    std::vector<IBoard::PositionXY> gaps4BC;
                    adversaryStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_AA);
                    adversaryStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_B);
                    adversaryStateCopy->getGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_C);

                    const IBoard::PositionXY newMove = gaps4BC[0];
                    boardCopy->putMove(newMove, myStateCopy->getPlayer());
                    myStateCopy->updateScore(newMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
                    adversaryStateCopy->updateScore(newMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

                    const bool isMy4A =
                        (myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0);
                    const uint32_t my3A4ANumberOfThreatsCurrent =
                            myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_A) +
                                myStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_A);

                    const bool is2x3AMitigationPossibleStage3 =
                        (my3A4ANumberOfThreatsCurrent >= 2) || isMy4A;

                    const bool isAdversaryHas2x4BC =        (adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) +
                                                             adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
                                                             adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
                                                             adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C))>1;

                    retVal = (is2x3AMitigationPossibleStage3 and !isAdversaryHas2x4BC) ? false : true;
                }
            }
            else
            {
                retVal = false;
            }

            if(retVal)
                break;
        }
    }
    else if(is2x3AMitigationPossibleStage2)
    {
        // Check if there are gaps common for 3A threats.
        std::vector<IBoard::PositionXY> gaps3A;
        myState->getGapsNonUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);

        VectorUnique<uint32_t , GomokuBoard::k_MAX_GOMOKU_BOARD_SQARE_SIZE> gate;
        for(auto citer = gaps3A.begin(); citer < gaps3A.end(); ++citer)
        {
            bool isUnique = !gate.isPresent(citer->convert2Linear(boardCopy->getSize()));
            if(isUnique)
            {
                gate.insert(citer->convert2Linear(boardCopy->getSize()));
            }
            else
            {
                buildUpMove = *citer;
                retVal         = true;
            }
        }
    }
    else
    {
        // Nothing to do.
    }

    // Leave not touched IBoard.
    backFromCopyState(board);
    return retVal;
}

bool EvalBoard::isBlockAndAttack3APossible(const bool isMaxPlayer, IBoard::PositionXY& buildUpMove, const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) const
{
    bool retVal = false;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = &cpu;
        adversaryState = &human;
    }
    else
    {
        myState        = &human;;
        adversaryState = &cpu;
    }

    // Operate on copy instance.
    shared_ptr<IBoard> boardCopy = nullptr;
    shared_ptr<ThreatTracker> myStateCopy = nullptr;
    shared_ptr<ThreatTracker> adversaryStateCopy = nullptr;
    createCopyState(board, *myState, *adversaryState, boardCopy, myStateCopy, adversaryStateCopy);
    const uint32_t initMoveN = boardCopy->getMoveNumber();
    myStateCopy->mementoEnable();
    adversaryStateCopy->mementoEnable();

    const bool isMy3A   = (myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC = (myState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           myState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary3A = (adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isAdversary3BC =
        (adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_B) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_AA) > 0 ||
         adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_C) > 0);
    const bool isAdversary2A = (adversaryState->getNumberOf(ThreatFinder::THREAT_2_CASE_A) > 0);

    const uint32_t my3AThreatNumberInit = myState->getNumberOf(ThreatFinder::THREAT_3_CASE_A);
    const uint32_t adversary3AThreatNumberInit =
        adversaryState->getNumberOf(ThreatFinder::THREAT_3_CASE_A);
    const uint32_t adversary4BCThreatNumberInit =
        adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
        adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
        adversaryState->getNumberOf(ThreatFinder::THREAT_4_CASE_C);

    // Mitigation is possible when you have 3A and adversary has 2A or 3BC
    const bool is3AMitigationPossibleStage1 = (isMy3A && (isAdversary3BC || isAdversary2A));

    if(is3AMitigationPossibleStage1)
    {
        // Check if there are common gaps for my 3A and adversary's 3BC.
        std::vector<IBoard::PositionXY> gaps3A;
        std::vector<IBoard::PositionXY> gaps2A3BC;
        myState->getGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);
        adversaryState->getGapsUnique(gaps2A3BC, ThreatFinder::THREAT_2_CASE_A);
        adversaryState->getGapsUnique(gaps2A3BC, ThreatFinder::THREAT_3_CASE_AA);
        adversaryState->getGapsUnique(gaps2A3BC, ThreatFinder::THREAT_3_CASE_B);
        adversaryState->getGapsUnique(gaps2A3BC, ThreatFinder::THREAT_3_CASE_C);

        const std::vector<IBoard::PositionXY> commonMovements = FindCommonMovements(gaps3A, gaps2A3BC);

        for(auto iter = commonMovements.begin(); iter != commonMovements.end(); ++iter)
        {
            //revert to initial state
            const auto n = boardCopy->getMoveNumber() - initMoveN;
            boardCopy->removeNLastMove(n);
            myStateCopy->mementoRevert(n);
            adversaryStateCopy->mementoRevert(n);

            const IBoard::PositionXY newMove1 =*iter;

            // Mitigation is possible if adversary is able shut down my 3A creating his 3A or 4BC threat at the same
            // time.
            boardCopy->putMove(newMove1, adversaryStateCopy->getPlayer());
            myStateCopy->updateScore(newMove1, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
            adversaryStateCopy->updateScore(newMove1, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

            const uint32_t my3AThreatNumber =
                    myStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_A);
            const uint32_t adversary3AThreatNumber =
                    adversaryStateCopy->getNumberOf(ThreatFinder::THREAT_3_CASE_A);
            const uint32_t adversary4BCThreatNumber =
                    adversaryStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_AA) +
                            adversaryStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_B) +
                            adversaryStateCopy->getNumberOf(ThreatFinder::THREAT_4_CASE_C);

            // Check if adversary was able to mitigate my 3A threat building up its 3A or 4BC by the way.
            const bool is3AMitigationPossibleStage1 = (my3AThreatNumberInit > my3AThreatNumber) &&
                                                      ((adversary3AThreatNumberInit < adversary3AThreatNumber) ||
                                                       (adversary4BCThreatNumberInit < adversary4BCThreatNumber));

            if(is3AMitigationPossibleStage1)
            {
                buildUpMove = newMove1;
                retVal = true;
            }

            if(retVal)
                break;
        }
    }

    // Leave not touched IBoard.
    backFromCopyState(board);
    return retVal;
}

int EvalBoard::getBonus(const bool isMaxPlayer, IBoard::PositionXY & buildUpMove) const
{
    int retVal = 0;
    int mySign = 0;
    IBoard::PositionXY temp;

    const ThreatTracker * myState        {nullptr};
    const ThreatTracker * adversaryState {nullptr};

    if(isMaxPlayer)
    {
        myState        = m_trackerCpu;
        adversaryState = m_trackerHuman;
        mySign               = 1;
    }
    else
    {
        myState        = m_trackerHuman;
        adversaryState = m_trackerCpu;
        mySign               = -1;
    }

    const uint32_t common3A_2A =
        myState->getCommonFieldNumber(ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A);
    const uint32_t common2A_2A =
        myState->getCommonFieldNumber(ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A);

    if(common3A_2A > 0)
    {
        // cout<<m_pIBoardScoreCpu->GetIBoard()<<endl;
        retVal += std::pow(4, common3A_2A) > 30 ? 2 * 30 : std::pow(4, common3A_2A);
    }
    if(common2A_2A > 0)
    {
        // cout<<m_pIBoardScoreCpu->GetIBoard()<<endl;
        retVal += std::pow(3, common2A_2A) > 30 ? 2 * 30 : std::pow(3, common2A_2A);
    }

    return retVal;
}

//copyies current state(board,trackers), so that we don't use original one. Notice that method changes board for global Score class.
void EvalBoard::createCopyState( const IBoard& board,
                                 const ThreatTracker& mySt,
                                 const ThreatTracker& adversarySt,
                                 shared_ptr<IBoard>& boardCpy,
                                 shared_ptr<ThreatTracker>& myStCpy,
                                 shared_ptr<ThreatTracker>& adversaryStCpy  ) const
{
    boardCpy = board.clone();
    myStCpy = make_shared<ThreatTracker>(mySt);
    adversaryStCpy = make_shared<ThreatTracker>(adversarySt);
    Score::getInstance()->setBoard(*boardCpy);
}

//Set oryginal board for global Score class.
void EvalBoard::backFromCopyState(const IBoard& board) const
{
    Score::getInstance()->setBoard(board);
}

//Get first common element. k_XY_OUT_OF_BOARD if not found.
static IBoard::PositionXY FindCommonMove(const std::vector<IBoard::PositionXY> & rGapsA,
                                           const std::vector<IBoard::PositionXY> & rGapsB)
{
    IBoard::PositionXY retVal {k_XY_OUT_OF_BOARD};
    auto common = FindCommonMovements(rGapsA,rGapsB);
    if(not common.empty())
    {
        retVal = common[0];
    }

    return retVal;
}

//Find common elements in both vectors. Empty vct if not found
static std::vector<IBoard::PositionXY> FindCommonMovements(const std::vector<IBoard::PositionXY> & rGapsA,
                                                             const std::vector<IBoard::PositionXY> & rGapsB)
{
    std::set<IBoard::PositionXY> setA(rGapsA.begin(), rGapsA.end());
    std::vector<IBoard::PositionXY> common{};

    for (const auto& item : rGapsB) {
        if (setA.find(item) != setA.end()) {
            common.push_back(item);
        }
    }

    return common;
}

/////////////////////////////////////////////////////////////////////////////////////
// METHOD NAME: ScoreEval
//
/// Evaluate score value taking offset into account.
///
/// @param evalBoard Base for evaluation.
///
/// @param offset Score offset.
///
/// @retval Container with common movements.
/////////////////////////////////////////////////////////////////////////////////////
static int ScoreEval(const IEvalBoard * const evalBoard, const int offset)
{
    int retVal = 0;

    int scoreTmp;
    IBoard::PositionXY moveTmp;
    retVal = offset + evalBoard->regularEval(false, moveTmp, scoreTmp);

    return retVal;
}
