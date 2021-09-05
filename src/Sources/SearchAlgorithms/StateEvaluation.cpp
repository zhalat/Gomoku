#include <algorithm>  // For find().
#include <assert.h>   // For assert.
#include <math.h>
#include "ThreatsBloodRelation.hpp"  //
#include "VectorUnique.hpp"          // For VectorUnique definitions.
#include "StateEvaluation.hpp"       // For declaration.
#include "Score.hpp"

// FORWARD REFERENCES
/// Get first common element.
static Board::PositionField FindCommonMove(const std::vector<Board::PositionField> & rGapsA,
                                           const std::vector<Board::PositionField> & rGapsB);

/// Get all common elements.
static std::vector<Board::PositionField> FindCommonMovements(const std::vector<Board::PositionField> & rGapsA,
                                                             const std::vector<Board::PositionField> & rGapsB);

/// Evaluate score value taking offset into account.
static int ScoreEval(const StateEvaluationIf * const pStateEvaluationIf, const int offset);

// Point beyond the board. Useful for initialization.
static const Board::PositionField POSITION_OUT_OF_BOARD = Board::PositionField(Board::PositionField::INVALID_FIELD);
static const Board::PositionXY XY_OUT_OF_BOARD =
    Board::PositionXY(Board::PositionXY::INVALID_FIELD, Board::PositionXY::INVALID_FIELD);

StateEvaluation::HeadShotActionState StateEvaluation::m_HeadShotActionStateMaxConditionCheckerEnabled[] = {
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot4BCPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot3APossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot3AAPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShotDragonPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShotLizardPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsDouble3AOneStrokePossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsDouble3AMitigationPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsBlockAndAttack3APossible },
};

StateEvaluation::HeadShotActionState StateEvaluation::m_HeadShotActionStateMinConditionCheckerEnabled[] = {
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot4BCPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot3APossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot3AAPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShotDragonPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShotLizardPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsDouble3AOneStrokePossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsDouble3AMitigationPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsBlockAndAttack3APossible },
};

StateEvaluation::HeadShotActionState StateEvaluation::m_HeadShotActionStateMaxConditionCheckerDisabled[] = {
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot4BCPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot3APossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot3AAPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShotDragonPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShotLizardPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsDouble3AOneStrokePossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsDouble3AMitigationPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsBlockAndAttack3APossible },
};

StateEvaluation::HeadShotActionState StateEvaluation::m_HeadShotActionStateMinConditionCheckerDisabled[] = {
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot4BCPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot3APossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShot3AAPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShotDragonPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsHeadShotLizardPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsDouble3AOneStrokePossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsDouble3AMitigationPossible },
    { false, false, XY_OUT_OF_BOARD, &StateEvaluation::IsBlockAndAttack3APossible },
};

bool StateEvaluation::IsWinner(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const
{
    bool retVal = false;
    int mySign  = 0;

    const BoardScore * pMyBoardState = NULL;

    if(isMaxPlayer)
    {
        pMyBoardState = m_pBoardScoreCpu;
        mySign        = 1;
    }
    else
    {
        pMyBoardState = m_pBoardScoreHuman;
        mySign        = -1;
    }

    const bool isWinner = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER) > 0;

    if(isWinner)
    {
        rBuildUpMove = XY_OUT_OF_BOARD;
        rStateScore  = mySign * Score::THREAT_WINNER_SCORE;
        retVal       = true;
    }

    return retVal;
}

bool StateEvaluation::IsLooser(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const
{
    bool retVal       = false;
    int adversarySign = 0;

    const BoardScore * pAdversaryState = NULL;

    if(isMaxPlayer)
    {
        pAdversaryState = m_pBoardScoreHuman;
        adversarySign   = -1;
    }
    else
    {
        pAdversaryState = m_pBoardScoreCpu;
        adversarySign   = 1;
    }

    const bool isWinner = pAdversaryState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER) > 0;

    if(isWinner)
    {
        rBuildUpMove = XY_OUT_OF_BOARD;
        rStateScore  = adversarySign * Score::THREAT_WINNER_SCORE;
        retVal       = true;
    }

    return retVal;
}

/// Predict the winner.
bool StateEvaluation::ImpliciteWinner(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const
{
    bool retVal = false;
    int mySign  = 0;
    Board::PositionXY temp;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
        mySign               = 1;
    }
    else
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
        mySign               = -1;
    }

    const bool isMyWinner = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER) > 0;
    const bool isMy4A     = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A);
    const bool isMy2x4BC  = ((pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
                             pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
                             pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C)) > 1);
    const bool isMy4ABC   = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) ||
                          pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) ||
                          pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) ||
                          pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);

    const bool isMy4BC = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) ||
                         pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) ||
                         pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);
    const bool isMy3A   = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A);
    const bool isMy2x3A = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 1);

    const bool isAdversary3A   = pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A);
    const bool isAdversary4ABC = pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) ||
                                 pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) ||
                                 pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) ||
                                 pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);

    if(isMyWinner)
    {
        rStateScore = mySign * Score::THREAT_WINNER_SCORE;
        retVal      = true;
    }
    else if(!isAdversary4ABC && isMy4A)
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isAdversary4ABC && isMy2x4BC)
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isAdversary4ABC && isMy4BC && isMy3A)
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;

        // Be careful when adversary has 3A and blocking your 4ABC extends its 3A->4A.
        // See UT AlphaBetaTest::IssueTest20()
        if(isAdversary3A)
        {
            std::vector<Board::PositionField> gaps3A;
            std::vector<Board::PositionField> gaps4ABC;
            pAdversaryBoardState->GetGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);
            pMyBoardState->GetGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_AA);
            pMyBoardState->GetGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_B);
            pMyBoardState->GetGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_C);

            // Common gap means adversary's block->attack->win.
            retVal = (FindCommonMove(gaps3A, gaps4ABC) == POSITION_OUT_OF_BOARD) ? true : false;
        }
    }
    else if(!isAdversary4ABC && !isAdversary3A && isMy2x3A && !HeadShotRun(HEAD_SHOOT_4BC, !isMaxPlayer, temp, false) &&
            !HeadShotRun(HEAD_SHOOT_3A, !isMaxPlayer, temp, false) &&
            !HeadShotRun(HEAD_SHOOT_3AA, !isMaxPlayer, temp, false) &&
            !HeadShotRun(MITIGATION_3A, isMaxPlayer, temp, false))
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isAdversary4ABC && !isAdversary3A && isMy3A && !HeadShotRun(HEAD_SHOOT_4BC, !isMaxPlayer, temp, false) &&
            !HeadShotRun(HEAD_SHOOT_3A, !isMaxPlayer, temp, false) &&
            !HeadShotRun(HEAD_SHOOT_3AA, !isMaxPlayer, temp, false) &&
            ((HeadShotRun(HEAD_SHOOT_DOUBLE_3A_ONE_STROKE, isMaxPlayer, temp, false) &&
              !HeadShotRun(MITIGATION_3A, isMaxPlayer, temp, false) &&
              !HeadShotRun(MITIGATION_DOUBLE_3A, isMaxPlayer, temp, false)) ||
             HeadShotRun(HEAD_SHOOT_LIZARD, isMaxPlayer, temp, false)))
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isAdversary4ABC && isMy4ABC &&
            (HeadShotRun(HEAD_SHOOT_4BC, isMaxPlayer, temp, false) ||
             HeadShotRun(HEAD_SHOOT_3A, isMaxPlayer, temp, false) ||
             HeadShotRun(HEAD_SHOOT_3AA, isMaxPlayer, temp, false) ||
             HeadShotRun(HEAD_SHOOT_DRAGON, isMaxPlayer, temp, false)))
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;

        // Be careful when adversary has 3A and blocking your 4ABC extends its 3A->4A.
        // See UT AlphaBetaTest::IssueTest20()
        if(isAdversary3A)
        {
            std::vector<Board::PositionField> gaps3A;
            std::vector<Board::PositionField> gaps4ABC;
            pAdversaryBoardState->GetGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);
            pMyBoardState->GetGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_AA);
            pMyBoardState->GetGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_B);
            pMyBoardState->GetGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_C);

            // Common gap means adversary's block->attack->win.
            retVal = (FindCommonMove(gaps3A, gaps4ABC) == POSITION_OUT_OF_BOARD) ? true : false;
        }
    }
    else if(!isAdversary4ABC && !isAdversary3A && isMy3A && !HeadShotRun(HEAD_SHOOT_4BC, !isMaxPlayer, temp, false) &&
            !HeadShotRun(HEAD_SHOOT_3A, !isMaxPlayer, temp, false) &&
            !HeadShotRun(HEAD_SHOOT_3AA, !isMaxPlayer, temp, false) &&
            !HeadShotRun(MITIGATION_3A, isMaxPlayer, temp, false) &&
            !HeadShotRun(HEAD_SHOOT_DRAGON, !isMaxPlayer, temp, false) &&
            (HeadShotRun(HEAD_SHOOT_4BC, isMaxPlayer, temp, false) ||
             HeadShotRun(HEAD_SHOOT_3A, isMaxPlayer, temp, false) ||
             HeadShotRun(HEAD_SHOOT_3AA, isMaxPlayer, temp, false) ||
             HeadShotRun(HEAD_SHOOT_DRAGON, isMaxPlayer, temp, false) ||
             HeadShotRun(HEAD_SHOOT_LIZARD, isMaxPlayer, temp, false)))
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else
    {
        rStateScore = 0;
        retVal      = false;
    }

    return retVal;
}

bool StateEvaluation::ImpliciteLooser(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const
{
    bool retVal       = false;
    int adversarySign = 0;
    Board::PositionXY temp;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
        adversarySign        = -1;
    }
    else
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
        adversarySign        = 1;
    }

    const bool isAdversaryWinner = pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER) > 0;
    const bool isAdversary4ABC   = pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) ||
                                 pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) ||
                                 pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) ||
                                 pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);
    const bool isAdversary3A = pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A);
    const bool isMy4BC       = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) ||
                         pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) ||
                         pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);
    const bool isMy3A = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0;

    if(isAdversaryWinner)
    {
        rStateScore = adversarySign * Score::THREAT_WINNER_SCORE;
        retVal      = true;
    }
    else if(isAdversary4ABC)
    {
        rStateScore = adversarySign * Score::THREAT_WINNER_SCORE;
        retVal      = true;
    }
    else if(isAdversary3A && !isMy4BC)
    {
        rStateScore = adversarySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(HeadShotRun(HEAD_SHOOT_4BC, !isMaxPlayer, temp, true))
    {
        rStateScore = adversarySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(HeadShotRun(HEAD_SHOOT_3A, !isMaxPlayer, temp, true) ||
            HeadShotRun(HEAD_SHOOT_3AA, !isMaxPlayer, temp, true))
    {
        rStateScore = adversarySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(HeadShotRun(HEAD_SHOOT_DOUBLE_3A_ONE_STROKE, !isMaxPlayer, temp,
                        true) &&  // shall be also !isMy3A && ' the same as lizard'
            !HeadShotRun(MITIGATION_DOUBLE_3A, !isMaxPlayer, temp, true))
    {
        rStateScore = adversarySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(HeadShotRun(HEAD_SHOOT_DRAGON, !isMaxPlayer, temp, true))
    {
        rStateScore = adversarySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isMy3A && HeadShotRun(HEAD_SHOOT_LIZARD, !isMaxPlayer, temp, true))
    {
        rStateScore = adversarySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else
    {
        rStateScore = 0;
        retVal      = false;
    }

    return retVal;
}

bool StateEvaluation::RegularEval(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove, int & rStateScore) const
{
    rStateScore = (static_cast<int>(m_pBoardScoreCpu->GetScore() + GetBonus(true, rBuildUpMove)) -
                   static_cast<int>(m_pBoardScoreHuman->GetScore() + GetBonus(false, rBuildUpMove)));
}

bool StateEvaluation::ExtendWinnerThreatMove(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                             int & rStateScore) const
{
    bool retVal       = false;
    int mySign        = 0;
    int adversarySign = 0;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
        mySign               = 1;
        adversarySign        = -1;
    }
    else
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
        mySign               = -1;
        adversarySign        = 1;
    }

    // Operate on this board instance.
    Board * pBoard = const_cast<Board *>(&pMyBoardState->GetBoard());

    const bool isMy4ABC = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) ||
                          pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) ||
                          pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);
    const bool isMy4AA         = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA);
    const bool isMy3A          = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A);
    const bool isAdversary4ABC = pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) ||
                                 pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) ||
                                 pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) ||
                                 pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);

    if(isMy4ABC)
    {
        // Find gaps for 4ABC.
        std::vector<Board::PositionField> gaps4ABC;
        pMyBoardState->GetGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_A);
        pMyBoardState->GetGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_B);
        pMyBoardState->GetGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_C);

        // .xxxx. /o.xxxxo / oxx.xx*
        rBuildUpMove = Board::PositionXY(pMyBoardState->GetBoard().GetSize(), gaps4ABC[0]);
        rStateScore  = mySign * Score::THREAT_WINNER_SCORE;
        retVal       = true;
    }
    else if(isMy4AA)
    {
        // Find gaps for 4ABC.
        std::vector<Board::PositionField> gaps4ABC;
        pMyBoardState->GetGapsUnique(gaps4ABC, ThreatFinder::THREAT_4_CASE_AA);

        // .xxx.x.
        rBuildUpMove = Board::PositionXY(pMyBoardState->GetBoard().GetSize(), gaps4ABC[1]);
        rStateScore  = mySign * Score::THREAT_WINNER_SCORE;
        retVal       = true;
    }
    else if(isMy3A && !isAdversary4ABC)
    {
        // Find gaps for 3A.
        std::vector<Board::PositionField> gaps3A;
        pMyBoardState->GetGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);

        for(auto iter = gaps3A.begin(); iter != gaps3A.end(); ++iter)
        {
            const Board::PositionXY newMove(m_pBoard->GetSize(), *iter);
            BoardScore * pMyBoardStateCopy = new BoardScore(*pMyBoardState);
            pMyBoardStateCopy->SetBoard(*pBoard);

            pBoard->PutMove(newMove, pMyBoardState->GetPlayer());
            Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, newMove);

            const bool isMy4A = pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A);

            pBoard->RemoveMove(newMove);
            delete pMyBoardStateCopy;

            if(isMy4A)
            {
                rBuildUpMove = newMove;
                rStateScore  = mySign * Score::THREAT_WINNER_SCORE;
                retVal       = true;
                break;
            }
        }
    }

    return retVal;
}

bool StateEvaluation::ExtendWinnerActionMove(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                             int & rStateScore) const
{
    int retVal                              = false;
    int mySign                              = 0;
    int adversarySign                       = 0;
    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;
    Board::PositionXY buildUpTmp;

    if(isMaxPlayer)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
        mySign               = 1;
        adversarySign        = -1;
    }
    else
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
        mySign               = -1;
        adversarySign        = 1;
    }

    const bool isAdversary3A = pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0;

    if(IsHeadShot4BCPossible(isMaxPlayer, rBuildUpMove))
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(IsHeadShot3APossible(isMaxPlayer, rBuildUpMove))
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(IsHeadShot3AAPossible(isMaxPlayer, rBuildUpMove))
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(IsHeadShotDragonPossible(isMaxPlayer, rBuildUpMove))
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(!isAdversary3A && IsHeadShotLizardPossible(isMaxPlayer, rBuildUpMove))
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else if(IsDouble3AOneStrokePossible(isMaxPlayer, rBuildUpMove) && !IsHeadShot3APossible(!isMaxPlayer, buildUpTmp) &&
            !IsHeadShot3AAPossible(!isMaxPlayer, buildUpTmp) && !IsHeadShot4BCPossible(!isMaxPlayer, buildUpTmp) &&
            !IsHeadShotDragonPossible(!isMaxPlayer, buildUpTmp))
    {
        rStateScore = mySign * ScoreEval(this, MILESTONE_SCORE);
        retVal      = true;
    }
    else
    {}

    return retVal;
}

void StateEvaluation::SetBoards(const BoardScore & rBoardScoreCpu, const BoardScore & rBoardScoreHuman)
{
    m_pBoardScoreCpu   = &rBoardScoreCpu;
    m_pBoardScoreHuman = &rBoardScoreHuman;

    // Human and CPU must use the same  board.
    assert(&m_pBoardScoreHuman->GetBoard() == &m_pBoardScoreCpu->GetBoard());
    const Board * pBoard = &m_pBoardScoreCpu->GetBoard();
    m_pBoard             = const_cast<Board *>(pBoard);
}

StateEvaluation * StateEvaluation::GetInstance()
{
    static StateEvaluation stateEvaluation;
    return &stateEvaluation;
}

void StateEvaluation::Update() const
{
    // Boad state has changed. Clear state action.
    for(uint32_t i = 0; i < StateEvaluation::HEAD_SHOT_ACTION_NUMBER; ++i)
    {
        m_HeadShotActionStateMinConditionCheckerEnabled[i].m_IsUpToDate  = false;
        m_HeadShotActionStateMaxConditionCheckerEnabled[i].m_IsUpToDate  = false;
        m_HeadShotActionStateMinConditionCheckerDisabled[i].m_IsUpToDate = false;
        m_HeadShotActionStateMaxConditionCheckerDisabled[i].m_IsUpToDate = false;
    }
}

bool StateEvaluation::HeadShotRun(const HeadShotAction headShotAction, const bool isMaxPlayer,
                                  Board::PositionXY & rShotMove, const bool checkWinnerCondition) const
{
    bool retVal                                                 = false;
    const uint32_t index                                        = static_cast<uint32_t>(headShotAction);
    StateEvaluation::HeadShotActionState * pHeadShotActionState = NULL;

    if(isMaxPlayer && checkWinnerCondition)
    {
        pHeadShotActionState = &m_HeadShotActionStateMaxConditionCheckerEnabled[index];
    }
    else if(isMaxPlayer && !checkWinnerCondition)
    {
        pHeadShotActionState = &m_HeadShotActionStateMaxConditionCheckerDisabled[index];
    }
    else if(!isMaxPlayer && checkWinnerCondition)
    {
        pHeadShotActionState = &m_HeadShotActionStateMinConditionCheckerEnabled[index];
    }
    else if(!isMaxPlayer && !checkWinnerCondition)
    {
        pHeadShotActionState = &m_HeadShotActionStateMinConditionCheckerDisabled[index];
    }
    else
    {
        assert(false);
    }

    if(pHeadShotActionState->m_IsUpToDate)
    {
        // Don't run head shot function to save time. Get the previous result.
        retVal    = pHeadShotActionState->m_IsPossible;
        rShotMove = pHeadShotActionState->m_StateMove;
    }
    else
    {
        // You have to run head shot function due to board state changing.
        FuncPtr pFuncPtr = pHeadShotActionState->m_pFuncPtr;
        retVal           = (this->*pFuncPtr)(isMaxPlayer, rShotMove, checkWinnerCondition, NULL, NULL);

        // Save result & mark as up to date.
        pHeadShotActionState->m_IsPossible = retVal;
        pHeadShotActionState->m_StateMove  = rShotMove;
        pHeadShotActionState->m_IsUpToDate = true;
    }

    return retVal;
}

bool StateEvaluation::IsHeadShot4BCPossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                            const bool checkWinnerMoveCondition, const BoardScore * pCpuBoardScore,
                                            const BoardScore * pHumanBoardScore) const
{
    bool retVal = false;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
    }
    else if(isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pCpuBoardScore;
        pAdversaryBoardState = pHumanBoardScore;
    }
    else if(!isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
    }
    else if(!isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pHumanBoardScore;
        pAdversaryBoardState = pCpuBoardScore;
    }
    else
    {
        assert(false);
    }

    const bool isMy4ABC = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);

    const bool isHeadShootPossibleStage0 = (isMy4ABC || isAdversary4ABC) && checkWinnerMoveCondition;
    if(isHeadShootPossibleStage0)
    {
        return retVal;
    }

    // Head shoot is possible when you have: at least 2x 3BC.
    const bool isHeadShootPossibleStage1 =
        (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA) +
         pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B) +
         pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C)) > 1;

    if(isHeadShootPossibleStage1)
    {
        // Check if there are gaps common for 3BC threats.
        std::vector<Board::PositionField> gaps3BC;
        pMyBoardState->GetGapsNonUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_AA);
        pMyBoardState->GetGapsNonUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_B);
        pMyBoardState->GetGapsNonUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_C);

        VectorUnique<Board::PositionField, GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE> gate;
        for(auto citer = gaps3BC.begin(); citer < gaps3BC.end(); ++citer)
        {
            bool isUnique = !gate.IsPresent(*citer);
            if(isUnique)
            {
                gate.Insert(*citer);
            }
            else
            {
                rBuildUpMove = Board::PositionXY(m_pBoard->GetSize(), *citer);
                retVal       = true;
            }
        }
    }

    return retVal;
}

bool StateEvaluation::IsHeadShot3APossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                           const bool checkWinnerMoveCondition, const BoardScore * pCpuBoardScore,
                                           const BoardScore * pHumanBoardScore) const
{
    bool retVal = false;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
    }
    else if(isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pCpuBoardScore;
        pAdversaryBoardState = pHumanBoardScore;
    }
    else if(!isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
    }
    else if(!isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pHumanBoardScore;
        pAdversaryBoardState = pCpuBoardScore;
    }
    else
    {
        assert(false);
    }

    // Operate on this board instance.
    Board * pBoard           = const_cast<Board *>(&pMyBoardState->GetBoard());
    const uint32_t initMoveN = pMyBoardState->GetBoard().GetMoveNumber();

    // Head shoot is possible when you have: 2A && 3BC && opponent doesn't have 4ABC.
    const bool isMy2A   = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A) > 0;
    const bool isMy3BC  = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA) > 0 ||
                          pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B) > 0 ||
                          pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C) > 0);
    const bool isMy3A   = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary3A = pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0;

    const uint32_t my4BCNumberOfThreatsInit =
        pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
        pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
        pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);

    const bool isHeadShootPossibleStage0 = (isMy4ABC || isMy3A || isAdversary4ABC) && checkWinnerMoveCondition;
    if(isHeadShootPossibleStage0)
    {
        return retVal;
    }

    const bool isHeadShootPossibleStage1 = (isMy2A && isMy3BC && !isAdversary4ABC);

    if(isHeadShootPossibleStage1)
    {
        // Find common move for 2A && 3BC threats.
        std::vector<Board::PositionField> gaps2A;
        std::vector<Board::PositionField> gaps3BC;
        pMyBoardState->GetGapsUnique(gaps2A, ThreatFinder::THREAT_2_CASE_A);
        pMyBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_AA);
        pMyBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_B);
        pMyBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_C);

        const std::vector<Board::PositionField> commonMovements = FindCommonMovements(gaps3BC, gaps2A);
        for(auto iter = commonMovements.begin(); iter != commonMovements.end(); ++iter)
        {
            // Revert board. Use copy boardState 1.
            pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);
            BoardScore * pMyBoardStateCopy        = new BoardScore(*pMyBoardState);
            BoardScore * pAdversaryBoardStateCopy = new BoardScore(*pAdversaryBoardState);
            pMyBoardStateCopy->SetBoard(*pBoard);
            pAdversaryBoardStateCopy->SetBoard(*pBoard);

            // A new move must create my new 3A and 4BC.
            const Board::PositionXY newMove(pBoard->GetSize(), *iter);
            pBoard->PutMove(newMove, pMyBoardState->GetPlayer());
            Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, newMove);
            Score::GetInstance()->UpdateScore(*pAdversaryBoardStateCopy, newMove);

            // Check out if my 3A and 4BC has been created.
            const uint32_t my4BCNumberOfThreatsStage1 =
                (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
                 pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
                 pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));

            const bool isHeadShootPossibleStage2 =
                (my4BCNumberOfThreatsStage1 > my4BCNumberOfThreatsInit) &&
                (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0);

            if(isHeadShootPossibleStage2)
            {
                if(isAdversary3A)
                {
                    // Find common move for my 4BC and adversary's 3A threat.
                    std::vector<Board::PositionField> gaps4BC;
                    std::vector<Board::PositionField> gaps3A;
                    pMyBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_AA);
                    pMyBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_B);
                    pMyBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_C);
                    pAdversaryBoardStateCopy->GetGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);

                    const Board::PositionField commonMoveStage2 = FindCommonMove(gaps4BC, gaps3A);

                    if(commonMoveStage2 != POSITION_OUT_OF_BOARD)
                    {
                        const Board::PositionXY commonMoveStageXY2(pBoard->GetSize(), commonMoveStage2);

                        pBoard->PutMove(commonMoveStageXY2, pAdversaryBoardStateCopy->GetPlayer());
                        Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, commonMoveStageXY2);
                        Score::GetInstance()->UpdateScore(*pAdversaryBoardStateCopy, commonMoveStageXY2);

                        // Check if the move shut down my 4BC.
                        const uint32_t my4BCNumberOfThreatsStage2 =
                            (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
                             pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
                             pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));

                        // Only adverary's 4A threat may shut down my attack. 4AA is not included.
                        // My 3A threat must exist.
                        const uint32_t adversary4ANumberOfThreatsStage2 =
                            pAdversaryBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A);

                        const bool isMyAttackFail =
                            (((my4BCNumberOfThreatsStage2 < my4BCNumberOfThreatsStage1) &&
                              (adversary4ANumberOfThreatsStage2 > 0)) ||
                             (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A)) == 0);

                        if(isMyAttackFail)
                        {
                            retVal = false;
                        }
                        else
                        {
                            rBuildUpMove = newMove;
                            retVal       = true;
                        }
                    }
                    else
                    {
                        rBuildUpMove = newMove;
                        retVal       = true;
                    }
                }
                else
                {
                    rBuildUpMove = newMove;
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
                    pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A);
                const uint32_t my4BCNumberOfThreatsStage3 =
                    (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
                     pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
                     pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
                assert(my3ACNumberOfThreatsStage3 > 0);

                // Find the 4AB threat that has just been created at stage 1.
                std::vector<Board::PositionField> gaps3A;
                std::vector<Board::PositionField> gaps4BC;
                pMyBoardStateCopy->GetGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);
                pMyBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_AA);
                pMyBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_B);
                pMyBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_C);

                const std::vector<Board::PositionField> commonMovements = FindCommonMovements(gaps4BC, gaps3A);

                for(auto iter = commonMovements.begin(); iter != commonMovements.end(); ++iter)
                {
                    const Board::PositionXY shutDownMove(pBoard->GetSize(), *iter);
                    pBoard->PutMove(shutDownMove, pAdversaryBoardState->GetPlayer());
                    Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, shutDownMove);

                    // Check if one adversary move could shut down my action.
                    const uint32_t my3ACNumberOfThreatsStage4 =
                        pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A);
                    const uint32_t my4BCNumberOfThreatsStage4 =
                        (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
                         pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
                         pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
                    const bool isShutDown = (my3ACNumberOfThreatsStage4 < my3ACNumberOfThreatsStage3) &&
                                            (my4BCNumberOfThreatsStage4 < my4BCNumberOfThreatsStage3);

                    if(isShutDown)
                    {
                        retVal = false;
                        break;
                    }
                }

                delete pMyBoardStateCopy;
                delete pAdversaryBoardStateCopy;
                break;
            }
            else
            {
                delete pMyBoardStateCopy;
                delete pAdversaryBoardStateCopy;
            }
        }
    }

    // Leave not touched board.
    pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);

    return retVal;
}

bool StateEvaluation::IsHeadShot3AAPossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                            const bool checkWinnerMoveCondition, const BoardScore * pCpuBoardScore,
                                            const BoardScore * pHumanBoardScore) const
{
    bool retVal = false;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
    }
    else if(isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pCpuBoardScore;
        pAdversaryBoardState = pHumanBoardScore;
    }
    else if(!isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
    }
    else if(!isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pHumanBoardScore;
        pAdversaryBoardState = pCpuBoardScore;
    }
    else
    {
        assert(false);
    }

    // Operate on this board instance.
    Board * pBoard           = const_cast<Board *>(&pMyBoardState->GetBoard());
    const uint32_t initMoveN = pMyBoardState->GetBoard().GetMoveNumber();

    // Head shoot is possible when you have: 2A && 3BC && opponent doesn't have 4ABC.
    const bool isMy2A   = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A) > 0;
    const bool isMy3BC  = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA) > 0 ||
                          pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B) > 0 ||
                          pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C) > 0);
    const bool isMy3A   = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary3A = pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0;

    const uint32_t my4BCNumberOfThreatsInit =
        pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
        pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
        pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);

    const bool isHeadShootPossibleStage0 = (isMy4ABC || isMy3A || isAdversary4ABC) && checkWinnerMoveCondition;
    if(isHeadShootPossibleStage0)
    {
        return retVal;
    }

    const bool isHeadShootPossibleStage1 = (isMy2A && isMy3BC && !isAdversary4ABC);

    if(isHeadShootPossibleStage1)
    {
        // Find common move for 2A && 3BC threats.
        std::vector<Board::PositionField> gaps2A;
        std::vector<Board::PositionField> gaps3BC;
        pMyBoardState->GetGapsUnique(gaps2A, ThreatFinder::THREAT_2_CASE_A);
        pMyBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_AA);
        pMyBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_B);
        pMyBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_C);

        const std::vector<Board::PositionField> commonMovements = FindCommonMovements(gaps3BC, gaps2A);

        for(auto iter = commonMovements.begin(); iter != commonMovements.end(); ++iter)
        {
            // Revert board. Use copy boardState 1.
            pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);
            BoardScore * pMyBoardStateCopy        = new BoardScore(*pMyBoardState);
            BoardScore * pAdversaryBoardStateCopy = new BoardScore(*pAdversaryBoardState);
            pMyBoardStateCopy->SetBoard(*pBoard);
            pAdversaryBoardStateCopy->SetBoard(*pBoard);

            // Check if its possible to crate 3AA by force using 3BC and 2A.
            const Board::PositionXY newMove3AA(pBoard->GetSize(), *iter);
            pBoard->PutMove(newMove3AA, pMyBoardState->GetPlayer());
            Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, newMove3AA);
            Score::GetInstance()->UpdateScore(*pAdversaryBoardStateCopy, newMove3AA);

            const uint32_t my4BCNumberOfThreatsStage1 =
                (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
                 pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
                 pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));

#warning "checkWinnerMoveCondition. Might not work when my 3A threat was already present on board."
            const bool isHeadShootPossibleStage2 =
                (my4BCNumberOfThreatsStage1 > my4BCNumberOfThreatsInit) &&
                (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA) > 0);

            if(isHeadShootPossibleStage2)
            {
                bool isAdversaryShutMyAttackStage2 = false;

                if(isAdversary3A)
                {
                    // Find common move for my 4BC and adversary's 3A threat.
                    std::vector<Board::PositionField> gaps4BC;
                    std::vector<Board::PositionField> gaps3A;
                    pMyBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_AA);
                    pMyBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_B);
                    pMyBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_C);
                    pAdversaryBoardStateCopy->GetGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);

                    const Board::PositionField commonMoveStage2 = FindCommonMove(gaps4BC, gaps3A);

                    if(commonMoveStage2 != POSITION_OUT_OF_BOARD)
                    {
                        // Don't operate on original. Use copy 2.
                        const Board::PositionXY commonMoveStageXY2(pBoard->GetSize(), commonMoveStage2);

                        pBoard->PutMove(commonMoveStageXY2, pAdversaryBoardStateCopy->GetPlayer());
                        Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, commonMoveStageXY2);
                        Score::GetInstance()->UpdateScore(*pAdversaryBoardStateCopy, commonMoveStageXY2);

                        // Check if the move shut down my 4BC.
                        const uint32_t my4BCNumberOfThreatsStage2 =
                            (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
                             pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
                             pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));

                        // Only adverary's 4A threat may shut down my attack. 4AA is not included.
                        // My 3AA threat must exist.
                        const uint32_t adversary4ANumberOfThreatsStage2 =
                            pAdversaryBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A);

                        isAdversaryShutMyAttackStage2 =
                            (((my4BCNumberOfThreatsStage2 < my4BCNumberOfThreatsStage1) &&
                              (adversary4ANumberOfThreatsStage2 > 0)) ||
                             (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA)) == 0);
                    }
                }

                if(!isAdversaryShutMyAttackStage2)
                {
                    // Here we know that we have 3AA & 4BC and adversary is not able to shut down my 4BC by its 3A (if
                    // having it).

                    // Check if its possible to crate heat3A shoot using 3AA.
                    Board::PositionXY buildUpMoveTmp;
                    retVal =
                        IsHeadShot3APossible(true, buildUpMoveTmp, false, pMyBoardStateCopy, pAdversaryBoardStateCopy);

                    rBuildUpMove = (true == retVal) ? newMove3AA : rBuildUpMove;
                }
            }
            else
            {
                // It means that I am not able to crate either 4ABC or 3A. No death threat.
                retVal = false;
            }

            delete pMyBoardStateCopy;
            delete pAdversaryBoardStateCopy;

            if(retVal)
            {
                break;
            }
        }
    }

    // Leave not touched board.
    pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);

    return retVal;
}

bool StateEvaluation::IsHeadShotDragonPossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                               const bool checkWinnerMoveCondition, const BoardScore * pCpuBoardScore,
                                               const BoardScore * pHumanBoardScore) const
{
    bool retVal = false;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
    }
    else if(isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pCpuBoardScore;
        pAdversaryBoardState = pHumanBoardScore;
    }
    else if(!isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
    }
    else if(!isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pHumanBoardScore;
        pAdversaryBoardState = pCpuBoardScore;
    }
    else
    {
        assert(false);
    }

    // Operate on this board instance.
    Board * pBoard           = const_cast<Board *>(&pMyBoardState->GetBoard());
    const uint32_t initMoveN = pMyBoardState->GetBoard().GetMoveNumber();

    // Dragon shoot is possible when you have: 2x3BC opponent doesn't have 4ABC.
    const bool isMy2x3BC = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA) +
                            pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B) +
                            pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C)) > 1;
    const bool isMy3A    = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC  = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);

    const bool isHeadShootPossibleStage0 = (isMy4ABC || isMy3A || isAdversary4ABC) && checkWinnerMoveCondition;
    if(isHeadShootPossibleStage0)
    {
        return retVal;
    }

    const bool isHeadShootPossibleStage1 = (isMy2x3BC && !isAdversary4ABC);

    if(isHeadShootPossibleStage1)
    {
        // Find gap movies for 3BC threats.
        std::vector<Board::PositionField> gaps3BC;
        pMyBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_B);
        pMyBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_C);
        pMyBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_AA);

        for(auto iter = gaps3BC.begin(); iter != gaps3BC.end(); ++iter)
        {
            // Revert board. Use copy boardState 1.
            pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);
            BoardScore * pMyBoardStateCopy        = new BoardScore(*pMyBoardState);
            BoardScore * pAdversaryBoardStateCopy = new BoardScore(*pAdversaryBoardState);
            pMyBoardStateCopy->SetBoard(*pBoard);
            pAdversaryBoardStateCopy->SetBoard(*pBoard);

            // Put new move.
            const Board::PositionXY newMove(m_pBoard->GetSize(), *iter);
            pBoard->PutMove(newMove, pMyBoardState->GetPlayer());
            Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, newMove);
            Score::GetInstance()->UpdateScore(*pAdversaryBoardStateCopy, newMove);

            // Head shot Dragon precedes 3A Head shot.
            const bool isHeadShot3A =
                IsHeadShot3APossible(true, rBuildUpMove, false, pMyBoardStateCopy, pAdversaryBoardStateCopy);

            // Now we know that IsHeadShot3A is possible but we don't known if it was caused by newMove or existing one.
            // See IsHeadShotDragonPossibleTest7().
            bool isOK = false;
            if(isHeadShot3A)
            {
                // a.
                // Put HeadShot3A move and update threats.
                pBoard->PutMove(rBuildUpMove, pMyBoardState->GetPlayer());
                Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, rBuildUpMove);

                // b.
                // Such newly created 3A threat must contain also 'newMove'.
                const ThreatFinder::ThreatLocation threatLocation =
                    pMyBoardStateCopy->GetThreatList(ThreatFinder::THREAT_3_CASE_A).back();

                for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS; ++i)
                {
                    const Board::PositionXY el = threatLocation.m_ThreatDetails.m_MyPawns[i];
                    if(el == newMove)
                    {
                        isOK = true;
                        break;
                    }
                }
            }

            delete pMyBoardStateCopy;
            delete pAdversaryBoardStateCopy;

            if(isOK)
            {
                retVal = true;
                break;
            }
        }
    }

    // Leave not touched board.
    pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);

    return retVal;
}

bool StateEvaluation::IsHeadShotLizardPossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                               const bool checkWinnerMoveCondition, const BoardScore * pCpuBoardScore,
                                               const BoardScore * pHumanBoardScore) const
{
    bool retVal = false;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
    }
    else if(isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pCpuBoardScore;
        pAdversaryBoardState = pHumanBoardScore;
    }
    else if(!isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
    }
    else if(!isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pHumanBoardScore;
        pAdversaryBoardState = pCpuBoardScore;
    }
    else
    {
        assert(false);
    }

    // Operate on this board instance.
    Board * pBoard           = const_cast<Board *>(&pMyBoardState->GetBoard());
    const uint32_t initMoveN = pMyBoardState->GetBoard().GetMoveNumber();

    // Lizard shoot is possible when you have: 2x3BC && 2A opponent doesn't have 4ABC.
    const uint32_t myNumberOf3BC = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA) +
                                    pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B) +
                                    pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
    const bool isMy2x3BC         = (myNumberOf3BC > 1);
    const bool isMy2A            = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A) > 0);
    const bool isMy3A            = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC          = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);

    const bool isHeadShootPossibleStage0 = (isMy4ABC || isMy3A || isAdversary4ABC) && checkWinnerMoveCondition;
    if(isHeadShootPossibleStage0)
    {
        return retVal;
    }

    const bool isHeadShootPossibleStage1 = (isMy2x3BC && isMy2A && !isAdversary4ABC);

    if(isHeadShootPossibleStage1)
    {
        // a. Get gaps for each 3BC threat.
        static const uint32_t maxGapSize                    = 2;
        Board::PositionXY xyGaps[myNumberOf3BC][maxGapSize] = { 0 };
        ThreatFinder::KindOfThreats kindOfThreats[] = { ThreatFinder::THREAT_3_CASE_AA, ThreatFinder::THREAT_3_CASE_B,
                                                        ThreatFinder::THREAT_3_CASE_C };

        uint32_t index = 0;
        for(uint32_t i = 0; i < NUMELEM(kindOfThreats); ++i)
        {
            // Get 4BC threat list.
            const std::list<ThreatFinder::ThreatLocation> & theratList = pMyBoardState->GetThreatList(kindOfThreats[i]);

            for(auto iter = theratList.begin(); iter != theratList.end(); ++iter)
            {
                xyGaps[index][0]   = iter->m_ThreatDetails.m_Gaps[0];
                xyGaps[index++][1] = iter->m_ThreatDetails.m_Gaps[1];
            }
        }

        // b. Extend each 3BC threat and check if 'double 3A possible'.
        assert(myNumberOf3BC > 1);
        for(uint32_t i = 0; i < myNumberOf3BC - 1; ++i)
        {
            for(uint32_t j = 0; j < maxGapSize; ++j)
            {
                const Board::PositionXY newMove1 = xyGaps[i][j];

                for(uint32_t k = 0; k < maxGapSize; ++k)
                {
                    const Board::PositionXY newMove2 = xyGaps[i + 1][k];

                    // Revert board. Use copy boardState 1.
                    pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);
                    BoardScore * pMyBoardStateCopy        = new BoardScore(*pMyBoardState);
                    BoardScore * pAdversaryBoardStateCopy = new BoardScore(*pAdversaryBoardState);
                    pMyBoardStateCopy->SetBoard(*pBoard);
                    pAdversaryBoardStateCopy->SetBoard(*pBoard);

                    // Put new movies.
                    if(pBoard->PutMove(newMove1, pMyBoardState->GetPlayer()))
                    {
                        Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, newMove1);
                        Score::GetInstance()->UpdateScore(*pAdversaryBoardStateCopy, newMove1);
                    }

                    if(pBoard->PutMove(newMove2, pMyBoardState->GetPlayer()))
                    {
                        Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, newMove2);
                        Score::GetInstance()->UpdateScore(*pAdversaryBoardStateCopy, newMove2);
                    }

                    // Head shot Dragon precedes 3A Head shot.
                    const bool isDouble3APossible = IsDouble3AOneStrokePossible(
                        true, rBuildUpMove, false, pMyBoardStateCopy, pAdversaryBoardStateCopy);

                    // Now we know that IsHeadShot3A is possible but we don't known if it was caused by newMove or
                    // existing one. See IsHeadShotDragonPossibleTest7().
                    bool isOK1 = false;
                    if(isDouble3APossible)
                    {
                        // a.
                        // Put Double3AOneStroke move and update threats.
                        pBoard->PutMove(rBuildUpMove, pMyBoardState->GetPlayer());
                        Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, rBuildUpMove);

                        // b.
                        // Such newly created 3A threat must contain also 'newMove'.
                        const ThreatFinder::ThreatLocation threatLocation =
                            pMyBoardStateCopy->GetThreatList(ThreatFinder::THREAT_3_CASE_A).back();

                        for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS; ++i)
                        {
                            const Board::PositionXY el = threatLocation.m_ThreatDetails.m_MyPawns[i];
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
                        std::vector<Board::PositionField> my4BCgaps;
                        pMyBoardStateCopy->GetGapsUnique(my4BCgaps, ThreatFinder::THREAT_4_CASE_B);
                        pMyBoardStateCopy->GetGapsUnique(my4BCgaps, ThreatFinder::THREAT_4_CASE_C);
                        pMyBoardStateCopy->GetGapsUnique(my4BCgaps, ThreatFinder::THREAT_4_CASE_AA);

                        std::vector<Board::PositionField> adversart2Agaps;
                        pAdversaryBoardStateCopy->GetGapsUnique(adversart2Agaps, ThreatFinder::THREAT_2_CASE_A);
                        const Board::PositionField commonMove = FindCommonMove(my4BCgaps, adversart2Agaps);

                        if(POSITION_OUT_OF_BOARD == commonMove)
                        {
                            isOK2 = true;
                        }
                    }

                    delete pMyBoardStateCopy;
                    delete pAdversaryBoardStateCopy;

                    if(isOK2)
                    {
                        rBuildUpMove = newMove1;
                        retVal       = true;
                        goto exit;
                    }
                }
            }
        }
    }

exit:

    // Leave not touched board.
    pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);
    return retVal;
}

bool StateEvaluation::IsDouble3AOneStrokePossible(const bool isMaxPlayer, Board::PositionXY & rBuildUpMove,
                                                  const bool checkWinnerMoveCondition,
                                                  const BoardScore * pCpuBoardScore,
                                                  const BoardScore * pHumanBoardScore) const
{
    bool retVal = false;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
    }
    else if(isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pCpuBoardScore;
        pAdversaryBoardState = pHumanBoardScore;
    }
    else if(!isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
    }
    else if(!isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pHumanBoardScore;
        pAdversaryBoardState = pCpuBoardScore;
    }
    else
    {
        assert(false);
    }

    // Operate on this board instance.
    Board * pBoard           = const_cast<Board *>(&pMyBoardState->GetBoard());
    const uint32_t initMoveN = pMyBoardState->GetBoard().GetMoveNumber();

    // 1. Head shoot is possible when you have: at least 2x 2A and opponent neither have 3A nor 4ABC.
    const bool isMy3A   = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary3A = pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0;

    const uint32_t my3A4ANumberOfThreatsInitStage0 =
        pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) +
        pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A);

    // 1a. Don't consider creating double threat if there is winning move.
    const bool isDouble3APossibleStage0 =
        (isMy3A || isMy4ABC || isAdversary3A || isAdversary4ABC) && checkWinnerMoveCondition;
    if(isDouble3APossibleStage0)
    {
        return retVal;
    }

    // 2. Check if head shot is possible.
    const bool isDouble3APossibleStage1 =
        (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A) > 1);

    if(isDouble3APossibleStage1)
    {
        // 3. Find duplicated gaps for 2A threat.
        std::vector<Board::PositionField> duplicatedGaps2A;
        pMyBoardState->GetGapsDuplicated(duplicatedGaps2A, ThreatFinder::THREAT_2_CASE_A);

        // 3a. Go thru each gaps which are common (duplicated) and check if the move creates 2x3A threats.
        for(auto it = duplicatedGaps2A.begin(); it != duplicatedGaps2A.end(); ++it)
        {
            // Revert board. Use copy boardState 1.
            pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);
            BoardScore * pMyBoardStateCopy = new BoardScore(*pMyBoardState);
            pMyBoardStateCopy->SetBoard(*pBoard);

            // Put move to create 3A.
            const Board::PositionXY newMove(m_pBoard->GetSize(), *it);

            pBoard->PutMove(newMove, pMyBoardState->GetPlayer());
            Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, newMove);

            // Count current number of 3A and 4A threats. Notice that it might happen that previous 3A -> 4A.
            const uint32_t my3A4ANumberOfThreatsCurrentStage2 =
                pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) +
                pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A);

            // A new move newMove must have created additional two 3A.
            const bool isDouble3APossibleStage2 =
                (my3A4ANumberOfThreatsCurrentStage2 >= (my3A4ANumberOfThreatsInitStage0 + 2));
            if(isDouble3APossibleStage2)
            {
                rBuildUpMove = newMove;
                retVal       = true;

                // 4. Its far probable that this move meets all requirements to create 2x3A.
                // But such case can be easily dismissed by adversary ...x.xx..x...
                // Check if adversary is able to shut down my attack.

                // 4a. Find duplicated gaps for 3A threat.
                std::vector<Board::PositionField> duplicatedGaps3A;
                pMyBoardStateCopy->GetGapsDuplicated(duplicatedGaps3A, ThreatFinder::THREAT_3_CASE_A);

                for(auto it = duplicatedGaps3A.begin(); it != duplicatedGaps3A.end(); ++it)
                {
                    // Revert board. Use copy boardState 2.
                    pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);
                    BoardScore * pMyBoardStateCopy2 = new BoardScore(*pMyBoardStateCopy);
                    pMyBoardStateCopy2->SetBoard(*pBoard);

                    // Put move to create 3A.
                    const Board::PositionXY adversaryMove(m_pBoard->GetSize(), *it);
                    pBoard->PutMove(adversaryMove, pAdversaryBoardState->GetPlayer());
                    Score::GetInstance()->UpdateScore(*pMyBoardStateCopy2, adversaryMove);

                    const uint32_t my3A4ANumberOfThreatsCurrentStage3 =
                        pMyBoardStateCopy2->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) +
                        pMyBoardStateCopy2->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A);

                    delete pMyBoardStateCopy2;

                    // Adversary move must not shut down my both newly 3A threats.
                    // We can lost only one 3A.
                    const bool isDouble3APossibleStage3 =
                        (my3A4ANumberOfThreatsCurrentStage3 + 1) >= my3A4ANumberOfThreatsCurrentStage2;

                    if(!isDouble3APossibleStage3)
                    {
                        retVal = false;
                        break;
                    }
                }
            }

            delete pMyBoardStateCopy;

            if(retVal)
            {
                break;
            }
        }
    }

    // Leave not touched board.
    pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);

    return retVal;
}

bool StateEvaluation::IsDouble3AMitigationPossible(const bool isMaxPlayer, Board::PositionXY & rBuildDownMove,
                                                   const bool checkWinnerMoveCondition,
                                                   const BoardScore * pCpuBoardScore,
                                                   const BoardScore * pHumanBoardScore) const
{
    bool retVal = false;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
    }
    else if(isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pCpuBoardScore;
        pAdversaryBoardState = pHumanBoardScore;
    }
    else if(!isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
    }
    else if(!isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pHumanBoardScore;
        pAdversaryBoardState = pCpuBoardScore;
    }
    else
    {
        assert(false);
    }

    // Operate on this board instance.
    Board * pBoard           = const_cast<Board *>(&pMyBoardState->GetBoard());
    const uint32_t initMoveN = pMyBoardState->GetBoard().GetMoveNumber();

    const bool isMy4ABC = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const uint32_t adversary4ABCNumberOfThreatsInit =
        (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) +
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
    const bool isAdversary4ABC = (adversary4ABCNumberOfThreatsInit > 0);
    const bool isAdversary3A   = (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0);

    const uint32_t my3A4ANumberOfThreatsInit =
        pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) +
        pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A);

    // Don't consider mitigation if there is quick move to win.
    const bool is2x3AMitigationPossibleStage0 =
        (isMy4ABC || isAdversary4ABC || isAdversary3A) && checkWinnerMoveCondition;
    if(is2x3AMitigationPossibleStage0)
    {
        return retVal;
    }

    // Mitigation is possible when you have 2x3A and adversary has 3BC.
    const bool isMy2x3A = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 1);
    const bool isAdversary3BC =
        (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C) > 0);

    const bool is2x3AMitigationPossibleStage1 = (isMy2x3A && isAdversary3BC);
    const bool is2x3AMitigationPossibleStage2 = (isMy2x3A);

    if(is2x3AMitigationPossibleStage1)
    {
        // Check if there are common gaps for my 3A and adversary's 3BC.
        std::vector<Board::PositionField> gaps3A;
        std::vector<Board::PositionField> gaps3BC;
        pMyBoardState->GetGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);
        pAdversaryBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_AA);
        pAdversaryBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_B);
        pAdversaryBoardState->GetGapsUnique(gaps3BC, ThreatFinder::THREAT_3_CASE_C);

        const std::vector<Board::PositionField> commonMovements = FindCommonMovements(gaps3A, gaps3BC);

        for(auto iter = commonMovements.begin(); iter != commonMovements.end(); ++iter)
        {
            // Mitigation is possible if adversary is able shut down one of my 3A.
            const Board::PositionXY newMove(m_pBoard->GetSize(), *iter);

            // Revert board. Use copy boardState 1.
            pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);
            BoardScore * pMyBoardStateCopy        = new BoardScore(*pMyBoardState);
            BoardScore * pAdversaryBoardStateCopy = new BoardScore(*pAdversaryBoardState);
            pMyBoardStateCopy->SetBoard(*pBoard);
            pAdversaryBoardStateCopy->SetBoard(*pBoard);

            rBuildDownMove = newMove;
            pBoard->PutMove(newMove, pAdversaryBoardStateCopy->GetPlayer());
            Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, newMove);
            Score::GetInstance()->UpdateScore(*pAdversaryBoardStateCopy, newMove);

            const uint32_t adversary4ABCNumberOfThreatsCurrent =
                (pAdversaryBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) +
                 pAdversaryBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
                 pAdversaryBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
                 pAdversaryBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));

            if(adversary4ABCNumberOfThreatsInit < adversary4ABCNumberOfThreatsCurrent)
            {
                // Check if adversary was able to mitigate one of my 3A threat.
                const uint32_t my3A4ANumberOfThreatsCurrent =
                    pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) +
                    pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A);
                const bool is2x3AMitigationPossibleStage2 = (my3A4ANumberOfThreatsCurrent == my3A4ANumberOfThreatsInit);

                if(!is2x3AMitigationPossibleStage2)
                {
                    // Adversary mitigated my 3A threat. Check if I can create another.
                    std::vector<Board::PositionField> gaps4BC;
                    pAdversaryBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_AA);
                    pAdversaryBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_B);
                    pAdversaryBoardStateCopy->GetGapsUnique(gaps4BC, ThreatFinder::THREAT_4_CASE_C);

                    const Board::PositionXY newMove(m_pBoard->GetSize(), gaps4BC[0]);
                    pBoard->PutMove(newMove, pMyBoardStateCopy->GetPlayer());
                    Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, newMove);

                    const bool isMy4A =
                        (pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0);
                    const uint32_t my3A4ANumberOfThreatsCurrent =
                        pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) +
                        pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A);

                    const bool is2x3AMitigationPossibleStage3 =
                        (my3A4ANumberOfThreatsCurrent == my3A4ANumberOfThreatsInit) || isMy4A;

                    retVal = (is2x3AMitigationPossibleStage3) ? false : true;
                }
            }
            else
            {
                retVal = false;
            }

            delete pMyBoardStateCopy;
            delete pAdversaryBoardStateCopy;

            if(retVal)
                break;
        }
    }
    else if(is2x3AMitigationPossibleStage2)
    {
        // Check if there are gaps common for 3A threats.
        std::vector<Board::PositionField> gaps3A;
        pMyBoardState->GetGapsNonUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);

        VectorUnique<Board::PositionField, GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE> gate;
        for(auto citer = gaps3A.begin(); citer < gaps3A.end(); ++citer)
        {
            bool isUnique = !gate.IsPresent(*citer);
            if(isUnique)
            {
                gate.Insert(*citer);
            }
            else
            {
                rBuildDownMove = Board::PositionXY(m_pBoard->GetSize(), *citer);
                retVal         = true;
            }
        }
    }
    else
    {
        // Nothing to do.
    }

    // Leave not touched board.
    pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);

    return retVal;
}

bool StateEvaluation::IsBlockAndAttack3APossible(const bool isMaxPlayer, Board::PositionXY & rBuildDownMove,
                                                 const bool checkWinnerMoveCondition, const BoardScore * pCpuBoardScore,
                                                 const BoardScore * pHumanBoardScore) const
{
    bool retVal = false;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
    }
    else if(isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pCpuBoardScore;
        pAdversaryBoardState = pHumanBoardScore;
    }
    else if(!isMaxPlayer && NULL == pCpuBoardScore && NULL == pHumanBoardScore)
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
    }
    else if(!isMaxPlayer && NULL != pCpuBoardScore && NULL != pHumanBoardScore)
    {
        pMyBoardState        = pHumanBoardScore;
        pAdversaryBoardState = pCpuBoardScore;
    }
    else
    {
        assert(false);
    }

    // Operate on this board instance.
    Board * pBoard           = const_cast<Board *>(&pMyBoardState->GetBoard());
    const uint32_t initMoveN = pMyBoardState->GetBoard().GetMoveNumber();

    const bool isMy3A   = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isMy4ABC = (pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
                           pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary4ABC =
        (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C) > 0);
    const bool isAdversary3A = (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) > 0);
    const bool isAdversary3BC =
        (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA) > 0 ||
         pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C) > 0);
    const bool isAdversary2A = (pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A) > 0);

    const uint32_t my3AThreatNumberInit = pMyBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A);
    const uint32_t adversary3AThreatNumberInit =
        pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A);
    const uint32_t adversary4BCThreatNumberInit =
        pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
        pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
        pAdversaryBoardState->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);

    // Don't consider mitigation if there is quick move to win.
    const bool isBlockAndAttack3APossible0 = (isAdversary4ABC || isAdversary3A || isMy4ABC) && checkWinnerMoveCondition;
    if(isBlockAndAttack3APossible0)
    {
        return retVal;
    }

    // Mitigation is possible when you have 3A and adversary has 2A or 3BC
    const bool is3AMitigationPossibleStage1 = (isMy3A && (isAdversary3BC || isAdversary2A));

    if(is3AMitigationPossibleStage1)
    {
        // Check if there are common gaps for my 3A and adversary's 3BC.
        std::vector<Board::PositionField> gaps3A;
        std::vector<Board::PositionField> gaps2A3BC;
        pMyBoardState->GetGapsUnique(gaps3A, ThreatFinder::THREAT_3_CASE_A);
        pAdversaryBoardState->GetGapsUnique(gaps2A3BC, ThreatFinder::THREAT_2_CASE_A);
        pAdversaryBoardState->GetGapsUnique(gaps2A3BC, ThreatFinder::THREAT_3_CASE_AA);
        pAdversaryBoardState->GetGapsUnique(gaps2A3BC, ThreatFinder::THREAT_3_CASE_B);
        pAdversaryBoardState->GetGapsUnique(gaps2A3BC, ThreatFinder::THREAT_3_CASE_C);

        const std::vector<Board::PositionField> commonMovements = FindCommonMovements(gaps3A, gaps2A3BC);

        for(auto iter = commonMovements.begin(); iter != commonMovements.end(); ++iter)
        {
            // Mitigation is possible if adversary is able shut down my 3A creating his 3A or 4BC threat at the same
            // time.
            const Board::PositionXY newMove(m_pBoard->GetSize(), *iter);

            // Revert board. Use copy boardState 1.
            pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);
            BoardScore * pMyBoardStateCopy        = new BoardScore(*pMyBoardState);
            BoardScore * pAdversaryBoardStateCopy = new BoardScore(*pAdversaryBoardState);
            pMyBoardStateCopy->SetBoard(*pBoard);
            pAdversaryBoardStateCopy->SetBoard(*pBoard);

            rBuildDownMove = newMove;
            pBoard->PutMove(newMove, pAdversaryBoardStateCopy->GetPlayer());
            Score::GetInstance()->UpdateScore(*pMyBoardStateCopy, newMove);
            Score::GetInstance()->UpdateScore(*pAdversaryBoardStateCopy, newMove);

            const uint32_t my3AThreatNumber =
                pMyBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A);
            const uint32_t adversary3AThreatNumber =
                pAdversaryBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A);
            const uint32_t adversary4BCThreatNumber =
                pAdversaryBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA) +
                pAdversaryBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) +
                pAdversaryBoardStateCopy->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C);

            // Check if adversary was able to mitigate my 3A threat building up its 3A or 4BC by the way.
            const bool is3AMitigationPossibleStage1 = (my3AThreatNumberInit > my3AThreatNumber) &&
                                                      ((adversary3AThreatNumberInit < adversary3AThreatNumber) ||
                                                       (adversary4BCThreatNumberInit < adversary4BCThreatNumber));

            if(is3AMitigationPossibleStage1)
            {
                retVal = true;
            }

            delete pMyBoardStateCopy;
            delete pAdversaryBoardStateCopy;

            if(retVal)
                break;
        }
    }

    // Leave not touched board.
    pBoard->RemoveNLastMove(pBoard->GetMoveNumber() - initMoveN);

    return retVal;
}

int StateEvaluation::GetBonus(const bool isMaxPlayer, Board::PositionXY & rBuildDownMove,
                              const bool checkWinnerMoveCondition, const BoardScore * pCpuBoardScore,
                              const BoardScore * pHumanBoardScore) const
{
    int retVal = 0;
    int mySign = 0;
    Board::PositionXY temp;

    const BoardScore * pMyBoardState        = NULL;
    const BoardScore * pAdversaryBoardState = NULL;

    if(isMaxPlayer)
    {
        pMyBoardState        = m_pBoardScoreCpu;
        pAdversaryBoardState = m_pBoardScoreHuman;
        mySign               = 1;
    }
    else
    {
        pMyBoardState        = m_pBoardScoreHuman;
        pAdversaryBoardState = m_pBoardScoreCpu;
        mySign               = -1;
    }

    const uint32_t common3A_2A =
        pMyBoardState->GetCommonFieldNumber(ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A);
    const uint32_t common2A_2A =
        pMyBoardState->GetCommonFieldNumber(ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A);

    if(common3A_2A > 0)
    {
        // cout<<m_pBoardScoreCpu->GetBoard()<<endl;
        retVal += std::pow(4, common3A_2A) > 30 ? 2 * 30 : std::pow(4, common3A_2A);
    }
    if(common2A_2A > 0)
    {
        // cout<<m_pBoardScoreCpu->GetBoard()<<endl;
        retVal += std::pow(3, common2A_2A) > 30 ? 2 * 30 : std::pow(3, common2A_2A);
    }

    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////
// METHOD NAME: FindCommonMove
//
/// Get first common element.
///
/// @param rGapsA First container
///
/// @param rGapsB Second container
///
/// @retval First common element or POSITION_OUT_OF_BOARD if not found.
/////////////////////////////////////////////////////////////////////////////////////
static Board::PositionField FindCommonMove(const std::vector<Board::PositionField> & rGapsA,
                                           const std::vector<Board::PositionField> & rGapsB)
{
    Board::PositionField retVal = POSITION_OUT_OF_BOARD;

    VectorUnique<Board::PositionField, GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE> gapsA;
    gapsA = rGapsA;

    for(auto iter = rGapsB.begin(); iter != rGapsB.end(); ++iter)
    {
        const bool isGapOK = gapsA.IsPresent(*iter);
        if(isGapOK)
        {
            retVal = *iter;
            break;
        }
    }

    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////
// METHOD NAME: FindCommonMovements
//
/// Get all common element.
///
/// @param rGapsA First container
///
/// @param rGapsB Second container
///
/// @retval Container with common movements.
/////////////////////////////////////////////////////////////////////////////////////
static std::vector<Board::PositionField> FindCommonMovements(const std::vector<Board::PositionField> & rGapsA,
                                                             const std::vector<Board::PositionField> & rGapsB)
{
    std::vector<Board::PositionField> retVal;

    VectorUnique<Board::PositionField, GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE> gapsA;
    gapsA = rGapsA;

    for(auto iter = rGapsB.begin(); iter != rGapsB.end(); ++iter)
    {
        const bool isGapOK = gapsA.IsPresent(*iter);
        if(isGapOK)
        {
            retVal.push_back(*iter);
        }
    }

    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////
// METHOD NAME: ScoreEval
//
/// Evaluate score value taking offset into account.
///
/// @param pStateEvaluationIf Base for evaluation.
///
/// @param offset Score offset.
///
/// @retval Container with common movements.
/////////////////////////////////////////////////////////////////////////////////////
static int ScoreEval(const StateEvaluationIf * const pStateEvaluationIf, const int offset)
{
    int retVal = 0;

    int scoreTmp;
    Board::PositionXY moveTmp;
    retVal = offset + pStateEvaluationIf->RegularEval(false, moveTmp, scoreTmp);

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
