#include "Threat4CaseC.h"

/// Threat-mask for X player.
const ThreatFinder::ThreatPattern Threat4CaseC::m_threatPatternX[] = {
    // Finds:
    // O.XXXXO
    // OX.XXXO
    // OXX.XXO
    // OXXX.XO
    // OXXXX.O
    //{ 0x00004100, 0 },
    { 0x00006000, 1 }, { 0x00005000, 2 }, { 0x00004800, 3 }, { 0x00004400, 4 }, { 0x00004200, 5 },
    //{ 0x00004100, 6 },
};

/// Threat-mask for O player.
const ThreatFinder::ThreatPattern Threat4CaseC::m_threatPatternO[] = {
    // Finds:
    // X.OOOOX
    // XO.OOOX
    // XOO.OOX
    // XOOO.OX
    // XOOOO.X
    //{ 0x00000041, 0 },
    { 0x00000060, 1 }, { 0x00000050, 2 }, { 0x00000048, 3 }, { 0x00000044, 4 }, { 0x00000042, 5 },
    //{ 0x00000041, 6 },
};

/// Keeps number of elements in pattern threat.
const uint32_t Threat4CaseC::m_threatPatternElements = NUMELEM(m_threatPatternX);

/// Define all points of view. Those are taken from m_threatPattern.
/// For both player is the same.
const uint32_t Threat4CaseC::m_pov[] = {1, 2, 3, 4, 5 };

Threat4CaseC::Threat4CaseC() : ThreatFinder(PATTERN_LENGHT, m_pov, NUMELEM(m_pov), k_ATOM_NUMBER_4C)
{
    // nothing to do.
}

///	Check pretendThreat if meets all requirement to real threat.
bool Threat4CaseC::checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                               const Board::Player playerPerspective) const
{
    // Equal the first pointOfview in m_threatPattern
    static const uint32_t pointOfViewOffset = 1;
    const uint32_t threatPatternIndex       = pointOfView - pointOfViewOffset;

    static const uint32_t myExpectedPawnInRow = 4;
    static const uint32_t expectedGaps        = 1;
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
        threatPattern          = m_threatPatternX[threatPatternIndex].m_threatPattern;
    }
    else if(Board::PLAYER_B == playerPerspective)
    {
        myPawnsCntrMask        = 0x0000FF00;
        adversaryPawnsCntrMask = 0x000000FF;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        threatPattern          = m_threatPatternO[threatPatternIndex].m_threatPattern;
    }
    else
    {
        assert(false);
    }

    // 1. Check my pawns.
    const uint32_t myPawnsCntr = __builtin_popcount(pretendThreat & myPawnsCntrMask);
    const bool isMyCntrMatch   = (myPawnsCntr == myExpectedPawnInRow);

    // 2. Check enemy pawns.
    const bool isEnemyPawnsMatch =
        ((pretendThreat & adversaryPawnsCntrMask) == (threatPattern & adversaryPawnsCntrMask));

    // 3. Check empty space.
    const uint32_t emptySpaceCntr    = __builtin_popcount(pretendThreat & emptyCntrMask);
    const bool isEmptySpaceCntrMatch = (emptySpaceCntr == expectedGaps);

    // 4. Check asterix.
    // n.a

    const bool retVal = (isMyCntrMatch && isEnemyPawnsMatch && isEmptySpaceCntrMatch);

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
void Threat4CaseC::getThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
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
    const uint8_t enemyPawnsHexCode =
        static_cast<uint8_t>((m_threatDownDetails.m_hexCode & adversaryPawnsCntrMask) >> enemyPawnsShift);
    const uint8_t gapsHexCode        = static_cast<uint8_t>((m_threatDownDetails.m_hexCode & emptyCntrMask) >> 16);
    const uint8_t myPawnsHexCodeNorm = standarizePov(myPawnsHexCode, m_threatDownDetails.m_pointOfView, PATTERN_LENGHT);
    const uint8_t enemyPawnsHexCodeNorm =
            standarizePov(enemyPawnsHexCode, m_threatDownDetails.m_pointOfView, PATTERN_LENGHT);
    const uint8_t gapsHexCodeNorm = standarizePov(gapsHexCode, m_threatDownDetails.m_pointOfView, PATTERN_LENGHT);

    Board::PositionXY initialPositionNorm = initialPosition;
    getGomokuBoard().goDirection(initialPositionNorm, directionBackward, m_threatDownDetails.m_pointOfView);

    // 1. Provide my pawns.
    getPieces(myPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_myPawns[0],
              ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS);

    // 2. Provide enemy pawns.
    getPieces(enemyPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_enemyPawns[0],
              ThreatFinder::ThreatUpDetails::k_MAX_ENEMY_PAWNS);
    // a. make adjustment for a case ex. |.xxx.o   o.xxx.|
    const bool isEnemyPawnOnBoard1 = getGomokuBoard().isOnBoard(rThreatUpDetails.m_enemyPawns[0]);
    const bool isEnemyPawnOnBoard2 = getGomokuBoard().isOnBoard(rThreatUpDetails.m_enemyPawns[1]);
    Board::PositionXY beginTmp     = rThreatUpDetails.m_enemyPawns[0];
    Board::PositionXY endTmp       = rThreatUpDetails.m_enemyPawns[1];
    if(!isEnemyPawnOnBoard1 && !isEnemyPawnOnBoard2)
    {
        getGomokuBoard().goDirection(rThreatUpDetails.m_enemyPawns[0], directionForward);
        getGomokuBoard().goDirection(rThreatUpDetails.m_enemyPawns[1], directionBackward);
        beginTmp = rThreatUpDetails.m_enemyPawns[0];
        endTmp   = rThreatUpDetails.m_enemyPawns[1];

        rThreatUpDetails.m_enemyPawns[0] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
        rThreatUpDetails.m_enemyPawns[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else if(isEnemyPawnOnBoard1 && !isEnemyPawnOnBoard2)
    {
        getGomokuBoard().goDirection(rThreatUpDetails.m_enemyPawns[1], directionBackward);
        endTmp = rThreatUpDetails.m_enemyPawns[1];

        rThreatUpDetails.m_enemyPawns[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else if(!isEnemyPawnOnBoard1 && isEnemyPawnOnBoard2)
    {
        getGomokuBoard().goDirection(rThreatUpDetails.m_enemyPawns[0], directionForward);
        beginTmp                         = rThreatUpDetails.m_enemyPawns[0];
        rThreatUpDetails.m_enemyPawns[0] = rThreatUpDetails.m_enemyPawns[1];
        rThreatUpDetails.m_enemyPawns[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else
    {
        // nothing to do
    }

    // 3. Provide gaps.
    getPieces(gapsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_gaps[0],
              ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES);

    // 4. Provide extended gaps.
    // none

    // 5. Set begin and end.
    rThreatUpDetails.m_beginningThreat = beginTmp;
    rThreatUpDetails.m_endThreat       = endTmp;

    // Clear for the next coming.
    m_threatDownDetails.clearAll();
}
