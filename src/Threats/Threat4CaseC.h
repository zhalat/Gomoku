#pragma once
#include <assert.h>
#include "Board.h"
#include "ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Threat4CaseC.
///
/// Threat4CaseC class declaration.
///
/// @par Full Description.
/// Allows to find case C of threat four pattern on a gomoku board.
///
/// O.XXXXO
/// OX.XXXO
/// OXX.XXO
/// OXXX.XO
/// OXXXX.O
///-----------------------------------symmetric--------------------------------------------
/// n/a
///////////////////////////////////////////////////////////////////////////////////////////
class Threat4CaseC final : public ThreatFinder
{
   public:
    static constexpr uint32_t PATTERN_LENGHT = 7;
    static const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_4C;

    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const Board::Player playerPerspective) const override;
    void getThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override { return false; }
    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
    };

    Threat4CaseC();
    Threat4CaseC(const Threat4CaseC &&) = delete;
    Threat4CaseC(const Threat4CaseC &) = delete;
    Threat4CaseC & operator=(const Threat4CaseC &) = delete;
    Threat4CaseC & operator=(const Threat4CaseC &&) = delete;
    virtual ~Threat4CaseC()=default;

   private:
    /// Threat pattern for X player.
    static const ThreatPattern m_threatPatternX[];

    /// Threat pattern for O player.
    static const ThreatPattern m_threatPatternO[];
    static const uint32_t m_pov[];
    static const uint32_t m_threatPatternElements;
    mutable ThreatDownDetails m_threatDownDetails;
};
