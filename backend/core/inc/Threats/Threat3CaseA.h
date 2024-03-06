#pragma once
#include <assert.h>
#include "Interfaces/IBoard.h"
#include "ThreatFinder.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Threat3CaseA.
///
/// Threat3CaseA class declaration.
///
/// @par Full Description.
/// Allows to find case c of threat three pattern on a gomoku board.
///
/// *..XXX.
/// *.X.XX.
/// *.XX.X.
/// *.XXX..
/// ..XXX.*
/// .X.XX.*
/// .XX.X.*
/// .XXX..*
///-----------------------------------symmetric--------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////
class Threat3CaseA final : public ThreatFinder
{
   public:
    static constexpr uint32_t PATTERN_LENGHT = 7;
    static const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> k_ATOM_NUMBER_3A;

    bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                     const IBoard::Player playerPerspective) const override;
    void getThreatUpDetails(const IBoard::PositionXY initialPosition, const Trend trend,
                            ThreatUpDetails & rThreatUpDetails) const override;
    bool isSearchForSimmetrics() const override
    {
        const bool isAllDone = m_foundFlags.m_isSymmetricFound && m_foundFlags.m_isNormalFound;
        const bool retVal    = isAllDone == true ? false : true;
        return retVal;
    }
    void prepareSelfForNewSearch() override
    {
        m_threatDownDetails.clearAll();
        m_foundFlags.clearAll();
    };

    Threat3CaseA();
    Threat3CaseA(const Threat3CaseA &&) = delete;
    Threat3CaseA(const Threat3CaseA &) = delete;
    Threat3CaseA & operator=(const Threat3CaseA &) = delete;
    Threat3CaseA & operator=(const Threat3CaseA &&) = delete;
    virtual ~Threat3CaseA()=default;

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
