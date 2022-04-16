/*
 * Threat3CaseATest.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: Zbigniew Halat
 */
#include <assert.h>                // for assert.
#include "Board.hpp"               // for Board definitions.
#include "Threat3CaseATest.hpp"    // for header class definition.

void Threat3CaseATest::FindPatternOnHorizontalTrendTest1()
{
	// Testing of each position: ..XXX.

	// a:   ..X...
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   ..XX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// c:   ..XXX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternOnHorizontalTrendTest2()
{
	// Testing of each position: .X.XX.

	// a:   .X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   .X.X..
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// c:   .X.XX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternOnHorizontalTrendTest3()
{
	// Testing of each position: .XX.X.

	// a:   ..X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 2 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   .XX...
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// c:   .XX.X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternOnHorizontalTrendTest4()
{
	// Testing of each position: .XXX..

	// a:   .X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 2 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   .XX...
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// c:   .XXX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternOnHorizontalTrendTest5()
{
	// a. Precondition:
	//						   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . x . x . x . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|

	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 8 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b. Action:
	//						   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . x . x . x x . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 9 ), Board::PLAYER_A );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 9 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternOnHorizontalTrendTest6()
{
	// a. Precondition:
	//						   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . x . . x x . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|

	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 7 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 8 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b. Action:
	//						   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . x . x x x . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 6 ), Board::PLAYER_A );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternOnHorizontalTrendTest7()
{
	// a. Precondition:
	//						   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . x x . . x . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|

	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 5 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 8 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b. Action:
	//						   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . x x x . x . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 6 ), Board::PLAYER_A );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternOnHorizontalTrendTest8()
{
	// a. Precondition:
	//						   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . x x x o . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|

	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 5 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 7 ), Board::PLAYER_B );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternOnHorizontalTrendTest9()
{
	// a. Precondition:
	//						   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . o x x x . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|

	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 5 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_B );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternAbuttedToBoardTest1()
{
	// Testing abutted to frame: ..XXX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 2 ), ThreatFinder::RISING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 3 ), ThreatFinder::RISING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternAbuttedToBoardTest2()
{
	// Testing abutted to frame: .X.XX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 3 ), ThreatFinder::RISING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternAbuttedToBoardTest3()
{
	// Testing abutted to frame: .XX.X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternAbuttedToBoardTest4()
{
	// Testing abutted to frame: .XXX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 5, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternInTheMiddleTest1()
{
	// Testing in the middle: OXXX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 0 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 3 ), Board::PLAYER_A );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternInTheMiddleTest2()
{
	// Testing in the middle: O.XXX.O
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 0 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 6 ), Board::PLAYER_B );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternInTheMiddleTest3()
{
	// Testing in the middle: O.XXX..O
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 0 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 7 ), Board::PLAYER_B );

	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternSixInRow1()
{
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 8 ), Board::PLAYER_A );

	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat3CaseATest::FindPatternSixInRow2()
{
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 1 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 4 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 6 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 8 ), Board::PLAYER_B );

	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
}

void Threat3CaseATest::FindPatternSixInRow3()
{
	//						   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . x . . x x x . o . . .|
	//	4 |. . . . . . . . . . . . . . .|
	//	5 |. . . . . . . . . . . . . . .|
	//	6 |. . . . . . . . . . . . . . .|
	//	7 |. . . . . . . . . . . . . . .|
	//	8 |. . . . . . . . . . . . . . .|
	//	9 |. . . . . . . . . . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 7 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 8 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 9 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 11 ), Board::PLAYER_B );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
}

void Threat3CaseATest::FindPatternSixInRow4()
{
	//						   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. x x x . x . . . . . . . . .|
	//	3 |. x x x . . x . . . . . . . .|
	//	4 |. x x x . . o . . . . . . . .|
	//	5 |. . . . . . . . . . . . . . .|
	//	6 |. . . . . . . . . . . . . . .|

	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );

	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 6 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A) );
}

void Threat3CaseATest::ThreatUpDetalisAsterisesTest1()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . x x x . . . . . . x x x .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . x . . . . . o . . . .|
	//4 |. . . x . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . o . .|
	//6 |. x . . . . . . . . . . . o .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . o . . . .|
	//11|. . . x . . . . . . . . . . .|
	//12|. . x . . . . . . . . . o . .|
	//13|. x . . . . . . . . . . . o .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	ThreatFinder::ThreatUpDetails threatUpDetails;

	// For now cant see the reason for this test. * seems to not have usage.
	// Continue this test if needed.

	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 4 ), Board::PLAYER_A );

	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 11 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 12 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 13 ), Board::PLAYER_A );

	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 6, 1 ), Board::PLAYER_A );

	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 10 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 12 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 6, 13 ), Board::PLAYER_B );

	m_pGomokuBoard->PutMove( Board::PositionXY( 11, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 12, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 13, 1 ), Board::PLAYER_A );

	m_pGomokuBoard->PutMove( Board::PositionXY( 11, 11 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 12, 12 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 13, 13 ), Board::PLAYER_B );
}

void Threat3CaseATest::GetPieces1()
{
	// .xxx..*
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. x x x . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 6 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	//    Normal: .xxx..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.xxx..
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

void Threat3CaseATest::GetPieces2()
{
	// |.xx.x.*
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. x x . x . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 6 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );

	m_pThreatFinder->FindThreatPattern( elX3, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	//    Normal: .xxx..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.xxx..
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

void Threat3CaseATest::GetPieces3()
{
	// *.x.xx.|
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . x . x x .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix2 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 11 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 14 );
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 12 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 13 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 8 );
	const Board::PositionXY end = Board::PositionXY( 1, 14 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );

	m_pThreatFinder->FindThreatPattern( elX3, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	//    Normal: .xxx..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.xxx..
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

void Threat3CaseATest::GetPieces4()
{
	// *..xxx..*
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . x x x . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elAsterix2 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elGap7 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap8 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elExtendGap2 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elX1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 2 );
	const Board::PositionXY end = Board::PositionXY( 1, 10 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );

	m_pThreatFinder->FindThreatPattern( elX3, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	//    Normal: .xxx..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.xxx..
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

void Threat3CaseATest::GetPieces5()
{
	// |.x.xx.*o
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. x . x x . . o . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elGap3 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 1, 0 );
	const Board::PositionXY elGap7 = Board::PositionXY( 1, 2 );
	const Board::PositionXY elGap8 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 1 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 6 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );

	m_pThreatFinder->FindThreatPattern( elX3, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	//    Normal: .xxx..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.xxx..
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

void Threat3CaseATest::GetPieces6()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . x . . . . . . . . . . .|
	//3 |. . x . . . . . . . . . . . .|
	//4 |. x . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 0, 5 );
	const Board::PositionXY elGap2 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap3 = Board::PositionXY( 5, 0 );
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 0, 5 );
	const Board::PositionXY elGap7 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elGap8 = Board::PositionXY( 5, 0 );
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = Board::PositionXY( 0, 5 );
	const Board::PositionXY elX1 = Board::PositionXY( 2, 3 );
	const Board::PositionXY elX2 = Board::PositionXY( 3, 2 );
	const Board::PositionXY elX3 = Board::PositionXY( 4, 1 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 5 );
	const Board::PositionXY end = Board::PositionXY( 5, 0 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );

	m_pThreatFinder->FindThreatPattern( elX3, ThreatFinder::RISING, Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	//    Normal: .xxx..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.xxx..
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

void Threat3CaseATest::GetPieces7()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . x . . . .|
	//2 |. . . . . . . . . . . x . . .|
	//3 |. . . . . . . . . . . . x . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 0, 9 );
	const Board::PositionXY elGap2 = Board::PositionXY( 4, 13 );
	const Board::PositionXY elGap3 = Board::PositionXY( 5, 14 );
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 0, 9 );
	const Board::PositionXY elGap7 = Board::PositionXY( 4, 13 );
	const Board::PositionXY elGap8 = Board::PositionXY( 5, 14 );
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = Board::PositionXY( 5, 14 );
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elX2 = Board::PositionXY( 2, 11 );
	const Board::PositionXY elX3 = Board::PositionXY( 3, 12 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 9 );
	const Board::PositionXY end = Board::PositionXY( 5, 14 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );

	m_pThreatFinder->FindThreatPattern( elX3, ThreatFinder::FALLING, Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	//    Normal: .xxx..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.xxx..
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

void Threat3CaseATest::GetPieces8()
{
	// This the case where threat begins at (0, 13) and ends at (6, 7).
	// Only symmetric side exists (see that we start at 2,11)

	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . * .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . x . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . x . . . . .|
	//5 |. . . . . . . . x . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . x . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = Board::PositionXY( 0, 13 );
	const Board::PositionXY elGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap3 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = Board::PositionXY( 1, 12 );
	const Board::PositionXY elGap7 = Board::PositionXY( 3, 10 );
	const Board::PositionXY elGap8 = Board::PositionXY( 6, 7 );
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 2, 11 );
	const Board::PositionXY elX2 = Board::PositionXY( 4, 9 );
	const Board::PositionXY elX3 = Board::PositionXY( 5, 8 );
	const Board::PositionXY X4 = Board::PositionXY( 7, 6 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 13 );
	const Board::PositionXY end = Board::PositionXY( 6, 7 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( X4,   Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	//    Normal: .xxx..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.xxx..
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

void Threat3CaseATest::GetPieces9()
{
	// This the case where threat begins at (0, 13) and ends at (6, 7).
	// Only symmetric side exists (see that we start at 2,11)

	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . x . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . x . . . . .|
	//5 |. . . . . . . . x . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . x . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . * . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 9, 4 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 3, 10 );
	const Board::PositionXY elGap2 = Board::PositionXY( 6, 7 );
	const Board::PositionXY elGap3 = Board::PositionXY( 8, 5 );
	const Board::PositionXY elGap4 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap6 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap7 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap8 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap9 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap10 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elX1 = Board::PositionXY( 4, 9 );
	const Board::PositionXY elX2 = Board::PositionXY( 5, 8 );
	const Board::PositionXY elX3 = Board::PositionXY( 7, 6 );
	const Board::PositionXY X4 = Board::PositionXY( 2, 11 );
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 3, 10 );
	const Board::PositionXY end = Board::PositionXY( 9, 4 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( X4,   Board::PLAYER_A );

	m_pThreatFinder->FindThreatPattern( elX3, ThreatFinder::RISING, Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[3] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_MyPawns[4] );

	// c. Check '.':
	//    Normal: .xxx..*
	CPPUNIT_ASSERT( elGap1 == threatLocation.m_ThreatDetails.m_Gaps[0] );
	CPPUNIT_ASSERT( elGap2 == threatLocation.m_ThreatDetails.m_Gaps[1] );
	CPPUNIT_ASSERT( elGap3 == threatLocation.m_ThreatDetails.m_Gaps[2] );
	CPPUNIT_ASSERT( elGap4 == threatLocation.m_ThreatDetails.m_Gaps[3] );
	CPPUNIT_ASSERT( elGap5 == threatLocation.m_ThreatDetails.m_Gaps[4] );

	//    Symmetric: *.xxx..
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
