#include "Threats/Threat2CaseC.h"

const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> Threat2CaseC::k_ATOM_NUMBER_2C=
        {
                { ThreatFinder::MY_PAWN, 2 },
                { ThreatFinder::ENEMY_PAWN, 0 },
                { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
                { ThreatFinder::ASTERIX, -1 }  // it depends.
        };
/// Threat-mask for X player.
const ThreatFinder::ThreatPattern Threat2CaseC::m_threatPatternX[] = {
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
const ThreatFinder::ThreatPattern Threat2CaseC::m_threatPatternO[] = {
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
const uint32_t Threat2CaseC::m_threatPatternElements = NUMELEM(m_threatPatternX);

/// Define all points of view. Those are taken from m_threatPattern.
/// For both player is the same.
const uint32_t Threat2CaseC::m_pov[] = {1, 2, 3, 4, 5 };

Threat2CaseC::Threat2CaseC() : ThreatFinder(PATTERN_LENGHT, m_pov, NUMELEM(m_pov), k_ATOM_NUMBER_2C)
{
    // nothing to do.
}

///	Check pretendThreat if meets all requirement to real threat.
bool Threat2CaseC::checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                               const IBoard::Player playerPerspective) const
{
    // Equal the first pointOfview in m_threatPattern
    static const uint32_t pointOfViewOffset = 1;
    const uint32_t threatPatternIndex       = pointOfView - pointOfViewOffset;

    static const uint32_t myExpectedPawnInRow = 2;
    static const uint32_t expectedGaps        = 3;
    uint32_t myPawnsCntrMask                  = 0;
    uint32_t adversaryPawnsCntrMask           = 0;
    uint32_t emptyCntrMask                    = 0;
    uint32_t asterixCntrMask                  = 0;
    uint32_t threatPattern                    = 0;

    if(IBoard::PLAYER_A == playerPerspective)
    {
        myPawnsCntrMask        = 0x000000FF;
        adversaryPawnsCntrMask = 0x0000FF00;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        threatPattern          = m_threatPatternX[threatPatternIndex].m_threatPattern;
    }
    else if(IBoard::PLAYER_B == playerPerspective)
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
        m_threatDownDetails.m_hexCode           = pretendThreat;
        m_threatDownDetails.m_pointOfView       = pointOfView;
        m_threatDownDetails.m_playerPerspective = playerPerspective;
    }

    return retVal;
}

/// Gets threat up details after threat has been found.
void Threat2CaseC::getThreatUpDetails(const IBoard::PositionXY initialPosition, const Trend trend,
                                      ThreatUpDetails & rThreatUpDetails) const
{
    const uint32_t stepForward      = PATTERN_LENGHT - m_threatDownDetails.m_pointOfView - 1;
    const uint32_t stepBackward     = m_threatDownDetails.m_pointOfView;
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
    const IBoard::Direction directionForward  = Trend2DirectionStraight.at(trend);
    const IBoard::Direction directionBackward = Trend2DirectionReverse.at(trend);

    if(IBoard::PLAYER_A == m_threatDownDetails.m_playerPerspective)
    {
        myPawnsCntrMask        = 0x000000FF;
        adversaryPawnsCntrMask = 0x0000FF00;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        myPawnsShift           = 0;
        enemyPawnsShift        = 8;
    }
    else if(IBoard::PLAYER_B == m_threatDownDetails.m_playerPerspective)
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

    IBoard::PositionXY initialPositionNorm = initialPosition;
    getBoard().goDirection(initialPositionNorm, directionBackward, m_threatDownDetails.m_pointOfView);

    // 1. Provide my pawns.
    getPieces(myPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_myPawns[0],
              ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS);

    // 2. Provide enemy pawns.
    getPieces(enemyPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_enemyPawns[0],
              ThreatFinder::ThreatUpDetails::k_MAX_ENEMY_PAWNS);
    // a. make adjustment for a case ex. |.x.x.o   o.x.x.|
    const bool isEnemyPawnOnBoard1 = getBoard().isOnBoard(rThreatUpDetails.m_enemyPawns[0]);
    const bool isEnemyPawnOnBoard2 = getBoard().isOnBoard(rThreatUpDetails.m_enemyPawns[1]);
    IBoard::PositionXY beginTmp     = rThreatUpDetails.m_enemyPawns[0];
    IBoard::PositionXY endTmp       = rThreatUpDetails.m_enemyPawns[1];
    if(!isEnemyPawnOnBoard1 && !isEnemyPawnOnBoard2)
    {
        getBoard().goDirection(rThreatUpDetails.m_enemyPawns[0], directionForward);
        getBoard().goDirection(rThreatUpDetails.m_enemyPawns[1], directionBackward);
        beginTmp = rThreatUpDetails.m_enemyPawns[0];
        endTmp   = rThreatUpDetails.m_enemyPawns[1];

        rThreatUpDetails.m_enemyPawns[0] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
        rThreatUpDetails.m_enemyPawns[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else if(isEnemyPawnOnBoard1 && !isEnemyPawnOnBoard2)
    {
        getBoard().goDirection(rThreatUpDetails.m_enemyPawns[1], directionBackward);
        endTmp = rThreatUpDetails.m_enemyPawns[1];

        rThreatUpDetails.m_enemyPawns[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else if(!isEnemyPawnOnBoard1 && isEnemyPawnOnBoard2)
    {
        getBoard().goDirection(rThreatUpDetails.m_enemyPawns[0], directionForward);
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

    // 4. Provide extended gaps. Special case: ox...xo
    IBoard::PositionXY pretendExtGap1 = rThreatUpDetails.m_myPawns[1];
    IBoard::PositionXY pretendExtGap2 = rThreatUpDetails.m_myPawns[0];
    getBoard().goDirection(pretendExtGap1, directionForward, 2);
    getBoard().goDirection(pretendExtGap2, directionBackward, 2);
    const bool isPretendExtGap1OK =
            (pretendExtGap1 <= rThreatUpDetails.m_gaps[2]) && (getBoard().isOnBoard(pretendExtGap1));
    const bool isPretendExtGap2OK =
            (pretendExtGap2 >= rThreatUpDetails.m_gaps[0]) && (getBoard().isOnBoard(pretendExtGap2));
    const bool isSpecialCaseOK = (specialCaseMask == (specialCaseMask & gapsHexCodeNorm));

    if(isPretendExtGap1OK)
    {
        rThreatUpDetails.m_extGaps[0] = pretendExtGap1;
        rThreatUpDetails.m_extGaps[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else if(isPretendExtGap2OK)
    {
        rThreatUpDetails.m_extGaps[0] = pretendExtGap2;
        rThreatUpDetails.m_extGaps[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else if(isSpecialCaseOK)
    {
        // ox...xo. Extended gaps is in the middle.
        rThreatUpDetails.m_extGaps[0] = rThreatUpDetails.m_gaps[1];
        rThreatUpDetails.m_extGaps[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }
    else
    {
        rThreatUpDetails.m_extGaps[0] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
        rThreatUpDetails.m_extGaps[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    }

    // 5. Set begin and end.
    rThreatUpDetails.m_beginningThreat = beginTmp;
    rThreatUpDetails.m_endThreat       = endTmp;

    // Clear for the next coming.
    m_threatDownDetails.clearAll();
}
