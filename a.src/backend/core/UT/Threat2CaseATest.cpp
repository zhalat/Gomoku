#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Interfaces/IBoard.h"
#include "GomokuBoard.h"
#include "Threats/Threat2CaseA.h"

class Threat2CaseATest : public ::testing::Test
{
    void SetUp()
    {
        m_board = new GomokuBoard(15);
        m_threatFinder = new Threat2CaseA();
        m_threatFinder->setBoard(m_board);
    }

    void TearDown()
    {
        delete m_board;
        delete m_threatFinder;
    }

public:
    GomokuBoard* m_board{nullptr};
    ThreatFinder* m_threatFinder{nullptr};
};

TEST_F(Threat2CaseATest, FindPatternOnHorizontalTrendTest1)
{
    // Testing of each position: .XX...

    // a:   .X....
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   .XX...
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternOnHorizontalTrendTest2)
{
    // Testing of each position: .X.X..

    // a:   .X....
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   .X.X..
    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternOnHorizontalTrendTest3)
{
    // Testing of each position: .X..X.

    // a:   .X....
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   .X..X.
    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternOnHorizontalTrendTest4)
{
    // Testing of each position: ..XX..

    // a:   ..X...
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   ..XX..
    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternOnHorizontalTrendTest5)
{
    // Testing of each position: ..X.X.

    // a:   ..X...
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   ..X.X.
    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternOnHorizontalTrendTest6)
{
    // Testing of each position: ...XX.

    // a:   ....X.
    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   ...XX.
    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternAbuttedToBoardTest1)
{
    // Testing of each position: .XX...
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 1), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(5, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternAbuttedToBoardTest2)
{
    // Testing of each position: .X.X..
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 1), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(5, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternAbuttedToBoardTest3)
{
    // Testing of each position: .X..X.
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 1), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(5, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternAbuttedToBoardTest4)
{
    // Testing of each position: ..XX..
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 2), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(5, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 3), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternAbuttedToBoardTest5)
{
    // Testing of each position: ..X.X.
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 2), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(5, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 3), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternAbuttedToBoardTest6)
{
    // Testing of each position: ...XX.
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(5, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 2), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternIntruder)
{
    // Testing of each position: .X..X.

    // a:   .X....
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   .X..X.
    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // c:   .XO.X.
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternSixInARow1)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. x x . . x . . . . . . . . .|
    // 1 |. . . . . . . . . x . . x x .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    m_board->putMove(IBoard::PositionXY(0, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(0, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(0, 5), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(1, 9), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 12), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 13), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 9), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(
        m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 12), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(
        m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 13), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternSixInARow2)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. x x . . . x . . . . . . . .|
    // 1 |. . . . . . . . x . . x . x .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    m_board->putMove(IBoard::PositionXY(0, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(0, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(0, 6), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(1, 8), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 11), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 13), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 11), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 13), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, FindPatternSixInARow3)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . x . x x . . . x . . .|
    // 2 |. . . . x . x x . . . o . . .|
    // 3 |. . . . o . x x . . . x . . .|

    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 7), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 11), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 11), IBoard::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(3, 4), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(3, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 7), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 11), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat2CaseATest, GetPieces1)
{
    // .x.x..*
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. x . x . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap4       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 6);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .x.x..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.x.x..
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // e. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // f. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat2CaseATest, GetPieces2)
{
    // .xx...*
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. x x . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap4       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
    ;
    const IBoard::PositionXY end = IBoard::PositionXY(1, 6);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .xx...*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: |.xx...
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat2CaseATest, GetPieces3)
{
    // *.x..x.
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . x . . x .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 9);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 11);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 12);
    const IBoard::PositionXY elGap4       = IBoard::PositionXY(1, 14);
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 10);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 13);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 14);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[1]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[0]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .x..x.|
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.x..x.
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat2CaseATest, GetPieces4)
{
    //
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . * . . . x x . . . * . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 11);
    const IBoard::PositionXY elAsterix2   = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 9);
    const IBoard::PositionXY elGap4       = IBoard::PositionXY(1, 10);
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap9       = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(1, 9);
    const IBoard::PositionXY elExtendGap2 = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 7);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 11);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .xx...*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *...xx.
    ASSERT_TRUE(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat2CaseATest, GetPieces5)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . x . x . . * . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 7);
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap4       = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elGap9       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elExtendGap2 = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .x.x..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: |..x.x.
    ASSERT_TRUE(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);
}

TEST_F(Threat2CaseATest, GetPieces6)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |* . . x . x . . * . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elAsterix2   = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elGap4       = IBoard::PositionXY(1, 7);
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap9       = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(1, 7);
    const IBoard::PositionXY elExtendGap2 = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 8);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .x.x..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *..x.x.
    ASSERT_TRUE(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat2CaseATest, GetPieces7)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |* . . x . x . . o . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elAsterix2   = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elGap4       = IBoard::PositionXY(1, 7);
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap9       = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(1, 7);
    const IBoard::PositionXY elExtendGap2 = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elO1         = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 8);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elO2, IBoard::PLAYER_B);
    m_threatFinder->findThreatPattern(elX1, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .x.x..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *..x.x.
    ASSERT_TRUE(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat2CaseATest, GetPieces8)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . x . . . . . . . . . .|
    // 2 |. . . x . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|
    // 4 |. . . . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(0, 5);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(3, 2);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(4, 1);
    const IBoard::PositionXY elGap4       = IBoard::PositionXY(5, 0);
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(0, 5);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(3, 2);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(4, 1);
    const IBoard::PositionXY elGap9       = IBoard::PositionXY(5, 0);
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(4, 1);
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(2, 3);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 5);
    const IBoard::PositionXY end          = IBoard::PositionXY(5, 0);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX1, ThreatFinder::RISING, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .x.x..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *..x.x.
    ASSERT_TRUE(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat2CaseATest, GetPieces9)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . x . . .|
    // 3 |. . . . . . . . . . . . . . .|
    // 4 |. . . . . . . . . . . . . x .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(0, 9);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 10);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(3, 12);
    const IBoard::PositionXY elGap4       = IBoard::PositionXY(5, 14);
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(0, 9);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(1, 10);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(3, 12);
    const IBoard::PositionXY elGap9       = IBoard::PositionXY(5, 14);
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = IBoard::PositionXY(0, 9);
    const IBoard::PositionXY elX1         = IBoard::PositionXY(2, 11);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(4, 13);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 9);
    const IBoard::PositionXY end          = IBoard::PositionXY(5, 14);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX1, ThreatFinder::FALLING, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .x.x..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *..x.x.
    ASSERT_TRUE(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat2CaseATest, GetPieces10)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . * .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|
    // 4 |. . . . . . . . . x . . . . .|
    // 5 |. . . . . . . . x . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . x . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = IBoard::PositionXY(0, 13);
    const IBoard::PositionXY elGap1       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(1, 12);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(2, 11);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(3, 10);
    const IBoard::PositionXY elGap9       = IBoard::PositionXY(6, 7);
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = IBoard::PositionXY(2, 11);
    const IBoard::PositionXY elX1         = IBoard::PositionXY(4, 9);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(5, 8);
    const IBoard::PositionXY X3           = IBoard::PositionXY(7, 6);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 13);
    const IBoard::PositionXY end          = IBoard::PositionXY(6, 7);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(X3, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX1, ThreatFinder::RISING, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .x.x..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *..x.x.
    ASSERT_TRUE(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat2CaseATest, GetPieces11)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . x . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . x . . . . .|
    // 4 |. . . . . . . . x . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . * . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1 = IBoard::PositionXY(8, 4);
    const IBoard::PositionXY elAsterix2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1     = IBoard::PositionXY(2, 10);
    const IBoard::PositionXY elGap2     = IBoard::PositionXY(5, 7);
    const IBoard::PositionXY elGap3     = IBoard::PositionXY(6, 6);
    const IBoard::PositionXY elGap4     = IBoard::PositionXY(7, 5);
    const IBoard::PositionXY elGap5     = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6     = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap7     = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap8     = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    ;
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(6, 6);
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(3, 9);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(4, 8);
    const IBoard::PositionXY X3           = IBoard::PositionXY(1, 11);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(2, 10);
    const IBoard::PositionXY end          = IBoard::PositionXY(8, 4);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(X3, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX1, ThreatFinder::RISING, IBoard::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    ASSERT_TRUE(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    ASSERT_TRUE(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    ASSERT_TRUE(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    ASSERT_TRUE(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);

    // c. Check '.':
    //    Normal: .x.x..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *..x.x.
    ASSERT_TRUE(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}
