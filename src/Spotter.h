#pragma once
#include "Interfaces/ISpotter.h"
#include "Threats/ThreatFinder.h"
#include <list>
#include <vector>

using std::list;
using std::vector;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Spotter
///
/// Spotter class declaration.
///
/// @par Full Description.
/// Search threats in provided region.
///////////////////////////////////////////////////////////////////////////////////////////
class Spotter : public ISpotter
{
   public:

    void addToExecute(const RegionToInvestigate regionToInvestigate) override;
    vector<SpottedThreats> execute(const IBoard::PositionXY xy, const bool isOpponentMove,const uint32_t multiplier = ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER) override;
    void resetInstance();

    Spotter(const IBoard::Player playerPerspective);
    Spotter(Spotter&& ref);
    Spotter(const Spotter& ref);
    Spotter & operator=(const Spotter& ref);
    Spotter & operator=(const Spotter&& ref);
    virtual ~Spotter()=default;

   private:
    IBoard::Player m_myPlayer;
    list<RegionToInvestigate> m_regionToInvestigate;
};
