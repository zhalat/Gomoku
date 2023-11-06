#pragma once
#include <assert.h>
#include "Board.h"
#include "ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Threat4CaseA.
///
/// Threat4CaseA class declaration.
///
/// @par Full Description.
/// Allows to find case B of threat four pattern on a gomoku board.
///
/// .XXXX.
///-----------------------------------symmetric--------------------------------------------
/// n/a
///////////////////////////////////////////////////////////////////////////////////////////
class Threat4CaseA final : public ThreatFinder
{
   public:

    static constexpr uint32_t PATTERN_LENGHT = 6;
    static const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_4A;

    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const Board::Player playerPerspective) const override;
    void getThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override{ return false; }
    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
    };
    
    Threat4CaseA();
    Threat4CaseA(const Threat4CaseA &&) = delete;
    Threat4CaseA(const Threat4CaseA &) = delete;
    Threat4CaseA & operator=(const Threat4CaseA &) = delete;
    Threat4CaseA & operator=(const Threat4CaseA &&) = delete;
    virtual ~Threat4CaseA()=default;

private:
    /// Threat pattern for X player.
    static const ThreatPattern m_threatPatternX[];

    /// Threat pattern for O player.
    static const ThreatPattern m_threatPatternO[];
    static const uint32_t m_pov[];
    static const uint32_t m_threatPatternElements;
    mutable ThreatDownDetails m_threatDownDetails;
};
