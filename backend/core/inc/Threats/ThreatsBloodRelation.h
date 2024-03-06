#pragma once
#include <assert.h>
#include "DataContainers/SingleList.h"
#include "ThreatFinder.h"

class ThreatsBloodRelation final
{
   public:
    static constexpr uint32_t FOUR_LIST_SIZE             = 4;
    static constexpr uint32_t THREE_LIST_SIZE            = 4;
    static constexpr uint32_t TWO_LIST_SIZE              = 4;
    static constexpr uint32_t JOKER_LIST_SIZE            = 3;
    static constexpr uint32_t ACE_LIST_SIZE              = 2;
    static constexpr uint32_t MANY_GAPS_SIZE             = 3;
    static constexpr uint32_t EXTENDED_NEIGHBORHOOD_SIZE = 4;
    static constexpr uint32_t DISMISSAL_SIZE_X           = 13;
    static constexpr uint32_t DISMISSAL_SIZE_Y           = 8;
    static constexpr uint32_t PROMOTION_SIZE_X           = 13;
    static constexpr uint32_t PROMOTION_SIZE_Y           = 8;

    static bool IsOnFourList(const ThreatFinder::KindOfThreats);
    static bool IsOnThreeList(const ThreatFinder::KindOfThreats);
    static bool IsOnTwoList(const ThreatFinder::KindOfThreats);
    static bool IsOnJokerList(const ThreatFinder::KindOfThreats);
    static bool IsOnAceList(const ThreatFinder::KindOfThreats);
    static bool IsOnManyGapsList(const ThreatFinder::KindOfThreats);
    static bool IsOnExtendedNeighborhoodList(const ThreatFinder::KindOfThreats kindOfThreat);

    // Groups related to number of pawns in a row.
    static constexpr ThreatFinder::KindOfThreats FOUR_LIST[] = { ThreatFinder::THREAT_4_CASE_A,
                                                                 ThreatFinder::THREAT_4_CASE_AA,
                                                                 ThreatFinder::THREAT_4_CASE_B,
                                                                 ThreatFinder::THREAT_4_CASE_C };

    static constexpr ThreatFinder::KindOfThreats THREE_LIST[] = { ThreatFinder::THREAT_3_CASE_A,
                                                                  ThreatFinder::THREAT_3_CASE_AA,
                                                                  ThreatFinder::THREAT_3_CASE_B,
                                                                  ThreatFinder::THREAT_3_CASE_C };

    static constexpr ThreatFinder::KindOfThreats TWO_LIST[] = { ThreatFinder::THREAT_2_CASE_A,
                                                                ThreatFinder::THREAT_2_CASE_AA,
                                                                ThreatFinder::THREAT_2_CASE_B,
                                                                ThreatFinder::THREAT_2_CASE_C };

    // Groups related to threat danger.
    static constexpr ThreatFinder::KindOfThreats JOKER_LIST[] = { ThreatFinder::THREAT_4_CASE_A,
                                                                  ThreatFinder::THREAT_4_CASE_B,
                                                                  ThreatFinder::THREAT_4_CASE_C };

    static constexpr ThreatFinder::KindOfThreats ACE_LIST[] = { ThreatFinder::THREAT_4_CASE_A,
                                                                ThreatFinder::THREAT_4_CASE_C };

    // Groups that have more than one consecutive gaps.
    static constexpr ThreatFinder::KindOfThreats MANY_GAPS[] = { ThreatFinder::THREAT_3_CASE_A,
                                                                 ThreatFinder::THREAT_3_CASE_B,
                                                                 ThreatFinder::THREAT_2_CASE_A };

    // Groups that need to have extended neighborhoods.
    static constexpr ThreatFinder::KindOfThreats EXTENDED_NEIGHBORHOOD[] = { ThreatFinder::THREAT_3_CASE_A,
                                                                             ThreatFinder::THREAT_3_CASE_B,
                                                                             ThreatFinder::THREAT_3_CASE_C,
                                                                             ThreatFinder::THREAT_2_CASE_A };

    // Dismissal Group.
    static constexpr ThreatFinder::KindOfThreats DISMISSAL[DISMISSAL_SIZE_X][DISMISSAL_SIZE_Y] = {
        // here, only initialize threat but not its dependencies.
        // Keep the order as it is for Score::m_ThreatScore.
        // THREAT_WINNER
        { ThreatFinder::THREAT_NONE },
        // THREAT_4_CASE_A
        { ThreatFinder::THREAT_4_CASE_B, ThreatFinder::THREAT_NONE },
        // THREAT_4_CASE_AA
        { ThreatFinder::THREAT_4_CASE_B, ThreatFinder::THREAT_3_CASE_B, ThreatFinder::THREAT_2_CASE_B,
          ThreatFinder::THREAT_NONE },
        // THREAT_4_CASE_B
        { ThreatFinder::THREAT_4_CASE_C, ThreatFinder::THREAT_3_CASE_B, ThreatFinder::THREAT_2_CASE_B,
          ThreatFinder::THREAT_NONE },
        // THREAT_4_CASE_C
        { ThreatFinder::THREAT_NONE },
        // THREAT_3_CASE_A
        { ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_3_CASE_B, ThreatFinder::THREAT_3_CASE_C,
          ThreatFinder::THREAT_2_CASE_B, ThreatFinder::THREAT_NONE },
        // THREAT_3_CASE_AA
        { ThreatFinder::THREAT_3_CASE_B, ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_B,
          ThreatFinder::THREAT_NONE },
        // THREAT_3_CASE_B
        { ThreatFinder::THREAT_3_CASE_C, ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_B,
          ThreatFinder::THREAT_NONE },
        // THREAT_3_CASE_C
        { ThreatFinder::THREAT_NONE },
        // THREAT_2_CASE_A
        { ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_B, ThreatFinder::THREAT_2_CASE_C,
          ThreatFinder::THREAT_NONE },
        // THREAT_2_CASE_AA
        { ThreatFinder::THREAT_2_CASE_B, ThreatFinder::THREAT_NONE },
        // THREAT_2_CASE_B
        { ThreatFinder::THREAT_2_CASE_C, ThreatFinder::THREAT_NONE },
        // THREAT_2_CASE_C
        { ThreatFinder::THREAT_NONE }
    };

    // Promotion Group.
    static constexpr ThreatFinder::KindOfThreats PROMOTION[PROMOTION_SIZE_X][PROMOTION_SIZE_Y] = {
        // here, only initialize threat but not its dependencies.
        // Keep the order as it is for Score::m_ThreatScore.
        // THREAT_WINNER
        { ThreatFinder::THREAT_NONE },
        // THREAT_4_CASE_A
        { ThreatFinder::THREAT_WINNER, ThreatFinder::THREAT_NONE },
        // THREAT_4_CASE_AA
        { ThreatFinder::THREAT_WINNER, ThreatFinder::THREAT_NONE },
        // THREAT_4_CASE_B
        { ThreatFinder::THREAT_WINNER, ThreatFinder::THREAT_NONE },
        // THREAT_4_CASE_C
        { ThreatFinder::THREAT_WINNER, ThreatFinder::THREAT_NONE },
        // THREAT_3_CASE_A
        { ThreatFinder::THREAT_4_CASE_A, ThreatFinder::THREAT_4_CASE_AA, ThreatFinder::THREAT_4_CASE_B,
          ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_NONE },
        // THREAT_3_CASE_AA
        { ThreatFinder::THREAT_4_CASE_AA, ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A,
          ThreatFinder::THREAT_NONE },
        // THREAT_3_CASE_B
        { ThreatFinder::THREAT_4_CASE_B, ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_NONE },
        // THREAT_3_CASE_C
        { ThreatFinder::THREAT_4_CASE_C, ThreatFinder::THREAT_NONE },
        // THREAT_2_CASE_A
        { ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_3_CASE_AA, ThreatFinder::THREAT_3_CASE_B,
          ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_NONE },
        // THREAT_2_CASE_AA
        { ThreatFinder::THREAT_3_CASE_AA, ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_B,
          ThreatFinder::THREAT_NONE },
        // THREAT_2_CASE_B
        { ThreatFinder::THREAT_3_CASE_B, ThreatFinder::THREAT_3_CASE_C, ThreatFinder::THREAT_2_CASE_A,
          ThreatFinder::THREAT_NONE },
        // THREAT_2_CASE_C
        { ThreatFinder::THREAT_3_CASE_C, ThreatFinder::THREAT_NONE },

    };

    ThreatsBloodRelation()  = default;
    ThreatsBloodRelation(const ThreatsBloodRelation &&) = delete;
    ThreatsBloodRelation(const ThreatsBloodRelation &) = delete;
    ThreatsBloodRelation & operator=(const ThreatsBloodRelation &) = delete;
    ThreatsBloodRelation & operator=(const ThreatsBloodRelation &&) = delete;
    ~ThreatsBloodRelation() = default;
};
