/*
 * Threat2CaseATest.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: Zbigniew Halat
 */
#include <assert.h>                // for assert.
#include "Board.hpp"               // for Board definitions.
#include "Threat2CaseATest.hpp"    // for header class definition.

void Threat2CaseATest::FindPatternOnHorizontalTrendTest1()
{
	// Testing of each position: .XX...

	// a:   .X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   .XX...
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternOnHorizontalTrendTest2()
{
	// Testing of each position: .X.X..

	// a:   .X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   .X.X..
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternOnHorizontalTrendTest3()
{
	// Testing of each position: .X..X.

	// a:   .X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   .X..X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternOnHorizontalTrendTest4()
{
	// Testing of each position: ..XX..

	// a:   ..X...
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   ..XX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternOnHorizontalTrendTest5()
{
	// Testing of each position: ..X.X.

	// a:   ..X...
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   ..X.X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternOnHorizontalTrendTest6()
{
	// Testing of each position: ...XX.

	// a:   ....X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   ...XX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternAbuttedToBoardTest1()
{
	// Testing of each position: .XX...
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 2 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternAbuttedToBoardTest2()
{
	// Testing of each position: .X.X..
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternAbuttedToBoardTest3()
{
	// Testing of each position: .X..X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternAbuttedToBoardTest4()
{
	// Testing of each position: ..XX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 2 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternAbuttedToBoardTest5()
{
	// Testing of each position: ..X.X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 2 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternAbuttedToBoardTest6()
{
	// Testing of each position: ...XX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 3 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 2 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternIntruder()
{
	// Testing of each position: .X..X.

	// a:   .X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   .X..X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// c:   .XO.X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternSixInARow1()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. x x . . x . . . . . . . . .|
	//1 |. . . . . . . . . x . . x x .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 9 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 12 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 13 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 9 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 12 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 13 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternSixInARow2()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. x x . . . x . . . . . . . .|
	//1 |. . . . . . . . x . . x . x .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 8 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 11 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 13 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 11 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 13 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::FindPatternSixInARow3()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . x . x x . . . x . . .|
	//2 |. . . . x . x x . . . o . . .|
	//3 |. . . . o . x x . . . x . . .|

	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 7 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 11 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 7 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 11 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 4 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 7 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 11 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat2CaseATest::StandarizePOVTest1()
{
	// Test  '.xx...*' from various point of view:
	//
	const uint8_t Lenght2A = 7;
	// a. *
	const uint8_t asterixNorm = 0x40;

	const uint8_t asterixPov0 = 0x40;
	const uint8_t asterixPov2 = 0x10;
	const uint8_t asterixPov5 = 0x02;
	CPPUNIT_ASSERT( asterixNorm == m_pThreatFinder->StandarizePOV( asterixPov0, 0, Lenght2A ) );
	CPPUNIT_ASSERT( asterixNorm == m_pThreatFinder->StandarizePOV( asterixPov2, 2, Lenght2A ) );
	CPPUNIT_ASSERT( asterixNorm == m_pThreatFinder->StandarizePOV( asterixPov5, 5, Lenght2A ) );

	// b. .
	const uint8_t dotNorm = 0x39;

	const uint8_t dotPov0 = 0x39;
	const uint8_t dotPov3 = 0x47;
	const uint8_t dotPov5 = 0x4D;
	CPPUNIT_ASSERT( dotNorm == m_pThreatFinder->StandarizePOV( dotPov0, 0, Lenght2A ) );
	CPPUNIT_ASSERT( dotNorm == m_pThreatFinder->StandarizePOV( dotPov3, 3, Lenght2A ) );
	CPPUNIT_ASSERT( dotNorm == m_pThreatFinder->StandarizePOV( dotPov5, 5, Lenght2A ) );

	// b. x
	const uint8_t xNorm = 0x06;

	const uint8_t xPov0 = 0x06;
	const uint8_t xPov2 = 0x21;
	const uint8_t xPov5 = 0x30;
	CPPUNIT_ASSERT( xNorm == m_pThreatFinder->StandarizePOV( xPov0, 0, Lenght2A ) );
	CPPUNIT_ASSERT( xNorm == m_pThreatFinder->StandarizePOV( xPov2, 2, Lenght2A ) );
	CPPUNIT_ASSERT( xNorm == m_pThreatFinder->StandarizePOV( xPov5, 5, Lenght2A ) );
}

void Threat2CaseATest::StandarizePOVTest2()
{
	const uint8_t Lenght2A = 7;
	// Test  '*...xx.' from various point of view:
	//
	// a. *
	const uint8_t asterixNorm = 0x01;

	const uint8_t asterixPov0 = 0x01;
	const uint8_t asterixPov3 = 0x40;
	const uint8_t asterixPov6 = 0x40;
	CPPUNIT_ASSERT( asterixNorm == m_pThreatFinder->StandarizePOV( asterixPov0, 0, Lenght2A ) );
	CPPUNIT_ASSERT( asterixNorm == m_pThreatFinder->StandarizePOV( asterixPov3, 3, Lenght2A ) );
	CPPUNIT_ASSERT( asterixNorm == m_pThreatFinder->StandarizePOV( asterixPov6, 6, Lenght2A ) );

	// b. .
	const uint8_t dotNorm = 0x4E;

	const uint8_t dotPov0 = 0x4E;
	const uint8_t dotPov2 = 0x33;
	const uint8_t dotPov6 = 0x39;
	CPPUNIT_ASSERT( dotNorm == m_pThreatFinder->StandarizePOV( dotPov0, 0, Lenght2A ) );
	CPPUNIT_ASSERT( dotNorm == m_pThreatFinder->StandarizePOV( dotPov2, 2, Lenght2A ) );
	CPPUNIT_ASSERT( dotNorm == m_pThreatFinder->StandarizePOV( dotPov6, 6, Lenght2A ) );

	// b. x
	const uint8_t xNorm = 0x30;

	const uint8_t xPov0 = 0x30;
	const uint8_t xPov2 = 0x0C;
	const uint8_t xPov6 = 0x06;
	CPPUNIT_ASSERT( xNorm == m_pThreatFinder->StandarizePOV( xPov0, 0, Lenght2A ) );
	CPPUNIT_ASSERT( xNorm == m_pThreatFinder->StandarizePOV( xPov2, 2, Lenght2A ) );
	CPPUNIT_ASSERT( xNorm == m_pThreatFinder->StandarizePOV( xPov6, 6, Lenght2A ) );
}

void Threat2CaseATest::GetPieces1()
{
	// .x.x..*
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. x . x . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap4 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 6 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
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

	// c. Check '.':
	//    Normal: .x.x..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.x.x..
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// e. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// f. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat2CaseATest::GetPieces2()
{
	// .xx...*
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. x x . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap4 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );;
	const Board::PositionXY end = Board::PositionXY( 1, 6 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
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

	// c. Check '.':
	//    Normal: .xx...*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: |.xx...
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat2CaseATest::GetPieces3()
{
	// *.x..x.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . x . . x .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 11 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 12 );
	const Board::PositionXY elGap4 = Board::PositionXY( 1, 14 );
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 13 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 8 );
	const Board::PositionXY end = Board::PositionXY( 1, 14 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pThreatFinder->FindThreatPattern( elX2, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

	// 2. Get elements.
	ThreatFinder::ThreatLocation threatLocation;
	m_pThreatFinder->GetThreatFields( threatLocation );

	// 3. Make verification.
	// a. Check '*':
	CPPUNIT_ASSERT( elAsterix1 == threatLocation.m_ThreatDetails.m_Asterixes[1] );
	CPPUNIT_ASSERT( elAsterix2 == threatLocation.m_ThreatDetails.m_Asterixes[0] );

	// b. Check 'x':
	CPPUNIT_ASSERT( elX1 == threatLocation.m_ThreatDetails.m_MyPawns[0] );
	CPPUNIT_ASSERT( elX2 == threatLocation.m_ThreatDetails.m_MyPawns[1] );

	// c. Check '.':
	//    Normal: .x..x.|
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.x..x.
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat2CaseATest::GetPieces4()
{
	//
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . * . . . x x . . . * . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 11 );
	const Board::PositionXY elAsterix2 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elGap4 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elGap7 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap8 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap9 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elExtendGap2 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elX1 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 2 );
	const Board::PositionXY end = Board::PositionXY( 1, 11 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
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

	// c. Check '.':
	//    Normal: .xx...*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *...xx.
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat2CaseATest::GetPieces5()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . x . x . . * . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap4 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap7 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elGap8 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elGap9 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elExtendGap2 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elX1 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
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

	// c. Check '.':
	//    Normal: .x.x..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: |..x.x.
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );
}

void Threat2CaseATest::GetPieces6()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |* . . x . x . . * . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elAsterix2 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elGap4 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elGap7 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elGap8 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap9 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elExtendGap2 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elX1 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 8 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
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

	// c. Check '.':
	//    Normal: .x.x..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *..x.x.
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat2CaseATest::GetPieces7()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |* . . x . x . . o . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elAsterix2 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elGap4 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elGap7 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elGap8 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap9 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elExtendGap2 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elX1 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elO1 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 8 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
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

	// c. Check '.':
	//    Normal: .x.x..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *..x.x.
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat2CaseATest::GetPieces8()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . x . . . . . . . . . .|
	//2 |. . . x . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 0, 5 );
	const Board::PositionXY elGap2 = Board::PositionXY( 3, 2 );
	const Board::PositionXY elGap3 = Board::PositionXY( 4, 1 );
	const Board::PositionXY elGap4 = Board::PositionXY( 5, 0 );
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 0, 5 );
	const Board::PositionXY elGap7 = Board::PositionXY( 3, 2 );
	const Board::PositionXY elGap8 = Board::PositionXY( 4, 1 );
	const Board::PositionXY elGap9 = Board::PositionXY( 5, 0 );
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 4, 1 );
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elX2 = Board::PositionXY( 2, 3 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 5 );
	const Board::PositionXY end = Board::PositionXY( 5, 0 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
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

	// c. Check '.':
	//    Normal: .x.x..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *..x.x.
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat2CaseATest::GetPieces9()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . x . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . x .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 0, 9 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elGap3 = Board::PositionXY( 3, 12 );
	const Board::PositionXY elGap4 = Board::PositionXY( 5, 14 );
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 0, 9 );
	const Board::PositionXY elGap7 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elGap8 = Board::PositionXY( 3, 12 );
	const Board::PositionXY elGap9 = Board::PositionXY( 5, 14 );
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = Board::PositionXY( 0, 9 );
	const Board::PositionXY elX1 = Board::PositionXY( 2, 11 );
	const Board::PositionXY elX2 = Board::PositionXY( 4, 13 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 9 );
	const Board::PositionXY end = Board::PositionXY( 5, 14 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
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

	// c. Check '.':
	//    Normal: .x.x..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *..x.x.
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat2CaseATest::GetPieces10()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . * .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . x . . . . .|
	//5 |. . . . . . . . x . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . x . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = Board::PositionXY( 0, 13 );
	const Board::PositionXY elGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap3 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 1, 12 );
	const Board::PositionXY elGap7 = Board::PositionXY( 2, 11 );
	const Board::PositionXY elGap8 = Board::PositionXY( 3, 10 );
	const Board::PositionXY elGap9 = Board::PositionXY( 6, 7 );
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = Board::PositionXY( 2, 11 );
	const Board::PositionXY elX1 = Board::PositionXY( 4, 9 );
	const Board::PositionXY elX2 = Board::PositionXY( 5, 8 );
	const Board::PositionXY X3 = Board::PositionXY( 7, 6 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 13 );
	const Board::PositionXY end = Board::PositionXY( 6, 7 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( X3, Board::PLAYER_A );
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

	// c. Check '.':
	//    Normal: .x.x..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *..x.x.
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat2CaseATest::GetPieces11()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . x . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . x . . . . .|
	//4 |. . . . . . . . x . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . * . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 8, 4 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 2, 10 );
	const Board::PositionXY elGap2 = Board::PositionXY( 5, 7 );
	const Board::PositionXY elGap3 = Board::PositionXY( 6, 6 );
	const Board::PositionXY elGap4 = Board::PositionXY( 7, 5 );
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap7 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap8 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;;
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 6, 6 );
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 3, 9 );
	const Board::PositionXY elX2 = Board::PositionXY( 4, 8 );
	const Board::PositionXY X3 = Board::PositionXY( 1, 11 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 2, 10 );
	const Board::PositionXY end = Board::PositionXY( 8, 4 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( X3, Board::PLAYER_A );
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

	// c. Check '.':
	//    Normal: .x.x..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *..x.x.
	CPPUNIT_ASSERT( elGap6 == threatLocation.m_ThreatDetails.m_Gaps[5] );
	CPPUNIT_ASSERT( elGap7 == threatLocation.m_ThreatDetails.m_Gaps[6] );
	CPPUNIT_ASSERT( elGap8 == threatLocation.m_ThreatDetails.m_Gaps[7] );
	CPPUNIT_ASSERT( elGap9 == threatLocation.m_ThreatDetails.m_Gaps[8] );
	CPPUNIT_ASSERT( elGap10 == threatLocation.m_ThreatDetails.m_Gaps[9] );

	// d. Extend gaps:
	CPPUNIT_ASSERT( elExtendGap1 == threatLocation.m_ThreatDetails.m_ExtGaps[0] );
	CPPUNIT_ASSERT( elExtendGap2 == threatLocation.m_ThreatDetails.m_ExtGaps[1] );

	// d. Check 'o':
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

