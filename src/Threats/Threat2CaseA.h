#pragma once
#include <assert.h>
#include "Board.h"
#include "ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Threat2CaseA.
///
/// Threat2CaseA class declaration.
///
/// @par Full Description.
/// Allows to find case c of threat
///
// .xx...*
// .x.x..*
// .x..x.*
// ..xx..*
// ..x.x.*
// ...xx.*
///-----------------------------------symmetric--------------------------------------------
// *...xx.
// *..x.x.
// *..xx..
// *.x..x.
// *.x.x..
// *.xx...
///////////////////////////////////////////////////////////////////////////////////////////
class Threat2CaseA final : public ThreatFinder
{
   public:
    static constexpr uint32_t k_PATTERN_LENGHT = 7;
    const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_2A =
            {
                    { ThreatFinder::MY_PAWN, 2 },
                    { ThreatFinder::ENEMY_PAWN, 0 },
                    { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
                    { ThreatFinder::ASTERIX, -1 }  // it depends.
            };
    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const Board::Player playerPerspective) const override;
    void getThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override
    {
        const bool isAllDone = m_foundFlags.m_isSymmetricFound && m_foundFlags.m_isNormalFound;
        const bool retVal    = isAllDone == true ? false : true;
        return retVal;
    }

    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
        m_foundFlags.clearAll();
    };

    Threat2CaseA();
    Threat2CaseA(const Threat2CaseA &&) = delete;
    Threat2CaseA(const Threat2CaseA &) = delete;
    Threat2CaseA & operator=(const Threat2CaseA &) = delete;
    Threat2CaseA & operator=(const Threat2CaseA &&) = delete;
    virtual ~Threat2CaseA()=default;

   private:
    // Check threat to find normal and symmetric pattern.
    bool CheckThreatNormal(const uint32_t pretendThreat, const uint32_t pointOfView,
                           const Board::Player playerPerspective) const;
    bool CheckThreatSymmetric(const uint32_t pretendThreat, const uint32_t pointOfView,
                              const Board::Player playerPerspective) const;

    // Threat pattern for X player.
    static const ThreatPattern m_threatPatternX[];

    // Threat pattern for O player.
    static const ThreatPattern m_threatPatternO[];
    static const uint32_t m_pov[];
    static const uint32_t m_threatPatternElements;
    mutable ThreatDownDetails m_threatDownDetails;
    mutable FoundFlags m_foundFlags;
};
