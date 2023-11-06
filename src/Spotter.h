#pragma once
#include "Board.h"
#include "Threats/ThreatFinder.h"
#include "DataContainers/SingleList.h"
#include <vector>

using std::vector;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Spotter
///
/// Spotter class declaration.
///
/// @par Full Description.
/// Search threats in provided region.
///////////////////////////////////////////////////////////////////////////////////////////
class Spotter
{
   public:
    struct RegionToInvestigate
    {
        Board::PositionXY m_xy;
        ThreatFinder::KindOfThreats m_threatKind;
        ThreatFinder::Trend m_trend;
    };

    struct SpottedThreats
    {
        ThreatFinder::ThreatLocation m_location;
        ThreatFinder::KindOfThreats m_threatKind;
        uint32_t m_multiplier;
    };

    void addToExecute(const RegionToInvestigate regionToInvestigate);
    vector<SpottedThreats> execute(const Board::PositionXY xy, const bool isOpponentMove,const uint32_t multiplier = ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    void resetInstance();

    Spotter(const Board::Player playerPerspective):m_myPlayer{playerPerspective}{};
    virtual ~Spotter()=default;

   private:
    Spotter(const Spotter &&) = delete;
    Spotter(const Spotter &) = delete;
    Spotter & operator=(const Spotter &) = delete;
    Spotter & operator=(const Spotter &&) = delete;

    Board::Player m_myPlayer;
    SingleList<RegionToInvestigate> m_regionToInvestigate;
};
