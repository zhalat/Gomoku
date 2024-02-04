#include "Threat3CaseA.h"

const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> Threat3CaseA::k_ATOM_NUMBER_3A= {
        { ThreatFinder::MY_PAWN, 2 },
        { ThreatFinder::ENEMY_PAWN, 0 },
        { ThreatFinder::GAP, -1 },     // it depends. .xx...* or  *...xx...*
        { ThreatFinder::ASTERIX, -1 }  // it depends.
};

/// Threat-mask for X player.
const ThreatFinder::ThreatPattern Threat3CaseA::m_threatPatternX[] = {
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
const ThreatFinder::ThreatPattern Threat3CaseA::m_threatPatternO[] = {
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
const uint32_t Threat3CaseA::m_threatPatternElements = NUMELEM(m_threatPatternX) / 2;

/// Define all points of view. Those are taken from m_threatPattern.
/// For both player is the same.
const uint32_t Threat3CaseA::m_pov[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };

Threat3CaseA::Threat3CaseA() : ThreatFinder(PATTERN_LENGHT, m_pov, NUMELEM(m_pov), k_ATOM_NUMBER_3A)
{
    m_foundFlags.clearAll();
}

///	Check pretendThreat if meets all requirement to real threat.
bool Threat3CaseA::checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                               const IBoard::Player playerPerspective) const
{
    // Points when to switch to search symmetric pattern.
    static const uint32_t pointOfViewSwitch = 0x05;
    bool FindSuccessNormal                  = false;
    bool FindSuccessSymmetric               = false;

    if(true == m_foundFlags.m_isSearchingForSymmetric)
    {
        // It means that ThreatFinder is searching for symmetric pattern.
        if(false == m_foundFlags.m_isSymmetricFound)
        {
            // It means symmetric pattern has not been found yet.
            FindSuccessSymmetric = CheckThreatSymmetric(pretendThreat, pointOfView, playerPerspective);
        }
    }
    else
    {
        // It means that ThreatFinder is searching for normal pattern.
        if(false == m_foundFlags.m_isNormalFound)
        {
            // It means normal pattern has not been found yet.
            FindSuccessNormal = CheckThreatNormal(pretendThreat, pointOfView, playerPerspective);
        }
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
            m_foundFlags.m_isNormalFound                     = true;
        }

        if(FindSuccessSymmetric)
        {
            m_threatDownDetails.m_foundFlags.m_isSymmetricFound = true;
            m_foundFlags.m_isSymmetricFound                     = true;
        }
    }

    // 3. Switch to symmetric
    if(pointOfView == pointOfViewSwitch)
    {
        m_foundFlags.m_isSearchingForSymmetric = true;
    }

    return (FindSuccessNormal || FindSuccessSymmetric);
}

// Check threat to find normal pattern.
bool Threat3CaseA::CheckThreatNormal(const uint32_t pretendThreat, const uint32_t pointOfView,
                                     const IBoard::Player playerPerspective) const
{
    // Equal the first pointOfview in m_threatPattern
    static const uint32_t pointOfViewOffset = 1;
    const uint32_t threatPatternIndex       = pointOfView - pointOfViewOffset;

    static const uint32_t myExpectedPawnInRow = 3;
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
                                        const IBoard::Player playerPerspective) const
{
    // Equal the first pointOfview in m_threatPattern
    static const uint32_t pointOfViewOffset    = 1;
    const uint32_t symmetricThreatPatternIndex = NUMELEM(m_pov) / 2 + pointOfView - pointOfViewOffset;

    static const uint32_t myExpectedPawnInRow = 3;
    static const uint32_t expectedGaps        = 3;
    uint32_t myPawnsCntrMask                  = 0;
    uint32_t adversaryPawnsCntrMask           = 0;
    uint32_t emptyCntrMask                    = 0;
    uint32_t asterixCntrMask                  = 0;
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
void Threat3CaseA::getThreatUpDetails(const IBoard::PositionXY initialPosition, const Trend trend,
                                      ThreatUpDetails & rThreatUpDetails) const
{
    const uint32_t lastGapIndex     = 2;
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
    const uint8_t gapsHexCode        = static_cast<uint8_t>((m_threatDownDetails.m_hexCode & emptyCntrMask) >> 16);
    const uint8_t myPawnsHexCodeNorm = standarizePov(myPawnsHexCode, m_threatDownDetails.m_pointOfView, PATTERN_LENGHT);
    const uint8_t gapsHexCodeNorm    = standarizePov(gapsHexCode, m_threatDownDetails.m_pointOfView, PATTERN_LENGHT);

    IBoard::PositionXY initialPositionNorm = initialPosition;
    getBoard().goDirection(initialPositionNorm, directionBackward, m_threatDownDetails.m_pointOfView);

    // 1. Provide my pawns.
    getPieces(myPawnsHexCodeNorm, initialPositionNorm, directionForward, &rThreatUpDetails.m_myPawns[0],
              ThreatFinder::ThreatUpDetails::k_MAX_MY_PAWNS);

    // 2. Provide asterixes & gaps
    if(m_threatDownDetails.m_foundFlags.m_isNormalFound)
    {
        // a. Get asterixes.
        IBoard::PositionXY initialPositionNormTmp = initialPositionNorm;
        getBoard().goDirection(initialPositionNormTmp, directionForward, PATTERN_LENGHT - 1);
        rThreatUpDetails.m_asterixes[0] = getBoard().isOnBoard(initialPositionNormTmp)
                                              ? initialPositionNormTmp
                                              : ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;

        // b. Get gaps. Keeps gaps in index 0-4.
        // 	  We don't want to count asterix as a gap. Remove that bit.
        uint8_t gapsHexCodeNormTmp = gapsHexCodeNorm;
        CLR_BIT(gapsHexCodeNormTmp, (PATTERN_LENGHT - 1));
        getPieces(gapsHexCodeNormTmp, initialPositionNorm, directionForward, &rThreatUpDetails.m_gaps[0],
                  ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2);

        // c. Get extension gap. It's two movies from the second X. Must not be gather than Gaps[3].
        IBoard::PositionXY pretendExtGap = rThreatUpDetails.m_myPawns[2];
        getBoard().goDirection(pretendExtGap, directionForward, 2);
        const bool ispretendExtGapOK =
                (pretendExtGap <= rThreatUpDetails.m_gaps[2]) && (getBoard().isOnBoard(pretendExtGap));
        rThreatUpDetails.m_extGaps[0] =
            (ispretendExtGapOK) ? pretendExtGap : ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;

        // d. Provide threat beginning.
        rThreatUpDetails.m_beginningThreat = rThreatUpDetails.m_gaps[0];
        rThreatUpDetails.m_endThreat =
            (rThreatUpDetails.m_asterixes[0] != ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD)
                ? rThreatUpDetails.m_asterixes[0]
                : rThreatUpDetails.m_gaps[lastGapIndex];
    }

    if(m_threatDownDetails.m_foundFlags.m_isSymmetricFound)
    {
        // a. Get asterixes.
        rThreatUpDetails.m_asterixes[1] = (true == getBoard().isOnBoard(initialPositionNorm))
                                              ? initialPositionNorm
                                              : ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;

        // b. Get gaps. Keeps gaps in index 5-9.
        // 	  We don't want to count asterix as a gap. Remove that bit.
        uint8_t gapsHexCodeNormTmp = gapsHexCodeNorm;
        CLR_BIT(gapsHexCodeNormTmp, 0);
        getPieces(gapsHexCodeNormTmp, initialPositionNorm, directionForward,
                  &rThreatUpDetails.m_gaps[ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2],
                  ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2);

        // c. Get extension gap. It's two movies from the first X. Must not be lower than Gaps[0].
        IBoard::PositionXY pretendExtGap = rThreatUpDetails.m_myPawns[0];
        getBoard().goDirection(pretendExtGap, directionBackward, 2);
        const bool ispretendExtGapOK =
                (pretendExtGap >= rThreatUpDetails.m_gaps[ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2]) &&
                (getBoard().isOnBoard(pretendExtGap));
        rThreatUpDetails.m_extGaps[1] =
            ispretendExtGapOK ? pretendExtGap : ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;

        // d. Provide threat beginning & end. Threat's size must be greedy.
        const uint32_t lastGapSimmetricIndex = 2 + ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2;
        rThreatUpDetails.m_beginningThreat =
            (rThreatUpDetails.m_asterixes[1] != ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD)
                ? rThreatUpDetails.m_asterixes[1]
                : rThreatUpDetails.m_gaps[ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2];
        rThreatUpDetails.m_endThreat =
            ((rThreatUpDetails.m_gaps[lastGapSimmetricIndex] > rThreatUpDetails.m_endThreat) ||
             (rThreatUpDetails.m_endThreat == ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD))
                ? rThreatUpDetails.m_gaps[lastGapSimmetricIndex]
                : rThreatUpDetails.m_endThreat;
    }

    // Clear for the next coming.
    m_threatDownDetails.clearAll();
}
