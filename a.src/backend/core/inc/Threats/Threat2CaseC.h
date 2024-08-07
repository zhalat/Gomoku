#pragma once
#include <assert.h>
#include "Interfaces/IBoard.h"
#include "ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Threat2CaseC.
///
/// Threat2CaseC class declaration.
///
/// @par Full Description.
/// Allows to find case c of threat two pattern on a gomoku board.
///
/// oxx...o
/// o.xx..o
/// o..xx.o
/// o...xxo
/// ox.x..o
/// o.x.x.o
///-----------------------------------symmetric--------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////
class Threat2CaseC final : public ThreatFinder
{
   public:
    static constexpr uint32_t PATTERN_LENGHT = 7;
    static const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_2C;
    
    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const IBoard::Player playerPerspective) const override;
    void getThreatUpDetails(const IBoard::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override { return false; }
    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
    };

    Threat2CaseC();
    Threat2CaseC(const Threat2CaseC &&) = delete;
    Threat2CaseC(const Threat2CaseC &) = delete;
    Threat2CaseC & operator=(const Threat2CaseC &) = delete;
    Threat2CaseC & operator=(const Threat2CaseC &&) = delete;
    virtual ~Threat2CaseC()=default;

   private:
    /// Threat pattern for X player.
    static const ThreatPattern m_threatPatternX[];

    /// Threat pattern for O player.
    static const ThreatPattern m_threatPatternO[];
    static const uint32_t m_pov[];
    static const uint32_t m_threatPatternElements;
    mutable ThreatDownDetails m_threatDownDetails;
};

