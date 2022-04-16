/////////////////////////////////////////////////////////////////////////////////////////
/// @file Score.hpp
///
/// Estimate score for board state.
///
/// @par Full Description.
/// Score class analyze board for searching threats and assigns points for each threat found.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 08-Apr-2016 Initial revision.
/// - zhalat 30-Apr-2016 ThreatWinner added to threat score.
/// - zhalat 15-Nov-2016 BoardScore class were extracted from this file.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined ( SCORE_HPP_ )
#define SCORE_HPP_

// SYSTEM INCLUDES
#include <string.h>          // For memset.

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Board.hpp"         // For Board declaration.
#include "ThreatFinder.hpp"

// FORWARD REFERENCES
class BoardScore;
using std::vector;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Score
///
/// Estimates board state for each player point of view.
///
/// @par Full Description.
/// Score class analyze board for searching threats and assigns points for each threat found.
///////////////////////////////////////////////////////////////////////////////////////////
class Score
{
public:

    /// Associate threat and score (how danger threat is).
    struct ThreatScore
    {
        // Kind of threat.
        const ThreatFinder::KindOfThreats threatKind;

        // Pointer to threat class.
        ThreatFinder *const m_pThreat;

        // Score assigned to the threat.
        const uint32_t m_Score;
    };

	///Threats score.
    static const uint32_t THREAT_WINNER_SCORE 	 = 1000;

    static const uint32_t THREAT_4_CASE_A_SCORE  = 100;
    static const uint32_t THREAT_4_CASE_AA_SCORE = 50;
    static const uint32_t THREAT_4_CASE_B_SCORE  = 25;
    static const uint32_t THREAT_4_CASE_C_SCORE  = 15;

    static const uint32_t THREAT_3_CASE_A_SCORE  = 30;
    static const uint32_t THREAT_3_CASE_AA_SCORE = 15;
    static const uint32_t THREAT_3_CASE_B_SCORE  = 5;
    static const uint32_t THREAT_3_CASE_C_SCORE  = 3;

    static const uint32_t THREAT_2_CASE_A_SCORE =  4;
    static const uint32_t THREAT_2_CASE_AA_SCORE = 2;
    static const uint32_t THREAT_2_CASE_B_SCORE =  2;
    static const uint32_t THREAT_2_CASE_C_SCORE =  1;

    /// Keeps list of all available threats and
    /// associate score to each threat(how danger threat is).
    /// ThreatWinner;
    /// Threat4CaseA;
    /// Threat4CaseAA;
    /// Threat4CaseB;
    /// Threat4CaseC;
    /// Threat3CaseA;
    /// Threat3CaseAA;
    /// Threat3CaseB;
    /// Threat3CaseC;
    /// Threat2CaseA;
    /// Threat2CaseAA;
    /// Threat2CaseB;
    /// Threat2CaseC;
    static const ThreatScore m_ThreatScore[];

    /// How many threats there are defined.
    static const uint32_t MAX_KIND_OF_THREATS = 13; //sizeof m_ThreatScore

    ///	Max number the same kind of threat.
    static const uint32_t MAX_TRACKED_THREATS = 15;

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: Score::GetInstance
    //
    /// Get instance of Score.
    ///
    /// @par Full Description
    /// Get instance of Score.
    ///
    /// @return pointer to Score instance.
    /////////////////////////////////////////////////////////////////////////////
    static Score* GetInstance();

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Score::UpdateScore
    //
    /// Updates board' score by taking account the new moves.
    ///
    /// @par Full Description.
    /// Updates board' score by taking account the new moves.
    /// Finds threats from xy list position and update board score accordingly.
    /// To keep board' score up to date each move on board must be analyzed.
    ///
    /// @param boardScore Board score needs to be updated.
    /// @param xy List of new moves.
    ///////////////////////////////////////////////////////////////////////
    void UpdateScore( BoardScore& boardScore, const vector< Board::PositionXY >& xyList, const uint32_t multiplier = ThreatFinder::ThreatLocation::DEFAULT_MULTIPLIER );

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Score::UpdateScore
    //
    /// Updates board' score by taking account the new move.
    ///
    /// @par Full Description.
    /// Updates board' score by taking account the new moves.
    /// Finds threats from xy position and update board score accordingly.
    ///
    /// @param boardScore Board score needs to be updated.
    /// @param xy A new move.
    ///////////////////////////////////////////////////////////////////////
    void UpdateScore( BoardScore& boardScore, const Board::PositionXY xy, const uint32_t multiplier = ThreatFinder::ThreatLocation::DEFAULT_MULTIPLIER );

    /// Destructor.
    virtual ~Score();

private:
    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: Score::SetBoard
    //
    /// Set board for threats searching.
    ///
    /// @par Full Description
    /// Set board for threats searching.
    ///
    /// @param board  Board for threats searching.
    /////////////////////////////////////////////////////////////////////////////
    void SetBoard( const Board& rBoard );

    /// Private copy constructor - forbid copying.
    Score( const Score& ){}

    /// Private assign operator - forbid copying.
    Score& operator=( const Score& ){}

    /// Private default constructor - forbid create instance.
    Score()
    {};

    /// Handler for instance.
    static Score* m_pInstance;
};

#endif /* SCORE_HPP_ */

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