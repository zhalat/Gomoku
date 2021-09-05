/////////////////////////////////////////////////////////////////////////////////////////
/// @file Threat2CaseC.cpp
///
/// Threat2CaseC class definition.
///
/// @par Full Description.
/// Threat2CaseC finds pawns' which constitute one case of four pattern.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 18-Feb-2016 Initial revision.
/// - zhalat 15-Oct-2016 Performance improvement.
/// 					 Pattern mask usage instead of full pattern.
/// - zhalat 27-Nov-2017 All threat pieces location available via GetThreatUpDetails().
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Threat2CaseC.hpp"  // Threat2CaseC definition.

// FORWARD REFERENCES
// <none>

/// Tells how many pawns/gaps/asterixes this thrat has.
const std::unordered_map<ThreatFinder::ThreatAtom, int, std::hash<int>> Threat2CaseC::ATOM_NUMBER_2C = {
    { ThreatFinder::MY_PAWN, 2 },
    { ThreatFinder::ENEMY_PAWN, 0 },
    { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
    { ThreatFinder::ASTERIX, -1 }  // it depends.
};

/// Threat-mask for X player.
const ThreatFinder::ThreatPattern Threat2CaseC::m_ThreatPatternX[] = {
    // Finds:
    // oxx...o
    // o.xx..o
    // o..xx.o
    // o...xxo
    // ox.x..o
    // o.x.x.o
    //{ 0x00004100, 0 },
    { 0x00006000, 1 }, { 0x00005000, 2 }, { 0x00004800, 3 }, { 0x00004400, 4 }, { 0x00004200, 5 },
    //{ 0x00004100, 6 }
};

/// Threat-mask for O player.
const ThreatFinder::ThreatPattern Threat2CaseC::m_ThreatPatternO[] = {
    // Finds:
    // xoo...x
    // x.oo..x
    // x..oo.x
    // x...oox
    // xo.o..x
    // x.o.o.x
    //{ 0x00000041, 0 },
    { 0x00000060, 1 }, { 0x00000050, 2 }, { 0x00000048, 3 }, { 0x00000044, 4 }, { 0x00000042, 5 },
    //{ 0x00000041, 6 }
};

/// Keeps number of elements in pattern threat.
const uint32_t Threat2CaseC::m_ThreatPatternElements = NUMELEM(m_ThreatPatternX);

/// Define all points of view. Those are taken from m_ThreatPattern.
/// For both player is the same.
const uint32_t Threat2CaseC::m_PointsView[] = { 1, 2, 3, 4, 5 };

Threat2CaseC::Threat2CaseC() : ThreatFinder(PATTERN_LENGHT, m_PointsView, NUMELEM(m_PointsView), ATOM_NUMBER_2C)
{
    // nothing to do.
}

///	Check pretendThreat if meets all requirement to real threat.
bool Threat2CaseC::CheckThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                               const Board::Player playerPerspective) const
{
    // Equal the first pointOfview in m_ThreatPattern
    static const uint32_t pointOfViewOffset = 1;
    const uint32_t threatPatternIndex       = pointOfView - pointOfViewOffset;

    static const uint32_t myExpectedPawnInRow = 2;
    static const uint32_t expectedGaps        = 3;
    uint32_t myPawnsCntrMask                  = 0;
    uint32_t adversaryPawnsCntrMask           = 0;
    uint32_t emptyCntrMask                    = 0;
    uint32_t asterixCntrMask                  = 0;
    uint32_t threatPattern                    = 0;

    if(Board::PLAYER_A == playerPerspective)
    {
        myPawnsCntrMask        = 0x000000FF;
        adversaryPawnsCntrMask = 0x0000FF00;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        threatPattern          = m_ThreatPatternX[threatPatternIndex].m_ThreatPattern;
    }
    else if(Board::PLAYER_B == playerPerspective)
    {
        myPawnsCntrMask        = 0x0000FF00;
        adversaryPawnsCntrMask = 0x000000FF;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        threatPattern          = m_ThreatPatternO[threatPatternIndex].m_ThreatPattern;
    }
    else
    {
        assert(false);
    }

    // 1. Check my pawns(number and location).
    const uint32_t myPawnsCntr = __builtin_popcount(pretendThreat & myPawnsCntrMask);
    const bool isMyPawnsMatch  = (myPawnsCntr == myExpectedPawnInRow);

    // 2. Check enemy pawns.
    const bool isEnemyPawnsMatch =
        ((pretendThreat & adversaryPawnsCntrMask) & (threatPattern & adversaryPawnsCntrMask)) ==
        (threatPattern & adversaryPawnsCntrMask);

    // 3. Check empty space.
    const uint32_t gapsCntr     = __builtin_popcount(pretendThreat & emptyCntrMask);
    const bool isGapsPawnsMatch = (gapsCntr == expectedGaps);

    // 4. Check asterix.
    // n.a

    // Summarize.
    const bool isAllMatch = isMyPawnsMatch && isEnemyPawnsMatch && isGapsPawnsMatch;

    const bool retVal = isAllMatch;

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
void Threat2CaseC::GetThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                                      ThreatUpDetails & rThreatUpDetails) const
{
    const uint32_t stepForward      = PATTERN_LENGHT - m_ThreatDownDetails.m_PointOfView - 1;
    const uint32_t stepBackward     = m_ThreatDownDetails.m_PointOfView;
    const uint32_t specialCaseMask  = 0x1C;
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
    const uint8_t enemyPawnsHexCode =
        static_cast<uint8_t>((m_ThreatDownDetails.m_HexCode & adversaryPawnsCntrMask) >> enemyPawnsShift);
    const uint8_t gapsHexCode        = static_cast<uint8_t>((m_ThreatDownDetails.m_HexCode & emptyCntrMask) >> 16);
    const uint8_t myPawnsHexCodeNorm = StandarizePOV(myPawnsHexCode, m_ThreatDownDetails.m_PointOfView, PATTERN_LENGHT);
    const uint8_t enemyPawnsHexCodeNorm =
        StandarizePOV(enemyPawnsHexCode, m_ThreatDownDetails.m_PointOfView, PATTERN_LENGHT);
    const uint8_t gapsHexCodeNorm = StandarizePOV(gapsHexCode, m_ThreatDownDetails.m_PointOfView, PATTERN_LENGHT);

    Board::PositionXY initialPositionNorm = initialPosition;
    GetGomokuBoard().GoDirection(initialPositionNorm, directionBackward, m_ThreatDownDetails.m_PointOfView);

    // 1. Provide my pawns.
    GetPieces(myPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_MyPawns[0],
              ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS);

    // 2. Provide enemy pawns.
    GetPieces(enemyPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_EnemyPawns[0],
              ThreatFinder::ThreatUpDetails::MAX_ENEMY_PAWNS);
    // a. make adjustment for a case ex. |.x.x.o   o.x.x.|
    const bool isEnemyPawnOnBoard1 = GetGomokuBoard().IsOnBoard(rThreatUpDetails.m_EnemyPawns[0]);
    const bool isEnemyPawnOnBoard2 = GetGomokuBoard().IsOnBoard(rThreatUpDetails.m_EnemyPawns[1]);
    Board::PositionXY beginTmp     = rThreatUpDetails.m_EnemyPawns[0];
    Board::PositionXY endTmp       = rThreatUpDetails.m_EnemyPawns[1];
    if(!isEnemyPawnOnBoard1 && !isEnemyPawnOnBoard2)
    {
        GetGomokuBoard().GoDirection(rThreatUpDetails.m_EnemyPawns[0], directionForward);
        GetGomokuBoard().GoDirection(rThreatUpDetails.m_EnemyPawns[1], directionBackward);
        beginTmp = rThreatUpDetails.m_EnemyPawns[0];
        endTmp   = rThreatUpDetails.m_EnemyPawns[1];

        rThreatUpDetails.m_EnemyPawns[0] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
        rThreatUpDetails.m_EnemyPawns[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    }
    else if(isEnemyPawnOnBoard1 && !isEnemyPawnOnBoard2)
    {
        GetGomokuBoard().GoDirection(rThreatUpDetails.m_EnemyPawns[1], directionBackward);
        endTmp = rThreatUpDetails.m_EnemyPawns[1];

        rThreatUpDetails.m_EnemyPawns[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    }
    else if(!isEnemyPawnOnBoard1 && isEnemyPawnOnBoard2)
    {
        GetGomokuBoard().GoDirection(rThreatUpDetails.m_EnemyPawns[0], directionForward);
        beginTmp                         = rThreatUpDetails.m_EnemyPawns[0];
        rThreatUpDetails.m_EnemyPawns[0] = rThreatUpDetails.m_EnemyPawns[1];
        rThreatUpDetails.m_EnemyPawns[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    }
    else
    {
        // nothing to do
    }

    // 3. Provide gaps.
    GetPieces(gapsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_Gaps[0],
              ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES);

    // 4. Provide extended gaps. Special case: ox...xo
    Board::PositionXY pretendExtGap1 = rThreatUpDetails.m_MyPawns[1];
    Board::PositionXY pretendExtGap2 = rThreatUpDetails.m_MyPawns[0];
    GetGomokuBoard().GoDirection(pretendExtGap1, directionForward, 2);
    GetGomokuBoard().GoDirection(pretendExtGap2, directionBackward, 2);
    const bool isPretendExtGap1OK =
        (pretendExtGap1 <= rThreatUpDetails.m_Gaps[2]) && (GetGomokuBoard().IsOnBoard(pretendExtGap1));
    const bool isPretendExtGap2OK =
        (pretendExtGap2 >= rThreatUpDetails.m_Gaps[0]) && (GetGomokuBoard().IsOnBoard(pretendExtGap2));
    const bool isSpecialCaseOK = (specialCaseMask == (specialCaseMask & gapsHexCodeNorm));

    if(isPretendExtGap1OK)
    {
        rThreatUpDetails.m_ExtGaps[0] = pretendExtGap1;
        rThreatUpDetails.m_ExtGaps[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    }
    else if(isPretendExtGap2OK)
    {
        rThreatUpDetails.m_ExtGaps[0] = pretendExtGap2;
        rThreatUpDetails.m_ExtGaps[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    }
    else if(isSpecialCaseOK)
    {
        // ox...xo. Extended gaps is in the middle.
        rThreatUpDetails.m_ExtGaps[0] = rThreatUpDetails.m_Gaps[1];
        rThreatUpDetails.m_ExtGaps[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    }
    else
    {
        rThreatUpDetails.m_ExtGaps[0] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
        rThreatUpDetails.m_ExtGaps[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    }

    // 5. Set begin and end.
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