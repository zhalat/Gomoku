#pragma once
#include <assert.h>
#include "Board.h"
#include "ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Threat4CaseB.
///
/// Threat4CaseB class declaration.
///
/// @par Full Description.
/// Allows to find case B of threat four pattern on a gomoku board.
///
/// OX.XXX*
/// OXX.XX*
/// OXXX.X*
/// OXXXX.*
///-----------------------------------symmetric--------------------------------------------
/// *.XXXXO
/// *X.XXXO
/// *XX.XXO
/// *XXX.XO
///////////////////////////////////////////////////////////////////////////////////////////
class Threat4CaseB final: public ThreatFinder
{
   public:
    static constexpr uint32_t PATTERN_LENGHT = 7;
    static const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_4B;

    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const Board::Player playerPerspective) const override;
    void getThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override{ return false; }
    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
        m_foundFlags.clearAll();
    };

    Threat4CaseB();
    Threat4CaseB(const Threat4CaseB &&) = delete;
    Threat4CaseB(const Threat4CaseB &) = delete;
    Threat4CaseB & operator=(const Threat4CaseB &) = delete;
    Threat4CaseB & operator=(const Threat4CaseB &&) = delete;
    virtual ~Threat4CaseB() =default;

   private:
    bool CheckThreatNormal(const uint32_t pretendThreat, const uint32_t pointOfView,
                           const Board::Player playerPerspective) const;
    bool CheckThreatSymmetric(const uint32_t pretendThreat, const uint32_t pointOfView,
                              const Board::Player playerPerspective) const;

    /// Threat pattern for X player.
    static const ThreatPattern m_threatPatternX[];

    /// Threat pattern for O player.
    static const ThreatPattern m_threatPatternO[];
    static const uint32_t m_pov[];
    static const uint32_t m_threatPatternElements;
    mutable ThreatDownDetails m_threatDownDetails;
    mutable FoundFlags m_foundFlags;
};
