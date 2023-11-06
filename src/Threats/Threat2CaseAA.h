#pragma once
#include <assert.h>
#include "Board.h"
#include "ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Threat2CaseAA.
///
/// Threat2CaseAA class declaration.
///
/// @par Full Description.
/// Allows to find case c of threat two pattern on a gomoku board.
///
// *x...x*
///-----------------------------------symmetric--------------------------------------------
/// n.a
///////////////////////////////////////////////////////////////////////////////////////////
class Threat2CaseAA final : public ThreatFinder
{
   public:
    static constexpr uint32_t PATTERN_LENGHT = 7;
    static const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_2AA;

    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const Board::Player playerPerspective) const override;
    void getThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override{ return false; }
    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
    };

    Threat2CaseAA();
    Threat2CaseAA(const Threat2CaseAA &&) = delete;
    Threat2CaseAA(const Threat2CaseAA &) = delete;
    Threat2CaseAA & operator=(const Threat2CaseAA &) = delete;
    Threat2CaseAA & operator=(const Threat2CaseAA &&) = delete;
    virtual ~Threat2CaseAA()=default;

   private:
    /// Threat pattern for X player.
    static const ThreatPattern m_threatPatternX[];

    /// Threat pattern for O player.
    static const ThreatPattern m_threatPatternO[];
    static const uint32_t m_pov[];
    static const uint32_t m_threatPatternElements;
    mutable ThreatDownDetails m_threatDownDetails;
};
