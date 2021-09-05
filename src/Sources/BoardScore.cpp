/////////////////////////////////////////////////////////////////////////////////////////
/// @file BoardScore.cpp
///
/// Keeps threats for board.
///
/// @par Full Description.
/// Keeps threats for board.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 08-Apr-2016 Initial revision.
/// - zhalat 18-Nov-2016 Introducing spotter for managing threats changes.
/// - zhalat 15-Dec-2016 Extended interface for GetExGaps().
/// - zhalat 29-May-2017 Anomaly fix: GameRecord7_L4_fixed
/// - zhalat 04-Feb-2018 VectorLight repleaced by VectorUnique.
/// - zhalat 16-Feb-2018 GetLastAddedThreat() added.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2018 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>   // For assert.
#include <algorithm>  // For find().

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "BoardScore.hpp"            // For BoardScore declaration.
#include "ThreatsBloodRelation.hpp"  // For EXTENDED_NEIGHBORHOOD
#include "VectorUnique.hpp"          // For VectorUnique definitions.

// FORWARD REFERENCES
// <none>

// Point beyond the board. Useful for initialization.
const Board::PositionXY XY_OUT_OF_BOARD =
    Board::PositionXY(Board::PositionXY::INVALID_FIELD, Board::PositionXY::INVALID_FIELD);

/// Provide number of recognized threats of threatKind kind.
uint32_t BoardScore::GetNumberOfRecognizedThreat(ThreatFinder::KindOfThreats threatKind) const
{
    assert(threatKind < ThreatFinder::KindOfThreats::THREAT_NONE);

    const uint32_t index = static_cast<uint32_t>(threatKind);

    const uint32_t retVal = m_ThreatsOnBoard.m_NumberRecognizedThreat[index];

    return retVal;
}

/// Gets gaps belonging to provided kind of threat(extended included). Repetitive included.
void BoardScore::GetGapsNonUnique(std::vector<Board::PositionField> & rGaps,
                                  const ThreatFinder::KindOfThreats threatKind) const
{
    const uint32_t threatIndex = static_cast<uint32_t>(threatKind);

    // Get iterator to threat list:
    std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
        m_ThreatsOnBoard.m_RecognizedThreats[threatIndex].begin();

    for(; citer != m_ThreatsOnBoard.m_RecognizedThreats[threatIndex].end(); ++citer)
    {
        const ThreatFinder::ThreatLocation & rThreatLocation = *citer;

        // Symmetric threats (like 2A, 3A) might have duplicated gaps. One from normal side and second symmetric side.
        // Prevent adding the same gaps from the same threat.
        VectorUnique<Board::PositionField, GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE> addedGaps;

        // Go thru each threats' gaps.
        for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES; ++i)
        {
            const Board::PositionXY pretendGapXY = rThreatLocation.m_ThreatDetails.m_Gaps[i];

            if(ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD != pretendGapXY)
            {
                const Board::PositionField pretendGapPosition(m_pBoard->GetSize(), pretendGapXY);
                const bool isGapOK = !addedGaps.IsPresent(pretendGapPosition);

                if(isGapOK)
                {
                    rGaps.push_back(pretendGapPosition);
                    addedGaps.Insert(pretendGapPosition);
                }
            }
        }
    }
}

/// Gets gaps belonging to provided kind of threat(extended included). Repetitive doesn't included.
void BoardScore::GetGapsUnique(std::vector<Board::PositionField> & rGaps,
                               const ThreatFinder::KindOfThreats threatKind) const
{
    const uint32_t threatIndex = static_cast<uint32_t>(threatKind);

    // Get iterator to threat list:
    std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
        m_ThreatsOnBoard.m_RecognizedThreats[threatIndex].begin();

    // Keeps gaps that have been added.
    VectorUnique<Board::PositionField, GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE> addedGaps;

    for(; citer != m_ThreatsOnBoard.m_RecognizedThreats[threatIndex].end(); ++citer)
    {
        const ThreatFinder::ThreatLocation & rThreatLocation = *citer;

        // Go thru each threats' gaps.
        for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::MAX_EMPTY_SPACES; ++i)
        {
            const Board::PositionXY pretendGapXY = rThreatLocation.m_ThreatDetails.m_Gaps[i];
            const Board::PositionField pretendGap(m_pBoard->GetSize(), pretendGapXY);

            // Gap must be unique.
            const bool isGapOK =
                (pretendGapXY != ThreatFinder::ThreatLocation::XY_OUT_OF_BOARD) && (!addedGaps.IsPresent(pretendGap));

            if(isGapOK)
            {
                rGaps.push_back(pretendGap);
                addedGaps.Insert(pretendGap);
            }
        }
    }
}

/// Gets gaps that are common to more than one threat (extended included).
void BoardScore::GetGapsDuplicated(std::vector<Board::PositionField> & rGaps,
                                   const ThreatFinder::KindOfThreats threatKind) const
{
    std::vector<Board::PositionField> nonUniqueGaps;
    GetGapsNonUnique(nonUniqueGaps, threatKind);

    // Left only duplications.
    VectorUnique<Board::PositionField, GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE> firstGate;
    VectorUnique<Board::PositionField, GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE> secondtGate;
    for(std::vector<Board::PositionField>::const_iterator citer = nonUniqueGaps.begin(); citer < nonUniqueGaps.end();
        ++citer)
    {
        bool isFirstGateOK = firstGate.IsPresent(*citer);

        if(isFirstGateOK)
        {
            // But avoid to add duplication twice. Once is enough.
            bool isSecondGateOK = !secondtGate.IsPresent(*citer);

            if(isSecondGateOK)
            {
                rGaps.push_back(*citer);
                secondtGate.Insert(*citer);
            }
        }
        else
        {
            firstGate.Insert(*citer);
        }
    }
}

/// Gets all extend gaps belongs to provided threat.
void BoardScore::GetExGaps(std::vector<Board::PositionField> & exGaps,
                           const ThreatFinder::KindOfThreats threatKind) const
{
    const uint32_t threatIndex = static_cast<uint32_t>(threatKind);

    // Get iterator to threat list:
    std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
        m_ThreatsOnBoard.m_RecognizedThreats[threatIndex].begin();

    for(; citer != m_ThreatsOnBoard.m_RecognizedThreats[threatIndex].end(); ++citer)
    {
        const ThreatFinder::ThreatLocation & rThreatLocation = *citer;

        const Board::PositionXY xy1 = rThreatLocation.m_ThreatDetails.m_ExtGaps[0];
        const Board::PositionXY xy2 = rThreatLocation.m_ThreatDetails.m_ExtGaps[1];

        if(XY_OUT_OF_BOARD != xy1)
        {
            const Board::PositionField positionField(m_pBoard->GetSize(), xy1);
            exGaps.push_back(positionField);
        }

        if(XY_OUT_OF_BOARD != xy2)
        {
            const Board::PositionField positionField(m_pBoard->GetSize(), xy2);
            exGaps.push_back(positionField);
        }
    }
}

/// Get number of fields that both threats kind have in common.
uint32_t BoardScore::GetCommonFieldNumber(const ThreatFinder::KindOfThreats threatKindA,
                                          const ThreatFinder::KindOfThreats threatKindB) const
{
    uint32_t retVal = 0;

    if(threatKindA == threatKindB)
    {
        VectorUnique<Board::PositionField, GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE> tmp;

        const uint32_t threatIndex = static_cast<uint32_t>(threatKindA);
        std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
            m_ThreatsOnBoard.m_RecognizedThreats[threatIndex].begin();

        // Go thru each threat.
        for(; citer != m_ThreatsOnBoard.m_RecognizedThreats[threatIndex].end(); ++citer)
        {
            const ThreatFinder::ThreatLocation & rThreatLocation = *citer;

            // Go thru each threat's element.
            for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS; ++i)
            {
                const Board::PositionXY xy = rThreatLocation.m_ThreatDetails.m_MyPawns[i];
                if(XY_OUT_OF_BOARD == xy)
                {
                    break;
                }

                const Board::PositionField positionField(m_pBoard->GetSize(), xy);

                if(!tmp.IsPresent(positionField))
                {
                    tmp.Insert(positionField);
                }
                else
                {
                    // It means that other threat has the same field.
                    retVal++;
                }
            }
        }
    }
    else
    {
        std::list<Board::PositionField> tmp[GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE];

        const uint32_t threatIndexB = static_cast<uint32_t>(threatKindB);
        std::list<ThreatFinder::ThreatLocation>::const_iterator citerB =
            m_ThreatsOnBoard.m_RecognizedThreats[threatIndexB].begin();

        // 1. Put each elements of threat B to vector list.
        for(; citerB != m_ThreatsOnBoard.m_RecognizedThreats[threatIndexB].end(); ++citerB)
        {
            const ThreatFinder::ThreatLocation & rThreatLocation = *citerB;

            // Go thru each threat's element.
            for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS; ++i)
            {
                const Board::PositionXY xy = rThreatLocation.m_ThreatDetails.m_MyPawns[i];
                if(XY_OUT_OF_BOARD == xy)
                {
                    break;
                }

                const Board::PositionField positionField(m_pBoard->GetSize(), xy);
                const uint32_t index = static_cast<uint32_t>(positionField);
                tmp[index].push_back(positionField);
            }
        }

        const uint32_t threatIndexA = static_cast<uint32_t>(threatKindA);
        std::list<ThreatFinder::ThreatLocation>::const_iterator citerA =
            m_ThreatsOnBoard.m_RecognizedThreats[threatIndexA].begin();

        // 2. Go thru each threats
        for(; citerA != m_ThreatsOnBoard.m_RecognizedThreats[threatIndexA].end(); ++citerA)
        {
            const ThreatFinder::ThreatLocation & rThreatLocation = *citerA;

            // Go thru each threat's element and check how many threat threatKindB has in common.
            for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::MAX_MY_PAWNS; ++i)
            {
                const Board::PositionXY xy = rThreatLocation.m_ThreatDetails.m_MyPawns[i];
                if(XY_OUT_OF_BOARD == xy)
                {
                    break;
                }

                const Board::PositionField positionField(m_pBoard->GetSize(), xy);
                const uint32_t index = static_cast<uint32_t>(positionField);

                retVal += tmp[index].size();
            }
        }
    }

    return retVal;
}

/// From provided threat list remove such that include xy position.
uint32_t BoardScore::RemoveThreats(const Board::PositionXY xy)
{
    uint32_t retVal = 0;

    // Check if xy move is an enemy's move. If so it means:
    // -some special care must be taken when enemy's move is a part of my threat.
    //  The move could reduce my threat or just only mitigate
    // -if the enemy move doesn't touch my existing threats, no need to find a new threats or
    /// repudiate the previous.
    const bool isEnemyMove = ((m_pBoard->GetMove(xy) != m_player) && (m_pBoard->GetMove(xy) != Board::PLAYER_EMPTY));

    for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
    {
        // If there are no threats, its meaningless to check all cells.
        if(m_ThreatsOnBoard.m_NumberRecognizedThreat[i] > 0)
        {
            std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
                m_ThreatsOnBoard.m_RecognizedThreats[i].begin();

            // Indicates which part of threat (first / last) GetThreatElementPromotion shall take.
            // Indexes are associate with Trend enum VERTICAL= 0 etc. True means first
            bool GetThreatElementPromotionIndicator[4] = { true, true, true, true };

            for(; citer != m_ThreatsOnBoard.m_RecognizedThreats[i].end();)
            {
                // Check if provided xy is part of this threat.
                ThreatFinder::ThreatLocation threatLocation = *citer;
                const bool isPartOfThreat                   = IsPartOfThreat(threatLocation, xy);

                if(isPartOfThreat)
                {
                    if(isEnemyMove)  // There's necessity to run 'Dismissal' threat group.
                    {
                        // Get info required for reupadate threat. Must be able to keep up to 3 parts like: xxoxx or
                        // (rare situation) x.x..x.
                        Board::PositionXY threatElements[MAX_THREAT_PARTS] = { XY_OUT_OF_BOARD, XY_OUT_OF_BOARD,
                                                                               XY_OUT_OF_BOARD };

                        GetThreatElementDismissal(threatLocation, m_player, &threatElements[0]);
                        const ThreatFinder::KindOfThreats currentThreat = Score::m_ThreatScore[i].threatKind;
                        const ThreatFinder::Trend currentTrend          = threatLocation.m_Trend;

                        // Add to spotter not empty threat' part element.
                        for(uint32_t i = 0; i < MAX_THREAT_PARTS; ++i)
                        {
                            const Board::PositionXY xyThreatElement = threatElements[i];

                            if(XY_OUT_OF_BOARD != xyThreatElement)
                            {
                                // Ask Spotter to find out what is going on there.
                                const Spotter::RegionToInvestigate regionToInvestigate{ xyThreatElement, currentThreat,
                                                                                        currentTrend };
                                m_Spotter.AddToExecute(regionToInvestigate);
                            }
                        }
                    }
                    else  // There's necessity to run 'Promotion' threat group.
                    {
                        const ThreatFinder::KindOfThreats currentThreat = Score::m_ThreatScore[i].threatKind;
                        const ThreatFinder::Trend currentTrend          = threatLocation.m_Trend;
                        const uint32_t index                            = static_cast<uint32_t>(currentTrend);

                        // Find not empty element of threat.
                        Board::PositionXY xyThreatElement = xy;
                        GetThreatElementPromotion(threatLocation, xyThreatElement,
                                                  GetThreatElementPromotionIndicator[index]);

                        // Mark that the first element was used for this trend.
                        GetThreatElementPromotionIndicator[index] = false;

                        // Ask Spotter to find out what is going on there.
                        const Spotter::RegionToInvestigate regionToInvestigate{ xyThreatElement, currentThreat,
                                                                                currentTrend };
                        m_Spotter.AddToExecute(regionToInvestigate);
                    }

                    // Removing threat.
                    citer = m_ThreatsOnBoard.m_RecognizedThreats[i].erase(citer);
                    --m_ThreatsOnBoard.m_NumberRecognizedThreat[i];

                    // Remove score that's connected with the thread.
                    m_Score -= Score::m_ThreatScore[i].m_Score * threatLocation.m_Multiplier;

                    ++retVal;
                }
                else
                {
                    ++citer;
                }
            }
        }
    }

    return retVal;
}

/// Revert instance to ininial state.
void BoardScore::ResetInstance()
{
    m_Score = 0;
    memset(m_ThreatsOnBoard.m_NumberRecognizedThreat, 0, sizeof(m_ThreatsOnBoard.m_NumberRecognizedThreat));

    for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
    {
        m_ThreatsOnBoard.m_RecognizedThreats[i].clear();
    }

    m_Spotter.ResetInstance();
}

/// Adds a new threat location.
bool BoardScore::AddThreats(const ThreatFinder::ThreatLocation & rTreatLocation, const uint32_t kindOfThreat,
                            const uint32_t multiplier)
{
    bool retVal = false;
    assert(kindOfThreat < Score::MAX_KIND_OF_THREATS);

    if(m_ThreatsOnBoard.m_NumberRecognizedThreat[kindOfThreat] < Score::MAX_TRACKED_THREATS)
    {
        // Get list of threats:
        std::list<ThreatFinder::ThreatLocation> & rThreatList = m_ThreatsOnBoard.m_RecognizedThreats[kindOfThreat];

        // Add the new.
        rThreatList.push_back(rTreatLocation);

        ++m_ThreatsOnBoard.m_NumberRecognizedThreat[kindOfThreat];

        // Update score. See m_ThreatScore for threat-points association.
        // Multiplier (default 1) can be used to boost threat score.
        // Typical situation is while min max tree browsing to favor threat found at the lowest deep search.
        // While game it results that best threat are found first.
        m_Score += Score::m_ThreatScore[kindOfThreat].m_Score * multiplier;

        retVal = true;
    }
#if defined(DEBBUG_MODE)
    if(!retVal)
    {
        std::cout << "No space for new threats!!." << std::endl
    }
#endif
    // assert(retVal);
    return retVal;
}

/// Provide threat list.
const std::list<ThreatFinder::ThreatLocation> & BoardScore::GetThreatList(
    const ThreatFinder::KindOfThreats threatKind) const
{
    const uint32_t index = static_cast<uint32_t>(threatKind);
    return m_ThreatsOnBoard.m_RecognizedThreats[index];
}

/// Check if provided position is part of provided threat.
bool BoardScore::IsPartOfThreat(const ThreatFinder::ThreatLocation & rThreatLocation, const Board::PositionXY xy) const
{
    bool retVal = false;

    if(rThreatLocation.m_Trend == ThreatFinder::HORIZONTAL)
    {
        if((rThreatLocation.m_ThreatDetails.m_BeginningThreat.m_x == xy.m_x) &&
           (xy.m_y >= rThreatLocation.m_ThreatDetails.m_BeginningThreat.m_y) &&
           (xy.m_y <= rThreatLocation.m_ThreatDetails.m_EndThreat.m_y))
        {
            retVal = true;
        }
    }
    else if(rThreatLocation.m_Trend == ThreatFinder::VERTICAL)
    {
        if((rThreatLocation.m_ThreatDetails.m_BeginningThreat.m_y == xy.m_y) &&
           (xy.m_x >= rThreatLocation.m_ThreatDetails.m_BeginningThreat.m_x) &&
           (xy.m_x <= rThreatLocation.m_ThreatDetails.m_EndThreat.m_x))
        {
            retVal = true;
        }
    }
    else if(rThreatLocation.m_Trend == ThreatFinder::RISING)
    {
        // Threat is a line as: y=-x+b
        // Firstly it's needed to compute parameter b.
        // Then check if provided position xy is on the line. Also xy must be
        // in the middle of points constrained by [threatBegin, threatEnd].
        const int32_t b = rThreatLocation.m_ThreatDetails.m_BeginningThreat.m_y +
                          rThreatLocation.m_ThreatDetails.m_BeginningThreat.m_x;
        const bool isOnLine      = ((-xy.m_x + b) == xy.m_y);
        const bool isInTheMiddle = (rThreatLocation.m_ThreatDetails.m_BeginningThreat <= xy) &&
                                   (xy <= rThreatLocation.m_ThreatDetails.m_EndThreat);

        if(isOnLine && isInTheMiddle)
        {
            retVal = true;
        }
    }
    else if(rThreatLocation.m_Trend == ThreatFinder::FALLING)
    {
        // Threat is a line as: y=x+b
        // Firstly it's needed to compute parameter b.
        // Then check if provided position xy is on the line. Also xy must be
        // in the middle of points constrained by [threatBegin, threatEnd].
        const int32_t b = rThreatLocation.m_ThreatDetails.m_BeginningThreat.m_y -
                          rThreatLocation.m_ThreatDetails.m_BeginningThreat.m_x;
        const bool isOnLine      = ((xy.m_x + b) == xy.m_y);
        const bool isInTheMiddle = (rThreatLocation.m_ThreatDetails.m_BeginningThreat <= xy) &&
                                   (xy <= rThreatLocation.m_ThreatDetails.m_EndThreat);

        if(isOnLine && isInTheMiddle)
        {
            retVal = true;
        }
    }
    else
    {
        // threat is corrupted.
        assert(false);
    }

    return retVal;
}

/// In provided threat, search for any, non empty move, belongs to 'player' move.
void BoardScore::GetThreatElementDismissal(const ThreatFinder::ThreatLocation & rThreatLocation,
                                           const Board::Player player,
                                           Board::PositionXY threatElements[MAX_THREAT_PARTS]) const
{
    assert(Board::PLAYER_A == player || Board::PLAYER_B == player);

    // Find out direction toward which we are going to crawl.
    const Board::Direction directionForward  = ThreatFinder::Trend2DirectionStraight.at(rThreatLocation.m_Trend);
    const Board::Direction directionBackward = ThreatFinder::Trend2DirectionReverse.at(rThreatLocation.m_Trend);

    const Board::Player rivalPlayer = (player == Board::PLAYER_A) ? Board::PLAYER_B : Board::PLAYER_A;
    bool isFound                    = false;
    bool threatSeparator            = true;
    Board::PositionXY temp          = XY_OUT_OF_BOARD;

    // Starts searching element from the beginning of threat till end of threat.
    for(temp = rThreatLocation.m_ThreatDetails.m_BeginningThreat; temp < rThreatLocation.m_ThreatDetails.m_EndThreat;)
    {
        const Board::Player pawn = m_pBoard->GetMove(temp);

        if(player == pawn && threatSeparator)
        {
            isFound         = true;
            threatSeparator = false;

            const uint32_t pawnsInRow = m_pBoard->InRow(temp, directionForward);

            // Add to first free cell.
            if(XY_OUT_OF_BOARD == threatElements[0])
            {
                threatElements[0] = temp;
            }
            else if(XY_OUT_OF_BOARD == threatElements[1])
            {
                threatElements[1] = temp;
            }
            else if(XY_OUT_OF_BOARD == threatElements[2])
            {
                threatElements[2] = temp;
            }
            else
            {
                assert(false);
            }

            // May go many steps further.
            m_pBoard->GoDirection(temp, directionForward, pawnsInRow);
        }
        else if(rivalPlayer == pawn)
        {
            // Prevents adding many the same part of threat.
            // Ex1. initial threat:  .x..x.. -> enemy move split it: .x..xo.
            //                                               but only ^     should be add.
            // Ex2. initial threat: .x..x.. -> enemy move split it: .x.ox..
            // two parts shall be added 					         ^  ^   should be add.
            threatSeparator = true;
            m_pBoard->GoDirection(temp, directionForward);
        }
        else
        {
            // Go one step further.
            m_pBoard->GoDirection(temp, directionForward);
        }
    }

    // If assert fail, it would mean such threat could not even be provided here.
    assert(isFound);
}

/// In provided threat, search for any, non empty move, belongs to 'player' move.
void BoardScore::GetThreatElementPromotion(const ThreatFinder::ThreatLocation & rThreatLocation,
                                           Board::PositionXY & threatElement, const bool isTheFist) const
{
    bool isFound = false;

    // Find element that isn't the move that has just been put.
    // isTheFist == true:  xx.x
    //         get first   ^
    //
    // isTheFist == false:  xx.x
    //           get last      ^

    if(isTheFist)
    {
        for(uint32_t i = 0; i < rThreatLocation.m_ThreatDetails.MAX_MY_PAWNS; ++i)
        {
            const bool isElFound = (rThreatLocation.m_ThreatDetails.m_MyPawns[i] != threatElement) &&
                                   (rThreatLocation.m_ThreatDetails.m_MyPawns[i] != XY_OUT_OF_BOARD);
            if(isElFound)
            {
                threatElement = rThreatLocation.m_ThreatDetails.m_MyPawns[i];
                isFound       = true;
                break;
            }
        }
    }
    else
    {
        for(int32_t i = (rThreatLocation.m_ThreatDetails.MAX_MY_PAWNS - 1); i >= 0; --i)
        {
            const bool isElFound = (rThreatLocation.m_ThreatDetails.m_MyPawns[i] != threatElement) &&
                                   (rThreatLocation.m_ThreatDetails.m_MyPawns[i] != XY_OUT_OF_BOARD);
            if(isElFound)
            {
                threatElement = rThreatLocation.m_ThreatDetails.m_MyPawns[i];
                isFound       = true;
                break;
            }
        }
    }

    // If assert fail, it would mean such threat could not even be provided here.
    assert(isFound);
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
