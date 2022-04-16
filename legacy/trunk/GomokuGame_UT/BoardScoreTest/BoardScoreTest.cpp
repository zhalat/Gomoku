/*
 * BoardScoreTest.cpp
 *
 *  Created on: 24 Apr, 2016
 *      Author: ginar
 */
#include "BoardScoreTest.hpp"		// for header class definition.
#include "Board.hpp"
#include "Score.hpp"
#include <algorithm>

#define NUMELEM( x )    ( sizeof( x )/sizeof( x[ 0 ] ) )
static bool IsOntheList( const Board::PositionXY xy, const vector<Board::PositionXY>& vct );

static bool Checker( const Board::PositionField positionField, const std::vector<Board::PositionField>& container )
{
	bool isOK = false;

	for( uint32_t i = 0; i < container.size(); ++i )
	{
		if(container[i]==positionField)
		{
			isOK = true;
		}
	}

	return isOK;
}

void BoardScoreTest::AddThreatsTest1()
{
	// Define some threat pairs [threatBegin, threatEnd]
	const Board::PositionXY threat1Begin = Board::PositionXY( 5, 1 ); // assume its Threat2CaseA
	const Board::PositionXY threat1End = Board::PositionXY( 5, 6 );
	const uint32_t threat1Value = Score::THREAT_2_CASE_A_SCORE;

	const Board::PositionXY threat2Begin = Board::PositionXY( 2, 4 ); // assume its Threat2CaseA
	const Board::PositionXY threat2End = Board::PositionXY( 6, 4 );
	const uint32_t threat2Value = Score::THREAT_2_CASE_A_SCORE;

	const Board::PositionXY threat3Begin = Board::PositionXY( 0, 8 ); // assume its Threat2CaseB
	const Board::PositionXY threat3End = Board::PositionXY( 5, 8 );
	const uint32_t threat3Value = Score::THREAT_2_CASE_B_SCORE;

	const Board::PositionXY threat4Begin = Board::PositionXY( 5, 8 ); // assume its Threat3CaseB
	const Board::PositionXY threat4End = Board::PositionXY( 5, 13 );
	const uint32_t threat4Value = Score::THREAT_3_CASE_B_SCORE;

	const Board::PositionXY threat5Begin = Board::PositionXY( 8, 4 ); // assume its Threat4CaseC
	const Board::PositionXY threat5End = Board::PositionXY( 8, 8 );
	const uint32_t threat5Value = Score::THREAT_4_CASE_C_SCORE;

	// On empty board there are no threats.
	CPPUNIT_ASSERT( 0 == m_pBoardScoreHuman->GetScore() );

	ThreatFinder::ThreatLocation threatContainer;

	// Add threat, then check score.
	threatContainer.m_ThreatDetails.m_BeginningThreat = threat1Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat1End;
	threatContainer.m_Trend = ThreatFinder::HORIZONTAL;
	CPPUNIT_ASSERT_EQUAL( true, m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_A ) );
	CPPUNIT_ASSERT( threat1Value == m_pBoardScoreHuman->GetScore() );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat2Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat2End;
	threatContainer.m_Trend = ThreatFinder::VERTICAL;
	CPPUNIT_ASSERT_EQUAL( true, m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_A ) );
	CPPUNIT_ASSERT( (threat1Value + threat2Value) == m_pBoardScoreHuman->GetScore() );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat3Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat3End;
	threatContainer.m_Trend = ThreatFinder::VERTICAL;
	CPPUNIT_ASSERT_EQUAL( true, m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_B ) );
	CPPUNIT_ASSERT( (threat1Value + threat2Value + threat3Value) == m_pBoardScoreHuman->GetScore() );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat4Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat4End;
	threatContainer.m_Trend = ThreatFinder::HORIZONTAL;
	CPPUNIT_ASSERT_EQUAL( true, m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_B ) );
	CPPUNIT_ASSERT( (threat1Value + threat2Value + threat3Value + threat4Value) == m_pBoardScoreHuman->GetScore() );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat5Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat5End;
	threatContainer.m_Trend = ThreatFinder::HORIZONTAL;
	CPPUNIT_ASSERT_EQUAL( true, m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_4_CASE_C ) );
	CPPUNIT_ASSERT( (threat1Value + threat2Value + threat3Value + threat4Value + threat5Value) == m_pBoardScoreHuman->GetScore() );
}

void BoardScoreTest::RemoveThreatsRemoveAllTest1()
{
	// Add one threat and remove it. Score shall be clear.
	// Define threat pairs [threatBegin, threatEnd]
	const Board::PositionXY threat1Begin = Board::PositionXY( 5, 1 ); // assume its Threat2CaseC
	const Board::PositionXY threat1End = Board::PositionXY( 5, 6 );

	ThreatFinder::ThreatLocation threatContainer;

	// Add threat, then check score.
	threatContainer.m_ThreatDetails.m_BeginningThreat = threat1Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat1End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 5, 3 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 5, 4 );
	threatContainer.m_Trend = ThreatFinder::HORIZONTAL;

	// Empty board at the begining, so 0 score.
    CPPUNIT_ASSERT( 0 == m_pBoardScoreHuman->GetScore() );

	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_C );

	// A new move is a part of threat1 (newMove belongs to the threat).
	const Board::PositionXY newMove = Board::PositionXY( 5, 5 );
	CPPUNIT_ASSERT( 1 == m_pBoardScoreHuman->RemoveThreats( newMove ) );
    CPPUNIT_ASSERT( 0 == m_pBoardScoreHuman->GetScore() );
}

void BoardScoreTest::RemoveThreatsRemoveAllTest2()
{
	// Add some threats of the same kind, then remove all of it separately.
	const Board::PositionXY threat1Begin = Board::PositionXY( 3, 2 ); // assume its Threat2CaseC
	const Board::PositionXY threat1End = Board::PositionXY( 3, 6 );

	const Board::PositionXY threat2Begin = Board::PositionXY( 7, 2 ); // assume its Threat2CaseC
	const Board::PositionXY threat2End = Board::PositionXY( 7, 6 );

	const Board::PositionXY threat3Begin = Board::PositionXY( 3, 9 ); // assume its Threat2CaseC
	const Board::PositionXY threat3End = Board::PositionXY( 7, 9 );

	ThreatFinder::ThreatLocation threatContainer;

	// Add threat, then remove it. The score shall be 0.
	threatContainer.m_ThreatDetails.m_BeginningThreat = threat1Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat1End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 3, 3 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 3, 4 );
	threatContainer.m_Trend = ThreatFinder::HORIZONTAL;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_C );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat2Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat2End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 7, 3 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 7, 5 );
	threatContainer.m_Trend = ThreatFinder::HORIZONTAL;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_C );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat3Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat3End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 4, 9 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 5, 9 );
	threatContainer.m_Trend = ThreatFinder::VERTICAL;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_C );

	// Each a new move belongs exactly to one of the previously added threat.
	Board::PositionXY newMovesList[] = { Board::PositionXY( 3, 5 ), Board::PositionXY( 7, 4 ), Board::PositionXY( 6, 9 ) };

	// Remove sequentially.
	for( uint32_t i = 0; i < NUMELEM(newMovesList); ++i )
	{
		CPPUNIT_ASSERT( 1 == m_pBoardScoreHuman->RemoveThreats( newMovesList[i] ) );
	}

    CPPUNIT_ASSERT( 0 == m_pBoardScoreHuman->GetScore() );
}

void BoardScoreTest::RemoveThreatsRemoveAllTest3()
{
	// Add some threats of the same kind, then remove at one.

	// Add some threats of the same kind, then remove all of it separately.
	const Board::PositionXY threat1Begin = Board::PositionXY( 2, 2 ); // assume its Threat3CaseA
	const Board::PositionXY threat1End = Board::PositionXY( 6, 6 );

	const Board::PositionXY threat2Begin = Board::PositionXY( 2, 4 ); // assume its Threat3CaseA
	const Board::PositionXY threat2End = Board::PositionXY( 6, 4 );

	const Board::PositionXY threat3Begin = Board::PositionXY( 2, 6 ); // assume its Threat3CaseA
	const Board::PositionXY threat3End = Board::PositionXY( 6, 2 );

	const Board::PositionXY threat4Begin = Board::PositionXY( 4, 2 ); // assume its Threat3CaseA
	const Board::PositionXY threat4End = Board::PositionXY( 4, 6 );

	const uint32_t numberOfThreats = 4;

	ThreatFinder::ThreatLocation threatContainer;

	// Add threat, then remove it. The socre shall be 0.
	threatContainer.m_ThreatDetails.m_BeginningThreat = threat1Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat1End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 2, 2 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 6, 6 );
	threatContainer.m_Trend = ThreatFinder::FALLING;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_A );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat2Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat2End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 2, 4 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 6, 4 );
	threatContainer.m_Trend = ThreatFinder::VERTICAL;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_A );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat3Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat3End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 2, 6 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 6, 2 );
	threatContainer.m_Trend = ThreatFinder::RISING;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_A );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat4Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat4End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 4, 2 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 4, 6 );
	threatContainer.m_Trend = ThreatFinder::HORIZONTAL;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_A );


	// List contains move but none of them belongs to any threat.
	Board::PositionXY newMovesList1[] = { Board::PositionXY( 1, 7 ), Board::PositionXY( 3, 2 ), Board::PositionXY( 4, 1 ), Board::PositionXY( 7, 7 ) };

	// Try remove. Nothing should happen.
	for( uint32_t i = 0; i < NUMELEM(newMovesList1); ++i )
	{
		CPPUNIT_ASSERT( 0 == m_pBoardScoreHuman->RemoveThreats( newMovesList1[i] ) );
	}

	// List contains move that belongs to all threat.
	Board::PositionXY newMovesList2[] = { Board::PositionXY( 4, 4 ) };
	for( uint32_t i = 0; i < NUMELEM(newMovesList2); ++i )
	{
		CPPUNIT_ASSERT( numberOfThreats == m_pBoardScoreHuman->RemoveThreats( newMovesList2[i] ) );
	}

    CPPUNIT_ASSERT( 0 == m_pBoardScoreHuman->GetScore() );
}

void BoardScoreTest::RemoveThreatsPartiallyRemoveTest()
{
	// Threats are put of various kind.
	// Some of them are removed.

	// Define threats' locations.
	const Board::PositionXY threat1Begin = Board::PositionXY( 1, 1 ); // assume its Threat4CaseA
	const Board::PositionXY threat1End = Board::PositionXY( 5, 1 );
	const uint32_t threat1Value = Score::THREAT_4_CASE_A_SCORE;

	const Board::PositionXY threat2Begin = Board::PositionXY( 1, 1 ); // assume its Threat4CaseB
	const Board::PositionXY threat2End = Board::PositionXY( 1, 6 );
	const uint32_t threat2Value = Score::THREAT_4_CASE_B_SCORE;

	const Board::PositionXY threat3Begin = Board::PositionXY( 1, 4 ); // assume its Threat4CaseC
	const Board::PositionXY threat3End = Board::PositionXY( 5, 0 );
	const uint32_t threat3Value = Score::THREAT_4_CASE_C_SCORE;

	const Board::PositionXY threat4Begin = Board::PositionXY( 3, 5 ); // assume its Threat3CaseB
	const Board::PositionXY threat4End = Board::PositionXY( 6, 8 );
	const uint32_t threat4Value = Score::THREAT_3_CASE_B_SCORE;

	const Board::PositionXY threat5Begin = Board::PositionXY( 7, 1 ); // assume its Threat2CaseA
	const Board::PositionXY threat5End = Board::PositionXY( 7, 4 );
	const uint32_t threat5Value = Score::THREAT_2_CASE_A_SCORE;

	const uint32_t threatValueSum = threat1Value + threat2Value + threat3Value + threat4Value + threat5Value;

	ThreatFinder::ThreatLocation threatContainer;

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat1Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat1End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 1, 1 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 5, 1 );
	threatContainer.m_Trend = ThreatFinder::VERTICAL;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_4_CASE_A );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat2Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat2End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 1, 1 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 1, 6 );
	threatContainer.m_Trend = ThreatFinder::HORIZONTAL;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_4_CASE_B );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat3Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat3End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 1, 4 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 5, 0 );
	threatContainer.m_Trend = ThreatFinder::RISING;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_4_CASE_C );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat4Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat4End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 3, 5 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 6, 8 );
	threatContainer.m_Trend = ThreatFinder::FALLING;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_B );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat5Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat5End;
	threatContainer.m_ThreatDetails.m_MyPawns[ 0 ] = Board::PositionXY( 7, 1 );
	threatContainer.m_ThreatDetails.m_MyPawns[ 1 ] = Board::PositionXY( 7, 4 );
	threatContainer.m_Trend = ThreatFinder::HORIZONTAL;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_A );

	// List contains move that belong to at least one threat.
	Board::PositionXY newMovesList[] = { Board::PositionXY( 1, 1 ), Board::PositionXY( 3, 2 ), Board::PositionXY( 6, 8 ), Board::PositionXY( 7, 1 ) };

	CPPUNIT_ASSERT( threatValueSum == m_pBoardScoreHuman->GetScore() );

	// Score that will be subtracted after each move from newMovesList.
	const uint32_t score[] = { threat1Value + threat2Value, threat3Value, threat4Value, threat5Value };

	for( uint32_t i = 0, val = threatValueSum; i < NUMELEM(newMovesList); ++i )
	{
		CPPUNIT_ASSERT( 1 <= m_pBoardScoreHuman->RemoveThreats( newMovesList[i] ) );
		val -= score[i];
		CPPUNIT_ASSERT( val == m_pBoardScoreHuman->GetScore() );
	}
}

void BoardScoreTest::GetNumberOfRecognizedThreatTest()
{
	// Define five threats and then, add them to BoardScore, and check that
	// four threat are exist.

	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . o . . . . .|
	//	1 |. . x . . . . . x . . . . . .|
	//	2 |. . x x . . . x . . . . . . .|
	//	3 |. . . . . . x . . . . . . . .|
	//	4 |. . . . . x . . . . . . . . .|
	//	5 |. . . . . . . . . . . x x x x|
	//	6 |. . . . . . . . . . . . . . .|

	const uint32_t numberOfThreatsTHREAT_2_CASE_C = 2;
	const uint32_t numberOfThreatsTHREAT_3_CASE_A = 1;
	const uint32_t numberOfThreatsTHREAT_4_CASE_B = 2;

	// Define 4 threats' locations.
	const Board::PositionXY threat1Begin = Board::PositionXY( 2, 1 ); // assume its THREAT_2_CASE_C
	const Board::PositionXY threat1End = Board::PositionXY( 2, 5 );

	const Board::PositionXY threat2Begin = Board::PositionXY( 0, 2 ); // assume its THREAT_2_CASE_A
	const Board::PositionXY threat2End = Board::PositionXY( 6, 2 );

	const Board::PositionXY threat3Begin = Board::PositionXY( 0, 1 ); // assume its THREAT_3_CASE_A
	const Board::PositionXY threat3End = Board::PositionXY( 5, 6);

	const Board::PositionXY threat4Begin = Board::PositionXY( 0, 9 ); // assume its THREAT_4_CASE_B
	const Board::PositionXY threat4End = Board::PositionXY( 6, 3 );

	const Board::PositionXY threat5Begin = Board::PositionXY( 5, 0 ); // assume its THREAT_4_CASE_B
	const Board::PositionXY threat5End = Board::PositionXY( 5, 4 );


	ThreatFinder::ThreatLocation threatContainer;

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat1Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat1End;
	threatContainer.m_Trend = ThreatFinder::HORIZONTAL;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_C );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat2Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat2End;
	threatContainer.m_Trend = ThreatFinder::VERTICAL;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_C );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat3Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat3End;
	threatContainer.m_Trend = ThreatFinder::FALLING;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_A );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat4Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat4End;
	threatContainer.m_Trend = ThreatFinder::RISING;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_4_CASE_B );

	threatContainer.m_ThreatDetails.m_BeginningThreat = threat5Begin;
	threatContainer.m_ThreatDetails.m_EndThreat = threat5End;
	threatContainer.m_Trend = ThreatFinder::RISING;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_4_CASE_B );

	CPPUNIT_ASSERT( numberOfThreatsTHREAT_2_CASE_C == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C) );
	CPPUNIT_ASSERT( numberOfThreatsTHREAT_3_CASE_A == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A) );
	CPPUNIT_ASSERT( numberOfThreatsTHREAT_4_CASE_B == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B) );
}

void BoardScoreTest::GetExGapsTest1()
{
	//	  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	// 0 |x . x . . . . . . . . x . . x|
	// 1 |. . . o . x x . . o . . . . .|
	// 2 |. . . . . . . . . . . . . . .|
	// 3 |. x x . . . . . . x x . . . .|
	// 4 |. . . . . . . . . . . . . . .|
	// 5 |x x x . . . . . . . . . . . .|
	// 6 |. . . . . . . . . . . . . . .|
	// 7 |. . . . . . . . x x x . . . .|
	// 8 |. . . . . . . . . . . . . . .|
	// 9 |. . . . . . . . . . . . . . .|

	ThreatFinder::ThreatLocation threatContainer;
	ThreatFinder::ThreatUpDetails &threatUpDetails = threatContainer.m_ThreatDetails;

	// Define 7 threats' locations.
	// 1. assume its THREAT_2_CASE_B
	threatUpDetails.m_ExtGaps[ 0 ] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	threatUpDetails.m_ExtGaps[ 1 ] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_B );

	threatUpDetails.m_ExtGaps[ 0 ] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	threatUpDetails.m_ExtGaps[ 1 ] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_B );

	// 2. assume its THREAT_2_CASE_C
	threatUpDetails.m_ExtGaps[ 0 ] = Board::PositionXY( 1, 8 );
	threatUpDetails.m_ExtGaps[ 1 ] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_C );

	// 3. assume its THREAT_2_CASE_A
	threatUpDetails.m_ExtGaps[ 0 ] = Board::PositionXY( 3, 4 );
	threatUpDetails.m_ExtGaps[ 1 ] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_A );

	threatUpDetails.m_ExtGaps[ 0 ] = Board::PositionXY( 3, 12 );
	threatUpDetails.m_ExtGaps[ 1 ] = Board::PositionXY( 3, 7 );
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_A );

	// 4. assume its THREAT_3_CASE_B
	threatUpDetails.m_ExtGaps[ 0 ] = Board::PositionXY( 5, 4 );
	threatUpDetails.m_ExtGaps[ 1 ] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_B );

	// 5. assume its THREAT_3_CASE_A
	threatUpDetails.m_ExtGaps[ 0 ] = Board::PositionXY( 7, 12 );
	threatUpDetails.m_ExtGaps[ 1 ] = Board::PositionXY( 7, 6 );
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_A );

	//-------------------------------------------------------------------------------------
	std::vector<Board::PositionField> exGaps;
	uint32_t expectedExGapsNumber = 0;

	// 1. Check THREAT_2_CASE_B:
	expectedExGapsNumber = 0;
	m_pBoardScoreHuman->GetExGaps( exGaps, ThreatFinder::THREAT_2_CASE_B );
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );
	exGaps.clear();

	// 2. Check THREAT_2_CASE_C:
	expectedExGapsNumber = 1;
	m_pBoardScoreHuman->GetExGaps( exGaps, ThreatFinder::THREAT_2_CASE_C );
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );
	exGaps.clear();

	// 3. Check THREAT_2_CASE_A:
	expectedExGapsNumber = 3;
	m_pBoardScoreHuman->GetExGaps(exGaps, ThreatFinder::THREAT_2_CASE_A);
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );
	Board::PositionXY expectedExGapsList2A[] = { Board::PositionXY( 3, 4 ), Board::PositionXY( 3, 12 ), Board::PositionXY( 3, 7 ) };
	for( uint32_t i = 0; i < NUMELEM( expectedExGapsList2A); ++i )
	{
		const Board::PositionField positionField( m_pGomokuBoard->GetSize(), expectedExGapsList2A[ i ] );
		const bool isOnGapsList = Checker( positionField, exGaps );
		CPPUNIT_ASSERT( isOnGapsList == true );
	}
	exGaps.clear();

	// 4. Check THREAT_3_CASE_B:
	expectedExGapsNumber = 1;
	m_pBoardScoreHuman->GetExGaps(exGaps, ThreatFinder::THREAT_3_CASE_B);
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );
	exGaps.clear();

	// 5. Check THREAT_3_CASE_A:
	expectedExGapsNumber = 2;
	m_pBoardScoreHuman->GetExGaps(exGaps, ThreatFinder::THREAT_3_CASE_A);
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );
	exGaps.clear();
}

void BoardScoreTest::GetGapsUniqueTest1()
{
	//	.                      1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . x x . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|

	ThreatFinder::ThreatLocation threatContainer;
	ThreatFinder::ThreatUpDetails &threatUpDetails = threatContainer.m_ThreatDetails;

	const vector<Board::PositionXY> expected2A {
		Board::PositionXY( 1, 3 ),
		Board::PositionXY( 1, 4 ),
		Board::PositionXY( 1, 5 ),
		Board::PositionXY( 1, 8 ),
		Board::PositionXY( 1, 9 ),
		Board::PositionXY( 1, 10 )
	};

	// normal side
	threatUpDetails.m_Gaps[ 0 ] = Board::PositionXY( 1, 8 );
	threatUpDetails.m_Gaps[ 1 ] = Board::PositionXY( 1, 9 );
	threatUpDetails.m_Gaps[ 2 ] = Board::PositionXY( 1, 10 );

	// symmetric side
	threatUpDetails.m_Gaps[ ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES/2 + 0 ] = Board::PositionXY( 1, 3 );
	threatUpDetails.m_Gaps[ ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES/2 + 1 ] = Board::PositionXY( 1, 4 );
	threatUpDetails.m_Gaps[ ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES/2 + 2 ] = Board::PositionXY( 1, 5 );

	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_2_CASE_A );

	// Check gaps.
	std::vector<Board::PositionField> gaps;
	m_pBoardScoreHuman->GetGapsUnique( gaps, ThreatFinder::THREAT_2_CASE_A );
	const uint32_t expectedSize2A = expected2A.size();
	const uint32_t size2A = gaps.size();
	CPPUNIT_ASSERT( expectedSize2A == size2A );

	for ( vector< Board::PositionField >::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1 )
	{
		const Board::PositionXY xy = Board::PositionXY( m_pGomokuBoard->GetSize(), *it1 );
		CPPUNIT_ASSERT( IsOntheList( xy, expected2A ) );
	}
	gaps.clear();
}

void BoardScoreTest::GetGapsNonUniqueTest1()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . x . . . . . . . . . . . .|
	//3 |. . . x . . . . . . . . . . .|
	//4 |. . . . x . . . . . . . . . .|
	//5 |. . . . . . x x x . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	ThreatFinder::ThreatLocation threatContainer;
	ThreatFinder::ThreatUpDetails &threatUpDetails = threatContainer.m_ThreatDetails;

	const vector<Board::PositionXY> expected3A {
		Board::PositionXY( 0, 0 ),
		Board::PositionXY( 1, 1 ),
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 5, 4 ),
	    // Board::PositionXY( 5, 5 ), //doubled
		Board::PositionXY( 5, 9 ),
		Board::PositionXY( 5, 10 )
	};

	// 1. Add first threat.
	// a.normal side
	threatUpDetails.m_Gaps[ 0 ] = Board::PositionXY( 5, 5 );
	threatUpDetails.m_Gaps[ 1 ] = Board::PositionXY( 6, 6 );

	// b.symmetric side
	threatUpDetails.m_Gaps[ ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES/2 + 0 ] = Board::PositionXY( 0, 0 );
	threatUpDetails.m_Gaps[ ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES/2 + 1 ] = Board::PositionXY( 1, 1 );
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_A );
	threatUpDetails.ClearAll();

	// 2. Add second threat.
	// a.normal side
	threatUpDetails.m_Gaps[ 0 ] = Board::PositionXY( 5, 9 );
	threatUpDetails.m_Gaps[ 1 ] = Board::PositionXY( 5, 10 );

	// b.symmetric side
	threatUpDetails.m_Gaps[ ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES/2 + 0 ] = Board::PositionXY( 5, 4 );
	threatUpDetails.m_Gaps[ ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES/2 + 1 ] = Board::PositionXY( 5, 5 );
	m_pBoardScoreHuman->AddThreats( threatContainer, ThreatFinder::THREAT_3_CASE_A );
	threatUpDetails.ClearAll();

	// 3. Check gaps.
	std::vector<Board::PositionField> gaps;
	m_pBoardScoreHuman->GetGapsUnique( gaps, ThreatFinder::THREAT_3_CASE_A );
	const uint32_t expectedSize3A = expected3A.size();
	const uint32_t size3A = gaps.size();
	CPPUNIT_ASSERT( expectedSize3A == size3A );

	for ( vector< Board::PositionField >::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1 )
	{
		const Board::PositionXY xy = Board::PositionXY( m_pGomokuBoard->GetSize(), *it1 );
		CPPUNIT_ASSERT( IsOntheList( xy, expected3A ) );
	}
	gaps.clear();
}

void BoardScoreTest::GetGapsDuplicatedTest1()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . x . . . . . . . . . . .|
	//2 |. . . x . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . x + . x . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . x . .|
	//8 |. . . . . . . + . . o . . . .|
	//9 |. . . . . . . . . . x . . . .|
	//10|. . . . . + . x x + . . . . .|
	//11|. . . . x . . . . . x . . . .|
	//12|. . . x . . . . . . . x . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const vector<Board::PositionXY> expected2AResult {
		Board::PositionXY( 5, 3 ),
		Board::PositionXY( 10, 5 ),
		Board::PositionXY( 10, 9 ),
		Board::PositionXY( 8, 7 )
	};

	// 2. Put moves.
	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 1, 3 ),
		Board::PositionXY( 2, 3 ),
		Board::PositionXY( 5, 2 ),
		Board::PositionXY( 5, 5),
		Board::PositionXY( 7, 12 ),
		Board::PositionXY( 9, 10 ),
		Board::PositionXY( 10, 7 ),
		Board::PositionXY( 10, 8 ),
		Board::PositionXY( 11, 4 ),
		Board::PositionXY( 11, 10 ),
		Board::PositionXY( 12, 3 ),
		Board::PositionXY( 12, 11 )
	};

	const Board::PositionXY cpuMove1 = Board::PositionXY( 8, 10 );

	for ( uint32_t i = 0; i < xyHuman.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyHuman[i] );
	}

	m_pGomokuBoard->PutMove( cpuMove1, m_pBoardScoreCpu->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, cpuMove1 );
	rScore.UpdateScore( *m_pBoardScoreCpu, cpuMove1 );

	std::vector<Board::PositionField> duplicatedGaps;
	//----------------------------------------------
	// 3. Checking.

	// 3a. Checking 2B:
	const uint32_t expectedSize2B = 0;
	m_pBoardScoreHuman->GetGapsDuplicated( duplicatedGaps, ThreatFinder::THREAT_2_CASE_B );
	const uint32_t size2B = duplicatedGaps.size();
	CPPUNIT_ASSERT( expectedSize2B == size2B );
	duplicatedGaps.clear();

	// 3b. Checking 2A:
	const uint32_t expectedSize2A = expected2AResult.size();
	m_pBoardScoreHuman->GetGapsDuplicated( duplicatedGaps, ThreatFinder::THREAT_2_CASE_A );
	const uint32_t size2A = duplicatedGaps.size();
	CPPUNIT_ASSERT( expectedSize2A == size2A );
	duplicatedGaps.clear();

	for ( vector< Board::PositionField >::const_iterator it1 = duplicatedGaps.begin(); it1 != duplicatedGaps.end(); ++it1 )
	{
		const Board::PositionXY xy = Board::PositionXY( m_pGomokuBoard->GetSize(), *it1 );
		CPPUNIT_ASSERT( IsOntheList( xy, expected2AResult ) );
	}
	duplicatedGaps.clear();
}

void BoardScoreTest::GetCommonFieldNumber1()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . x . . . . . . . . . . . .|
	//3 |. . x . . . . . . . . . . . .|
	//4 |. . x . . . . . . . . . . . .|
	//5 |. . . x . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 1;

	// 2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 2, 2 ),
		Board::PositionXY( 3, 2 ),
		Board::PositionXY( 4, 2 ),
		Board::PositionXY( 5, 3)
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber2()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . x . . . . . . . . . .|
	//3 |. . . . x . . . . . . . . . .|
	//4 |. . . . x . . . . . . . . . .|
	//5 |. . . x . x . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 2;

	// 2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 2, 4 ),
		Board::PositionXY( 3, 4 ),
		Board::PositionXY( 4, 4 ),
		Board::PositionXY( 5, 3),
		Board::PositionXY( 5, 5),
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber3()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . o . . . . . . . . .|
	//2 |. . . . . o . . . . . . . . .|
	//3 |. . . . . o . . . . . . . . .|
	//4 |. . . . x o . . . . . . . . .|
	//5 |. . . x x o . . . . . . . . .|
	//6 |. . . . x x . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 3;

	// 2. Put moves.
	vector< Board::PositionXY > xyMove1{
		Board::PositionXY( 4, 4 ),
		Board::PositionXY( 5, 4 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 5, 3),
		Board::PositionXY( 6, 5),
	};

	vector< Board::PositionXY > xyMove2{
		Board::PositionXY( 1, 5 ),
		Board::PositionXY( 2, 5 ),
		Board::PositionXY( 3, 5 ),
		Board::PositionXY( 4, 5),
		Board::PositionXY( 5, 5),
	};

	for ( uint32_t i = 0; i < xyMove1.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove1[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove1[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove1[i] );

		m_pGomokuBoard->PutMove( xyMove2[i], m_pBoardScoreCpu->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove2[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove2[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber4()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . x . . . . . . . . . . . .|
	//3 |. . x . . . x x . . . . . . .|
	//4 |. . x . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . x . . . . . . . . . . .|
	//7 |. . . . x . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 0;

	//2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 2, 2 ),
		Board::PositionXY( 3, 2 ),
		Board::PositionXY( 4, 2 ),
		Board::PositionXY( 6, 3 ),
		Board::PositionXY( 7, 4 ),
		Board::PositionXY( 3, 6 ),
		Board::PositionXY( 3, 7 ),
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber5()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . x . x . . . . . . .|
	//4 |. . . . . . x . . . . . . . .|
	//5 |. . . . . . o . . . . . . . .|
	//6 |. . . . . . x x . x . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 1;

	//2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 3, 5 ),
		Board::PositionXY( 3, 7 ),
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 6, 9 ),
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	const Board::PositionXY additional = Board::PositionXY( 5, 6 );
	m_pGomokuBoard->PutMove( additional, m_pBoardScoreCpu->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, additional );
	rScore.UpdateScore( *m_pBoardScoreCpu, additional );

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber6()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . x . . . . . . . . . .|
	//3 |. . . . x . . . . . . . . . .|
	//4 |. . . x . x . . . . . . . . .|
	//5 |. . . . x . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 4;

	//2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 2, 4 ),
		Board::PositionXY( 3, 4 ),
		Board::PositionXY( 5, 4 ),
		Board::PositionXY( 4, 3 ),
		Board::PositionXY( 4, 5 ),
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber7()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . x x x . . x . . . . . . .|
	//2 |. . . . . x . x . . . . . . .|
	//3 |. . . . . . . x . . . . . . .|
	//4 |. . . . . . . . x . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 3;

	//2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 1, 2 ),
		Board::PositionXY( 1, 3 ),
		Board::PositionXY( 1, 4 ),
		Board::PositionXY( 1, 7 ),
		Board::PositionXY( 2, 5 ),
		Board::PositionXY( 2, 7 ),
		Board::PositionXY( 3, 7 ),
		Board::PositionXY( 4, 8 ),
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber8()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . x . . . . . x . . . . .|
	//4 |. . . . x . . . x . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 0;

	//2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 3, 3 ),
		Board::PositionXY( 4, 4 ),
		Board::PositionXY( 3, 9 ),
		Board::PositionXY( 4, 8 ),
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber9()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . x . . . . . . . . .|
	//3 |. . . . x . . . . . . . . . .|
	//4 |. . . . x . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 1;

	//2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 3, 4 ),
		Board::PositionXY( 4, 4 ),
		Board::PositionXY( 2, 5 ),
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber10()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . x x . . . . . . . . . .|
	//4 |. . . x . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 3;

	//2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 3, 3 ),
		Board::PositionXY( 3, 4 ),
		Board::PositionXY( 4, 3 ),
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber11()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . x . . . . . . . . . . .|
	//3 |. . . x . . . . . . . . . . .|
	//4 |. x . . . x . . . . . . . . .|
	//5 |. . . x . . . . . . . . . . .|
	//6 |. . . x . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 4;

	//2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 2, 3 ),
		Board::PositionXY( 3, 3 ),
		Board::PositionXY( 5, 3 ),
		Board::PositionXY( 6, 3 ),
		Board::PositionXY( 4, 1 ),
		Board::PositionXY( 4, 5 ),
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::GetCommonFieldNumber12()
{
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . x x . . . . . . . . . .|
	//3 |. . . x x . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	//1. Define expectation.
	const uint32_t expectResult = 8;

	//2. Put moves.
	vector< Board::PositionXY > xyMove{
		Board::PositionXY( 2, 3 ),
		Board::PositionXY( 2, 4 ),
		Board::PositionXY( 3, 3 ),
		Board::PositionXY( 3, 4 ),
	};

	for ( uint32_t i = 0; i < xyMove.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyMove[i], m_pBoardScoreHuman->GetPlayer() );
		rScore.UpdateScore( *m_pBoardScoreHuman, xyMove[i] );
		rScore.UpdateScore( *m_pBoardScoreCpu, xyMove[i] );
	}

	CPPUNIT_ASSERT( expectResult == m_pBoardScoreHuman->GetCommonFieldNumber( ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A ) );
}

void BoardScoreTest::RealGapsTest1()
{
	// Functional test: Test aims to test real gaps form real threats.

	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |+ . . . . . . . . . . . . . .|
	//1 |. + . . . . . . . . . . . . .|
	//2 |. . x . . . . . . . . . . . .|
	//3 |. . . x . . . . . . o . . . .|
	//4 |. . . . x . . . . . x . . . .|
	//5 |. . . . + + x x x + + . . . .|
	//6 |. . . . . . + . . . x . . . .|
	//7 |. . . . . . . . . . + . . . .|
	//8 |. . . . . . . . . . + . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . + x + + + x + . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	ThreatFinder::ThreatLocation threatContainer;
	ThreatFinder::ThreatUpDetails &threatUpDetails = threatContainer.m_ThreatDetails;

	//1. Put move.
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 2, 2 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 3, 3 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 4, 4 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 6 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 5, 6 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 7 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 5, 7 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 8 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 5, 8 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 10 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 4, 10 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 6, 10 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 6, 10 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 12, 4 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 12, 4 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 12, 8 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 12, 8 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 10 ), Board::PLAYER_B );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 3, 10 ) );

	//2. Expectation list of:
	// -2B gaps.
	const vector<Board::PositionXY> expected2BGapsALL {
		Board::PositionXY( 5, 10 ),
		Board::PositionXY( 7, 10 ),
		Board::PositionXY( 8, 10 )
	};
	const vector<Board::PositionXY> expected2BExGaps {
		Board::PositionXY( 8, 10 )
	};

	// -2AA gaps.
	const vector<Board::PositionXY> expected2AAGapsALL {
		Board::PositionXY( 12, 3 ),
		Board::PositionXY( 12, 5 ),
		Board::PositionXY( 12, 6 ),
		Board::PositionXY( 12, 7 ),
		Board::PositionXY( 12, 9 )
	};
	const vector<Board::PositionXY> expected2AAExGaps {
		Board::PositionXY( 12, 6 )
	};

	// -3A gaps.
	const vector<Board::PositionXY> expected3AGapsALL {
		Board::PositionXY( 0, 0 ),
		Board::PositionXY( 1, 1 ),
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 5, 4 ),
		//Board::PositionXY( 5, 5 ), doubled
		Board::PositionXY( 5, 9 ),
		Board::PositionXY( 5, 10 )
	};
	const vector<Board::PositionXY> expected3AExGaps {
		Board::PositionXY( 0, 0 ),
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 5, 4 ),
		Board::PositionXY( 5, 10 )
	};

	// 3. Checking:
	std::vector<Board::PositionField> gaps;
	//----------------------------------------------
		// a. 2B unique gaps.
	m_pBoardScoreHuman->GetGapsUnique( gaps, ThreatFinder::THREAT_2_CASE_B );
	const uint32_t expectedSize2BUnique = expected2BGapsALL.size();
	const uint32_t size2BUnique = gaps.size();
	CPPUNIT_ASSERT( expectedSize2BUnique == size2BUnique );

	for ( vector< Board::PositionField >::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1 )
	{
		const Board::PositionXY xy = Board::PositionXY( m_pGomokuBoard->GetSize(), *it1 );
		CPPUNIT_ASSERT( IsOntheList( xy, expected2BGapsALL ) );
	}
	gaps.clear();

		// b. 2B extend gaps.
	m_pBoardScoreHuman->GetExGaps( gaps, ThreatFinder::THREAT_2_CASE_B );
	const uint32_t expectedSize2BExtended = expected2BExGaps.size();
	const uint32_t size2BExtended = gaps.size();
	CPPUNIT_ASSERT( expectedSize2BExtended == size2BExtended );

	for ( vector< Board::PositionField >::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1 )
	{
		const Board::PositionXY xy = Board::PositionXY( m_pGomokuBoard->GetSize(), *it1 );
		CPPUNIT_ASSERT( IsOntheList( xy, expected2BExGaps ) );
	}
	gaps.clear();
	//----------------------------------------------

	// a. 2AA unique gaps.
	m_pBoardScoreHuman->GetGapsUnique( gaps, ThreatFinder::THREAT_2_CASE_AA );
	const uint32_t expectedSize2AAUnique = expected2AAGapsALL.size();
	const uint32_t size2AAUnique = gaps.size();
	CPPUNIT_ASSERT( expectedSize2AAUnique == size2AAUnique );

	for ( vector< Board::PositionField >::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1 )
	{
		const Board::PositionXY xy = Board::PositionXY( m_pGomokuBoard->GetSize(), *it1 );
		CPPUNIT_ASSERT( IsOntheList( xy, expected2AAGapsALL ) );
	}
	gaps.clear();

		// b. 2AA extend gaps.
	m_pBoardScoreHuman->GetExGaps( gaps, ThreatFinder::THREAT_2_CASE_AA );
	const uint32_t expectedSize2AAExtended = expected2AAExGaps.size();
	const uint32_t size2AAExtended = gaps.size();
	CPPUNIT_ASSERT( expectedSize2AAExtended == size2AAExtended );

	for ( vector< Board::PositionField >::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1 )
	{
		const Board::PositionXY xy = Board::PositionXY( m_pGomokuBoard->GetSize(), *it1 );
		CPPUNIT_ASSERT( IsOntheList( xy, expected2AAExGaps ) );
	}
	gaps.clear();
	//----------------------------------------------

	// a. 3A unique gaps.
	m_pBoardScoreHuman->GetGapsUnique( gaps, ThreatFinder::THREAT_3_CASE_A );
	const uint32_t expectedSize3AUnique = expected3AGapsALL.size();
	const uint32_t size3AUnique = gaps.size();
	CPPUNIT_ASSERT( expectedSize3AUnique == size3AUnique );

	for ( vector< Board::PositionField >::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1 )
	{
		const Board::PositionXY xy = Board::PositionXY( m_pGomokuBoard->GetSize(), *it1 );
		CPPUNIT_ASSERT( IsOntheList( xy, expected3AGapsALL ) );
	}
	gaps.clear();

		// b. 3A extend gaps.
	m_pBoardScoreHuman->GetExGaps( gaps, ThreatFinder::THREAT_3_CASE_A );
	const uint32_t expectedSize3AExtended = expected3AExGaps.size();
	const uint32_t size3AExtended = gaps.size();
	CPPUNIT_ASSERT( expectedSize3AExtended == size3AExtended );

	for ( vector< Board::PositionField >::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1 )
	{
		const Board::PositionXY xy = Board::PositionXY( m_pGomokuBoard->GetSize(), *it1 );
		CPPUNIT_ASSERT( IsOntheList( xy, expected3AExGaps ) );
	}
	gaps.clear();
	//----------------------------------------------
}


void BoardScoreTest::RealGapsTest2()
{
	// Functional test: Test aims to test real gaps form real threats.

	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . . . . . . x . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . x . . . . . . . . .|
	//8 |. . . . x . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	//0. Preconditions.
	Score& rScore = *Score::GetInstance();

	ThreatFinder::ThreatLocation threatContainer;
	ThreatFinder::ThreatUpDetails &threatUpDetails = threatContainer.m_ThreatDetails;

	//1. Put move.
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 7 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 5, 7 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 7, 5 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 7, 5 ) );
	m_pGomokuBoard->PutMove( Board::PositionXY( 8, 4 ), m_pBoardScoreHuman->GetPlayer() );
	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 8, 4 ) );

	//2. Expectation list of:
	// -3A gaps.
	const vector<Board::PositionXY> expected3AGapsALL {
		Board::PositionXY( 4, 8 ),
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 9, 3 )
	};

	// 3. Checking:
	std::vector<Board::PositionField> gaps;
	//----------------------------------------------

	// a. 3A unique gaps.
	m_pBoardScoreHuman->GetGapsNonUnique( gaps, ThreatFinder::THREAT_3_CASE_A );
	const uint32_t expectedSize3ANonUnique = expected3AGapsALL.size();
	const uint32_t size3ANonUnique = gaps.size();
	CPPUNIT_ASSERT( expectedSize3ANonUnique == size3ANonUnique );

	for ( vector< Board::PositionField >::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1 )
	{
		const Board::PositionXY xy = Board::PositionXY( m_pGomokuBoard->GetSize(), *it1 );
		CPPUNIT_ASSERT( IsOntheList( xy, expected3AGapsALL ) );
	}
	gaps.clear();
}


// Check if provided item on the list.
static bool IsOntheList( const Board::PositionXY xy, const vector<Board::PositionXY>& vct )
{
	return std::find(vct.begin(), vct.end(), xy) != vct.end();
}
