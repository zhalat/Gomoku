#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Board.h"
#include "GomokuBoard.h"
#include "Threats/ThreatWinner.h"

class ThreatWinnerTest : public ::testing::Test
{
    void SetUp()
    {
        m_board = new GomokuBoard(15);
        m_threatFinder = new ThreatWinner();
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

TEST_F(ThreatWinnerTest, FindPatternOnHorizontalTrendTest1)
{
    // a:   X....
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // b:   XX...
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // c:   XXX..
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // d:   XXXX.
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // e:   XXXXX
    m_board->putMove(Board::PositionXY(1, 5), Board::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // Six in a row is not winning path.
    // f:   XXXXXX
    m_board->putMove(Board::PositionXY(1, 6), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
}

TEST_F(ThreatWinnerTest, FindPatternOnHorizontalTrendTest2)
{
    // a:   X....
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::FALLING, Board::PLAYER_A));

    // b:   XX...
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(2, 2), ThreatFinder::FALLING, Board::PLAYER_A));

    // c:   XXX..
    m_board->putMove(Board::PositionXY(3, 3), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::FALLING, Board::PLAYER_A));

    // d:   XXXX.
    m_board->putMove(Board::PositionXY(4, 4), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 4), ThreatFinder::FALLING, Board::PLAYER_A));

    // e:   XXXXX
    m_board->putMove(Board::PositionXY(5, 5), Board::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(5, 5), ThreatFinder::FALLING, Board::PLAYER_A));

    // Six in a row is not winning path.
    // f:   XXXXXX
    m_board->putMove(Board::PositionXY(6, 6), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(6, 6), ThreatFinder::FALLING, Board::PLAYER_A));
}

TEST_F(ThreatWinnerTest, FindPatternOnHorizontalTrendTest3)
{
    // a:   O....
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::FALLING, Board::PLAYER_B));

    // b:   OO...
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(2, 2), ThreatFinder::FALLING, Board::PLAYER_B));

    // c:   OOO..
    m_board->putMove(Board::PositionXY(3, 3), Board::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::FALLING, Board::PLAYER_B));

    // d:   OOOO.
    m_board->putMove(Board::PositionXY(4, 4), Board::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 4), ThreatFinder::FALLING, Board::PLAYER_B));

    // e:   OOOOO
    m_board->putMove(Board::PositionXY(5, 5), Board::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(5, 5), ThreatFinder::FALLING, Board::PLAYER_B));

    // Six in a row is not winning path.
    // f:   OOOOOO
    m_board->putMove(Board::PositionXY(6, 6), Board::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(6, 6), ThreatFinder::FALLING, Board::PLAYER_B));
}

TEST_F(ThreatWinnerTest, FindPatternOnHorizontalTrendTest4)
{
    // a:   XXX.X
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 5), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // b:   XXXXX
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
}

TEST_F(ThreatWinnerTest, FindPatternOnHorizontalTrendTest5)
{
    // a:   OOO.OO
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 5), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 6), Board::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_B));

    // b:   OOOOOO
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
}

TEST_F(ThreatWinnerTest, FindPatternOnHorizontalTrendTest6)
{
    // a:   XXX.XO
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 5), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 6), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_B));

    // b:   XXXXXO
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
}

TEST_F(ThreatWinnerTest, FindPatternOnHorizontalTrendTest7)
{
    // a:   XOOO.OX
    m_board->putMove(Board::PositionXY(1, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 5), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 6), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 0), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_B));

    // b:   XOOOOOX
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
}

TEST_F(ThreatWinnerTest, FindPatternAbuttedToBoardTest)
{
    // a:   X....
    m_board->putMove(Board::PositionXY(4, 0), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 0), ThreatFinder::RISING, Board::PLAYER_A));

    // b:   XX...
    m_board->putMove(Board::PositionXY(3, 1), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 1), ThreatFinder::RISING, Board::PLAYER_A));

    // c:   XXX..
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(2, 2), ThreatFinder::RISING, Board::PLAYER_A));

    // d:   XXXX.
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::RISING, Board::PLAYER_A));

    // e:   XXXXX
    m_board->putMove(Board::PositionXY(0, 4), Board::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 4), ThreatFinder::RISING, Board::PLAYER_A));
}

TEST_F(ThreatWinnerTest, GetPieces1)
{
    // .xxxx.
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . x x x x x . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = Board::PositionXY(1, 3);
    const Board::PositionXY elAsterix2   = Board::PositionXY(1, 9);
    const Board::PositionXY elGap1       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elX1         = Board::PositionXY(1, 4);
    const Board::PositionXY elX2         = Board::PositionXY(1, 5);
    const Board::PositionXY elX3         = Board::PositionXY(1, 6);
    const Board::PositionXY elX4         = Board::PositionXY(1, 7);
    const Board::PositionXY elX5         = Board::PositionXY(1, 8);
    const Board::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(1, 3);
    const Board::PositionXY end          = Board::PositionXY(1, 9);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elX5, Board::PLAYER_A);
    m_threatFinder->findThreatPattern(elX1, ThreatFinder::HORIZONTAL, Board::PLAYER_A);

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

TEST_F(ThreatWinnerTest, GetPieces2)
{
    // |xxxx.
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |x x x x x . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = Board::PositionXY(1, 5);
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elX1         = Board::PositionXY(1, 0);
    const Board::PositionXY elX2         = Board::PositionXY(1, 1);
    const Board::PositionXY elX3         = Board::PositionXY(1, 2);
    const Board::PositionXY elX4         = Board::PositionXY(1, 3);
    const Board::PositionXY elX5         = Board::PositionXY(1, 4);
    const Board::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(1, 0);
    const Board::PositionXY end          = Board::PositionXY(1, 5);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elX5, Board::PLAYER_A);
    m_threatFinder->findThreatPattern(elX1, ThreatFinder::HORIZONTAL, Board::PLAYER_A);

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

TEST_F(ThreatWinnerTest, GetPieces3)
{
    // |xxxx.
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . x x x x x|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = Board::PositionXY(1, 9);
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elX1         = Board::PositionXY(1, 10);
    const Board::PositionXY elX2         = Board::PositionXY(1, 11);
    const Board::PositionXY elX3         = Board::PositionXY(1, 12);
    const Board::PositionXY elX4         = Board::PositionXY(1, 13);
    const Board::PositionXY elX5         = Board::PositionXY(1, 14);
    const Board::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(1, 9);
    const Board::PositionXY end          = Board::PositionXY(1, 14);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elX5, Board::PLAYER_A);
    m_threatFinder->findThreatPattern(elX1, ThreatFinder::HORIZONTAL, Board::PLAYER_A);

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

TEST_F(ThreatWinnerTest, GetPieces4)
{
    // |xxxxx|
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . x . . . . . . . . . .|
    // 1 |. . . x . . . . . . . . . . .|
    // 2 |. . x . . . . . . . . . . . .|
    // 3 |. x . . . . . . . . . . . . .|
    // 4 |x . . . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elX1         = Board::PositionXY(0, 4);
    const Board::PositionXY elX2         = Board::PositionXY(1, 3);
    const Board::PositionXY elX3         = Board::PositionXY(2, 2);
    const Board::PositionXY elX4         = Board::PositionXY(3, 1);
    const Board::PositionXY elX5         = Board::PositionXY(4, 0);
    const Board::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(0, 4);
    const Board::PositionXY end          = Board::PositionXY(4, 0);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elX5, Board::PLAYER_A);
    m_threatFinder->findThreatPattern(elX1, ThreatFinder::RISING, Board::PLAYER_A);

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
