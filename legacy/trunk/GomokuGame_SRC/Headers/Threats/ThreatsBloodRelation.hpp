/////////////////////////////////////////////////////////////////////////////////////////
/// @file ThreatsBloodRelation.hpp
///
/// ThreatsBloodRelation class declaration.
///
/// @par Full Description.
/// Preserves some relations between threats.
/// Examplary: Threat4CaseA, Threat4CaseB, Threat4CaseC are deadly threats called joker threat.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 31-Jul-2016 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined ( THREAT_BLOOD_RELATION_A_HPP_ )
#define THREAT_BLOOD_RELATION_A_HPP_

// SYSTEM INCLUDES
#include <assert.h>             // For assert.

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "SingleList.hpp"		// For SingleList definition.
#include "ThreatFinder.hpp"

// FORWARD REFERENCES
// <none>

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: ThreatsBloodRelation.
///
/// ThreatsBloodRelation class declaration.
///
/// @par Full Description.
/// Define some relations between each threat.
///////////////////////////////////////////////////////////////////////////////////////////
class ThreatsBloodRelation
{
public:

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatsBloodRelation::Init
    //
    /// Initialize the content.
    ///
    /// @par Full Description
    /// Initialize the content.
    ///////////////////////////////////////////////////////////////////////
	static void Init();

    static bool IsOnFourList( const ThreatFinder::KindOfThreats );
    static bool IsOnThreeList( const ThreatFinder::KindOfThreats );
    static bool IsOnTwoList( const ThreatFinder::KindOfThreats );
    static bool IsOnJokerList( const ThreatFinder::KindOfThreats );
    static bool IsOnAceList( const ThreatFinder::KindOfThreats );
    static bool IsOnManyGapsList( const ThreatFinder::KindOfThreats );
    static bool IsOnExtendedNeighborhoodList( const ThreatFinder::KindOfThreats kindOfThreat );

	struct ThreatChanging
	{
		ThreatFinder::KindOfThreats m_KindOfThreat;
		SingleList<ThreatFinder::KindOfThreats> m_Dependency;

		// Default constructor.
		ThreatChanging()
		 : m_KindOfThreat( ThreatFinder::THREAT_NONE )
		 , m_Dependency()
		{}

		// Constructor.
		ThreatChanging( ThreatFinder::KindOfThreats kindOfThreat )
		 : m_KindOfThreat( kindOfThreat )
		 , m_Dependency()
		{}

		// Copy constructor.
		ThreatChanging( const ThreatChanging& )
		{
#warning "This constructor shall be removed: ThreatChanging( const ThreatChanging& )=delete."
#warning "Copy constructor required by compiler to be able init DISMISSAL/PROMOTION. This is gcc bug: see GCC Bugzilla – Bug 63707"

			// Be sure nobody use it.
			assert( false );
		}
	};

	// Groups related to number of pawns in a row.
    static const ThreatFinder::KindOfThreats FOUR_LIST[];
    static const ThreatFinder::KindOfThreats THREE_LIST[];
    static const ThreatFinder::KindOfThreats TWO_LIST[];

    // Groups related to threat danger.
    static const ThreatFinder::KindOfThreats JOKER_LIST[];
    static const ThreatFinder::KindOfThreats ACE_LIST[];

    // Groups that have more than one consecutive gaps.
    static const ThreatFinder::KindOfThreats MANY_GAPS[];

    // Groups that need to have extended neighborhoods.
    static const ThreatFinder::KindOfThreats EXTENDED_NEIGHBORHOOD[];

    // Dismissal Group.
    static ThreatChanging DISMISSAL[];

    // Promotion Group.
    static ThreatChanging PROMOTION[];

    static const uint32_t FOUR_LIST_SIZE  = 4;
    static const uint32_t THREE_LIST_SIZE = 4;
    static const uint32_t TWO_LIST_SIZE   = 4;
    static const uint32_t JOKER_LIST_SIZE = 3;
    static const uint32_t ACE_LIST_SIZE   = 2;
    static const uint32_t MANY_GAPS_SIZE  = 3;
    static const uint32_t EXTENDED_NEIGHBORHOOD_SIZE = 4;
    static const uint32_t DISMISSAL_SIZE  = 12;
    static const uint32_t PROMOTION_SIZE  = 12;

private:

};
#endif /* THREAT_BLOOD_RELATION_A_HPP_ */

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
