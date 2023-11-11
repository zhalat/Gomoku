#pragma  once
#include <assert.h>
#include "Interfaces/IBoard.h"
#include "ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Threat2CaseB.
///
/// Threat2CaseB class declaration.
///
/// @par Full Description.
/// Allows to find case B of threat two pattern on a gomoku board.
///
/// oxx...*
/// ox.x..*
/// ox..x.*
/// ox...x*
///-----------------------------------symmetric--------------------------------------------
/// *x...xo
/// *.x..xo
/// *..x.xo
/// *...xxo
///////////////////////////////////////////////////////////////////////////////////////////
class Threat2CaseB final : public ThreatFinder
{
   public:
    static constexpr uint32_t PATTERN_LENGHT = 7;
    static const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_2B;

    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const IBoard::Player playerPerspective) const override;
    void getThreatUpDetails(const IBoard::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override { return false; }
    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
        m_foundFlags.clearAll();
    };

    Threat2CaseB();
    Threat2CaseB(const Threat2CaseB &&) = delete;
    Threat2CaseB(const Threat2CaseB &) = delete;
    Threat2CaseB & operator=(const Threat2CaseB &) = delete;
    Threat2CaseB & operator=(const Threat2CaseB &&) = delete;
    virtual ~Threat2CaseB()=default;
    
   private:
    // Check threat to find normal and symmetric pattern.
    bool CheckThreatNormal(const uint32_t pretendThreat, const uint32_t pointOfView,
                           const IBoard::Player playerPerspective) const;
    bool CheckThreatSymmetric(const uint32_t pretendThreat, const uint32_t pointOfView,
                              const IBoard::Player playerPerspective) const;

    /// Threat pattern for X player.
    static const ThreatPattern m_threatPatternX[];

    /// Threat pattern for O player.
    static const ThreatPattern m_threatPatternO[];
    static const uint32_t m_pov[];
    static const uint32_t m_threatPatternElements;
    mutable ThreatDownDetails m_threatDownDetails;
    mutable FoundFlags m_foundFlags;
};
