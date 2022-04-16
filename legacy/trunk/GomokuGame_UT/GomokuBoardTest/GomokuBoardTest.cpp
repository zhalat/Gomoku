/*
 * GomokuBoardTest.cpp
 *
 *  Created on: Feb 1, 2015
 *      Author: ginar
 */
#include <assert.h>     			// for assert.
#include "GomokuBoardTest.hpp"		// for header class definition.
#include "Board.hpp"				// for Board definitions.

void GomokuBoardTest::ConstructorInvalidParameterTest()
{
	// Invalid input argument - out of scope.

	// Max valid size.
	uint32_t const maxValidSize = GomokuBoard::MAX_GOMOKU_BOARD_SIZE;

	// Min invalid size.
	uint32_t const minValidSize = maxValidSize + 1;

	// Is exception occurred.
	bool IsExceptionOccured = false;

	const GomokuBoard* pGomokuBoard = NULL;

	// Check invalid parameter.
	try {
		pGomokuBoard = new GomokuBoard( minValidSize );
	}
	catch ( const std::string& e ) {
		IsExceptionOccured = true;
	}
	catch ( ... ) {
		IsExceptionOccured = false;
	}

	CPPUNIT_ASSERT_EQUAL( true, IsExceptionOccured );
	CPPUNIT_ASSERT( NULL == pGomokuBoard );

	// Check invalid parameter.
	try {
		pGomokuBoard = new GomokuBoard( 0 );
	}
	catch ( const std::string& e ) {
		IsExceptionOccured = true;
	}
	catch ( ... ) {
		IsExceptionOccured = false;
	}

	CPPUNIT_ASSERT_EQUAL( true, IsExceptionOccured );
	CPPUNIT_ASSERT( NULL == pGomokuBoard );

	IsExceptionOccured = false;

	//Check last valid parameter
	try {
		pGomokuBoard = new GomokuBoard( maxValidSize );
	}
	catch ( const std::string& e ) {
		IsExceptionOccured = true;
	}
	catch ( ... ) {
		IsExceptionOccured = false;
	}

	CPPUNIT_ASSERT_EQUAL( false, IsExceptionOccured );
	CPPUNIT_ASSERT( NULL != pGomokuBoard );
}

void GomokuBoardTest::ConstructorConnectionCorrectnessTest()
{
	// Checking if constructor made edge connections correctly for gomoku board.
	Board::PositionField fieldA( 0 );
	Board::PositionField fieldB( 0 );

	// Check all corners.
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 1;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 6;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 7;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 2;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 12;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 30;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 5;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 4;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 10;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 11;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 2;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 3;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 6;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 30;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 30;
	fieldB.m_field = 30;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 24;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 25;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 31;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 0;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 32;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 18;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 35;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 34;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 28;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 29;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 0;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 30;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 33;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 23;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	// verges.
	fieldA.m_field = 6;
	fieldB.m_field = 6;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 0;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 1;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 7;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 13;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 12;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 11;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 17;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 3;
	fieldB.m_field = 3;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 2;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 8;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 9;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 10;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 4;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 1;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 34;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 29;
	fieldB.m_field = 29;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 22;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 23;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 28;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 34;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 18;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 24;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 30;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 34;
	fieldB.m_field = 34;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 27;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 28;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 29;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 33;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 32;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 3;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	// in the middle.
	fieldA.m_field = 7;
	fieldB.m_field = 7;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 0;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 1;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 2;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 8;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 6;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 12;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 13;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 14;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 3;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 15;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );;
	fieldA.m_field = 7;
	fieldB.m_field = 18;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 28;
	fieldB.m_field = 28;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 21;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 22;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 23;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 27;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 28;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 33;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 34;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 25;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 15;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 17;
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
}

void GomokuBoardTest::CopyConstructorTest()
{
	// Create GomokuBoard on the base of existing board.
	GomokuBoard* gboardCopy = NULL;
	gboardCopy = new GomokuBoard( static_cast< GomokuBoard& >( *m_GomokuBoard ) );
	assert( gboardCopy != NULL );

	// Check size.
	CPPUNIT_ASSERT_EQUAL( gboardCopy->GetSize(), m_GomokuBoard->GetSize() );

	// Check connections.
	Board::PositionField fieldA( 0 );
	Board::PositionField fieldB( 0 );
    CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 1;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 6;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 7;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 2;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 12;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 30;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 0;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 5;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 4;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 10;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 11;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 2;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 3;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 6;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 30;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 5;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 30;
	fieldB.m_field = 30;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 24;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 25;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 31;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 0;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 32;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 18;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 30;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 35;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 34;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 28;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 29;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 0;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 30;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 33;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 35;
	fieldB.m_field = 23;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	// verges.
	fieldA.m_field = 6;
	fieldB.m_field = 6;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 0;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 1;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 7;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 13;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 12;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 11;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 6;
	fieldB.m_field = 17;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 3;
	fieldB.m_field = 3;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 2;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 8;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 9;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 10;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 4;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 1;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 3;
	fieldB.m_field = 34;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 29;
	fieldB.m_field = 29;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 22;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 23;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 28;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 34;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 18;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 24;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 29;
	fieldB.m_field = 30;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 34;
	fieldB.m_field = 34;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 27;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 28;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 29;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 33;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 32;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 3;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 34;
	fieldB.m_field = 5;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	// in the middle.
	fieldA.m_field = 7;
	fieldB.m_field = 7;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 0;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 1;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 2;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 8;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 6;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 12;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 13;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 14;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 3;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 7;
	fieldB.m_field = 15;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB  ) );
	fieldA.m_field = 7;
	fieldB.m_field = 18;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );

	fieldA.m_field = 28;
	fieldB.m_field = 28;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 21;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 22;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 23;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 27;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 29;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 33;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 34;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 35;
	CPPUNIT_ASSERT_EQUAL( true, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 25;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 15;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
	fieldA.m_field = 28;
	fieldB.m_field = 17;
	CPPUNIT_ASSERT_EQUAL( false, gboardCopy->m_pBoardStructure->Adjacent( fieldA, fieldB ) );
}

void GomokuBoardTest::PutMoveTest()
{
	const Board::PositionXY validXY( 0, 0 );
	const Board::PositionXY invalid1XY( 5, 6 );
	const Board::PositionXY invalid2XY( 6, 5 );

	const Board::Player invalidPlayer = Board::PLAYER_EMPTY;
	const Board::Player validPlayerA = Board::PLAYER_A;
	const Board::Player validPlayerB = Board::PLAYER_B;

	// Check invalid position.
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->PutMove( invalid1XY, validPlayerA ) );
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->PutMove( invalid2XY, validPlayerB ) );

	// Check invalid player.
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->PutMove( validXY, invalidPlayer ) );

	// Check some valid moves.
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->PutMove( validXY, validPlayerA ) );
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->PutMove( Board::PositionXY( 5, 0 ), validPlayerA ) );
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->PutMove( Board::PositionXY( 0, 5 ), validPlayerA ) );
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->PutMove( Board::PositionXY( 5, 5 ), validPlayerA ) );

	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->PutMove( Board::PositionXY( 3, 0 ), validPlayerB ) );
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->PutMove( Board::PositionXY( 0, 2 ), validPlayerB ) );
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->PutMove( Board::PositionXY( 3, 2 ), validPlayerB ) );
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->PutMove( Board::PositionXY( 5, 2 ), validPlayerB ) );
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->PutMove( Board::PositionXY( 3, 5 ), validPlayerB ) );

	// Trying put move on not vacant place.

	// Try to put PlayerA to a place occuped by PlayerA.
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->PutMove( Board::PositionXY( 0, 0 ), validPlayerA ) );
	// Try to put PlayerB to a place occuped by PlayerB.
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->PutMove( Board::PositionXY( 3, 0 ), validPlayerB ) );
	// Try to put PlayerB to a place occuped by PlayerA.
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->PutMove( Board::PositionXY( 0, 0 ), validPlayerB ) );
	// Try to put PlayerA to a place occuped by PlayerB.
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->PutMove( Board::PositionXY( 3, 0 ), validPlayerA ) );
}

void GomokuBoardTest::GetMoveTest()
{
	// Define some positions.
	const Board::PositionXY xy1( 0, 0 );
	const Board::PositionXY xy2( 3, 3 );
	const Board::PositionXY xy3( 5, 5 );

	const Board::Player invalidPlayer = Board::PLAYER_EMPTY;
	const Board::Player validPlayerA = Board::PLAYER_A;
	const Board::Player validPlayerB = Board::PLAYER_B;

	// Check if vacant fields.
	CPPUNIT_ASSERT_EQUAL( Board::PLAYER_EMPTY, m_GomokuBoard->GetMove( xy1 ) );
	CPPUNIT_ASSERT_EQUAL( Board::PLAYER_EMPTY, m_GomokuBoard->GetMove( xy2 ) );
	CPPUNIT_ASSERT_EQUAL( Board::PLAYER_EMPTY, m_GomokuBoard->GetMove( xy3 ) );

	m_GomokuBoard->PutMove( xy1, validPlayerA );
	CPPUNIT_ASSERT_EQUAL( Board::PLAYER_A, m_GomokuBoard->GetMove( xy1 ) );
	m_GomokuBoard->PutMove( xy2, validPlayerA );
	CPPUNIT_ASSERT_EQUAL( Board::PLAYER_A, m_GomokuBoard->GetMove( xy2 ) );
	m_GomokuBoard->PutMove( xy3, validPlayerB );
	CPPUNIT_ASSERT_EQUAL( Board::PLAYER_B, m_GomokuBoard->GetMove( xy3 ) );
}

void GomokuBoardTest::GetLastMoveTest()
{
	Board::PositionXY lastMove;

	// Check empty board.
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->GetLastMove( lastMove ) );

	// Check if last accepted move is available thru GetLastMove()
	m_GomokuBoard->PutMove( Board::PositionXY( 0, 0 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->GetLastMove( lastMove ) );
	CPPUNIT_ASSERT( Board::PositionXY( 0, 0 ) == lastMove );

	m_GomokuBoard->PutMove( Board::PositionXY( 2, 5), Board::PLAYER_B );
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->GetLastMove( lastMove ) );
	CPPUNIT_ASSERT( Board::PositionXY( 2, 5 ) == lastMove );

	// Not accepted move shall not modyfy last move.
	m_GomokuBoard->PutMove( Board::PositionXY( 0, 0 ), Board::PLAYER_A );
	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->GetLastMove( lastMove ) );
	CPPUNIT_ASSERT( Board::PositionXY( 2, 5 ) == lastMove );
}

void GomokuBoardTest::VacantFieldsTest()
{
	using namespace graph;

	// Clear board should has size x size vacant fields.
	const uint32_t maxVacantFields = m_GomokuBoard->GetSize() * m_GomokuBoard->GetSize();
	CPPUNIT_ASSERT_EQUAL( maxVacantFields, m_GomokuBoard->VacantFields() );

	uint32_t vacantFields = maxVacantFields;

    // Go through all fields of board and put move sequentially.
    for( Node i = 0; i < m_GomokuBoard->GetSize(); ++i )
    {
        for( Node j = 0; j < m_GomokuBoard->GetSize(); ++j )
        {
        	const Board::PositionXY xy( i, j );

        	m_GomokuBoard->PutMove( xy, Board::PLAYER_A );
        	vacantFields--;
        	CPPUNIT_ASSERT_EQUAL( vacantFields, m_GomokuBoard->VacantFields() );
        }
    }
}

void GomokuBoardTest::EdgeDistanceTest()
{
	const Board::PositionXY inTheMiddle( 4, 1 );

	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 4 ), m_GomokuBoard->EdgeDistance( inTheMiddle, Board::UP ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->EdgeDistance( inTheMiddle, Board::DOWN ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->EdgeDistance( inTheMiddle, Board::LEFT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 4 ), m_GomokuBoard->EdgeDistance( inTheMiddle, Board::RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 4 ), m_GomokuBoard->EdgeDistance( inTheMiddle, Board::UP_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->EdgeDistance( inTheMiddle, Board::UP_LEFT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->EdgeDistance( inTheMiddle, Board::DOWN_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->EdgeDistance( inTheMiddle, Board::DOWN_LEFT ) );

	const Board::PositionXY atTheCorner( 0, 5 );

	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->EdgeDistance( atTheCorner, Board::UP ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 5 ), m_GomokuBoard->EdgeDistance( atTheCorner, Board::DOWN ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 5 ), m_GomokuBoard->EdgeDistance( atTheCorner, Board::LEFT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->EdgeDistance( atTheCorner, Board::RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->EdgeDistance( atTheCorner, Board::UP_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->EdgeDistance( atTheCorner, Board::UP_LEFT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->EdgeDistance( atTheCorner, Board::DOWN_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 5 ), m_GomokuBoard->EdgeDistance( atTheCorner, Board::DOWN_LEFT ) );
}

void GomokuBoardTest::NeighbourDistanceTest()
{
	//Put some moves:
	m_GomokuBoard->PutMove( Board::PositionXY( 0, 5 ), Board::PLAYER_B );
	m_GomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );
	m_GomokuBoard->PutMove( Board::PositionXY( 3, 4 ), Board::PLAYER_A );
	m_GomokuBoard->PutMove( Board::PositionXY( 4, 1 ), Board::PLAYER_A );

	// From this vacant position distance will be computed.
	const Board::PositionXY pointOfView1( 4, 5 );

	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -1 ), m_GomokuBoard->NeighbourDistance( pointOfView1, Board::UP, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView1, Board::DOWN, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( 3 ), m_GomokuBoard->NeighbourDistance( pointOfView1, Board::LEFT, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView1, Board::RIGHT, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView1, Board::UP_RIGHT, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( 0 ), m_GomokuBoard->NeighbourDistance( pointOfView1, Board::UP_LEFT, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView1, Board::DOWN_RIGHT, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView1, Board::DOWN_LEFT, Board::PLAYER_A ) );

	// From this non-vacant position distance will be computed.
	const Board::PositionXY pointOfView2( 0, 5 );

	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView2, Board::UP, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView2, Board::DOWN, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView2, Board::LEFT, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView2, Board::RIGHT, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView2, Board::UP_RIGHT, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView2, Board::UP_LEFT, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( -2 ), m_GomokuBoard->NeighbourDistance( pointOfView2, Board::DOWN_RIGHT, Board::PLAYER_A ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< int32_t >( 3 ), m_GomokuBoard->NeighbourDistance( pointOfView2, Board::DOWN_LEFT, Board::PLAYER_A ) );
}

void GomokuBoardTest::InRowTest()
{
	//Put some moves:
	m_GomokuBoard->PutMove( Board::PositionXY( 0, 0 ), Board::PLAYER_B );
	m_GomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_B );
	m_GomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_B );
	m_GomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );
	m_GomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_B );
	m_GomokuBoard->PutMove( Board::PositionXY( 5, 5 ), Board::PLAYER_B );
	m_GomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_A );
	m_GomokuBoard->PutMove( Board::PositionXY( 4, 3 ), Board::PLAYER_A );
	m_GomokuBoard->PutMove( Board::PositionXY( 5, 3 ), Board::PLAYER_A );

	const Board::PositionXY pointOfView1( 0, 0 );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView1, Board::UP ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView1, Board::DOWN ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView1, Board::LEFT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView1, Board::RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView1, Board::UP_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView1, Board::UP_LEFT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 3 ), m_GomokuBoard->InRow( pointOfView1, Board::DOWN_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView1, Board::DOWN_LEFT ) );

	const Board::PositionXY pointOfView2( 3, 3 );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 2 ), m_GomokuBoard->InRow( pointOfView2, Board::UP ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 3 ), m_GomokuBoard->InRow( pointOfView2, Board::DOWN ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView2, Board::LEFT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView2, Board::RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView2, Board::UP_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView2, Board::UP_LEFT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView2, Board::DOWN_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 1 ), m_GomokuBoard->InRow( pointOfView2, Board::DOWN_LEFT ) );

	// Point of view form vacant field.
	const Board::PositionXY pointOfView3( 3, 2 );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->InRow( pointOfView3, Board::UP ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->InRow( pointOfView3, Board::DOWN ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->InRow( pointOfView3, Board::LEFT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->InRow( pointOfView3, Board::RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->InRow( pointOfView3, Board::UP_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->InRow( pointOfView3, Board::UP_LEFT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->InRow( pointOfView3, Board::DOWN_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< uint32_t >( 0 ), m_GomokuBoard->InRow( pointOfView3, Board::DOWN_LEFT ) );
}

void GomokuBoardTest::IsOnEdgeTest()
{
	// Define some positions.
	const Board::PositionXY xyEdgeUp( 0, 2 );
	const Board::PositionXY xyEdgeDown( 5, 2 );
	const Board::PositionXY xyEdgeLeft( 2, 0 );
	const Board::PositionXY xyEdgeRight( 2, 5 );
	const Board::PositionXY xyEdgeCornerUpLeft( 0, 0 );
	const Board::PositionXY xyEdgeCornerUpRight( 0, 5 );
	const Board::PositionXY xyEdgeCornerDownLeft( 5, 0 );
	const Board::PositionXY xyEdgeCornerDownRight( 5, 5 );
	const Board::PositionXY xyEdgeInTheMiddle( 3, 3 );

	CPPUNIT_ASSERT_EQUAL( Board::EDGE_UP, m_GomokuBoard->IsOnEdge( xyEdgeUp ) );
	CPPUNIT_ASSERT_EQUAL( Board::EDGE_DOWN, m_GomokuBoard->IsOnEdge( xyEdgeDown ) );
	CPPUNIT_ASSERT_EQUAL( Board::EDGE_LEFT, m_GomokuBoard->IsOnEdge( xyEdgeLeft ) );
	CPPUNIT_ASSERT_EQUAL( Board::EDGE_RIGHT, m_GomokuBoard->IsOnEdge(xyEdgeRight ) );
	CPPUNIT_ASSERT_EQUAL( Board::CORNER_UP_LEFT, m_GomokuBoard->IsOnEdge( xyEdgeCornerUpLeft ) );
	CPPUNIT_ASSERT_EQUAL( Board::CORNER_UP_RIGHT, m_GomokuBoard->IsOnEdge( xyEdgeCornerUpRight ) );
	CPPUNIT_ASSERT_EQUAL( Board::CORNER_DOWN_LEFT, m_GomokuBoard->IsOnEdge( xyEdgeCornerDownLeft ) );
	CPPUNIT_ASSERT_EQUAL( Board::CORNER_DOWN_RIGHT, m_GomokuBoard->IsOnEdge( xyEdgeCornerDownRight ) );
	CPPUNIT_ASSERT_EQUAL( Board::EDGE_NONE, m_GomokuBoard->IsOnEdge( xyEdgeInTheMiddle ) );
}

void GomokuBoardTest::GoDirectionTest()
{
	// Check position on corner.
	const Board::PositionXY xyCorner( 0, 5 );

	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->CanIGo( xyCorner, Board::UP ) );
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->CanIGo( xyCorner, Board::UP_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->CanIGo( xyCorner, Board::DOWN_RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->CanIGo( xyCorner, Board::RIGHT ) );
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->CanIGo( xyCorner, Board::UP_LEFT ) );

	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->CanIGo( xyCorner, Board::LEFT ) );
	Board::PositionXY xyCornerLeft( xyCorner );
	m_GomokuBoard->GoDirection( xyCornerLeft, Board::LEFT );
	CPPUNIT_ASSERT( Board::PositionXY( 0, 4 ) == xyCornerLeft );

	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->CanIGo( xyCorner, Board::DOWN ) );
	Board::PositionXY xyCornerDown( xyCorner );
	m_GomokuBoard->GoDirection( xyCornerDown, Board::DOWN );
	CPPUNIT_ASSERT( Board::PositionXY( 1, 5 ) == xyCornerDown );

	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->CanIGo( xyCorner, Board::DOWN_LEFT ) );
	Board::PositionXY xyCornerDownLeft( xyCorner );
	m_GomokuBoard->GoDirection( xyCornerDownLeft, Board::DOWN_LEFT );
	CPPUNIT_ASSERT( Board::PositionXY( 1, 4 ) == xyCornerDownLeft );

	// Check position on board frame.
	const Board::PositionXY xyFrame( 3, 0 );

	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->CanIGo( xyFrame, Board::LEFT ) );
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->CanIGo( xyFrame, Board::DOWN_LEFT ) );
	CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->CanIGo( xyFrame, Board::UP_LEFT ) );

	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->CanIGo( xyFrame, Board::UP ) );
	Board::PositionXY xyFrameUp( xyFrame );
	m_GomokuBoard->GoDirection( xyFrameUp, Board::UP );
	CPPUNIT_ASSERT( Board::PositionXY( 2, 0 ) == xyFrameUp );

	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->CanIGo( xyFrame, Board::UP_RIGHT ) );
	Board::PositionXY xyFrameUpRight( xyFrame );
	m_GomokuBoard->GoDirection( xyFrameUpRight, Board::UP_RIGHT );
	CPPUNIT_ASSERT( Board::PositionXY( 2, 1 ) == xyFrameUpRight );

	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->CanIGo( xyFrame, Board::RIGHT ) );
	Board::PositionXY xyFrameRight( xyFrame );
	m_GomokuBoard->GoDirection( xyFrameRight, Board::RIGHT );
	CPPUNIT_ASSERT( Board::PositionXY( 3, 1 ) == xyFrameRight );

	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->CanIGo( xyFrame, Board::DOWN_RIGHT ) );
	Board::PositionXY xyFrameDownRight( xyFrame );
	m_GomokuBoard->GoDirection( xyFrameDownRight, Board::DOWN_RIGHT );
	CPPUNIT_ASSERT( Board::PositionXY( 4, 1 ) == xyFrameDownRight );

	CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->CanIGo( xyFrame, Board::DOWN ) );
	Board::PositionXY xyFrameDown( xyFrame );
	m_GomokuBoard->GoDirection( xyFrameDown, Board::DOWN );
	CPPUNIT_ASSERT( Board::PositionXY( 4, 0 ) == xyFrameDown );
}

void GomokuBoardTest::RemoveMoveTest()
{
	const Board::PositionXY xy1( 0, 0 );
	const Board::PositionXY xy2( 1, 1 );
	const Board::PositionXY vacant( 2, 2 );

	const Board::Player validPlayerA = Board::PLAYER_A;
	const Board::Player validPlayerB = Board::PLAYER_B;

	// Put some moves.
    m_GomokuBoard->PutMove( xy1, validPlayerA );
    m_GomokuBoard->PutMove( xy2, validPlayerB );

    // Remove sequentally all of them.
    CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->RemoveMove( xy1 ) );
    CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->RemoveMove( xy2 ) );

    // Trying removing vacant field.
    CPPUNIT_ASSERT_EQUAL( false, m_GomokuBoard->RemoveMove( vacant ) );
}

void GomokuBoardTest::RemoveNLastMoveTest()
{
	const Board::Player playerA = Board::PLAYER_A;
	const uint32_t cntrA = 4;
	const Board::PositionXY xyA1( 0, 0 );
	const Board::PositionXY xyA2( 1, 1 );
	const Board::PositionXY xyA3( 2, 2 );
	const Board::PositionXY xyA4( 3, 3 );


	const Board::Player playerB = Board::PLAYER_B;
	const uint32_t cntrB = 3;
	const Board::PositionXY xyB1( 0, 5 );
	const Board::PositionXY xyB2( 1, 5 );
	const Board::PositionXY xyB3( 2, 5 );

	// Put some moves.
	const uint32_t cntrEmpty = 0;
    CPPUNIT_ASSERT_EQUAL( cntrEmpty, m_GomokuBoard->GetMoveNumber() );
    m_GomokuBoard->PutMove( xyA1, playerA );
    m_GomokuBoard->PutMove( xyA2, playerA );
    m_GomokuBoard->PutMove( xyA3, playerA );
    m_GomokuBoard->PutMove( xyA4, playerA );
    m_GomokuBoard->PutMove( xyB1, playerB );
    m_GomokuBoard->PutMove( xyB2, playerB );
    m_GomokuBoard->PutMove( xyB3, playerB );

    CPPUNIT_ASSERT_EQUAL( cntrA + cntrB, m_GomokuBoard->GetMoveNumber() );

    // Remove all playerB moves.
    CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->RemoveNLastMove( cntrB ) );
    CPPUNIT_ASSERT_EQUAL( cntrA, m_GomokuBoard->GetMoveNumber() );
    // Remove all playerA moves.
    CPPUNIT_ASSERT_EQUAL( true, m_GomokuBoard->RemoveNLastMove( cntrA ) );
    CPPUNIT_ASSERT_EQUAL( cntrEmpty, m_GomokuBoard->GetMoveNumber() );
}

void GomokuBoardTest::OppositePlayerTest()
{
	const Board::Player playerA = Board::PLAYER_A;
	const Board::Player playerB = Board::PLAYER_B;

	CPPUNIT_ASSERT_EQUAL( playerB , m_GomokuBoard->OppositePlayer( playerA ) );
	CPPUNIT_ASSERT_EQUAL( playerA , m_GomokuBoard->OppositePlayer( playerB ) );
}

void GomokuBoardTest::GetFirstMoveTest()
{
	uint32_t moveCntr = 0;

	// No move on board.
	CPPUNIT_ASSERT( 0 == m_GomokuBoard->GetMoveNumber() );
	Board::PositionXY firstMove;
	CPPUNIT_ASSERT( false == m_GomokuBoard->GetFirstMove(firstMove) );

	m_GomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_B ); moveCntr++;
	m_GomokuBoard->PutMove( Board::PositionXY( 5, 5 ), Board::PLAYER_B ); moveCntr++;
	m_GomokuBoard->PutMove( Board::PositionXY( 2, 3 ), Board::PLAYER_A ); moveCntr++;

	CPPUNIT_ASSERT( moveCntr == m_GomokuBoard->GetMoveNumber() );
	CPPUNIT_ASSERT( true == m_GomokuBoard->GetFirstMove(firstMove) );
	CPPUNIT_ASSERT( firstMove == Board::PositionXY( 4, 4 ) );
}

void GomokuBoardTest::GetMoveTestFail()
{
#warning "How tests method that shoud assert."
//	const Board::PositionXY invalid1XY( 6, 5 );
//	const Board::PositionXY invalid2XY( 5, 6 );
//
//	// Out of the board. Assert expected.
//	m_GomokuBoard->GetMove( invalid1XY );
//	m_GomokuBoard->GetMove( invalid2XY );
	CPPUNIT_ASSERT(false);
}

