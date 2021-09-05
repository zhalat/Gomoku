/////////////////////////////////////////////////////////////////////////////////////////
/// @file Threat3CaseA.cpp
///
/// Threat3CaseA class definition.
///
/// @par Full Description.
/// Threat3CaseA finds pawns' which constitute one case of four pattern.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 18-Feb-2016 Initial revision.
/// - zhalat 15-Oct-2016 Performance improvement.
/// 					 Pattern mask usage instead of full pattern.
/// - zhalat 03-Dec-2016 Bug fixing: CheckThreat() threated opponent move as itself.
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
#include "Threat3CaseA.hpp"  // Threat3CaseA definition.

// FORWARD REFERENCES
// <none>

/// Tells how many pawns/gaps/asterixes this thrat has.
const std::unordered_map<ThreatFinder::ThreatAtom, int, std::hash<int>> Threat3CaseA::ATOM_NUMBER_3A = {
    { ThreatFinder::MY_PAWN, 2 },
    { ThreatFinder::ENEMY_PAWN, 0 },
    { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
    { ThreatFinder::ASTERIX, -1 }  // it depends.
};

/// Threat-mask for X player.
const ThreatFinder::ThreatPattern Threat3CaseA::m_ThreatPatternX[] = {
    // Finds:
    // ..XXX.*
    // .X.XX.*
    // .XX.X.*
    // .XXX..*
    //{ 0x40211E00, 0 },
    { 0x20500F00, 1 },
    { 0x10482700, 2 },
    { 0x08443300, 3 },
    { 0x04423900, 4 },
    { 0x02413C00, 5 },
    //{ 0x01423C00, 6 },

    // Finds:
    // *..XXX.
    // *.X.XX.
    // *.XX.X.
    // *.XXX..
    //{ 0x01423C00, 0 },
    { 0x40211E00, 1 },
    { 0x40300F00, 2 },
    { 0x40281700, 3 },
    { 0x40241B00, 4 },
    { 0x40221D00, 5 },
    //{ 0x40211E00, 6 },
};

/// Threat-mask for O player.
const ThreatFinder::ThreatPattern Threat3CaseA::m_ThreatPatternO[] = {
    // Finds:
    // ..OOO.*
    // .O.OO.*
    // .OO.O.*
    // .OOO..*
    //{ 0x4021001E, 0 },
    { 0x2050000F, 1 },
    { 0x10480027, 2 },
    { 0x08440033, 3 },
    { 0x04420039, 4 },
    { 0x0241003C, 5 },
    //{ 0x0142003C, 6 },

    // Finds:
    // *..OOO.
    // *.O.OO.
    // *.OO.O.
    // *.OOO..
    //{ 0x0142003C, 0 },
    { 0x4021001E, 1 },
    { 0x4030000F, 2 },
    { 0x40280017, 3 },
    { 0x4024001B, 4 },
    { 0x4022001D, 5 },
    //{ 0x4021001E, 6 },
};

/// Keeps number of elements in pattern threat.
const uint32_t Threat3CaseA::m_ThreatPatternElements = NUMELEM(m_ThreatPatternX) / 2;

/// Define all points of view. Those are taken from m_ThreatPattern.
/// For both player is the same.
const uint32_t Threat3CaseA::m_PointsView[] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };

Threat3CaseA::Threat3CaseA() : ThreatFinder(PATTERN_LENGHT, m_PointsView, NUMELEM(m_PointsView), ATOM_NUMBER_3A)
{
    m_FoundFlags.ClearAll();
}

///	Check pretendThreat if meets all requirement to real threat.
bool Threat3CaseA::CheckThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                               const Board::Player playerPerspective) const
{
    // Points when to switch to search symmetric pattern.
    static const uint32_t pointOfViewSwitch = 0x05;
    bool FindSuccessNormal                  = false;
    bool FindSuccessSymmetric               = false;

    if(true == m_FoundFlags.m_IsSearchingForSymmetric)
    {
        // It means that ThreatFinder is searching for symmetric pattern.
        if(false == m_FoundFlags.m_IsSymmetricFound)
        {
            // It means symmetric pattern has not been found yet.
            FindSuccessSymmetric = CheckThreatSymmetric(pretendThreat, pointOfView, playerPerspective);
        }
    }
    else
    {
        // It means that ThreatFinder is searching for normal pattern.
        if(false == m_FoundFlags.m_IsNormalFound)
        {
            // It means normal pattern has not been found yet.
            FindSuccessNormal = CheckThreatNormal(pretendThreat, pointOfView, playerPerspective);
        }
    }

    // 2. If found, leave down details.
    if(FindSuccessNormal || FindSuccessSymmetric)
    {
        m_ThreatDownDetails.m_HexCode           = pretendThreat;
        m_ThreatDownDetails.m_PointOfView       = pointOfView;
        m_ThreatDownDetails.m_PlayerPerspective = playerPerspective;

        if(FindSuccessNormal)
        {
            m_ThreatDownDetails.m_FoundFlags.m_IsNormalFound = true;
            m_FoundFlags.m_IsNormalFound                     = true;
        }

        if(FindSuccessSymmetric)
        {
            m_ThreatDownDetails.m_FoundFlags.m_IsSymmetricFound = true;
            m_FoundFlags.m_IsSymmetricFound                     = true;
        }
    }

    // 3. Switch to symmetric
    if(pointOfView == pointOfViewSwitch)
    {
        m_FoundFlags.m_IsSearchingForSymmetric = true;
    }

    return (FindSuccessNormal || FindSuccessSymmetric);
}

// Check threat to find normal pattern.
bool Threat3CaseA::CheckThreatNormal(const uint32_t pretendThreat, const uint32_t pointOfView,
                                     const Board::Player playerPerspective) const
{
    // Equal the first pointOfview in m_ThreatPattern
    static const uint32_t pointOfViewOffset = 1;
    const uint32_t threatPatternIndex       = pointOfView - pointOfViewOffset;

    static const uint32_t myExpectedPawnInRow = 3;
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

    // 2. Check enemy pawns.
    const uint32_t enemyPawnsCntr = __builtin_popcount(pretendThreat & (threatPattern & adversaryPawnsCntrMask));
    const bool isEnemyCntrMatch   = (enemyPawnsCntr == 0);

    // 3. Check empty space.
    const uint32_t gapsCntr = __builtin_popcount(pretendThreat & emptyCntrMask);
    const bool isGapsCntrMatch =
        ((pretendThreat & emptyCntrMask) & (threatPattern & emptyCntrMask)) == (threatPattern & emptyCntrMask);

    // 4. Check asterix.
    const bool isAsterixMatch =
        ((pretendThreat & asterixCntrMask) & (threatPattern & asterixCntrMask)) == (threatPattern & asterixCntrMask);

    // Summarize.
    const bool isAllMatch = (myPawnsCntr == myExpectedPawnInRow) && isEnemyCntrMatch && (gapsCntr >= expectedGaps) &&
                            isGapsCntrMatch && isAsterixMatch;
    const bool retVal = isAllMatch;
    return retVal;
}

// Check threat to find symmetric pattern.
bool Threat3CaseA::CheckThreatSymmetric(const uint32_t pretendThreat, const uint32_t pointOfView,
                                        const Board::Player playerPerspective) const
{
    // Equal the first pointOfview in m_ThreatPattern
    static const uint32_t pointOfViewOffset    = 1;
    const uint32_t symmetricThreatPatternIndex = NUMELEM(m_PointsView) / 2 + pointOfView - pointOfViewOffset;

    static const uint32_t myExpectedPawnInRow = 3;
    static const uint32_t expectedGaps        = 3;
    uint32_t myPawnsCntrMask                  = 0;
    uint32_t adversaryPawnsCntrMask           = 0;
    uint32_t emptyCntrMask                    = 0;
    uint32_t asterixCntrMask                  = 0;
    uint32_t symmetricThreatPattern           = 0;

    if(Board::PLAYER_A == playerPerspective)
    {
        myPawnsCntrMask        = 0x000000FF;
        adversaryPawnsCntrMask = 0x0000FF00;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        symmetricThreatPattern = m_ThreatPatternX[symmetricThreatPatternIndex].m_ThreatPattern;
    }
    else if(Board::PLAYER_B == playerPerspective)
    {
        myPawnsCntrMask        = 0x0000FF00;
        adversaryPawnsCntrMask = 0x000000FF;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        symmetricThreatPattern = m_ThreatPatternO[symmetricThreatPatternIndex].m_ThreatPattern;
    }
    else
    {
        assert(false);
    }

    // 1. Check my pawns(number and location).
    const uint32_t myPawnsCntr = __builtin_popcount(pretendThreat & myPawnsCntrMask);

    // 2. Check enemy pawns.
    const uint32_t enemySymmetricPawnsCntr =
        __builtin_popcount(pretendThreat & (symmetricThreatPattern & adversaryPawnsCntrMask));
    const bool isEnemySymmetricCntrMatch = (enemySymmetricPawnsCntr == 0);

    // 3. Check empty space.
    const uint32_t gapsCntr = __builtin_popcount(pretendThreat & emptyCntrMask);
    const bool isGapsCntrSymmetricMatch =
        ((pretendThreat & emptyCntrMask) & (symmetricThreatPattern & emptyCntrMask)) ==
        (symmetricThreatPattern & emptyCntrMask);

    // 4. Check asterix.
    const bool isAsteriSymmetricxMatch =
        ((pretendThreat & asterixCntrMask) & (symmetricThreatPattern & asterixCntrMask)) ==
        (symmetricThreatPattern & asterixCntrMask);

    // Summarize.
    const bool isAllSymmetricMatch = (myPawnsCntr == myExpectedPawnInRow) && isEnemySymmetricCntrMatch &&
                                     (gapsCntr >= expectedGaps) && isGapsCntrSymmetricMatch && isAsteriSymmetricxMatch;

    const bool retVal = isAllSymmetricMatch;
    return retVal;
}

/// Gets threat up details after threat has been found.
void Threat3CaseA::GetThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                                      ThreatUpDetails & rThreatUpDetails) const
{
    const uint32_t lastGapIndex     = 2;
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
    const uint8_t myPawnsHexCodeNorm = StandarizePOV(myPawnsHexCode, m_ThreatDownDetails.m_PointOfView, PATTERN_LENGHT);
    const uint8_t gapsHexCodeNorm    = StandarizePOV(gapsHexCode, m_ThreatDownDetails.m_PointOfView, PATTERN_LENGHT);

    Board::PositionXY initialPositionNorm = initialPosition;
    GetGomokuBoard().GoDirection(initialPositionNorm, directionBackward, m_ThreatDownDetails.m_PointOfView);

    // 1. Provide my pawns.
    GetPieces(myPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_MyPawns[0],
              ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS);

    // 2. Provide asterixes & gaps
    if(m_ThreatDownDetails.m_FoundFlags.m_IsNormalFound)
    {
        // a. Get asterixes.
        Board::PositionXY initialPositionNormTmp = initialPositionNorm;
        GetGomokuBoard().GoDirection(initialPositionNormTmp, directionForward, PATTERN_LENGHT - 1);
        rThreatUpDetails.m_Asterixes[0] = GetGomokuBoard().IsOnBoard(initialPositionNormTmp)
                                              ? initialPositionNormTmp
                                              : ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;

        // b. Get gaps. Keeps gaps in index 0-4.
        // 	  We don't want to count asterix as a gap. Remove that bit.
        uint8_t gapsHexCodeNormTmp = gapsHexCodeNorm;
        CLR_BIT(gapsHexCodeNormTmp, (PATTERN_LENGHT - 1));
        GetPieces(gapsHexCodeNormTmp, initialPositionNorm, directionForward, &rThreatUpDetails.m_Gaps[0],
                  ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES / 2);

        // c. Get extension gap. It's two movies from the second X. Must not be gather than Gaps[3].
        Board::PositionXY pretendExtGap = rThreatUpDetails.m_MyPawns[2];
        GetGomokuBoard().GoDirection(pretendExtGap, directionForward, 2);
        const bool ispretendExtGapOK =
            (pretendExtGap <= rThreatUpDetails.m_Gaps[2]) && (GetGomokuBoard().IsOnBoard(pretendExtGap));
        rThreatUpDetails.m_ExtGaps[0] =
            (ispretendExtGapOK) ? pretendExtGap : ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;

        // d. Provide threat beginning.
        rThreatUpDetails.m_BeginningThreat = rThreatUpDetails.m_Gaps[0];
        rThreatUpDetails.m_EndThreat =
            (rThreatUpDetails.m_Asterixes[0] != ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD)
                ? rThreatUpDetails.m_Asterixes[0]
                : rThreatUpDetails.m_Gaps[lastGapIndex];
    }

    if(m_ThreatDownDetails.m_FoundFlags.m_IsSymmetricFound)
    {
        // a. Get asterixes.
        rThreatUpDetails.m_Asterixes[1] = (true == GetGomokuBoard().IsOnBoard(initialPositionNorm))
                                              ? initialPositionNorm
                                              : ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;

        // b. Get gaps. Keeps gaps in index 5-9.
        // 	  We don't want to count asterix as a gap. Remove that bit.
        uint8_t gapsHexCodeNormTmp = gapsHexCodeNorm;
        CLR_BIT(gapsHexCodeNormTmp, 0);
        GetPieces(gapsHexCodeNormTmp, initialPositionNorm, directionForward,
                  &rThreatUpDetails.m_Gaps[ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES / 2],
                  ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES / 2);

        // c. Get extension gap. It's two movies from the first X. Must not be lower than Gaps[0].
        Board::PositionXY pretendExtGap = rThreatUpDetails.m_MyPawns[0];
        GetGomokuBoard().GoDirection(pretendExtGap, directionBackward, 2);
        const bool ispretendExtGapOK =
            (pretendExtGap >= rThreatUpDetails.m_Gaps[ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES / 2]) &&
            (GetGomokuBoard().IsOnBoard(pretendExtGap));
        rThreatUpDetails.m_ExtGaps[1] =
            ispretendExtGapOK ? pretendExtGap : ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;

        // d. Provide threat beginning & end. Threat's size must be greedy.
        const uint32_t lastGapSimmetricIndex = 2 + ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES / 2;
        rThreatUpDetails.m_BeginningThreat =
            (rThreatUpDetails.m_Asterixes[1] != ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD)
                ? rThreatUpDetails.m_Asterixes[1]
                : rThreatUpDetails.m_Gaps[ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES / 2];
        rThreatUpDetails.m_EndThreat =
            ((rThreatUpDetails.m_Gaps[lastGapSimmetricIndex] > rThreatUpDetails.m_EndThreat) ||
             (rThreatUpDetails.m_EndThreat == ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD))
                ? rThreatUpDetails.m_Gaps[lastGapSimmetricIndex]
                : rThreatUpDetails.m_EndThreat;
    }

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
