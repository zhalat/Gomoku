#pragma once
#include <assert.h>
#include "Board.h"
#include "ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: ThreatWinner.
///
/// ThreatWinner class declaration.
///
/// @par Full Description.
/// Allows to find winner threat pattern on a gomoku board.
///
/// *XXXXX*
///-----------------------------------symmetric--------------------------------------------
/// n/a
///////////////////////////////////////////////////////////////////////////////////////////
class ThreatWinner final : public ThreatFinder
{
   public:
    static constexpr uint32_t PATTERN_LENGHT = 7;
    static const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_WINNER;

    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const Board::Player playerPerspective) const override;
    void getThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override { return false; }
    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
    };

    ThreatWinner();
    ThreatWinner(const ThreatWinner &&) = delete;
    ThreatWinner(const ThreatWinner &) = delete;
    ThreatWinner & operator=(const ThreatWinner &) = delete;
    ThreatWinner & operator=(const ThreatWinner &&) = delete;
    ~ThreatWinner()=default;

   private:
    /// Threat pattern for X player.
    static const ThreatPattern m_threatPatternX[];

    /// Threat pattern for O player.
    static const ThreatPattern m_threatPatternO[];
    static const uint32_t m_pov[];
    static const uint32_t m_threatPatternElements;
    mutable ThreatDownDetails m_threatDownDetails;
};

