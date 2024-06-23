#include <assert.h>
#include <algorithm>
#include "ThreatTracker.h"
#include "Threats/ThreatsBloodRelation.h"
#include "DataContainers/VectorUnique.h"

static constexpr IBoard::PositionXY k_XY_OUT_OF_BOARD = IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD);

/// Gets number of recognized the provided kind of threat.
uint32_t ThreatTracker::getNumberOf(ThreatFinder::KindOfThreats threatKind) const
{
    const uint32_t index = static_cast<uint32_t>(threatKind);
    const uint32_t retVal = m_threatsOnBoard.m_numberOfThreats[index];
    return retVal;
}

/// Gets gaps belonging to provided kind of threat(extended included). Repetitive included.
void ThreatTracker::getGapsNonUnique(std::vector<IBoard::PositionXY> & gaps,
                                     const ThreatFinder::KindOfThreats threatKind) const
{
    const uint32_t threatIndex = static_cast<uint32_t>(threatKind);

    std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
        m_threatsOnBoard.m_recognizedThreats[threatIndex].begin();

    for(; citer != m_threatsOnBoard.m_recognizedThreats[threatIndex].end(); ++citer)
    {
        const ThreatFinder::ThreatLocation & threatLocation = *citer;

        // Symmetric threats (like 2A, 3A) might have duplicated gaps. One from normal side and second symmetric side.
        // Prevent adding the same gaps from the same threat.
        VectorUnique<uint32_t, GomokuBoard::k_MAX_GOMOKU_BOARD_SQARE_SIZE> addedGaps;

        // Go thru each threats' gaps.
        for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES; ++i)
        {
            const IBoard::PositionXY pretendGapXY = threatLocation.m_threatDetails.m_gaps[i];

            if(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD != pretendGapXY)
            {
                const bool isGapOK = !addedGaps.isPresent(pretendGapXY.convert2Linear(m_board->getSize()));

                if(isGapOK)
                {
                    gaps.push_back(pretendGapXY);
                    addedGaps.insert(pretendGapXY.convert2Linear(m_board->getSize()));
                }
            }
        }
    }
}

/// Gets gaps belonging to provided kind of threat(extended included). Repetitive doesn't included.
void ThreatTracker::getGapsUnique(std::vector<IBoard::PositionXY> & gaps,
                                  const ThreatFinder::KindOfThreats threatKind) const
{
    const uint32_t threatIndex = static_cast<uint32_t>(threatKind);

    std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
        m_threatsOnBoard.m_recognizedThreats[threatIndex].begin();

    VectorUnique<uint32_t, GomokuBoard::k_MAX_GOMOKU_BOARD_SQARE_SIZE> addedGaps;

    for(; citer != m_threatsOnBoard.m_recognizedThreats[threatIndex].end(); ++citer)
    {
        const ThreatFinder::ThreatLocation & rThreatLocation = *citer;

        // Go thru each threats' gaps.
        for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES; ++i)
        {
            const IBoard::PositionXY pretendGapXY = rThreatLocation.m_threatDetails.m_gaps[i];

            // Gap must be unique.
            const bool isGapOK =
                (pretendGapXY != ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD) && (!addedGaps.isPresent(pretendGapXY.convert2Linear(m_board->getSize())));

            if(isGapOK)
            {
                gaps.push_back(pretendGapXY);
                addedGaps.insert(pretendGapXY.convert2Linear(m_board->getSize()));
            }
        }
    }
}

/// Gets gaps that are common to more than one threat (extended included).
void ThreatTracker::getGapsDuplicated(std::vector<IBoard::PositionXY> & gaps,
                                      const ThreatFinder::KindOfThreats threatKind) const
{
    std::vector<IBoard::PositionXY> nonUniqueGaps;
    getGapsNonUnique(nonUniqueGaps, threatKind);

    // Left only duplications.
    VectorUnique<uint32_t, GomokuBoard::k_MAX_GOMOKU_BOARD_SQARE_SIZE> firstGate;
    VectorUnique<uint32_t, GomokuBoard::k_MAX_GOMOKU_BOARD_SQARE_SIZE> secondtGate;
    for(std::vector<IBoard::PositionXY>::const_iterator citer = nonUniqueGaps.begin(); citer < nonUniqueGaps.end();
        ++citer)
    {
        bool isFirstGateOK = firstGate.isPresent(citer->convert2Linear(m_board->getSize()));

        if(isFirstGateOK)
        {
            // But avoid to add duplication twice. Once is enough.
            bool isSecondGateOK = !secondtGate.isPresent(citer->convert2Linear(m_board->getSize()));

            if(isSecondGateOK)
            {
                gaps.push_back(*citer);
                secondtGate.insert(citer->convert2Linear(m_board->getSize()));
            }
        }
        else
        {
            firstGate.insert(citer->convert2Linear(m_board->getSize()));
        }
    }
}

/// Gets all extend gaps belongs to provided threat.
///// Extended gap occurs for threat which has more than one gap in a row.
///// Exemplary: .XXX.. / .XX... / OXXX..
/////                 ^       ^         ^
/////                 ^^^^^^'GapExt'^^^^^
void ThreatTracker::getExGaps(std::vector<IBoard::PositionXY> & exGaps,
                              const ThreatFinder::KindOfThreats threatKind) const
{
    const uint32_t threatIndex = static_cast<uint32_t>(threatKind);

    std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
        m_threatsOnBoard.m_recognizedThreats[threatIndex].begin();

    for(; citer != m_threatsOnBoard.m_recognizedThreats[threatIndex].end(); ++citer)
    {
        const ThreatFinder::ThreatLocation & threatLocation = *citer;

        const IBoard::PositionXY xy1 = threatLocation.m_threatDetails.m_extGaps[0];
        const IBoard::PositionXY xy2 = threatLocation.m_threatDetails.m_extGaps[1];

        if(k_XY_OUT_OF_BOARD != xy1)
        {
            exGaps.push_back(xy1);
        }

        if(k_XY_OUT_OF_BOARD != xy2)
        {
            exGaps.push_back(xy2);
        }
    }
}

/// Get number of fields that both threats kind have in common.
uint32_t ThreatTracker::getCommonFieldNumber(const ThreatFinder::KindOfThreats threatKindA,
                                             const ThreatFinder::KindOfThreats threatKindB) const
{
    uint32_t retVal = 0;

    if(threatKindA == threatKindB)
    {
        VectorUnique<uint32_t , GomokuBoard::k_MAX_GOMOKU_BOARD_SQARE_SIZE> tmp;

        const uint32_t threatIndex = static_cast<uint32_t>(threatKindA);
        std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
            m_threatsOnBoard.m_recognizedThreats[threatIndex].begin();

        for(; citer != m_threatsOnBoard.m_recognizedThreats[threatIndex].end(); ++citer)
        {
            const ThreatFinder::ThreatLocation & rThreatLocation = *citer;

            for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS; ++i)
            {
                const IBoard::PositionXY xy = rThreatLocation.m_threatDetails.m_myPawns[i];
                if(k_XY_OUT_OF_BOARD == xy)
                {
                    break;
                }

                const uint32_t positionField(xy.convert2Linear(m_board->getSize()));

                if(!tmp.isPresent(positionField))
                {
                    tmp.insert(positionField);
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
        std::list<uint32_t> tmp[GomokuBoard::k_MAX_GOMOKU_BOARD_SQARE_SIZE];

        const uint32_t threatIndexB = static_cast<uint32_t>(threatKindB);
        std::list<ThreatFinder::ThreatLocation>::const_iterator citerB =
            m_threatsOnBoard.m_recognizedThreats[threatIndexB].begin();

        // 1. Put each elements of threat B to vector list.
        for(; citerB != m_threatsOnBoard.m_recognizedThreats[threatIndexB].end(); ++citerB)
        {
            const ThreatFinder::ThreatLocation & rThreatLocation = *citerB;

            // Go thru each threat's element.
            for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS; ++i)
            {
                const IBoard::PositionXY xy = rThreatLocation.m_threatDetails.m_myPawns[i];
                if(k_XY_OUT_OF_BOARD == xy)
                {
                    break;
                }

                const uint32_t positionField(xy.convert2Linear(m_board->getSize()));
                const uint32_t index = static_cast<uint32_t>(positionField);
                tmp[index].push_back(positionField);
            }
        }

        const uint32_t threatIndexA = static_cast<uint32_t>(threatKindA);
        std::list<ThreatFinder::ThreatLocation>::const_iterator citerA =
            m_threatsOnBoard.m_recognizedThreats[threatIndexA].begin();

        // 2. Go thru each threats
        for(; citerA != m_threatsOnBoard.m_recognizedThreats[threatIndexA].end(); ++citerA)
        {
            const ThreatFinder::ThreatLocation & rThreatLocation = *citerA;

            // Go thru each threat's element and check how many threat threatKindB has in common.
            for(uint32_t i = 0; i < ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS; ++i)
            {
                const IBoard::PositionXY xy = rThreatLocation.m_threatDetails.m_myPawns[i];
                if(k_XY_OUT_OF_BOARD == xy)
                {
                    break;
                }

                const uint32_t positionField(xy.convert2Linear(m_board->getSize()));
                const uint32_t index = static_cast<uint32_t>(positionField);

                retVal += tmp[index].size();
            }
        }
    }

    return retVal;
}

/// From provided threat list remove such that include xy position.
uint32_t ThreatTracker::removeThreats(const IBoard::PositionXY xy)
{
    uint32_t retVal = 0;

    // Check if xy move is an enemy's move. If so it means:
    // -some special care must be taken when enemy's move is a part of my threat.
    //  The move could reduce my threat or just only mitigate
    // -if the enemy move doesn't touch my existing threats, no need to find a new threats or
    /// repudiate the previous.
    const bool isEnemyMove = ((m_board->getMove(xy) != m_player) && (m_board->getMove(xy) != IBoard::PLAYER_EMPTY));

    for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
    {
        // If there are no threats, its meaningless to check all cells.
        if(m_threatsOnBoard.m_numberOfThreats[i] > 0)
        {
            std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
                m_threatsOnBoard.m_recognizedThreats[i].begin();

            // Indicates which part of threat (first / last) getThreatElementPromotion shall take.
            // Indexes are associate with Trend enum VERTICAL= 0 etc. True means first
            bool GetThreatElementPromotionIndicator[4] = { true, true, true, true };

            for(; citer != m_threatsOnBoard.m_recognizedThreats[i].end();)
            {
                // Check if provided xy is part of this threat.
                ThreatFinder::ThreatLocation threatLocation = *citer;
                const bool isThreatPart                   = isPartOfThreat(threatLocation, xy);

                if(isThreatPart)
                {
                    if(isEnemyMove)  // There's necessity to run 'Dismissal' threat group.
                    {
                        // Get info required for reupadate threat. Must be able to keep up to 3 parts like: xxoxx or
                        // (rare situation) x.x..x.
                        IBoard::PositionXY threatElements[k_MAX_THREAT_PARTS] = {k_XY_OUT_OF_BOARD, k_XY_OUT_OF_BOARD,
                                                                                k_XY_OUT_OF_BOARD };

                        getThreatElementDismissal(threatLocation, m_player, &threatElements[0]);
                        const ThreatFinder::KindOfThreats currentThreat = Score::m_ThreatScore[i].threatKind;
                        const ThreatFinder::Trend currentTrend          = threatLocation.m_trend;

                        // Add to spotter not empty threat' part element.
                        for(uint32_t i = 0; i < k_MAX_THREAT_PARTS; ++i)
                        {
                            const IBoard::PositionXY xyThreatElement = threatElements[i];

                            if(k_XY_OUT_OF_BOARD != xyThreatElement)
                            {
                                // Ask Spotter to find out what is going on there.
                                const ISpotter::RegionToInvestigate regionToInvestigate{ xyThreatElement, currentThreat,
                                                                                        currentTrend };
                                m_spotter.addToExecute(regionToInvestigate);
                            }
                        }
                    }
                    else  // There's necessity to run 'Promotion' threat group.
                    {
                        const ThreatFinder::KindOfThreats currentThreat = Score::m_ThreatScore[i].threatKind;
                        const ThreatFinder::Trend currentTrend          = threatLocation.m_trend;
                        const uint32_t index                            = static_cast<uint32_t>(currentTrend);

                        // Find not empty element of threat.
                        IBoard::PositionXY xyThreatElement = xy;
                        getThreatElementPromotion(threatLocation, xyThreatElement,
                                                  GetThreatElementPromotionIndicator[index]);

                        // Mark that the first element was used for this trend.
                        GetThreatElementPromotionIndicator[index] = false;

                        // Ask Spotter to find out what is going on there.
                        const ISpotter::RegionToInvestigate regionToInvestigate{ xyThreatElement, currentThreat,
                                                                                currentTrend };
                        m_spotter.addToExecute(regionToInvestigate);
                    }

                    // Removing threat.
                    citer = m_threatsOnBoard.m_recognizedThreats[i].erase(citer);
                    --m_threatsOnBoard.m_numberOfThreats[i];

                    // Remove score that's connected with the thread.
                    m_score -= Score::m_ThreatScore[i].m_Score * threatLocation.m_multiplier;

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

/// Adds a new threat location.
bool ThreatTracker::addThreats(const ThreatFinder::ThreatLocation & treatLocation, const uint32_t kindOfThreat,
                               const uint32_t multiplier)
{
    bool retVal = false;
    assert(kindOfThreat < Score::MAX_KIND_OF_THREATS);

    if(m_threatsOnBoard.m_numberOfThreats[kindOfThreat] < Score::MAX_TRACKED_THREATS)
    {
        // Get list of threats:
        std::list<ThreatFinder::ThreatLocation> & threatList = m_threatsOnBoard.m_recognizedThreats[kindOfThreat];

        // Add the new.
        threatList.push_back(treatLocation);

        ++m_threatsOnBoard.m_numberOfThreats[kindOfThreat];

        // Update score. See m_ThreatScore for threat-points association.
        // Multiplier (default 1) can be used to boost threat score.
        // Typical situation is while min max tree browsing to favor threat found at the lowest deep search.
        // While game it results that best threat are found first.
        m_score += Score::m_ThreatScore[kindOfThreat].m_Score * multiplier;

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

/// Keep updating for new movies
void ThreatTracker::updateScore(const IBoard::PositionXY xy, bool isEnemy, const uint32_t multiplier)
{
    this->removeThreats(xy);

    const auto newSpottetThreats = m_spotter.execute(xy,isEnemy,multiplier);
    for(auto& el : newSpottetThreats)
    {
        this->addThreats(el.m_location,el.m_threatKind, multiplier);
    }

    storeMemento();
}

/// Provide threat list.
const std::list<ThreatFinder::ThreatLocation> & ThreatTracker::getThreatList(
    const ThreatFinder::KindOfThreats threatKind) const
{
    const uint32_t index = static_cast<uint32_t>(threatKind);
    return m_threatsOnBoard.m_recognizedThreats[index];
}

void ThreatTracker::mementoEnable()
{
    if(m_isMementoEnabled)
        return;

    //put current state at the very bottom
    m_isMementoEnabled=true;
    storeMemento();
}

/// Revert instance to ininial state.
void ThreatTracker::resetInstance()
{
    m_score = 0;
    memset(m_threatsOnBoard.m_numberOfThreats, 0, sizeof(m_threatsOnBoard.m_numberOfThreats));

    for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
    {
        m_threatsOnBoard.m_recognizedThreats[i].clear();
    }

    m_spotter.resetInstance();
    m_memento.clearAll();
    m_hashCntr=0;
}

/// Check if provided position is part of provided threat.
bool ThreatTracker::isPartOfThreat(const ThreatFinder::ThreatLocation & rThreatLocation, const IBoard::PositionXY xy) const
{
    bool retVal = false;

    if(rThreatLocation.m_trend == ThreatFinder::HORIZONTAL)
    {
        if((rThreatLocation.m_threatDetails.m_beginningThreat.m_x == xy.m_x) &&
           (xy.m_y >= rThreatLocation.m_threatDetails.m_beginningThreat.m_y) &&
           (xy.m_y <= rThreatLocation.m_threatDetails.m_endThreat.m_y))
        {
            retVal = true;
        }
    }
    else if(rThreatLocation.m_trend == ThreatFinder::VERTICAL)
    {
        if((rThreatLocation.m_threatDetails.m_beginningThreat.m_y == xy.m_y) &&
           (xy.m_x >= rThreatLocation.m_threatDetails.m_beginningThreat.m_x) &&
           (xy.m_x <= rThreatLocation.m_threatDetails.m_endThreat.m_x))
        {
            retVal = true;
        }
    }
    else if(rThreatLocation.m_trend == ThreatFinder::RISING)
    {
        // Threat is a line as: y=-x+b
        // Firstly it's needed to compute parameter b.
        // Then check if provided position xy is on the line. Also xy must be
        // in the middle of points constrained by [threatBegin, threatEnd].
        const int32_t b = rThreatLocation.m_threatDetails.m_beginningThreat.m_y +
                          rThreatLocation.m_threatDetails.m_beginningThreat.m_x;
        const bool isOnLine      = ((-xy.m_x + b) == xy.m_y);
        const bool isInTheMiddle = (rThreatLocation.m_threatDetails.m_beginningThreat <= xy) &&
                                   (xy <= rThreatLocation.m_threatDetails.m_endThreat);

        if(isOnLine && isInTheMiddle)
        {
            retVal = true;
        }
    }
    else if(rThreatLocation.m_trend == ThreatFinder::FALLING)
    {
        // Threat is a line as: y=x+b
        // Firstly it's needed to compute parameter b.
        // Then check if provided position xy is on the line. Also xy must be
        // in the middle of points constrained by [threatBegin, threatEnd].
        const int32_t b = rThreatLocation.m_threatDetails.m_beginningThreat.m_y -
                          rThreatLocation.m_threatDetails.m_beginningThreat.m_x;
        const bool isOnLine      = ((xy.m_x + b) == xy.m_y);
        const bool isInTheMiddle = (rThreatLocation.m_threatDetails.m_beginningThreat <= xy) &&
                                   (xy <= rThreatLocation.m_threatDetails.m_endThreat);

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
void ThreatTracker::getThreatElementDismissal(const ThreatFinder::ThreatLocation & threatLocation,
                                              const IBoard::Player player,
                                              IBoard::PositionXY threatElements[k_MAX_THREAT_PARTS]) const
{
    assert(IBoard::PLAYER_A == player || IBoard::PLAYER_B == player);

    // Find out direction toward which we are going to crawl.
    const IBoard::Direction directionForward  = ThreatFinder::Trend2DirectionStraight.at(threatLocation.m_trend);
    const IBoard::Direction directionBackward = ThreatFinder::Trend2DirectionReverse.at(threatLocation.m_trend);

    const IBoard::Player rivalPlayer = (player == IBoard::PLAYER_A) ? IBoard::PLAYER_B : IBoard::PLAYER_A;
    bool isFound                    = false;
    bool threatSeparator            = true;
    IBoard::PositionXY temp          = k_XY_OUT_OF_BOARD;

    // Starts searching element from the beginning of threat till end of threat.
    for(temp = threatLocation.m_threatDetails.m_beginningThreat; temp < threatLocation.m_threatDetails.m_endThreat;)
    {
        const IBoard::Player pawn = m_board->getMove(temp);

        if(player == pawn && threatSeparator)
        {
            isFound         = true;
            threatSeparator = false;

            const uint32_t pawnsInRow = m_board->inRow(temp, directionForward);

            // Add to first free cell.
            if(k_XY_OUT_OF_BOARD == threatElements[0])
            {
                threatElements[0] = temp;
            }
            else if(k_XY_OUT_OF_BOARD == threatElements[1])
            {
                threatElements[1] = temp;
            }
            else if(k_XY_OUT_OF_BOARD == threatElements[2])
            {
                threatElements[2] = temp;
            }
            else
            {
                assert(false);
            }

            // May go many steps further.
            m_board->goDirection(temp, directionForward, pawnsInRow);
        }
        else if(rivalPlayer == pawn)
        {
            // Prevents adding many the same part of threat.
            // Ex1. initial threat:  .x..x.. -> enemy move split it: .x..xo.
            //                                               but only ^     should be add.
            // Ex2. initial threat: .x..x.. -> enemy move split it: .x.ox..
            // two parts shall be added 					         ^  ^   should be add.
            threatSeparator = true;
            m_board->goDirection(temp, directionForward);
        }
        else
        {
            // Go one step further.
            m_board->goDirection(temp, directionForward);
        }
    }

    // If assert fail, it would mean such threat could not even be provided here.
    assert(isFound);
}

/// In provided threat, search for any, non empty move, belongs to 'player' move.
void ThreatTracker::getThreatElementPromotion(const ThreatFinder::ThreatLocation & rThreatLocation,
                                              IBoard::PositionXY & threatElement, const bool isTheFist) const
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
        for(uint32_t i = 0; i < rThreatLocation.m_threatDetails.k_MAX_MY_PAWNS; ++i)
        {
            const bool isElFound = (rThreatLocation.m_threatDetails.m_myPawns[i] != threatElement) &&
                                   (rThreatLocation.m_threatDetails.m_myPawns[i] != k_XY_OUT_OF_BOARD);
            if(isElFound)
            {
                threatElement = rThreatLocation.m_threatDetails.m_myPawns[i];
                isFound       = true;
                break;
            }
        }
    }
    else
    {
        for(int32_t i = (rThreatLocation.m_threatDetails.k_MAX_MY_PAWNS - 1); i >= 0; --i)
        {
            const bool isElFound = (rThreatLocation.m_threatDetails.m_myPawns[i] != threatElement) &&
                                   (rThreatLocation.m_threatDetails.m_myPawns[i] != k_XY_OUT_OF_BOARD);
            if(isElFound)
            {
                threatElement = rThreatLocation.m_threatDetails.m_myPawns[i];
                isFound       = true;
                break;
            }
        }
    }

    // If assert fail, it would mean such threat could not even be provided here.
    assert(isFound);
}

void ThreatTracker::storeMemento()
{
    if(m_isMementoEnabled)
    {
        Memento data{m_threatsOnBoard, m_score, ++m_hashCntr};
        m_memento.pushData(data);
    }
}

bool ThreatTracker::mementoRevert(uint32_t n)
{
    if(m_memento.empty() or 0==n)
        return false;

    if(m_memento.getSize()<n)
        return false;

    for(int i = 0; i<n; ++i)
    {
        m_memento.popData();
    }
    const Memento newState = m_memento.topData();
    this->m_threatsOnBoard = newState.m_threatsOnBoard;
    this->m_score = newState.m_score;

    //always keep the very first state
    if(m_memento.empty())
    {
        m_memento.pushData(newState);
    }
    return true;
}