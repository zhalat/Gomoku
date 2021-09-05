/////////////////////////////////////////////////////////////////////////////////////////
/// @file Threat2CaseB.cpp
///
/// Threat2CaseB class definition.
///
/// @par Full Description.
/// Threat2CaseB finds pawns' which constitute one case of four pattern.
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
#include "Threat2CaseB.hpp"  // Threat2CaseB definition.

// FORWARD REFERENCES
// <none>

/// Tells how many pawns/gaps/asterixes this thrat has.
const std::unordered_map<ThreatFinder::ThreatAtom, int, std::hash<int>> Threat2CaseB::ATOM_NUMBER_2B = {
    { ThreatFinder::MY_PAWN, 2 },
    { ThreatFinder::ENEMY_PAWN, 0 },
    { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
    { ThreatFinder::ASTERIX, -1 }  // it depends.
};

/// Threat-mask for X player.
const ThreatFinder::ThreatPattern Threat2CaseB::m_ThreatPatternX[] = {
    // Finds:
    // oxx...*
    // ox.x..*
    // ox..x.*
    // ox...x*
    //{ 0x403C0102, 0 },
    { 0x201E4001, 1 },
    { 0x100F4020, 2 },
    { 0x08174020, 3 },
    { 0x041B4020, 4 },
    { 0x021D4020, 5 },
    //{ 0x011E4020, 6 },

    // Finds:
    // *x...xo
    // *.x..xo
    // *..x.xo
    // *...xxo
    //{ 0x011E4020, 0 },
    { 0x400F2010, 1 },
    { 0x40271008, 2 },
    { 0x40330804, 3 },
    { 0x40390402, 4 },
    { 0x403C0201, 5 },
    //{ 0x403C0102, 6 }
};

/// Threat-mask for O player.
const ThreatFinder::ThreatPattern Threat2CaseB::m_ThreatPatternO[] = {
    // Finds:
    // xoo...*
    // xo.o..*
    // xo..o.*
    // xo...o*
    //{ 0x403C0201, 0 },
    { 0x201E0140, 1 },
    { 0x100F2040, 2 },
    { 0x08172040, 3 },
    { 0x041B2040, 4 },
    { 0x021D2040, 5 },
    //{ 0x011E2040, 6 },

    // Finds:
    // *o...ox
    // *.o..ox
    // *..o.ox
    // *...oox
    //{ 0x011E2040, 0 },
    { 0x400F1020, 1 },
    { 0x40270810, 2 },
    { 0x40330408, 3 },
    { 0x40390204, 4 },
    { 0x403C0102, 5 },
    //{ 0x403C0201, 6 }
};

/// Keeps number of elements in pattern threat.
const uint32_t Threat2CaseB::m_ThreatPatternElements = NUMELEM(m_ThreatPatternX) / 2;

/// Define all points of view. Those are taken from m_ThreatPattern.
/// For both player is the same.
const uint32_t Threat2CaseB::m_PointsView[] = { 1, 2, 3, 4, 5 };

Threat2CaseB::Threat2CaseB() : ThreatFinder(PATTERN_LENGHT, m_PointsView, NUMELEM(m_PointsView), ATOM_NUMBER_2B)
{
    // nothing to do.
}

///	Check pretendThreat if meets all requirement to real threat.
bool Threat2CaseB::CheckThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                               const Board::Player playerPerspective) const
{
    // When first found (normal/symmetric) just quit.
    bool FindSuccessNormal    = false;
    bool FindSuccessSymmetric = false;

    // 1. Check symmetric/normal pattern.
    if(true == CheckThreatNormal(pretendThreat, pointOfView, playerPerspective))
    {
        FindSuccessNormal = true;
    }
    else if(true == CheckThreatSymmetric(pretendThreat, pointOfView, playerPerspective))
    {
        FindSuccessSymmetric = true;
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
        }

        if(FindSuccessSymmetric)
        {
            m_ThreatDownDetails.m_FoundFlags.m_IsSymmetricFound = true;
        }
    }

    return (FindSuccessNormal || FindSuccessSymmetric);
}

// Check threat to find normal pattern.
bool Threat2CaseB::CheckThreatNormal(const uint32_t pretendThreat, const uint32_t pointOfView,
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
    const bool isMyPawnsMatch =
        ((pretendThreat & myPawnsCntrMask) & (threatPattern & myPawnsCntrMask)) == (threatPattern & myPawnsCntrMask);

    // 2. Check enemy pawns.
    const bool isEnemyPawnsMatch =
        ((pretendThreat & adversaryPawnsCntrMask) & (threatPattern & adversaryPawnsCntrMask)) ==
        (threatPattern & adversaryPawnsCntrMask);

    // 3. Check empty space.
    const uint32_t gapsCntr = __builtin_popcount(pretendThreat & emptyCntrMask & threatPattern);

    // 4. Check asterix.
    const bool isAsterixMatch =
        ((pretendThreat & asterixCntrMask) & (threatPattern & asterixCntrMask)) == (threatPattern & asterixCntrMask);

    // Summarize.
    const bool isAllMatch = (myPawnsCntr == myExpectedPawnInRow) && isMyPawnsMatch && isEnemyPawnsMatch &&
                            (gapsCntr >= expectedGaps) && isAsterixMatch;

    return isAllMatch;
}

// Check threat to find symmetric pattern.
bool Threat2CaseB::CheckThreatSymmetric(const uint32_t pretendThreat, const uint32_t pointOfView,
                                        const Board::Player playerPerspective) const
{
    // Equal the first pointOfview in m_ThreatPattern
    static const uint32_t pointOfViewOffset    = 1;
    static const uint32_t symmetricOffset      = NUMELEM(m_ThreatPatternX) / 2;
    const uint32_t symmetricThreatPatternIndex = pointOfView + symmetricOffset - pointOfViewOffset;

    static const uint32_t myExpectedPawnInRow = 2;
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
    const bool isMySymmetricPawnsMatch =
        ((pretendThreat & myPawnsCntrMask) & (symmetricThreatPattern & myPawnsCntrMask)) ==
        (symmetricThreatPattern & myPawnsCntrMask);

    // 2. Check enemy pawns.
    const bool isEnemySymmetricPawnsMatch =
        ((pretendThreat & adversaryPawnsCntrMask) & (symmetricThreatPattern & adversaryPawnsCntrMask)) ==
        (symmetricThreatPattern & adversaryPawnsCntrMask);

    // 3. Check empty space.
    const uint32_t gapsCntrSymmetric = __builtin_popcount(pretendThreat & emptyCntrMask & symmetricThreatPattern);

    // 4. Check asterix.
    const bool isAsterixSymmetricMatch =
        ((pretendThreat & asterixCntrMask) & (symmetricThreatPattern & asterixCntrMask)) ==
        (symmetricThreatPattern & asterixCntrMask);

    // Summarize.
    const bool isAllSymmetricMatch = (myPawnsCntr == myExpectedPawnInRow) && isMySymmetricPawnsMatch &&
                                     isEnemySymmetricPawnsMatch && (gapsCntrSymmetric >= expectedGaps) &&
                                     isAsterixSymmetricMatch;

    return isAllSymmetricMatch;
}

/// Gets threat up details after threat has been found.
void Threat2CaseB::GetThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
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

    int extGapIndex            = -1;
    uint8_t gapsHexCodeNormTmp = gapsHexCodeNorm;
    Board::PositionXY beginTmp = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    Board::PositionXY endTmp   = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    if(m_ThreatDownDetails.m_FoundFlags.m_IsNormalFound)
    {
        rThreatUpDetails.m_EnemyPawns[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
        const bool isEnemyOnBoard        = GetGomokuBoard().IsOnBoard(rThreatUpDetails.m_EnemyPawns[0]);

        // a. Adjust enemy/Get asterix.
        if(isEnemyOnBoard)
        {
            beginTmp = rThreatUpDetails.m_EnemyPawns[0];
        }
        else
        {
            rThreatUpDetails.m_EnemyPawns[0] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
            beginTmp                         = rThreatUpDetails.m_MyPawns[0];
        }

        endTmp = rThreatUpDetails.m_MyPawns[0];
        GetGomokuBoard().GoDirection(endTmp, directionForward, PATTERN_LENGHT - 2);

        const bool isEndTmpOnBoard = GetGomokuBoard().IsOnBoard(endTmp);
        if(isEndTmpOnBoard)
        {
            rThreatUpDetails.m_Asterixes[0] = endTmp;
        }
        else
        {
            rThreatUpDetails.m_Asterixes[0] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;

            // One step too far.
            GetGomokuBoard().GoDirection(endTmp, directionBackward);
        }

        // b. We don't want to count asterix as a gap. Remove that bit.
        CLR_BIT(gapsHexCodeNormTmp, (PATTERN_LENGHT - 1));

        // c. Get extended gaps index.
        static const uint8_t extGapsPattern1 = 0x38;
        static const uint8_t extGapsPattern2 = 0x34;
        static const uint8_t extGapsPattern3 = 0x1C;
        const bool isExtGapsPattern1OK       = (extGapsPattern1 == (extGapsPattern1 & gapsHexCodeNormTmp));
        const bool isExtGapsPattern2OK       = (extGapsPattern2 == (extGapsPattern2 & gapsHexCodeNormTmp));
        const bool isExtGapsPattern3OK       = (extGapsPattern3 == (extGapsPattern3 & gapsHexCodeNormTmp));

        if(isExtGapsPattern1OK)
            extGapIndex = 1;
        else if(isExtGapsPattern2OK)
            extGapIndex = 2;
        else if(isExtGapsPattern3OK)
            extGapIndex = 1;
        else
            extGapIndex = -1;
    }
    else if(m_ThreatDownDetails.m_FoundFlags.m_IsSymmetricFound)
    {
        // a. Adjust enemy/Get asterix.
        //   Enemy is one step further of the second myPawns.
        Board::PositionXY enemyTmp = rThreatUpDetails.m_MyPawns[1];
        GetGomokuBoard().GoDirection(enemyTmp, directionForward);

        const bool isEnemyOnBoard = GetGomokuBoard().IsOnBoard(enemyTmp);
        if(isEnemyOnBoard)
        {
            endTmp                           = enemyTmp;
            rThreatUpDetails.m_EnemyPawns[0] = endTmp;
            rThreatUpDetails.m_EnemyPawns[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
        }
        else
        {
            endTmp                           = rThreatUpDetails.m_MyPawns[1];
            rThreatUpDetails.m_EnemyPawns[0] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
            rThreatUpDetails.m_EnemyPawns[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
        }

        beginTmp = rThreatUpDetails.m_MyPawns[1];
        GetGomokuBoard().GoDirection(beginTmp, directionBackward, PATTERN_LENGHT - 2);

        const bool isBeginTmpOnBoard = GetGomokuBoard().IsOnBoard(beginTmp);
        if(isBeginTmpOnBoard)
        {
            rThreatUpDetails.m_Asterixes[0] = beginTmp;
        }
        else
        {
            rThreatUpDetails.m_Asterixes[0] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;

            // One step too far.
            GetGomokuBoard().GoDirection(beginTmp, directionForward);
        }

        // b. We don't want to count asterix as a gap. Remove that bit.
        CLR_BIT(gapsHexCodeNormTmp, 0);

        // c. Get extended gaps index.
        static const uint8_t extGapsPattern1 = 0x1C;
        static const uint8_t extGapsPattern2 = 0x16;
        static const uint8_t extGapsPattern3 = 0x0E;
        const bool isExtGapsPattern1OK       = (extGapsPattern1 == (extGapsPattern1 & gapsHexCodeNormTmp));
        const bool isExtGapsPattern2OK       = (extGapsPattern2 == (extGapsPattern2 & gapsHexCodeNormTmp));
        const bool isExtGapsPattern3OK       = (extGapsPattern3 == (extGapsPattern3 & gapsHexCodeNormTmp));

        if(isExtGapsPattern1OK)
            extGapIndex = 1;
        else if(isExtGapsPattern2OK)
            extGapIndex = 0;
        else if(isExtGapsPattern3OK)
            extGapIndex = 1;
        else
            extGapIndex = -1;
    }
    else
    {
        assert(false);
    }

    // 3. Provide gaps. Keeps gaps in index 0-4.
    GetPieces(gapsHexCodeNormTmp, initialPositionNorm, directionForward, &rThreatUpDetails.m_Gaps[0],
              ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES);

    // 4. Provide extended gap.
    rThreatUpDetails.m_ExtGaps[0] =
        (extGapIndex != -1) ? rThreatUpDetails.m_Gaps[extGapIndex] : ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;
    rThreatUpDetails.m_ExtGaps[1] = ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD;

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