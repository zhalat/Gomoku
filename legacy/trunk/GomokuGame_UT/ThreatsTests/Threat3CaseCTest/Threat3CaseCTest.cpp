/*
 * Threat3CaseCTest.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: Zbigniew Halat
 */
#include <assert.h>                // for assert.
#include "Board.hpp"               // for Board definitions.
#include "Threat3CaseCTest.hpp"    // for header class definition.

void Threat3CaseCTest::FindPatternOnHorizontalTrendTest1()
{
	// Testing of each position: .XXX.

	// a:   .X...
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   ..XX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// c:   ..XXX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// d:   O..XXXO
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 0 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}


void Threat3CaseCTest::FindPatternOnHorizontalTrendTest2()
{
	//                        1 1 1 1 1
	//     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//  0 |. . . . . . . . . . . . . . .|
	//  1 |. . . x . x . x . . . . . . .|
	//  2 |. . . . . . . . . . . . . . .|
	//  3 |. . . . . . . . . . . . . . .|

	// Testing of each position: x.x.x

	// a:   X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   X.X..
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// c:   X.X.X
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 7 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// d:   OX.X.XO
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 8 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseCTest::FindPatternOnHorizontalTrendTest3()
{
	//                        1 1 1 1 1
	//     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//  0 |. . . . . . . . . . . . . . .|
	//  1 |. . x o . o . o x . . . . . .|
	//  2 |. . . . . . . . . . . . . . .|
	//  3 |. . . . . . . . . . . . . . .|

	//precondition
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 8 ), Board::PLAYER_A );

	// Testing of each position: o.o.o

	// a:   o....
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );

	// b:   o.o..
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );

	// c:   o.o.o
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 7 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );

	// c:   o.ooo
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
}

void Threat3CaseCTest::FindPatternOnHorizontalTrendTest4()
{
	//                         1 1 1 1 1
	//     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//  0 |. . . . . . . . . . . . . . .|
	//  1 |. . o x x x . . o . . . . . .|
	//  2 |. . . . . . . . . . . . . . .|
	//  3 |. . . . . . . . . . . . . . .|

	// Precondition:
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 8 ), Board::PLAYER_B );

	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseCTest::FindPatternOnHorizontalTrendTest5()
{
	//                         1 1 1 1 1
	//     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//  0 |. . . . . . . . . . . . . . .|
	//  1 |. . o . . x x x o . . . . . .|
	//  2 |. . . . . . . . . . . . . . .|
	//  3 |. . . . . . . . . . . . . . .|

	// Precondition:
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 8 ), Board::PLAYER_B );

	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 7 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseCTest::FindPatternOnHorizontalTrendTest6()
{
	//                         1 1 1 1 1
	//     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//  0 |. . . . . . . . . . . . . . .|
	//  1 |. . o x . . x x o . . . . . .|
	//  2 |. . . . . . . . . . . . . . .|
	//  3 |. . . . . . . . . . . . . . .|

	// Precondition:
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 8 ), Board::PLAYER_B );

	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 7 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseCTest::FindPatternOnHorizontalTrendTest7()
{
	//                         1 1 1 1 1
	//     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//  0 |. . . . . . . . . . . . . . .|
	//  1 |. . o x x . . x o . . . . . .|
	//  2 |. . . . . . . . . . . . . . .|
	//  3 |. . . . . . . . . . . . . . .|

	// Precondition:
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 8 ), Board::PLAYER_B );

	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 7 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseCTest::FindPatternOnHorizontalTrendTest8()
{

	//                         1 1 1 1 1
	//     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//  0 |. . . . . . . . . . . . . . .|
	//  1 |. . o x x . . x x . . . . . .|
	//  2 |. . . . . . . . . . . . . . .|
	//  3 |. . . . . . . . . . . . . . .|

	// Precondition:
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );

	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 8 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 7 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseCTest::FindPatternOnFallingTrendTest9()
{
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|
	//	5 |. . . . . . . . . . . . . . .|
	//	6 |. . . . . . . . . . . . . . .|
	//	7 |. . . . . . . . . . . . . . .|
	//	8 |. . . . . . . . . . . . . . .|
	//	9 |. . . . . . . . . . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . . . . . . o . . .|
	//	12|. . . . . . . . . . . . x . .|
	//	13|. . . . . . . . . . . . . x .|
	//	14|. . . . . . . . . . . . . . x|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	// Precondition:
	m_pGomokuBoard->PutMove( Board::PositionXY( 11, 11 ), Board::PLAYER_B );

	m_pGomokuBoard->PutMove( Board::PositionXY( 12, 12 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 13, 13 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 14, 14 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 12, 12 ), ThreatFinder::FALLING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 13, 13 ), ThreatFinder::FALLING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 14, 14 ), ThreatFinder::FALLING, Board::PLAYER_A ) );
}

void Threat3CaseCTest::FindPatternOnRisingTrendTest10()
{
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|
	//	5 |. . . . . . . . . . . . . . .|
	//	6 |. . . . . . . . . . . . . . .|
	//	7 |. . . . . . . . . . . . . . .|
	//	8 |. . . . . . . . . . . . . . .|
	//	9 |. . . . . . . . . . . . . . .|
	//	10|. . . . x . . . . . . . . . .|
	//	11|. . . o . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. o . . . . . . . . . . . . .|
	//	14|o . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	// Precondition:
	m_pGomokuBoard->PutMove( Board::PositionXY( 10, 4 ), Board::PLAYER_A );

	m_pGomokuBoard->PutMove( Board::PositionXY( 11, 3 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 13, 1 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 14, 0 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 11, 3 ), ThreatFinder::RISING, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 13, 1 ), ThreatFinder::RISING, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 14, 0 ), ThreatFinder::RISING, Board::PLAYER_B ) );
}


void Threat3CaseCTest::FindPatternAbuttedToBoardTest1()
{
	// Testing abutted to frame: .XXX.

	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 2 ), ThreatFinder::RISING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::RISING, Board::PLAYER_A ) );
}

void Threat3CaseCTest::GetPieces1()
{
	// oxxx..o
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |o x x x . . o . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap3 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap7 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap8 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elO1 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elO2 = Board::PositionXY( 1, 6 );
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 6 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elO1, Board::PLAYER_B );
	m_pGomokuBoard->PutMove( elO2, Board::PLAYER_B );
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

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// f. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat3CaseCTest::GetPieces2()
{
	// |..xxxo
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . x x x o . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elGap3 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap7 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap8 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elO1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 5 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elO1, Board::PLAYER_B );
	m_pThreatFinder->FindThreatPattern( elX2, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

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

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// f. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat3CaseCTest::GetPieces3()
{
	// |.xxx.o
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. x x x . o . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 4 );
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
	const Board::PositionXY elX1 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elO1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 5 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elO1, Board::PLAYER_B );
	m_pThreatFinder->FindThreatPattern( elX2, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

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

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// f. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat3CaseCTest::GetPieces4()
{
	// o.x.xx|
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . o . x . x x|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 12 );
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
	const Board::PositionXY elX1 = Board::PositionXY( 1, 11 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 13 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 14 );
	const Board::PositionXY elO1 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 9 );
	const Board::PositionXY end = Board::PositionXY( 1, 14 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elO1, Board::PLAYER_B );

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

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// f. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat3CaseCTest::GetPieces5()
{
	// ox..xxo
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . o x . . x x o . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 6 );
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
	const Board::PositionXY elX2 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elX4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO1 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elO2 = Board::PositionXY( 1, 9 );
	const Board::PositionXY beginning = Board::PositionXY( 1, 3 );
	const Board::PositionXY end = Board::PositionXY( 1, 9 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elO1, Board::PLAYER_B );
	m_pGomokuBoard->PutMove( elO2, Board::PLAYER_B );
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

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// f. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat3CaseCTest::GetPieces6()
{
	// |x.xx.|
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . x . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . x . . . . . . . . . . . .|
	//3 |. x . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elGap2 = Board::PositionXY( 4, 0 );
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
	const Board::PositionXY elX2 = Board::PositionXY( 2, 2 );
	const Board::PositionXY elX3 = Board::PositionXY( 3, 1 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 4 );
	const Board::PositionXY end = Board::PositionXY( 4, 0 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pThreatFinder->FindThreatPattern( elX2, ThreatFinder::RISING, Board::PLAYER_A );

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

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// f. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat3CaseCTest::GetPieces7()
{
	// |x..xx|
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . x . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . x .|
	//4 |. . . . . . . . . . . . . . x|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 11 );
	const Board::PositionXY elGap2 = Board::PositionXY( 2, 12 );
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
	const Board::PositionXY elX1 = Board::PositionXY( 0, 10 );
	const Board::PositionXY elX2 = Board::PositionXY( 3, 13 );
	const Board::PositionXY elX3 = Board::PositionXY( 4, 14 );
	const Board::PositionXY elX4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 10 );
	const Board::PositionXY end = Board::PositionXY( 4, 14 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pThreatFinder->FindThreatPattern( elX2, ThreatFinder::FALLING, Board::PLAYER_A );

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

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// f. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat3CaseCTest::GetPieces8()
{
	// |..xxx|
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . x . .|
	//3 |. . . . . . . . . . . . . x .|
	//4 |. . . . . . . . . . . . . . x|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 0, 10 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 11 );
	const Board::PositionXY elGap3 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap7 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap8 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 0, 10 );
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 2, 12 );
	const Board::PositionXY elX2 = Board::PositionXY( 3, 13 );
	const Board::PositionXY elX3 = Board::PositionXY( 4, 14 );
	const Board::PositionXY elX4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 10 );
	const Board::PositionXY end = Board::PositionXY( 4, 14 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pThreatFinder->FindThreatPattern( elX1, ThreatFinder::FALLING, Board::PLAYER_A );

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

	// d. Check 'o':
	CPPUNIT_ASSERT( elO1 == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( elO2 == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// f. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}
