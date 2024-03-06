#include "Threats/ThreatFinder.h"
#include "Threats/ThreatsBloodRelation.h"

bool ThreatsBloodRelation::IsOnFourList(const ThreatFinder::KindOfThreats kindOfThreat)
{
    bool retVal = false;

    for(uint32_t i = 0; i < ThreatsBloodRelation::FOUR_LIST_SIZE; ++i)
    {
        if(kindOfThreat == ThreatsBloodRelation::FOUR_LIST[i])
        {
            retVal = true;
            break;
        }
    }

    return retVal;
}

bool ThreatsBloodRelation::IsOnThreeList(const ThreatFinder::KindOfThreats kindOfThreat)
{
    bool retVal = false;

    for(uint32_t i = 0; i < ThreatsBloodRelation::THREE_LIST_SIZE; ++i)
    {
        if(kindOfThreat == ThreatsBloodRelation::THREE_LIST[i])
        {
            retVal = true;
            break;
        }
    }

    return retVal;
}

bool ThreatsBloodRelation::IsOnTwoList(const ThreatFinder::KindOfThreats kindOfThreat)
{
    bool retVal = false;

    for(uint32_t i = 0; i < ThreatsBloodRelation::TWO_LIST_SIZE; ++i)
    {
        if(kindOfThreat == ThreatsBloodRelation::TWO_LIST[i])
        {
            retVal = true;
            break;
        }
    }

    return retVal;
}

bool ThreatsBloodRelation::IsOnJokerList(const ThreatFinder::KindOfThreats kindOfThreat)
{
    bool retVal = false;

    for(uint32_t i = 0; i < ThreatsBloodRelation::JOKER_LIST_SIZE; ++i)
    {
        if(kindOfThreat == ThreatsBloodRelation::JOKER_LIST[i])
        {
            retVal = true;
            break;
        }
    }

    return retVal;
}

bool ThreatsBloodRelation::IsOnAceList(const ThreatFinder::KindOfThreats kindOfThreat)
{
    bool retVal = false;

    for(uint32_t i = 0; i < ThreatsBloodRelation::ACE_LIST_SIZE; ++i)
    {
        if(kindOfThreat == ThreatsBloodRelation::ACE_LIST[i])
        {
            retVal = true;
            break;
        }
    }

    return retVal;
}

bool ThreatsBloodRelation::IsOnManyGapsList(const ThreatFinder::KindOfThreats kindOfThreat)
{
    bool retVal = false;

    for(uint32_t i = 0; i < ThreatsBloodRelation::MANY_GAPS_SIZE; ++i)
    {
        if(kindOfThreat == ThreatsBloodRelation::MANY_GAPS[i])
        {
            retVal = true;
            break;
        }
    }

    return retVal;
}

bool ThreatsBloodRelation::IsOnExtendedNeighborhoodList(const ThreatFinder::KindOfThreats kindOfThreat)
{
    bool retVal = false;

    for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
    {
        if(kindOfThreat == ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i])
        {
            retVal = true;
            break;
        }
    }

    return retVal;
}
