/////////////////////////////////////////////////////////////////////////////////////////
/// @file OpenBook.cpp
///
/// Opening book.
///
/// @par Full Description.
/// Guideline for up to three first move.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 28-Dec-2016 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>         // For assert.
#include <cstdlib>     		// For srand().

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "OpenBook.hpp"		// For declaration.
#include "Board.hpp"		// For Board interface.

// FORWARD REFERENCES
// <none>

#define NUMELEM( x )    ( sizeof( x )/sizeof( x[ 0 ] ) )

// Point beyond the board. Useful for initialization.
const Board::PositionXY XY_OUT_OF_BOARD = Board::PositionXY( Board::PositionXY::INVALID_FIELD, Board::PositionXY::INVALID_FIELD );

// Directions to find direct or indirect kind of opening game.
const Board::Direction OpenBook::DIRECT_PATH[] 	 = { Board::UP, Board::RIGHT, Board::DOWN, Board::LEFT };
const Board::Direction OpenBook::INDIRECT_PATH[] = { Board::UP_RIGHT, Board::DOWN_RIGHT, Board::DOWN_LEFT, Board::UP_LEFT };
const uint32_t OpenBook::DIRECT_PATH_SIZE 		 = NUMELEM( DIRECT_PATH );
const uint32_t OpenBook::INDIRECT_PATH_SIZE 	 = NUMELEM( INDIRECT_PATH );

const OpenBook::Openings OpenBook::DIRECT_OPEN[] = {
	{ Board::UP, OpenBook::m_CrawlingChainUp },
	{ Board::RIGHT, OpenBook::m_CrawlingChainRight },
	{ Board::DOWN, OpenBook::m_CrawlingChainDown },
	{ Board::LEFT, OpenBook::m_CrawlingChainLeft }
};
const uint32_t OpenBook::DIRECT_OPEN_SIZE = NUMELEM( OpenBook::DIRECT_OPEN );

const OpenBook::Openings OpenBook::INDIRECT_OPEN[] = {
	{ Board::UP_RIGHT, OpenBook::m_CrawlingChainUpRight },
	{ Board::DOWN_RIGHT, OpenBook::m_CrawlingChainDownRight },
	{ Board::DOWN_LEFT, OpenBook::m_CrawlingChainDownLeft },
	{ Board::UP_LEFT, OpenBook::m_CrawlingChainUpLeft }
};
const uint32_t OpenBook::INDIRECT_OPEN_SIZE = NUMELEM( OpenBook::INDIRECT_OPEN );

// Letters point best movements for 'direct open game'.
// Notice that this is only one from four cases (UP case).
//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//0 |. . . . . . . . . . . . . . .|
//1 |. . . . . . . . . . . . . . .|
//2 |. . . . . . . . . . . . . . .|
//3 |. . . . . . . . . . . . . . .|
//4 |. . . . . . A . . . . . . . .|
//5 |. . . . . B o C . . . . . . .|
//6 |. . . . D . x . E . . . . . .|
//7 |. . . . . . . . . . . . . . .|
//8 |. . . . . . F . . . . . . . .|
//9 |. . . . . . . . . . . . . . .|
OpenBook::CrawlingChain OpenBook::m_CrawlingChainUp[] = {
	{'A', {} },
	{'B', {} },
	{'C', {} },
	{'D', {} },
	{'E', {} },
	{'F', {} }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainRight[] = {
	{'A', {} },
	{'B', {} },
	{'C', {} },
	{'D', {} },
	{'E', {} },
	{'F', {} }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainDown[] = {
	{'A', {} },
	{'B', {} },
	{'C', {} },
	{'D', {} },
	{'E', {} },
	{'F', {} }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainLeft[] = {
	{'A', {} },
	{'B', {} },
	{'C', {} },
	{'D', {} },
	{'E', {} },
	{'F', {} }
};

const uint32_t OpenBook::CRAWLING_DIRECT_SIZE = NUMELEM( m_CrawlingChainUp );

// Letters point best movements for 'indirect open game'.
// Notice that this is only one from four cases (UP_RIGHT case).
//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//0 |. . . . . . . . . . . . . . .|
//1 |. . . . . . . . . . . . . . .|
//2 |. . . . . . . . . . . . . . .|
//3 |. . . . . . . . . . . . . . .|
//4 |. . . . . G H . . . . . . . .|
//5 |. . . . . I . o . . . . . . .|
//6 |. . . . . . x . J . . . . . .|
//7 |. . . . M . . K L . . . . . .|
//8 |. . . . . N . . . . . . . . .|
//9 |. . . . . . . . . . . . . . .|
OpenBook::CrawlingChain OpenBook::m_CrawlingChainUpRight[] = {
	{'G', {} },
	{'H', {} },
	{'I', {} },
	{'J', {} },
	{'M', {} },
	{'K', {} },
	{'L', {} },
	{'N', {} }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainDownRight[] = {
	{'G', {} },
	{'H', {} },
	{'I', {} },
	{'J', {} },
	{'M', {} },
	{'K', {} },
	{'L', {} },
	{'N', {} }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainDownLeft[] = {
	{'G', {} },
	{'H', {} },
	{'I', {} },
	{'J', {} },
	{'M', {} },
	{'K', {} },
	{'L', {} },
	{'N', {} }
};

OpenBook::CrawlingChain OpenBook::m_CrawlingChainUpLeft[] = {
	{'G', {} },
	{'H', {} },
	{'I', {} },
	{'J', {} },
	{'M', {} },
	{'K', {} },
	{'L', {} },
	{'N', {} }
};

const uint32_t OpenBook::CRAWLING_INDIRECT_SIZE = NUMELEM( m_CrawlingChainUpRight );

// Constructor.
void OpenBook::Init()
{
	m_CrawlingChainUp[0].m_CrawlingList.AddToTail( Crawling( Board::UP, 2 ) ); 				// A
	m_CrawlingChainUp[1].m_CrawlingList.AddToTail( Crawling( Board::UP_LEFT, 1 ) ); 		// B
	m_CrawlingChainUp[2].m_CrawlingList.AddToTail( Crawling( Board::UP_RIGHT, 1 ) );		// C
	m_CrawlingChainUp[3].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 2 ) ); 			// D
	m_CrawlingChainUp[4].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 2 ) ); 			// E
	m_CrawlingChainUp[5].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 2 ) ); 			// F

	m_CrawlingChainRight[0].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 2 ) ); 		// A
	m_CrawlingChainRight[1].m_CrawlingList.AddToTail( Crawling( Board::UP_RIGHT, 1 ) ); 	// B
	m_CrawlingChainRight[2].m_CrawlingList.AddToTail( Crawling( Board::DOWN_RIGHT, 1 ) ); 	// C
	m_CrawlingChainRight[3].m_CrawlingList.AddToTail( Crawling( Board::UP, 2 ) ); 			// D
	m_CrawlingChainRight[4].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 2 ) ); 		// E
	m_CrawlingChainRight[5].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 2 ) ); 		// F

	m_CrawlingChainDown[0].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 2 ) ); 			// A
	m_CrawlingChainDown[1].m_CrawlingList.AddToTail( Crawling( Board::DOWN_RIGHT, 1 ) ); 	// B
	m_CrawlingChainDown[2].m_CrawlingList.AddToTail( Crawling( Board::DOWN_LEFT, 1 ) ); 	// C
	m_CrawlingChainDown[3].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 2 ) ); 		// D
	m_CrawlingChainDown[4].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 2 ) ); 			// E
	m_CrawlingChainDown[5].m_CrawlingList.AddToTail( Crawling( Board::UP, 2 ) ); 			// F

	m_CrawlingChainLeft[0].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 2 ) ); 			// A
	m_CrawlingChainLeft[1].m_CrawlingList.AddToTail( Crawling( Board::DOWN_LEFT, 1 ) ); 	// B
	m_CrawlingChainLeft[2].m_CrawlingList.AddToTail( Crawling( Board::UP_LEFT, 1 ) ); 		// C
	m_CrawlingChainLeft[3].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 2 ) ); 			// D
	m_CrawlingChainLeft[4].m_CrawlingList.AddToTail( Crawling( Board::UP, 2 ) ); 			// E
	m_CrawlingChainLeft[5].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 2 ) ); 		// F

	m_CrawlingChainUpRight[0].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 1 ) ); 		// G
	m_CrawlingChainUpRight[0].m_CrawlingList.AddToTail( Crawling( Board::UP, 2 ) );
	m_CrawlingChainUpRight[1].m_CrawlingList.AddToTail( Crawling( Board::UP, 2 ) ); 		// H
	m_CrawlingChainUpRight[2].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 1 ) ); 		// I
	m_CrawlingChainUpRight[2].m_CrawlingList.AddToTail( Crawling( Board::UP, 1 ) );
	m_CrawlingChainUpRight[3].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 2 ) ); 		// J
	m_CrawlingChainUpRight[4].m_CrawlingList.AddToTail( Crawling( Board::DOWN_RIGHT, 1 ) );	// K
	m_CrawlingChainUpRight[5].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 2 ) ); 		// L
	m_CrawlingChainUpRight[5].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 1 ) );
	m_CrawlingChainUpRight[6].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 1 ) ); 		// M
	m_CrawlingChainUpRight[6].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 2 ) );
	m_CrawlingChainUpRight[7].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 2 ) ); 		// N
	m_CrawlingChainUpRight[7].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 1 ) );

	m_CrawlingChainDownRight[0].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 2 ) ); 		// G
	m_CrawlingChainDownRight[0].m_CrawlingList.AddToTail( Crawling( Board::UP, 1 ) );
	m_CrawlingChainDownRight[1].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 2 ) ); 		// H
	m_CrawlingChainDownRight[2].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 1 ) ); 		// I
	m_CrawlingChainDownRight[2].m_CrawlingList.AddToTail( Crawling( Board::UP, 1 ) );
	m_CrawlingChainDownRight[3].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 2 ) ); 		// J
	m_CrawlingChainDownRight[4].m_CrawlingList.AddToTail( Crawling( Board::DOWN_LEFT, 1 ) );	// K
	m_CrawlingChainDownRight[5].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 2 ) ); 		// L
	m_CrawlingChainDownRight[5].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 1 ) );
	m_CrawlingChainDownRight[6].m_CrawlingList.AddToTail( Crawling( Board::UP, 2 ) ); 			// M
	m_CrawlingChainDownRight[6].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 1 ) );
	m_CrawlingChainDownRight[7].m_CrawlingList.AddToTail( Crawling( Board::UP, 1 ) ); 			// N
	m_CrawlingChainDownRight[7].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 2 ) );

	m_CrawlingChainDownLeft[0].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 1 ) ); 		// G
	m_CrawlingChainDownLeft[0].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 2 ) );
	m_CrawlingChainDownLeft[1].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 2 ) ); 			// H
	m_CrawlingChainDownLeft[2].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 1 ) ); 		// I
	m_CrawlingChainDownLeft[2].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 1 ) );
	m_CrawlingChainDownLeft[3].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 2 ) ); 			// J
	m_CrawlingChainDownLeft[4].m_CrawlingList.AddToTail( Crawling( Board::UP_LEFT, 1 ) );		// K
	m_CrawlingChainDownLeft[5].m_CrawlingList.AddToTail( Crawling( Board::UP, 1 ) ); 			// L
	m_CrawlingChainDownLeft[5].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 2 ) );
	m_CrawlingChainDownLeft[6].m_CrawlingList.AddToTail( Crawling( Board::UP, 1 ) ); 			// M
	m_CrawlingChainDownLeft[6].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 2 ) );
	m_CrawlingChainDownLeft[7].m_CrawlingList.AddToTail( Crawling( Board::UP, 2 ) ); 			// N
	m_CrawlingChainDownLeft[7].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 1 ) );

	m_CrawlingChainUpLeft[0].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 2 ) ); 			// G
	m_CrawlingChainUpLeft[0].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 1 ) );
	m_CrawlingChainUpLeft[1].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 2 ) ); 			// H
	m_CrawlingChainUpLeft[2].m_CrawlingList.AddToTail( Crawling( Board::LEFT, 1 ) ); 			// I
	m_CrawlingChainUpLeft[2].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 1 ) );
	m_CrawlingChainUpLeft[3].m_CrawlingList.AddToTail( Crawling( Board::UP, 2 ) ); 				// J
	m_CrawlingChainUpLeft[4].m_CrawlingList.AddToTail( Crawling( Board::UP_RIGHT, 1 ) );		// K
	m_CrawlingChainUpLeft[5].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 1 ) ); 			// L
	m_CrawlingChainUpLeft[5].m_CrawlingList.AddToTail( Crawling( Board::UP, 2 ) );
	m_CrawlingChainUpLeft[6].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 2 ) ); 			// M
	m_CrawlingChainUpLeft[6].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 1 ) );
	m_CrawlingChainUpLeft[7].m_CrawlingList.AddToTail( Crawling( Board::RIGHT, 2 ) ); 			// N
	m_CrawlingChainUpLeft[7].m_CrawlingList.AddToTail( Crawling( Board::DOWN, 1 ) );
}

/// Provide best third move for white.
Board::PositionXY OpenBook::GetBestThirdWhiteMove( const Board& rBoard )
{
	static bool isInitPerformed = false;

	if( !isInitPerformed )
	{
		Init();
		isInitPerformed = true;
	}

	Board::PositionXY retVal = XY_OUT_OF_BOARD;

	// Get the first move.
	Board::PositionXY xyFirst;
	const bool status = rBoard.GetFirstMove( xyFirst );
	assert( status );

	// Checks kind of open game.
	const bool isDirectOpen = ( OpenBook::DIRECT == OpenGame( rBoard ) );
	const bool isInDirectOpen = ( OpenBook::INDIRECT == OpenGame( rBoard ) );

	if( isDirectOpen )
	{
		// Find out main direction.
		uint32_t index = DIRECT_PATH_SIZE;
		for( uint32_t i = 0; i < DIRECT_PATH_SIZE; ++i )
		{
			if( Board::NO_NEIGHBOR_FOUND != rBoard.NeighbourDistance( xyFirst, DIRECT_PATH[ i ], rBoard.GetMove( xyFirst ) ) )
			{
				index = i;
				break;
			}
		}
		assert( index < DIRECT_PATH_SIZE );

		const Board::Direction mainDirection = DIRECT_PATH[ index ];

		// Find chain associated with the main direction.
		IteratorIf<OpenBook::Crawling>* pIteratorIfToExecute = NULL;
		for( uint32_t i = 0; i < DIRECT_OPEN_SIZE; ++i )
		{
			if( mainDirection == DIRECT_OPEN[i].m_MainDirection )
			{
				// Draw lots to chose one of the open game letter: A,B,C,D,E,F. Don't matter which one.
				const uint32_t randomIndex = ( rand() % CRAWLING_DIRECT_SIZE );
				pIteratorIfToExecute = DIRECT_OPEN[ i ].m_pCrawlingChain[ randomIndex ].m_CrawlingList.GetIterator();
				break;
			}
		}

		assert( NULL != pIteratorIfToExecute );

		Board::PositionXY xyCrawling = xyFirst;

		// Find out the position on board associated with letter that has just been drawn.
		for( ; pIteratorIfToExecute->HasNext(); )
		{
			const OpenBook::Crawling crawling = pIteratorIfToExecute->GetNext();
			rBoard.GoDirection( xyCrawling, crawling.m_Direction, crawling.m_Shift );
			assert( rBoard.IsOnBoard( xyCrawling ) );
		}
		pIteratorIfToExecute->SetToBase();

		retVal = xyCrawling;
	}
	else if( isInDirectOpen )
	{
		// Find out main direction.
		uint32_t index = INDIRECT_PATH_SIZE;
		for( uint32_t i = 0; i < INDIRECT_PATH_SIZE; ++i )
		{
			if( Board::NO_NEIGHBOR_FOUND != rBoard.NeighbourDistance( xyFirst, INDIRECT_PATH[ i ], rBoard.GetMove( xyFirst ) ) )
			{
				index = i;
				break;
			}
		}
		assert( index < INDIRECT_PATH_SIZE );

		const Board::Direction mainDirection = INDIRECT_PATH[ index ];

		// Find chain associated with the main direction.
		IteratorIf<OpenBook::Crawling>* pIteratorIfToExecute = NULL;
		for( uint32_t i = 0; i < INDIRECT_OPEN_SIZE; ++i )
		{
			if( mainDirection == INDIRECT_OPEN[i].m_MainDirection )
			{
				// Draw lots to chose one of the open game letter: A,B,C,D,E,F. Don't matter which one.
				const uint32_t randomIndex = ( rand() % CRAWLING_INDIRECT_SIZE );
				pIteratorIfToExecute = INDIRECT_OPEN[ i ].m_pCrawlingChain[ randomIndex ].m_CrawlingList.GetIterator();
				break;
			}
		}

		assert( NULL != pIteratorIfToExecute );

		Board::PositionXY xyCrawling = xyFirst;

		// Find out the position on board associated with letter that has just been drawn.
		for( ; pIteratorIfToExecute->HasNext(); )
		{
			const OpenBook::Crawling crawling = pIteratorIfToExecute->GetNext();
			rBoard.GoDirection( xyCrawling, crawling.m_Direction, crawling.m_Shift );
			assert( rBoard.IsOnBoard( xyCrawling ) );
		}
		pIteratorIfToExecute->SetToBase();

		retVal = xyCrawling;
	}
	else
	{
		// means opening game is undefined.
	}

	return retVal;
}

// Provide best second move for black.
Board::PositionXY OpenBook::GetBestSecondBlackMove( const Board& rBoard )
{
	// No dedicated opening-book for black.
	// Just choose randomly one of the following option

	// Direct opening(o -first move):
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . o . o . . . . . . .|
	//3 |. . . . . . x . . . . . . . .|
	//4 |. . . . . o . o . . . . . . .|

	static const Board::Direction direction[] = { Board::UP_RIGHT,
												  Board::DOWN_RIGHT,
												  Board::DOWN_LEFT,
												  Board::UP_LEFT };

	const uint32_t randomIndex = ( rand() % NUMELEM( direction ) );

	Board::PositionXY xy = XY_OUT_OF_BOARD;
	assert( rBoard.GetLastMove( xy ) );
	assert( rBoard.CanIGo( xy, direction[ randomIndex ] ) );
    rBoard.GoDirection( xy, direction[ randomIndex ] );

    return xy;
}

/// Check if game has 'open direct' introduction.
OpenBook::OpenGameType OpenBook::OpenGame( const Board& rBoard )
{
	// Direct opening(x -first move):
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . x o . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|

	// Indirect opening(x -first move):
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . o . . . . . . .|
	//3 |. . . . . . x . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|

	// Moves on board to be able call this method.
	static const uint32_t minMoveOnBoard = 2;
	assert( minMoveOnBoard == rBoard.GetMoveNumber() );

	OpenBook::OpenGameType retVal = OpenBook::UNDEFINED;

	Board::PositionXY xyFirst;
	const bool status = rBoard.GetFirstMove( xyFirst );
	assert( status );

	const Board::Player player = rBoard.GetMove( xyFirst );

	for( uint32_t i = 0; i < DIRECT_PATH_SIZE; ++i )
	{
		if( Board::NO_NEIGHBOR_FOUND != rBoard.NeighbourDistance( xyFirst, DIRECT_PATH[ i ], player ) )
		{
			retVal = OpenBook::DIRECT;
			break;
		}
	}

	for( uint32_t i = 0; i < INDIRECT_PATH_SIZE; ++i )
	{
		if( Board::NO_NEIGHBOR_FOUND != rBoard.NeighbourDistance( xyFirst, INDIRECT_PATH[ i ], player ) )
		{
			// Open game cant be direct and indirect at the same time.
			assert ( OpenBook::UNDEFINED == retVal );

			retVal = OpenBook::INDIRECT;
			break;
		}
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
