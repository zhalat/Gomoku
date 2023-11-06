#include "ThreatWinner.h"

const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> ThreatWinner::k_ATOM_NUMBER_WINNER= {
        { ThreatFinder::MY_PAWN, 2 },
        { ThreatFinder::ENEMY_PAWN, 0 },
        { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
        { ThreatFinder::ASTERIX, -1 }  // it depends.
};

/// Threat-mask for X player.
const ThreatFinder::ThreatPattern ThreatWinner::m_threatPatternX[] = {
    // Finds:
    // *XXXXX*
    //{ 0x41000000, 0 },
    { 0x60000000, 1 }, { 0x50000000, 2 }, { 0x48000000, 3 }, { 0x44000000, 4 }, { 0x42000000, 5 },
    //{ 0x41000000, 6 }
};

/// Threat-mask for O player.
const ThreatFinder::ThreatPattern ThreatWinner::m_threatPatternO[] = {
    // Finds:
    // *OOOOO*
    //{ 0x41000000, 0 },
    { 0x60000000, 1 }, { 0x50000000, 2 }, { 0x48000000, 3 }, { 0x44000000, 4 }, { 0x42000000, 5 },
    //{ 0x41000000, 6 }
};

const uint32_t ThreatWinner::m_threatPatternElements = NUMELEM(m_threatPatternX);

/// Define all points of view because not all point of view must be checked. See m_threatPattern
/// For both players are the same.
const uint32_t ThreatWinner::m_pov[] = {1, 2, 3, 4, 5 };

ThreatWinner::ThreatWinner() : ThreatFinder(PATTERN_LENGHT, m_pov, NUMELEM(m_pov), k_ATOM_NUMBER_WINNER)
{

}

///	Check pretendThreat if meets all requirement to real threat.
bool ThreatWinner::checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                               const Board::Player playerPerspective) const
{
    // Equal the first pointOfview in m_threatPattern
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
        threatPattern     = m_threatPatternX[threatPatternIndex].m_threatPattern;
    }
    else if(Board::PLAYER_B == playerPerspective)
    {
        myPawnsCntrMask   = 0x0000FF00;
        adversaryCntrMask = 0x000000FF;
        emptyCntrMask     = 0x00FF0000;
        asterixCntrMask   = 0xFF000000;
        threatPattern     = m_threatPatternO[threatPatternIndex].m_threatPattern;
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
        m_threatDownDetails.m_hexCode           = pretendThreat;
        m_threatDownDetails.m_pointOfView       = pointOfView;
        m_threatDownDetails.m_playerPerspective = playerPerspective;
    }

    return retVal;
}

/// Gets threat up details after threat has been found.
void ThreatWinner::getThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
                                      ThreatUpDetails & rThreatUpDetails) const
{
    const uint32_t stepForward      = PATTERN_LENGHT - m_threatDownDetails.m_pointOfView - 1;
    const uint32_t stepBackward     = m_threatDownDetails.m_pointOfView;
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

    if(Board::PLAYER_A == m_threatDownDetails.m_playerPerspective)
    {
        myPawnsCntrMask        = 0x000000FF;
        adversaryPawnsCntrMask = 0x0000FF00;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        myPawnsShift           = 0;
        enemyPawnsShift        = 8;
    }
    else if(Board::PLAYER_B == m_threatDownDetails.m_playerPerspective)
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
        static_cast<uint8_t>((m_threatDownDetails.m_hexCode & myPawnsCntrMask) >> myPawnsShift);
    const uint8_t myPawnsHexCodeNorm = standarizePov(myPawnsHexCode, m_threatDownDetails.m_pointOfView, PATTERN_LENGHT);

    Board::PositionXY initialPositionNorm = initialPosition;
    getBoard().goDirection(initialPositionNorm, directionBackward, m_threatDownDetails.m_pointOfView);

    // 1. Provide my pawns.
    getPieces(myPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_myPawns[0],
              ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS);

    // 2. Provide asterixes.
    Board::PositionXY asterix1Tmp = rThreatUpDetails.m_myPawns[0];
    Board::PositionXY asterix2Tmp = rThreatUpDetails.m_myPawns[4];
    getBoard().goDirection(asterix1Tmp, directionBackward);
    getBoard().goDirection(asterix2Tmp, directionForward);
    const bool isAsterix1TmpOnBoard = getBoard().isOnBoard(asterix1Tmp);
    const bool isAsterix2TmpOnBoard = getBoard().isOnBoard(asterix2Tmp);

    Board::PositionXY beginTmp;
    Board::PositionXY endTmp;

    if(isAsterix1TmpOnBoard && isAsterix2TmpOnBoard)
    {
        beginTmp                        = asterix1Tmp;
        endTmp                          = asterix2Tmp;
        rThreatUpDetails.m_asterixes[0] = asterix1Tmp;
        rThreatUpDetails.m_asterixes[1] = asterix2Tmp;
    }
    else if(!isAsterix1TmpOnBoard && isAsterix2TmpOnBoard)
    {
        beginTmp                        = rThreatUpDetails.m_myPawns[0];
        endTmp                          = asterix2Tmp;
        rThreatUpDetails.m_asterixes[0] = asterix2Tmp;
        rThreatUpDetails.m_asterixes[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else if(isAsterix1TmpOnBoard && !isAsterix2TmpOnBoard)
    {
        beginTmp                        = asterix1Tmp;
        endTmp                          = rThreatUpDetails.m_myPawns[4];
        rThreatUpDetails.m_asterixes[0] = asterix1Tmp;
        rThreatUpDetails.m_asterixes[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else if(!isAsterix1TmpOnBoard && !isAsterix2TmpOnBoard)
    {
        beginTmp                        = rThreatUpDetails.m_myPawns[0];
        endTmp                          = rThreatUpDetails.m_myPawns[4];
        rThreatUpDetails.m_asterixes[0] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
        rThreatUpDetails.m_asterixes[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else
    {
        // nothing to do.
    }

    // 3. Provide extended gaps.
    // none

    // 4. Set begin and end.
    rThreatUpDetails.m_beginningThreat = beginTmp;
    rThreatUpDetails.m_endThreat       = endTmp;

    // Clear for the next coming.
    m_threatDownDetails.clearAll();
}
