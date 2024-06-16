#include <queue>
#include <ctime>
#include "Interfaces/IBoard.h"
#include "Threats/ThreatFinder.h"

const std::unordered_map<ThreatFinder::Trend, IBoard::Direction> ThreatFinder::Trend2DirectionStraight { { ThreatFinder::VERTICAL, IBoard::DOWN },
                                                                                   { ThreatFinder::HORIZONTAL, IBoard::RIGHT },
                                                                                   { ThreatFinder::RISING, IBoard::DOWN_LEFT },
                                                                                   { ThreatFinder::FALLING, IBoard::DOWN_RIGHT }};

const std::unordered_map<ThreatFinder::Trend, IBoard::Direction> ThreatFinder::Trend2DirectionReverse{ { ThreatFinder::VERTICAL, IBoard::UP },
                                                                                 { ThreatFinder::HORIZONTAL, IBoard::LEFT },
                                                                                 { ThreatFinder::RISING, IBoard::UP_RIGHT },
                                                                                 { ThreatFinder::FALLING, IBoard::UP_LEFT }};

/// Browse neighborhood for threat.
bool ThreatFinder::findThreatPattern(const IBoard::PositionXY & initialPosition, const Trend trend,
                                     const IBoard::Player playerPerspective)
{
    bool retVal = false;

    // IBoard has to be provided first.
    assert(NULL != m_board);

    // Ensure that initial field is on board.
    const bool isOnBoardOk = m_board->isOnBoard(initialPosition);
    assert(isOnBoardOk);

    // Ensure that initialPosition is not empty.
    const bool isGetMoveOk = IBoard::PLAYER_EMPTY != m_board->getMove(initialPosition);
    assert(isGetMoveOk);

    const IBoard::Player opponentPlayer = (IBoard::PLAYER_A == playerPerspective) ? IBoard::PLAYER_B : IBoard::PLAYER_A;

    // Reset previous result.
    m_threatLocation.clearAll();
    prepareSelfForNewSearch();

    // Point of view means which position in the pattern we are.
    // We can consider pattern at its beginning but also in the middle:
    // OX.XXX
    // ^
    // point of view = 0, steps before reversion = 5
    //
    // OX.XXX
    //     ^
    // point of view = 4, steps before reversion = 1
    //
    // Because we don't know which part of threat user has just created,
    // there is necessity go thru all points of view.

    // Go thru all points of view.
    for(uint32_t i = 0; i < m_pointsViewSize; ++i)
    {
        const uint32_t currentPointOfView = m_pointsView[i];

        // Used for jumping thru board.
        IBoard::PositionXY currentPositionOnBoard = initialPosition;
        uint32_t currentThreat                   = 0;

        // Used for keeping how many steps should be done before the opposite direction will take place.
        const uint32_t stepsBeforeReversion = m_patternLenght - currentPointOfView - 1;

        // Points if reversion took place. It is allowed only once.
        bool isReversion = false;

        // Exception counter. There is allowed only once consecutive exception occurrence.
        uint32_t exceptionCntr = 0;

        // If for 100% sure there is no threat.
        bool isHopeless = false;

        for(uint32_t j = 0; j < m_patternLenght; ++j)
        {
            if(0 == exceptionCntr)
            {
                // Get actual pawn (from board).
                const IBoard::Player currentPawn = m_board->getMove(currentPositionOnBoard);

                currentThreat |= (static_cast<uint32_t>(currentPawn) << j);

                // Recognize '*' asterix - an empty place or opponent.
                const bool isEmptyOrRival = (currentPawn != playerPerspective);

                if(isEmptyOrRival)
                {
                    currentThreat |= (static_cast<uint32_t>(IBoard::PLAYER_EMPTY_OR_ENEMY) << j);
                }
            }

            // Find out a next location on board.

            // Check if reversion should take place. Each threat pattern variation might have different
            // number of steps before antithetical direction on trend line should take place.
            if(j == stepsBeforeReversion)
            {
                isReversion            = true;
                currentPositionOnBoard = initialPosition;
            }

            const bool isNewPositionOutOfBoard = !makeStepOnTrend(isReversion, currentPositionOnBoard, trend);

            // Don't check out of board if all pattern particle has just been checked.
            const bool isEnd = ((j + 1) == m_patternLenght);
            if(isNewPositionOutOfBoard && !isEnd)
            {
                // This is an exception thats means move is out of board.
                ++exceptionCntr;

                if(!(exceptionCntr <= k_MAX_ALLOWED_EXCEPTION))
                {
                    isHopeless = true;
                    break;
                }

                // If new position is out of board it general means that pattern was not found.
                // However we can treat board frame as opponent move. So put there just an opponent move and check.
                currentThreat |= (static_cast<uint32_t>(opponentPlayer) << (j + 1));
                currentThreat |= (static_cast<uint32_t>(IBoard::PLAYER_EMPTY_OR_ENEMY) << (j + 1));

                if(isReversion)
                {
                    j++;
                }
            }
            else
            {
                exceptionCntr = 0;
            }
        }

        // Examine the result.
        if(!isHopeless && checkThreat(currentThreat, currentPointOfView, playerPerspective))
        {
            // Indicate that pattern was found.
            m_isThreatPatternFound = true;

            // Get details.
            m_threatLocation.m_threatDetails.m_whos = playerPerspective;
            getThreatUpDetails(initialPosition, trend, m_threatLocation.m_threatDetails);
            m_threatLocation.m_trend = trend;

            retVal = true;

            if(false == isSearchForSimmetrics())
            {
                break;
            }
        }
    }

    return retVal;
}

// Gets begin and end fields of threat.
void ThreatFinder::getThreatFields(ThreatLocation & rThreatLocation) const
{
    // Firstly any threat must be found.
    assert(true == m_isThreatPatternFound);
    rThreatLocation = m_threatLocation;
}

/// Change hexCode as if was being seen from 0 point of view.
uint8_t ThreatFinder::standarizePov(const uint8_t hexCode, const uint8_t pointOfView, const uint8_t length) const
{
    const uint8_t shiftN = length - pointOfView;
    const uint8_t mask   = ((uint8_t)1 << shiftN) - 1;
    uint8_t retVal       = hexCode;
    std::queue<uint8_t> lifo;

    for(uint8_t i = shiftN; i < length; ++i)
    {
        const uint8_t el = ((uint8_t)1 << i) & hexCode;
        lifo.push(el);
    }

    retVal &= mask;

    for(; false == lifo.empty();)
    {
        retVal           = retVal << 1;
        const uint8_t el = lifo.front();
        lifo.pop();

        if(el)
        {
            retVal |= 0x1;
        }
    }

    return retVal;
}

/// Provide (x,y) threat's pieces(x,o,.,*) basing on normalized threat.
void ThreatFinder::getPieces(const uint8_t normHexCode, const IBoard::PositionXY initialPositionNorm,
                             const IBoard::Direction direction, IBoard::PositionXY pBuffer[],
                             const uint32_t bufferSize) const
{
    static const uint8_t mask           = 0x01;
    static const uint8_t maxHexCodeBits = 8;

    uint8_t normHexCodeTmp = normHexCode;
    uint32_t index         = 0;
    for(uint32_t i = 0; i < maxHexCodeBits; ++i)
    {
        const bool isPiece = (normHexCodeTmp & mask);
        if(isPiece)
        {
            assert(index < bufferSize);
            IBoard::PositionXY initialPositionNormTmp = initialPositionNorm;
            getBoard().goDirection(initialPositionNormTmp, direction, i);
            pBuffer[index++] = initialPositionNormTmp;
        }
        normHexCodeTmp = normHexCodeTmp >> 1;
    }
}

/// From currentXYPosition make one step on trend towards up/right/up_right if no reversion or
/// down/left/down_left if reversion should take place. Such a new position override currentXYPosition.
/// If new currentXYPosition would exceed board return false and old position is preserved.
bool ThreatFinder::makeStepOnTrend(const bool isReversion, IBoard::PositionXY & currentXYPosition,
                                   const Trend trend) const
{
    bool retVal = false;
    assert(NULL != m_board);

    // Find out direction toward which we are going to crawl.
    const IBoard::Direction directionForward  = Trend2DirectionStraight.at(trend);
    const IBoard::Direction directionBackward = Trend2DirectionReverse.at(trend);
    IBoard::Direction direction = IBoard::DIRECTION_NONE;
    if(!isReversion)
    {
        direction = directionForward;
    }
    else
    {
        direction = directionBackward;
    }

    if(m_board->canIGo(currentXYPosition, direction))
    {
        m_board->goDirection(currentXYPosition, direction);
        retVal = true;
    }
    else
    {
        retVal = false;
    }

    return retVal;
}
