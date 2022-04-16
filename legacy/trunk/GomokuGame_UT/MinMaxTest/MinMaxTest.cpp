/*
 * ScoreTest.cpp
 *
 *  Created on: 29 may, 2016
 *      Author: zby
 */
#include <assert.h>     		// for assert.
#include <algorithm>    		// std::find
#include <ctime>
#include "MinMaxTest.hpp"
#include "BoardScore.hpp"
#include "ThreatsBloodRelation.hpp"
#include "PriorityQueue.hpp"

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

void MinMaxTest::GenerateCandTestEmptyBoard()
{
	cout<< "GenerateCandTestEmptyBoard in progress.. "<<endl;

	MinMax* pMinMax = MinMax::GetInstance();

	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( Board::PLAYER_A );
	// Empty board - empty candidate.
	pMinMax->BoardScoreCopyInitUT();
	vector< Board::PositionField > candidate = pMinMax->GenerateCand();
	CPPUNIT_ASSERT( 0 == candidate.size() );
}

void MinMaxTest::GenerateCandTestCorner()
{
	cout<< "GenerateCandTestCorner in progress.. "<<endl;

    // -----------------------
    //  | x | . |   |   |   |
    // -----------------------
    //  | . | . |   |   |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------

	MinMax* pMinMax = MinMax::GetInstance();

	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( Board::PLAYER_A );

	// Put move into the corner.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 0 ), Board::PLAYER_A );

	// Corner has only 3 neighbors.
	const vector< Board::PositionField > expected = { 1, 15, 16 };

	vector< Board::PositionField > candidate = pMinMax->GenerateCand();
	CPPUNIT_ASSERT( expected == candidate );
}

void MinMaxTest::GenerateCandTesCenter()
{
	cout<< "GenerateCandTesCenter in progress.. "<<endl;

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

	MinMax* pMinMax = MinMax::GetInstance();

	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	// Put move into the center.
	m_pGomokuBoard->PutMove( Board::PositionXY( 5, 5 ), Board::PLAYER_A );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	// Corner has only 8 neighbors.
	const vector< Board::PositionField > expected = { 64, 65, 66, 79, 81, 94, 95, 96 };

	vector< Board::PositionField > candidate = pMinMax->GenerateCand();
	CPPUNIT_ASSERT( expected == candidate );
}

void MinMaxTest::GenerateCandTesConcatenatedMoves()
{
	cout<< "GenerateCandTesConcatenatedMoves in progress.. "<<endl;

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
	MinMax* pMinMax = MinMax::GetInstance();

	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	// Put move into the center.
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 1 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 2, 2 ), Board::PLAYER_A );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );

	const vector< Board::PositionField > expected = { 0, 1, 2, 15, 17, 18, 30, 31, 33, 46, 47, 48 };

	vector< Board::PositionField > candidate = pMinMax->GenerateCand();

	CPPUNIT_ASSERT( expected == candidate );
}

void MinMaxTest::GenerateCandTesMixed1()
{
	cout<< "GenerateCandTesMixed1 in progress.. "<<endl;

    // -----------------------
    //  | x | . | x | . |   |
    // -----------------------
    //  | . | . | o | . |   |
    // -----------------------
    //  |   | . | . | . |   |
    // -----------------------
    //  |   |   |   |   |   |
    // -----------------------

	MinMax* pMinMax = MinMax::GetInstance();

	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	// Put move into the center.
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 0 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 0, 2 ), Board::PLAYER_A );
	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 2 ), Board::PLAYER_B );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );

	const vector< Board::PositionField > expected = { 1, 3, 15, 16, 18, 31, 32, 33 };

	vector< Board::PositionField > candidate = pMinMax->GenerateCand();

	CPPUNIT_ASSERT( expected == candidate );
}

void MinMaxTest::GenerateCandTesMixed2()
{
	cout<< "GenerateCandTesMixed2 in progress.. "<<endl;

	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

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

	MinMax* pMinMax = MinMax::GetInstance();
	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );

	const vector< Board::PositionField > expected1 = { 1, 15, 16 };
	vector< Board::PositionField > candidate1 = pMinMax->GenerateCand();
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
	vector< Board::PositionField > candidate2 = pMinMax->GenerateCand();
	CPPUNIT_ASSERT( expected2 == candidate2 );
}

void MinMaxTest::UpdateCandTest1()
{
	cout<< "UpdateCandTest1 in progress.. "<<endl;

	// The scenario:
	// 1. On the board where are 3 move run initCandidates = GenerateCand()
	// 2. The result is initCandidates vector which contains (unique) neighborhood of each move.
	// 3. Put a new move to one of neighbor.
	// 4. The result shall be that the neighbor shall be removed from initCandidates and
	//    his unique neighbors will be added to initial initCandidates.

	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	MinMax* pMinMax = MinMax::GetInstance();
	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );

	const Board& board = boardScoreComputer.GetBoard();

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

	vector< Board::PositionField > initCandidatesStl = pMinMax->GenerateCand();

	vector< Board::PositionXY > expected = { Board::PositionXY( 3, 1 ),
											 Board::PositionXY( 4, 1 ),
											 Board::PositionXY( 5, 1 )
											};

	// Check that 'initCandidates' does not include yet: {(3,1) (4,1) (5,1)}.
	for ( vector< Board::PositionXY >::const_iterator it1 = expected.begin(); it1 != expected.end(); ++it1 )
	{
		for ( vector< Board::PositionField >::const_iterator it2 = initCandidatesStl.begin(); it2 != initCandidatesStl.end(); ++it2 )
		{
			const Board& board = boardScoreComputer.GetBoard();
			const Board::PositionXY xy = Board::PositionXY( board.GetSize(), *it2 );
			const bool isDifferent = !( *it1 == xy );
			CPPUNIT_ASSERT( isDifferent );
		}
	}

	// Converts stl vector to VectorLight
	MinMax::VectorUniqueType initCandidates;
    initCandidates = initCandidatesStl;

	// The position where a new move will be put.
	const Board::PositionField newMove = Board::PositionField( board.GetSize(), Board::PositionXY( 4, 2 ) );

	// Needs for UpdateCand() initialization.
	pMinMax->BoardScoreCopyInitUT();

	// Put move and update candidates.
	MinMax::VectorUniqueType updatedCandidats = pMinMax->UpdateCand( initCandidates, newMove );

	const uint32_t initCandidatesStlSize = initCandidatesStl.size();
	const uint32_t updatedCandidatsSize = updatedCandidats.GetNumberOfElements();
	const uint32_t expectedSize = expected.size();

	// The size should be larger because of adding new neighborhood but smaller because of putting newMove move.
	CPPUNIT_ASSERT( updatedCandidatsSize == ( initCandidatesStlSize + expectedSize - 1 ) );

	// Check that 'updatedCandidats' includes neighborhood of the newMove: {(3,1) (4,1) (5,1)}.
	for ( vector< Board::PositionXY >::const_iterator pIteratorExpectation = expected.begin(); pIteratorExpectation != expected.end(); ++pIteratorExpectation )
	{
		bool isInclude = false;

		MinMax::VectorUniqueTypeIterator pIterator = updatedCandidats.GetIteratorBegin();
		for ( ; pIterator != updatedCandidats.GetIteratorEnd(); ++pIterator)
		{
			const Board& board = boardScoreComputer.GetBoard();
			const Board::PositionXY xy = Board::PositionXY( board.GetSize(), *pIterator );

			if( xy == *pIteratorExpectation  )
			{
				isInclude = true;
			}
		}

		CPPUNIT_ASSERT( true == isInclude );
	}
}

void MinMaxTest::UpdateCandTest2()
{
	cout<< "UpdateCandTest2 in progress.. "<<endl;

	// The scenario:
	// 1. On the board where are 3 move run initCandidates = GenerateCand()
	// 2. The result is initCandidates vector which contains (unique) neighborhood of each move.
	// 3. Put a new move to one of neighbor.
	// 2. THEN add an extra move into a board just next to the neighborhood.
	// 4. The result shall be that the neighbor shall be removed from initCandidates and
	//    his unique neighbors will be added to initial initCandidates.
	// 	  The extra move should not be included as it's not vacant position.

	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	MinMax* pMinMax = MinMax::GetInstance();
	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );

	const Board& board = boardScoreComputer.GetBoard();

	// Put move into the board.
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

	vector< Board::PositionField > initCandidatesStl = pMinMax->GenerateCand();

	vector< Board::PositionXY > expected = { Board::PositionXY( 3, 1 ),
											 //Board::PositionXY( 4, 1 ),
											 Board::PositionXY( 5, 1 )
											};

	// Check that 'initCandidates' does not include yet: {(3,1) (5,1)}.
	for ( vector< Board::PositionXY >::const_iterator it1 = expected.begin(); it1 != expected.end(); ++it1 )
	{
		for ( vector< Board::PositionField >::const_iterator it2 = initCandidatesStl.begin(); it2 != initCandidatesStl.end(); ++it2 )
		{
			const Board& board = boardScoreComputer.GetBoard();
			const Board::PositionXY xy = Board::PositionXY( board.GetSize(), *it2 );
			const bool isDifferent = !( *it1 == xy );
			CPPUNIT_ASSERT( isDifferent );
		}
	}

	// The position where an extra move will be put.
	const Board::PositionXY extraMove = Board::PositionXY( 4, 1 );
	m_pGomokuBoard->PutMove( extraMove, Board::PLAYER_B );

	// Converts stl vector to VectorLight
	MinMax::VectorUniqueType initCandidates;
    initCandidates = initCandidatesStl;

	// The position where a new move will be put.
	const Board::PositionField newMove = Board::PositionField( board.GetSize(), Board::PositionXY( 4, 2 ) );

	// Needs for initialize UpdateCand().
	pMinMax->BoardScoreCopyInitUT();
	MinMax::VectorUniqueType updatedCandidats = pMinMax->UpdateCand( initCandidates, newMove );

	const uint32_t initCandidatesStlSize = initCandidatesStl.size();
	const uint32_t updatedCandidatsSize = updatedCandidats.GetNumberOfElements();
	const uint32_t expectedSize = expected.size();

	// The size should be larger because of adding new neighborhood but smaller because of putting newMove move.
	CPPUNIT_ASSERT( updatedCandidatsSize == ( initCandidatesStlSize + expectedSize - 1 ) );

	// Check that 'updatedCandidats' includes neighborhood of the newMove: {(3,1) (5,1)}.
	for ( vector< Board::PositionXY >::const_iterator pIteratorExpectation = expected.begin(); pIteratorExpectation != expected.end(); ++pIteratorExpectation )
	{
		bool isInclude = false;

		MinMax::VectorUniqueTypeIterator pIterator = updatedCandidats.GetIteratorBegin();
		for ( ; pIterator != updatedCandidats.GetIteratorEnd(); ++pIterator)
		{
			const Board& board = boardScoreComputer.GetBoard();
			const Board::PositionXY xy = Board::PositionXY( board.GetSize(), *pIterator );

			if( xy == *pIteratorExpectation  )
			{
				isInclude = true;
			}
		}

		CPPUNIT_ASSERT( true == isInclude );
	}
}

void MinMaxTest::SwitchPlayerTest()
{
	cout<< "SwitchPlayerTest in progress.. "<<endl;

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	MinMax* pMinMax = MinMax::GetInstance();
	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( Board::PLAYER_B );

	// Check who's current move is.
	CPPUNIT_ASSERT( Board::PLAYER_B == pMinMax->WhoIsCurrentMove() );

	pMinMax->SwitchPlayer();

	// Check who's current move is.
	CPPUNIT_ASSERT( Board::PLAYER_A == pMinMax->WhoIsCurrentMove() );

	pMinMax->SwitchPlayer();

	// Check who's current move is.
	CPPUNIT_ASSERT( Board::PLAYER_B == pMinMax->WhoIsCurrentMove() );
}

void MinMaxTest::GameTreeBrowsingBasicDeep2Test()
{
	cout<< "GameTreeBrowsingBasicDeep2Test in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	// Put some moves into board.
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

	m_pGomokuBoard->PutMove( xyList[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyList[0] );
	pScore->UpdateScore( boardScoreHuman, xyList[0] );

	m_pGomokuBoard->PutMove( xyList[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyList[1] );
	pScore->UpdateScore( boardScoreHuman, xyList[1] );

	m_pGomokuBoard->PutMove( xyList[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyList[2] );
	pScore->UpdateScore( boardScoreHuman, xyList[2] );
	xyList.clear();

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

    // One of the following move is expected.
    const vector< Board::PositionXY > expected = { Board::PositionXY( 1, 1 ), Board::PositionXY( 5, 5 ) };
    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

    // Check depth == 1
    pMinMax->SetDeep( 1 );
    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);

    // Check depth == 2
    pMinMax->SetDeep( 2 );
    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);

    // Check depth == 3
    pMinMax->SetDeep( 3 );
    const Board::PositionXY result3 = pMinMax->FindBestMove(nBestMove);

    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result1 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result2 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result3 ) );
}

void MinMaxTest::GameTreeBrowsingBasicDeep3Test()
{
	cout<< "GameTreeBrowsingBasicDeep3Test in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	// Put some moves into board.
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

	m_pGomokuBoard->PutMove( xyList[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyList[0] );
	pScore->UpdateScore( boardScoreHuman, xyList[0] );

	m_pGomokuBoard->PutMove( xyList[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyList[1] );
	pScore->UpdateScore( boardScoreHuman, xyList[1] );

	m_pGomokuBoard->PutMove( xyList[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyList[2] );
	pScore->UpdateScore( boardScoreHuman, xyList[2] );
	xyList.clear();

    // One of the following move is expected.
    const vector< Board::PositionXY > expected = { Board::PositionXY( 1, 1 ), Board::PositionXY( 5, 5 ) };

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

	// Check depth == 1
    pMinMax->SetDeep( 1 );
    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);

	// Check depth == 2
    pMinMax->SetDeep( 2 );
    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);

	// Check depth == 3
    pMinMax->SetDeep( 3 );
    const Board::PositionXY result3 = pMinMax->FindBestMove(nBestMove);

    // Check if the move 'result' is on the expected list.
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result1 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result2 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result3 ) );
}

void MinMaxTest::GameTreeBrowsingBestMoveTest1()
{
	cout<< "GameTreeBrowsingBestMoveTest1 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	// Put some moves into board.
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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[4] );
	m_pGomokuBoard->PutMove( xyListCpu[5], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[5] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[5] );
	m_pGomokuBoard->PutMove( xyListUser[0], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreComputer, xyListUser[0] );
	pScore->UpdateScore( boardScoreHuman, xyListUser[0] );

    // One of the following best move is expected.
    const vector< Board::PositionXY > expected = { Board::PositionXY( 5, 1 ) };

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

	// Check for depth == 1.
    pMinMax->SetDeep( 1 );
    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);

	// Check for depth == 2.
    pMinMax->SetDeep( 2 );
    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);

	// Check for depth == 3.
    pMinMax->SetDeep( 3 );
    const Board::PositionXY result3 = pMinMax->FindBestMove(nBestMove);

    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result1 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result2 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result3 ) );
}

void MinMaxTest::GameTreeBrowsingBestMoveTest2()
{
	cout<< "GameTreeBrowsingBestMoveTest2 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	// Put some moves into board.
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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

    // One of the following move is expected.
    const vector< Board::PositionXY > expected = { Board::PositionXY( 3, 4 ) };

    // Set depth == 1
    pMinMax->SetDeep( 1 );
    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);

    // Set depth == 2
    pMinMax->SetDeep( 2 );
    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);

    // Set depth == 3
    pMinMax->SetDeep( 3 );
    const Board::PositionXY result3 = pMinMax->FindBestMove(nBestMove);

    // Check if the move 'result' is on the expected list.
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result1 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result2 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result3 ) );
}

void MinMaxTest::GameTreeBrowsingBestMoveTest3()
{
	cout<< "GameTreeBrowsingBestMoveTest3 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	// Put some moves into board.
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
    //  |   |   |   | x |   |   |   |   |
    // ----------------------------------
    //  |   |   |   |   | o |   |   |   |
    // ----------------------------------
    //  |   |   |   |   |   |   |   |   |
    // ----------------------------------
	// Update score for current state.
    vector< Board::PositionXY > xyListCpu{
    									   Board::PositionXY( 3, 3 )
    								   	 };

    vector< Board::PositionXY > xyListHuman{
    										 Board::PositionXY( 4, 4 )
    								   	   };

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListHuman[0], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[0] );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[0] );

    // One of the following move is expected.
    const vector< Board::PositionXY > expected = { Board::PositionXY( 2, 3 ),
												   Board::PositionXY( 2, 4 ),
												   Board::PositionXY( 3, 2 ),
												   Board::PositionXY( 3, 4 ),
												   Board::PositionXY( 3, 5 ),
												   Board::PositionXY( 4, 2 ),
												   Board::PositionXY( 4, 3 )
												  };

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

	// Set depth == 1
    pMinMax->SetDeep( 1 );
    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);

	// Set depth == 2
    pMinMax->SetDeep( 2 );
    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);

	// Set depth == 3
    pMinMax->SetDeep( 3 );
    const Board::PositionXY result3 = pMinMax->FindBestMove(nBestMove);

    // Check if the move 'result' is on the expected list.
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result1 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result2 ) );
    CPPUNIT_ASSERT( expected.end() != std::find( expected.begin(), expected.end(), result3 ) );
}

void MinMaxTest::GameTreeBrowsingBestMoveTest4()
{
	cout<< "GameTreeBrowsingBestMoveTest4 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	// Put some moves into board.
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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );

	m_pGomokuBoard->PutMove( xyListHuman[0], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[0] );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[1] );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[2] );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[2] );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

	// There is only one expected best move:
    const Board::PositionXY expected = Board::PositionXY( 10, 2 );
    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

    // Check depth == 1
    pMinMax->SetDeep( 1 );
    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);
    CPPUNIT_ASSERT( expected == result1 );

    // Check depth == 2
    pMinMax->SetDeep( 2 );
    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);
    CPPUNIT_ASSERT( expected == result2 );

    // Check depth == 3
    pMinMax->SetDeep( 3 );
    const Board::PositionXY result3 = pMinMax->FindBestMove(nBestMove);
    CPPUNIT_ASSERT( expected == result3 );
}

void MinMaxTest::GameTreeBrowsingBestMoveTest5()
{
	cout<< "GameTreeBrowsingBestMoveTest5 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );
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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[4] );

	m_pGomokuBoard->PutMove( xyListHuman[0], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[0] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[1] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[2] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[2] );
	m_pGomokuBoard->PutMove( xyListHuman[3], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[3] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[3] );
	m_pGomokuBoard->PutMove( xyListHuman[4], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[4] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[4] );

	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

	// Action: User created dead threat. It must be blocked
	const Board::PositionXY bestMove = Board::PositionXY( 7, 8 );
    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

	// Find best move.
	pMinMax->SetDeep( 1 );
	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);
    CPPUNIT_ASSERT( bestMove == result1 );

	pMinMax->SetDeep( 2 );
	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);
    CPPUNIT_ASSERT( bestMove == result2 );

	pMinMax->SetDeep( 3 );
	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
    const Board::PositionXY result3 = pMinMax->FindBestMove(nBestMove);
    CPPUNIT_ASSERT( bestMove == result3 );
}

void MinMaxTest::GameTreeBrowsingBestMoveTest6()
{
	cout<< "GameTreeBrowsingBestMoveTest6 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );
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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );

	m_pGomokuBoard->PutMove( xyListHuman[0], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[0] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[1] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[2] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[2] );
	m_pGomokuBoard->PutMove( xyListHuman[3], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[3] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[3] );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

	// Action: User created dead threat. It must be blocked
	const Board::PositionXY bestMove1 = Board::PositionXY( 3, 9 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 8, 4 );
    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

	pMinMax->SetDeep( 1 );
    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);
    nBestMove.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result1 || bestMove2 == result1 );

	pMinMax->SetDeep( 2 );
    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);
    nBestMove.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 );

	pMinMax->SetDeep( 3 );
    const Board::PositionXY result3 = pMinMax->FindBestMove(nBestMove);
    nBestMove.ClearAll();
    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3 );
}

void MinMaxTest::GameTreeBrowsingBestMoveTest7()
{
	cout<< "GameTreeBrowsingBestMoveTest7 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );
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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );

	m_pGomokuBoard->PutMove( xyListHuman[0], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[0] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[1] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[2] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[2] );
	m_pGomokuBoard->PutMove( xyListHuman[3], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[3] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[3] );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

	// Action: User created dead threat. It must be blocked
	const Board::PositionXY bestMove = Board::PositionXY( 11, 9 );
    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

//	pMinMax->SetDeep( 1 );
//    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);
//    nBestMove.ClearAll();
//    CPPUNIT_ASSERT( bestMove == result1 );

	pMinMax->SetDeep( 2 );
    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);
    nBestMove.ClearAll();
    CPPUNIT_ASSERT( bestMove == result2  );

	pMinMax->SetDeep( 3 );
    const Board::PositionXY result3 = pMinMax->FindBestMove(nBestMove);
    nBestMove.ClearAll();
    CPPUNIT_ASSERT( bestMove == result3 );
}

void MinMaxTest::GameTreeBrowsingBestMoveTest8()
{
	cout<< "GameTreeBrowsingBestMoveTest8 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[4] );
	m_pGomokuBoard->PutMove( xyListCpu[5], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[5] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[5] );

	m_pGomokuBoard->PutMove( xyListHuman[0], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[0] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[1] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[2] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[2] );
	m_pGomokuBoard->PutMove( xyListHuman[3], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[3] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[3] );
	m_pGomokuBoard->PutMove( xyListHuman[4], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[4] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[4] );
	m_pGomokuBoard->PutMove( xyListHuman[5], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[5] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[5] );
	m_pGomokuBoard->PutMove( xyListHuman[6], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[6] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[6]);

	const uint32_t nBest = 12;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMove( nBest );
	vector<Board::PositionXY> candidates = {};

	// Action: CPU extends it's threat creating a new at once.
	const Board::PositionXY bestMoveStage1 = Board::PositionXY( 9, 4 );
	const Board::PositionXY bestMoveStage2 = Board::PositionXY( 9, 3 );
	const Board::PositionXY humanChallenge = Board::PositionXY( 7, 8 );

	pMinMax->SetDeep( 2 );
    pMinMax->FindBestMove( nBestMove );

    uint32_t nBestMovesSize = nBestMove.GetSize();
    for( uint32_t i = 0; i < nBestMovesSize; ++i )
    {
        const Board::PositionXY el = nBestMove.PopData().m_move;
        candidates.push_back( el );
    }

    pMinMax->SetDeep( 4 );
    nBestMove.ClearAll();
    Board::PositionXY retVal = pMinMax->FindBestMove( nBestMove, candidates );
    CPPUNIT_ASSERT( retVal == bestMoveStage1  );

	m_pGomokuBoard->PutMove( bestMoveStage1, boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, bestMoveStage1 );
	pScore->UpdateScore( boardScoreComputer, bestMoveStage1);

	m_pGomokuBoard->PutMove( humanChallenge, boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreHuman, humanChallenge );
	pScore->UpdateScore( boardScoreComputer, humanChallenge);

	pMinMax->SetDeep( 2 );
	nBestMove.ClearAll();
    candidates.clear();
    pMinMax->FindBestMove( nBestMove );

    nBestMovesSize = nBestMove.GetSize();
    for( uint32_t i = 0; i < nBestMovesSize; ++i )
    {
        const Board::PositionXY el = nBestMove.PopData().m_move;
        candidates.push_back( el );
    }

    pMinMax->SetDeep( 4 );
    nBestMove.ClearAll();
    retVal = pMinMax->FindBestMove( nBestMove, candidates );
    CPPUNIT_ASSERT( retVal == bestMoveStage2  );

}

void MinMaxTest::GenerateCandidateExtendGapsTest1()
{
	cout<< "GenerateCandidateExtendGapsTest1 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );

	std::vector<Board::PositionField> exGaps;
	uint32_t expectedExGapsNumber = 3;

	boardScoreComputer.GetExGaps(exGaps, ThreatFinder::THREAT_2_CASE_A);
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );

	Board::PositionXY expectedExGapsList2A[] = { Board::PositionXY( 1, 4 ), Board::PositionXY( 4, 2 ), Board::PositionXY( 4, 4 ) };
	for( uint32_t i = 0; i < NUMELEM( expectedExGapsList2A ); ++i )
	{
		const Board::PositionField positionField( m_pGomokuBoard->GetSize(), expectedExGapsList2A[ i ] );
		const bool isOnGapsList = Checker( positionField, exGaps );
		CPPUNIT_ASSERT( isOnGapsList == true );
	}
}

void MinMaxTest::GenerateCandidateExtendGapsTest2()
{
	cout<< "GenerateCandidateExtendGapsTest2 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[4] );
	m_pGomokuBoard->PutMove( xyListCpu[5], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[5] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[5] );
	m_pGomokuBoard->PutMove( xyListCpu[6], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[6] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[6] );
	m_pGomokuBoard->PutMove( xyListCpu[7], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[7] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[7] );
	m_pGomokuBoard->PutMove( xyListCpu[8], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[8] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[8] );
	m_pGomokuBoard->PutMove( xyListCpu[9], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[9] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[9] );
	m_pGomokuBoard->PutMove( xyListCpu[10], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[10] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[10] );
	m_pGomokuBoard->PutMove( xyListCpu[11], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[11] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[11] );
	m_pGomokuBoard->PutMove( xyListCpu[12], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[12] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[12] );

	m_pGomokuBoard->PutMove( xyListHuman[0], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[0] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[0] );
	m_pGomokuBoard->PutMove( xyListHuman[1], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[1] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[1] );
	m_pGomokuBoard->PutMove( xyListHuman[2], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[2] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[2] );
	m_pGomokuBoard->PutMove( xyListHuman[3], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[3] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[3] );
	m_pGomokuBoard->PutMove( xyListHuman[4], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[4] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[4] );
	m_pGomokuBoard->PutMove( xyListHuman[5], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[5] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[5] );
	m_pGomokuBoard->PutMove( xyListHuman[6], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[6] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[6] );
	m_pGomokuBoard->PutMove( xyListHuman[7], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[7] );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[7] );

	std::vector<Board::PositionField> exGaps;
	uint32_t expectedExGapsNumber = 6;

	// Those that are on EXTENDED_NEIGHBORHOOD list
	for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
	{
		boardScoreComputer.GetExGaps(exGaps, ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i]);
	}
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );

	Board::PositionXY expectedExGapsList[] = { Board::PositionXY( 1, 5 ), Board::PositionXY( 2, 12 ), Board::PositionXY( 3, 11 ),Board::PositionXY( 4, 5 ),
											    Board::PositionXY( 4, 3 ), Board::PositionXY( 4, 11 )  };
	for( uint32_t i = 0; i < NUMELEM( expectedExGapsList ); ++i )
	{
		const Board::PositionField positionField( m_pGomokuBoard->GetSize(), expectedExGapsList[ i ] );
		const bool isOnGapsList = Checker( positionField, exGaps );
		CPPUNIT_ASSERT( isOnGapsList == true );
	}
}

void MinMaxTest::GenerateCandidateExtendGapsTest3()
{
	cout<< "GenerateCandidateExtendGapsTest3 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[4] );

	std::vector<Board::PositionField> exGaps;
	uint32_t expectedExGapsNumber = 4;

	// Those that are on EXTENDED_NEIGHBORHOOD list
	for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
	{
		boardScoreComputer.GetExGaps(exGaps, ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i]);
	}
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );

	Board::PositionXY expectedExGapsList[] = { Board::PositionXY( 1, 1 ), Board::PositionXY( 1, 7 ), Board::PositionXY( 3, 8 ), Board::PositionXY( 3, 13 )  };
	for( uint32_t i = 0; i < NUMELEM( expectedExGapsList ); ++i )
	{
		const Board::PositionField positionField( m_pGomokuBoard->GetSize(), expectedExGapsList[ i ] );
		const bool isOnGapsList = Checker( positionField, exGaps );
		CPPUNIT_ASSERT( isOnGapsList == true );
	}
}

void MinMaxTest::GenerateCandidateExtendGapsTest4()
{
	cout<< "GenerateCandidateExtendGapsTest4 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_B );
	BoardScore boardScoreHuman( Board::PLAYER_A );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	0 |. . + + + + + . . . . . . . .|
	//	1 |. + + o o o + + . . . . . . .|
	//	2 |. . + + + + + . . + + + + . .|
	//	3 |. . . . . . . . + + o o + + .|
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

	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
	m_pGomokuBoard->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );
	m_pGomokuBoard->PutMove( xyListCpu[4], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[4] );

	vector< Board::PositionXY > expectedCandidates = { Board::PositionXY( 0, 2 ),
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

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

	vector< Board::PositionField > candidate = pMinMax->GenerateCand();
	CPPUNIT_ASSERT( expectedCandidates.size() == candidate.size() );

	for( uint32_t i = 0; i <  expectedCandidates.size(); ++i )
	{
		Board::PositionField temp( m_pGomokuBoard->GetSize(), expectedCandidates[i]);
		const bool isOnList = Checker( temp, candidate );
		CPPUNIT_ASSERT( isOnList == true );
	}
}

void MinMaxTest::GenerateCandidateExtendGapsTest5()
{
	cout<< "GenerateCandidateExtendGapsTest5 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

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
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );

	m_pGomokuBoard->PutMove(xyListCpu[1], Board::PLAYER_A);
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );

	std::vector<Board::PositionField> exGaps;
	uint32_t expectedExGapsNumber = 2;

	// Those that are on EXTENDED_NEIGHBORHOOD list
	for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
	{
		boardScoreComputer.GetExGaps(exGaps, ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i]);
	}
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );

	Board::PositionXY expectedExGapsList[] = { Board::PositionXY( 3, 3 ), Board::PositionXY( 3, 8 ) };

	for( uint32_t i = 0; i < NUMELEM( expectedExGapsList ); ++i )
	{
		const Board::PositionField positionField( m_pGomokuBoard->GetSize(), expectedExGapsList[ i ] );
		const bool isOnGapsList = Checker( positionField, exGaps );
		CPPUNIT_ASSERT( isOnGapsList == true );
	}
	exGaps.clear();

	// Now human puts its own move on ex gaps position.
	m_pGomokuBoard->PutMove( xyListHuman[0], Board::PLAYER_B );
	pScore->UpdateScore( boardScoreComputer, xyListHuman[0] );
	pScore->UpdateScore( boardScoreHuman, xyListHuman[0] );

	// Its expected that one extended gaps will be removed.
	expectedExGapsNumber = 1;

	// Those that are on EXTENDED_NEIGHBORHOOD list
	for(uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i)
	{
		boardScoreComputer.GetExGaps(exGaps, ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[i]);
	}
	CPPUNIT_ASSERT( exGaps.size() == expectedExGapsNumber );
}

void MinMaxTest::StalemateTest1()
{
	cout<< "StalemateTest1 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoardStalemate );
	boardScoreHuman.SetBoard( *m_pGomokuBoardStalemate );

//	   0 1 2 3 4
//	   _ _ _ _ _
//	0 |x o x x x|
//	1 |x x o x x|
//	2 |x x x o x|
//	3 |x x x x o|
//	4 |o . . . o|
//	  |_ _ _ _ _|

	// Update score for current state.
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
    m_pGomokuBoardStalemate->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[1], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[4], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[4] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[5], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[5] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[5] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[6], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[6] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[6] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[7], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[7] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[7] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[8], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[8] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[8] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[9], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[9] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[9] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[10], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[10] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[10] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[11], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[11] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[11] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[12], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[12] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[12] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[13], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[13] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[13] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[14], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[14] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[14] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[15], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[15] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[15] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[16], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[16] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[16] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[17], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[17] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[17] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[18], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[18] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[18] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[19], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[19] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[19] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[20], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[20] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[20] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[21], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[21] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[21] );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

    pMinMax->SetDeep( 3 );
    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);

}

void MinMaxTest::StalemateTest2()
{
	cout<< "StalemateTest2 in progress.. "<<endl;

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoardStalemate );
	boardScoreHuman.SetBoard( *m_pGomokuBoardStalemate );

//	   0 1 2 3 4
//	   _ _ _ _ _
//	0 |x o x x x|
//	1 |x x o x x|
//	2 |x x x o x|
//	3 |x x x x o|
//	4 |o o . . o|
//	  |_ _ _ _ _|

	// Update score for current state.
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
    m_pGomokuBoardStalemate->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[1], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[4], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[4] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[4] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[5], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[5] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[5] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[6], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[6] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[6] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[7], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[7] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[7] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[8], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[8] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[8] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[9], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[9] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[9] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[10], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[10] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[10] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[11], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[11] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[11] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[12], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[12] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[12] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[13], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[13] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[13] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[14], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[14] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[14] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[15], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[15] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[15] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[16], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[16] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[16] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[17], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[17] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[17] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[18], boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[18] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[18] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[19], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[19] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[19] );

    m_pGomokuBoardStalemate->PutMove( xyListCpu[20], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[20] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[20] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[21], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[21] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[21] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[22], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[22] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[22] );
    m_pGomokuBoardStalemate->PutMove( xyListCpu[23], boardScoreHuman.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, xyListCpu[23] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[23] );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);

    pMinMax->SetDeep( 3 );
    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);
}

void MinMaxTest::PerformanceTest1()
{
	//TIME TOO EXPENSIVE

//	cout<< "PerformanceTest1 in progress.. "<<endl;
//
//	// Get singletons.
//    Score* pScore = Score::GetInstance();
//	MinMax* pMinMax = MinMax::GetInstance();
//
//	// Prepare BoardScore.
//	BoardScore boardScoreComputer( Board::PLAYER_A );
//	BoardScore boardScoreHuman( Board::PLAYER_B );
//	boardScoreComputer.SetBoard( *m_pGomokuBoard );
//	boardScoreHuman.SetBoard( *m_pGomokuBoard );
//
//// This is the worst case as far as number potential candidate concerned.
//// It will took the most time to calculate best move.
////
////    					  1 1 1 1 1
////    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
////    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//// 0 |. . . . . . . . . . . . . . .|
//// 1 |. x . . x . . x . . x . . x .|
//// 2 |. . . . . . . . . . . . . . .|
//// 3 |. . . . . . . . . . . . . . .|
//// 4 |. x . . x . . x . . x . . x .|
//// 5 |. . . . . . . . . . . . . . .|
//// 6 |. . . . . . . . . . . . . . .|
//// 7 |. x . . x . . x . . x . . x .|
//// 8 |. . . . . . . . . . . . . . .|
//// 9 |. . . . . . . . . . . . . . .|
//// 10|. x . . x . . x . . x . . x .|
//// 11|. . . . . . . . . . . . . . .|
//// 12|. . . . . . . . . . . . . . .|
//// 13|. x . . x . . x . . x . . x .|
//// 14|. . . . . . . . . . . . . . .|
////   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
//
//	// Update score for current state.
//    vector< Board::PositionXY > xyListCpu{
//										 	Board::PositionXY( 1, 1 ),
//											Board::PositionXY( 1, 4 ),
//											Board::PositionXY( 1, 7 ),
//											Board::PositionXY( 1, 10 ),
//											Board::PositionXY( 1, 13 ),
//
//										 	Board::PositionXY( 4, 1 ),
//											Board::PositionXY( 4, 4 ),
//											Board::PositionXY( 4, 7 ),
//											Board::PositionXY( 4, 10 ),
//											Board::PositionXY( 4, 13 ),
//
//										 	Board::PositionXY( 7, 1 ),
//											Board::PositionXY( 7, 4 ),
//											Board::PositionXY( 7, 7 ),
//											Board::PositionXY( 7, 10 ),
//											Board::PositionXY( 7, 13 ),
//
//										 	Board::PositionXY( 10, 1 ),
//											Board::PositionXY( 10, 4 ),
//											Board::PositionXY( 10, 7 ),
//											Board::PositionXY( 10, 10 ),
//											Board::PositionXY( 10, 13 ),
//
//										 	Board::PositionXY( 13, 1 ),
//											Board::PositionXY( 13, 4 ),
//											Board::PositionXY( 13, 7 ),
//											Board::PositionXY( 13, 10 ),
//											Board::PositionXY( 13, 13 ),
//
//    								   	  };
//	m_pGomokuBoard->PutMove( xyListCpu[0], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[0] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[0] );
//	m_pGomokuBoard->PutMove( xyListCpu[1], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[1] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[1] );
//	m_pGomokuBoard->PutMove( xyListCpu[2], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[2] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[2] );
//	m_pGomokuBoard->PutMove( xyListCpu[3], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[3] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[3] );
//	m_pGomokuBoard->PutMove( xyListCpu[4], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[4] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[4] );
//
//	m_pGomokuBoard->PutMove( xyListCpu[5], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[5] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[5] );
//	m_pGomokuBoard->PutMove( xyListCpu[6], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[6] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[6] );
//	m_pGomokuBoard->PutMove( xyListCpu[7], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[7] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[7] );
//	m_pGomokuBoard->PutMove( xyListCpu[8], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[8] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[8] );
//	m_pGomokuBoard->PutMove( xyListCpu[9], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[9] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[9] );
//
//	m_pGomokuBoard->PutMove( xyListCpu[10], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[10] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[10] );
//	m_pGomokuBoard->PutMove( xyListCpu[11], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[11] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[11] );
//	m_pGomokuBoard->PutMove( xyListCpu[12], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[12] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[12] );
//	m_pGomokuBoard->PutMove( xyListCpu[13], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[13] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[13] );
//	m_pGomokuBoard->PutMove( xyListCpu[14], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[14] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[14] );
//
//	m_pGomokuBoard->PutMove( xyListCpu[15], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[15] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[15] );
//	m_pGomokuBoard->PutMove( xyListCpu[16], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[16] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[16] );
//	m_pGomokuBoard->PutMove( xyListCpu[17], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[17] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[17] );
//	m_pGomokuBoard->PutMove( xyListCpu[18], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[18] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[18] );
//	m_pGomokuBoard->PutMove( xyListCpu[19], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[19] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[19] );
//
//	m_pGomokuBoard->PutMove( xyListCpu[20], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[20] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[20] );
//	m_pGomokuBoard->PutMove( xyListCpu[21], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[21] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[21] );
//	m_pGomokuBoard->PutMove( xyListCpu[22], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[22] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[22] );
//	m_pGomokuBoard->PutMove( xyListCpu[23], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[23] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[23] );
//	m_pGomokuBoard->PutMove( xyListCpu[24], boardScoreComputer.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, xyListCpu[24] );
//	pScore->UpdateScore( boardScoreHuman, xyListCpu[24] );
//
//	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
//	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
//
//	// Time measure:
//	clock_t t_depth1_begin = 0, t_depth1_end = 0;
//	clock_t t_depth2_begin = 0, t_depth2_end = 0;
//	clock_t t_depth3_begin = 0, t_depth3_end = 0;
//
//    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove(1);
//
//
//    // Check depth == 1
//	t_depth1_begin = clock();
//    pMinMax->SetDeep( 1 );
//    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove);
//    t_depth1_end = clock();
//    double t_depth1_all = ((double)(t_depth1_end- t_depth1_begin)/CLOCKS_PER_SEC);
//    printf("FindBestMove: depth == 1 took %f seconds to execute \n\n", t_depth1_all);
//
//    // Check depth == 2
//	t_depth2_begin = clock();
//    pMinMax->SetDeep( 2 );
//    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);
//    t_depth2_end = clock();
//    double t_depth2_all = ((double)(t_depth2_end- t_depth2_begin)/CLOCKS_PER_SEC);
//    printf("FindBestMove: depth == 2 took %f seconds to execute \n\n", t_depth2_all);
//
//    // Check depth == 3
//	t_depth3_begin = clock();
//    pMinMax->SetDeep( 3 );
//    const Board::PositionXY result3 = pMinMax->FindBestMove(nBestMove);
//    t_depth3_end = clock();
//    double t_depth3_all = ((double)(t_depth3_end- t_depth3_begin)/CLOCKS_PER_SEC);
//    printf("FindBestMove: depth == 3 took %f seconds to execute \n\n", t_depth3_all);
//
//// Results: 23.NOV.2016
////    FindBestMove: depth == 1 took 0.015000 seconds to execute
////
////    FindBestMove: depth == 2 took 0.047000 seconds to execute
////
////    FindBestMove: depth == 3 took 131.915000 seconds to execute
////
//// Results: 27.NOV.2016 ()
////    FindBestMove: depth == 1 took 0.004000 seconds to execute
////
////    FindBestMove: depth == 2 took 0.061000 seconds to execute
////
////    FindBestMove: depth == 3 took 136.573000 seconds to execute
////
//// Results: 16.MAY.2017 ()
////    FindBestMove: depth == 1 took 0.004000 seconds to execute
////
////    FindBestMove: depth == 2 took 0.872000 seconds to execute
////
////    FindBestMove: depth == 3 took 155.986000 seconds to execute
////
//// Results: 21.MAY.2017 ()
////    depth == 1 took 0.005000 seconds to execute
////
////    FindBestMove: depth == 2 took 0.870000 seconds to execute
////
////    FindBestMove: depth == 3 took 149.262000 seconds to execute
////
//// Results: 07.JUN.2017 ()
////    FindBestMove: depth == 1 took 0.005000 seconds to execute
////
////    FindBestMove: depth == 2 took 0.878000 seconds to execute
////
////    FindBestMove: depth == 3 took 158.018000 seconds to execute
}

void MinMaxTest::AnomalyReproduction1()
{
	cout<< "AnomalyReproduction1 in progress.. "<<endl;

	// This scenario fix one of the anomaly
	// - (algo returned out of board move.)

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

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

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );


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
		pScore->UpdateScore( boardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( boardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove(xyHuman[i], Board::PLAYER_B);
		pScore->UpdateScore( boardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( boardScoreHuman, xyHuman[i] );
	}

	m_pGomokuBoard->PutMove(xyListCpu[27], Board::PLAYER_A);
	pScore->UpdateScore( boardScoreComputer, xyListCpu[27] );
	pScore->UpdateScore( boardScoreHuman, xyListCpu[27] );

	const  Board::PositionXY issue  = Board::PositionXY(4, 9);

	m_pGomokuBoard->PutMove(issue, Board::PLAYER_B);
	pScore->UpdateScore( boardScoreComputer, issue );
	pScore->UpdateScore( boardScoreHuman, issue );

	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

	const uint32_t nBest = 12;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( nBest );
	vector<Board::PositionXY> candidates = {};

    pMinMax->SetDeep( 2 );

    pMinMax->FindBestMove( nBestMoves );
	const uint32_t nBestMovesSize = nBestMoves.GetSize();
	for( uint32_t i = 0; i < nBest; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}

	nBestMoves.ClearAll();

    pMinMax->SetDeep( 4 );
    const Board::PositionXY result = pMinMax->FindBestMove( nBestMoves, candidates );
    CPPUNIT_ASSERT( XY_OUT_OF_BOARD != result );
}

void MinMaxTest::AnomalyReproduction2()
{
	cout<< "AnomalyReproduction2 in progress.. "<<endl;

	//TIME TOO EXPENSIVE

//	// This scenario fix anomaly: GameRecord3_L2
//
//	//                       1 1 1 1 1
//	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//	//0 |. . . . . . . . . . . . . . .|
//	//1 |. . . . . . . . . . . . . . .|
//	//2 |. . . . . . . . . . . . . . .|
//	//3 |. . . . . . . . . . . . . . .|
//	//4 |. . . . . . x . . . . . . . .|
//	//5 |. . . . . . . o . . . . . . .|
//	//6 |. . . . . . x . o o . . . . .|
//	//7 |. . . . . x o x x o . . . . .|
//	//8 |. . . . . . . . o . x . . . .|
//	//9 |. . . . . . . . . . . . . . .|
//	//10|. . . . . . . . . . . . . . .|
//	//11|. . . . . . . . . . . . . . .|
//	//12|. . . . . . . . . . . . . . .|
//	//13|. . . . . . . . . . . . . . .|
//	//14|. . . . . . . . . . . . . . .|
//	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
//
//	// Get singletons.
//    Score* pScore = Score::GetInstance();
//	MinMax* pMinMax = MinMax::GetInstance();
//
//	// Prepare BoardScore.
//	BoardScore boardScoreComputer( Board::PLAYER_A );
//	BoardScore boardScoreHuman( Board::PLAYER_B );
//	boardScoreComputer.SetBoard( *m_pGomokuBoard );
//	boardScoreHuman.SetBoard( *m_pGomokuBoard );
//
//
//	vector< Board::PositionXY > xyListCpu{
//		Board::PositionXY(7,7),
//		Board::PositionXY(6,6),
//		Board::PositionXY(7,8),
//		Board::PositionXY(7,5),
//		Board::PositionXY(4,6),
//		Board::PositionXY(8,10)
//	};
//
//	vector< Board::PositionXY > xyHuman{
//		Board::PositionXY(6,8),
//		Board::PositionXY(8,8),
//		Board::PositionXY(7,9),
//		Board::PositionXY(5,7),
//		Board::PositionXY(7,6),
//		Board::PositionXY(6,9)
//	};
//
//	for ( uint32_t i = 0; i<xyListCpu.size(); ++i )
//	{
//		m_pGomokuBoard->PutMove( xyListCpu[i], boardScoreComputer.GetPlayer() );
//		pScore->UpdateScore( boardScoreComputer, xyListCpu[i] );
//		pScore->UpdateScore( boardScoreHuman, xyListCpu[i] );
//
//		m_pGomokuBoard->PutMove( xyHuman[i], boardScoreHuman.GetPlayer() );
//		pScore->UpdateScore( boardScoreComputer, xyHuman[i] );
//		pScore->UpdateScore( boardScoreHuman, xyHuman[i] );
//	}
//
//	// Action: User created two-triple threats. It must be blocked
//	const Board::PositionXY bestMove1 = Board::PositionXY( 6, 10 );
//	const Board::PositionXY bestMove2 = Board::PositionXY( 6, 7 );
//	const Board::PositionXY bestMove3 = Board::PositionXY( 9, 7 );
//    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove( 1 );
//
//	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
//	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
//
//	pMinMax->SetDeep( 2 );
//    const Board::PositionXY result2 = pMinMax->FindBestMove(nBestMove);
//    nBestMove.ClearAll();
//    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 || bestMove3 == result2 );
//
//	pMinMax->SetDeep( 4 );
//    const Board::PositionXY result4 = pMinMax->FindBestMove(nBestMove);
//    nBestMove.ClearAll();
//    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4 || bestMove3 == result4 );
}

void MinMaxTest::AnomalyReproduction3()
{
	cout<< "AnomalyReproduction3 in progress.. "<<endl;

	//TIME TOO EXPENSIVE

//	// This scenario fix anomaly: GameRecord7_L4
//
//	//	.                      1 1 1 1 1
//	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//	//	0 |. . . . . . . . . . . . . . .|
//	//	1 |. . . . . . . . . . . . . . .|
//	//	2 |. . . . . . . . . . . . . . .|
//	//	3 |. . . . . . . x . o . . . . .|
//	//	4 |. . . . . . . o x . . . . . .|
//	//	5 |. . . . . . . x . . . . . . .|
//	//	6 |. . . . . . x . o x . . . . .|
//	//	7 |. . . . . x . x o . . . . . .|
//	//	8 |. . . . o . x o o o . . . . .|
//	//	9 |. . . . o . o . x . . . . . .|
//	//	10|. . . . . . . . . . . . . . .|
//	//	11|. . . . . . . . . . . . . . .|
//	//	12|. . . . . . . . . . . . . . .|
//	//	13|. . . . . . . . . . . . . . .|
//	//	14|. . . . . . . . . . . . . . .|
//	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
//
//	// Get singletons.
//    Score* pScore = Score::GetInstance();
//	MinMax* pMinMax = MinMax::GetInstance();
//
//	// Prepare BoardScore.
//	BoardScore boardScoreComputer( Board::PLAYER_A );
//	BoardScore boardScoreHuman( Board::PLAYER_B );
//	boardScoreComputer.SetBoard( *m_pGomokuBoard );
//	boardScoreHuman.SetBoard( *m_pGomokuBoard );
//
//	vector< Board::PositionXY > xyListCpu{
//		Board::PositionXY(7,7),
//		Board::PositionXY(6,6),
//		Board::PositionXY(5,7),
//		Board::PositionXY(9,8),
//		Board::PositionXY(4,8),
//		Board::PositionXY(3,7),
//		Board::PositionXY(7,5),
//		Board::PositionXY(8,6),
//		Board::PositionXY(6,9)
//
//	};
//
//	vector< Board::PositionXY > xyHuman{
//		Board::PositionXY(6,8),
//		Board::PositionXY(8,8),
//		Board::PositionXY(7,8),
//		Board::PositionXY(8,7),
//		Board::PositionXY(3,9),
//		Board::PositionXY(8,9),
//		Board::PositionXY(8,4),
//		Board::PositionXY(9,6),
//		Board::PositionXY(9,4)
//	};
//
//	// 1. Put moves into board to create anomaly situation.
//	uint32_t i;
//	for ( i = 0; i < xyHuman.size(); ++i )
//	{
//		m_pGomokuBoard->PutMove( xyListCpu[i], boardScoreComputer.GetPlayer() );
//		pScore->UpdateScore( boardScoreComputer, xyListCpu[i] );
//		pScore->UpdateScore( boardScoreHuman, xyListCpu[i] );
//
//		m_pGomokuBoard->PutMove( xyHuman[i], boardScoreHuman.GetPlayer() );
//		pScore->UpdateScore( boardScoreComputer, xyHuman[i] );
//		pScore->UpdateScore( boardScoreHuman, xyHuman[i] );
//	}
//
//	m_pGomokuBoard->PutMove( Board::PositionXY( 4,7 ), boardScoreHuman.GetPlayer() );
//	pScore->UpdateScore( boardScoreComputer, Board::PositionXY( 4, 7 ) );
//	pScore->UpdateScore( boardScoreHuman, Board::PositionXY( 4 , 7 ) );
//
//	// 2. Find best nBest (12) best moves on deep 2.
//	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
//	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
//
//	const uint32_t nBest = 12;
//	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( nBest );
//	vector<Board::PositionXY> candidates = {};
//
//    pMinMax->SetDeep( 2 );
//
//    pMinMax->FindBestMove( nBestMoves );
//	const uint32_t nBestMovesSize = nBestMoves.GetSize();
//	for( uint32_t i = 0; i < nBest; ++i )
//	{
//		const Board::PositionXY el = nBestMoves.PopData().m_move;
//		candidates.push_back( el );
//	}
//
//	nBestMoves.ClearAll();
//
//	// Action: If cpu wont block human triple threat it extends it and win within 4 moves.
//	const Board::PositionXY bestMove1 = Board::PositionXY( 10, 4 );
//	const Board::PositionXY bestMove2 = Board::PositionXY( 10, 5 );
//	const Board::PositionXY bestMove3 = Board::PositionXY( 11, 4 );
//
//    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove( 1 );
//
//    // 1 and 3 depth search are pro aggressive as they always end browsing at cpu move.
//    // Like if I put here  user there and I finally here.
//
//	//	pMinMax->SetDeep( 1 );
//	//    const Board::PositionXY result1 = pMinMax->FindBestMove(nBestMove, candidates);
//	//    nBestMove.ClearAll();
//	//    CPPUNIT_ASSERT( bestMove1 == result1 || bestMove2 == result1 );
//
//	//	pMinMax->SetDeep( 2 );
//	//    const Board::PositionXY result2 = pMinMax->FindBestMove( nBestMove, candidates );
//	//    nBestMove.ClearAll();
//	//    CPPUNIT_ASSERT( bestMove1 == result2 || bestMove2 == result2 || bestMove3 == result2 );
//
//	//	pMinMax->SetDeep( 3 );
//	//    const Board::PositionXY result3 = pMinMax->FindBestMove( nBestMove, candidates );
//	//    nBestMove.ClearAll();
//	//    CPPUNIT_ASSERT( bestMove1 == result3 || bestMove2 == result3  || bestMove3 == result3 );
//
//	pMinMax->SetDeep( 4 );
//    const Board::PositionXY result4 = pMinMax->FindBestMove( nBestMove,candidates );
//    nBestMove.ClearAll();
//    CPPUNIT_ASSERT( bestMove1 == result4 || bestMove2 == result4  || bestMove3 == result4 );
}

void MinMaxTest::AnomalyReproduction4()
{
	cout<< "AnomalyReproduction4 in progress.. "<<endl;

	//TIME TOO EXPENSIVE

//	// This scenario fix anomaly: GameRecord5_L4
//
//	// Resolution: need more depth. With 5th depth algo. gets proper move.
//
//	//.                       1 1 1 1 1
//	//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//	//   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//	//0 |. . . . . . . . . . . . . . .|
//	//1 |. . . . . . . . . . . . . . .|
//	//2 |. . . . . . . . . . . . . . .|
//	//3 |. . . . . . . . . . . . . . .|
//	//4 |. . . . . . . . . . . . . . .|
//	//5 |. . . . . . o . . . . . . . .|
//	//6 |. . . . . o o x o . . . . . .|
//	//7 |. . . . . . o x . x x . . . .|
//	//8 |. . . . . . x o x o . . . . .|
//	//9 |. . . . . . . o x . . . . . .|
//	//10|. . . . . o x x x o x . . . .|
//	//11|. . . . . . . . o . . . . . .|
//	//12|. . . . . . . . . . . . . . .|
//	//13|. . . . . . . . . . . . . . .|
//	//14|. . . . . . . . . . . . . . .|
//	//  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
//
//	// Get singletons.
//    Score* pScore = Score::GetInstance();
//	MinMax* pMinMax = MinMax::GetInstance();
//
//	// Prepare BoardScore.
//	BoardScore boardScoreComputer( Board::PLAYER_A );
//	BoardScore boardScoreHuman( Board::PLAYER_B );
//	boardScoreComputer.SetBoard( *m_pGomokuBoard );
//	boardScoreHuman.SetBoard( *m_pGomokuBoard );
//
//	vector< Board::PositionXY > xyListCpu{
//		Board::PositionXY(7,7),
//		Board::PositionXY(8,8),
//		Board::PositionXY(7,9),
//		Board::PositionXY(10,6),
//		Board::PositionXY(8,6),
//		Board::PositionXY(6,7),
//		Board::PositionXY(9,8),
//		Board::PositionXY(10,8),
//		Board::PositionXY(10,7),
//		Board::PositionXY(7,10),
//		Board::PositionXY(10,10)
//
//	};
//
//	vector< Board::PositionXY > xyHuman{
//		Board::PositionXY(6,8),
//		Board::PositionXY(6,6),
//		Board::PositionXY(7,6),
//		Board::PositionXY(9,7),
//		Board::PositionXY(6,5),
//		Board::PositionXY(8,7),
//		Board::PositionXY(5,6),
//		Board::PositionXY(11,8),
//		Board::PositionXY(10,5),
//		Board::PositionXY(8,9),
//		Board::PositionXY(10,9)
//	};
//
//	// 1. Put moves into board to create anomaly situation.
//	uint32_t i;
//	for ( i = 0; i < xyHuman.size(); ++i )
//	{
//		m_pGomokuBoard->PutMove( xyListCpu[i], boardScoreComputer.GetPlayer() );
//		pScore->UpdateScore( boardScoreComputer, xyListCpu[i] );
//		pScore->UpdateScore( boardScoreHuman, xyListCpu[i] );
//
//		m_pGomokuBoard->PutMove( xyHuman[i], boardScoreHuman.GetPlayer() );
//		pScore->UpdateScore( boardScoreComputer, xyHuman[i] );
//		pScore->UpdateScore( boardScoreHuman, xyHuman[i] );
//	}
//
//	// 2. Find best nBest (12) best moves on deep 2.
//	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
//	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
//
//	const uint32_t nBest = 12;
//	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( nBest );
//	vector<Board::PositionXY> candidates = {};
//
//    pMinMax->SetDeep( 2 );
//
//    pMinMax->FindBestMove( nBestMoves );
//	const uint32_t nBestMovesSize = nBestMoves.GetSize();
//	for( uint32_t i = 0; i < nBest; ++i )
//	{
//		const Board::PositionXY el = nBestMoves.PopData().m_move;
//		candidates.push_back( el );
//	}
//
//	nBestMoves.ClearAll();
//
//	const Board::PositionXY bestMove1 = Board::PositionXY( 7, 11 );
//	const Board::PositionXY bestMove2 = Board::PositionXY( 9, 9 );
//	const Board::PositionXY bestMove3 = Board::PositionXY( 8, 10 );
//
//    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove( 1 );
//
//    // Need at least 5 depth to get best move.
//	pMinMax->SetDeep( 5 );
//    const Board::PositionXY result5 = pMinMax->FindBestMove( nBestMove, candidates );
//    nBestMove.ClearAll();
//    CPPUNIT_ASSERT( bestMove1 == result5 || bestMove2 == result5 || bestMove3 == result5 );
}

void MinMaxTest::AnomalyReproduction5()
{
	cout<< "AnomalyReproduction5 in progress.. "<<endl;

	// This scenario fix anomaly: GameRecord9_L4

	// Resolution: Checked and is resolved BTW other anomaly fix.

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

	// Get singletons.
    Score* pScore = Score::GetInstance();
	MinMax* pMinMax = MinMax::GetInstance();

	// Prepare BoardScore.
	BoardScore boardScoreComputer( Board::PLAYER_A );
	BoardScore boardScoreHuman( Board::PLAYER_B );
	boardScoreComputer.SetBoard( *m_pGomokuBoard );
	boardScoreHuman.SetBoard( *m_pGomokuBoard );

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

	// 1. Put moves into board to create anomaly situation.
	uint32_t i;
	for ( i = 0; i < xyHuman.size(); ++i )
	{
		m_pGomokuBoard->PutMove( xyListCpu[i], boardScoreComputer.GetPlayer() );
		pScore->UpdateScore( boardScoreComputer, xyListCpu[i] );
		pScore->UpdateScore( boardScoreHuman, xyListCpu[i] );

		m_pGomokuBoard->PutMove( xyHuman[i], boardScoreHuman.GetPlayer() );
		pScore->UpdateScore( boardScoreComputer, xyHuman[i] );
		pScore->UpdateScore( boardScoreHuman, xyHuman[i] );
	}

	// 2. Find best nBest (12) best moves on deep 2.
	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );

	const uint32_t nBest = 12;
	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( nBest );
	vector<Board::PositionXY> candidates = {};

    pMinMax->SetDeep( 2 );

    pMinMax->FindBestMove( nBestMoves );
	const uint32_t nBestMovesSize = nBestMoves.GetSize();
	for( uint32_t i = 0; i < nBest; ++i )
	{
		const Board::PositionXY el = nBestMoves.PopData().m_move;
		candidates.push_back( el );
	}

	nBestMoves.ClearAll();

    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove( 1 );

	pMinMax->SetDeep( 4 );
    const Board::PositionXY result4 = pMinMax->FindBestMove( nBestMove, candidates );
    nBestMove.ClearAll();

	// Best strategy is:

	// a. Blocking human threats.
	const Board::PositionXY bestMove1 = Board::PositionXY( 8,6 );
	const Board::PositionXY bestMove2 = Board::PositionXY( 8,12 );
	const Board::PositionXY bestMove3 = Board::PositionXY( 11,9 );

	const bool defend = bestMove1 == result4 || bestMove2 == result4 || bestMove3 == result4;

	// b. Increasing itself attack:
	m_pGomokuBoard->PutMove( result4, boardScoreComputer.GetPlayer() );
	pScore->UpdateScore( boardScoreComputer, result4 );
	pScore->UpdateScore( boardScoreHuman, result4 );
	const bool attack = ( 0 < boardScoreComputer.GetNumberOfRecognizedThreat( ThreatFinder::THREAT_4_CASE_A ) ) ||
			 	 	    ( 0 < boardScoreComputer.GetNumberOfRecognizedThreat( ThreatFinder::THREAT_4_CASE_C ) ) ||
						( 0 < boardScoreComputer.GetNumberOfRecognizedThreat( ThreatFinder::THREAT_4_CASE_B ) ) ||
						( 0 < boardScoreComputer.GetNumberOfRecognizedThreat( ThreatFinder::THREAT_3_CASE_A ) ) ||
						( 0 < boardScoreComputer.GetNumberOfRecognizedThreat( ThreatFinder::THREAT_3_CASE_C ) );


    CPPUNIT_ASSERT( defend || attack );

}

void MinMaxTest::AnomalyReproduction6()
{
	cout<< "AnomalyReproduction6 in progress.. "<<endl;

	//TIME TOO EXPENSIVE

//	// This scenario fix anomaly:
//
//	// Resolution: More depth (at least 5)
//
//	//	.                      1 1 1 1 1
//	//	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//	//	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//	//	0 |. . . . . . . . . . . . . . .|
//	//	1 |. . . . . . . . . . . . . . .|
//	//	2 |. . . . . . . . . . . . . . .|
//	//	3 |. . . . . . . . . . . . . . .|
//	//	4 |. . . . . . . . . . . . . . .|
//	//	5 |. . . . . . o . . . . . . . .|
//	//	6 |. . . . . . x x . . . . . . .|
//	//	7 |. . . . . . o x x . . . . . .|
//	//	8 |. . . . . . . x o x . . . . .|
//	//	9 |. . . . . . o o o x . . . . .|
//	//	10|. . . . . . . o . . . . . . .|
//	//	11|. . . . . . . . . . . . . . .|
//	//	12|. . . . . . . . . . . . . . .|
//	//	13|. . . . . . . . . . . . . . .|
//	//	14|. . . . . . . . . . . . . . .|
//	//	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
//
//
//	// Get singletons.
//    Score* pScore = Score::GetInstance();
//	MinMax* pMinMax = MinMax::GetInstance();
//
//	// Prepare BoardScore.
//	BoardScore boardScoreComputer( Board::PLAYER_A );
//	BoardScore boardScoreHuman( Board::PLAYER_B );
//	boardScoreComputer.SetBoard( *m_pGomokuBoard );
//	boardScoreHuman.SetBoard( *m_pGomokuBoard );
//
//	vector< Board::PositionXY > xyListCpu{
//		Board::PositionXY(6,6),
//		Board::PositionXY(6,7),
//		Board::PositionXY(7,7),
//		Board::PositionXY(7,8),
//		Board::PositionXY(8,7),
//		Board::PositionXY(8,9),
//		Board::PositionXY(9,9)
//	};
//
//	vector< Board::PositionXY > xyHuman{
//		Board::PositionXY(5,6),
//		Board::PositionXY(7,6),
//		Board::PositionXY(9,6),
//		Board::PositionXY(8,8),
//		Board::PositionXY(9,7),
//		Board::PositionXY(9,8),
//		Board::PositionXY(10,7)
//	};
//
//	// 1. Put moves into board to create anomaly situation.
//	uint32_t i;
//	for ( i = 0; i < xyHuman.size(); ++i )
//	{
//		m_pGomokuBoard->PutMove( xyListCpu[i], boardScoreComputer.GetPlayer() );
//		pScore->UpdateScore( boardScoreComputer, xyListCpu[i] );
//		pScore->UpdateScore( boardScoreHuman, xyListCpu[i] );
//
//		m_pGomokuBoard->PutMove( xyHuman[i], boardScoreHuman.GetPlayer() );
//		pScore->UpdateScore( boardScoreComputer, xyHuman[i] );
//		pScore->UpdateScore( boardScoreHuman, xyHuman[i] );
//	}
//
//	// 2. Find best nBest (12) best moves on deep 2.
//	pMinMax->SetBoardScore( boardScoreComputer, boardScoreHuman );
//	pMinMax->SetInitialPlayer( boardScoreComputer.GetPlayer() );
//
//	const uint32_t nBest = 12;
//	SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( nBest );
//	vector<Board::PositionXY> candidates = {};
//
//    pMinMax->SetDeep( 2 );
//
//    pMinMax->FindBestMove( nBestMoves );
//	const uint32_t nBestMovesSize = nBestMoves.GetSize();
//	for( uint32_t i = 0; i < nBest; ++i )
//	{
//		const Board::PositionXY el = nBestMoves.PopData().m_move;
//		candidates.push_back( el );
//	}
//
//	const Board::PositionXY bestMove1 = Board::PositionXY( 6, 9 );
//
//	nBestMoves.ClearAll();
//
//    SearchTreeAlgorithmIf::PriorityQueueScore nBestMove( 1 );
//
//	pMinMax->SetDeep( 5 );
//    const Board::PositionXY result5 = pMinMax->FindBestMove( nBestMove, candidates );
//    nBestMove.ClearAll();
//    CPPUNIT_ASSERT( bestMove1 == result5 );
}
