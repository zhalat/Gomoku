/*
 * SingleListTest.cpp
 *
 *  Created on: 31 dec, 2016
 *      Author: halsoft
 */
#include <assert.h>     		// for assert.
#include <iostream>
#include "OpenBookTest.hpp"

static bool Checker( const Board::PositionXY xy, const std::vector<Board::PositionXY>& container )
{
	bool isOK = false;

	for( uint32_t i = 0; i < container.size(); ++i )
	{
		if( container[ i ] == xy )
		{
			isOK = true;
		}
	}

	return isOK;
}

void OpenBookTest::DirectOpeningGame1()
{
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
	m_pBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_A );
	m_pBoard->PutMove( Board::PositionXY( 5, 6 ), Board::PLAYER_B );

	const std::vector<Board::PositionXY> expectedMovements = {
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 8, 6 )
	};

	const uint32_t maxSamples = 100;

	for( uint32_t i = 0; i < maxSamples; ++i )
	{
		const Board::PositionXY xyOpening = OpenBook::GetBestThirdWhiteMove( *m_pBoard );

		const bool isOnExpectedList = Checker( xyOpening, expectedMovements );
		CPPUNIT_ASSERT( isOnExpectedList == true );
	}
}
void OpenBookTest::DirectOpeningGame2()
{
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . D . . . . . . . .|
	//5 |. . . . . . . B . . . . . . .|
	//6 |. . . . F . x o A . . . . . .|
	//7 |. . . . . . . C . . . . . . .|
	//8 |. . . . . . E . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	m_pBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_A );
	m_pBoard->PutMove( Board::PositionXY( 6, 7 ), Board::PLAYER_B );

	const std::vector<Board::PositionXY> expectedMovements = {
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 8, 6 )
	};

	const uint32_t maxSamples = 100;

	for( uint32_t i = 0; i < maxSamples; ++i )
	{
		const Board::PositionXY xyOpening = OpenBook::GetBestThirdWhiteMove( *m_pBoard );

		const bool isOnExpectedList = Checker( xyOpening, expectedMovements );
		CPPUNIT_ASSERT( isOnExpectedList == true );
	}
}

void OpenBookTest::DirectOpeningGame3()
{
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . F . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . E . x . D . . . . . .|
	//7 |. . . . . C o B . . . . . . .|
	//8 |. . . . . . A . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	m_pBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_A );
	m_pBoard->PutMove( Board::PositionXY( 7, 6 ), Board::PLAYER_B );

	const std::vector<Board::PositionXY> expectedMovements = {
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 7, 5 ),
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 8, 6 )
	};

	const uint32_t maxSamples = 100;

	for( uint32_t i = 0; i < maxSamples; ++i )
	{
		const Board::PositionXY xyOpening = OpenBook::GetBestThirdWhiteMove( *m_pBoard );

		const bool isOnExpectedList = Checker( xyOpening, expectedMovements );
		CPPUNIT_ASSERT( isOnExpectedList == true );
	}
}

void OpenBookTest::DirectOpeningGame4()
{
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . E . . . . . . . .|
	//5 |. . . . . C . . . . . . . . .|
	//6 |. . . . A o x . F . . . . . .|
	//7 |. . . . . B . . . . . . . . .|
	//8 |. . . . . . D . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	m_pBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_A );
	m_pBoard->PutMove( Board::PositionXY( 6, 5 ), Board::PLAYER_B );

	const std::vector<Board::PositionXY> expectedMovements = {
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 7, 5 ),
		Board::PositionXY( 8, 6 )
	};

	const uint32_t maxSamples = 100;

	for( uint32_t i = 0; i < maxSamples; ++i )
	{
		const Board::PositionXY xyOpening = OpenBook::GetBestThirdWhiteMove( *m_pBoard );

		const bool isOnExpectedList = Checker( xyOpening, expectedMovements );
		CPPUNIT_ASSERT( isOnExpectedList == true );
	}
}

void OpenBookTest::IndirectOpeningGame1()
{
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
	m_pBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_A );
	m_pBoard->PutMove( Board::PositionXY( 5, 7 ), Board::PLAYER_B );

	const std::vector<Board::PositionXY> expectedMovements = {
		Board::PositionXY( 4, 5 ),
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 7, 4 ),
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 8, 5 )
	};

	const uint32_t maxSamples = 100;

	for( uint32_t i = 0; i < maxSamples; ++i )
	{
		const Board::PositionXY xyOpening = OpenBook::GetBestThirdWhiteMove( *m_pBoard );

		const bool isOnExpectedList = Checker( xyOpening, expectedMovements );
		CPPUNIT_ASSERT( isOnExpectedList == true );
	}
}

void OpenBookTest::IndirectOpeningGame2()
{
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . M . . . . . . . . .|
	//5 |. . . . N . . I G . . . . . .|
	//6 |. . . . . . x . H . . . . . .|
	//7 |. . . . . K . o . . . . . . .|
	//8 |. . . . . L J . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	m_pBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_A );
	m_pBoard->PutMove( Board::PositionXY( 7, 7 ), Board::PLAYER_B );

	const std::vector<Board::PositionXY> expectedMovements = {
		Board::PositionXY( 4, 5 ),
		Board::PositionXY( 5, 4 ),
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 5, 8 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 7, 5 ),
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 8, 6 )
	};

	const uint32_t maxSamples = 100;

	for( uint32_t i = 0; i < maxSamples; ++i )
	{
		const Board::PositionXY xyOpening = OpenBook::GetBestThirdWhiteMove( *m_pBoard );

		const bool isOnExpectedList = Checker( xyOpening, expectedMovements );
		CPPUNIT_ASSERT( isOnExpectedList == true );
	}
}

void OpenBookTest::IndirectOpeningGame3()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . N . . . . . . .|
	//5 |. . . . L K . . M . . . . . .|
	//6 |. . . . J . x . . . . . . . .|
	//7 |. . . . . o . I . . . . . . .|
	//8 |. . . . . . H G . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	m_pBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_A );
	m_pBoard->PutMove( Board::PositionXY( 7, 5 ), Board::PLAYER_B );

	const std::vector<Board::PositionXY> expectedMovements = {
		Board::PositionXY( 4, 7 ),
		Board::PositionXY( 5, 8 ),
		Board::PositionXY( 5, 4 ),
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 8, 6 ),
		Board::PositionXY( 8, 7 )
	};

	const uint32_t maxSamples = 100;

	for( uint32_t i = 0; i < maxSamples; ++i )
	{
		const Board::PositionXY xyOpening = OpenBook::GetBestThirdWhiteMove( *m_pBoard );

		const bool isOnExpectedList = Checker( xyOpening, expectedMovements );
		CPPUNIT_ASSERT( isOnExpectedList == true );
	}
}

void OpenBookTest::IndirectOpeningGame4()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . J L . . . . . . .|
	//5 |. . . . . o . K . . . . . . .|
	//6 |. . . . H . x . . . . . . . .|
	//7 |. . . . G I . . N . . . . . .|
	//8 |. . . . . . . M . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	m_pBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_A );
	m_pBoard->PutMove( Board::PositionXY( 5, 5 ), Board::PLAYER_B );

	const std::vector<Board::PositionXY> expectedMovements = {
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 4, 7 ),
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 7, 4 ),
		Board::PositionXY( 7, 5 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 8, 7 )
	};

	const uint32_t maxSamples = 100;

	for( uint32_t i = 0; i < maxSamples; ++i )
	{
		const Board::PositionXY xyOpening = OpenBook::GetBestThirdWhiteMove( *m_pBoard );

		const bool isOnExpectedList = Checker( xyOpening, expectedMovements );
		CPPUNIT_ASSERT( isOnExpectedList == true );
	}
}


