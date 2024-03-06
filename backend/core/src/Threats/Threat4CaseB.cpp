#include "Threats/Threat4CaseB.h"

const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> Threat4CaseB::k_ATOM_NUMBER_4B = {
        { ThreatFinder::MY_PAWN, 2 },
        { ThreatFinder::ENEMY_PAWN, 0 },
        { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
        { ThreatFinder::ASTERIX, -1 }  // it depends.
};

/// Threat-mask for X player.
const ThreatFinder::ThreatPattern Threat4CaseB::m_threatPatternX[] = {
    // Finds:
    // OX.XXX*
    // OXX.XX*
    // OXXX.X*
    // OXXXX.*
    //{ 0x403C0102, 0 },
    { 0x201E4001, 1 },
    { 0x100F4020, 2 },
    { 0x08174020, 3 },
    { 0x041B4020, 4 },
    { 0x021D4020, 5 },
    //{ 0x011E4020, 6 },

    // Finds:
    // *.XXXXO
    // *X.XXXO
    // *XX.XXO
    // *XXX.XO
    //{ 0x011E4020, 0 },
    { 0x400F2010, 1 },
    { 0x40271008, 2 },
    { 0x40330804, 3 },
    { 0x40390402, 4 },
    { 0x403C0201, 5 },
    //{ 0x403C0102, 6 },
};

/// Threat-mask for O player.
const ThreatFinder::ThreatPattern Threat4CaseB::m_threatPatternO[] = {
    // Finds:
    // XO.OOO
    // XOO.OO
    // XOOO.O
    // XOOOO.
    //{ 0x403C0201, 0 },
    { 0x201E0140, 1 },
    { 0x100F2040, 2 },
    { 0x08172040, 3 },
    { 0x041B2040, 4 },
    { 0x021D2040, 5 },
    //{ 0x011E2040, 6 },

    // Finds:
    // .OOOOX
    // O.OOOX
    // OO.OOX
    // OOO.OX
    //{ 0x011E2040, 0 },
    { 0x400F1020, 1 },
    { 0x40270810, 2 },
    { 0x40330408, 3 },
    { 0x40390204, 4 },
    { 0x403C0102, 5 },
    //{ 0x403C0201, 6 },

};

/// Keeps number of elements in pattern threat.
const uint32_t Threat4CaseB::m_threatPatternElements = NUMELEM(m_threatPatternX) / 2;

/// Define all points of view. Those are taken from m_threatPattern.
/// For both player is the same.
const uint32_t Threat4CaseB::m_pov[] = {1, 2, 3, 4, 5 };

Threat4CaseB::Threat4CaseB() : ThreatFinder(PATTERN_LENGHT, m_pov, NUMELEM(m_pov), k_ATOM_NUMBER_4B)
{

}
///	Check pretendThreat if meets all requirement to real threat.
bool Threat4CaseB::checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                               const IBoard::Player playerPerspective) const
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
        m_threatDownDetails.m_hexCode           = pretendThreat;
        m_threatDownDetails.m_pointOfView       = pointOfView;
        m_threatDownDetails.m_playerPerspective = playerPerspective;

        if(FindSuccessNormal)
        {
            m_threatDownDetails.m_foundFlags.m_isNormalFound = true;
        }

        if(FindSuccessSymmetric)
        {
            m_threatDownDetails.m_foundFlags.m_isSymmetricFound = true;
        }
    }

    return (FindSuccessNormal || FindSuccessSymmetric);
}

// Check threat to find normal pattern.
bool Threat4CaseB::CheckThreatNormal(const uint32_t pretendThreat, const uint32_t pointOfView,
                                     const IBoard::Player playerPerspective) const
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
    uint32_t symmetricThreatPattern           = 0;

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
    const bool isMyPawnsMatch  = ((pretendThreat & myPawnsCntrMask) & (threatPattern & myPawnsCntrMask));

    // 2. Check enemy pawns.
    const bool isEnemyPawnsMatch =
        ((pretendThreat & adversaryPawnsCntrMask) & (threatPattern & adversaryPawnsCntrMask));

    // 3. Check empty space.
    const uint32_t gapsCntr = __builtin_popcount(pretendThreat & emptyCntrMask & threatPattern);

    // 4. Check asterix.
    const bool isAsterixMatch = ((pretendThreat & asterixCntrMask) & (threatPattern & asterixCntrMask));

    // Summarize.
    const bool isAllMatch = (myPawnsCntr == myExpectedPawnInRow) && isMyPawnsMatch && isEnemyPawnsMatch &&
                            (gapsCntr >= expectedGaps) && isAsterixMatch;

    return isAllMatch;
}

// Check threat to find symmetric pattern.
bool Threat4CaseB::CheckThreatSymmetric(const uint32_t pretendThreat, const uint32_t pointOfView,
                                        const IBoard::Player playerPerspective) const
{
    // Equal the first pointOfview in m_threatPattern
    static const uint32_t pointOfViewOffset    = 1;
    static const uint32_t symmetricOffset      = NUMELEM(m_threatPatternX) / 2;
    const uint32_t symmetricThreatPatternIndex = pointOfView - pointOfViewOffset + symmetricOffset;

    static const uint32_t myExpectedPawnInRow = 4;
    static const uint32_t expectedGaps        = 1;
    uint32_t myPawnsCntrMask                  = 0;
    uint32_t adversaryPawnsCntrMask           = 0;
    uint32_t emptyCntrMask                    = 0;
    uint32_t asterixCntrMask                  = 0;
    uint32_t threatPattern                    = 0;
    uint32_t symmetricThreatPattern           = 0;

    if(IBoard::PLAYER_A == playerPerspective)
    {
        myPawnsCntrMask        = 0x000000FF;
        adversaryPawnsCntrMask = 0x0000FF00;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        symmetricThreatPattern = m_threatPatternX[symmetricThreatPatternIndex].m_threatPattern;
    }
    else if(IBoard::PLAYER_B == playerPerspective)
    {
        myPawnsCntrMask        = 0x0000FF00;
        adversaryPawnsCntrMask = 0x000000FF;
        emptyCntrMask          = 0x00FF0000;
        asterixCntrMask        = 0xFF000000;
        symmetricThreatPattern = m_threatPatternO[symmetricThreatPatternIndex].m_threatPattern;
    }
    else
    {
        assert(false);
    }

    // 1. Check my pawns(number and location).
    const uint32_t myPawnsCntr = __builtin_popcount(pretendThreat & myPawnsCntrMask);
    const bool isMySymmetricPawnsMatch =
        ((pretendThreat & adversaryPawnsCntrMask) & (symmetricThreatPattern & adversaryPawnsCntrMask));

    // 2. Check enemy pawns.
    const bool isEnemySymmetricPawnsMatch =
        ((pretendThreat & adversaryPawnsCntrMask) & (symmetricThreatPattern & adversaryPawnsCntrMask));

    // 3. Check empty space.
    const uint32_t gapsCntrSymmetric = __builtin_popcount(pretendThreat & emptyCntrMask & symmetricThreatPattern);

    // 4. Check asterix.
    const bool isAsterixMatch = ((pretendThreat & asterixCntrMask) & (threatPattern & asterixCntrMask));
    const bool isAsterixSymmetricMatch =
        ((pretendThreat & asterixCntrMask) & (symmetricThreatPattern & asterixCntrMask));

    // Summarize.
    const bool isAllSymmetricMatch = (myPawnsCntr == myExpectedPawnInRow) && isMySymmetricPawnsMatch &&
                                     isEnemySymmetricPawnsMatch && (gapsCntrSymmetric >= expectedGaps) &&
                                     isAsterixSymmetricMatch;
    return isAllSymmetricMatch;
}

/// Gets threat up details after threat has been found.
void Threat4CaseB::getThreatUpDetails(const IBoard::PositionXY initialPosition, const Trend trend,
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

    uint8_t gapsHexCodeNormTmp = gapsHexCodeNorm;
    IBoard::PositionXY beginTmp = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    IBoard::PositionXY endTmp   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    if(m_threatDownDetails.m_foundFlags.m_isNormalFound)
    {
        rThreatUpDetails.m_enemyPawns[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
        const bool isEnemyOnBoard        = getBoard().isOnBoard(rThreatUpDetails.m_enemyPawns[0]);

        // a. Adjust enemy/Get asterix.
        if(isEnemyOnBoard)
        {
            beginTmp = rThreatUpDetails.m_enemyPawns[0];
        }
        else
        {
            rThreatUpDetails.m_enemyPawns[0] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
            beginTmp                         = rThreatUpDetails.m_myPawns[0];
        }

        endTmp = rThreatUpDetails.m_myPawns[0];
        getBoard().goDirection(endTmp, directionForward, PATTERN_LENGHT - 2);

        const bool isEndTmpOnBoard = getBoard().isOnBoard(endTmp);
        if(isEndTmpOnBoard)
        {
            rThreatUpDetails.m_asterixes[0] = endTmp;
        }
        else
        {
            rThreatUpDetails.m_asterixes[0] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;

            // One step too far.
            getBoard().goDirection(endTmp, directionBackward);
        }

        // b. We don't want to count asterix as a gap. Remove that bit.
        CLR_BIT(gapsHexCodeNormTmp, (PATTERN_LENGHT - 1));
    }
    else if(m_threatDownDetails.m_foundFlags.m_isSymmetricFound)
    {
        // a. Adjust enemy/Get asterix.
        //   Enemy is one step further of the forth myPawns.
        IBoard::PositionXY enemyTmp = rThreatUpDetails.m_myPawns[3];
        getBoard().goDirection(enemyTmp, directionForward);

        const bool isEnemyOnBoard = getBoard().isOnBoard(enemyTmp);
        if(isEnemyOnBoard)
        {
            endTmp                           = enemyTmp;
            rThreatUpDetails.m_enemyPawns[0] = endTmp;
            rThreatUpDetails.m_enemyPawns[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
        }
        else
        {
            endTmp                           = rThreatUpDetails.m_myPawns[3];
            rThreatUpDetails.m_enemyPawns[0] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
            rThreatUpDetails.m_enemyPawns[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
        }

        beginTmp = rThreatUpDetails.m_myPawns[3];
        getBoard().goDirection(beginTmp, directionBackward, PATTERN_LENGHT - 2);

        const bool isBeginTmpOnBoard = getBoard().isOnBoard(beginTmp);
        if(isBeginTmpOnBoard)
        {
            rThreatUpDetails.m_asterixes[0] = beginTmp;
        }
        else
        {
            rThreatUpDetails.m_asterixes[0] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;

            // One step too far.
            getBoard().goDirection(beginTmp, directionForward);
        }

        // b. We don't want to count asterix as a gap. Remove that bit.
        CLR_BIT(gapsHexCodeNormTmp, 0);
    }
    else
    {
        assert(false);
    }

    // 3. Provide gaps. Keeps gaps in index 0-4.
    getPieces(gapsHexCodeNormTmp, initialPositionNorm, directionForward, &rThreatUpDetails.m_gaps[0],
              ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES);

    // 4. Provide extended gaps.
    // none

    // 5. Set begin and end.
    rThreatUpDetails.m_beginningThreat = beginTmp;
    rThreatUpDetails.m_endThreat       = endTmp;

    // Clear for the next coming.
    m_threatDownDetails.clearAll();
}
