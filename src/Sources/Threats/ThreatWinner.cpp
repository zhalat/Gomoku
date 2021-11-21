/////////////////////////////////////////////////////////////////////////////////////////
/// @file ThreatWinner.cpp
///
/// ThreatWinner class definition.
///
/// @par Full Description.
/// ThreatWinner finds pawns' which constitute one case of four pattern.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 18-Feb-2016 Initial revision.
/// - zhalat 15-Oct-2016 Performance improvement.
/// 					 Pattern mask usage instead of full pattern.
/// - zhalat 09-Sep-2017 Six in row recognition.
/// - zhalat 27-Nov-2017 All threat pieces location available via GetThreatUpDetails().
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "ThreatWinner.hpp"  // ThreatWinner definition.

// FORWARD REFERENCES
// <none>

/// Tells how many pawns/gaps/asterixes this thrat has.
const std::unordered_map<ThreatFinder::ThreatAtom, int, std::hash<int>> ThreatWinner::ATOM_NUMBER_WINNER = {
    { ThreatFinder::MY_PAWN, 2 },
    { ThreatFinder::ENEMY_PAWN, 0 },
    { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
    { ThreatFinder::ASTERIX, -1 }  // it depends.
};

/// Threat-mask for X player.
const ThreatFinder::ThreatPattern ThreatWinner::m_ThreatPatternX[] = {
    // Finds:
    // *XXXXX*
    //{ 0x41000000, 0 },
    { 0x60000000, 1 }, { 0x50000000, 2 }, { 0x48000000, 3 }, { 0x44000000, 4 }, { 0x42000000, 5 },
    //{ 0x41000000, 6 }
};

/// Threat-mask for O player.
const ThreatFinder::ThreatPattern ThreatWinner::m_ThreatPatternO[] = {
    // Finds:
    // *OOOOO*
    //{ 0x41000000, 0 },
    { 0x60000000, 1 }, { 0x50000000, 2 }, { 0x48000000, 3 }, { 0x44000000, 4 }, { 0x42000000, 5 },
    //{ 0x41000000, 6 }
};

/// Keeps number of elements in pattern threat.
const uint32_t ThreatWinner::m_ThreatPatternElements = NUMELEM(m_ThreatPatternX);

/// Define all points of view because not all point of view must be checked. See m_ThreatPattern
/// For both players are the same.
const uint32_t ThreatWinner::m_PointsView[] = { 1, 2, 3, 4, 5 };

ThreatWinner::ThreatWinner() : ThreatFinder(PATTERN_LENGHT, m_PointsView, NUMELEM(m_PointsView), ATOM_NUMBER_WINNER)
{
    // nothing to do.
}

///	Check pretendThreat if meets all requirement to real threat.
bool ThreatWinner::CheckThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                               const Board::Player playerPerspective) const
{
    // Equal the first pointOfview in m_ThreatPattern
    static const uint32_t pointOfViewOffset = 1;
    const uint32_t threatPatternIndex       = pointOfView - pointOfViewOffset;

    static const uint32_t myExpectedPawnInRow = 5;
    uint32_t myPawnsCntrMask                  = 0;
    uint32_t adversaryCntrMask                = 0;
    uint32_t emptyCntrMask                    = 0;
    uint32_t asterixCntrMask                  = 0;
    uint32_t threatPattern                    = 0;

    if(Board::PLAYER_A == playerPerspective)
    {
        myPawnsCntrMask   = 0x000000FF;
        adversaryCntrMask = 0x0000FF00;
        emptyCntrMask     = 0x00FF0000;
        asterixCntrMask   = 0xFF000000;
        threatPattern     = m_ThreatPatternX[threatPatternIndex].m_ThreatPattern;
    }
    else if(Board::PLAYER_B == playerPerspective)
    {
        myPawnsCntrMask   = 0x0000FF00;
        adversaryCntrMask = 0x000000FF;
        emptyCntrMask     = 0x00FF0000;
        asterixCntrMask   = 0xFF000000;
        threatPattern     = m_ThreatPatternO[threatPatternIndex].m_ThreatPattern;
    }
    else
    {
        assert(false);
    }

    // 1. Check my pawns.
    const uint32_t myPawnsCntr = __builtin_popcount(pretendThreat & myPawnsCntrMask);
    const bool isMyCntrMatch   = (myPawnsCntr == myExpectedPawnInRow);

    // 2. Check enemy pawns.
    // n.a

    // 3. Check empty space.
    // n.a

    // 4. Check asterix.
    const bool isAsterixMatch = ((pretendThreat & asterixCntrMask) == (threatPattern & asterixCntrMask));

    const bool retVal = (isMyCntrMatch && isAsterixMatch);

    // 5. If found leave down details.
    if(retVal)
    {
        m_ThreatDownDetails.m_HexCode           = pretendThreat;
        m_ThreatDownDetails.m_PointOfView       = pointOfView;
        m_ThreatDownDetails.m_PlayerPerspective = playerPerspective;
    }

    return retVal;
}

/// Gets threat up details after threat has been found.
void ThreatWinner::GetThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                                      ThreatUpDetails & rThreatUpDetails) const
{
    const uint32_t stepForward      = PATTERN_LENGHT - m_ThreatDownDetails.m_PointOfView - 1;
    const uint32_t stepBackward     = m_ThreatDownDetails.m_PointOfView;
    uint32_t steps                  = 0;
    uint32_t myPawnsCntrMask        = 0;
    uint32_t adversaryPawnsCntrMask = 0;
    uint32_t emptyCntrMask          = 0;
    uint32_t asterixCntrMask        = 0;
    uint32_t threatPattern          = 0;
    uint32_t symmetricThreatPattern = 0;
    uint32_t myPawnsShift           = 0;
    uint32_t enemyPawnsShift        = 0;

    // 0. Precondition.
    const Board::Direction directionForward  = Trend2DirectionStraight.at(trend);
    const Board::Direction directionBackward = Trend2DirectionReverse.at(trend);

    if(Board::PLAYER_A == m_ThreatDownDetails.m_PlayerPerspective)
    {
        myPawnsCntrMask        = 0x000000FF;
        adversaryPawnsCntrMask = 0x0000FF00;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        myPawnsShift           = 0;
        enemyPawnsShift        = 8;
    }
    else if(Board::PLAYER_B == m_ThreatDownDetails.m_PlayerPerspective)
    {
        myPawnsCntrMask        = 0x0000FF00;
        adversaryPawnsCntrMask = 0x000000FF;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        myPawnsShift           = 8;
        enemyPawnsShift        = 0;
    }
    else
    {
        assert(false);
    }

    // 0. HexCode normalization to pov == 0.
    const uint8_t myPawnsHexCode =
        static_cast<uint8_t>((m_ThreatDownDetails.m_HexCode & myPawnsCntrMask) >> myPawnsShift);
    const uint8_t myPawnsHexCodeNorm = StandarizePOV(myPawnsHexCode, m_ThreatDownDetails.m_PointOfView, PATTERN_LENGHT);

    Board::PositionXY initialPositionNorm = initialPosition;
    GetGomokuBoard().GoDirection(initialPositionNorm, directionBackward, m_ThreatDownDetails.m_PointOfView);

    // 1. Provide my pawns.
    GetPieces(myPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_MyPawns[0],
              ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS);

    // 2. Provide asterixes.
    Board::PositionXY asterix1Tmp = rThreatUpDetails.m_MyPawns[0];
    Board::PositionXY asterix2Tmp = rThreatUpDetails.m_MyPawns[4];
    GetGomokuBoard().GoDirection(asterix1Tmp, directionBackward);
    GetGomokuBoard().GoDirection(asterix2Tmp, directionForward);
    const bool isAsterix1TmpOnBoard = GetGomokuBoard().IsOnBoard(asterix1Tmp);
    const bool isAsterix2TmpOnBoard = GetGomokuBoard().IsOnBoard(asterix2Tmp);

    Board::PositionXY beginTmp;
    Board::PositionXY endTmp;

    if(isAsterix1TmpOnBoard && isAsterix2TmpOnBoard)
    {
        beginTmp                        = asterix1Tmp;
        endTmp                          = asterix2Tmp;
        rThreatUpDetails.m_Asterixes[0] = asterix1Tmp;
        rThreatUpDetails.m_Asterixes[1] = asterix2Tmp;
    }
    else if(!isAsterix1TmpOnBoard && isAsterix2TmpOnBoard)
    {
        beginTmp                        = rThreatUpDetails.m_MyPawns[0];
        endTmp                          = asterix2Tmp;
        rThreatUpDetails.m_Asterixes[0] = asterix2Tmp;
        rThreatUpDetails.m_Asterixes[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    }
    else if(isAsterix1TmpOnBoard && !isAsterix2TmpOnBoard)
    {
        beginTmp                        = asterix1Tmp;
        endTmp                          = rThreatUpDetails.m_MyPawns[4];
        rThreatUpDetails.m_Asterixes[0] = asterix1Tmp;
        rThreatUpDetails.m_Asterixes[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    }
    else if(!isAsterix1TmpOnBoard && !isAsterix2TmpOnBoard)
    {
        beginTmp                        = rThreatUpDetails.m_MyPawns[0];
        endTmp                          = rThreatUpDetails.m_MyPawns[4];
        rThreatUpDetails.m_Asterixes[0] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
        rThreatUpDetails.m_Asterixes[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    }
    else
    {
        // nothing to do.
    }

    // 3. Provide extended gaps.
    // none

    // 4. Set begin and end.
    rThreatUpDetails.m_BeginningThreat = beginTmp;
    rThreatUpDetails.m_EndThreat       = endTmp;

    // Clear for the next coming.
    m_ThreatDownDetails.ClearAll();
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