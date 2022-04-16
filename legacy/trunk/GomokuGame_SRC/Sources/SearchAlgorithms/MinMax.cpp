/////////////////////////////////////////////////////////////////////////////////////////
/// @file MinMax.cpp
///
/// MinMax algorithm implementation.
///
/// @par Full Description.
/// MinMax algorithm implementation.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 03-May-2016 Initial revision.
/// - zhalat 20-May-2016 Implementation of GameTreeBrowsing() with recursion.
/// - zhalat 04-Oct-2016 Increases performance of generating candidates by introduce VectorLight
///                      instead of stl::vector in time critical region code.
/// - zhalat 12-Dec-2016 UpdateCandidate updated for extended gaps for threats from EXTENDED_NEIGHBORHOOD list.
/// - zhalat 21-Dec-2016 Algorithm chooses not only move that maximalize cpu score but also minimalize opponent score.
/// - zhalat 21-Dec-2017 Adjusting coefficients.
/// - zhalat 29-Dec-2017 Add game tree logs.
/// - zhalat 04-Feb-2018 VectorLight repleaced by VectorUnique.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <vector>       // For vector container.
#include <set>          // For set container.
#include <ctime>        // For time to set seed for random.
#include <limits>       // For numeric_limits.
#include <algorithm>    // std::sort, uses in debbug mode.

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "MinMax.hpp"         		// For MinMax declaration.
#include "IteratorIf.hpp"     		// For iterator interface.
#include "Score.hpp"          		// For Score instance.
#include "BoardScore.hpp"     		// For BoardScore definition.
#include "VectorUnique.hpp"    		// For VectorUnique container.
#include "ThreatsBloodRelation.hpp" // For EXTENDED_NEIGHBORHOOD[].

// FORWARD REFERENCES
//#define DEBBUG_MODE
// Use those flags to prints board while debbuging. Change to true via debbguger.
static bool LogStart = false;

/// Converts vector xy to vector fieldPosition.
static void VctrXy2VctrPosition( const vector<Board::PositionXY>& rVctrXy, vector<Board::PositionField>& rVctrPos, const uint32_t size );

/// Handler for instance.
MinMax* MinMax::m_pInstance = NULL;

/// Get instance of Score.
MinMax* MinMax::GetInstance()
{
    if ( NULL == m_pInstance )
    {
        m_pInstance = new MinMax( SearchTreeAlgorithmIf::DEFAULT_DEPTH, "MinMax" );
        return m_pInstance;
    }
    else
    {
        return m_pInstance;
    }
}

/// Finds the best possible move.
Board::PositionXY MinMax::FindBestMove( PriorityQueueScore& rBestMove, const vector<Board::PositionXY>& rInitCandidates )
{
    using namespace std;

    // Check that all necessary information was provided.
    assert( 0 < m_DeepSearch );
    assert( NULL != m_pBoardScoreCpu );
    assert( NULL != m_pBoardScoreHuman );
    assert( Board::PLAYER_EMPTY != m_CurrentPlayerMove );

    // We want to have deep copy of BoardScore member to not modify originals.
    BoardScoreCopy();

    // Generate list of candidate movies.
    const bool isInitCandidatesProvided = !rInitCandidates.empty();
    VectorUniqueType initCandidates;

    if( isInitCandidatesProvided )
    {
    	vector<Board::PositionField> initCandidatesStl;
    	VctrXy2VctrPosition( rInitCandidates, initCandidatesStl, m_pBoard->GetSize() );
    	initCandidates = initCandidatesStl;

        // Get extended fields for 2A, 3A, 3C.
        std::vector<Board::PositionField> exGaps;
        for( uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i )
        {
        	const ThreatFinder::KindOfThreats kindOfThreat = ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[ i ];
        	m_pBoardScoreCpu->GetExGaps( exGaps, kindOfThreat );
        	m_pBoardScoreHuman->GetExGaps( exGaps, kindOfThreat );
        }

        // Add extended gap iif the place has not been added yet.
        for( uint32_t i = 0; i < exGaps.size(); ++i )
        {
        	const Board::PositionField data = exGaps[i];
    		const bool isNewCandidate = !initCandidates.IsPresent( static_cast<uint32_t>( data ) );

    		if( isNewCandidate )
    		{
    			initCandidates.Insert( data );
    		}
        }
    }
    else
    {
        vector<Board::PositionField> initCandidatesStl = GenerateCand();
        initCandidates = initCandidatesStl;
    }

    // Validate number of candidates.
    const uint32_t avaliableCandidats = initCandidates.GetNumberOfElements();
    if ( SearchTreeAlgorithmIf::MAX_CAND < avaliableCandidats )
    {
        // Do sth to reduce or put event to log.
    }
    else if ( 0 == avaliableCandidats )
    {
        assert( false );
    }

    // When the board goes to limit, it is impossible to go deeper that number of vacant fields.
    const uint32_t currentDeepSearch = m_DeepSearch;
    m_DeepSearch = ( avaliableCandidats < m_DeepSearch ) ? avaliableCandidats : m_DeepSearch;

    vector<Board::PositionXY> treeTracker;

#if defined( DEBBUG_MODE )
    m_Logger.NewRecord( Logger::LOG_MINMAX_TREE_RECORD_FILE_NAME );
    m_Logger.NewRecord( Logger::LOG_MINMAX_BOARD_RECORD_FILE_NAME );
#endif

    ScoreForMove retVal = GameTreeBrowsing( initCandidates, rBestMove, treeTracker );

    m_DeepSearch = currentDeepSearch;

    return retVal.m_move;
}

/// Browses the game-tree to find best move.
SearchTreeAlgorithmIf::ScoreForMove MinMax::GameTreeBrowsing( VectorUniqueType& rCandidates, PriorityQueueScore& bestMoves, vector<Board::PositionXY>& treeTracker, const uint32_t deep )
{
	uint32_t logger = 0;

    // Get singleton instance only once.
    static Score& rScore = *Score::GetInstance();

    // Player who has right to put move now.
    const Board::Player currentPlayerMove = WhoIsCurrentMove();
    const Board::Player cumputerPlayer = m_pBoardScoreCpu->GetPlayer();
    const bool isMaximizingPlayer = ( currentPlayerMove == cumputerPlayer );

    // Initialize best move.
    ScoreForMove bestMove;

    if ( isMaximizingPlayer )
    {
        bestMove.m_score = std::numeric_limits<int>::min();
    }
    else
    {
        bestMove.m_score = std::numeric_limits<int>::max();
    }

    if ( deep == m_DeepSearch )    // We reach the leaf.
    {
    	if( isMaximizingPlayer )
    	{
            bestMove.m_score = (float)(m_pBoardScoreCpuCopy->GetScore())  -  static_cast<int>( m_pBoardScoreHumanCopy->GetScore() );
    	}
    	else
    	{
            bestMove.m_score = -static_cast<int>( (float)(m_pBoardScoreHumanCopy->GetScore()) ) +  m_pBoardScoreCpuCopy->GetScore() ;
    	}

   		bestMove.m_move = treeTracker.front();
        return bestMove;
    }

    // Make snapshot unless we reach the leaf.
    MakeSnapshot( deep );

    // Go thru all candidates.
    for ( VectorUniqueTypeIterator pIterator = rCandidates.GetIteratorBegin(); pIterator != rCandidates.GetIteratorEnd(); )
    {
    	const Board::PositionField currentCandidat = *pIterator;
    	++pIterator;

    	// Get candidate which will put on board.
    	const Board::PositionXY currentCandidatXY( m_pBoardCopy->GetSize(), currentCandidat );
        const Board::Player currentPlayerForMove = WhoIsCurrentMove();

        // Put new move into board and keep track.
        assert( m_pBoardCopy->PutMove( currentCandidat, currentPlayerForMove ) );
        rScore.UpdateScore( *m_pBoardScoreCpuCopy, currentCandidatXY,  1 );
        rScore.UpdateScore( *m_pBoardScoreHumanCopy, currentCandidatXY, 1 );

        treeTracker.push_back( currentCandidatXY );

        const bool isGameOver = m_pBoardScoreCpuCopy->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_WINNER ) > 0 || m_pBoardScoreHumanCopy->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_WINNER ) > 0;
        ScoreForMove leafScore;

        if( !isGameOver )
        {
            // Create candidates list for next move.
        	VectorUniqueType nextCandidates = UpdateCand( rCandidates, currentCandidat );

            // The next move is rivals'.
            SwitchPlayer();

        	// Go one move deeper.
        	leafScore = GameTreeBrowsing( nextCandidates, bestMoves, treeTracker, deep + 1 );
        }
        else if( isMaximizingPlayer )
        {
        	leafScore.m_score = Score::THREAT_WINNER_SCORE;
        	leafScore.m_move = treeTracker.front();
        	SwitchPlayer();
        }
        else
        {
        	leafScore.m_score = -Score::THREAT_WINNER_SCORE;
        	leafScore.m_move = treeTracker.front();
        	SwitchPlayer();
        }

#if defined( DEBBUG_MODE )
        if( LogStart )
        {
			++logger;

			ScoreForMove log;
			log.m_move = treeTracker.back();
			log.m_score = leafScore.m_score;

			m_Logger.AddEntryToRecord( deep, logger, log );
			m_Logger.AddEntryToRecord( deep, logger, *m_pBoardCopy );
			m_Logger.AddEntryToRecord( deep, logger, *m_pBoardScoreCpuCopy );
			m_Logger.AddEntryToRecord( deep, logger, *m_pBoardScoreHumanCopy );
        }
#endif

        // Take best move for cpu when is cpu move.
        // Take best move for human when is human move.
        const bool isBestForCpu = ( ( isMaximizingPlayer ) && ( leafScore.m_score > bestMove.m_score ) );
        const bool isOneOfTheBestForCpu = ( ( isMaximizingPlayer ) && ( 0 == deep ) );
        const bool isBestForHuman = ( ( !isMaximizingPlayer ) && ( leafScore.m_score < bestMove.m_score ) );

        if ( isBestForCpu )
        {
            bestMove = leafScore;
        }

        if( isOneOfTheBestForCpu )
        {
        	bestMoves.PushData( leafScore );
        }

        if ( isBestForHuman )
        {
            bestMove = leafScore;
        }

        // Crawl thru tree.
        if ( pIterator == rCandidates.GetIteratorEnd() )
        {
            // Go one level up in the tree.
        	RemoveSnapshot( deep );

        	if ( deep > 0 )
        	{
            	RetreiveSnapshot( deep - 1 );
        	}
        	else
        	{
        		// all work done!
        	}

        	m_pBoardCopy->RemoveMove( treeTracker.back() );
        	treeTracker.pop_back();
        }
        else if( isGameOver )
        {
            // Go one level up in the tree.
        	RemoveSnapshot( deep );
        	if ( deep > 0 )
        	{
            	RetreiveSnapshot( deep - 1 );
        	}

        	m_pBoardCopy->RemoveMove( treeTracker.back() );
        	treeTracker.pop_back();

        	SwitchPlayer();

        	// There is no point browsing thru the rest moves.
        	break;
        }
        else
        {
        	// Undo move, and keep track.
        	m_pBoardCopy->RemoveMove( currentCandidatXY );
        	treeTracker.pop_back();

        	RetreiveSnapshot( deep );
        }

        SwitchPlayer();
    }

    // When all work is done.
    return bestMove;
}

/// Generate list of candidate moves.
vector< Board::PositionField > MinMax::GenerateCand() const
{
    // Algorithm finds those fields which:
    // a) are vacant
    // b) adhere to not vacant field
	// c) extends 3A, 3B  and all 4th threats
    // See below - fields assigned with dot will be returned.
	//	 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	|. . . . . . . . . . . . . . .|
	//	|. . . . . . . . . . . . . . .|
	//	|. . . . . . . . . . . . . . .|
	//	|. . + + + . . . . . . . . . .|
	//	|. . + O + + . . . . + . . . .|
	//	|. . + + X + . . + + . . . . .|
	//	|. . . + + + . + X + . . . . .|
	//	|. . . . . . + X + . . . . . .|
	//	|. . . . . + X + . . . . . . .|
	//	|. . . . . + + . . . . . . . .|
	//	|. . . . + . . . . . . . . . .|
	//	|. . . . . . . . . . . . . . .|

    vector<graph::Node> neighborhood;
    const Board& board = *m_pBoard;

    // Get neighborhoods:
    const auto citr = board.GetIterator();
    for( citr->SetToBase(); citr->HasNext(); )
    {
        if ( Board::PLAYER_EMPTY != citr->GetNext() )
        {
            // GetNext() increments collection index to the next.
            // To take current index, decrementing is needed.
            const uint32_t index = citr->GetIndex() - 1;

            // Make some nasty conversions.
            const Board::PositionField field = static_cast<Board::PositionField>( index );
            const Board::PositionXY xy = Board::PositionXY( board.GetSize(), field );

            // Get neighbors.
            vector<graph::Node> neighbors = board.GetNeighborhood( xy );

            // Concatenate vectors.
            neighborhood.insert( neighborhood.end(), neighbors.begin(), neighbors.end() );
        }
    }

    // Remove not vacant position:
    for ( auto pos = neighborhood.begin(); pos != neighborhood.end(); )
    {
    	const Board::PositionXY xy = Board::PositionXY( board.GetSize(), static_cast<Board::PositionField>(*pos) );

        if( board.GetMove( xy ) != Board::PLAYER_EMPTY )
        {
        	// Remove position - iterator automatically points the next element.
            neighborhood.erase( pos );
        }
        else
        {
            ++pos;
        }
    }

    // Get extended fields for 2A, 3A, 3C for CPU.
    std::vector<Board::PositionField> exGaps;
    for( uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i )
    {
    	const ThreatFinder::KindOfThreats kindOfThreat = ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[ i ];
    	m_pBoardScoreCpu->GetExGaps( exGaps, kindOfThreat );
    	m_pBoardScoreHuman->GetExGaps( exGaps, kindOfThreat );
    }

    // Concatenate vectors.
    neighborhood.insert( neighborhood.end(), exGaps.begin(), exGaps.end() );

    // Remove duplication:
    std::set<graph::Node> unique( neighborhood.begin(), neighborhood.end() );

    vector< Board::PositionField > retVal( unique.begin(), unique.end() );
    return retVal;
}

/// Generate list of candidate moves.
MinMax::VectorUniqueType MinMax::UpdateCand( const VectorUniqueType& rCandidates, uint32_t position ) const
{
    const Board& board = *m_pBoardCopy;

	// Get neighbors of current position.
    const Board::Neighbours& neighbours = board.GetNeighborhood( static_cast<Board::PositionField>( position ) );

    VectorUniqueType neighborhood = rCandidates;

	for ( uint32_t k = 0; k < neighbours.m_NeighbourhoodSize; ++k )
	{
		const Board::PositionField dana = neighbours.m_Neighbourhood[ k ];

		const bool isCandidateValid = ( board.GetMove( dana ) == Board::PLAYER_EMPTY ) && ( !neighborhood.IsPresent( dana ) );

		if( isCandidateValid )
		{
			neighborhood.Insert( dana );
		}
	}

	// Get extended gaps.
    std::vector<Board::PositionField> exGaps;
    for( uint32_t i = 0; i < ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD_SIZE; ++i )
    {
    	const ThreatFinder::KindOfThreats kindOfThreat = ThreatsBloodRelation::EXTENDED_NEIGHBORHOOD[ i ];
    	m_pBoardScoreCpuCopy->GetExGaps( exGaps, kindOfThreat );
    	m_pBoardScoreHumanCopy->GetExGaps( exGaps, kindOfThreat );
    }

    // Add extended gap iif the place has not been added yet.
    for( uint32_t i = 0; i < exGaps.size(); ++i )
    {
    	const Board::PositionField dana = exGaps[i];
		const bool isNewCandidate = !neighborhood.IsPresent( dana );

		if( isNewCandidate )
		{
			neighborhood.Insert( dana );
		}
    }

    assert( true == neighborhood.Remove( position ) );

#if defined( DEBBUG_MODE )
	// Keep order. It helps for investigation while debbuging.
	vector< Board::PositionField > order;
	IteratorIf<uint32_t>* pIterator = neighborhood.GetIterator();

    for ( pIterator->SetToBase(); pIterator->HasNext(); )
    {
    	const Board::PositionField positionField = static_cast< Board::PositionField >( pIterator->GetNext() );
    	order.push_back( positionField );
    }
    std::sort( order.begin(), order.end() );

    neighborhood.Clear();
    neighborhood = order;
#endif

	return neighborhood;
}

/// Do deep copy of Board Score.
void MinMax::BoardScoreCopy()
{
    assert( NULL != m_pBoardScoreCpu );
    assert( NULL != m_pBoardScoreHuman );

    // Delete previous state of game.
    delete m_pBoardScoreCpuCopy;
    delete m_pBoardScoreHumanCopy;
    delete m_pBoardCopy;

    // Do copy of m_pBoardScores.
    m_pBoardScoreCpuCopy = new BoardScore( *m_pBoardScoreCpu );
    m_pBoardScoreHumanCopy = new BoardScore( *m_pBoardScoreHuman );
    assert( NULL != m_pBoardScoreCpuCopy );
    assert( NULL != m_pBoardScoreHumanCopy );

    // Then provide copy of Board.
    m_pBoardCopy = &m_pBoard->Clone();
    m_pBoardScoreCpuCopy->SetBoard( *m_pBoardCopy );
    m_pBoardScoreHumanCopy->SetBoard( *m_pBoardCopy );
}

/// Make snapshot on provided depth.
void MinMax::MakeSnapshot( uint32_t depth )
{
    assert( NULL != m_pBoardScoreCpuCopy );
    assert( NULL != m_pBoardScoreHumanCopy );
    assert( NULL == m_SnapshotContainerCpu[ depth ] );
    assert( NULL == m_SnapshotContainerHuman[ depth ] );

    // Make snapshot of BoardScoreCopy for each player.
    m_SnapshotContainerCpu[ depth ] = new BoardScore( *m_pBoardScoreCpuCopy );
    m_SnapshotContainerHuman[ depth ] = new BoardScore( *m_pBoardScoreHumanCopy );
    assert( NULL != m_SnapshotContainerCpu[ depth ] );
    assert( NULL != m_SnapshotContainerHuman[ depth ] );
}

/// Retrieve snapshot on provided depth.
void MinMax::RetreiveSnapshot( uint32_t depth )
{
	assert( NULL != m_SnapshotContainerCpu[ depth ] );
	assert( NULL != m_SnapshotContainerHuman[ depth ] );
	*m_pBoardScoreCpuCopy = *m_SnapshotContainerCpu[ depth ];
	*m_pBoardScoreHumanCopy = *m_SnapshotContainerHuman[ depth ];
}

/// Remove snapshot on provided depth.
void MinMax::RemoveSnapshot( uint32_t depth )
{
    assert( NULL != m_SnapshotContainerCpu[ depth ] );
    assert( NULL != m_SnapshotContainerHuman[ depth ] );
    delete m_SnapshotContainerCpu[ depth ];
    delete m_SnapshotContainerHuman[ depth ];
    m_SnapshotContainerCpu[ depth ] = NULL;
    m_SnapshotContainerHuman[ depth ] = NULL;
}

// Converts vector xy to vectro fieldPosition.
static void VctrXy2VctrPosition( const vector<Board::PositionXY>& rVctrXy, vector<Board::PositionField>& rVctrPos, const uint32_t boardSize )
{
	for( auto cit = rVctrXy.begin(); cit != rVctrXy.end(); ++cit )
	{
		const Board::PositionField data( boardSize, *cit );
		rVctrPos.push_back( data );
	}
}

/***************************************************************************
 *   Copyright (C) 2018 by Zbigniew Halat                                  *
 *   zby.halat@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/
