#pragma once
#include <assert.h>
#include "Board.h"
#include "ThreatFinder.h"

class Threat4CaseAA final : public ThreatFinder
{
   public:
    static constexpr uint32_t PATTERN_LENGHT = 7;
    const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_4AA = {
            { ThreatFinder::MY_PAWN, 2 },
            { ThreatFinder::ENEMY_PAWN, 0 },
            { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
            { ThreatFinder::ASTERIX, -1 }  // it depends.
    };
    
    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const Board::Player playerPerspective) const override;
    void getThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override{ return false; }
    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
    };

    Threat4CaseAA();
    Threat4CaseAA(const Threat4CaseAA &&) = delete;
    Threat4CaseAA(const Threat4CaseAA &) = delete;
    Threat4CaseAA & operator=(const Threat4CaseAA &) = delete;
    Threat4CaseAA & operator=(const Threat4CaseAA &&) = delete;
    virtual ~Threat4CaseAA()=default;

private:
    /// Threat pattern for X player.
    static const ThreatPattern m_threatPatternX[];

    /// Threat pattern for O player.
    static const ThreatPattern m_threatPatternO[];
    static const uint32_t m_pov[];
    static const uint32_t m_threatPatternElements;
    mutable ThreatDownDetails m_threatDownDetails;
};
