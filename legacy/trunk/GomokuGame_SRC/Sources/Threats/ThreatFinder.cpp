/////////////////////////////////////////////////////////////////////////////////////////
/// @file ThreatFinder.hpp
///
/// ThreatFinder class definition.
///
/// @par Full Description.
/// ThreatFinder finds pawns' pattern on gomoku board.
/// See article: 'Go-Moku and Threat-Space Search' by L.V. Allis & H.J. van den Herik
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 01-Feb-2016 Initial revision.
/// - zhalat 03-Dec-2016 Fix bug: Don't check outside of board exception when all pattern element were checked.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <queue>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Board.hpp"         // PositionField, PositionXY, Board's enums.
#include "ThreatFinder.hpp"  // ThreatFinder class declaration.
#include <ctime>        	 // For time to set seed for random.

// FORWARD REFERENCES
/// Straight and reverse conversion trend to direction.
const std::unordered_map<ThreatFinder::Trend, Board::Direction, std::hash<int>> ThreatFinder::Trend2DirectionStraight = {
	{ ThreatFinder::VERTICAL,   Board::DOWN },
	{ ThreatFinder::HORIZONTAL, Board::RIGHT },
	{ ThreatFinder::RISING,     Board::DOWN_LEFT },
	{ ThreatFinder::FALLING,    Board::DOWN_RIGHT }
};
const std::unordered_map<ThreatFinder::Trend, Board::Direction, std::hash<int>> ThreatFinder::Trend2DirectionReverse = {
	{ ThreatFinder::VERTICAL,   Board::UP },
	{ ThreatFinder::HORIZONTAL, Board::LEFT },
	{ ThreatFinder::RISING,     Board::UP_RIGHT },
	{ ThreatFinder::FALLING,    Board::UP_LEFT }
};

//const std::unordered_map<ThreatFinder::Trend, Board::Direction> ThreatFinder::Trend2DirectionReverse = {};
const Board::PositionXY ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD = Board::PositionXY( Board::PositionXY::INVALID_FIELD, Board::PositionXY::INVALID_FIELD );
const Board::PositionXY ThreatFinder::ThreatLocation::XY_BEGIN_OF_BOARD = Board::PositionXY( 0, 0 );

/// Browse neighborhood for threat.
bool ThreatFinder::FindThreatPattern( const Board::PositionXY& initialPosition, const Trend trend, const Board::Player playerPerspective )
{
    bool retVal = false;

    // Board has to be provided first.
    assert( NULL != m_pGomokuBoard );

    // Ensure that initial field is on board.
    assert( m_pGomokuBoard->IsOnBoard( initialPosition ) );

    // Ensure that initialPosition is not empty.
    assert( Board::PLAYER_EMPTY != m_pGomokuBoard->GetMove( initialPosition ) );

    const Board::Player opponentPlayer = ( Board::PLAYER_A == playerPerspective ) ? Board::PLAYER_B : Board::PLAYER_A;

    // Reset previous result.
	m_ThreatLocation.ClearAll();
    PrepareSelfForNewSearch();

    // Point of view means which position in the pattern we are.
    // We can consider pattern at its beginning but also in the middle:
    // OX.XXX
    // ^
    // point of view = 0, steps before reversion = 5
    //
    // OX.XXX
    //     ^
    // point of view = 4, steps before reversion = 1
    //
    // Because we don't know which part of threat user has just created,
    // there is necessity go thru all points of view.

	// Go thru all points of view.
	for( uint32_t i = 0; i < m_PointsViewSize; ++i )
	{
		const uint32_t currentPointOfView = m_pPointsView[ i ];

		// Used for jumping thru board.
		Board::PositionXY currentPositionOnBoard = initialPosition;
		uint32_t currentThreat = 0;

		// Used for keeping how many steps should be done before the opposite direction will take place.
		const uint32_t stepsBeforeReversion = m_PatternLenght - currentPointOfView - 1;

		// Points if reversion took place. It is allowed only once.
		bool isReversion = false;

		// Exception counter. There is allowed only once consecutive exception occurrence.
		uint32_t exceptionCntr = 0;

		// If for 100% sure there is no threat.
		bool isHopeless = false;

		for( uint32_t j = 0; j < m_PatternLenght; ++j )
		{
			if ( 0 == exceptionCntr )
			{
				// Get actual pawn (from board).
				const Board::Player currentPawn = m_pGomokuBoard->GetMove( currentPositionOnBoard );

				currentThreat |= ( static_cast<uint32_t>( currentPawn ) << j );

				// Recognize '*' asterix - an empty place or opponent.
				const bool isEmptyOrRival = ( currentPawn != playerPerspective );

				if( isEmptyOrRival )
				{
					currentThreat |= ( static_cast<uint32_t>( Board::PLAYER_EMPTY_OR_ENEMY ) << j );
				}
			}

			// Find out a next location on board.

			// Check if reversion should take place. Each threat pattern variation might have different
			// number of steps before antithetical direction on trend line should take place.
			if ( j == stepsBeforeReversion )
			{
				isReversion = true;
				currentPositionOnBoard = initialPosition;
			}

			const bool isNewPositionOutOfBoard = !MakeStepOnTrend( isReversion, currentPositionOnBoard, trend );

			// Don't check out of board if all pattern particle has just been checked.
			const bool isEnd = ( (j + 1) == m_PatternLenght );
			if( isNewPositionOutOfBoard && !isEnd )
			{
				// This is an exception thats means move is out of board.
				++exceptionCntr;

				if( !( exceptionCntr <= MAX_ALLOVED_EXCEPTION ) )
				{
					isHopeless = true;
					break;
				}

				// If new position is out of board it general means that pattern was not found.
				// However we can treat board frame as opponent move. So put there just an opponent move and check.
				currentThreat |= ( static_cast<uint32_t>( opponentPlayer ) << ( j + 1 ) );
				currentThreat |= ( static_cast<uint32_t>( Board::PLAYER_EMPTY_OR_ENEMY ) << ( j + 1 ) );

				#warning "Make it better."
				if( isReversion )
				{
					j++;
				}
			}
			else
			{
				exceptionCntr = 0;
			}
		}

		// Examine the result.
		if( !isHopeless && CheckThreat( currentThreat, currentPointOfView, playerPerspective ) )
		{
		    // Indicate that pattern was found.
		    m_IsThreatPatternFound = true;

            // Get details.
            m_ThreatLocation.m_ThreatDetails.m_WhoIs = playerPerspective;
            GetThreatUpDetails( initialPosition, trend, m_ThreatLocation.m_ThreatDetails );
            m_ThreatLocation.m_Trend = trend;

			retVal = true;

			if( false == IsSearchForSimmetrics() )
			{
				break;
			}
		}
	}

	return retVal;
}

// Gets begin and end fields of threat.
void ThreatFinder::GetThreatFields( ThreatLocation& rThreatLocation ) const
{
    // Firstly any threat must be found.
    assert( true == m_IsThreatPatternFound );

    rThreatLocation = m_ThreatLocation;
}

/// Change hexCode as if was being seen from 0 point of view.
uint8_t ThreatFinder::StandarizePOV( const uint8_t hexCode, const uint8_t pointOfView, const uint8_t length ) const
{
	const uint8_t shiftN = length - pointOfView;
	const uint8_t mask = ( (uint8_t)1<<shiftN ) - 1;
	uint8_t retVal = hexCode;
	std::queue<uint8_t> lifo;

	for( uint8_t i = shiftN; i < length; ++i )
	{
		const uint8_t el = ( (uint8_t)1 << i ) & hexCode;
		lifo.push( el );
	}

	retVal &= mask;

	for( ; false == lifo.empty(); )
	{
		retVal = retVal << 1;
		const uint8_t el = lifo.front();
		lifo.pop();

		if( el )
		{
			retVal |= 0x1;
		}
	}

	return retVal;
}

/// Provide (x,y) threat's pieces(x,o,.,*) basing on normalized threat.
void ThreatFinder::GetPieces( const uint8_t normHexCode, const Board::PositionXY initialPositionNorm, const Board::Direction direction, Board::PositionXY pBuffer[], const uint32_t bufferSize ) const
{
	static const uint8_t mask = 0x01;
	static const uint8_t maxHexCodeBits = 8;

	uint8_t normHexCodeTmp = normHexCode;
	uint32_t index = 0;
	for( uint32_t i = 0; i < maxHexCodeBits; ++i )
	{
		const bool isPiece = ( normHexCodeTmp & mask );
		if( isPiece )
		{
			assert( index < bufferSize );
			Board::PositionXY initialPositionNormTmp = initialPositionNorm;
			GetGomokuBoard().GoDirection( initialPositionNormTmp, direction, i );
			pBuffer[ index++ ] = initialPositionNormTmp;
		}
		normHexCodeTmp = normHexCodeTmp >> 1;
	}
}

/// From currentXYPosition make one step on trend towards up/right/up_right if no reversion or
/// down/left/down_left if reversion should take place. Such a new position override currentXYPosition.
/// If new currentXYPosition would exceed board return false and old position is preserved.
bool ThreatFinder::MakeStepOnTrend( const bool isReversion, Board::PositionXY& currentXYPosition, const Trend trend ) const
{
    bool retVal = false;

    // Board have to be provided first.
    assert( NULL != m_pGomokuBoard );

    // Find out direction toward which we are going to crawl.
	const Board::Direction directionForward = Trend2DirectionStraight.at( trend );
	const Board::Direction directionBackward = Trend2DirectionReverse.at( trend );

    Board::Direction direction = Board::DIRECTION_NONE;

    if ( !isReversion )
    {
    	direction = directionForward;
    }
    else
    {
    	direction = directionBackward;
    }

    // Check if we can go one step further.
    if ( m_pGomokuBoard->CanIGo( currentXYPosition, direction ) )
    {
        // Go one step further.
        m_pGomokuBoard->GoDirection( currentXYPosition, direction );
        retVal = true;
    }
    else
    {
        retVal = false;
    }

    return retVal;
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
