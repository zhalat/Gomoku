#pragma once
#include <string.h>
#include "Threats/ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Score
///
/// Estimates board state for each player point of view.
///
/// @par Full Description.
/// Score class analyze board for searching threats and assigns points for each threat found.
///////////////////////////////////////////////////////////////////////////////////////////
class Score final
{
   public:
    /// Associate threat and score (how danger threat is).
    struct ThreatScore
    {
        const ThreatFinder::KindOfThreats threatKind;
        ThreatFinder * const m_pThreat;
        const uint32_t m_Score;
    };

    /// Threats score.
    static constexpr uint32_t THREAT_WINNER_SCORE = 1000;

    static constexpr uint32_t THREAT_4_CASE_A_SCORE  = 100;
    static constexpr uint32_t THREAT_4_CASE_AA_SCORE = 50;
    static constexpr uint32_t THREAT_4_CASE_B_SCORE  = 25;
    static constexpr uint32_t THREAT_4_CASE_C_SCORE  = 15;

    static constexpr uint32_t THREAT_3_CASE_A_SCORE  = 30;
    static constexpr uint32_t THREAT_3_CASE_AA_SCORE = 15;
    static constexpr uint32_t THREAT_3_CASE_B_SCORE  = 5;
    static constexpr uint32_t THREAT_3_CASE_C_SCORE  = 3;

    static constexpr uint32_t THREAT_2_CASE_A_SCORE  = 4;
    static constexpr uint32_t THREAT_2_CASE_AA_SCORE = 2;
    static constexpr uint32_t THREAT_2_CASE_B_SCORE  = 2;
    static constexpr uint32_t THREAT_2_CASE_C_SCORE  = 1;

    static const ThreatScore m_ThreatScore[];
    static constexpr uint32_t MAX_KIND_OF_THREATS = 13;
    static constexpr uint32_t MAX_TRACKED_THREATS = 15;

    static Score * getInstance();
    void setBoard(const Board & rBoard);
    Score() = default;

   private:
    Score(const Score &&) = delete;
    Score(const Score &) = delete;
    Score & operator=(const Score &) = delete;
    Score & operator=(const Score &&) = delete;
    virtual ~Score()=default;
};

