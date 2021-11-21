/////////////////////////////////////////////////////////////////////////////////////////
/// @file Threat2CaseAA.cpp
///
/// Threat2CaseAA class definition.
///
/// @par Full Description.
/// Threat2CaseAA finds pawns' which constitute one case of four pattern.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 28-Oct-2017 Initial revision.
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
#include "Threat2CaseAA.hpp"  // Threat2CaseAA definition.

// FORWARD REFERENCES
// <none>

/// Tells how many pawns/gaps/asterixes this thrat has.
const std::unordered_map<ThreatFinder::ThreatAtom, int, std::hash<int>> Threat2CaseAA::ATOM_NUMBER_2AA = {
    { ThreatFinder::MY_PAWN, 2 },
    { ThreatFinder::ENEMY_PAWN, 0 },
    { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
    { ThreatFinder::ASTERIX, -1 }  // it depends.
};

/// Threat-mask for X player.
const ThreatFinder::ThreatPattern Threat2CaseAA::m_ThreatPatternX[] = {
    // Finds:
    // .x...x.
    //{ 0x005D0022, 0 },
    { 0x006E0011, 1 }, { 0x00570028, 2 }, { 0x005B0024, 3 }, { 0x005D0022, 4 }, { 0x005E0021, 5 },
    //{ 0x005D0022, 6 },
};

/// Threat-mask for O player.
const ThreatFinder::ThreatPattern Threat2CaseAA::m_ThreatPatternO[] = {
    // Finds:
    // .o...o.
    //{ 0x005D2200, 0 },
    { 0x006E1100, 1 }, { 0x00572800, 2 }, { 0x005B2400, 3 }, { 0x005D2200, 4 }, { 0x005E2100, 5 },
    //{ 0x005D2200, 6 },
};

/// Keeps number of elements in pattern threat.
const uint32_t Threat2CaseAA::m_ThreatPatternElements = NUMELEM(m_ThreatPatternX);

/// Define all points of view. Those are taken from m_ThreatPattern.
/// For both player is the same.
const uint32_t Threat2CaseAA::m_PointsView[] = { 1, 2, 3, 4, 5 };

Threat2CaseAA::Threat2CaseAA() : ThreatFinder(PATTERN_LENGHT, m_PointsView, NUMELEM(m_PointsView), ATOM_NUMBER_2AA)
{
    // nothing to do.
}

///	Check pretendThreat if meets all requirement to real threat.
bool Threat2CaseAA::CheckThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                                const Board::Player playerPerspective) const
{
    // Equal the first pointOfview in m_ThreatPattern
    static const uint32_t pointOfViewOffset = 1;
    const uint32_t threatPatternIndex       = pointOfView - pointOfViewOffset;

    static const uint32_t myExpectedPawnInRow = 2;
    static const uint32_t expectedGaps        = 5;
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
    const bool isMyPawnsMatch =
        ((pretendThreat & myPawnsCntrMask) & (threatPattern & myPawnsCntrMask)) == (threatPattern & myPawnsCntrMask);

    // 2. Check enemy pawns.
    const uint32_t enemyPawnsCntr = __builtin_popcount(pretendThreat & adversaryCntrMask);
    const bool isEnemyCntrMatch   = (enemyPawnsCntr == 0);

    // 3. Check empty space.
    const bool isEmptySpaceMatch =
        ((pretendThreat & emptyCntrMask) & (threatPattern & emptyCntrMask)) == (threatPattern & emptyCntrMask);

    // 4. Check asterix.
    // n.a

    const bool retVal = (isMyCntrMatch && isMyPawnsMatch && isEnemyCntrMatch && isEmptySpaceMatch);

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
void Threat2CaseAA::GetThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
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
    const uint8_t gapsHexCode        = static_cast<uint8_t>((m_ThreatDownDetails.m_HexCode & emptyCntrMask) >> 16);
    const uint8_t asterixHexCode     = static_cast<uint8_t>((m_ThreatDownDetails.m_HexCode & asterixCntrMask) >> 24);
    const uint8_t myPawnsHexCodeNorm = StandarizePOV(myPawnsHexCode, m_ThreatDownDetails.m_PointOfView, PATTERN_LENGHT);
    const uint8_t gapsHexCodeNorm    = StandarizePOV(gapsHexCode, m_ThreatDownDetails.m_PointOfView, PATTERN_LENGHT);
    const uint8_t asterixHexCodeNorm = StandarizePOV(asterixHexCode, m_ThreatDownDetails.m_PointOfView, PATTERN_LENGHT);

    Board::PositionXY initialPositionNorm = initialPosition;
    GetGomokuBoard().GoDirection(initialPositionNorm, directionBackward, m_ThreatDownDetails.m_PointOfView);

    // 1. Provide my pawns.
    GetPieces(myPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_MyPawns[0],
              ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS);

    // 2. Provide gaps.
    //    a. Don't count asterixes as gaps.
    uint8_t gapsHexCodeNormTmp = gapsHexCodeNorm;
    //    b. Get gaps.
    GetPieces(gapsHexCodeNormTmp, initialPositionNorm, directionForward, &rThreatUpDetails.m_Gaps[0],
              ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES);

    // 3. Provide extended gap.
    rThreatUpDetails.m_ExtGaps[0] = rThreatUpDetails.m_Gaps[2];
    rThreatUpDetails.m_ExtGaps[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    ;

    // 4. Provide beginning & end.
    rThreatUpDetails.m_BeginningThreat = rThreatUpDetails.m_Gaps[0];
    rThreatUpDetails.m_EndThreat       = rThreatUpDetails.m_Gaps[4];

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