#include "Score.h"
#include "Threats/Threat2CaseA.h"
#include "Threats/Threat2CaseAA.h"
#include "Threats/Threat2CaseB.h"
#include "Threats/Threat2CaseC.h"
#include "Threats/Threat3CaseA.h"
#include "Threats/Threat3CaseAA.h"
#include "Threats/Threat3CaseB.h"
#include "Threats/Threat3CaseC.h"
#include "Threats/Threat4CaseA.h"
#include "Threats/Threat4CaseAA.h"
#include "Threats/Threat4CaseB.h"
#include "Threats/Threat4CaseC.h"
#include "Threats/ThreatWinner.h"
#include "Threats/ThreatFinder.h"

static ThreatWinner threatWinner;
static Threat4CaseA threat4CaseA;
static Threat4CaseAA threat4CaseAA;
static Threat4CaseB threat4CaseB;
static Threat4CaseC threat4CaseC;
static Threat3CaseA threat3CaseA;
static Threat3CaseAA threat3CaseAA;
static Threat3CaseB threat3CaseB;
static Threat3CaseC threat3CaseC;
static Threat2CaseA threat2CaseA;
static Threat2CaseAA threat2CaseAA;
static Threat2CaseB threat2CaseB;
static Threat2CaseC threat2CaseC;

const Score::ThreatScore Score::m_ThreatScore[] = {
    /*0 */ { ThreatFinder::THREAT_WINNER, &threatWinner, THREAT_WINNER_SCORE },
    /*1 */ { ThreatFinder::THREAT_4_CASE_A, &threat4CaseA, THREAT_4_CASE_A_SCORE },
    /*2 */ { ThreatFinder::THREAT_4_CASE_AA, &threat4CaseAA, THREAT_4_CASE_AA_SCORE },
    /*3 */ { ThreatFinder::THREAT_4_CASE_B, &threat4CaseB, THREAT_4_CASE_B_SCORE },
    /*4 */ { ThreatFinder::THREAT_4_CASE_C, &threat4CaseC, THREAT_4_CASE_C_SCORE },
    /*5 */ { ThreatFinder::THREAT_3_CASE_A, &threat3CaseA, THREAT_3_CASE_A_SCORE },
    /*6 */ { ThreatFinder::THREAT_3_CASE_AA, &threat3CaseAA, THREAT_3_CASE_AA_SCORE },
    /*7 */ { ThreatFinder::THREAT_3_CASE_B, &threat3CaseB, THREAT_3_CASE_B_SCORE },
    /*8 */ { ThreatFinder::THREAT_3_CASE_C, &threat3CaseC, THREAT_3_CASE_C_SCORE },
    /*9 */ { ThreatFinder::THREAT_2_CASE_A, &threat2CaseA, THREAT_2_CASE_A_SCORE },
    /*10 */ { ThreatFinder::THREAT_2_CASE_AA, &threat2CaseAA, THREAT_2_CASE_AA_SCORE },
    /*11*/ { ThreatFinder::THREAT_2_CASE_B, &threat2CaseB, THREAT_2_CASE_B_SCORE },
    /*12*/ { ThreatFinder::THREAT_2_CASE_C, &threat2CaseC, THREAT_2_CASE_C_SCORE },
};

Score * Score::getInstance()
{
    static Score score{};
    return &score;
}

void Score::setBoard(const Board & rBoard)
{
    for(uint32_t i = 0; i < NUMELEM(m_ThreatScore); ++i)
    {
        m_ThreatScore[i].m_pThreat->setBoard(&rBoard);
    }
}
