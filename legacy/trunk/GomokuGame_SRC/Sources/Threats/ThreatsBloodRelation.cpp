/////////////////////////////////////////////////////////////////////////////////////////
/// @file ThreatsBloodRelation.cpp
///
/// ThreatsBloodRelation class definition.
///
/// @par Full Description.
/// Preserves some relations between threats.
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

// SYSTEM INCLUDES
#include <assert.h>                  // For assert.
#include <algorithm>                 // For find algorithm.

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "ThreatFinder.hpp"  		 // For enum KindOfThreats.
#include "ThreatsBloodRelation.hpp"  // For ThreatsBloodRelation declaration.

// FORWARD REFERENCES
// <none>

void ThreatsBloodRelation::Init()
{
	static bool isFirstCall = true;

	if( true == isFirstCall )
	{
		isFirstCall = false;

		//---------------------------DISMISSALL LIST----------------------------------------------
		//THREAT_WINNER
		//ThreatsBloodRelation::DISMISSAL[ 0 ].m_Dependency.AddToTail( ThreatFinder::x );

		//THREAT_4_CASE_A
		ThreatsBloodRelation::DISMISSAL[ 1 ].m_Dependency.AddToTail( ThreatFinder::THREAT_4_CASE_B );

		//THREAT_4_CASE_AA
		ThreatsBloodRelation::DISMISSAL[ 2 ].m_Dependency.AddToTail( ThreatFinder::THREAT_4_CASE_B );
		ThreatsBloodRelation::DISMISSAL[ 2 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_B);
		ThreatsBloodRelation::DISMISSAL[ 2 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_B );

		//THREAT_4_CASE_B
		ThreatsBloodRelation::DISMISSAL[ 3 ].m_Dependency.AddToTail( ThreatFinder::THREAT_4_CASE_C );
		ThreatsBloodRelation::DISMISSAL[ 3 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_B );
		ThreatsBloodRelation::DISMISSAL[ 3 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_B );

		//THREAT_4_CASE_C
		//ThreatsBloodRelation::DISMISSAL[ 4 ].m_Dependency.AddToTail( ThreatFinder::x );

		//THREAT_3_CASE_A
		ThreatsBloodRelation::DISMISSAL[ 5 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_A );
		ThreatsBloodRelation::DISMISSAL[ 5 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_B );
		ThreatsBloodRelation::DISMISSAL[ 5 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_C );
		ThreatsBloodRelation::DISMISSAL[ 5 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_B );

		//THREAT_3_CASE_AA
		ThreatsBloodRelation::DISMISSAL[ 6 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_B );
		ThreatsBloodRelation::DISMISSAL[ 6 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_A );
		ThreatsBloodRelation::DISMISSAL[ 6 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_B );

		//THREAT_3_CASE_B
		ThreatsBloodRelation::DISMISSAL[ 7 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_C );
		ThreatsBloodRelation::DISMISSAL[ 7 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_A );
		ThreatsBloodRelation::DISMISSAL[ 7 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_B );

		//THREAT_3_CASE_C
		//ThreatsBloodRelation::DISMISSAL[ 8 ].m_Dependency.AddToTail( ThreatFinder::x );

		//THREAT_2_CASE_A
		ThreatsBloodRelation::DISMISSAL[ 9 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_A );
		ThreatsBloodRelation::DISMISSAL[ 9 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_B );
		ThreatsBloodRelation::DISMISSAL[ 9 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_C );

		//THREAT_2_CASE_AA
		ThreatsBloodRelation::DISMISSAL[ 10 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_B );

		//THREAT_2_CASE_B
		ThreatsBloodRelation::DISMISSAL[ 11 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_C );

		//THREAT_2_CASE_C
		//ThreatsBloodRelation::DISMISSAL[ 12 ].m_Dependency.AddToTail( ThreatFinder::x );

		//---------------------------PROMOTION LIST----------------------------------------------
		//THREAT_WINNER
		//ThreatsBloodRelation::PROMOTION[ 0 ].m_Dependency.AddToTail( ThreatFinder::x );

		//THREAT_4_CASE_A
		ThreatsBloodRelation::PROMOTION[ 1 ].m_Dependency.AddToTail( ThreatFinder::THREAT_WINNER );

		//THREAT_4_CASE_AA
		ThreatsBloodRelation::PROMOTION[ 2 ].m_Dependency.AddToTail( ThreatFinder::THREAT_WINNER );

		//THREAT_4_CASE_B
		ThreatsBloodRelation::PROMOTION[ 3 ].m_Dependency.AddToTail( ThreatFinder::THREAT_WINNER );

		//THREAT_4_CASE_C
		ThreatsBloodRelation::PROMOTION[ 4 ].m_Dependency.AddToTail( ThreatFinder::THREAT_WINNER );

		//THREAT_3_CASE_A
		ThreatsBloodRelation::PROMOTION[ 5 ].m_Dependency.AddToTail( ThreatFinder::THREAT_4_CASE_A );
		ThreatsBloodRelation::PROMOTION[ 5 ].m_Dependency.AddToTail( ThreatFinder::THREAT_4_CASE_AA );
		ThreatsBloodRelation::PROMOTION[ 5 ].m_Dependency.AddToTail( ThreatFinder::THREAT_4_CASE_B );
		ThreatsBloodRelation::PROMOTION[ 5 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_A );

		//THREAT_3_CASE_AA
		ThreatsBloodRelation::PROMOTION[ 6 ].m_Dependency.AddToTail( ThreatFinder::THREAT_4_CASE_AA );
		ThreatsBloodRelation::PROMOTION[ 6 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_A );
		ThreatsBloodRelation::PROMOTION[ 6 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_A );

		//THREAT_3_CASE_B
		ThreatsBloodRelation::PROMOTION[ 7 ].m_Dependency.AddToTail( ThreatFinder::THREAT_4_CASE_B );
		ThreatsBloodRelation::PROMOTION[ 7 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_A );

		//THREAT_3_CASE_C
		ThreatsBloodRelation::PROMOTION[ 8 ].m_Dependency.AddToTail( ThreatFinder::THREAT_4_CASE_C );

		//THREAT_2_CASE_A
		ThreatsBloodRelation::PROMOTION[ 9 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_A );
		ThreatsBloodRelation::PROMOTION[ 9 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_AA );
		ThreatsBloodRelation::PROMOTION[ 9 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_B );
		ThreatsBloodRelation::PROMOTION[ 9 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_A );

		//THREAT_2_CASE_AA
		ThreatsBloodRelation::PROMOTION[ 10 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_AA );
		ThreatsBloodRelation::PROMOTION[ 10 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_A );
		ThreatsBloodRelation::PROMOTION[ 10 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_B );

		//THREAT_2_CASE_B
		ThreatsBloodRelation::PROMOTION[ 11 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_B );
		ThreatsBloodRelation::PROMOTION[ 11 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_C );
		ThreatsBloodRelation::PROMOTION[ 11 ].m_Dependency.AddToTail( ThreatFinder::THREAT_2_CASE_A );

		//THREAT_2_CASE_C
		ThreatsBloodRelation::PROMOTION[ 12 ].m_Dependency.AddToTail( ThreatFinder::THREAT_3_CASE_C );
	}
}

bool ThreatsBloodRelation::IsOnFourList( const ThreatFinder::KindOfThreats kindOfThreat )
{
	bool retVal = false;

	for( uint32_t i = 0; i < ThreatsBloodRelation::FOUR_LIST_SIZE; ++i )
	{
		if ( kindOfThreat == ThreatsBloodRelation::FOUR_LIST[ i ] )
		{
			retVal = true;
			break;
		}
	}

	return retVal;
}

bool ThreatsBloodRelation::IsOnThreeList( const ThreatFinder::KindOfThreats kindOfThreat )
{
	bool retVal = false;

	for( uint32_t i = 0; i < ThreatsBloodRelation::THREE_LIST_SIZE; ++i )
	{
		if ( kindOfThreat == ThreatsBloodRelation::THREE_LIST[ i ] )
		{
			retVal = true;
			break;
		}
	}

	return retVal;
}

bool ThreatsBloodRelation::IsOnTwoList( const ThreatFinder::KindOfThreats kindOfThreat )
{
	bool retVal = false;

	for( uint32_t i = 0; i < ThreatsBloodRelation::TWO_LIST_SIZE; ++i )
	{
		if ( kindOfThreat == ThreatsBloodRelation::TWO_LIST[ i ] )
		{
			retVal = true;
			break;
		}
	}

	return retVal;
}

bool ThreatsBloodRelation::IsOnJokerList( const ThreatFinder::KindOfThreats kindOfThreat )
{
	bool retVal = false;

	for( uint32_t i = 0; i < ThreatsBloodRelation::JOKER_LIST_SIZE; ++i )
	{
		if ( kindOfThreat == ThreatsBloodRelation::JOKER_LIST[ i ] )
		{
			retVal = true;
			break;
		}
	}

	return retVal;
}

bool ThreatsBloodRelation::IsOnAceList( const ThreatFinder::KindOfThreats kindOfThreat )
{
	bool retVal = false;

	for( uint32_t i = 0; i < ThreatsBloodRelation::ACE_LIST_SIZE; ++i )
	{
		if ( kindOfThreat == ThreatsBloodRelation::ACE_LIST[ i ] )
		{
			retVal = true;
			break;
		}
	}

	return retVal;
}

bool ThreatsBloodRelation::IsOnManyGapsList( const ThreatFinder::KindOfThreats kindOfThreat )
{
	bool retVal = false;

	for( uint32_t i = 0; i < ThreatsBloodRelation::MANY_GAPS_SIZE; ++i )
	{
		if ( kindOfThreat == ThreatsBloodRelation::MANY_GAPS[ i ] )
		{
			retVal = true;
			break;
		}
	}

	return retVal;
}

bool ThreatsBloodRelation::IsOnExtendedNeighborhoodList( const ThreatFinder::KindOfThreats kindOfThreat )
{
	bool retVal = false;

	for( uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i )
	{
		if ( kindOfThreat == ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[ i ] )
		{
			retVal = true;
			break;
		}
	}

	return retVal;
}

// Four threat group.
const ThreatFinder::KindOfThreats ThreatsBloodRelation::FOUR_LIST[] = {   ThreatFinder::THREAT_4_CASE_A,
																		  ThreatFinder::THREAT_4_CASE_AA,
																		  ThreatFinder::THREAT_4_CASE_B,
																		  ThreatFinder::THREAT_4_CASE_C
																	  };
// Three threat group.
const ThreatFinder::KindOfThreats ThreatsBloodRelation::THREE_LIST[] = {   ThreatFinder::THREAT_3_CASE_A,
																		   ThreatFinder::THREAT_3_CASE_AA,
																		   ThreatFinder::THREAT_3_CASE_B,
																		   ThreatFinder::THREAT_3_CASE_C
																	   };
// Two threat group.
const ThreatFinder::KindOfThreats ThreatsBloodRelation::TWO_LIST[] = {   ThreatFinder::THREAT_2_CASE_A,
																		 ThreatFinder::THREAT_2_CASE_AA,
																		 ThreatFinder::THREAT_2_CASE_B,
																		 ThreatFinder::THREAT_2_CASE_C
																	 };
// Joker threats list.
const ThreatFinder::KindOfThreats ThreatsBloodRelation::JOKER_LIST[] = {   ThreatFinder::THREAT_4_CASE_A,
                                                                           ThreatFinder::THREAT_4_CASE_B,
                                                                           ThreatFinder::THREAT_4_CASE_C
                                                                       };
// Ace threat list.
const ThreatFinder::KindOfThreats ThreatsBloodRelation::ACE_LIST[] = {   ThreatFinder::THREAT_4_CASE_A,
                                                                         ThreatFinder::THREAT_4_CASE_C
                                                                     };
// Group that have more than one consecutive gaps.
const ThreatFinder::KindOfThreats ThreatsBloodRelation::MANY_GAPS[] = {   ThreatFinder::THREAT_3_CASE_A,
                                                                          ThreatFinder::THREAT_3_CASE_B,
																		  ThreatFinder::THREAT_2_CASE_A
                                                                      };
// Group that needs to have extended neighborhoods.
const ThreatFinder::KindOfThreats ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[] = {
																				      ThreatFinder::THREAT_3_CASE_A,
																					  ThreatFinder::THREAT_3_CASE_B,
																					  ThreatFinder::THREAT_3_CASE_C,
																					  ThreatFinder::THREAT_2_CASE_A,
																    			  };

// Dismissal Group.
ThreatsBloodRelation::ThreatChanging ThreatsBloodRelation::DISMISSAL[] =
{
	// here, only initialize threat but not its dependencies.
	// Keep the order as it is for Score::m_ThreatScore.
	{ ThreatChanging( ThreatFinder::THREAT_WINNER ) },
	{ ThreatChanging( ThreatFinder::THREAT_4_CASE_A ) },
	{ ThreatChanging( ThreatFinder::THREAT_4_CASE_AA ) },
	{ ThreatChanging( ThreatFinder::THREAT_4_CASE_B ) },
	{ ThreatChanging( ThreatFinder::THREAT_4_CASE_C ) },
	{ ThreatChanging( ThreatFinder::THREAT_3_CASE_A ) },
	{ ThreatChanging( ThreatFinder::THREAT_3_CASE_AA ) },
	{ ThreatChanging( ThreatFinder::THREAT_3_CASE_B ) },
	{ ThreatChanging( ThreatFinder::THREAT_3_CASE_C ) },
	{ ThreatChanging( ThreatFinder::THREAT_2_CASE_A ) },
	{ ThreatChanging( ThreatFinder::THREAT_2_CASE_AA ) },
	{ ThreatChanging( ThreatFinder::THREAT_2_CASE_B ) },
    { ThreatChanging( ThreatFinder::THREAT_2_CASE_C ) },
};

// Promotion Group.
ThreatsBloodRelation::ThreatChanging ThreatsBloodRelation::PROMOTION[] =
{
    // here, only initialize threat but not its dependencies.
	// Keep the order as it is for Score::m_ThreatScore.
    { ThreatChanging( ThreatFinder::THREAT_WINNER ) },
    { ThreatChanging( ThreatFinder::THREAT_4_CASE_A ) },
    { ThreatChanging( ThreatFinder::THREAT_4_CASE_AA ) },
    { ThreatChanging( ThreatFinder::THREAT_4_CASE_B ) },
    { ThreatChanging( ThreatFinder::THREAT_4_CASE_C ) },
    { ThreatChanging( ThreatFinder::THREAT_3_CASE_A ) },
    { ThreatChanging( ThreatFinder::THREAT_3_CASE_AA ) },
    { ThreatChanging( ThreatFinder::THREAT_3_CASE_B ) },
    { ThreatChanging( ThreatFinder::THREAT_3_CASE_C ) },
    { ThreatChanging( ThreatFinder::THREAT_2_CASE_A ) },
    { ThreatChanging( ThreatFinder::THREAT_2_CASE_AA ) },
	{ ThreatChanging( ThreatFinder::THREAT_2_CASE_B ) },
    { ThreatChanging( ThreatFinder::THREAT_2_CASE_C ) },
};

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