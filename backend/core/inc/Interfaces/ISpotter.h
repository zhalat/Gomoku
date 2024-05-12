#pragma once
#include <vector>

class ISpotter
{
public:
    struct RegionToInvestigate
    {
        IBoard::PositionXY m_xy;
        ThreatFinder::KindOfThreats m_threatKind;
        ThreatFinder::Trend m_trend;
    };

    struct SpottedThreats
    {
        ThreatFinder::ThreatLocation m_location;
        ThreatFinder::KindOfThreats m_threatKind;
        uint32_t m_multiplier;
    };

    virtual void setPlayerPerspective(IBoard::Player player) = 0;
    virtual void addToExecute(const RegionToInvestigate regionToInvestigate) =0;
    virtual std::vector<SpottedThreats> execute(const IBoard::PositionXY xy, const bool isOpponentMove,const uint32_t multiplier = ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER) =0;
    virtual void resetInstance() =0;
    ISpotter() = default;
    virtual ~ISpotter()=default;

};
