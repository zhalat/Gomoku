/////////////////////////////////////////////////////////////////////////////////////////
/// @file Spotter.hpp
///
/// Search threats in provided region.
///
/// @par Full Description.
/// Search threats in provided region.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 06-Nov-2016 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined ( SPOTTER_HPP_ )
#define SPOTTER_HPP_

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES

#include "ThreatFinder.hpp" 	// For threat kind.
#include "Board.hpp"			// For Board::position.
#include "SingleList.hpp"		// For list definition.

// FORWARD REFERENCES
class BoardScore;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Spotter
///
/// Spotter interface declaration.
///
/// @par Full Description.
/// Search threats in provided region.
///////////////////////////////////////////////////////////////////////////////////////////
class Spotter
{
public:

    struct RegionToInvestigate
    {
        Board::PositionXY   		m_Xy;
        ThreatFinder::KindOfThreats m_ThreatKind;
        ThreatFinder::Trend 		m_Trend;
    };

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Spotter::AddToExecute
    //
    ///	Add region to investigate.
    ///
    /// @par Full Description
    /// Add region to investigate.
    ///
    /// @param regionToInvestigate Region to investigate.
    ///////////////////////////////////////////////////////////////////////
    void AddToExecute( const RegionToInvestigate regionToInvestigate );

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Spotter::Execute
    //
    /// Search threats.
    ///
    /// @par Full Description
    /// Searches threat from provided position.
    ///
    /// @param xy				Position around where threat will be browsing.
    /// @param isOpponentMove	Tells if provided move is opponent move.
	/// @param  multiplier      Multiple default score. By default == 1.
    ///
    ///////////////////////////////////////////////////////////////////////
    void Execute( const Board::PositionXY xy, const bool isOpponentMove, const uint32_t multiplier = ThreatFinder::ThreatLocation::DEFAULT_MULTIPLIER );

	/////////////////////////////////////////////////////////////////////////////
	// METHOD NAME: Spotter::ResetInstance
	//
	/// Revert instance to initial state.
	///
	/// @par Full Description
	/// Revert instance to initial state.
	/////////////////////////////////////////////////////////////////////////////
    void ResetInstance();

    // Constructor.
    Spotter( BoardScore& rBoardScore );

	// Destructor.
	virtual	~Spotter()
	{}

private:
    // Prevent either copying or assigning (>= C++11).
    Spotter( const Spotter& rSpotter ) = delete;
    Spotter& operator=( const Spotter& rSpotter ) = delete;

    BoardScore& m_rBoardScore;
    SingleList<RegionToInvestigate> m_RegionToInvestigate;
};

#endif /* SPOTTER_HPP_ */

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
