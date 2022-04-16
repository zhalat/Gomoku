/////////////////////////////////////////////////////////////////////////////////////////
/// @file GomokuGame.hpp
///
/// Gomoku game logic class definition.
///
/// @par Full Description.
/// Gomoku game logic and UI - user interface class definition.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 25-Jun-2016 Initial revision.
/// - zhalat 01-Jan-2017 The second move for white is taken from opening book.
/// - zhalat 20-Apr-2017 Adjust class to be able running from QT.
/// - zhalat 29-May-2017 Adding randomize.
/// - zhalat 28-Oct-2017 Implement GetInitCandidates().
/// - zhalat 04-Feb-2018 VectorLight repleaced by VectorUnique.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <time.h>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "GomokuGame.hpp"
#include "MinMax.hpp"
#include "AlphaBeta.hpp"
#include "GomokuBoard.hpp"
#include "BoardScore.hpp"
#include "OpenBook.hpp"
#include "PriorityQueue.hpp"
#include "ThreatsBloodRelation.hpp"
#include "VectorUnique.hpp"
#if defined ( GUI_GOMOKU_GAME )
#include "GomokuInputStream.h"
#endif

// FORWARD REFERENCES
#define DISPLAY_ON true

using namespace std;

#warning "XY_OUT_OF_BOARD definie in in Board.hpp and remove duplication thru many files."
// Point beyond the board. Useful for initialization.
const Board::PositionXY XY_OUT_OF_BOARD = Board::PositionXY( Board::PositionXY::INVALID_FIELD, Board::PositionXY::INVALID_FIELD );

/// Configure base game parameter.
void GomokuGame::Init( const uint32_t size,
                       const Board::Player humanColor,
                       const TwoPlayersGame::Level level,
                       const bool isRandomize,
                       const uint32_t maxTime,
                       std::istream& inStream,
                       std::ostream& outStream )
{
	srand (time(NULL));

    // Create file to record game.
    if( !m_Logger.IsRecordExist( Logger::LOG_GAME_RECORD_FILE_NAME ) )
    {
    	try{
    		m_Logger.NewRecord( Logger::LOG_GAME_RECORD_FILE_NAME );
    	}
    	catch(...)
    	{
    		assert( false );
    	}
    }
    else
    {
    	//Clear record.
    	m_Logger.ClearRecord( Logger::LOG_GAME_RECORD_FILE_NAME );
    }

    assert( ( size >= GomokuBoard::MIN_GOMOKU_BOARD_SIZE ) &&
            ( size <= GomokuBoard::MAX_GOMOKU_BOARD_SIZE ) );

    m_pBoard = new GomokuBoard( size );
    assert( m_pBoard );

    m_HumanColor = humanColor;
    m_ComputerColor = ( humanColor == Board::PLAYER_A ) ?  Board::PLAYER_B : Board::PLAYER_A;

    // Board score for both players. Keeps score and threats which player was able to set.
    m_pBoardScoreHuman = new BoardScore( m_HumanColor );
    m_pBoardScoreCpu = new BoardScore( m_ComputerColor );
    assert( m_pBoardScoreHuman );
    assert( m_pBoardScoreCpu );

    m_pBoardScoreHuman->SetBoard( *m_pBoard );
    m_pBoardScoreCpu->SetBoard( *m_pBoard );

    assert ( LEVEL_NONE != level );
    m_Level = level;

    // Depending on game level, choose proper algorithm.
    // It will set default settings for the algo. but you still have control over algo. settings (like set deep, tactics).
    // Just use SearchTreeAlgorithmIf's interface.
    SetSearchAlgorithm( level );

    if( Board::PLAYER_A == m_ComputerColor )
    {
    	m_Logger.FirstPlayer( Logger::LOG_GAME_RECORD_FILE_NAME, true );
    }
    else
    {
    	m_Logger.FirstPlayer( Logger::LOG_GAME_RECORD_FILE_NAME, false );
    }
    m_IsRandomize = isRandomize;
    m_MaxTime = maxTime;

    pInputStream = &inStream;
    pOutputStream = &outStream;
}

/// Starts game.
void GomokuGame::Play()
{
    static Score* const pScore = Score::GetInstance();

    // Keeps human move read from input stream.
    Board::PositionXY humanMove = XY_OUT_OF_BOARD;
    Board::PositionXY cpuMove = XY_OUT_OF_BOARD;

    // 'x' means white - always starts.
    bool isComputerMove = ( Board::PLAYER_A == m_ComputerColor ) ? true : false;

    enum PlayStateMachine
    {
        PLAY_STATE_MACHINE_NONE,
        START,
        CPU_WHITE_FIRST_MOVE,
        CPU_WHITE_OPEN_BOOK_MOVE,
        CPU_BLACK_OPEN_BOOK_MOVE,
        CPU_AI_MOVE,
        HUMAN_MOVE,
        HUMAN_VALIDATION_MOVE,
        CHECK_WINNER,
        DISPLAY,
        GAME_OVER,
    };

    PlayStateMachine playStateMachine = START;
    PlayStateMachine playStateMachineShadow = PLAY_STATE_MACHINE_NONE;
    bool isEnd = false;

    while( !isEnd )
    {
        switch( playStateMachine )
        {
            case START:
            {
                assert ( m_pSearchAlgorithm );
                assert ( m_Level != LEVEL_NONE );
                assert ( NULL != pInputStream );
                assert ( NULL != pOutputStream );

                m_pSearchAlgorithm->SetInitialPlayer( m_ComputerColor );
                m_pSearchAlgorithm->SetBoardScore( *m_pBoardScoreCpu, *m_pBoardScoreHuman );

                playStateMachineShadow = CHECK_WINNER;
                if( Board::Player::PLAYER_A == m_ComputerColor )
                {
                	// Don't display empty board when cpu starts.
                	playStateMachine = CHECK_WINNER;
                }
                else
                {
                	playStateMachine = DISPLAY;
                }
            }
            break;

            case CPU_WHITE_FIRST_MOVE:
            {
                // Put the first move on center of the board.
                const Board::PositionXY firstMove( m_pBoard->GetSize()/2, m_pBoard->GetSize()/2 );
                cpuMove = firstMove;
                m_pBoard->PutMove( firstMove, m_ComputerColor );
                pScore->UpdateScore( *m_pBoardScoreCpu, cpuMove );
                pScore->UpdateScore( *m_pBoardScoreHuman, cpuMove );

                isComputerMove = false;

                playStateMachineShadow = CHECK_WINNER;
                playStateMachine = DISPLAY;
            }
            break;

            case CPU_WHITE_OPEN_BOOK_MOVE:
            {
                assert( Board::PLAYER_A == m_ComputerColor );

                cpuMove = OpenBook::GetBestThirdWhiteMove( *m_pBoard );

                if( XY_OUT_OF_BOARD == cpuMove )
                {
#warning "Don't use AI. Rand one of the following spot. Implemment it in opening book"
                    // game is neither direct nor indirect.
                    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
                    //0 |. . . . . . . . . . . . . . .|
                    //1 |. . . . . . . . . . . . . . .|
                    //2 |. . . . . . . . . . . . . . .|
                    //3 |. . . . . . . . . . . . . . .|
                    //4 |. . . . . c . c . . . . . . .|
                    //5 |. . . . c . . . c . . . . . .|
                    //6 |. . . . . . x . . . . . . . .|
                    //7 |. . . . c . . . c . . . . . .|
                    //8 |. . . . . c . c . . . . . . .|
                    //9 |. . . . . . . . . . . . . . .|
                    SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( 1 );
                    cpuMove = m_pSearchAlgorithm->FindBestMove( nBestMoves );
                }

                m_pBoard->PutMove( cpuMove, m_ComputerColor );

                pScore->UpdateScore( *m_pBoardScoreCpu, cpuMove );
                pScore->UpdateScore( *m_pBoardScoreHuman, cpuMove );

                isComputerMove = false;

                playStateMachineShadow = CHECK_WINNER;
                playStateMachine = DISPLAY;
            }
            break;

            case CPU_BLACK_OPEN_BOOK_MOVE:
            {
                assert( Board::PLAYER_B == m_ComputerColor );

                cpuMove = OpenBook::GetBestSecondBlackMove( *m_pBoard );

                m_pBoard->PutMove( cpuMove, m_ComputerColor );

                pScore->UpdateScore( *m_pBoardScoreCpu, cpuMove );
                pScore->UpdateScore( *m_pBoardScoreHuman, cpuMove );

                isComputerMove = false;

                playStateMachineShadow = CHECK_WINNER;
                playStateMachine = DISPLAY;
            }
            break;

            case CPU_AI_MOVE:
            {
                cpuMove = GetBestMove();

                m_pBoard->PutMove( cpuMove, m_ComputerColor );

                pScore->UpdateScore( *m_pBoardScoreCpu, cpuMove );
                pScore->UpdateScore( *m_pBoardScoreHuman, cpuMove );

                isComputerMove = false;

                playStateMachineShadow = CHECK_WINNER;
                playStateMachine = DISPLAY;

            }
            break;

            case HUMAN_MOVE:
            {
                humanMove = GetUserMove();
                playStateMachineShadow = PLAY_STATE_MACHINE_NONE;
                playStateMachine = HUMAN_VALIDATION_MOVE;
            }
            break;

            case HUMAN_VALIDATION_MOVE:
            {
                if( ValidateMove( humanMove ) )
                {
                    m_pBoard->PutMove( humanMove, m_HumanColor );
                    pScore->UpdateScore( *m_pBoardScoreCpu, humanMove );
                    pScore->UpdateScore( *m_pBoardScoreHuman, humanMove );
                    humanMove = XY_OUT_OF_BOARD;

                    isComputerMove = true;

                    playStateMachineShadow = CHECK_WINNER;
                    playStateMachine = DISPLAY;
                }
                else
                {
                    *pOutputStream<<INVALID_MOVE_MSG<<TERMINATOR_MSG;

                    playStateMachineShadow = PLAY_STATE_MACHINE_NONE;
                    playStateMachine = HUMAN_MOVE;
                }

                pOutputStream->flush();
            }
            break;

            case CHECK_WINNER:
            {
                bool isCpuWhiteOpening = ( isComputerMove && ( 2 == m_pBoard->GetMoveNumber() ) );
                bool isCpuBlackOpening = ( isComputerMove && ( 1 == m_pBoard->GetMoveNumber() ) );
                bool isCpuFirstMove = ( isComputerMove && ( 0 == m_pBoard->GetMoveNumber() ) );

                if( WinnerCheck( m_ComputerColor ) )
                {
                    *pOutputStream<<LOOSER_MSG;
                    const ThreatFinder::ThreatLocation& rThreatLocation = m_pBoardScoreCpu->GetThreatList( ThreatFinder::THREAT_WINNER ).front();
                    for( uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS; ++i )
                    {
                    	const Board::PositionXY rXy = rThreatLocation.m_ThreatDetails.m_MyPawns[ i ];
                    	*pOutputStream<<WINNER_MOVIES_MARK<<rXy;
                    }

                	playStateMachine = GAME_OVER;
                	playStateMachineShadow = GAME_OVER;
                }
                else if( WinnerCheck( m_HumanColor ) )
                {
                    *pOutputStream<<WINNER_MSG;
                    const ThreatFinder::ThreatLocation& rThreatLocation = m_pBoardScoreHuman->GetThreatList( ThreatFinder::THREAT_WINNER ).front();
                    for( uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS; ++i )
                    {
                    	const Board::PositionXY rXy = rThreatLocation.m_ThreatDetails.m_MyPawns[ i ];
                    	*pOutputStream<<WINNER_MOVIES_MARK<<rXy;
                    }

                	playStateMachine = GAME_OVER;
                	playStateMachineShadow = GAME_OVER;
                }
                else if ( Stalemate() )
                {
                    *pOutputStream<<STALEMATE_MSG;

                	playStateMachine = GAME_OVER;
                	playStateMachineShadow = GAME_OVER;
                }
                else if( isCpuWhiteOpening )
                {
                    playStateMachine = CPU_WHITE_OPEN_BOOK_MOVE;
                    playStateMachine = CPU_AI_MOVE;
                }
                else if( isCpuBlackOpening )
                {
                    //playStateMachine = CPU_BLACK_OPEN_BOOK_MOVE;
                	playStateMachine = CPU_AI_MOVE;
                }
                else if ( isCpuFirstMove )
                {
                    playStateMachine = CPU_WHITE_FIRST_MOVE;
                }
                else if( isComputerMove )
                {
                    playStateMachine = CPU_AI_MOVE;
                }
                else
                {
                    playStateMachine = HUMAN_MOVE;
                }

                *pOutputStream<<TERMINATOR_MSG;
                pOutputStream->flush();

                playStateMachineShadow = PLAY_STATE_MACHINE_NONE;
            }
            break;

            case DISPLAY:
            {
                *pOutputStream<<*m_pBoard;

                Board::PositionXY lastMove = XY_OUT_OF_BOARD;

                if( m_pBoard->GetLastMove( lastMove ) )
                {
                    const bool isComputerMovePrint = !isComputerMove;

                    if( isComputerMovePrint )
                    {
                        *pOutputStream<<LAST_CPU_MOVE_MSG<<lastMove;
                    }
                    else
                    {
                        *pOutputStream<<LAST_HUMAN_MOVE_MSG<<lastMove;
                    }

                    // Log the move.
                    m_Logger.AddEntryToRecord( lastMove );
                }

                pOutputStream->flush();

                playStateMachine = playStateMachineShadow;
            }
            break;

            case GAME_OVER:
            {
                isEnd = EndGame();
            	if( isEnd )
            	{
            		// Bye bye.
            	}
            	else
            	{
            		// Switch players color
            		Board::Player tmp = m_ComputerColor ;
            		m_ComputerColor = m_HumanColor;
            		m_HumanColor = tmp;
            	    isComputerMove = ( Board::PLAYER_A == m_ComputerColor ) ? true : false;

            		RestartGame();
            		playStateMachine = START;
            		playStateMachineShadow = PLAY_STATE_MACHINE_NONE;
            	}
            }
            break;

            default:
                assert( false );
        }
    }
}

/// Ends game.
bool GomokuGame::EndGame()
{
	bool retVal = true;
	std::string frontEndData = std::string();

#if defined ( GUI_GOMOKU_GAME )
        static_cast<GomokuInputStream*>( pInputStream )->WaitForData();
#endif

	*pInputStream>>frontEndData;

	if( pInputStream->fail() )
	{
		assert( false );
	}
	else
	{
		// GUI message parser.
		if( frontEndData == std::string( NEW_GAME ) )
		{
			pInputStream->clear();
			retVal = false;
		}
	}

	return retVal;
}

/// Set board to initialize state.
void GomokuGame::RestartGame()
{
	m_pBoard->ResetInstance();
	m_pBoardScoreCpu->ResetInstance();
	m_pBoardScoreHuman->ResetInstance();
	m_pBoardScoreCpu->SetPlayer( m_ComputerColor );
	m_pBoardScoreHuman->SetPlayer( m_HumanColor );
	pOutputStream->clear();
	pInputStream->clear();
}

/// Fetch user move.
Board::PositionXY GomokuGame::GetUserMove() const
{
    Board::PositionXY retVal = XY_OUT_OF_BOARD;
    uint32_t x = 0;
    uint32_t y = 0;

    while( true )
    {
        *pOutputStream<<YOUR_MOVE_MSG<<TERMINATOR_MSG;
        pOutputStream->flush();
        x = 0;
        y = 0;

#if defined ( GUI_GOMOKU_GAME )
        static_cast<GomokuInputStream*>( pInputStream )->WaitForData();
#endif

        *pInputStream>>x;
        if( pInputStream->fail() )
        {
            *pOutputStream<<INVALID_PARAMETER_MSG<<TERMINATOR_MSG;
            pInputStream->clear();
            // Ignore to the end of line
            pInputStream->ignore(INT_MAX, '\n');
            continue;
        }

        *pInputStream>>y;
        if( pInputStream->fail() )
        {
            *pOutputStream<<INVALID_PARAMETER_MSG<<TERMINATOR_MSG;
            pInputStream->clear();
            // Ignore to the end of line
            pInputStream->ignore(INT_MAX, '\n');
            continue;
        }
        else
        {
            break;
        }

        pOutputStream->flush();
    }

    retVal = Board::PositionXY( x, y );

    return retVal;
}

/// Check if provided move can be applied on board.
bool GomokuGame::ValidateMove( const Board::PositionXY& rXy ) const
{
    bool retVal = false;

    const bool isOnBoard = m_pBoard->IsOnBoard( rXy );
    const bool isVacant = ( ( isOnBoard ) && ( Board::PLAYER_EMPTY == m_pBoard->GetMove( rXy ) ) );

    // Position must be on board, vacant.
    retVal = ( isOnBoard && isVacant );

    return retVal;
}

/// Check against winner.
bool GomokuGame::WinnerCheck( const Board::Player player ) const
{
    bool retVal = false;

    if( ( m_pBoardScoreHuman->GetPlayer() == player ) && ( m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER ) ) )
    {
        retVal = true;
    }
    else if( ( m_pBoardScoreCpu->GetPlayer() == player ) && ( m_pBoardScoreCpu->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER ) ) )
    {
        retVal = true;
    }
    else
    {
       // nothing to do.
    }

    return retVal;
}

/// Check against stalemate.
bool GomokuGame::Stalemate() const
{
    static const uint32_t maxFields = m_pBoard->GetSize() * m_pBoard->GetSize();
    const uint32_t  moveOnBoard = m_pBoard->GetMoveNumber();
    const bool isStalemate = ( moveOnBoard == maxFields );

    return isStalemate;
}

/// Set searching algorithm.
void GomokuGame::SetSearchAlgorithm( const Level level )
{
    switch( level )
    {
        case BEGINNER:
        {
            const uint32_t beginnerDepth = 2U;
            m_pSearchAlgorithm = MinMax::GetInstance();
            m_pSearchAlgorithm->SetDeep( beginnerDepth );
        }
        break;

        case INTERMEDIATE:
        {
			const uint32_t intermediateDepth = 4U;
            m_pSearchAlgorithm = MinMax::GetInstance();
            m_pSearchAlgorithm->SetDeep( intermediateDepth );
        }
        break;

        case ADVANCED:
        {
            const uint32_t advancedDepth = 4U;
        	m_pSearchAlgorithm = AlphaBeta::GetInstance();
        	m_pSearchAlgorithm->SetDeep( advancedDepth );
        }
        break;

        default:
            assert( false );
    }

    assert( m_pSearchAlgorithm );
}

/// Get the best move.
Board::PositionXY GomokuGame::GetBestMove()
{
    Board::PositionXY retVal = XY_OUT_OF_BOARD;

    if( BEGINNER == m_Level )
    {
    	const uint32_t maxCandidatesNumber = 12U;
        SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );

        retVal = m_pSearchAlgorithm->FindBestMove( nBestMoves );
        nBestMoves.ClearAll();
    }
    else if( INTERMEDIATE == m_Level )
    {
    	const uint32_t maxCandidatesNumber = 15U;
        static const uint32_t defaultDepth = m_pSearchAlgorithm->GetDeep();
        SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
        vector<Board::PositionXY> candidates = {};

		const uint32_t beginnerDepth = 2U;
		GetInitCandidates( nBestMoves, beginnerDepth );

		const uint32_t candidatesNumber = nBestMoves.GetSize();
		for( uint32_t i = 0; i < candidatesNumber; ++i )
		{
			const Board::PositionXY el = nBestMoves.PopData().m_move;
			candidates.push_back( el );
		}
		nBestMoves.ClearAll();

        m_pSearchAlgorithm->SetDeep( defaultDepth );
        retVal = m_pSearchAlgorithm->FindBestMove( nBestMoves, candidates );

        // Add some randomize to game if enabled.
        if( m_IsRandomize )
        {
        	const uint32_t diversityPercent = 10;
        	retVal = RandomizeBestMove( nBestMoves, diversityPercent );

        }
    }
    else if( ADVANCED == m_Level )
    {
    	const uint32_t maxCandidatesNumber = 20U;
        SearchTreeAlgorithmIf::PriorityQueueScore nBestMoves( maxCandidatesNumber );
        vector<Board::PositionXY> candidates = {};

		const uint32_t beginnerDepth = 2U;
		GetInitCandidates( nBestMoves, beginnerDepth );

		const uint32_t candidatesNumber = nBestMoves.GetSize();
		for( uint32_t i = 0; i < candidatesNumber; ++i )
		{
			const Board::PositionXY el = nBestMoves.PopData().m_move;
			candidates.push_back( el );
			//cout<<el<<endl;
		}

		nBestMoves.ClearAll();
		retVal = m_pSearchAlgorithm->FindBestMove( nBestMoves, candidates );

        // Add some randomize to game if enabled.
        if( m_IsRandomize )
        {
        	const uint32_t diversityPercent = 5;
        	retVal = RandomizeBestMove( nBestMoves, diversityPercent );
        }
    }
    else
    {
        // Not supported.
        assert( false );
    }

    assert( XY_OUT_OF_BOARD != retVal);
    return retVal;
}

/// Provide initial candidates at specified depth.
void GomokuGame::GetInitCandidates( SearchTreeAlgorithmIf::PriorityQueueScore& rInitCandidates, const uint32_t initDepht ) const
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
	pMinMax->SetInitialPlayer( m_ComputerColor );
	pMinMax->SetBoardScore( *m_pBoardScoreCpu, *m_pBoardScoreHuman );
	pMinMax->FindBestMove( cpuCandidates );

	//b. Get best candidates for human. Reversing is needed.
	pMinMax->SetInitialPlayer( m_HumanColor );
	pMinMax->SetBoardScore( *m_pBoardScoreHuman, *m_pBoardScoreCpu );
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

/// Provide randomized move.
Board::PositionXY GomokuGame::RandomizeBestMove( const SearchTreeAlgorithmIf::PriorityQueueScore& nBestMoves, const uint32_t diversityPercent ) const
{
	assert( diversityPercent < 100 );
	Board::PositionXY retVal = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;

	//1. Find the range: <maxScore, (100-diversityPercent)maxScore >
	const SearchTreeAlgorithmIf::ScoreForMove topMove = nBestMoves.top();
	const int scoreMax = topMove.m_score;
	const float scoreDelta = abs( ( ((float)diversityPercent )/100 ) * scoreMax );
	const int scoreMin = static_cast<int>( ( (float)scoreMax - scoreDelta ) );

	//2. Make a list with the movies which score is being within the range.
	SearchTreeAlgorithmIf::PriorityQueueScore temp( nBestMoves );
	const uint32_t bestMoveSize = nBestMoves.size();
	Board::PositionXY theTopArray[ bestMoveSize ] = {};

	uint32_t i = 0;
	for( ; i < bestMoveSize; ++i )
	{
		const SearchTreeAlgorithmIf::ScoreForMove topMove = temp.PopData();
		const bool isStop = ( ( topMove.m_score < scoreMin ) || ( topMove.m_move == ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD ) );

		if( !isStop )
		{
			theTopArray[ i ] = topMove.m_move;
		}
		else
		{
			break;
		}
	}

	//3. Choose randomly move from the list.
	if( i > 0 )
	{
		uint32_t randIndex = rand() % i;
		retVal = theTopArray[ randIndex ];
	}
	else
	{
		retVal = topMove.m_move;
	}

	return retVal;
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

