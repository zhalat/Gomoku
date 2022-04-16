/*
 * ThreatWinnerTest.hpp
 *
 *  Created on: Apr 26, 2016
 *      Author: Zbigniew Halat
 */
#include <assert.h>     			// for assert.
#include "Board.hpp"				// for Board definitions.
#include "ThreatWinnerTest.hpp"	    // for header class definition.
#include "ThreatWinner.hpp"	        // for header class definition.

void ThreatWinnerTest::FindPatternOnHorizontalTrendTest1()
{
	// a:   X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   XX...
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// c:   XXX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// d:   XXXX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// e:   XXXXX
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// Six in a row is not winning path.
	// f:   XXXXXX
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void ThreatWinnerTest::FindPatternOnHorizontalTrendTest2()
{
	// a:   X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::FALLING, Board::PLAYER_A ) );

	// b:   XX...
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 2 ), ThreatFinder::FALLING, Board::PLAYER_A ) );

	// c:   XXX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::FALLING, Board::PLAYER_A ) );

	// d:   XXXX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 4 ), ThreatFinder::FALLING, Board::PLAYER_A ) );

	// e:   XXXXX
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 5 ), ThreatFinder::FALLING, Board::PLAYER_A ) );

	// Six in a row is not winning path.
	// f:   XXXXXX
	m_pGomokuBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 6, 6 ), ThreatFinder::FALLING, Board::PLAYER_A ) );
}

void ThreatWinnerTest::FindPatternOnHorizontalTrendTest3()
{
	// a:   O....
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::FALLING, Board::PLAYER_B ) );

	// b:   OO...
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 2 ), ThreatFinder::FALLING, Board::PLAYER_B ) );

	// c:   OOO..
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::FALLING, Board::PLAYER_B ) );

	// d:   OOOO.
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 4 ), ThreatFinder::FALLING, Board::PLAYER_B ) );

	// e:   OOOOO
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 5 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 5 ), ThreatFinder::FALLING, Board::PLAYER_B ) );

	// Six in a row is not winning path.
	// f:   OOOOOO
	m_pGomokuBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 6, 6 ), ThreatFinder::FALLING, Board::PLAYER_B ) );
}

void ThreatWinnerTest::FindPatternOnHorizontalTrendTest4()
{
	// a:   XXX.X
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   XXXXX
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void ThreatWinnerTest::FindPatternOnHorizontalTrendTest5()
{
	// a:   OOO.OO
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );

	// b:   OOOOOO
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
}

void ThreatWinnerTest::FindPatternOnHorizontalTrendTest6()
{
	// a:   XXX.XO
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );

	// b:   XXXXXO
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
}

void ThreatWinnerTest::FindPatternOnHorizontalTrendTest7()
{
	// a:   XOOO.OX
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 0 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 0 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );

	// b:   XOOOOOX
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
}

void ThreatWinnerTest::FindPatternAbuttedToBoardTest()
{
	// a:   X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 0 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 0 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	// b:   XX...
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 1 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	// c:   XXX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 2 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	// d:   XXXX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	// e:   XXXXX
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 4 ), ThreatFinder::RISING, Board::PLAYER_A ) );
}

void ThreatWinnerTest::GetPieces1()
{
	// .xxxx.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . x x x x x . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elAsterix2 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap3 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap7 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap8 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elX4 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elX5 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 3 );
	const Board::PositionXY end = Board::PositionXY( 1, 9 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX5, Board::PLAYER_A );
	m_pThreatFinder->FindThreatPattern( elX1, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

	// 2. Get elements.
	ThreatFinder::ThreatLocation threatLocation;
	m_pThreatFinder->GetThreatFields( threatLocation );

	// 3. Make verification.
	// a. Check '*':
	CPPUNIT_ASSERT( elAsterix1 == threatLocation.m_ThreatDetails.m_Asterixes[0] );
	CPPUNIT_ASSERT( elAsterix2 == threatLocation.m_ThreatDetails.m_Asterixes[1] );

	// b. Check 'x':
	CPPUNIT_ASSERT( elX1 == threatLocation.m_ThreatDetails.m_MyPawns[0] );
	CPPUNIT_ASSERT( elX2 == threatLocation.m_ThreatDetails.m_MyPawns[1] );
	CPPUNIT_ASSERT( elX3 == threatLocation.m_ThreatDetails.m_MyPawns[2] );
	CPPUNIT_ASSERT( elX4 == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( elX5 == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void ThreatWinnerTest::GetPieces2()
{
	// |xxxx.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |x x x x x . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap3 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap7 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap8 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elX4 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elX5 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 5 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX5, Board::PLAYER_A );
	m_pThreatFinder->FindThreatPattern( elX1, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

	// 2. Get elements.
	ThreatFinder::ThreatLocation threatLocation;
	m_pThreatFinder->GetThreatFields( threatLocation );

	// 3. Make verification.
	// a. Check '*':
	CPPUNIT_ASSERT( elAsterix1 == threatLocation.m_ThreatDetails.m_Asterixes[0] );
	CPPUNIT_ASSERT( elAsterix2 == threatLocation.m_ThreatDetails.m_Asterixes[1] );

	// b. Check 'x':
	CPPUNIT_ASSERT( elX1 == threatLocation.m_ThreatDetails.m_MyPawns[0] );
	CPPUNIT_ASSERT( elX2 == threatLocation.m_ThreatDetails.m_MyPawns[1] );
	CPPUNIT_ASSERT( elX3 == threatLocation.m_ThreatDetails.m_MyPawns[2] );
	CPPUNIT_ASSERT( elX4 == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( elX5 == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void ThreatWinnerTest::GetPieces3()
{
	// |xxxx.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . x x x x x|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap3 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap7 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap8 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 11 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 12 );
	const Board::PositionXY elX4 = Board::PositionXY( 1, 13 );
	const Board::PositionXY elX5 = Board::PositionXY( 1, 14 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 9 );
	const Board::PositionXY end = Board::PositionXY( 1, 14 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX5, Board::PLAYER_A );
	m_pThreatFinder->FindThreatPattern( elX1, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

	// 2. Get elements.
	ThreatFinder::ThreatLocation threatLocation;
	m_pThreatFinder->GetThreatFields( threatLocation );

	// 3. Make verification.
	// a. Check '*':
	CPPUNIT_ASSERT( elAsterix1 == threatLocation.m_ThreatDetails.m_Asterixes[0] );
	CPPUNIT_ASSERT( elAsterix2 == threatLocation.m_ThreatDetails.m_Asterixes[1] );

	// b. Check 'x':
	CPPUNIT_ASSERT( elX1 == threatLocation.m_ThreatDetails.m_MyPawns[0] );
	CPPUNIT_ASSERT( elX2 == threatLocation.m_ThreatDetails.m_MyPawns[1] );
	CPPUNIT_ASSERT( elX3 == threatLocation.m_ThreatDetails.m_MyPawns[2] );
	CPPUNIT_ASSERT( elX4 == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( elX5 == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void ThreatWinnerTest::GetPieces4()
{
	// |xxxxx|
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . x . . . . . . . . . .|
	//1 |. . . x . . . . . . . . . . .|
	//2 |. . x . . . . . . . . . . . .|
	//3 |. x . . . . . . . . . . . . .|
	//4 |x . . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap3 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap7 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap8 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 0, 4 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elX3 = Board::PositionXY( 2, 2 );
	const Board::PositionXY elX4 = Board::PositionXY( 3, 1 );
	const Board::PositionXY elX5 = Board::PositionXY( 4, 0 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 4 );
	const Board::PositionXY end = Board::PositionXY( 4, 0 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX5, Board::PLAYER_A );
	m_pThreatFinder->FindThreatPattern( elX1, ThreatFinder::RISING, Board::PLAYER_A );

	// 2. Get elements.
	ThreatFinder::ThreatLocation threatLocation;
	m_pThreatFinder->GetThreatFields( threatLocation );

	// 3. Make verification.
	// a. Check '*':
	CPPUNIT_ASSERT( elAsterix1 == threatLocation.m_ThreatDetails.m_Asterixes[0] );
	CPPUNIT_ASSERT( elAsterix2 == threatLocation.m_ThreatDetails.m_Asterixes[1] );

	// b. Check 'x':
	CPPUNIT_ASSERT( elX1 == threatLocation.m_ThreatDetails.m_MyPawns[0] );
	CPPUNIT_ASSERT( elX2 == threatLocation.m_ThreatDetails.m_MyPawns[1] );
	CPPUNIT_ASSERT( elX3 == threatLocation.m_ThreatDetails.m_MyPawns[2] );
	CPPUNIT_ASSERT( elX4 == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( elX5 == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}
