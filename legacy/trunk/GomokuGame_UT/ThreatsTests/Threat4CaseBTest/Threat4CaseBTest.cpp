/*
 * Threat4CaseBTest.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: ginar
 */
#include <assert.h>     			// for assert.
#include "Board.hpp"				// for Board definitions.
#include "Threat4CaseB.hpp"			// for Threat4CaseB definition.
#include "Threat4CaseBTest.hpp"	    // for header class definition.

void Threat4CaseBTest::FindThreatFourPatternHorizontalTrend1Test()
{
	// step by step build OX.XXX and verify if pattern is found.

	// a:   .X....
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_A );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// b:   OX....
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 3 ), Board::PLAYER_B );
	// no action due to opponent move

	// c:   OX.X..
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// d:   OX.XX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 7 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// e:   OX.XXX. - now pattern is completed.
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 8 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// f:   OX.XXXX. - now pattern is completed.
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 9 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 9 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat4CaseBTest::FindThreatFourPatternHorizontalTrend2Test()
{
	// step by step build XOOOO. and verify if pattern is founded.

	// a:   .O....
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 5 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );

	// b:   XO....
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 4 ), Board::PLAYER_A );
	// no action due to opponent move

	// c:   XOO...
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 6 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );

	// d:   XOOO..
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 7 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );

	// e:   XOOOO. - now pattern is completed.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 8 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
}

void Threat4CaseBTest::FindThreatFourPatternHorizontalTrend3Test()
{
	// .XX.X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 6 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// OXX.XX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 7 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// O.XX.X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 7 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// OXXX.X.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 3 ), Board::PLAYER_A );
    CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// XX.X.OXXX..
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 5 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 7 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 8 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 9 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 10 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_A );
    CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// XX.X.OXXXX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 11 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 11 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// OX..XXO
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 7 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 8 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// OXX.XXO
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 4 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 4 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat4CaseBTest::FindThreatFourPatternAbuttedToBoardFrame1Test()
{
	// Prepare state where four pattern is exactly sticking to board frame.
	// XXX.X0(board frame)
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 9 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 10 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 11 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 13 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 14 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 10 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );

	// Prepare state where four pattern is exactly sticking to board frame.
	// (board frame)XXX.X0
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 0 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 1 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
}

void Threat4CaseBTest::FindThreatFourPatternAbuttedToBoardFrame2Test()
{
	// Prepare state where four pattern is exactly sticking to board frame and frame board is considered as opposite player.
	// (board frame)XXXX.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 0 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 0 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // begin
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 2 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // middle
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // before end

	// Do the same but symmetrical.
	// .XXXX(board frame)
	m_pGomokuBoard->PutMove( Board::PositionXY( 11, 11 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 12, 12 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 13, 13 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 14, 14 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 11, 11 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // begin
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 12, 12 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // middle
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 14, 14 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // before end
}

void Threat4CaseBTest::FindThreatFourPatternAbuttedToBoardFrame3Test()
{
	// Prepare state where four pattern is exactly sticking to board frame and frame board is considered as opposite player.
	// O.XXXX(board frame)
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 14 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 13 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 12 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 11 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 9 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 14 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // begin
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 13 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // middle
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 11 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // before end

	// Do the same but symmetrical.
	// (board frame)XXXX.O
	m_pGomokuBoard->PutMove( Board::PositionXY( 14, 0 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 13, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 12, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 11, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 9, 5 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 14, 0 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // begin
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 13, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // middle
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 11, 3 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // before end
}

void Threat4CaseBTest::FindThreatFourPatternAbuttedToBoardFrame4Test()
{
	// Prepare state where four pattern is exactly sticking to board frame and frame board is considered as opposite player.
	// (board frame).XXXXO
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 13 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 12 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 11 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 10 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 9 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 1, 13 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // begin
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 11 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // middle
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 10 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // before end

	// Do the same but symmetrical.
	// (board frame).XXXXO
	m_pGomokuBoard->PutMove( Board::PositionXY( 13, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 12, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 11, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 10, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 9, 5 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 13, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // begin
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 11, 3 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // middle
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 10, 4 ), ThreatFinder::RISING, Board::PLAYER_A ) ); // before end
}

void Threat4CaseBTest::FindThreatFourPatternAbuttedToBoardFrame5Test()
{
	// Prepare state where four pattern is exactly sticking to board frame and frame board is considered as opposite player.
	// OXXXX(board frame).
	m_pGomokuBoard->PutMove( Board::PositionXY( 10, 10 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 11, 11 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 12, 12 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 13, 13 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 14, 14 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 11, 11 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // begin
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 12, 12 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // middle
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 14, 14 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // before end

	// (board frame)XXXXO.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 0 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 0 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // begin
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 2 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // middle
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 4, 4 ), ThreatFinder::FALLING, Board::PLAYER_A ) ); // before end
}

void Threat4CaseBTest::FindThreatFourPatternAbuttedToBoardFrame6Test()
{
	// (frame)XXXX(frame)
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 0 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 3 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 2, 1 ), ThreatFinder::RISING, Board::PLAYER_A ) );
}

void Threat4CaseBTest::FindThreatSixInRowTest1()
{
	// a:   .O....
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 5 ), Board::PLAYER_B );
	// b:   XO....
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 4 ), Board::PLAYER_A );
	// c:   XOO...
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 6 ), Board::PLAYER_B );
	// d:   XOOO..
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 7 ), Board::PLAYER_B );
	// e:   XOOOO. - now pattern is completed.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 8 ), Board::PLAYER_B );
	// f:   XOOOO.O - six in row.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 10 ), Board::PLAYER_B );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 5 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 6 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 7 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 8 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 0, 10 ), ThreatFinder::HORIZONTAL, Board::PLAYER_B ) );
}

void Threat4CaseBTest::FindThreatFourPatternMixTrendTest()
{
	// some complicated situations.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 7 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 5 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 6 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 4 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 5 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 6 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 6, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 6, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 6, 6 ), Board::PLAYER_B );
	m_pGomokuBoard->PutMove( Board::PositionXY( 6, 7 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 7, 2 ), Board::PLAYER_A );

	// Check situation form (6,2) position.
#warning "TODO: 6 pawns in row are improperly handled. This probably should be recognized by PostConditionConstrain()."
	//CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 6, 2 ), ThreatFinder::VERTICAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 6, 2 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 6, 2 ), ThreatFinder::RISING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 6, 2 ), ThreatFinder::FALLING, Board::PLAYER_A ) );

	// Check situation form (3,3) position.
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );

	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::VERTICAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::RISING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::FALLING, Board::PLAYER_A ) );

	// Change a little bit situation.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_B );

	// Again check situation form (3,3) position.
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::VERTICAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( true, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::HORIZONTAL, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::RISING, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( false, m_pThreatFinder->FindThreatPattern( Board::PositionXY( 3, 3 ), ThreatFinder::FALLING, Board::PLAYER_A ) );
}

void Threat4CaseBTest::GetPieces1()
{
	// oxxx.x*
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . o x x x . x . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 8 );
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
	const Board::PositionXY elX1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elX4 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elX5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO1 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 4 );
	const Board::PositionXY end = Board::PositionXY( 1, 10 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elO1, Board::PLAYER_B );
	m_pThreatFinder->FindThreatPattern( elX4, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

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

void Threat4CaseBTest::GetPieces2()
{
	// oxx..xo
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . o x x x . x o . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 10 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 8 );
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
	const Board::PositionXY elX1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elX2 = Board::PositionXY( 1, 6 );
	const Board::PositionXY elX3 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elX4 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elX5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO1 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elO2 = Board::PositionXY( 1, 10 );
	const Board::PositionXY beginning = Board::PositionXY( 1, 4 );
	const Board::PositionXY end = Board::PositionXY( 1, 10 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elO1, Board::PLAYER_B );
	m_pGomokuBoard->PutMove( elO2, Board::PLAYER_B );
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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat4CaseBTest::GetPieces3()
{
	// |xxx.x*
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |x x x . x * . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 3 );
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
	const Board::PositionXY elX4 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elX5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 5 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
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

void Threat4CaseBTest::GetPieces4()
{
	// |xxx.xo
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |x x x . x o . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 3 );
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
	const Board::PositionXY elX4 = Board::PositionXY( 1, 4 );
	const Board::PositionXY elX5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO1 = Board::PositionXY( 1, 5 );
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 0 );
	const Board::PositionXY end = Board::PositionXY( 1, 5 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat4CaseBTest::GetPieces5()
{
	// |x.xxx|
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . x . . . . . . . . . .|
	//1 |. . . x . . . . . . . . . . .|
	//2 |. . x . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |x . . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 3, 1 );
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
	const Board::PositionXY elX4 = Board::PositionXY( 4, 0 );
	const Board::PositionXY elX5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 4 );
	const Board::PositionXY end = Board::PositionXY( 4, 0 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
	m_pThreatFinder->FindThreatPattern( elX4, ThreatFinder::RISING, Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[0] );
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat4CaseBTest::GetPieces6()
{
	// |.xxxxo
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . x . . . .|
	//2 |. . . . . . . . . . . x . . .|
	//3 |. . . . . . . . . . . . x . .|
	//4 |. . . . . . . . . . . . . x .|
	//5 |. . . . . . . . . . . . . . o|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 0, 9 );
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
	const Board::PositionXY elX2 = Board::PositionXY( 2, 11 );
	const Board::PositionXY elX3 = Board::PositionXY( 3, 12 );
	const Board::PositionXY elX4 = Board::PositionXY( 4, 13 );
	const Board::PositionXY elX5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO1 = Board::PositionXY( 5, 14 );
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 0, 9 );
	const Board::PositionXY end = Board::PositionXY( 5, 14 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elO1, Board::PLAYER_B );
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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}

void Threat4CaseBTest::GetPieces7()
{
	//  *xx.xxo
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . x x . x x o . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|

	// 0. Define expectation.
	const Board::PositionXY elAsterix1 = Board::PositionXY( 1, 3 );
	const Board::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elGap1 = Board::PositionXY( 1, 6 );
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
	const Board::PositionXY elX3 = Board::PositionXY( 1, 7 );
	const Board::PositionXY elX4 = Board::PositionXY( 1, 8 );
	const Board::PositionXY elX5 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY elO1 = Board::PositionXY( 1, 9 );
	const Board::PositionXY elO2 = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	const Board::PositionXY beginning = Board::PositionXY( 1, 3 );
	const Board::PositionXY end = Board::PositionXY( 1, 9 );

	// 1. Create a threat.
	m_pGomokuBoard->PutMove( elX1, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX2, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX3, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elX4, Board::PLAYER_A );
	m_pGomokuBoard->PutMove( elO1, Board::PLAYER_B );
	m_pThreatFinder->FindThreatPattern( elX4, ThreatFinder::HORIZONTAL, Board::PLAYER_A );

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
	CPPUNIT_ASSERT( ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD == threatLocation.m_ThreatDetails.m_EnemyPawns[1] );

	// e. Check begin & end:
	CPPUNIT_ASSERT( beginning == threatLocation.m_ThreatDetails.m_BeginningThreat );
	CPPUNIT_ASSERT( end == threatLocation.m_ThreatDetails.m_EndThreat );
}


