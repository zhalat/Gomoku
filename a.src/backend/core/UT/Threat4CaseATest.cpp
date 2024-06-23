#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Interfaces/IBoard.h"
#include "GomokuBoard.h"
#include "Threats/Threat4CaseA.h"

class Threat4CaseATest : public ::testing::Test
{
    void SetUp()
    {
        m_board = new GomokuBoard(15);
        m_threatFinder = new Threat4CaseA();
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

TEST_F(Threat4CaseATest, FindPatternOnHorizontalTrendTest1)
{
    // step by step build .XXXX. and verify if pattern is found.

    // a:   .X....
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   .XX...
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // c:   .XXX..
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // d:   .XXXX.
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // e:   .XXXXX.
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat4CaseATest, FindPatternOnHorizontalTrendTest2)
{
    // step by step build .OOOO. and verify if pattern is found.

    // a:   .O....
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));

    // b:   .OO...
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));

    // c:   .OOO..
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));

    // d:   .OOOO.
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));

    // e:   .OOOOO.
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
}

TEST_F(Threat4CaseATest, FindPatternAbuttedToBoardFrameTest)
{
    //	                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . x . x . . . . . . . . .|
    //	1 |. . x x x . . . . . x . . . .|
    //	2 |. x x x . . . . . . . x . . .|
    //	3 |x x x . . . . . . . . . x . .|
    //	4 |x . . . . . . . . . . . . x .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    //	12|. . . . . . . . . . . . . . .|
    //	13|. . . . . . . . . . . . . . .|
    //	14|. . . . . . . . . . . . . . .|
    //	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // Some cases where false StraightFourPattern is abutted on the frame.
    m_board->putMove(IBoard::PositionXY(0, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 0), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 1), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(4, 0), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(0, 5), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 5), ThreatFinder::RISING, IBoard::PLAYER_A));

    // A case where true StraightFourPattern is abutted on frame.
    m_board->putMove(IBoard::PositionXY(1, 10), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 11), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 12), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 13), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 13), ThreatFinder::FALLING, IBoard::PLAYER_A));
}

TEST_F(Threat4CaseATest, getThreatFieldsTest1)
{
    // Create threat  .XXXX.
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);

    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // Get all fields which threat state.
    ThreatFinder::ThreatLocation threatLocation;

    m_threatFinder->getThreatFields(threatLocation);

    const IBoard::PositionXY beginThreat = IBoard::PositionXY(2, 1);
    const IBoard::PositionXY endThreat   = IBoard::PositionXY(2, 6);

    ASSERT_TRUE(beginThreat == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(endThreat == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat4CaseATest, getThreatFieldsTest2)
{
    // Create threat  .XXXX.
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);

    m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 1), ThreatFinder::RISING, IBoard::PLAYER_A);

    // Get all fields which threat state.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    const IBoard::PositionXY beginThreat = IBoard::PositionXY(0, 5);
    const IBoard::PositionXY endThreat   = IBoard::PositionXY(5, 0);

    ASSERT_TRUE(beginThreat == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(endThreat == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat4CaseATest, getThreatFieldsTest3)
{
    // Create threat  .XXXX.
    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 5), IBoard::PLAYER_A);

    m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::VERTICAL, IBoard::PLAYER_A);

    // Get all fields which threat state.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    const IBoard::PositionXY beginThreat = IBoard::PositionXY(0, 5);
    const IBoard::PositionXY endThreat   = IBoard::PositionXY(5, 5);

    ASSERT_TRUE(beginThreat == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(endThreat == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat4CaseATest, getThreatFieldsTest4)
{
    // Create threat  .XXXX.
    m_board->putMove(IBoard::PositionXY(1, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 4), IBoard::PLAYER_A);

    m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 1), ThreatFinder::FALLING, IBoard::PLAYER_A);

    // Get all fields which threat state.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    const IBoard::PositionXY beginThreat = IBoard::PositionXY(0, 0);
    const IBoard::PositionXY endThreat   = IBoard::PositionXY(5, 5);

    ASSERT_TRUE(beginThreat == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(endThreat == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat4CaseATest, GetPieces1)
{
    // .xxxx.
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . x x x x . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elX4         = IBoard::PositionXY(1, 7);
    const IBoard::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 8);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_board->putMove(elX4, IBoard::PLAYER_A);
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
    ASSERT_TRUE(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
    ASSERT_TRUE(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
    ASSERT_TRUE(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat4CaseATest, GetPieces2)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . x . . . . . . . . . .|
    // 2 |. . . x . . . . . . . . . . .|
    // 3 |. . x . . . . . . . . . . . .|
    // 4 |. x . . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(0, 5);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(5, 0);
    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(2, 3);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(3, 2);
    const IBoard::PositionXY elX4         = IBoard::PositionXY(4, 1);
    const IBoard::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 5);
    const IBoard::PositionXY end          = IBoard::PositionXY(5, 0);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_board->putMove(elX4, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX4, ThreatFinder::RISING, IBoard::PLAYER_A);

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
    ASSERT_TRUE(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
    ASSERT_TRUE(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
    ASSERT_TRUE(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    ASSERT_TRUE(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    ASSERT_TRUE(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    ASSERT_TRUE(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    ASSERT_TRUE(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    ASSERT_TRUE(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}
