/////////////////////////////////////////////////////////////////////////////////////////
/// @file Spotter.cpp
///
/// Search threats in provided region.
///
/// @par Full Description.
/// Search threats in provided region.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 06-Nov-2016 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>  // For assert.

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "ThreatsBloodRelation.hpp"  // For its initialization.
#include "Spotter.hpp"               // For declaration.
#include "Score.hpp"                 // For Score::m_ThreatScore
#include "BoardScore.hpp"            // For GetPlayer().

// FORWARD REFERENCES
// <none>

// Constructor.
Spotter::Spotter(BoardScore & rBoardScore) : m_rBoardScore(rBoardScore), m_RegionToInvestigate()
{
    assert(m_RegionToInvestigate.IsEmpty());
}

Spotter::~Spotter()
{}

void Spotter::AddToExecute(const RegionToInvestigate regionToInvestigate)
{
    m_RegionToInvestigate.AddToTail(regionToInvestigate);
}

void Spotter::Execute(const Board::PositionXY xy, const bool isOpponentMove, const uint32_t multiplier)
{
#warning \
    "Extract from this method. method 'ExecuteRegions()' and make it private. Execute() will run that metod and additionaly searches TWO_LIST threats."
    // Keeps in bit representation, direction where threats have been found.
    uint32_t trendMark = 0;

    // Go thru all threats marked to be executing their blood relation threats.
    IteratorIf<RegionToInvestigate> * const pIteratorIfToExecute = m_RegionToInvestigate.GetIterator();
    assert(pIteratorIfToExecute);

    for(; pIteratorIfToExecute->HasNext();)
    {
        const RegionToInvestigate regionToInvestigate = pIteratorIfToExecute->GetNext();
        const uint32_t threatBloodAssociationIndex    = static_cast<uint32_t>(regionToInvestigate.m_ThreatKind);

        // Get handle to dismissal/promotion threat container.
        const ThreatFinder::KindOfThreats * pThreatChanging{};
        if(isOpponentMove)
        {
            // Opponent's move can mitigate my threats.
            pThreatChanging = &ThreatsBloodRelation::DISMISSAL[threatBloodAssociationIndex][0];
        }
        else
        {
            // My move can boost my threats.
            pThreatChanging = &ThreatsBloodRelation::PROMOTION[threatBloodAssociationIndex][0];
        }

        for(; *pThreatChanging != ThreatFinder::THREAT_NONE; pThreatChanging++)
        {
            const uint32_t threatIndex = static_cast<uint32_t>(*pThreatChanging);
            const bool isFound         = Score::m_ThreatScore[threatIndex].m_pThreat->FindThreatPattern(
                regionToInvestigate.m_Xy, regionToInvestigate.m_Trend, m_rBoardScore.GetPlayer());

            if(isFound)
            {
                ThreatFinder::ThreatLocation threatLocation;

                Score::m_ThreatScore[threatIndex].m_pThreat->GetThreatFields(threatLocation);
                m_rBoardScore.AddThreats(threatLocation, threatIndex, multiplier);

                // Mark that, on this direction threat was found.
                trendMark |= 1 << regionToInvestigate.m_Trend;
                break;
            }
        }
    }

    // Searching region done.
    pIteratorIfToExecute->SetToBase();
    ResetInstance();

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
                isFoundHorizontal = Score::m_ThreatScore[threatIndex].m_pThreat->FindThreatPattern(
                    xy, ThreatFinder::HORIZONTAL, m_rBoardScore.GetPlayer());

                if(isFoundHorizontal)
                {
                    Score::m_ThreatScore[threatIndex].m_pThreat->GetThreatFields(threatLocation);
                    m_rBoardScore.AddThreats(threatLocation, threatIndex, multiplier);

                    // Mark that, on this direction threat was found.
                    trendMark |= 1 << ThreatFinder::HORIZONTAL;
                }
            }

            bool isFoundVertical = false;
            if(isVerticalRun)
            {
                isFoundVertical = Score::m_ThreatScore[threatIndex].m_pThreat->FindThreatPattern(
                    xy, ThreatFinder::VERTICAL, m_rBoardScore.GetPlayer());

                if(isFoundVertical)
                {
                    Score::m_ThreatScore[threatIndex].m_pThreat->GetThreatFields(threatLocation);
                    m_rBoardScore.AddThreats(threatLocation, threatIndex, multiplier);

                    // Mark that, on this direction threat was found.
                    trendMark |= 1 << ThreatFinder::VERTICAL;
                }
            }

            bool isFoundRising = false;
            if(isRisingRun)
            {
                isFoundRising = Score::m_ThreatScore[threatIndex].m_pThreat->FindThreatPattern(
                    xy, ThreatFinder::RISING, m_rBoardScore.GetPlayer());

                if(isFoundRising)
                {
                    Score::m_ThreatScore[threatIndex].m_pThreat->GetThreatFields(threatLocation);
                    m_rBoardScore.AddThreats(threatLocation, threatIndex, multiplier);

                    // Mark that, on this direction threat was found.
                    trendMark |= 1 << ThreatFinder::RISING;
                }
            }

            bool isFoundFalling = false;
            if(isFallingRun)
            {
                isFoundFalling = Score::m_ThreatScore[threatIndex].m_pThreat->FindThreatPattern(
                    xy, ThreatFinder::FALLING, m_rBoardScore.GetPlayer());

                if(isFoundFalling)
                {
                    Score::m_ThreatScore[threatIndex].m_pThreat->GetThreatFields(threatLocation);
                    m_rBoardScore.AddThreats(threatLocation, threatIndex, multiplier);

                    // Mark that, on this direction threat was found.
                    trendMark |= 1 << ThreatFinder::FALLING;
                }
            }
        }
    }
}

/// Revert instance to initial state.
void Spotter::ResetInstance()
{
    for(; !m_RegionToInvestigate.IsEmpty();)
    {
        m_RegionToInvestigate.RemoveFromTail();
    }

    assert(m_RegionToInvestigate.IsEmpty());
}

/***************************************************************************
 *   Copyright (C) 2018 by Zbigniew Halat                                  *
 *   zby.halat@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/
