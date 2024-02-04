#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IBoard.h"
#include "GomokuBoard.h"
#include "Threats/Threat3CaseC.h"

class Threat3CaseCTest : public ::testing::Test
{
    void SetUp()
    {
        m_board = new GomokuBoard(15);
        m_threatFinder = new Threat3CaseC();
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

TEST_F(Threat3CaseCTest, FindPatternOnHorizontalTrendTest1)
{
    // Testing of each position: .XXX.

    // a:   .X...
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   ..XX..
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // c:   ..XXX.
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // d:   O..XXXO
    m_board->putMove(IBoard::PositionXY(1, 0), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseCTest, FindPatternOnHorizontalTrendTest2)
{
    //                        1 1 1 1 1
    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //  0 |. . . . . . . . . . . . . . .|
    //  1 |. . . x . x . x . . . . . . .|
    //  2 |. . . . . . . . . . . . . . .|
    //  3 |. . . . . . . . . . . . . . .|

    // Testing of each position: x.x.x

    // a:   X....
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   X.X..
    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // c:   X.X.X
    m_board->putMove(IBoard::PositionXY(1, 7), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // d:   OX.X.XO
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(1, 8), IBoard::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseCTest, FindPatternOnHorizontalTrendTest3)
{
    //                        1 1 1 1 1
    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //  0 |. . . . . . . . . . . . . . .|
    //  1 |. . x o . o . o x . . . . . .|
    //  2 |. . . . . . . . . . . . . . .|
    //  3 |. . . . . . . . . . . . . . .|

    // precondition
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 8), IBoard::PLAYER_A);

    // Testing of each position: o.o.o

    // a:   o....
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));

    // b:   o.o..
    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));

    // c:   o.o.o
    m_board->putMove(IBoard::PositionXY(1, 7), IBoard::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));

    // c:   o.ooo
    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
}

TEST_F(Threat3CaseCTest, FindPatternOnHorizontalTrendTest4)
{
    //                         1 1 1 1 1
    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //  0 |. . . . . . . . . . . . . . .|
    //  1 |. . o x x x . . o . . . . . .|
    //  2 |. . . . . . . . . . . . . . .|
    //  3 |. . . . . . . . . . . . . . .|

    // Precondition:
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(1, 8), IBoard::PLAYER_B);

    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseCTest, FindPatternOnHorizontalTrendTest5)
{
    //                         1 1 1 1 1
    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //  0 |. . . . . . . . . . . . . . .|
    //  1 |. . o . . x x x o . . . . . .|
    //  2 |. . . . . . . . . . . . . . .|
    //  3 |. . . . . . . . . . . . . . .|

    // Precondition:
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(1, 8), IBoard::PLAYER_B);

    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 7), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseCTest, FindPatternOnHorizontalTrendTest6)
{
    //                         1 1 1 1 1
    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //  0 |. . . . . . . . . . . . . . .|
    //  1 |. . o x . . x x o . . . . . .|
    //  2 |. . . . . . . . . . . . . . .|
    //  3 |. . . . . . . . . . . . . . .|

    // Precondition:
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(1, 8), IBoard::PLAYER_B);

    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 7), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseCTest, FindPatternOnHorizontalTrendTest7)
{
    //                         1 1 1 1 1
    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //  0 |. . . . . . . . . . . . . . .|
    //  1 |. . o x x . . x o . . . . . .|
    //  2 |. . . . . . . . . . . . . . .|
    //  3 |. . . . . . . . . . . . . . .|

    // Precondition:
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(1, 8), IBoard::PLAYER_B);

    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 7), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseCTest, FindPatternOnHorizontalTrendTest8)
{
    //                         1 1 1 1 1
    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //  0 |. . . . . . . . . . . . . . .|
    //  1 |. . o x x . . x x . . . . . .|
    //  2 |. . . . . . . . . . . . . . .|
    //  3 |. . . . . . . . . . . . . . .|

    // Precondition:
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_B);

    m_board->putMove(IBoard::PositionXY(1, 8), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 7), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseCTest, FindPatternOnFallingTrendTest9)
{
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . o . . .|
    //	12|. . . . . . . . . . . . x . .|
    //	13|. . . . . . . . . . . . . x .|
    //	14|. . . . . . . . . . . . . . x|
    //	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // Precondition:
    m_board->putMove(IBoard::PositionXY(11, 11), IBoard::PLAYER_B);

    m_board->putMove(IBoard::PositionXY(12, 12), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(13, 13), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(14, 14), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(12, 12), ThreatFinder::FALLING, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(13, 13), ThreatFinder::FALLING, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(14, 14), ThreatFinder::FALLING, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseCTest, FindPatternOnRisingTrendTest10)
{
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . x . . . . . . . . . .|
    //	11|. . . o . . . . . . . . . . .|
    //	12|. . . . . . . . . . . . . . .|
    //	13|. o . . . . . . . . . . . . .|
    //	14|o . . . . . . . . . . . . . .|
    //	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
    // Precondition:
    m_board->putMove(IBoard::PositionXY(10, 4), IBoard::PLAYER_A);

    m_board->putMove(IBoard::PositionXY(11, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(13, 1), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(14, 0), IBoard::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(11, 3), ThreatFinder::RISING, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(13, 1), ThreatFinder::RISING, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(14, 0), ThreatFinder::RISING, IBoard::PLAYER_B));
}

TEST_F(Threat3CaseCTest, FindPatternAbuttedToBoardTest1)
{
    // Testing abutted to frame: .XXX.

    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 1), ThreatFinder::RISING, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::RISING, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::RISING, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseCTest, GetPieces1)
{
    // oxxx..o
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |o x x x . . o . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elO1         = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elO2         = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 6);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_board->putMove(elO1, IBoard::PLAYER_B);
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
    ASSERT_TRUE(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);

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

    // d. Check 'o':
    ASSERT_TRUE(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // f. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat3CaseCTest, GetPieces2)
{
    // |..xxxo
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . x x x o . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elO1         = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 5);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_board->putMove(elO1, IBoard::PLAYER_B);
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
    ASSERT_TRUE(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);

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

    // d. Check 'o':
    ASSERT_TRUE(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // f. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat3CaseCTest, GetPieces3)
{
    // |.xxx.o
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. x x x . o . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 4);
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
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elO1         = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 5);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_board->putMove(elO1, IBoard::PLAYER_B);
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
    ASSERT_TRUE(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);

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

    // d. Check 'o':
    ASSERT_TRUE(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // f. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat3CaseCTest, GetPieces4)
{
    // o.x.xx|
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . o . x . x x|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 10);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 12);
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
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 11);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 13);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 14);
    const IBoard::PositionXY elO1         = IBoard::PositionXY(1, 9);
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 9);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 14);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_board->putMove(elO1, IBoard::PLAYER_B);

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

    // d. Check 'o':
    ASSERT_TRUE(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // f. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat3CaseCTest, GetPieces5)
{
    // ox..xxo
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . o x . . x x o . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 6);
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
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 7);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elX4         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO1         = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elO2         = IBoard::PositionXY(1, 9);
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 9);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_board->putMove(elO1, IBoard::PLAYER_B);
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
    ASSERT_TRUE(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
    ASSERT_TRUE(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);

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

    // d. Check 'o':
    ASSERT_TRUE(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // f. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat3CaseCTest, GetPieces6)
{
    // |x.xx.|
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . x . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . x . . . . . . . . . . . .|
    // 3 |. x . . . . . . . . . . . . .|
    // 4 |. . . . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(4, 0);
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
    const IBoard::PositionXY elX1         = IBoard::PositionXY(0, 4);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(2, 2);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(3, 1);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 4);
    const IBoard::PositionXY end          = IBoard::PositionXY(4, 0);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::RISING, IBoard::PLAYER_A);

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

    // d. Check 'o':
    ASSERT_TRUE(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // f. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat3CaseCTest, GetPieces7)
{
    // |x..xx|
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . x . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . x .|
    // 4 |. . . . . . . . . . . . . . x|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 11);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(2, 12);
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
    const IBoard::PositionXY elX1         = IBoard::PositionXY(0, 10);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(3, 13);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(4, 14);
    const IBoard::PositionXY elX4         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 10);
    const IBoard::PositionXY end          = IBoard::PositionXY(4, 14);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::FALLING, IBoard::PLAYER_A);

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

    // d. Check 'o':
    ASSERT_TRUE(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // f. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat3CaseCTest, GetPieces8)
{
    // |..xxx|
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . x . .|
    // 3 |. . . . . . . . . . . . . x .|
    // 4 |. . . . . . . . . . . . . . x|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(0, 10);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 11);
    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(0, 10);
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(2, 12);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(3, 13);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(4, 14);
    const IBoard::PositionXY elX4         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 10);
    const IBoard::PositionXY end          = IBoard::PositionXY(4, 14);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
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
    ASSERT_TRUE(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);

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

    // d. Check 'o':
    ASSERT_TRUE(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Extend gaps:
    ASSERT_TRUE(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    ASSERT_TRUE(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // f. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}
