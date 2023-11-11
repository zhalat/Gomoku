#pragma once
#include <assert.h>
#include "Interfaces/IBoard.h"
#include "ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Threat3CaseAA.
///
/// Threat3CaseAA class declaration.
///
/// @par Full Description.
/// Allows to find case c of threat three pattern on a gomoku board.
///
/// .x.x.x.
/// .x..xx.
/// .xx..x.
///-----------------------------------symmetric--------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////
class Threat3CaseAA final : public ThreatFinder
{
   public:
    static constexpr uint32_t PATTERN_LENGHT = 7;
    static const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_3AA;

    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const IBoard::Player playerPerspective) const override;
    void getThreatUpDetails(const IBoard::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override{ return false; }
    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
    };

    Threat3CaseAA();
    Threat3CaseAA(const Threat3CaseAA &&) = delete;
    Threat3CaseAA(const Threat3CaseAA &) = delete;
    Threat3CaseAA & operator=(const Threat3CaseAA &) = delete;
    Threat3CaseAA & operator=(const Threat3CaseAA &&) = delete;
    virtual ~Threat3CaseAA()=default;

   private:
    /// Threat pattern for X player.
    static const ThreatPattern m_threatPatternX[];

    /// Threat pattern for O player.
    static const ThreatPattern m_threatPatternO[];
    static const uint32_t m_pov[];
    static const uint32_t m_threatPatternElements;
    mutable ThreatDownDetails m_threatDownDetails;
};