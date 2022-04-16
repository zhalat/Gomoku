/*
 * ScoreTest.cpp
 *
 *  Created on: 29 may, 2016
 *      Author: zby
 */
#include <assert.h>     		// for assert.
#include <algorithm>    		// std::find
#include <ctime>
#include "AlphaBetaTest.hpp"
#include "BoardScore.hpp"
#include "ThreatsBloodRelation.hpp"
#include "PriorityQueue.hpp"
#include "MinMax.hpp"
#include "VectorUnique.hpp"

#define NUMELEM( x )    ( sizeof( x )/sizeof( x[ 0 ] ) )

// Point beyond the board. Useful for initialization.
const Board::PositionXY XY_OUT_OF_BOARD = Board::PositionXY( Board::PositionXY::INVALID_FIELD, Board::PositionXY::INVALID_FIELD );

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

void AlphaBetaTest::GenerateCandTestEmptyBoard()
{
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	pAlphaBeta->SetInitialPlayer( Board::PLAYER_A );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// Empty board - empty candidate.
	pAlphaBeta->BoardScoreCopyInitUT();
	vector< Board::PositionField > candidate = pAlphaBeta->GenerateCand();
	CPPUNIT_ASSERT( 0 == candidate.size() );
}

void AlphaBetaTest::GenerateCandTestCorner()
{
    // -----------------------
    //  | x | . |   |   |   |
    // -----------------------
    //  | . | . |   |   |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------

	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	pAlphaBeta->SetInitialPlayer( Board::PLAYER_A );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// Put move into the corner.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 0 ), Board::PLAYER_A );

	// Corner has only 3 neighbors.
	const vector< Board::PositionField > expected = { 1, 15, 16 };

	vector< Board::PositionField > candidate = pAlphaBeta->GenerateCand();
	CPPUNIT_ASSERT( expected == candidate );
}

void AlphaBetaTest::GenerateCandTesCenter()
{
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------
    //  |   | . | . | . |   |
    // -----------------------
    //  |   | . | x | . |   |
    // -----------------------
    //  |   | . | . | . |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------

	// Corner has only 8 neighbors.
	const vector< Board::PositionField > expected = { 64, 65, 66, 79, 81, 94, 95, 96 };

	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// Put move into the center.
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 5 ), Board::PLAYER_A );

	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	vector< Board::PositionField > candidate = pAlphaBeta->GenerateCand();
	CPPUNIT_ASSERT( expected == candidate );
}

void AlphaBetaTest::GenerateCandTesConcatenatedMoves()
{
    // -----------------------
    //  | . | . | . |   |   |
    // -----------------------
    //  | . | x | . | . |   |
    // -----------------------
    //  | . | . | x | . |   |
    // -----------------------
    //  |   | . | . | . |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// Put move into the center.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );

	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	const vector< Board::PositionField > expected = { 0, 1, 2, 15, 17, 18, 30, 31, 33, 46, 47, 48 };

	vector< Board::PositionField > candidate = pAlphaBeta->GenerateCand();

	CPPUNIT_ASSERT( expected == candidate );
}

void AlphaBetaTest::GenerateCandTesMixed1()
{
    // -----------------------
    //  | x | . | x | . |   |
    // -----------------------
    //  | . | . | o | . |   |
    // -----------------------
    //  |   | . | . | . |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------

	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// Put move into the center.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 0 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );

	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	const vector< Board::PositionField > expected = { 1, 3, 15, 16, 18, 31, 32, 33 };

	vector< Board::PositionField > candidate = pAlphaBeta->GenerateCand();

	CPPUNIT_ASSERT( expected == candidate );
}

void AlphaBetaTest::GenerateCandTesMixed2()
{
	// Put move into the corner.
    // -----------------------
    //  | x | . |   |   |   |
    // -----------------------
    //  | . | . |   |   |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 0 ), Board::PLAYER_A );

	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	const vector< Board::PositionField > expected1 = { 1, 15, 16 };
	vector< Board::PositionField > candidate1 = pAlphaBeta->GenerateCand();
	CPPUNIT_ASSERT( expected1 == candidate1 );

	// Put one additional move.
    // -----------------------
    //  | x | x | . |   |   |
    // -----------------------
    //  | . | . | . |   |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 1 ), Board::PLAYER_A );

	const vector< Board::PositionField > expected2 = { 2, 15, 16, 17 };
	vector< Board::PositionField > candidate2 = pAlphaBeta->GenerateCand();
	CPPUNIT_ASSERT( expected2 == candidate2 );
}

void AlphaBetaTest::UpdateCandTest1()
{
	// The scenario:
	// 1. On the board where are 3 move run initCandidates = GenerateCand()
	// 2. The result is initCandidates vector which contains (unique) neighborhood of each move.
	// 3. Put a new move to one of neighbor.
	// 4. The result shall be that the neighbor shall be removed from initCandidates and
	//    his unique neighbors will be added to initial initCandidates.

	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	const Board& board = m_pBoardScoreComputer->GetBoard();

	// Put move into the board.
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | . | . | . |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | . | x | . | . |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | . | . | x | . |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | . | x | . | . |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | . | . | . |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 3 ), Board::PLAYER_A );

	vector< Board::PositionField > initCandidatesStl = pAlphaBeta->GenerateCand();

	vector< Board::PositionXY > expected = { Board::PositionXY( 3, 1 ),
											 Board::PositionXY( 4, 1 ),
											 Board::PositionXY( 5, 1 )
											};

	// Check that 'initCandidates' does not include yet: {(3,1) (4,1) (5,1)}.
	for ( vector< Board::PositionXY >::const_iterator it1 = expected.begin(); it1 != expected.end(); ++it1 )
	{
		for ( vector< Board::PositionField >::const_iterator it2 = initCandidatesStl.begin(); it2 != initCandidatesStl.end(); ++it2 )
		{
			const Board& board = m_pBoardScoreComputer->GetBoard();
			const Board::PositionXY xy = Board::PositionXY( board.GetSize(), *it2 );
			const bool isDifferent = !( *it1 == xy );
			CPPUNIT_ASSERT( isDifferent );
		}
	}

	// Converts stl vector to VectorLight
	AlphaBeta::VectorUniqueType initCandidates;
    initCandidates = initCandidatesStl;

	// The position where a new move will be put.
	const Board::PositionField newMove = Board::PositionField( board.GetSize(), Board::PositionXY( 4, 2 ) );

	// Needs for UpdateCand() initialization.
	pAlphaBeta->BoardScoreCopyInitUT();

	// Put move and update candidates.
	AlphaBeta::VectorUniqueType updatedCandidats = pAlphaBeta->UpdateCand( initCandidates, newMove );

	const uint32_t initCandidatesStlSize = initCandidatesStl.size();
	const uint32_t updatedCandidatsSize = updatedCandidats.GetNumberOfElements();
	const uint32_t expectedSize = expected.size();

	// The size should be larger because of adding new neighborhood but smaller because of putting newMove move.
	CPPUNIT_ASSERT( updatedCandidatsSize == ( initCandidatesStlSize + expectedSize - 1 ) );

	// Check that 'updatedCandidats' includes neighborhood of the newMove: {(3,1) (4,1) (5,1)}.
	for ( vector< Board::PositionXY >::const_iterator pIteratorExpectation = expected.begin(); pIteratorExpectation != expected.end(); ++pIteratorExpectation )
	{
		bool isInclude = false;

		AlphaBeta::VectorUniqueTypeIterator pIterator = updatedCandidats.GetIteratorBegin();
		for ( ; pIterator != updatedCandidats.GetIteratorEnd(); ++pIterator)
		{
			const Board& board = m_pBoardScoreComputer->GetBoard();
			const Board::PositionXY xy = Board::PositionXY( board.GetSize(), *pIterator );

			if( xy == *pIteratorExpectation  )
			{
				isInclude = true;
			}
		}

		CPPUNIT_ASSERT( true == isInclude );
	}
}

void AlphaBetaTest::UpdateCandTest2()
{
	// The scenario:
	// 1. On the board where are 3 move run initCandidates = GenerateCand()
	// 2. The result is initCandidates vector which contains (unique) neighborhood of each move.
	// 3. Put a new move to one of neighbor.
	// 2. THEN add an extra move into a board just next to the neighborhood.
	// 4. The result shall be that the neighbor shall be removed from initCandidates and
	//    his unique neighbors will be added to initial initCandidates.
	// 	  The extra move should not be included as it's not vacant position.

	// 1. Initialize algorithm.
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | . | . | . |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | . | x | . | . |   |   |   |
    // ----------------------------------------------
    //  |   |   | o | . | . | x | . |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | . | x | . | . |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | . | . | . |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
	m_pGomokuBoard->PutMove( Board::PositionXY( 3, 3 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 4, 4 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 3 ), Board::PLAYER_A );


	// 3. List of expected reslut.
	vector< Board::PositionXY > expected = { Board::PositionXY( 3, 1 ),
											 Board::PositionXY( 5, 1 )
											};
	// 4. Check the results.
	vector< Board::PositionField > initCandidatesStl = pAlphaBeta->GenerateCand();
	// Check that 'initCandidates' does not include yet: {(3,1) (5,1)}.
	for ( vector< Board::PositionXY >::const_iterator it1 = expected.begin(); it1 != expected.end(); ++it1 )
	{
		for ( vector< Board::PositionField >::const_iterator it2 = initCandidatesStl.begin(); it2 != initCandidatesStl.end(); ++it2 )
		{
			const Board& board = m_pBoardScoreComputer->GetBoard();
			const Board::PositionXY xy = Board::PositionXY( board.GetSize(), *it2 );
			const bool isDifferent = !( *it1 == xy );
			CPPUNIT_ASSERT( isDifferent );
		}
	}

	// The position where an extra move will be put.
	const Board::PositionXY extraMove = Board::PositionXY( 4, 1 );
	m_pGomokuBoard->PutMove( extraMove, Board::PLAYER_B );

	// Converts stl vector to VectorLight
	AlphaBeta::VectorUniqueType initCandidates;
    initCandidates = initCandidatesStl;

	// The position where a new move will be put.
    const Board& board = m_pBoardScoreComputer->GetBoard();
	const Board::PositionField newMove = Board::PositionField( board.GetSize(), Board::PositionXY( 4, 2 ) );

	// Needs for initialize UpdateCand().
	pAlphaBeta->BoardScoreCopyInitUT();
	AlphaBeta::VectorUniqueType updatedCandidats = pAlphaBeta->UpdateCand( initCandidates, newMove );

	const uint32_t initCandidatesStlSize = initCandidatesStl.size();
	const uint32_t updatedCandidatsSize = updatedCandidats.GetNumberOfElements();
	const uint32_t expectedSize = expected.size();

	// The size should be larger because of adding new neighborhood but smaller because of putting newMove move.
	CPPUNIT_ASSERT( updatedCandidatsSize == ( initCandidatesStlSize + expectedSize - 1 ) );

	// Check that 'updatedCandidats' includes neighborhood of the newMove: {(3,1) (5,1)}.
	for ( vector< Board::PositionXY >::const_iterator pIteratorExpectation = expected.begin(); pIteratorExpectation != expected.end(); ++pIteratorExpectation )
	{
		bool isInclude = false;

		AlphaBeta::VectorUniqueTypeIterator pIterator = updatedCandidats.GetIteratorBegin();
		for ( ; pIterator != updatedCandidats.GetIteratorEnd(); ++pIterator)
		{
			const Board& board = m_pBoardScoreComputer->GetBoard();
			const Board::PositionXY xy = Board::PositionXY( board.GetSize(), *pIterator );

			if( xy == *pIteratorExpectation  )
			{
				isInclude = true;
			}
		}

		CPPUNIT_ASSERT( true == isInclude );
	}
}

void AlphaBetaTest::SwitchPlayerTest()
{
	// Prepare BoardScore.
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	pAlphaBeta->SetInitialPlayer( Board::PLAYER_B );

	// Check who's current move is.
	CPPUNIT_ASSERT( Board::PLAYER_B == pAlphaBeta->WhoIsCurrentMove() );

	pAlphaBeta->SwitchPlayer();

	// Check who's current move is.
	CPPUNIT_ASSERT( Board::PLAYER_A == pAlphaBeta->WhoIsCurrentMove() );

	pAlphaBeta->SwitchPlayer();

	// Check who's current move is.
	CPPUNIT_ASSERT( Board::PLAYER_B == pAlphaBeta->WhoIsCurrentMove() );
}

void AlphaBetaTest::GameTreeBrowsingBasicDeep2Test()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );

	// 2. Put movies to the board.
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------
    //  |   | x |   |   |   |
    // -----------------------
    //  |   |   | x |   |   |
    // -----------------------
    //  |   |   |   | x |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------

	// Update score for current state.
    vector< Board::PositionXY > xyList{ Board::PositionXY( 2, 2 ),
    									Board::PositionXY( 3, 3 ),
    									Board::PositionXY( 4, 4 )
    								   };

	m_pGomokuBoard->PutMove( xyList[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyList[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyList[0] );

	m_pGomokuBoard->PutMove( xyList[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyList[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyList[1] );

	m_pGomokuBoard->PutMove( xyList[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyList[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyList[2] );
	xyList.clear();

	// 3. List of best move.
    const vector< Board::PositionXY > expected = { Board::PositionXY( 1, 1 ), Board::PositionXY( 5, 5 ) };

	// 4. Check the results.
    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

    pAlphaBeta->SetDeep( 1U );
    const Board::PositionXY result1 = pAlphaBeta->FindBestMove(nBestMove);

    pAlphaBeta->SetDeep( 2U );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove(nBestMove);

    pAlphaBeta->SetDeep( 3U );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMove);

    pAlphaBeta->SetDeep( 4U );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove(nBestMove);

    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result1 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result2 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result3 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result4 ) );
}

void AlphaBetaTest::GameTreeBrowsingBasicDeep3Test()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );

	// 2. Put movies to the board.
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------
    //  |   | x |   |   |   |
    // -----------------------
    //  |   |   | x |   |   |
    // -----------------------
    //  |   |   |   | x |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------

	// Update score for current state.
    vector< Board::PositionXY > xyList{ Board::PositionXY( 2, 2 ),
    									Board::PositionXY( 3, 3 ),
    									Board::PositionXY( 4, 4 )
    								   };

	m_pGomokuBoard->PutMove( xyList[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyList[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyList[0] );

	m_pGomokuBoard->PutMove( xyList[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyList[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyList[1] );

	m_pGomokuBoard->PutMove( xyList[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyList[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyList[2] );
	xyList.clear();

	// 3. List of best move.
    const vector< Board::PositionXY > expected = { Board::PositionXY( 1, 1 ), Board::PositionXY( 5, 5 ) };

	// 4. Check the results.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );

	// Check depth == 1
    pAlphaBeta->SetDeep( 1 );
    const Board::PositionXY result1 = pAlphaBeta->FindBestMove(nBestMoves);

	// Check depth == 2
    pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove(nBestMoves);

	// Check depth == 3
    pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves);

    // Check if the move 'result' is on the expected list.
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result1 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result2 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result3 ) );
}

void AlphaBetaTest::GameTreeBrowsingBestMoveTest1()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );

	// 2. Put movies to the board.
    // ----------------------------------
    //  |   | o |   |   |   |   |   |   |
    // ----------------------------------
    //  |   | x |   |   |   |   | x |   |
    // ----------------------------------
    //  |   | x |   |   |   |   | x |   |
    // ----------------------------------
    //  |   | x |   |   |   |   |   |   |
    // ----------------------------------
    //  |   | x |   |   |   |   |   |   |
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
	// Update score for current state.
    vector< Board::PositionXY > xyListCpu{
										 	Board::PositionXY( 1, 1 ),
											Board::PositionXY( 2, 1 ),
											Board::PositionXY( 3, 1 ),
											Board::PositionXY( 4, 1 ),
											Board::PositionXY( 1, 6 ),
											Board::PositionXY( 2, 6 )
    								   	  };

    vector< Board::PositionXY > xyListUser{
										 	Board::PositionXY( 0, 1 )
    								   	 };

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[4] );
	m_pGomokuBoard->PutMove( xyListCpu[5], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[5] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[5] );
	m_pGomokuBoard->PutMove( xyListUser[0], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListUser[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListUser[0] );

	// 3. List of best move.
    const vector< Board::PositionXY > expected = { Board::PositionXY( 5, 1 ) };

	// 4. Check the results.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );

	// Check for depth == 1.
    pAlphaBeta->SetDeep( 1 );
    const Board::PositionXY result1 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();

	// Check for depth == 2.
    pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();

	// Check for depth == 3.
    pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();

	// Check for depth == 4.
    pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();

    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result1 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result2 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result3 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result4 ) );
}

void AlphaBetaTest::GameTreeBrowsingBestMoveTest2()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );

	// 2. Put movies to the board.
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
    //  |   |   |   | x |   | x |   |   |
    // ----------------------------------
    //  |   |   | x |   |   |   | x |   |
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
	// Update score for current state.
    vector< Board::PositionXY > xyListCpu{
											Board::PositionXY( 5, 2 ),
											Board::PositionXY( 4, 3 ),
											Board::PositionXY( 5, 6 ),
											Board::PositionXY( 4, 5 )
    								   	  };

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[3] );

	// 3. List of best move.
    const vector< Board::PositionXY > expected = { Board::PositionXY( 3, 4 ) };

	// 4. Check the results.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );

    // Set depth == 1
    pAlphaBeta->SetDeep( 1 );
    const Board::PositionXY result1 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();

    // Set depth == 2
    pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();

    // Set depth == 3
    pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();

    // Set depth == 4
    pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();

    // Check if the move 'result' is on the expected list.
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result1 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result2 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result3 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result4 ) );
}

void AlphaBetaTest::GameTreeBrowsingBestMoveTest4()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );


	// 2. Put movies to the board.
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
    //  |   |   |   |   | o |   |   |   |
    // ----------------------------------
    //  |   |   |   | o |   | o |   |   |
    // ----------------------------------
    //  |   |   |   |   | x |   |   |   |
    // ----------------------------------
    //  |   |   |   | x |   |   |   |   |
    // ----------------------------------
    //  |   |   | x |   |   |   |   |   |
    // ----------------------------------
    //  |   | x |   |   |   |   |   |   |
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
	// Update score for current state.
    vector< Board::PositionXY > xyListCpu{  Board::PositionXY( 6, 6 ),
    										Board::PositionXY( 7, 5 ),
    										Board::PositionXY( 8, 4 ),
    										Board::PositionXY( 9, 3 )
    									};

    vector< Board::PositionXY > xyListHuman{
											  Board::PositionXY( 5, 7 ),
											  Board::PositionXY( 4, 6 ),
											  Board::PositionXY( 5, 5 )
											};

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[3] );

	m_pGomokuBoard->PutMove( xyListHuman[0], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[2] );


	// 3. List of best move.
    const Board::PositionXY expected = Board::PositionXY( 10, 2 );

	// 4. Check the results.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );

    // Check depth == 1
    pAlphaBeta->SetDeep( 1 );
    const Board::PositionXY result1 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( expected == result1 );

    // Check depth == 2
    pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( expected == result2 );

    // Check depth == 3
    pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( expected == result3 );

    // Check depth == 4
    pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( expected == result4 );
}

void AlphaBetaTest::GameTreeBrowsingBestMoveTest5()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|
	//	5 |. . . . . x . . . . . . . . .|
	//	6 |. . . . . x x x o . . . . . .|
	//	7 |. . . . . . . x . . . . . . .|
	//	8 |. . . . . . . . o . . . . . .|
	//	9 |. . . . . . . o o . . . . . .|
	//	10|. . . . . . . . o . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    vector< Board::PositionXY > xyListCpu{  Board::PositionXY( 5, 5 ),
    										Board::PositionXY( 6, 5 ),
    										Board::PositionXY( 6, 6 ),
    										Board::PositionXY( 6, 7 ),
    										Board::PositionXY( 7, 7 )
    									};

    vector< Board::PositionXY > xyListHuman{
											  Board::PositionXY( 6, 8 ),
											  Board::PositionXY( 8, 8 ),
											  Board::PositionXY( 9, 8 ),
											  Board::PositionXY( 10, 8 ),
											  Board::PositionXY( 9, 7 )
											};

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[4] );

	m_pGomokuBoard->PutMove( xyListHuman[0], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[0] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[1] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[2] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[2] );
	m_pGomokuBoard->PutMove( xyListHuman[3], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[3] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[3] );
	m_pGomokuBoard->PutMove( xyListHuman[4], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[4] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[4] );


	// 3. List of best move.
	const Board::PositionXY bestMove = Board::PositionXY( 7, 8 );

	// 5. Check the results.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );

	// Find best move.
	pAlphaBeta->SetDeep( 1 );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	const Board::PositionXY result1 = pAlphaBeta->FindBestMove(nBestMoves);
	CPPUNIT_ASSERT( bestMove == result1 );
	nBestMoves.ClearAll();

	pAlphaBeta->SetDeep( 2 );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	const Board::PositionXY result2 = pAlphaBeta->FindBestMove(nBestMoves);
 	CPPUNIT_ASSERT( bestMove == result2 );
	nBestMoves.ClearAll();

	pAlphaBeta->SetDeep( 3 );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves);
	CPPUNIT_ASSERT( bestMove == result3 );
	nBestMoves.ClearAll();

	pAlphaBeta->SetDeep( 4 );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	const Board::PositionXY result4 = pAlphaBeta->FindBestMove(nBestMoves);
	CPPUNIT_ASSERT( bestMove == result4 );
	nBestMoves.ClearAll();
}

void AlphaBetaTest::GameTreeBrowsingBestMoveTest6()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . x . . . . . .|
	//5 |. . . . . . . x . . . . . . .|
	//6 |. . . . . . x . . . . . . . .|
	//7 |. . . . . x . . . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . o o o o . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|


    vector< Board::PositionXY > xyListCpu{  Board::PositionXY( 5, 7 ),
    										Board::PositionXY( 6, 6 ),
    										Board::PositionXY( 7, 5 ),
    										Board::PositionXY( 4, 8 )
    									};

    vector< Board::PositionXY > xyListHuman{
											  Board::PositionXY( 9, 7 ),
											  Board::PositionXY( 9, 8 ),
											  Board::PositionXY( 9, 9 ),
											  Board::PositionXY( 9, 10 )
											};

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[3] );

	m_pGomokuBoard->PutMove( xyListHuman[0], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[0] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[1] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[2] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[2] );
	m_pGomokuBoard->PutMove( xyListHuman[3], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[3] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[3] );

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 3, 9 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 8, 4 );

	// 4. Check the results.
	const uint32_t maxCandidatesNumber = 1U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );

	pAlphaBeta->SetDeep( 1 );
    const Board::PositionXY result1 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result1 || bestMove2 == result1 );

	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3 );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 );

}

void AlphaBetaTest::GameTreeBrowsingBestMoveTest7()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . x . . . . . . . .|
	//7 |. . . . . x . . . . . . . . .|
	//8 |. . . . x . o . . . . . . . .|
	//9 |. . . . . . . o . . . . . . .|
	//10|. . . . . . . . o . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . o . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    vector< Board::PositionXY > xyListCpu{  Board::PositionXY( 8, 4 ),
    										Board::PositionXY( 7, 5 ),
    										Board::PositionXY( 6, 6 )
    									};

    vector< Board::PositionXY > xyListHuman{
											  Board::PositionXY( 8, 6 ),
											  Board::PositionXY( 9, 7 ),
											  Board::PositionXY( 10, 8 ),
											  Board::PositionXY( 12, 10 )
											};

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );

	m_pGomokuBoard->PutMove( xyListHuman[0], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[0] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[1] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[2] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[2] );
	m_pGomokuBoard->PutMove( xyListHuman[3], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[3] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[3] );

	// 3. List of best move.
	const Board::PositionXY bestMove = Board::PositionXY( 11, 9 );

	// 4. Check the results.
	const uint32_t maxCandidatesNumber = 1U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );

	pAlphaBeta->SetDeep( 1 );
    const Board::PositionXY result1 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove == result1 );

	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove == result2  );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove == result3 );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove == result4 );
}

void AlphaBetaTest::GameTreeBrowsingBestMoveTest8()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . x . . . .|
	//5 |. . . . . . . . . o . . . . .|
	//6 |. . . . . . . . o . . . . . .|
	//7 |. . . . . . x o . . . . . . .|
	//8 |. . . . . x o o o . . . . . .|
	//9 |. . . . . x x x o . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    vector< Board::PositionXY > xyListCpu{  Board::PositionXY( 9, 5 ),
    										Board::PositionXY( 9, 6 ),
    										Board::PositionXY( 9, 7 ),
											Board::PositionXY( 8, 5 ),
											Board::PositionXY( 7, 6 ),
											Board::PositionXY( 4, 10 )
    									};

    vector< Board::PositionXY > xyListHuman{
											  Board::PositionXY( 9, 8 ),
											  Board::PositionXY( 8, 6 ),
											  Board::PositionXY( 8, 7 ),
											  Board::PositionXY( 7, 7 ),
											  Board::PositionXY( 6, 8 ),
											  Board::PositionXY( 5, 9 ),
											  Board::PositionXY( 8, 8 )
											};

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[4] );
	m_pGomokuBoard->PutMove( xyListCpu[5], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[5] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[5] );

	m_pGomokuBoard->PutMove( xyListHuman[0], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[0] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[1] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[2] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[2] );
	m_pGomokuBoard->PutMove( xyListHuman[3], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[3] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[3] );
	m_pGomokuBoard->PutMove( xyListHuman[4], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[4] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[4] );
	m_pGomokuBoard->PutMove( xyListHuman[5], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[5] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[5] );
	m_pGomokuBoard->PutMove( xyListHuman[6], m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[6] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[6]);

	// 3. List of best move & action move. Action: CPU extends it's threat creating a new at once.
	const Board::PositionXY bestMoveStage1 = Board::PositionXY( 9, 4 );
	const Board::PositionXY bestMoveStage2 = Board::PositionXY( 9, 3 );
	const Board::PositionXY humanChallenge = Board::PositionXY( 7, 8 );

	// 4. Get initial candidates.
	const uint32_t maxCandidatesNumber = 12U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2 );

    const uint32_t nBestMovesSizePart1 = nBestMoves.GetSize();
    for( uint32_t i = 0; i < nBestMovesSizePart1; ++i )
    {
        const Board::PositionXY el = nBestMoves.PopData().m_move;
        candidates.push_back( el );
    }

    // 5. Check the results stage 1.
    pAlphaBeta->SetDeep( 4U );
    nBestMoves.ClearAll();
    const Board::PositionXY result4Part1 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( result4Part1 == bestMoveStage1  );

    // 6. Made an human action.
	m_pGomokuBoard->PutMove( result4Part1, m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, result4Part1 );
	pScore->UpdateScore( *m_pBoardScoreComputer, result4Part1);

	m_pGomokuBoard->PutMove( humanChallenge, m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreHuman, humanChallenge );
	pScore->UpdateScore( *m_pBoardScoreComputer, humanChallenge);

    // 7. Get initial candidates.
	nBestMoves.ClearAll();
    candidates.clear();
	GetInitCandidatesUT( nBestMoves, 2 );

    const uint32_t nBestMovesSizePart2 = nBestMoves.GetSize();
    for( uint32_t i = 0; i < nBestMovesSizePart2; ++i )
    {
        const Board::PositionXY el = nBestMoves.PopData().m_move;
        candidates.push_back( el );
    }

    // 8. Check the results stage 2.
    nBestMoves.ClearAll();
    pAlphaBeta->SetDeep( 4U );
    const Board::PositionXY result4Part2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( result4Part2 == bestMoveStage2  );
}

void AlphaBetaTest::GameTreeBrowsingBestMoveTest9()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//		                   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . o . . . . .|
	//	4 |. . . . . . . . o . o . . . .|
	//	5 |. . . . . . . . . . . . . . .|
	//	6 |. . . . . . . . . o . . . . .|
	//	7 |. . . . x . . . . o . . . . .|
	//	8 |. . . . . x . . . . . . . . .|
	//	9 |. . . . . . . . . . . . . . .|
	//	10|. . . . . x . . . . . . . . .|
	//	11|. . . . x . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 7, 4 ),
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 10, 5 ),
		Board::PositionXY( 11, 4 ),
		Board::PositionXY( 0, 0 )
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 3, 9 ),
		Board::PositionXY( 4, 8 ),
		Board::PositionXY( 4, 10 ),
		Board::PositionXY( 6, 9 ),
		Board::PositionXY( 7, 9 )
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	//3. List of best move:
	const Board::PositionXY bestMove1 = Board::PositionXY( 4, 9 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 5, 9 );

	// 4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2 );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}

	//5. Check the results.
	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 );

	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2a || bestMove2 == result2a );
}

void AlphaBetaTest::GameTreeBrowsingBestMoveTest10()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//		                   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . x x . o . .|
	//	4 |. . . . . . . . o o . . . . .|
	//	5 |. . . . . . . . . x . . . . .|
	//	6 |. . . . . . . . x . . . . . .|
	//	7 |. . . . . . . x . . . . . . .|
	//	8 |. . . . . . o . . . . . . . .|
	//	9 |. . . . . . . . . . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . o o o . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 3, 9 ),
		Board::PositionXY( 3, 10 ),
		Board::PositionXY( 5, 9 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 7, 7 )
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 14, 4 ),
		Board::PositionXY( 14, 5 ),
		Board::PositionXY( 14, 6 ),
		Board::PositionXY( 8, 6 ),
		Board::PositionXY( 4, 11 ),
		Board::PositionXY( 4, 9 ),
		Board::PositionXY( 3, 12 )
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );
	}

	for ( uint32_t i = 0; i < xyHuman.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	//3. List of best move:
	const Board::PositionXY bestMove1 = Board::PositionXY( 4, 10 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2 );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}

	//5. Check the results.
	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result2 );
    nBestMoves.ClearAll();
}

void AlphaBetaTest::GenerateCandidateExtendGapsTest1()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Put movies to the board.
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. x x . + . . . . . . . . . .|
	//	2 |. . x . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . + . + . . . . . . . . . .|
	//	5 |. . . . . . . . . . . . . . .|
	//	6 |. . . . . . . . . . . . . . .|
	//	7 |. . . . . . . . . . . . . . .|
	//	8 |. . . . . . . . . . . . . . .|
    vector< Board::PositionXY > xyListCpu{  Board::PositionXY( 1, 1 ),
    										Board::PositionXY( 1, 2 ),
    										Board::PositionXY( 2, 2 ),
    									};

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer());
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );

	//2. Expected result list:
	const uint32_t expectedExGapsNumber = 3;
	Board::PositionXY expectedExGapsList2A[] = { Board::PositionXY( 1, 4 ),
												 Board::PositionXY( 4, 2 ),
												 Board::PositionXY( 4, 4 ) };
	//3. Find candiates.
	std::vector<Board::PositionField> exGaps;
	m_pBoardScoreComputer->GetExGaps(exGaps, ThreatFinder::THREAT_2_CASE_A);

	//4. Check the results.
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );

	for( uint32_t i = 0; i < NUMELEM( expectedExGapsList2A ); ++i )
	{
		const Board::PositionField positionField( m_pGomokuBoard->GetSize(), expectedExGapsList2A[ i ] );
		const bool isOnGapsList = Checker( positionField, exGaps );
		CPPUNIT_ASSERT( isOnGapsList == true );
	}
}

void AlphaBetaTest::GenerateCandidateExtendGapsTest2()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Put movies to the board.
	//                         1 1 1 1 1
	//     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . x . . .|
	//	1 |. x x x . + . . . . o x . . .|
	//	2 |. . . x . . . . o . o x + . .|
	//	3 |. . . . . . o x x x . + . . .|
	//	4 |. . . + . + . . o o x + . . .|
	//	5 |. . . . . . . . . x . o . . .|
	//	6 |. . . . . . . . x . . . . . .|
	//	7 |. . . . . . . o . . . . . . .|
	//	8 |. . . . . . . . . . . . . . .|
    vector< Board::PositionXY > xyListCpu{  Board::PositionXY( 0, 11 ),
    										Board::PositionXY( 1, 1 ),
    										Board::PositionXY( 1, 2 ),
    										Board::PositionXY( 1, 3 ),
    										Board::PositionXY( 1, 11 ),
    										Board::PositionXY( 2, 3 ),
    										Board::PositionXY( 2, 11 ),
    										Board::PositionXY( 3, 7 ),
    										Board::PositionXY( 3, 8 ),
    										Board::PositionXY( 3, 9 ),
    										Board::PositionXY( 4, 10 ),
    										Board::PositionXY( 5, 9 ),
    										Board::PositionXY( 6, 8 )
    									};

    vector< Board::PositionXY > xyListHuman{
		  	  	  	  	  	  	  	  	  	  Board::PositionXY( 1, 10 ),
											  Board::PositionXY( 2, 8 ),
											  Board::PositionXY( 2, 10 ),
											  Board::PositionXY( 3, 6 ),
											  Board::PositionXY( 4, 8 ),
											  Board::PositionXY( 4, 9 ),
											  Board::PositionXY( 5, 11 ),
											  Board::PositionXY( 7, 7 )
											};

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[4] );
	m_pGomokuBoard->PutMove( xyListCpu[5], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[5] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[5] );
	m_pGomokuBoard->PutMove( xyListCpu[6], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[6] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[6] );
	m_pGomokuBoard->PutMove( xyListCpu[7], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[7] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[7] );
	m_pGomokuBoard->PutMove( xyListCpu[8], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[8] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[8] );
	m_pGomokuBoard->PutMove( xyListCpu[9], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[9] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[9] );
	m_pGomokuBoard->PutMove( xyListCpu[10], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[10] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[10] );
	m_pGomokuBoard->PutMove( xyListCpu[11], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[11] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[11] );
	m_pGomokuBoard->PutMove( xyListCpu[12], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[12] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[12] );

	m_pGomokuBoard->PutMove( xyListHuman[0], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[0] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[1] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[2] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[2] );
	m_pGomokuBoard->PutMove( xyListHuman[3], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[3] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[3] );
	m_pGomokuBoard->PutMove( xyListHuman[4], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[4] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[4] );
	m_pGomokuBoard->PutMove( xyListHuman[5], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[5] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[5] );
	m_pGomokuBoard->PutMove( xyListHuman[6], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[6] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[6] );
	m_pGomokuBoard->PutMove( xyListHuman[7], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[7] );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[7] );

	// 2. Expected candidates.
	const uint32_t expectedExGapsNumber = 6;
	Board::PositionXY expectedExGapsList[] = { Board::PositionXY( 1, 5 ), Board::PositionXY( 2, 12 ), Board::PositionXY( 3, 11 ),Board::PositionXY( 4, 5 ),
											   Board::PositionXY( 4, 3 ), Board::PositionXY( 4, 11 )  };

	// 3. Get candidates.
	std::vector<Board::PositionField> exGaps;
	for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
	{
		m_pBoardScoreComputer->GetExGaps(exGaps, ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i]);
	}

	// 4. Check the results.
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );

	for( uint32_t i = 0; i < NUMELEM( expectedExGapsList ); ++i )
	{
		const Board::PositionField positionField( m_pGomokuBoard->GetSize(), expectedExGapsList[ i ] );
		const bool isOnGapsList = Checker( positionField, exGaps );
		CPPUNIT_ASSERT( isOnGapsList == true );
	}
}

void AlphaBetaTest::GenerateCandidateExtendGapsTest3()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Put movies to the board.
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. + . x x x . + . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . + . x x . + .|
	//	4 |. . . . . . . . . . . . . . .|
	//	5 |. . . . . . . . . . . . . . .|
	//	6 |. . . . . . . . . . . . . . .|
	//	7 |. . . . . . . . . . . . . . .|
	//	8 |. . . . . . . . . . . . . . .|
    vector< Board::PositionXY > xyListCpu{  Board::PositionXY( 1, 3 ),
    										Board::PositionXY( 1, 4 ),
    										Board::PositionXY( 1, 5 ),
    										Board::PositionXY( 3, 10 ),
    										Board::PositionXY( 3, 11 ),
    									 };

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[4] );

	// 2. Expected result.
	const uint32_t expectedExGapsNumber = 4;
	Board::PositionXY expectedExGapsList[] = { Board::PositionXY( 1, 1 ),
											   Board::PositionXY( 1, 7 ),
											   Board::PositionXY( 3, 8 ),
											   Board::PositionXY( 3, 13 )  };

	// 3. Get candidate.
	std::vector<Board::PositionField> exGaps;
	for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
	{
		m_pBoardScoreComputer->GetExGaps(exGaps, ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i]);
	}

	// 4. Check the results.
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );

	for( uint32_t i = 0; i < NUMELEM( expectedExGapsList ); ++i )
	{
		const Board::PositionField positionField( m_pGomokuBoard->GetSize(), expectedExGapsList[ i ] );
		const bool isOnGapsList = Checker( positionField, exGaps );
		CPPUNIT_ASSERT( isOnGapsList == true );
	}
}

void AlphaBetaTest::GenerateCandidateExtendGapsTest4()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

    // 2. Put movies to the board.
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . + + + + + . . . . . . . .|
	//	1 |. + + x x x + + . . . . . . .|
	//	2 |. . + + + + + . . + + + + . .|
	//	3 |. . . . . . . . + + x x + + .|
	//	4 |. . . . . . . . . + + + + . .|
	//	5 |. . . . . . . . . . . . . . .|
	//	6 |. . . . . . . . . . . . . . .|
	//	7 |. . . . . . . . . . . . . . .|
	//	8 |. . . . . . . . . . . . . . .|
    vector< Board::PositionXY > xyListCpu{  Board::PositionXY( 1, 3 ),
    										Board::PositionXY( 1, 4 ),
    										Board::PositionXY( 1, 5 ),
    										Board::PositionXY( 3, 10 ),
    										Board::PositionXY( 3, 11 ),
    									 };

	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[4] );

	// 2. Expectation candidate list.
	vector< Board::PositionXY > expectedCandidates = {
														   Board::PositionXY( 0, 2 ),
														   Board::PositionXY( 0, 3 ),
														   Board::PositionXY( 0, 4 ),
														   Board::PositionXY( 0, 5 ),
														   Board::PositionXY( 0, 6 ),
														   Board::PositionXY( 1, 1 ),
														   Board::PositionXY( 1, 2 ),
														   Board::PositionXY( 1, 6 ),
														   Board::PositionXY( 1, 7 ),
														   Board::PositionXY( 2, 2 ),
														   Board::PositionXY( 2, 3 ),
														   Board::PositionXY( 2, 4 ),
														   Board::PositionXY( 2, 5 ),
														   Board::PositionXY( 2, 6 ),
														   Board::PositionXY( 2, 9 ),
														   Board::PositionXY( 2, 10 ),
														   Board::PositionXY( 2, 11 ),
														   Board::PositionXY( 2, 12 ),
														   Board::PositionXY( 3, 8 ),
														   Board::PositionXY( 3, 9 ),
														   Board::PositionXY( 3, 12 ),
														   Board::PositionXY( 3, 13 ),
														   Board::PositionXY( 4, 9 ),
														   Board::PositionXY( 4, 10 ),
														   Board::PositionXY( 4, 11 ),
														   Board::PositionXY( 4, 12 )
													  };

	// 3. Get candidates.

	vector< Board::PositionField > candidate = pAlphaBeta->GenerateCand();

	// 4. Check the results.
	CPPUNIT_ASSERT( expectedCandidates.size() == candidate.size() );

	for( uint32_t i = 0; i <  expectedCandidates.size(); ++i )
	{
		Board::PositionField temp( m_pGomokuBoard->GetSize(), expectedCandidates[i]);
		const bool isOnList = Checker( temp, candidate );
		CPPUNIT_ASSERT( isOnList == true );
	}
}

void AlphaBetaTest::GenerateCandidateExtendGapsTest5()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();

	// 1. Put movies to the board.
	//    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	// 0 |. . . . . . . . . . . . . . .|
	// 1 |. . . . . . . . . . . . . . .|
	// 2 |. . . . . . . . . . . . . . .|
	// 3 |. . . . . x x . . . . . . . .|
	// 4 |. . . . . . . . . . . . . . .|
	// 5 |. . . . . . . . . . . . . . .|
	// 6 |. . . . . . . . . . . . . . .|
	// 7 |. . . . . . . . . . . . . . .|
	// 8 |. . . . . . . . . . . . . . .|
	// 9 |. . . . . . . . . . . . . . .|

    const vector< Board::PositionXY > xyListCpu{
    											  Board::PositionXY( 3, 5 ),
    										      Board::PositionXY( 3, 6 )
    									 	   };

    const vector< Board::PositionXY > xyListHuman{ Board::PositionXY( 3, 8 ) };

	m_pGomokuBoard->PutMove(xyListCpu[0], Board::PLAYER_A);
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );

	m_pGomokuBoard->PutMove(xyListCpu[1], Board::PLAYER_A);
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );

	// 2. Expected result.
	const uint32_t expectedExGapsNumberPart1 = 2;
	const uint32_t expectedExGapsNumberPart2 = 1;
	Board::PositionXY expectedExGapsList[] = { Board::PositionXY( 3, 3 ), Board::PositionXY( 3, 8 ) };

	// 3. Get candidates.
	std::vector<Board::PositionField> exGaps;
	for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
	{
		m_pBoardScoreComputer->GetExGaps(exGaps, ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i]);
	}

	// 4. Check the results.
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumberPart1 );
	for( uint32_t i = 0; i < NUMELEM( expectedExGapsList ); ++i )
	{
		const Board::PositionField positionField( m_pGomokuBoard->GetSize(), expectedExGapsList[ i ] );
		const bool isOnGapsList = Checker( positionField, exGaps );
		CPPUNIT_ASSERT( isOnGapsList == true );
	}

	// 5. Continue action.
	exGaps.clear();

	// Now human puts its own move on ex gaps position.
	m_pGomokuBoard->PutMove( xyListHuman[0], Board::PLAYER_B );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListHuman[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListHuman[0] );

	// 6. Get candidates.
	for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
	{
		m_pBoardScoreComputer->GetExGaps(exGaps, ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i]);
	}

	// 7. Check the results.
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumberPart2 );
}

void AlphaBetaTest::StalemateTest1()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputerStalmate, *m_pBoardScoreHumanStalmate );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputerStalmate->GetPlayer() );

	//	   0 1 2 3 4
	//	   _ _ _ _ _
	//	0 |x o x x x|
	//	1 |x x o x x|
	//	2 |x x x o x|
	//	3 |x x x x o|
	//	4 |o . . . o|
	//	  |_ _ _ _ _|

	// 2. Put movies to the board.
    vector< Board::PositionXY > xyListCpu{
										 	Board::PositionXY( 0, 0 ),
											Board::PositionXY( 0, 1 ),
											Board::PositionXY( 0, 2 ),
											Board::PositionXY( 0, 3 ),
											Board::PositionXY( 0, 4 ),

										 	Board::PositionXY( 1, 0 ),
											Board::PositionXY( 1, 1 ),
											Board::PositionXY( 1, 2 ),
											Board::PositionXY( 1, 3 ),
											Board::PositionXY( 1, 4 ),

										 	Board::PositionXY( 2, 0 ),
											Board::PositionXY( 2, 1 ),
											Board::PositionXY( 2, 2 ),
											Board::PositionXY( 2, 3 ),
											Board::PositionXY( 2, 4 ),

										 	Board::PositionXY( 3, 0 ),
											Board::PositionXY( 3, 1 ),
											Board::PositionXY( 3, 2 ),
											Board::PositionXY( 3, 3 ),
											Board::PositionXY( 3, 4 ),

										 	Board::PositionXY( 4, 0 ),
											Board::PositionXY( 4, 4 ),

    								   	  };
    m_pGomokuBoardStalemate->PutMove( xyListCpu[0], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[0] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[1], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[1] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[2], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[2] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[3], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[3] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[4], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[4] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[4] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[5], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[5] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[5] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[6], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[6] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[6] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[7], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[7] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[7] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[8], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[8] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[8] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[9], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[9] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[9] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[10], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[10] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[10] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[11], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[11] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[11] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[12], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[12] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[12] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[13], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[13] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[13] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[14], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[14] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[14] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[15], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[15] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[15] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[16], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[16] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[16] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[17], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[17] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[17] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[18], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[18] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[18] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[19], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[19] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[19] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[20], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[20] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[20] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[21], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[21] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[21] );

	// 3. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );

	// 4. Check result - shall not crash.
    pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves);
}

void AlphaBetaTest::StalemateTest2()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputerStalmate, *m_pBoardScoreHumanStalmate );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputerStalmate->GetPlayer() );

	// 2. Put movies to the board.
	//	   0 1 2 3 4
	//	   _ _ _ _ _
	//	0 |x o x x x|
	//	1 |x x o x x|
	//	2 |x x x o x|
	//	3 |x x x x o|
	//	4 |o o . . o|
	//	  |_ _ _ _ _|
    vector< Board::PositionXY > xyListCpu{
										 	Board::PositionXY( 0, 0 ),
											Board::PositionXY( 0, 1 ),
											Board::PositionXY( 0, 2 ),
											Board::PositionXY( 0, 3 ),
											Board::PositionXY( 0, 4 ),

										 	Board::PositionXY( 1, 0 ),
											Board::PositionXY( 1, 1 ),
											Board::PositionXY( 1, 2 ),
											Board::PositionXY( 1, 3 ),
											Board::PositionXY( 1, 4 ),

										 	Board::PositionXY( 2, 0 ),
											Board::PositionXY( 2, 1 ),
											Board::PositionXY( 2, 2 ),
											Board::PositionXY( 2, 3 ),
											Board::PositionXY( 2, 4 ),

										 	Board::PositionXY( 3, 0 ),
											Board::PositionXY( 3, 1 ),
											Board::PositionXY( 3, 2 ),
											Board::PositionXY( 3, 3 ),
											Board::PositionXY( 3, 4 ),

										 	Board::PositionXY( 4, 0 ),
										 	Board::PositionXY( 4, 1 ),
										 	Board::PositionXY( 4, 2 ),
										 	Board::PositionXY( 4, 3 ),
											Board::PositionXY( 4, 4 ),

    								   	  };
    m_pGomokuBoardStalemate->PutMove( xyListCpu[0], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[0] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[1], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[1] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[2], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[2] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[3], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[3] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[4], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[4] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[4] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[5], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[5] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[5] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[6], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[6] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[6] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[7], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[7] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[7] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[8], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[8] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[8] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[9], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[9] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[9] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[10], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[10] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[10] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[11], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[11] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[11] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[12], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[12] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[12] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[13], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[13] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[13] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[14], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[14] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[14] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[15], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[15] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[15] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[16], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[16] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[16] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[17], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[17] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[17] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[18], m_pBoardScoreComputerStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[18] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[18] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[19], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[19] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[19] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[20], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[20] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[20] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[21], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[21] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[21] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[22], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[22] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[22] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[23], m_pBoardScoreHumanStalmate->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputerStalmate, xyListCpu[23] );
	pScore->UpdateScore( *m_pBoardScoreHumanStalmate, xyListCpu[23] );

	// 3. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );

	// 4. Check result - shall not crash.
    pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves);
}

void AlphaBetaTest::PerformanceTest1()
{
	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//
	// This is the worst case as far as number potential candidate concerned.
	// It will took the most time to calculate best move.
	//
	//    					  1 1 1 1 1
	//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	// 0 |. . . . . . . . . . . . . . .|
	// 1 |. x . . x . . x . . x . . x .|
	// 2 |. . . . . . . . . . . . . . .|
	// 3 |. . . . . . . . . . . . . . .|
	// 4 |. x . . x . . x . . x . . x .|
	// 5 |. . . . . . . . . . . . . . .|
	// 6 |. . . . . . . . . . . . . . .|
	// 7 |. x . . x . . x . . x . . x .|
	// 8 |. . . . . . . . . . . . . . .|
	// 9 |. . . . . . . . . . . . . . .|
	// 10|. x . . x . . x . . x . . x .|
	// 11|. . . . . . . . . . . . . . .|
	// 12|. . . . . . . . . . . . . . .|
	// 13|. x . . x . . x . . x . . x .|
	// 14|. . . . . . . . . . . . . . .|
	//   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	// Update score for current state.
    vector< Board::PositionXY > xyListCpu{
										 	Board::PositionXY( 1, 1 ),
											Board::PositionXY( 1, 4 ),
											Board::PositionXY( 1, 7 ),
											Board::PositionXY( 1, 10 ),
											Board::PositionXY( 1, 13 ),

										 	Board::PositionXY( 4, 1 ),
											Board::PositionXY( 4, 4 ),
											Board::PositionXY( 4, 7 ),
											Board::PositionXY( 4, 10 ),
											Board::PositionXY( 4, 13 ),

										 	Board::PositionXY( 7, 1 ),
											Board::PositionXY( 7, 4 ),
											Board::PositionXY( 7, 7 ),
											Board::PositionXY( 7, 10 ),
											Board::PositionXY( 7, 13 ),

										 	Board::PositionXY( 10, 1 ),
											Board::PositionXY( 10, 4 ),
											Board::PositionXY( 10, 7 ),
											Board::PositionXY( 10, 10 ),
											Board::PositionXY( 10, 13 ),

										 	Board::PositionXY( 13, 1 ),
											Board::PositionXY( 13, 4 ),
											Board::PositionXY( 13, 7 ),
											Board::PositionXY( 13, 10 ),
											Board::PositionXY( 13, 13 ),

    								   	  };
	m_pGomokuBoard->PutMove( xyListCpu[0], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[4] );

	m_pGomokuBoard->PutMove( xyListCpu[5], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[5] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[5] );
	m_pGomokuBoard->PutMove( xyListCpu[6], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[6] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[6] );
	m_pGomokuBoard->PutMove( xyListCpu[7], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[7] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[7] );
	m_pGomokuBoard->PutMove( xyListCpu[8], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[8] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[8] );
	m_pGomokuBoard->PutMove( xyListCpu[9], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[9] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[9] );

	m_pGomokuBoard->PutMove( xyListCpu[10], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[10] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[10] );
	m_pGomokuBoard->PutMove( xyListCpu[11], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[11] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[11] );
	m_pGomokuBoard->PutMove( xyListCpu[12], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[12] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[12] );
	m_pGomokuBoard->PutMove( xyListCpu[13], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[13] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[13] );
	m_pGomokuBoard->PutMove( xyListCpu[14], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[14] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[14] );

	m_pGomokuBoard->PutMove( xyListCpu[15], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[15] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[15] );
	m_pGomokuBoard->PutMove( xyListCpu[16], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[16] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[16] );
	m_pGomokuBoard->PutMove( xyListCpu[17], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[17] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[17] );
	m_pGomokuBoard->PutMove( xyListCpu[18], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[18] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[18] );
	m_pGomokuBoard->PutMove( xyListCpu[19], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[19] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[19] );

	m_pGomokuBoard->PutMove( xyListCpu[20], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[20] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[20] );
	m_pGomokuBoard->PutMove( xyListCpu[21], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[21] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[21] );
	m_pGomokuBoard->PutMove( xyListCpu[22], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[22] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[22] );
	m_pGomokuBoard->PutMove( xyListCpu[23], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[23] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[23] );
	m_pGomokuBoard->PutMove( xyListCpu[24], m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[24] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[24] );

	// Time measure:
	clock_t t_depth1_begin = 0, t_depth1_end = 0;
	clock_t t_depth2_begin = 0, t_depth2_end = 0;
	clock_t t_depth3_begin = 0, t_depth3_end = 0;

	// 5. Check the results.
	const uint32_t maxCandidatesNumber = 1U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );


    // Check depth == 1
	t_depth1_begin = clock();
    pAlphaBeta->SetDeep( 1 );
    const Board::PositionXY result1 = pAlphaBeta->FindBestMove(nBestMoves);
    t_depth1_end = clock();
    double t_depth1_all = ((double)(t_depth1_end- t_depth1_begin)/CLOCKS_PER_SEC);
    printf("FindBestMove: depth == 1 took %f seconds to execute \n\n", t_depth1_all);

    // Check depth == 2
	t_depth2_begin = clock();
    pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove(nBestMoves);
    t_depth2_end = clock();
    double t_depth2_all = ((double)(t_depth2_end- t_depth2_begin)/CLOCKS_PER_SEC);
    printf("FindBestMove: depth == 2 took %f seconds to execute \n\n", t_depth2_all);

    // Check depth == 3
	t_depth3_begin = clock();
    pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves);
    t_depth3_end = clock();
    double t_depth3_all = ((double)(t_depth3_end- t_depth3_begin)/CLOCKS_PER_SEC);
    printf("FindBestMove: depth == 3 took %f seconds to execute \n\n", t_depth3_all);

// Results: 24.JUN.2017
//    FindBestMove: depth == 1 took 0.004000 seconds to execute
//
//    FindBestMove: depth == 2 took 0.075000 seconds to execute
//
//    FindBestMove: depth == 3 took 4.275000 seconds to execute
//
// Results: 20.JUL.2017
//    FindBestMove: depth == 1 took 0.002000 seconds to execute
//
//    FindBestMove: depth == 2 took 0.196000 seconds to execute
//
//    FindBestMove: depth == 3 took 3.927000 seconds to execute

}

void AlphaBetaTest::AnomalyReproduction1()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- (algo returned out of board move.)
	 */

	// Get singletons.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();

	// 1. Initialize algorithm.
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . o x x x o x . . . . . .|
	//3 |. . . x o o o x o . . . . . .|
	//4 |. . o . x o o . o o . . . . .|
	//5 |. o x x x o x x x o . . . . .|
	//6 |. . . o x o o o x . . o . . .|
	//7 |. . . . o x o x x x o x . . .|
	//8 |. . . . . . x x o . o x . . .|
	//9 |. . . . . o x o x . x x . . .|
	//10|. . . . . o . . . . . o . . .|
	//11|. . . . . . . . . . . x . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7, 7),
		Board::PositionXY(5, 7),
		Board::PositionXY(6, 8),
		Board::PositionXY(7, 9),
		Board::PositionXY(9, 11),
		Board::PositionXY(8, 6),
		Board::PositionXY(5, 6),
		Board::PositionXY(6, 4),
		Board::PositionXY(7, 5),
		Board::PositionXY(5, 3),
		Board::PositionXY(7, 8),
		Board::PositionXY(5, 8),
		Board::PositionXY(5, 4),
		Board::PositionXY(9, 8),
		Board::PositionXY(4, 4),
		Board::PositionXY(2, 4),
		Board::PositionXY(2, 6),
		Board::PositionXY(7, 11),
		Board::PositionXY(2, 5),
		Board::PositionXY(8, 11),
		Board::PositionXY(2, 8),
		Board::PositionXY(11, 11),
		Board::PositionXY(5, 2),
		Board::PositionXY(9, 6),
		Board::PositionXY(3, 3),
		Board::PositionXY(8, 7),
		Board::PositionXY(9, 10),
		Board::PositionXY(3, 7)

	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(6, 6),
		Board::PositionXY(6, 7),
		Board::PositionXY(6, 5),
		Board::PositionXY(4, 6),
		Board::PositionXY(8, 10),
		Board::PositionXY(5, 9),
		Board::PositionXY(6, 3),
		Board::PositionXY(9, 5),
		Board::PositionXY(9, 7),
		Board::PositionXY(4, 2),
		Board::PositionXY(7, 6),
		Board::PositionXY(4, 8),
		Board::PositionXY(5, 5),
		Board::PositionXY(8, 8),
		Board::PositionXY(7, 4),
		Board::PositionXY(3, 4),
		Board::PositionXY(3, 5),
		Board::PositionXY(7, 10),
		Board::PositionXY(2, 3),
		Board::PositionXY(6, 11),
		Board::PositionXY(2, 7),
		Board::PositionXY(10, 11),
		Board::PositionXY(5, 1),
		Board::PositionXY(3, 6),
		Board::PositionXY(4, 5),
		Board::PositionXY(10, 5),
		Board::PositionXY(3, 8)
	};

	for ( uint32_t i = 0; i<xyHuman.size(); ++i )
	{
		m_pGomokuBoard->PutMove(xyListCpu[i], Board::PLAYER_A);
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove(xyHuman[i], Board::PLAYER_B);
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	m_pGomokuBoard->PutMove(xyListCpu[27], Board::PLAYER_A);
	pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[27] );
	pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[27] );

	const  Board::PositionXY issue  = Board::PositionXY(4, 9);

	m_pGomokuBoard->PutMove(issue, Board::PLAYER_B);
	pScore->UpdateScore( *m_pBoardScoreComputer, issue );
	pScore->UpdateScore( *m_pBoardScoreHuman, issue );

	// 3. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2 );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 4. Check the results - shall not be out of board.
    pAlphaBeta->SetDeep( 4U );
    const Board::PositionXY result = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( XY_OUT_OF_BOARD != result );
}

void AlphaBetaTest::AnomalyReproduction2()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see GameRecord3_L2
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . x . . . . . . . .|
	//5 |. . . . . . . o . . . . . . .|
	//6 |. . . . . . x . o o . . . . .|
	//7 |. . . . . x o x x o . . . . .|
	//8 |. . . . . . . . o . x . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7,7),
		Board::PositionXY(6,6),
		Board::PositionXY(7,8),
		Board::PositionXY(7,5),
		Board::PositionXY(4,6),
		Board::PositionXY(8,10)
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(6,8),
		Board::PositionXY(8,8),
		Board::PositionXY(7,9),
		Board::PositionXY(5,7),
		Board::PositionXY(7,6),
		Board::PositionXY(6,9)
	};

	for ( uint32_t i = 0; i<xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 6, 10 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 6, 7 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 9, 7 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}

	// 5. Check the results.
	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove(nBestMoves, candidates);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3 || bestMove3 == result3 );

    const Board::PositionXY result3a = pAlphaBeta->FindBestMove(nBestMoves);
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3a || bestMove2 == result3a || bestMove3 == result3a );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 || bestMove3 == result4 );

//	pAlphaBeta->SetDeep( 5 );
//    const Board::PositionXY result5 = pAlphaBeta->FindBestMove( nBestMoves );
//    nBestMoves.ClearAll();
//    CPPUNIT_ASSERT( bestMove1 == result5 || bestMove2 == result5 || bestMove3 == result5 );
}

void AlphaBetaTest::AnomalyReproduction3()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see GameRecord7_L4
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//
	//	.                      1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . x . o . . . . .|
	//	4 |. . . . . . . o x . . . . . .|
	//	5 |. . . . . . . x . . . . . . .|
	//	6 |. . . . . . x . o x . . . . .|
	//	7 |. . . . . x . x o . . . . . .|
	//	8 |. . . . o . x o o o . . . . .|
	//	9 |. . . . o . o . x . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7,7),
		Board::PositionXY(6,6),
		Board::PositionXY(5,7),
		Board::PositionXY(9,8),
		Board::PositionXY(4,8),
		Board::PositionXY(3,7),
		Board::PositionXY(7,5),
		Board::PositionXY(8,6),
		Board::PositionXY(6,9)

	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(6,8),
		Board::PositionXY(8,8),
		Board::PositionXY(7,8),
		Board::PositionXY(8,7),
		Board::PositionXY(3,9),
		Board::PositionXY(8,9),
		Board::PositionXY(8,4),
		Board::PositionXY(9,6),
		Board::PositionXY(9,4)
	};

	for ( uint32_t i = 0; i < xyHuman.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	m_pGomokuBoard->PutMove( Board::PositionXY( 4,7 ), m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, Board::PositionXY( 4, 7 ) );
	pScore->UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 4 , 7 ) );

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 10, 4 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 10, 5 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 11, 4 );
	const Board::PositionXY bestMove4 = Board::PositionXY( 7, 4 );

	// 4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();

	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}

	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 || bestMove3 == result2 || bestMove4 == result2 );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3  || bestMove3 == result3 || bestMove4 == result3 );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves,candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4  || bestMove3 == result4 || bestMove4 == result4 );
}

void AlphaBetaTest::AnomalyReproduction4()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see GameRecord5_L4
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//
	//.                      1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . . . . . o . . . . . . . .|
	//6 |. . . . . o o x o . . . . . .|
	//7 |. . . . . . o x . x x . . . .|
	//8 |. . . . . . x o x o . . . . .|
	//9 |. . . . . . . o x . . . . . .|
	//10|. . . . . o x x x o x . . . .|
	//11|. . . . . . . . o . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7,7),
		Board::PositionXY(8,8),
		Board::PositionXY(7,9),
		Board::PositionXY(10,6),
		Board::PositionXY(8,6),
		Board::PositionXY(6,7),
		Board::PositionXY(9,8),
		Board::PositionXY(10,8),
		Board::PositionXY(10,7),
		Board::PositionXY(7,10),
		Board::PositionXY(10,10)

	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(6,8),
		Board::PositionXY(6,6),
		Board::PositionXY(7,6),
		Board::PositionXY(9,7),
		Board::PositionXY(6,5),
		Board::PositionXY(8,7),
		Board::PositionXY(5,6),
		Board::PositionXY(11,8),
		Board::PositionXY(10,5),
		Board::PositionXY(8,9),
		Board::PositionXY(10,9)
	};

	// 1. Put moves into board to create anomaly situation.
	uint32_t i;
	for ( i = 0; i < xyHuman.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 7, 11 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 9, 9 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 8, 10 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
    // Need at least 5 depth to get best move.
	pAlphaBeta->SetDeep( 5 );
    const Board::PositionXY result5a = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result5a || bestMove2 == result5a || bestMove3 == result5a );

	pAlphaBeta->SetDeep( 5);
    const Board::PositionXY result5 = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result5 || bestMove2 == result5 || bestMove3 == result5 );
}

void AlphaBetaTest::AnomalyReproduction5()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see GameRecord9_L4
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	.                      1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . x . . . . . .|
	//	5 |. . . . . . . x o . . . . . .|
	//	6 |. . . . x . o o o x . . . . .|
	//	7 |. . . . . . x x o o o x . . .|
	//	8 |. . . . . . . o x o x . . . .|
	//	9 |. . . . . . x o x x x o . . .|
	//	10|. . . . . . . . o . o . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7,7),
		Board::PositionXY(8,8),
		Board::PositionXY(6,9),
		Board::PositionXY(5,7),
		Board::PositionXY(6,4),
		Board::PositionXY(7,6),
		Board::PositionXY(4,8),
		Board::PositionXY(9,10),
		Board::PositionXY(9,8),
		Board::PositionXY(9,9),
		Board::PositionXY(9,6),
		Board::PositionXY(8,10),
		Board::PositionXY(7,11)
		//Board::PositionXY(3,7)
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(6,8),
		Board::PositionXY(6,6),
		Board::PositionXY(7,9),
		Board::PositionXY(6,7),
		Board::PositionXY(5,8),
		Board::PositionXY(7,8),
		Board::PositionXY(8,9),
		Board::PositionXY(7,10),
		Board::PositionXY(8,7),
		Board::PositionXY(9,11),
		Board::PositionXY(9,7),
		Board::PositionXY(10,10),
		Board::PositionXY(10,8)
	};

	for ( uint32_t i = 0; i < xyHuman.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 8,6 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 8,12 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 11,9 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4U );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();

	// a. Best strategy is:
	const bool defend = bestMove1 == result4 || bestMove2 == result4 || bestMove3 == result4;

	// b. Increasing itself attack:
	m_pGomokuBoard->PutMove( result4, m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, result4 );
	pScore->UpdateScore( *m_pBoardScoreHuman, result4 );
	const bool attack = ( 0 < m_pBoardScoreComputer->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_4_CASE_A ) ) ||
			 	 	    ( 0 < m_pBoardScoreComputer->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_4_CASE_C ) ) ||
						( 0 < m_pBoardScoreComputer->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_4_CASE_B ) ) ||
						( 0 < m_pBoardScoreComputer->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_3_CASE_A ) ) ||
						( 0 < m_pBoardScoreComputer->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_3_CASE_C ) );

    CPPUNIT_ASSERT( defend || attack );
}

void AlphaBetaTest::AnomalyReproduction6()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see x
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	.                      1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . o . . . . . . .|
	//	5 |. . . . . . o . . . . . . . .|
	//	6 |. . . . . . x x . . . . . . .|
	//	7 |. . . . . . o x x . . . . . .|
	//	8 |. . . . . . . x o x . . . . .|
	//	9 |. . . . . . o o o x . . . . .|
	//	10|. . . . . . . o . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(6,6),
		Board::PositionXY(6,7),
		Board::PositionXY(7,7),
		Board::PositionXY(7,8),
		Board::PositionXY(8,7),
		Board::PositionXY(8,9),
		Board::PositionXY(9,9)
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(5,6),
		Board::PositionXY(7,6),
		Board::PositionXY(9,6),
		Board::PositionXY(8,8),
		Board::PositionXY(9,7),
		Board::PositionXY(9,8),
		Board::PositionXY(10,7)
	};

	for ( uint32_t i = 0; i < xyHuman.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	Board::PositionXY additional = Board::PositionXY(4,7);
	m_pGomokuBoard->PutMove( additional, m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, additional );
	pScore->UpdateScore( *m_pBoardScoreHuman, additional );

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 6, 9 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 2 );
	const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
	nBestMoves.ClearAll();
	CPPUNIT_ASSERT( bestMove1 == result2 );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3 );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4 );

	pAlphaBeta->SetDeep( 5 );
    const Board::PositionXY result5 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result5 );
}

void AlphaBetaTest::AnomalyReproduction7()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see x
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                        1 1 1 1 1
	//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	// 0 |. . . . . . . . . . . . . . .|
	// 1 |. . . . . . . . . . . . . . .|
	// 2 |. . . . . . . . . . . . . . .|
	// 3 |. . . . . . . . . . . . . . .|
	// 4 |. . . . . . . . . . o . . . .|
	// 5 |. . . . . . . . o x . . . . .|
	// 6 |. . . . . . . . x . . . . . .|
	// 7 |. . . . . . o x . . . . . . .|
	// 8 |. . . . . o x o x . . . . . .|
	// 9 |. . . . . o . . x . . . . . .|
	// 10|. . . . . . . . . . . . . . .|
	// 11|. . . . . . . . . . . . . . .|
	// 12|. . . . . . . . . . . . . . .|
	// 13|. . . . . . . . . . . . . . .|
	// 14|. . . . . . . . . . . . . . .|
	//   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7,7),
		Board::PositionXY(8,6),
		Board::PositionXY(6,8),
		Board::PositionXY(9,8),
		Board::PositionXY(8,8),
		Board::PositionXY(5,9),
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(7,6),
		Board::PositionXY(8,7),
		Board::PositionXY(9,5),
		Board::PositionXY(8,5),
		Board::PositionXY(5,8),
		Board::PositionXY(4,10),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 6, 7 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 4, 9 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 9, 4 );
	const Board::PositionXY bestMove4 = Board::PositionXY( 10, 8 );
	const Board::PositionXY bestMove5 = Board::PositionXY( 7, 8 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 || bestMove3 == result2 || bestMove4 == result2 || bestMove5 == result2 );

	pAlphaBeta->SetDeep( 3 );
	const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
	nBestMoves.ClearAll();
	CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3 || bestMove3 == result3 || bestMove4 == result3 || bestMove5 == result3 );

    pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 || bestMove3 == result4 || bestMove4 == result4 || bestMove5 == result4 );

	pAlphaBeta->SetDeep( 5 );
    const Board::PositionXY result5 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result5 || bestMove2 == result5 || bestMove3 == result5 || bestMove4 == result5 || bestMove5 == result5 );
}

void AlphaBetaTest::AnomalyReproduction8()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see x
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	                       1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |o . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . o . . . . . . .|
	//	4 |. . . . . . . x . . . . . . .|
	//	5 |. . . . . . x x . . . . . . .|
	//	6 |. . . . . . o x . x . . . . .|
	//	7 |. . . . . . o x o . . . . . .|
	//	8 |. . . . x o o o . x . . . . .|
	//	9 |. . . . . . o . o . . . . . .|
	//	10|. . . . . . x o . x . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7,7),
		Board::PositionXY(5,7),
		Board::PositionXY(6,7),
		Board::PositionXY(4,7),
		Board::PositionXY(8,9),
		Board::PositionXY(5,6),
		Board::PositionXY(10,6),
		Board::PositionXY(6,9),
		Board::PositionXY(8,4),
		Board::PositionXY(10,9),
		Board::PositionXY(0,0),

	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(6,6),
		Board::PositionXY(8,6),
		Board::PositionXY(8,7),
		Board::PositionXY(3,7),
		Board::PositionXY(7,6),
		Board::PositionXY(9,6),
		Board::PositionXY(7,8),
		Board::PositionXY(8,5),
		Board::PositionXY(9,8),
		Board::PositionXY(10,7),
		Board::PositionXY(8,3),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 7, 9 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 3U );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( result3 == bestMove1 );

	pAlphaBeta->SetDeep( 4U );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT(  result4 == bestMove1 );
}

void AlphaBetaTest::AnomalyReproduction9()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see GameRecord3_L2
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	.                      1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . o . . x . . .|
	//	4 |. . . . . . . . x . o . . . .|
	//	5 |. . . . . . . . x x . . . . .|
	//	6 |. . . . . . . o x . . . . . .|
	//	7 |. . . . . . o x x . . . . . .|
	//	8 |. . . . . o o x o . . . . . .|
	//	9 |. . . . . o o . . . . . . . .|
	//	10|. . . . . . x . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7,7),
		Board::PositionXY(6,8),
		Board::PositionXY(7,8),
		Board::PositionXY(5,8),
		Board::PositionXY(5,9),
		Board::PositionXY(10,6),
		Board::PositionXY(3,11),
		Board::PositionXY(4,8),
		Board::PositionXY(8,7),
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(6,7),
		Board::PositionXY(8,6),
		Board::PositionXY(7,6),
		Board::PositionXY(8,8),
		Board::PositionXY(9,6),
		Board::PositionXY(8,5),
		Board::PositionXY(4,10),
		Board::PositionXY(3,8),
		Board::PositionXY(9,5),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	const Board::PositionXY additionalX = Board::PositionXY( 2, 9 );
	m_pGomokuBoard->PutMove( additionalX, m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, additionalX );
	pScore->UpdateScore( *m_pBoardScoreHuman, additionalX );

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 9, 4 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 10, 3 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 9, 7 );
	const Board::PositionXY bestMove4 = Board::PositionXY( 9, 3 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3 || bestMove3 == result3 || bestMove4 == result3 );
    nBestMoves.ClearAll();

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 || bestMove3 == result4 || bestMove4 == result4 );
    nBestMoves.ClearAll();
}

void AlphaBetaTest::AnomalyReproduction10()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see GameRecord_case1
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	                       1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . x . . . . . . . . . . .|
	//	4 |. . . . o . . . . . . . . . .|
	//	5 |. . . . . x . . . . . . . . .|
	//	6 |. . . . . . x x . . . . . . .|
	//	7 |. . . . . . . x . . . . . . .|
	//	8 |. . . . . x o o o . . . . . .|
	//	9 |. . . . . . . o . . . . . . .|
	//	10|. . . . . . o . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7,7),
		Board::PositionXY(6,6),
		Board::PositionXY(5,5),
		Board::PositionXY(3,3),
		Board::PositionXY(6,7),
		Board::PositionXY(8,5)
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(8,6),
		Board::PositionXY(8,8),
		Board::PositionXY(9,7),
		Board::PositionXY(4,4),
		Board::PositionXY(8,7),
		Board::PositionXY(10,6)
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 11, 5 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 7, 9 );

	// 4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2  );
    nBestMoves.ClearAll();

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3  );
    nBestMoves.ClearAll();

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4  );
    nBestMoves.ClearAll();
}

void AlphaBetaTest::AnomalyReproduction11()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see GameRecord_case2
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . x . . . . . . . . . . .|
	//4 |. . . . o . . . . . . . . . .|
	//5 |. . . . o x . x x . . . . . .|
	//6 |. . . . . . x o . . . . . . .|
	//7 |. . . . . . o x . . . . . . .|
	//8 |. . . . . . . o o . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7,7),
		Board::PositionXY(6,6),
		Board::PositionXY(5,5),
		Board::PositionXY(3,3),
		Board::PositionXY(5,8),
		Board::PositionXY(5,7),
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(7,6),
		Board::PositionXY(6,7),
		Board::PositionXY(8,8),
		Board::PositionXY(4,4),
		Board::PositionXY(8,7),
		Board::PositionXY(5,4),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	// 3. List of best move.
	const Board::PositionXY bestMove1 = Board::PositionXY( 4, 3 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 6, 5 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 9, 8 );
	const Board::PositionXY bestMove4 = Board::PositionXY( 5, 6 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 || bestMove3 == result2 || bestMove4 == result2 );
    nBestMoves.ClearAll();

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3 || bestMove3 == result3 || bestMove4 == result3 );
    nBestMoves.ClearAll();

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 || bestMove3 == result4 || bestMove4 == result4 );
    nBestMoves.ClearAll();

	pAlphaBeta->SetDeep( 5 );
    const Board::PositionXY result5 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result5 || bestMove2 == result5 || bestMove3 == result5 || bestMove4 == result5 );
    nBestMoves.ClearAll();
}

void AlphaBetaTest::OpeningBoardTest1()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- Smoke test, how if algorithm doesn't fail in first move.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . . . . . . . . .|
	//7 |. . . . . . . o . . . . . . .|
	//8 |. . . . . . . . . . . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	nBestMoves.ClearAll();

	// a. Put first move.
	const Board::PositionXY firstMove = Board::PositionXY( 7, 7 );
	m_pGomokuBoard->PutMove( firstMove, m_pBoardScoreComputer->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, firstMove );
	pScore->UpdateScore( *m_pBoardScoreHuman, firstMove );

	pAlphaBeta->SetDeep( 5 );
    const Board::PositionXY result1 = pAlphaBeta->FindBestMove( nBestMoves );

	// b. Put second move.
	const Board::PositionXY secondMove = Board::PositionXY( 7, 6 );
	m_pGomokuBoard->PutMove( secondMove, m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, secondMove );
	pScore->UpdateScore( *m_pBoardScoreHuman, secondMove );

	pAlphaBeta->SetDeep( 5 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves );
}

void AlphaBetaTest::FinishWinnerActionsTest1()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- Algorithm shall ending his winner action.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . . . . . . . . . .|
	//5 |. . . . . . . . . . . . . . .|
	//6 |. . . . . . . o . . . . . . .|
	//7 |. . . . . . . x o . . . . . .|
	//8 |. . . . . . x . x o . . . . .|
	//9 |. . . . . . . . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(6,7),
		Board::PositionXY(7,8),
		Board::PositionXY(8,9)
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(7,7),
		Board::PositionXY(8,6),
		Board::PositionXY(8,8)
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	//3. List of best move:
	const Board::PositionXY bestMove1 = Board::PositionXY( 5, 6 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 9, 10 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 1 );
    const Board::PositionXY result1 = pAlphaBeta->FindBestMove( nBestMoves );
	nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result1 || bestMove2 == result1 );

	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves );
	nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves );
	nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3 );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves );
	nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 );

	pAlphaBeta->SetDeep( 5 );
    const Board::PositionXY result5 = pAlphaBeta->FindBestMove( nBestMoves );
	nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result5 || bestMove2 == result5 );

	pAlphaBeta->SetDeep( 1 );
    const Board::PositionXY result1b = pAlphaBeta->FindBestMove( nBestMoves, candidates);
	nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result1b || bestMove2 == result1b );

	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2b = pAlphaBeta->FindBestMove( nBestMoves, candidates);
	nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2b || bestMove2 == result2b );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3b = pAlphaBeta->FindBestMove( nBestMoves, candidates);
	nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3b || bestMove2 == result3b );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4b = pAlphaBeta->FindBestMove( nBestMoves, candidates);
	nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4b || bestMove2 == result4b );

	pAlphaBeta->SetDeep( 5 );
    const Board::PositionXY result5b = pAlphaBeta->FindBestMove( nBestMoves, candidates);
	nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result5b || bestMove2 == result5b );
}

void AlphaBetaTest::IssueTest1()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see Issue1.png. Algorithm shall block
	 * adversary's winning move
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . o o . .|
	//4 |. . . . . . . . . . . x . . .|
	//5 |. . . . . . . . . . x x . . .|
	//6 |. . . . . . o x o x o x . . .|
	//7 |. . . . . . o x x x o x . . .|
	//8 |. . . o x x x o x o x o . . .|
	//9 |. . o . . o o x x o x . . . .|
	//10|. . . . . x o o o . x . . . .|
	//11|. . . . . . . . . . o . . . .|
	//12|. . . . . . . . . o . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 7, 9 ),
		Board::PositionXY( 8, 8 ),
		Board::PositionXY( 9, 7 ),
		Board::PositionXY( 5, 11 ),
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 9, 8 ),
		Board::PositionXY( 8, 6 ),
		Board::PositionXY( 10, 5 ),
		Board::PositionXY( 8, 10 ),
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 8, 4 ),
		Board::PositionXY( 10, 10 ),
		Board::PositionXY( 9, 10 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 7, 11 ),
		Board::PositionXY( 6, 11 ),
		Board::PositionXY( 4, 11 ),
		Board::PositionXY( 5, 10 ),
		Board::PositionXY( 6, 9 )
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 10, 6 ),
		Board::PositionXY( 6, 10 ),
		Board::PositionXY( 8, 7 ),
		Board::PositionXY( 9, 6 ),
		Board::PositionXY( 10, 8 ),
		Board::PositionXY( 9, 9 ),
		Board::PositionXY( 10, 7 ),
		Board::PositionXY( 9, 5 ),
		Board::PositionXY( 8, 3 ),
		Board::PositionXY( 9, 2 ),
		Board::PositionXY( 11, 10 ),
		Board::PositionXY( 8, 9 ),
		Board::PositionXY( 7, 10 ),
		Board::PositionXY( 8, 11 ),
		Board::PositionXY( 3, 11 ),
		Board::PositionXY( 12, 9 ),
		Board::PositionXY( 3, 12 ),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	// 3. List of best moves.
	const Board::PositionXY bestMove1 = Board::PositionXY( 11, 7 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 11, 8 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 11, 9 );
	const Board::PositionXY bestMove4 = Board::PositionXY( 11, 11 );
	const Board::PositionXY bestMove5 = Board::PositionXY( 10, 9 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	//5. Find best move.
	pAlphaBeta->SetDeep( 2 );
	const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves );
	nBestMoves.ClearAll();
	CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 || bestMove3 == result2 || bestMove4 == result2 || bestMove5 == result2 );

	pAlphaBeta->SetDeep( 2 );
	const Board::PositionXY result2a = pAlphaBeta->FindBestMove( nBestMoves, candidates );
	nBestMoves.ClearAll();
	CPPUNIT_ASSERT( bestMove1 == result2a || bestMove2 == result2a || bestMove3 == result2a || bestMove4 == result2a || bestMove5 == result2a );

	pAlphaBeta->SetDeep( 3 );
	const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves );
	nBestMoves.ClearAll();
	CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3 || bestMove3 == result3 || bestMove4 == result3 || bestMove5 == result3 );

	pAlphaBeta->SetDeep( 3 );
	const Board::PositionXY result3a = pAlphaBeta->FindBestMove( nBestMoves, candidates );
	nBestMoves.ClearAll();
	CPPUNIT_ASSERT( bestMove1 == result3a || bestMove2 == result3a || bestMove3 == result3a || bestMove4 == result3a || bestMove5 == result3a );

	// Too much time consuming.
	pAlphaBeta->SetDeep( 4 );
	const Board::PositionXY result4a = pAlphaBeta->FindBestMove( nBestMoves, candidates );
	nBestMoves.ClearAll();
	CPPUNIT_ASSERT( bestMove1 == result4a || bestMove2 == result4a || bestMove3 == result4a || bestMove4 == result4a || bestMove5 == result4a );
}


void AlphaBetaTest::IssueTest3()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see Issue3.png
	 * Algorithm shall bock adversary's winning move.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	.                      1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |x . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . o . . . o . .|
	//	4 |. . . . . . . . . x . x . . .|
	//	5 |. . . . . . . . o o x . . . .|
	//	6 |. . . . . . . o o x . x . . .|
	//	7 |. . . . . . o x x x x o . . .|
	//	8 |. . . . . x . o . . . . . o .|
	//	9 |. . . . o . . . . . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 7, 9 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 7, 10 ),
		Board::PositionXY( 6, 9 ),
		Board::PositionXY( 4, 9 ),
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 5, 10 ),
		Board::PositionXY( 6, 11 ),
		Board::PositionXY( 4, 11 ),
		Board::PositionXY( 0, 0 )
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 7, 11 ),
		Board::PositionXY( 5, 8 ),
		Board::PositionXY( 9, 4 ),
		Board::PositionXY( 5, 9 ),
		Board::PositionXY( 8, 7 ),
		Board::PositionXY( 3, 8 ),
		Board::PositionXY( 3, 12 ),
		Board::PositionXY( 8, 13 )
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	//3. List of best move:
	const Board::PositionXY bestMove1 = Board::PositionXY( 4, 8 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 6, 10 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4a || bestMove2 == result4a );
}

void AlphaBetaTest::IssueTest4()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see Issue4.png
	 * Algorithm shall finds and block adversary's quick win move.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	                       1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|
	//	5 |. . . . . x o o o o x . . . .|
	//	6 |. . . . . . . o . o . . . . .|
	//	7 |. . . . . . . x x . . . . . .|
	//	8 |. . . . . . . x . . . . . . .|
	//	9 |. . . . . . . x . . . . . . .|
	//	10|. . . . . . . x . . . . . . .|
	//	11|. . . . . . . o . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 8, 7 ),
		Board::PositionXY( 9, 7 ),
		Board::PositionXY( 10, 7 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 5, 10 )
		//Board::PositionXY( 7, 9 )
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 5, 6 ),
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 11, 7 ),
		Board::PositionXY( 5, 8 ),
		Board::PositionXY( 5, 9 ),
		Board::PositionXY( 6, 9 )
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	//3. List of best move:
	const Board::PositionXY bestMove1 = Board::PositionXY( 6, 6 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4 );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4a );
}

void AlphaBetaTest::IssueTest5()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see Issue5.png
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . o . . .|
	//4 |. . . . . . o . . x x o . . .|
	//5 |. . . . . . x x o x . . . . .|
	//6 |. . . . . . . o x o . . . . .|
	//7 |. . . . . . . x o x . . . . .|
	//8 |. . . . . . o . . . x . . . .|
	//9 |. . . . . . . . . . . o . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 5, 9 ),
		Board::PositionXY( 4, 10 ),
		Board::PositionXY( 5, 6 ),
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 7, 9 ),
		Board::PositionXY( 8, 10 ),
		Board::PositionXY( 4, 9 )
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 8, 6 ),
		Board::PositionXY( 3, 11 ),
		Board::PositionXY( 4, 11 ),
		Board::PositionXY( 5, 8 ),
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 9, 11 ),
		Board::PositionXY( 6, 9 )
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	//3. List of best move:
	const Board::PositionXY bestMove1 = Board::PositionXY( 5, 10 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2  );

	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2a  );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3  );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3a  );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4 );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result4a );
}

void AlphaBetaTest::IssueTest6()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see Issue6.png
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . o . . . . . . . .|
	//5 |. . . . . . . x x . . . . . .|
	//6 |. . . . . . o o x . . . . . .|
	//7 |. . . . . . o x x x . . . . .|
	//8 |. . . . . . o . . . . . . . .|
	//9 |. . . . . . o . . . . . . . .|
	//10|. . . . . . . . . . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 7, 9 ),
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 5, 8 )
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 8, 6 ),
		Board::PositionXY( 9, 6 ),
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 6, 6 )
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	//3. List of best move:
	const Board::PositionXY bestMove = Board::PositionXY( 10, 6 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove == result2  );

	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove == result2a  );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove == result3  );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove == result3a  );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove == result4  );

	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove == result4a  );
}

void AlphaBetaTest::IssueTest7()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see Issue7.png
	 * CPU (player x) must block human dead attack. CPU must put (x,y) to not lost.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//		                   1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . x . . . . .|
	//	5 |. . . . . . . . . . o o . . .|
	//	6 |. . . . x o x x x o x o o . .|
	//	7 |. . . . . . . o o x x x o . .|
	//	8 |. . . . . . . x x o . . . . .|
	//	9 |. . . . . . . o o . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 8, 8 ),
		Board::PositionXY( 7, 9 ),
		Board::PositionXY( 8, 7 ),
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 6, 10 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 7, 10 ),
		Board::PositionXY( 7, 11 ),
		Board::PositionXY( 4, 9 ),

	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 8, 9 ),
		Board::PositionXY( 9, 7 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 9, 8 ),
		Board::PositionXY( 5, 11 ),
		Board::PositionXY( 6, 11 ),
		Board::PositionXY( 6, 9 ),
		Board::PositionXY( 6, 5 ),
		Board::PositionXY( 5, 10 ),
		Board::PositionXY( 7, 12 ),
		Board::PositionXY( 6, 12 ),

	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	Board::PositionXY additional = Board::PositionXY(6,12);
	m_pGomokuBoard->PutMove( additional, m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, additional );
	pScore->UpdateScore( *m_pBoardScoreHuman, additional );

	//3. List of best move:
	const Board::PositionXY bestMove1 = Board::PositionXY( 4, 11 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 3, 12 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 4, 12 );
	const Board::PositionXY bestMove4 = Board::PositionXY( 5, 12 );
	const Board::PositionXY bestMove5 = Board::PositionXY( 5, 9 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 || bestMove3 == result2  || bestMove4 == result2  || bestMove5 == result2 );

	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2a || bestMove2 == result2a || bestMove3 == result2a  || bestMove4 == result2a  || bestMove5 == result2a );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3 || bestMove3 == result3  || bestMove4 == result3  || bestMove5 == result3 );
}

void AlphaBetaTest::IssueTest8()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see Issue8.png
	 * CPU (player x) must block human 3A or extend its 3BC in such way to not create another 3A by human.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . o . x . . . . . .|
	//4 |. . . . . . x x o o . . . . .|
	//5 |. . . . . . o . x x o o . . .|
	//6 |. . . . . x o o o . x o o . .|
	//7 |. . . . . . o x x x . o . . .|
	//8 |. . . . . o x x x o . x . . .|
	//9 |. . . . x o . x . . . . . . .|
	//10|. . . . . . o x . . . . . . .|
	//11|. . . . . . . o . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 7, 9 ),
		Board::PositionXY( 8, 8 ),
		Board::PositionXY( 6, 10 ),
		Board::PositionXY( 9, 7 ),
		Board::PositionXY( 8, 7 ),
		Board::PositionXY( 10, 7 ),
		Board::PositionXY( 6, 5 ),
		Board::PositionXY( 9, 4 ),
		Board::PositionXY( 5, 9 ),
		Board::PositionXY( 5, 8 ),
		Board::PositionXY( 3, 8 ),
		Board::PositionXY( 8, 6 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 8, 11 ),
		Board::PositionXY( 4, 7 ),
		Board::PositionXY( 4, 6 ),
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 5, 11 ),
		Board::PositionXY( 10, 6 ),
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 11, 7 ),
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 5, 10 ),
		Board::PositionXY( 4, 9 ),
		Board::PositionXY( 6, 11 ),
		Board::PositionXY( 5, 6 ),
		Board::PositionXY( 8, 9 ),
		Board::PositionXY( 7, 11 ),
		Board::PositionXY( 4, 8 ),
		Board::PositionXY( 3, 6 ),
		Board::PositionXY( 9, 5 )
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	//3. List of best move:
	const Board::PositionXY bestMove1 = Board::PositionXY( 7, 10 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 8, 4 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 12, 8 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 || bestMove3 == result2 );

	pAlphaBeta->SetDeep( 2 );
    const Board::PositionXY result2a = pAlphaBeta->FindBestMove( nBestMoves );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2a || bestMove2 == result2a || bestMove3 == result2a );

	pAlphaBeta->SetDeep( 3 );
    const Board::PositionXY result3 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3 || bestMove3 == result3 );
}

void AlphaBetaTest::IssueTest9()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see Issue9.png
	 * Cpu should have taken block approach.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|
	//	5 |. . . . . . . . . . . . . . .|
	//	6 |. . . . . o . . . . . . . . .|
	//	7 |. . . . o x o . . . . . . . .|
	//	8 |. . . . . x . . . . . . . . .|
	//	9 |. . . . . . . . . . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 7, 5 ),
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 7, 4 ),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	const Board::PositionXY lastHumanMove = Board::PositionXY( 6, 5 );
	m_pGomokuBoard->PutMove( lastHumanMove, m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, lastHumanMove );
	pScore->UpdateScore( *m_pBoardScoreHuman, lastHumanMove );

	// 3. Must not get this move:
	Board::PositionXY worstMove = Board::PositionXY( 9, 5 );

	// 4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    nBestMoves.ClearAll();
    CPPUNIT_ASSERT( result4 != worstMove );
}

void AlphaBetaTest::IssueTest10()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- see Issue10.png
	 * Cpu didnt notice that its attack provoke human to create second thrat.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |o . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . o . x . . . .|
	//4 |. . . . . . . o o . . . . . .|
	//5 |. . . . . o . x . . . . . . .|
	//6 |. . . . . . x . o . . . . . .|
	//7 |. . . . . x o x x x o . . . .|
	//8 |. . . . x . . . x . . . . . .|
	//9 |. . . o . . . . . o . . . . .|
	//10|. . . . . . . . . . x . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY(7, 7 ),
		Board::PositionXY(5, 7 ),
		Board::PositionXY(6, 6 ),
		Board::PositionXY(8, 8 ),
		Board::PositionXY(7, 9 ),
		Board::PositionXY(10, 10 ),
		Board::PositionXY(7, 8 ),
		Board::PositionXY(7, 5 ),
		Board::PositionXY(8, 4 ),
		Board::PositionXY(3, 10 )
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY(6, 8 ),
		Board::PositionXY(4, 7 ),
		Board::PositionXY(4, 8 ),
		Board::PositionXY(5, 5 ),
		Board::PositionXY(3, 8 ),
		Board::PositionXY(9, 9 ),
		Board::PositionXY(7, 10 ),
		Board::PositionXY(7, 6 ),
		Board::PositionXY(9, 3 ),
		Board::PositionXY(0, 0 )
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
	}

	// 3. Best move:
 	const Board::PositionXY bestMove1 = Board::PositionXY( 5, 8 );

	// 4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result4  );
    nBestMoves.ClearAll();
}

void AlphaBetaTest::IssueTest17()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly-

	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                         1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . x . . . . . . .|
	//	4 |. . . . . . o x . . . . . . .|
	//	5 |. . . . . o . x o . . . . . .|
	//	6 |. . . . . . o o . x . . . . .|
	//	7 |. . . . . . . . . . . . . . .|
	//	8 |. . . . . . . . . . . . . . .|
	//	9 |. . . . . . . . . . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 4, 7 ),
		Board::PositionXY( 3, 7 ),
		Board::PositionXY( 6, 9 ),
		//Board::PositionXY( 4, 9 ),
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 6, 7 ),
		//Board::PositionXY( 5, 8 ),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );
		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );
	}
	const Board::PositionXY lastHumanMove1 = Board::PositionXY(5, 8 );
	m_pGomokuBoard->PutMove( lastHumanMove1, m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, lastHumanMove1 );
	pScore->UpdateScore( *m_pBoardScoreHuman, lastHumanMove1 );

	// 3. Best candidates:
 	const Board::PositionXY bestMove1 = Board::PositionXY( 7, 6 );

	// 4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result4 );
}

void AlphaBetaTest::IssueTest19()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly-
     *  CPU doesn't quick finish when there is 4AA threat.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	                       1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . o x x x o x . x . . . .|
	//	5 |. . . . x o o o x o . x o . .|
	//	6 |. . . . . x o x o . o x . . .|
	//	7 |. . . . . x o o o o x . . . .|
	//	8 |. . . . o x o o o x o x . . .|
	//	9 |. . . . . x x o x x o x x . .|
	//	10|. . . . . o x o o . . . . . .|
	//	11|. . . . . . . x . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 6, 5 ),
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 4, 4 ),
		Board::PositionXY( 5, 4 ),
		Board::PositionXY( 4, 5 ),
		Board::PositionXY( 9, 6 ),
		Board::PositionXY( 4, 8 ),
		Board::PositionXY( 9, 5 ),
		Board::PositionXY( 5, 8 ),
		Board::PositionXY( 4, 10 ),
		Board::PositionXY( 7, 5 ),
		Board::PositionXY( 7, 10 ),
		Board::PositionXY( 9, 11 ),
		Board::PositionXY( 9, 9 ),
		Board::PositionXY( 8, 9 ),
		Board::PositionXY( 10, 6 ),
		Board::PositionXY( 5, 11 ),
		Board::PositionXY( 9, 8 ),
		Board::PositionXY( 11, 7 ),
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 6, 11 ),
		Board::PositionXY( 9, 12 ),
		Board::PositionXY( 8, 11 ),
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 5, 6 ),
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 8, 6 ),
		Board::PositionXY( 4, 3 ),
		Board::PositionXY( 4, 7 ),
		Board::PositionXY( 5, 9 ),
		Board::PositionXY( 6, 8 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 7, 9 ),
		Board::PositionXY( 8, 10 ),
		Board::PositionXY( 8, 8 ),
		Board::PositionXY( 8, 7 ),
		Board::PositionXY( 9, 7 ),
		Board::PositionXY( 6, 10 ),
		Board::PositionXY( 10, 8 ),
		Board::PositionXY( 10, 7 ),
		Board::PositionXY( 8, 4 ),
		Board::PositionXY( 10, 5 ),
		Board::PositionXY( 5, 12 ),
		Board::PositionXY( 9, 10 ),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );

		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );
	}

	// 3. Best candidates:
 	const Board::PositionXY bestMove1 = Board::PositionXY( 7, 11 );
 	const Board::PositionXY bestMove2 = Board::PositionXY( 6, 9 );

	// 4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}
	nBestMoves.ClearAll();

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
    const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 );
}

void AlphaBetaTest::IssueTest16()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly-
	 * CPU must be aware that human is going to extend its 3B and 3A threat in such way
	 * to create eventually double 3A at one stone.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	                       1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |x . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . o . . . . . . . . .|
	//	5 |. . . . o x x o . . . . . . .|
	//	6 |. o . o x x o . . . . . . . .|
	//	7 |. . x o o o x . . . . . . . .|
	//	8 |. . . x . . . . . . . . . . .|
	//	9 |. . . x x . . . . . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . o . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 6, 5 ),
		Board::PositionXY( 5, 6 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 7, 2 ),
		Board::PositionXY( 8, 3 ),
		Board::PositionXY( 9, 4 ),
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 9, 3 ),
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 5, 4 ),
		Board::PositionXY( 4, 5 ),
		Board::PositionXY( 7, 4 ),
		Board::PositionXY( 6, 3 ),
		Board::PositionXY( 7, 3 ),
		Board::PositionXY( 7, 5 ),
		Board::PositionXY( 6, 1 ),
		Board::PositionXY( 11, 6 ),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );

		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );
	}
	const Board::PositionXY lastHumanMove = Board::PositionXY( 5, 7 );
	m_pGomokuBoard->PutMove( lastHumanMove, m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, lastHumanMove );
	pScore->UpdateScore( *m_pBoardScoreHuman, lastHumanMove );

	// 3. Best candidates:
	const Board::PositionXY bestMove1 = Board::PositionXY( 4, 8 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const SearchTreeAlgorithmIf::ScoreForMove el = nBestMoves.PopData();
		candidates.push_back( el.m_move );
	}

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result4 );
}

void AlphaBetaTest::IssueTest20()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly-
     *
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//                       1 1 1 1 1
	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//0 |. . . . . . . . . . . . . . .|
	//1 |. . . . . . . . . . . . . . .|
	//2 |. . . . . . . . . . . . . . .|
	//3 |. . . . . . . . . . . . . . .|
	//4 |. . . . . . o . . . . . . . .|
	//5 |. . . x . o x x . . . . . . .|
	//6 |. . . . o . o x . . . . . . .|
	//7 |. . . . . o o x . . . . . . .|
	//8 |. . . . . x o o . . . . . . .|
	//9 |. . . . . . x o . . . . . . .|
	//10|. . . . . . . . x . . . . . .|
	//11|. . . . . . . . . . . . . . .|
	//12|. . . . . . . . . . . . . . .|
	//13|. . . . . . . . . . . . . . .|
	//14|. . . . . . . . . . . . . . .|
	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 10, 8 ),
		Board::PositionXY( 5, 3 ),
		Board::PositionXY( 9, 6 ),
		Board::PositionXY( 5, 6 ),
		//Board::PositionXY( 4, 7 ),
		//Board::PositionXY( 4, 4 )
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 7, 5 ),
		Board::PositionXY( 8, 6 ),
		Board::PositionXY( 8, 7 ),
		Board::PositionXY( 9, 7 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 4, 6 ),
		//Board::PositionXY( 5, 5 ),
		//Board::PositionXY( 3, 7 ),
		//Board::PositionXY( 7, 3 )
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );

		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );
	}
	const Board::PositionXY lastHumanMove = Board::PositionXY( 5, 5 );
	m_pGomokuBoard->PutMove( lastHumanMove, m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, lastHumanMove );
	pScore->UpdateScore( *m_pBoardScoreHuman, lastHumanMove );

	// 3. Best candidates:
	const Board::PositionXY bestMove1 = Board::PositionXY( 3, 7 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 7, 3 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const SearchTreeAlgorithmIf::ScoreForMove el = nBestMoves.PopData();
		candidates.push_back( el.m_move );
	}

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 );
}

void AlphaBetaTest::IssueTest21()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly-
	 * Early recognizing fail.
     * The only move not leading to fail is (6,6)
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	//	                       1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|
	//	5 |. . . . . . . . . . . . . . .|
	//	6 |. . . . . x . . . . . . . . .|
	//	7 |. . . x o o o . . . . . . . .|
	//	8 |. . . . o x . . . . . . . . .|
	//	9 |. . . . . . . . . . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	// 2. Put movies to the board.
	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 6, 5 ),
		Board::PositionXY( 7, 3 ),
//		Board::PositionXY( 9, 3 ),
//		Board::PositionXY( 5, 4 ),
//		Board::PositionXY( 5, 3 ),
//		Board::PositionXY( 9, 4 ),
//		Board::PositionXY( 7, 8 ),
//		Board::PositionXY( 9, 7 )
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 7, 4 ),
		Board::PositionXY( 7, 5 ),
//		Board::PositionXY( 8, 4 ),
//		Board::PositionXY( 6, 4 ),
//		Board::PositionXY( 8, 6 ),
//		Board::PositionXY( 10, 4 ),
//		Board::PositionXY( 7, 7 ),
//		Board::PositionXY( 9, 5 )
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );

		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );
	}
	const Board::PositionXY lastHumanMove = Board::PositionXY( 8, 4 );
	m_pGomokuBoard->PutMove( lastHumanMove, m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, lastHumanMove );
	pScore->UpdateScore( *m_pBoardScoreHuman, lastHumanMove );

	// 3. Best candidates:
	const Board::PositionXY bestMove1 = Board::PositionXY( 6, 6 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const SearchTreeAlgorithmIf::ScoreForMove el = nBestMoves.PopData();
		candidates.push_back( el.m_move );
	}

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( bestMove1 == result4 );
}

void AlphaBetaTest::IssueTest22()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly-
     *
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	                       1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . o . . . o . . . . . .|
	//	3 |. . . . x . . x . . . . . . .|
	//	4 |. . . . x o x . . . . . . . .|
	//	5 |. . . . x x o . . . . . . . .|
	//	6 |. o x x x x o . . . . . . . .|
	//	7 |. . . o o x o x o . . . . . .|
	//	8 |. . . . o x o o o . . . . . .|
	//	9 |. . . . . o x . . . . . . . .|
	//	10|. . . . . . o . . . . . . . .|
	//	11|. . . . . . . x . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 6, 5 ),
		Board::PositionXY( 7, 5 ),
		Board::PositionXY( 6, 4 ),
		Board::PositionXY( 5, 5 ),
		Board::PositionXY( 5, 4 ),
		Board::PositionXY( 4, 6 ),
		Board::PositionXY( 9, 6 ),
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 6, 2 ),
		Board::PositionXY( 11, 7 ),
		Board::PositionXY( 6, 3 ),
		Board::PositionXY( 3, 7 ),
		Board::PositionXY( 3, 4 ),
		Board::PositionXY( 4, 4 ),
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 8, 7 ),
		Board::PositionXY( 7, 4 ),
		Board::PositionXY( 9, 5 ),
		Board::PositionXY( 6, 6 ),
		Board::PositionXY( 4, 5 ),
		Board::PositionXY( 5, 6 ),
		Board::PositionXY( 8, 6 ),
		Board::PositionXY( 7, 3 ),
		Board::PositionXY( 8, 4 ),
		Board::PositionXY( 10, 6 ),
		Board::PositionXY( 8, 8 ),
		Board::PositionXY( 6, 1 ),
		Board::PositionXY( 2, 8 ),
		Board::PositionXY( 7, 8 ),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );

		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );
	}
	const Board::PositionXY lastHumanMove = Board::PositionXY( 2, 4 );
	m_pGomokuBoard->PutMove( lastHumanMove, m_pBoardScoreHuman->GetPlayer() );
	pScore->UpdateScore( *m_pBoardScoreComputer, lastHumanMove );
	pScore->UpdateScore( *m_pBoardScoreHuman, lastHumanMove );

	// 3. Best candidates:
	const Board::PositionXY bestMove1 = Board::PositionXY( 6, 7 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 8, 9 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const SearchTreeAlgorithmIf::ScoreForMove el = nBestMoves.PopData();
		candidates.push_back( el.m_move );
	}

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );

    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 );
}

void AlphaBetaTest::IssueTest23()
{
	/* *************************** The issue crux **************************************
	 * *********************************************************************************
	 * This scenario fix one of the anomaly- cpu want to create lizard(winner) threat by exending
     * its 3BC threat (7,10). It is bad move as human cab easly block 4BC and create its 3A at
     * one stone.
	 */

	// 1. Initialize algorithm.
    Score* pScore = Score::GetInstance();
	AlphaBeta* pAlphaBeta = AlphaBeta::GetInstance();
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );

	// 2. Put movies to the board.
	//	                       1 1 1 1 1
	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . . . . . . . . . . . . . .|
	//	1 |. . . . . . . . . . . . . . .|
	//	2 |. . . . . . . . . . . . . . .|
	//	3 |. . . . . . . . . . . . . . .|
	//	4 |. . . . . . . . . . . . . . .|
	//	5 |. . . . . . o o . . . . . . .|
	//	6 |. . . . . . . x o . . . . . .|
	//	7 |. . . . . o x x x . . . . . .|
	//	8 |. . . . . o . x . . . . . . .|
	//	9 |. . . . . . . . . . . . . . .|
	//	10|. . . . . . . . . . . . . . .|
	//	11|. . . . . . . . . . . . . . .|
	//	12|. . . . . . . . . . . . . . .|
	//	13|. . . . . . . . . . . . . . .|
	//	14|. . . . . . . . . . . . . . .|
	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

	vector< Board::PositionXY > xyListCpu{
		Board::PositionXY( 6, 7 ),
		Board::PositionXY( 7, 6 ),
		Board::PositionXY( 7, 7 ),
		Board::PositionXY( 7, 8 ),
		Board::PositionXY( 8, 7 ),
	};

	vector< Board::PositionXY > xyHuman{
		Board::PositionXY( 5, 6 ),
		Board::PositionXY( 5, 7 ),
		Board::PositionXY( 7, 5 ),
		Board::PositionXY( 8, 5 ),
		Board::PositionXY( 6, 8 ),
	};

	for ( uint32_t i = 0; i < xyListCpu.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyHuman[i], m_pBoardScoreHuman->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyHuman[i] );

		m_pGomokuBoard->PutMove( xyListCpu[i], m_pBoardScoreComputer->GetPlayer() );
		pScore->UpdateScore( *m_pBoardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( *m_pBoardScoreHuman, xyListCpu[i] );
	}

	// 3. Best candidates:
	const Board::PositionXY bestMove1 = Board::PositionXY( 6, 7 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 8, 9 );

	//4. Get candidates.
	const uint32_t maxCandidatesNumber = 20U;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
	vector<Board::PositionXY> candidates = {};

	GetInitCandidatesUT( nBestMoves, 2U );

	const uint32_t candidatesNumber = nBestMoves.GetSize();
	for( uint32_t i = 0; i < candidatesNumber; ++i )
	{
		const SearchTreeAlgorithmIf::ScoreForMove el = nBestMoves.PopData();
		candidates.push_back( el.m_move );
	}

	// 3. Not best move
	const Board::PositionXY noBestMove1 = Board::PositionXY( 7, 10 );

	// 5. Check the results.
	pAlphaBeta->SetDeep( 4 );
	pAlphaBeta->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pAlphaBeta->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	const Board::PositionXY result4 = pAlphaBeta->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( noBestMove1 != result4  );
}

//---------------------------------------------------------------------------------------------------------------------------------------
void AlphaBetaTest::GetInitCandidatesUT( SearchTreeAlgorithmIf::PriorityQueueScore& rInitCandidates, const uint32_t initDepht ) const
{
	static MinMax* pMinMax = MinMax::GetInstance();
	pMinMax->SetDeep( initDepht );

	// Allocate 60% capacity for CPU and 40% for Human.
	const uint32_t size = rInitCandidates.GetContainerSize();
	const uint32_t cpuSize = ( 6 * size )/10;
	const uint32_t humanSize = ( 4 * size )/10;

	SearchTreeAlgorithmIf::PriorityQueueScore cpuCandidates( cpuSize ), humanCandidates( humanSize );
	vector<Board::PositionXY> existingCandidates;

	//a. Get best candidates for cpu.
	pMinMax->SetInitialPlayer( m_pBoardScoreComputer->GetPlayer() );
	pMinMax->SetBoardScore( *m_pBoardScoreComputer, *m_pBoardScoreHuman );
	pMinMax->FindBestMove( cpuCandidates );

	//b. Get best candidates for human. Reversing is needed.
	pMinMax->SetInitialPlayer( m_pBoardScoreHuman->GetPlayer() );
	pMinMax->SetBoardScore( *m_pBoardScoreHuman, *m_pBoardScoreComputer );
	pMinMax->FindBestMove( humanCandidates );

	//c. Merge into one output container. Be careful to not provide duplications.
	rInitCandidates.ClearAll();

	while( !cpuCandidates.empty() )
	{
		const SearchTreeAlgorithmIf::ScoreForMove scoreForMove = cpuCandidates.PopData();
		rInitCandidates.PushData( scoreForMove );

		//Remember xy position which was added.
		existingCandidates.push_back( scoreForMove.m_move );
	}

	while( !humanCandidates.empty() )
	{
		const SearchTreeAlgorithmIf::ScoreForMove scoreForMove = humanCandidates.PopData();

		// Don't provide xy move if was added before.
		const bool isNewMove = ( std::find( existingCandidates.begin(), existingCandidates.end(), scoreForMove.m_move ) == existingCandidates.end() );

		if( isNewMove )
		{
			rInitCandidates.PushData( scoreForMove );
		}
	}
}
