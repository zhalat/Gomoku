#pragma once
#include <assert.h>
#include "Board.h"
#include "ThreatFinder.h"

class Threat3CaseB final : public ThreatFinder
{
   public:
    static constexpr uint32_t PATTERN_LENGHT = 7;
    static const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_3B;

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

    Threat3CaseB();
    Threat3CaseB(const Threat3CaseB &&) = delete;
    Threat3CaseB(const Threat3CaseB &) = delete;
    Threat3CaseB & operator=(const Threat3CaseB &) = delete;
    Threat3CaseB & operator=(const Threat3CaseB &&) = delete;
    virtual ~Threat3CaseB()=default;

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
