/////////////////////////////////////////////////////////////////////////////////////////
/// @file BoardScore.hpp
///
/// Keeps threats for board.
///
/// @par Full Description.
/// Keeps threats for board.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 08-Apr-2016 Initial revision.
/// - zhalat 12-Dec-2016 Added m_RecognizedThreatsExt member for keeping 'external gaps'.
/// - zhalat 12-Jan-2017 Score multiplier for new threat.
/// - zhalat 29-Apr-2017 Added ability to print all threats.
/// - zhalat 01-Jun-2017 Speed up - use list instead array.
/// - zhalat 16-Feb-2018 Interface extended.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2018 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined ( BOARDSCORE_HPP_ )
#define BOARDSCORE_HPP_

// SYSTEM INCLUDES
#include <stdint.h>
#include <stdio.h>
#include <string.h>            		// For memset.
#include <vector>
#include <list>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Score.hpp"		   		// For some constants.
#include "Spotter.hpp"		   		// For Spotter definition.

// FORWARD REFERENCES
// none

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: BoardScore
///
/// Keeps threats for board.
///
/// @par Full Description.
/// Keeps threats for board.
///////////////////////////////////////////////////////////////////////////////////////////
 
// Associate board state with score.
class BoardScore
{
public:

	// Container for recognized threats on a board and it's number.
	struct ThreatsOnBoard
	{
		// Number of recognized threat for each kind.
		// Each column keeps number of recognized threats for its associated kind of threat:
		// Threat4CaseA; - column 0.
		// Threat4CaseB; - column 1.
		// Threat4CaseC; - ..
		// Threat3CaseA;
		// Threat3CaseB;
		// Threat3CaseC;
		// Threat2CaseA;
		// Threat2CaseB;
		// Threat2CaseC;
		uint32_t m_NumberRecognizedThreat[ Score::MAX_KIND_OF_THREATS ];

		// Recognized threats. Array contains all fields which recognized threats are stored.
		// The thread order shall exactly match to m_NumberRecognizedThreat.
		std::list<ThreatFinder::ThreatLocation> m_RecognizedThreats[ Score::MAX_KIND_OF_THREATS ];

		ThreatsOnBoard()
		{
			 memset( m_NumberRecognizedThreat, 0, sizeof( m_NumberRecognizedThreat ) );
		}
	};

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::GetNumberOfRecognizedThreat
	//
	/// Gets number of recognized the provided kind of threat.
	///
	/// @par Full Description
	/// Provide number of recognized threats of threatKind kind.
	///
	/// @param threatKind Kind of threat for query.
	///
	/// @retval Number of recognized threats.
	/////////////////////////////////////////////////////////////////////////////
	uint32_t GetNumberOfRecognizedThreat( ThreatFinder::KindOfThreats threatKind ) const;

#warning "GetGapsNonUnique/GetGapsUnique..GetCommonFieldNumber should be separated form this class as they're not related. Consider interface"
	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::GetGapsNonUnique
	//
	/// Gets gaps belonging to provided kind of threat(extended included).
	///
	/// @par Full Description
	/// Repetitive included.
	///
	/// @param exGaps     Vector where output to be stored.
	/// @param threatKind Threat family.
	/////////////////////////////////////////////////////////////////////////////
	void GetGapsNonUnique( std::vector<Board::PositionField>& rGaps, const ThreatFinder::KindOfThreats threatKind ) const;

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::GetGapsUnique
	//
	/// Gets gaps belonging to provided kind of threat(extended included).
	///
	/// @par Full Description
	/// Repetitive doesn't included.
	///
	/// @param exGaps     Vector where output to be stored.
	/// @param threatKind Threat family.
	/////////////////////////////////////////////////////////////////////////////
	void GetGapsUnique( std::vector<Board::PositionField>& rGaps, const ThreatFinder::KindOfThreats threatKind ) const;

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::GetGapsDuplicated
	//
	/// Gets gaps that are common to more than one threat (extended included).
	///
	/// @par Full Description
	/// Only repetitive.
	///
	/// @param exGaps     Vector where output to be stored.
	/// @param threatKind Threat family.
	/////////////////////////////////////////////////////////////////////////////
	void GetGapsDuplicated( std::vector<Board::PositionField>& rGaps, const ThreatFinder::KindOfThreats threatKind ) const;

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::GetExGaps
	//
	/// Gets all extend gaps belongs to provided threat.
	///
	/// @par Full Description
	/// Extended gap occurs for threat which has more than one gap in a row.
    /// Exemplary: .XXX.. / .XX... / OXXX..
    ///                 ^       ^         ^
    ///                 ^^^^^^'GapExt'^^^^^
	///
	/// @param	exGaps     Vector where output to be stored.
	/// @param  threatKind Threat family.
	/////////////////////////////////////////////////////////////////////////////
	void GetExGaps( std::vector<Board::PositionField>& exGaps, const ThreatFinder::KindOfThreats threatKind ) const;

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::GetCommonFieldNumber
	//
	/// Get number of fields that both threats kind have in common.
	///
	/// @par Full Description
	/// Get number of fields that both threats kind have in common.
	/// Use threatKindA >= threatKindB.
	///
	/// @param threatKindA Fist.
	/// @param threatKindB Second.
	///
	/// @retval Number of common fields.
	/////////////////////////////////////////////////////////////////////////////
	uint32_t GetCommonFieldNumber( const ThreatFinder::KindOfThreats threatKindA,
								   const ThreatFinder::KindOfThreats threatKindB ) const;

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::RemoveThreats
	//
	/// From threat list remove such that include xy position.
	///
	/// @par Full Description
	/// From threat list remove such that include xy position.
	/// Before removing remember those that require reupdate.
	///
	/// @param xy Threats contain this position will be removed.
	///
	/// @retval   Number of removed threats.
	/////////////////////////////////////////////////////////////////////////////
	uint32_t RemoveThreats( const Board::PositionXY xy );

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::AddThreats
	//
	/// Adds a new threat location.
	///
	/// @par Full Description
	/// Adds threat location.
	///
	/// @param  rTreatLocation Threat location on a board.
	/// @param  kindOfThreat   Row of array where threat will be added.
	/// @param  multiplier     Multiple default score. By default == 1.
	///
	/// @retval True if threat added, false otherwise (no space for additional threat).
	/////////////////////////////////////////////////////////////////////////////
	bool AddThreats( const ThreatFinder::ThreatLocation& rTreatLocation, const uint32_t kindOfThreat, const uint32_t multiplier = ThreatFinder::ThreatLocation::DEFAULT_MULTIPLIER );

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::GetThreatList
	//
	/// Provide threat list.
	///
	/// @par Full Description
	/// Threat list.
	///
	/// @param  kindOfThreat   Threat family.
	///
	/// @retval Threat list.
	/////////////////////////////////////////////////////////////////////////////
	const std::list<ThreatFinder::ThreatLocation>& GetThreatList( const ThreatFinder::KindOfThreats threatKind ) const;

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::GetScore
	//
	/// Get actual score.
	///
	/// @par Full Description
	/// Get actual score.
	///
	/// @retval Actual score.
	/////////////////////////////////////////////////////////////////////////////
	uint32_t GetScore() const
	{
		return m_Score;
	}

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::GetPlayer
	//
	/// Get player color.
	///
	/// @par Full Description
	/// Get player color.
	///
	/// @retval Player color.
	/////////////////////////////////////////////////////////////////////////////
	Board::Player GetPlayer() const
	{
		return m_player;
	}

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::SetPlayer
	//
	/// Set player color.
	///
	/// @par Full Description
	/// Set player color.
	///
	/// @par Player A owner of instance.
	/////////////////////////////////////////////////////////////////////////////
	void SetPlayer( const Board::Player player )
	{
		m_player = player;
	}

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::SetBoard
	//
	/// Set board.
	///
	/// @par Full Description
	/// Set board. Its possible set board only once.
	///
	/// @par Reference to board.
	/////////////////////////////////////////////////////////////////////////////
	void SetBoard( const Board& rBoard)
	{
		// Can be used only when there is no board set.
		assert( NULL == m_pBoard );
		m_pBoard = &rBoard;
	}

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::RemoveThreats
	//
	/// Get board.
	///
	/// @par Full Description
	/// Get board.
	///
	/// @retval Reference to board.
	/////////////////////////////////////////////////////////////////////////////
	const Board& GetBoard() const
	{
		// If default constructor BoardScore() was used, operator= must be invoked before
		// this method to provide Board.
		assert( NULL != m_pBoard );
		return *m_pBoard;
	}

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::ResetInstance
	//
	/// Revert instance to ininial state.
	///
	/// @par Full Description
	/// Revert instance to ininial state.
	/////////////////////////////////////////////////////////////////////////////
	void ResetInstance();

	Spotter& GetSpotter()
	{
		return m_Spotter;
	}

	// Operators ==/!=/</>.
	bool operator==( const BoardScore& boardScore ) const
	{
		const bool isEqual = ( this->m_Score == boardScore.m_Score );
		return isEqual;
	}

	bool operator!=( const BoardScore& boardScore ) const
	{
		const bool isNotEqual = !( *this == boardScore );
		return isNotEqual;
	}

	bool operator<( const BoardScore& boardScore ) const
	{
		const bool isGrather = ( this->m_Score < boardScore.m_Score );
		return isGrather;
	}

	bool operator>( const BoardScore& boardScore ) const
	{
		const bool isLower = ( this->m_Score > boardScore.m_Score );
		return isLower;
	}

	BoardScore& operator=( const BoardScore& rBoardScore )
	{
		if( this != &rBoardScore )
		{
			// Copy each members except for m_pBoard.
			Board::Player* pPlayerTemp = const_cast< Board::Player* >( &this->m_player );
			*pPlayerTemp = rBoardScore.m_player;
			m_ThreatsOnBoard = rBoardScore.m_ThreatsOnBoard;
			m_Score = rBoardScore.m_Score;
			// m_Spotter - don't copy. Just create empty.
		}

		return *this;
	}

	// Constructor.
	BoardScore( const Board::Player player )
	 : m_pBoard( NULL )
	 , m_player( player )
	 , m_ThreatsOnBoard()
	 , m_Score ( 0 )
	 , m_Spotter( *this )
	{
		// Nothing to do.
	}

	// Copy constructor.
	BoardScore( const BoardScore& rBoardScore )
	 : m_pBoard( NULL )
	 , m_player( rBoardScore.m_player )
	 , m_ThreatsOnBoard( rBoardScore.m_ThreatsOnBoard )
	 , m_Score( rBoardScore.m_Score )
	 , m_Spotter( *this )  // don't copy is. Just create empty.
	{
		// Nothing to do.
	}

	// Destructor.
	virtual	~BoardScore()
	{
		// Nothing to do.
	}

private:
	static const uint32_t MAX_THREAT_PARTS = 3;

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::IsPartOfThreat
	//
	/// Check if provided position is part of provided threat.
	///
	/// @par Full Description
	/// Check if provided position is part of provided threat.
	///
	/// @param rThreatContainer Provided threat location as pair [threatBegin,threatEnd].
	/// @param xy Position to be checked.
	/////////////////////////////////////////////////////////////////////////////
	bool IsPartOfThreat( const ThreatFinder::ThreatLocation& rThreatLocation, const Board::PositionXY xy ) const;

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: BoardScore::GetThreatElement
	//
	/// In provided threat, search for any, non empty move, belongs to 'player' move.
	///
	/// @par Full Description
	/// Examplary: 'OXXX..', not empty moves are 'OXXX' and 'player' argument specifies
	///            if X or O should be searching.
	///
	/// @param rThreatContainer 	Provide threat location as pair [threatBegin,threatEnd].
	/// @param player           	Specifies which player move is to be search.
	/// @param threatElements[out]  Element of threat.
	/////////////////////////////////////////////////////////////////////////////
	void GetThreatElementDismissal( const ThreatFinder::ThreatLocation& rThreatLocation, const Board::Player player, Board::PositionXY threatElements[ MAX_THREAT_PARTS ] ) const;
	void GetThreatElementPromotion( const ThreatFinder::ThreatLocation& rThreatLocation, Board::PositionXY& threatElement, const bool isTheFist ) const;

	// Board state.
	const Board* m_pBoard;

	// Who's score.
	Board::Player m_player;

	// Recognized threats on board.
	ThreatsOnBoard m_ThreatsOnBoard;

	uint32_t m_Score;

	// Execute only certain threats.
	Spotter m_Spotter;

    /// Print board.
    friend std::ostream& operator<<( std::ostream& _stream, const BoardScore& rBoardScore )
    {
    	_stream << "Recognized threats:" << endl;

    	for( uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i )
    	{
    		// Print threat number.
    		_stream << i << ": " << rBoardScore.m_ThreatsOnBoard.m_NumberRecognizedThreat[ i ] << " ";

    		std::list<ThreatFinder::ThreatLocation>::const_iterator citer = rBoardScore.m_ThreatsOnBoard.m_RecognizedThreats[ i ].begin();

    		for( ; citer != rBoardScore.m_ThreatsOnBoard.m_RecognizedThreats[ i ].end(); ++citer )
    		{
        		// Print the recognized group in format: [(beg_x,beg_y),(end_x,end_y) ]
        		_stream << "[" << "(" << citer->m_ThreatDetails.m_BeginningThreat.m_x<< "," << citer->m_ThreatDetails.m_BeginningThreat.m_y<< ")" << ",";
        		_stream << "(" << citer->m_ThreatDetails.m_EndThreat.m_x<< "," << citer->m_ThreatDetails.m_EndThreat.m_y<< ")" <<"] ";
    		}

    		_stream << endl;
    	}
    }
};
#endif /* BOARDSCORE_HPP_ */

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
