#include <memory>
#include "Threats/ThreatsBloodRelation.h"
#include "Spotter.h"
#include "Score.h"

Spotter::Spotter(const IBoard::Player playerPerspective)
:m_myPlayer{playerPerspective}
{};

Spotter::Spotter(const Spotter& ref)
:m_myPlayer{ref.m_myPlayer}
,m_regionToInvestigate{ref.m_regionToInvestigate}
{}

Spotter::Spotter(Spotter&& ref)
:m_myPlayer{ref.m_myPlayer}
,m_regionToInvestigate{std::move(ref.m_regionToInvestigate)}
{}

Spotter& Spotter::operator=(const Spotter& ref)
{
    if (this != &ref)
    {
        m_myPlayer = ref.m_myPlayer;
        m_regionToInvestigate = ref.m_regionToInvestigate;
    }
    return *this;
}

Spotter & Spotter::operator=(const Spotter&& ref)
{
    if (this != &ref)
    {
        m_myPlayer = std::move(ref.m_myPlayer);
        m_regionToInvestigate = std::move(ref.m_regionToInvestigate);
    }
    return *this;
}

void Spotter::addToExecute(const RegionToInvestigate regionToInvestigate)
{
    m_regionToInvestigate.push_back(regionToInvestigate);
}

vector<Spotter::SpottedThreats> Spotter::execute(const IBoard::PositionXY xy, const bool isOpponentMove, const uint32_t multiplier)
{

    // Keeps in bit representation, direction where threats have been found.
    uint32_t trendMark = 0;

    vector<Spotter::SpottedThreats> retVal;

    for(std::list<RegionToInvestigate>::iterator it = m_regionToInvestigate.begin(); it!=m_regionToInvestigate.end();++it)
    {
        const RegionToInvestigate regionToInvestigate = *it;
        const uint32_t threatBloodAssociationIndex    = static_cast<uint32_t>(regionToInvestigate.m_threatKind);

        // Get handle to dismissal/promotion threat container.
        const ThreatFinder::KindOfThreats * pThreatChanging{};
        if(isOpponentMove)
        {
            pThreatChanging = &ThreatsBloodRelation::DISMISSAL[threatBloodAssociationIndex][0];
        }
        else
        {
            pThreatChanging = &ThreatsBloodRelation::PROMOTION[threatBloodAssociationIndex][0];
        }

        for(; *pThreatChanging != ThreatFinder::THREAT_NONE; pThreatChanging++)
        {
            const uint32_t threatIndex = static_cast<uint32_t>(*pThreatChanging);
            const bool isFound         = Score::m_ThreatScore[threatIndex].m_pThreat->findThreatPattern(
                    regionToInvestigate.m_xy, regionToInvestigate.m_trend, m_myPlayer);

            if(isFound)
            {
                ThreatFinder::ThreatLocation threatLocation;

                Score::m_ThreatScore[threatIndex].m_pThreat->getThreatFields(threatLocation);
                SpottedThreats sp{threatLocation, static_cast<ThreatFinder::KindOfThreats>(threatIndex), multiplier};
                retVal.push_back(sp);

                // Mark that, on this direction threat was found.
                trendMark |= 1 << regionToInvestigate.m_trend;
                break;
            }
        }
    }

    // If it was my move, besides previous stuff, run all Threat2CaseX (see ThreatsBloodRelation::TWO_LIST) because the
    // new move might form a new threat. Here is a place where each a new threat is born.
    if(!isOpponentMove)
    {
        for(uint32_t i = 0; i < ThreatsBloodRelation::TWO_LIST_SIZE; ++i)
        {
            const uint32_t threatIndex = static_cast<uint32_t>(ThreatsBloodRelation::TWO_LIST[i]);
            ThreatFinder::ThreatLocation threatLocation;

            // Check if previously on specified trend any threat was found. If so, do not run it here again on the same
            // trend.
            const bool isHorizontalRun = ((trendMark & (1 << ThreatFinder::HORIZONTAL)) == 0);
            const bool isVerticalRun   = ((trendMark & (1 << ThreatFinder::VERTICAL)) == 0);
            const bool isRisingRun     = ((trendMark & (1 << ThreatFinder::RISING)) == 0);
            const bool isFallingRun    = ((trendMark & (1 << ThreatFinder::FALLING)) == 0);

            bool isFoundHorizontal = false;
            if(isHorizontalRun)
            {
                isFoundHorizontal = Score::m_ThreatScore[threatIndex].m_pThreat->findThreatPattern(
                    xy, ThreatFinder::HORIZONTAL, m_myPlayer);

                if(isFoundHorizontal)
                {
                    Score::m_ThreatScore[threatIndex].m_pThreat->getThreatFields(threatLocation);
                    SpottedThreats sp{threatLocation, static_cast<ThreatFinder::KindOfThreats>(threatIndex), multiplier};
                    retVal.push_back(sp);

                    // Mark that, on this direction threat was found.
                    trendMark |= 1 << ThreatFinder::HORIZONTAL;
                }
            }

            bool isFoundVertical = false;
            if(isVerticalRun)
            {
                isFoundVertical = Score::m_ThreatScore[threatIndex].m_pThreat->findThreatPattern(
                    xy, ThreatFinder::VERTICAL, m_myPlayer);

                if(isFoundVertical)
                {
                    Score::m_ThreatScore[threatIndex].m_pThreat->getThreatFields(threatLocation);
                    SpottedThreats sp{threatLocation, static_cast<ThreatFinder::KindOfThreats>(threatIndex), multiplier};
                    retVal.push_back(sp);

                    // Mark that, on this direction threat was found.
                    trendMark |= 1 << ThreatFinder::VERTICAL;
                }
            }

            bool isFoundRising = false;
            if(isRisingRun)
            {
                isFoundRising = Score::m_ThreatScore[threatIndex].m_pThreat->findThreatPattern(
                    xy, ThreatFinder::RISING, m_myPlayer);

                if(isFoundRising)
                {
                    Score::m_ThreatScore[threatIndex].m_pThreat->getThreatFields(threatLocation);
                    SpottedThreats sp{threatLocation, static_cast<ThreatFinder::KindOfThreats>(threatIndex), multiplier};
                    retVal.push_back(sp);

                    // Mark that, on this direction threat was found.
                    trendMark |= 1 << ThreatFinder::RISING;
                }
            }

            bool isFoundFalling = false;
            if(isFallingRun)
            {
                isFoundFalling = Score::m_ThreatScore[threatIndex].m_pThreat->findThreatPattern(
                    xy, ThreatFinder::FALLING,m_myPlayer);

                if(isFoundFalling)
                {
                    Score::m_ThreatScore[threatIndex].m_pThreat->getThreatFields(threatLocation);
                    SpottedThreats sp{threatLocation, static_cast<ThreatFinder::KindOfThreats>(threatIndex), multiplier};
                    retVal.push_back(sp);

                    // Mark that, on this direction threat was found.
                    trendMark |= 1 << ThreatFinder::FALLING;
                }
            }
        }
    }
    resetInstance();
    return retVal;
}

void Spotter::setPlayerPerspective(const IBoard::Player playerPerspective)
{
    m_myPlayer = playerPerspective;
}

void Spotter::resetInstance()
{
    m_regionToInvestigate.clear();
}

