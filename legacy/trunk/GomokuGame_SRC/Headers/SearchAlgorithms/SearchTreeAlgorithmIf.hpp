/////////////////////////////////////////////////////////////////////////////////////////
/// @file SearchTreeAlgorithmIf.hpp
///
/// SearchTreeAlgorithmIf interface declaration.
///
/// @par Full Description.
/// Abstract class for each search tree algorithm implementation.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 04-Apr-2016 Initial revision.
/// - zhalat 06-Jan-2016 Changing interface: FindBestMove().
/// - zhalat 09-Aug-2017 Extending interface for GetNodeValue() nad GetNodeValueQuick().
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined ( SEARCH_ALGO_HPP_ )
#define SEARCH_ALGO_HPP_

// SYSTEM INCLUDES
#include <assert.h>            		// For assert.
#include <vector>              		// For vector declaration.

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Board.hpp"        		// For Board definitions.
#include "BoardScore.hpp"	 		// For Board Score.
#include "PriorityQueue.hpp"		// For PriorityQueue definition.
#include "StateEvaluationIf.hpp"	// For Tactics enum declaration.

// FORWARD REFERENCES
using std::vector;
#define MIN( a, b )						( ( a ) < ( b ) ? ( a ) : ( b ) )
#define MAX( a, b )						( ( a ) > ( b ) ? ( a ) : ( b ) )
#define MINUS_INFINITY  				std::numeric_limits< int >::min()
#define PLUS_INFINITY   				std::numeric_limits< int >::max()

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: SearchTreeAlgorithmIf
///
/// SearchTreeAlgorithmIf interface definition.
///
/// @par Full Description.
/// Abstract class for each search tree algorithm implementation.
///////////////////////////////////////////////////////////////////////////////////////////
class SearchTreeAlgorithmIf
{
public:
    // Maximum move candidates to evaluate.
    static constexpr uint32_t MAX_CAND = 300;

    // Default depth.
    static constexpr uint32_t DEFAULT_DEPTH = 2;

    // Maximum of depth.
    static constexpr uint32_t DEPTH_MAX = 8;

    // Score for move.
    struct ScoreForMove
    {
        int m_score;
        Board::PositionXY m_move;

        ScoreForMove( const int score = 0 )
        {
            m_score = score;
            m_move = Board::PositionXY( Board::PositionXY::INVALID_FIELD, Board::PositionXY::INVALID_FIELD );
        }

        bool operator<( const ScoreForMove& rX ) const
        {
            const bool isGrather = ( this->m_score < rX.m_score );

            return isGrather;
        }

        bool operator>( const ScoreForMove& rX ) const
        {
            const bool isLess = ( this->m_score > rX.m_score );

            return isLess;
        }
    };

    typedef PriorityQueue< ScoreForMove, std::vector<ScoreForMove> > PriorityQueueScore;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::SetBoardScore
    //
    /// Set cpu board score for analyze.
    ///
    /// @param rBoardScoreCpu CPU board score reference to analyze.
    /// @param rBoardScoreHuman Human board score reference to analyze.
    ///
    /// @par Full Description
    /// Set board for analyze, by creating copy of provided board score.
    ///////////////////////////////////////////////////////////////////////
    virtual void SetBoardScore( const BoardScore& rBoardScoreCpu, const BoardScore& rBoardScoreHuman )
    {
    	m_pBoardScoreCpu = &rBoardScoreCpu;
    	m_pBoardScoreHuman = &rBoardScoreHuman;

    	// Human and CPU  should use the same  board.
    	assert( &m_pBoardScoreHuman->GetBoard() == &m_pBoardScoreCpu->GetBoard() );
    	m_pBoard = &m_pBoardScoreCpu->GetBoard();
    }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::FindBestMove
    //
    /// Finds the best possible move.
    ///
    /// @par Full Description
    /// You can provide as default argument:
    ///  - init candidates - then best moves are searched only among them.
    ///  - nothing - internal algorithm is used to get init candidates.
    ///
    /// @param rBestMove 	   [in/out] Container for n-best move.
    ///						            The top(best) is returned.
    /// @param rInitCandidates [in] Candidates among which best move is searching.
    ///
    /// @retval Best move.
    ///////////////////////////////////////////////////////////////////////
    virtual Board::PositionXY FindBestMove( PriorityQueueScore& rBestMove, const vector<Board::PositionXY>& rInitCandidates = vector<Board::PositionXY>() ) = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::GenerateCand
    //
    /// Generate list of candidate moves.
    ///
    /// @par Full Description
    /// Generate list of candidate moves.
    ///
    /// @retval Candidate moves list.
    ///////////////////////////////////////////////////////////////////////
    virtual vector< Board::PositionField > GenerateCand() const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::SetDeep
    //
    /// Set depth of algorithm.
    ///
    /// @par Full Description
    /// Set how many further moves algorithm will consider.
    ///////////////////////////////////////////////////////////////////////
    void SetDeep( const uint32_t deep )
    {
        m_DeepSearch = deep;
    }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::GetDeep
    //
    /// Get current deep
    ///
    /// @par Full Description
    /// Get current deep.
    ///////////////////////////////////////////////////////////////////////
    uint32_t GetDeep()
    {
        return m_DeepSearch;
    }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::SetInitialPlayer
    //
    /// Set player who's  move is now.
    ///
    /// @par Full Description
    /// Set player who's  move is now.
    ///////////////////////////////////////////////////////////////////////
    void SetInitialPlayer( const Board::Player playerInit )
    {
        m_CurrentPlayerMove = playerInit;
    }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::GetName
    //
    /// Get algorithm's name.
    ///
    /// @par Full Description
    /// Get algorithm's name.
    ///
    /// @retval Algorithm's name.
    ///////////////////////////////////////////////////////////////////////
    const char* const GetName() const
    {
        return m_pName;
    }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::SwitchPlayer
    //
    /// Switch player to opponent.
    /// Each invocation switching O->X or X->O.
    ///
    /// @par Full Description
    /// Always returns opposite player than has been so far.
    ///////////////////////////////////////////////////////////////////////
    void SwitchPlayer()
    {
        if ( Board::PLAYER_A == m_CurrentPlayerMove )
        {
            m_CurrentPlayerMove = Board::PLAYER_B;
        }
        else if ( Board::PLAYER_B == m_CurrentPlayerMove )
        {
            m_CurrentPlayerMove = Board::PLAYER_A;
        }
        else
        {
            assert( false );
        }
    }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::WhoIsCurrentMove
    //
    /// Gets current player.
    ///
    /// @par Full Description
    /// Get player who has right to put move now.
    ///
    /// @retval Player who has right to put move now.
    ///////////////////////////////////////////////////////////////////////
    Board::Player WhoIsCurrentMove() const
    {
        return m_CurrentPlayerMove;
    }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::IsMaxPlayer
    //
    /// Check if max player has right to move.
    ///
    /// @par Full Description
    /// True if max player has right to move.
    ///
    /// @retval True if max player has right to move.
    ///////////////////////////////////////////////////////////////////////
    inline bool IsMaxPlayer() const
    {
    	 bool retVal = ( m_CurrentPlayerMove == m_pBoardScoreCpu->GetPlayer() );
    	 return retVal;
    }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::StartTimer
    //
    /// Starts the timer.
    ///
    /// @par Full Description
    /// Starts the timer.
    ///////////////////////////////////////////////////////////////////////
    void StartTimer(){};

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::IsTimerElapsed
    //
    /// Check if timer elapsed.
    ///
    /// @par Full Description
    /// Check if timer elapsed.
    ///
    /// @retval True if timer elapsed, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    bool IsTimerElapsed() const{};

    /// Constructor.
    SearchTreeAlgorithmIf( const uint32_t deep, const char* const pName )
     : m_DeepSearch( deep )
     , m_CurrentPlayerMove( Board::PLAYER_EMPTY )
     , m_pBoard( NULL )
     , m_pBoardScoreCpu( NULL )
     , m_pBoardScoreHuman( NULL )
     , m_pStateEvaluationIf( NULL )
     , m_Timer( 0 )
     , m_pName( pName )
    {
        // Nothing to do.
    }

    /// Destructor.
    virtual ~SearchTreeAlgorithmIf()
    {
        // Nothing to do.
    }

protected:
    // How deep algorithm should go.
    uint32_t m_DeepSearch;

    // Player who currently has move.
    Board::Player m_CurrentPlayerMove;

    // BoardScore state.
    const Board* m_pBoard;
    const BoardScore* m_pBoardScoreCpu;
    const BoardScore* m_pBoardScoreHuman;

    // Evaluation board state.
    StateEvaluationIf* m_pStateEvaluationIf;

    // Timer.
    uint32_t m_Timer;

    // Algorithm's name.
    const char* const m_pName;
};

#endif /* SEARCH_ALGO_HPP_ */

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