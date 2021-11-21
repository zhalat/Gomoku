/////////////////////////////////////////////////////////////////////////////////////////
/// @file ThreatFinder.hpp
///
/// ThreatFinder class declaration.
///
/// @par Full Description.
/// ThreatFinder finds pawns' which cause threat on gomoku board.
/// See article: 'Go-Moku and Threat-Space Search' by L.V. Allis & H.J. van den Herik
/// Design patterns used: Template method.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 01-Feb-2016 Initial revision.
/// - zhalat 10-Apr-2016 Added GetThreatFields().
/// - zhalat 15-Oct-2016 FindThreatPattern performance improvement.
/// - zhalat 27-Nov-2016 Finder starts finds all matching threats for some threat depending on IsBreakWhenFirstFound().
/// - zhalat 13-Nov-2017 Added StandarizePOV().
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined(THREAT_FINDER_HPP_)
#define THREAT_FINDER_HPP_

// SYSTEM INCLUDES
#include <assert.h>       // For assert.
#include <unordered_map>  // For maps.

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Board.hpp"        // PositionField, PositionXY, Board's enums.
#include "GomokuBoard.hpp"  // GomokuBoard definitions.

// FORWARD REFERENCES
#define NUMELEM(x) (sizeof(x) / sizeof(x[0]))
#define CLR_BIT(p, n) ((p) &= ~((1) << (n)))

class TEST_Threat2CaseCTest_StandarizePOVTest1_Test;
class TEST_Threat2CaseATest_StandarizePOVTest1_Test;
class TEST_Threat2CaseATest_StandarizePOVTest2_Test;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: ThreatFinder.
///
/// ThreatFinder class declaration.
///
/// @par Full Description.
/// Abstrac clsss ThreatFinder. Finds pawns' threats on gomoku board.
///////////////////////////////////////////////////////////////////////////////////////////
class ThreatFinder
{
   public:
    static constexpr uint32_t MAX_ALLOVED_EXCEPTION = 2;

    /// Kind of threats. Stronger first.
    enum KindOfThreats
    {
        THREAT_WINNER    = 0,
        THREAT_4_CASE_A  = 1,
        THREAT_4_CASE_AA = 2,
        THREAT_4_CASE_B  = 3,
        THREAT_4_CASE_C  = 4,
        THREAT_3_CASE_A  = 5,
        THREAT_3_CASE_AA = 6,
        THREAT_3_CASE_B  = 7,
        THREAT_3_CASE_C  = 8,
        THREAT_2_CASE_A  = 9,
        THREAT_2_CASE_AA = 10,
        THREAT_2_CASE_B  = 11,
        THREAT_2_CASE_C  = 12,

        THREAT_NONE  // Must be the last.
    };

    /// Define a 4-way direction.
    enum Trend
    {
        VERTICAL   = 0,
        HORIZONTAL = 1,
        RISING     = 2,
        FALLING    = 3,

        TREND_NONE  // Must be the last.
    };

    /// List elements each threat is consisted from.
    enum ThreatAtom
    {
        MY_PAWN    = 0,
        ENEMY_PAWN = 1,
        GAP        = 2,
        ASTERIX    = 3
    };

    /// Straight and reverse conversion trend to direction.
    static const std::unordered_map<Trend, Board::Direction, std::hash<int>> Trend2DirectionStraight;
    static const std::unordered_map<Trend, Board::Direction, std::hash<int>> Trend2DirectionReverse;

    /// Keeps flags about symmetric pattern. Does matter only for symmetric patterns like 2A.
    struct FoundFlags
    {
        bool m_IsNormalFound;     // ..x.x.*
        bool m_IsSymmetricFound;  // *.x.x..
        bool m_IsSearchingForSymmetric;

        void ClearAll()
        {
            m_IsNormalFound           = false;
            m_IsSymmetricFound        = false;
            m_IsSearchingForSymmetric = false;
        }
    };

    /// Keeps threat content down details. Needed to find out threat location.
    struct ThreatDownDetails
    {
        uint32_t m_HexCode;
        uint32_t m_PointOfView;
        FoundFlags m_FoundFlags;
        Board::Player m_PlayerPerspective;

        ThreatDownDetails() : m_HexCode(0), m_PointOfView(0), m_FoundFlags{ 0 }, m_PlayerPerspective(Board::PLAYER_NONE)
        {}

        void ClearAll()
        {
            m_HexCode           = 0;
            m_PointOfView       = 0;
            m_FoundFlags        = { 0 };
            m_PlayerPerspective = Board::PLAYER_NONE;
        }
    };

    /// Keeps threat content up details. Needed to find out threat location.
    struct ThreatUpDetails
    {
        static const uint32_t MAX_MY_PAWNS    = 5;
        static const uint32_t MAX_ENEMY_PAWNS = 2;
        static const uint32_t MAX_EMPTY_SPACES =
            10;  // index [0-4] for normal; [5-9] symmetric. Duplication allowed! So must be filter while getting.
        static const uint32_t MAX_EXTEND_SPACES = 2;
        static const uint32_t MAX_ASTERIXES     = 2;

        Board::Player m_WhoIs;
        Board::PositionXY m_MyPawns[MAX_MY_PAWNS];
        Board::PositionXY m_EnemyPawns[MAX_ENEMY_PAWNS];
        Board::PositionXY m_Gaps[MAX_EMPTY_SPACES];
        Board::PositionXY m_ExtGaps[MAX_EXTEND_SPACES];
        Board::PositionXY m_Asterixes[MAX_ASTERIXES];
        Board::PositionXY m_BeginningThreat;
        Board::PositionXY m_EndThreat;

        ThreatUpDetails() { ClearAll(); }

        void ClearAll()
        {
            // Tell who's threat.
            m_WhoIs = Board::Player::PLAYER_NONE;

            // Set initial state.
            for(uint32_t i = 0; i < MAX_MY_PAWNS; ++i)
                m_MyPawns[i] = ThreatLocation::XY_OUT_OF_BOARD;
            for(uint32_t i = 0; i < MAX_ENEMY_PAWNS; ++i)
                m_EnemyPawns[i] = ThreatLocation::XY_OUT_OF_BOARD;
            for(uint32_t i = 0; i < MAX_EMPTY_SPACES; ++i)
                m_Gaps[i] = ThreatLocation::XY_OUT_OF_BOARD;
            for(uint32_t i = 0; i < MAX_EXTEND_SPACES; ++i)
                m_ExtGaps[i] = ThreatLocation::XY_OUT_OF_BOARD;
            for(uint32_t i = 0; i < MAX_ASTERIXES; ++i)
                m_Asterixes[i] = ThreatLocation::XY_OUT_OF_BOARD;

            m_BeginningThreat = ThreatLocation::XY_OUT_OF_BOARD;
            m_EndThreat       = ThreatLocation::XY_OUT_OF_BOARD;
        }
    };

    /// Keeps threat location on a board.
    struct ThreatLocation
    {
        static const Board::PositionXY XY_OUT_OF_BOARD;
        static const Board::PositionXY XY_BEGIN_OF_BOARD;
        static const uint32_t DEFAULT_MULTIPLIER = 1;

        Trend m_Trend;
        uint32_t m_Multiplier;
        ThreatUpDetails m_ThreatDetails;

        ThreatLocation() : m_Trend(TREND_NONE), m_Multiplier(DEFAULT_MULTIPLIER) { m_ThreatDetails.ClearAll(); }

        void ClearAll()
        {
            m_Trend      = TREND_NONE;
            m_Multiplier = ThreatLocation::DEFAULT_MULTIPLIER;
            m_ThreatDetails.ClearAll();
        }
    };

    /// Threat pattern container.
    struct ThreatPattern
    {
        uint32_t m_ThreatPattern;
        uint8_t m_PointOfView;
    };

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::FindThreatPattern
    //
    /// Browse neighborhood for threat.
    ///
    /// @par Full Description
    /// Browse xy neighborhood for threat pattern.
    /// NOTE: KEEP THIS METHOD AS FAST AS POSSIBLE.
    ///
    /// Implemented as template method.
    /// Look at documentation how this algorithm works.
    ///
    /// @param  initialPosition Position from which threat is being searched.
    /// @param  trend           Trend/direction on which threat pattern is looking for.
    /// @param  player          Perspective For which player threat is looking for.
    ///
    /// @retval True if threat was found, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool FindThreatPattern(const Board::PositionXY & initialPosition, const Trend trend,
                                   const Board::Player playerPerspective) final;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::GetGomokuBoard
    //
    /// Get gomoku board.
    ///
    /// @par Full Description
    /// Get gomoku board.
    ///
    /// @retval Reference to gomoku board.
    ///////////////////////////////////////////////////////////////////////
    const GomokuBoard & GetGomokuBoard() const
    {
        assert(NULL != m_pGomokuBoard);
        return *m_pGomokuBoard;
    }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::SetBoard
    //
    /// Set gomoku board.
    ///
    /// @par Full Description
    /// Set gomoku board.
    ///
    /// @param pBoard Pointer to gomoku board.
    ///////////////////////////////////////////////////////////////////////
    void SetBoard(const Board * pBoard) { m_pGomokuBoard = static_cast<const GomokuBoard *>(pBoard); }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::GetThreatFields
    //
    /// Gets threat location on a board.
    ///
    /// @par Full Description
    /// Gets threat location like: threat begin/end and it trend
    ///
    /// @param  threatLocation  Array where begin-field and end-field of threat will be stored.
    ///////////////////////////////////////////////////////////////////////
    void GetThreatFields(ThreatLocation & rThreatLocation) const;

    ThreatFinder(const uint32_t patternLenght, const uint32_t * pPointsView, const uint32_t pointsViewSize,
                 const std::unordered_map<ThreatFinder::ThreatAtom, int, std::hash<int>> atomNumber) :
        m_pGomokuBoard(NULL),
        m_PatternLenght(patternLenght),
        m_pPointsView(pPointsView),
        m_PointsViewSize(pointsViewSize),
        m_ThreatLocation(),
        m_IsThreatPatternFound(false)
    {
        // nothing to do.
    }

    // Destructor.
    virtual ~ThreatFinder()
    {
        m_pGomokuBoard         = NULL;
        m_pPointsView          = NULL;
        m_IsThreatPatternFound = false;
    }

   protected:
    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::CheckThreat
    //
    /// Check if given threat is real threat.
    ///
    /// @par Full Description
    ///	Concrete class will check pretendThreat if meets all requirement to
    /// real threat.
    ///
    /// @param  pretendThreat	  Threat to be checked.
    /// @param  pointOfView       Point of view.
    /// @param  playerPerspective For which player threat is looking for.
    ///
    /// @retval True if pretendent threat is real threat, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool CheckThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                             const Board::Player playerPerspective) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::GetThreatUpDetails
    //
    /// After threat was found, method provides threat up details.
    ///
    /// @par Full Description
    /// Provide details about threat like pawns/asterix/gaps arrangement.
    ///
    /// @param  initialPosition	  [in]Position from which threat is considered.
    /// @param  trend             [in]Threat's trend.
    /// @param  rThreatUpDetails  [out]Container where up details is being written.
    ///
    /// @retval Threat up details.
    ///////////////////////////////////////////////////////////////////////
    virtual void GetThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                                    ThreatUpDetails & rThreatUpDetails) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::StandarizePOV
    //
    /// Change hexCode as if was being seen from 0 point of view.
    ///
    /// @par Full Description
    /// Change hexCode as if was being seen from 0 point of view.
    ///
    /// @param  hexCode 	 hexCode to be standardized.
    /// @param  pointOfView  Point of view related to hexCode
    /// @param  length       Threat length.
    ///
    /// @retval hexCode seen form 0 point of view.
    ///////////////////////////////////////////////////////////////////////
    uint8_t StandarizePOV(const uint8_t hexCode, const uint8_t pointOfView, const uint8_t length) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::GetPieces
    //
    /// Get threat pieces.
    ///
    /// @par Full Description
    /// Provide (x,y) threat's pieces(x,o,.,*) basing on normalized threat.
    ///
    /// @param  normHexCode 	 Normalized hexCode.
    /// @param  normPointOfView  Normalized point of view.
    /// @param  direction		 Direction to crawl.
    /// @param  pBuffer          [out]Buffer where pieces' location will be written.
    /// @param  bufferSize       Buffer lenght.
    ///////////////////////////////////////////////////////////////////////
    void GetPieces(const uint8_t normHexCode, const Board::PositionXY initialPositionNorm,
                   const Board::Direction direction, Board::PositionXY pBuffer[], const uint32_t bufferSize) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::MakeStepOnTrend
    //
    /// Check if there is possible go one step forward/backward.
    ///
    /// @par Full Description
    /// Check if there is possible go one step forward/backward depending.
    ///
    /// @param  isReversion 	  Go forward or backward.
    /// @param  currentXYPosition Starting position.
    /// @param  trend    		  Trend to go.
    ///
    /// @retval True if possible false if out of the board.
    ///////////////////////////////////////////////////////////////////////
    bool MakeStepOnTrend(const bool isReversion, Board::PositionXY & currentXYPosition, const Trend trend) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::IsBreakWhenFirstFound
    //
    /// Indicate if searching should be continue to find symmetric.
    ///
    /// @par Full Description
    /// Indicate if searching should be continue to find symmetric.
    ///
    /// @retval True if continue, false, immediate stop.
    ///////////////////////////////////////////////////////////////////////
    virtual bool IsSearchForSimmetrics() const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: ThreatFinder::PrepareSelfForNewSearch
    //
    /// Prepare class for new search.
    ///
    /// @par Full Description
    /// Prepare class for new search. Like clearing the internal flags.
    ///////////////////////////////////////////////////////////////////////
    virtual void PrepareSelfForNewSearch() = 0;

   private:
    /// Private copy constructor - forbid copying.
    ThreatFinder(const ThreatFinder &);

    /// Private assign operator - forbid copying.
    ThreatFinder & operator=(const ThreatFinder &);

    /// Board for threat searching.
    const GomokuBoard * m_pGomokuBoard;

    /// Some feature describing pattern threat.
    const uint32_t m_PatternLenght;
    const uint32_t * m_pPointsView;
    const uint32_t m_PointsViewSize;

    // Keeps threat location on a board.
    ThreatLocation m_ThreatLocation;

    /// Points if the threat-pattern was found.
    bool m_IsThreatPatternFound;

    friend TEST_Threat2CaseCTest_StandarizePOVTest1_Test;
    friend TEST_Threat2CaseATest_StandarizePOVTest1_Test;
    friend TEST_Threat2CaseATest_StandarizePOVTest2_Test;
};
#endif /* THREAT_FINDER_HPP_ */

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
