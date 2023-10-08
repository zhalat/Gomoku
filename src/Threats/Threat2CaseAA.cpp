#include "Threat2CaseAA.h"

/// Threat-mask for X player.
const ThreatFinder::ThreatPattern Threat2CaseAA::m_threatPatternX[] = {
    // Finds:
    // .x...x.
    //{ 0x005D0022, 0 },
    { 0x006E0011, 1 }, { 0x00570028, 2 }, { 0x005B0024, 3 }, { 0x005D0022, 4 }, { 0x005E0021, 5 },
    //{ 0x005D0022, 6 },
};

/// Threat-mask for O player.
const ThreatFinder::ThreatPattern Threat2CaseAA::m_threatPatternO[] = {
    // Finds:
    // .o...o.
    //{ 0x005D2200, 0 },
    { 0x006E1100, 1 }, { 0x00572800, 2 }, { 0x005B2400, 3 }, { 0x005D2200, 4 }, { 0x005E2100, 5 },
    //{ 0x005D2200, 6 },
};

/// Keeps number of elements in pattern threat.
const uint32_t Threat2CaseAA::m_threatPatternElements = NUMELEM(m_threatPatternX);

/// Define all points of view. Those are taken from m_threatPattern.
/// For both player is the same.
const uint32_t Threat2CaseAA::m_pov[] = {1, 2, 3, 4, 5 };

Threat2CaseAA::Threat2CaseAA() : ThreatFinder(PATTERN_LENGHT, m_pov, NUMELEM(m_pov), k_ATOM_NUMBER_2AA)
{
    // nothing to do.
}

///	Check pretendThreat if meets all requirement to real threat.
bool Threat2CaseAA::checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                                const Board::Player playerPerspective) const
{
    // Equal the first pointOfview in m_threatPattern
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
        m_threatDownDetails.m_hexCode           = pretendThreat;
        m_threatDownDetails.m_pointOfView       = pointOfView;
        m_threatDownDetails.m_playerPerspective = playerPerspective;
    }

    return retVal;
}

/// Gets threat up details after threat has been found.
void Threat2CaseAA::getThreatUpDetails(const Board::PositionXY initialPosition, const Trend trend,
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
    const uint8_t gapsHexCode        = static_cast<uint8_t>((m_threatDownDetails.m_hexCode & emptyCntrMask) >> 16);
    const uint8_t asterixHexCode     = static_cast<uint8_t>((m_threatDownDetails.m_hexCode & asterixCntrMask) >> 24);
    const uint8_t myPawnsHexCodeNorm = standarizePov(myPawnsHexCode, m_threatDownDetails.m_pointOfView, PATTERN_LENGHT);
    const uint8_t gapsHexCodeNorm    = standarizePov(gapsHexCode, m_threatDownDetails.m_pointOfView, PATTERN_LENGHT);
    const uint8_t asterixHexCodeNorm = standarizePov(asterixHexCode, m_threatDownDetails.m_pointOfView, PATTERN_LENGHT);

    Board::PositionXY initialPositionNorm = initialPosition;
    getGomokuBoard().goDirection(initialPositionNorm, directionBackward, m_threatDownDetails.m_pointOfView);

    // 1. Provide my pawns.
    getPieces(myPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_myPawns[0],
              ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS);

    // 2. Provide gaps.
    //    a. Don't count asterixes as gaps.
    uint8_t gapsHexCodeNormTmp = gapsHexCodeNorm;
    //    b. Get gaps.
    getPieces(gapsHexCodeNormTmp, initialPositionNorm, directionForward, &rThreatUpDetails.m_gaps[0],
              ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES);

    // 3. Provide extended gap.
    rThreatUpDetails.m_extGaps[0] = rThreatUpDetails.m_gaps[2];
    rThreatUpDetails.m_extGaps[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;

    // 4. Provide beginning & end.
    rThreatUpDetails.m_beginningThreat = rThreatUpDetails.m_gaps[0];
    rThreatUpDetails.m_endThreat       = rThreatUpDetails.m_gaps[4];

    // Clear for the next coming.
    m_threatDownDetails.clearAll();
}
