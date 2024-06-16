#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Interfaces/IBoard.h"
#include "GomokuBoard.h"
#include "Threats/Threat3CaseA.h"

class Threat3CaseATest : public ::testing::Test
{
    void SetUp()
    {
        m_board = new GomokuBoard(15);
        m_threatFinder = new Threat3CaseA();
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

TEST_F(Threat3CaseATest, FindPatternOnHorizontalTrendTest1)
{
    // Testing of each position: ..XXX.

    // a:   ..X...
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   ..XX..
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // c:   ..XXX.
    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternOnHorizontalTrendTest2)
{
    // Testing of each position: .X.XX.

    // a:   .X....
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   .X.X..
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // c:   .X.XX.
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternOnHorizontalTrendTest3)
{
    // Testing of each position: .XX.X.

    // a:   ..X....
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   .XX...
    m_board->putMove(IBoard::PositionXY(3, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // c:   .XX.X.
    m_board->putMove(IBoard::PositionXY(3, 5), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternOnHorizontalTrendTest4)
{
    // Testing of each position: .XXX..

    // a:   .X....
    m_board->putMove(IBoard::PositionXY(4, 2), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b:   .XX...
    m_board->putMove(IBoard::PositionXY(4, 3), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // c:   .XXX..
    m_board->putMove(IBoard::PositionXY(4, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternOnHorizontalTrendTest5)
{
    // a. Precondition:
    //						   1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . x . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 8), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b. Action:
    //						   1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . x . x x . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    m_board->putMove(IBoard::PositionXY(2, 9), IBoard::PLAYER_A);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 8), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 9), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternOnHorizontalTrendTest6)
{
    // a. Precondition:
    //						   1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . . x x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 8), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b. Action:
    //						   1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . x x x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 8), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternOnHorizontalTrendTest7)
{
    // a. Precondition:
    //						   1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x x . . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 8), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    // b. Action:
    //						   1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x x x . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 8), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternOnHorizontalTrendTest8)
{
    // a. Precondition:
    //						   1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x x x o . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_B);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternOnHorizontalTrendTest9)
{
    // a. Precondition:
    //						   1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x x x . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_B);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternAbuttedToBoardTest1)
{
    // Testing abutted to frame: ..XXX.
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 2), ThreatFinder::RISING, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::RISING, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(5, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternAbuttedToBoardTest2)
{
    // Testing abutted to frame: .X.XX.
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 1), ThreatFinder::RISING, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::RISING, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(5, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternAbuttedToBoardTest3)
{
    // Testing abutted to frame: .XX.X.
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 1), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(5, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 4), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternAbuttedToBoardTest4)
{
    // Testing abutted to frame: .XXX..
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 1), ThreatFinder::RISING, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(5, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 3), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(5, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternInTheMiddleTest1)
{
    // Testing in the middle: OXXX..
    m_board->putMove(IBoard::PositionXY(4, 0), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 3), IBoard::PLAYER_A);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternInTheMiddleTest2)
{
    // Testing in the middle: O.XXX.O
    m_board->putMove(IBoard::PositionXY(4, 0), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(4, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 6), IBoard::PLAYER_B);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternInTheMiddleTest3)
{
    // Testing in the middle: O.XXX..O
    m_board->putMove(IBoard::PositionXY(4, 0), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(4, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 7), IBoard::PLAYER_B);

    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternSixInRow1)
{
    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 8), IBoard::PLAYER_A);

    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 8), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternSixInRow2)
{
    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(3, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(3, 4), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(3, 6), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(3, 8), IBoard::PLAYER_B);

    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 8), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
}

TEST_F(Threat3CaseATest, FindPatternSixInRow3)
{
    //						   1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. . . . x . . x x x . o . . .|
    //	4 |. . . . . . . . . . . . . . .|
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

    m_board->putMove(IBoard::PositionXY(3, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 7), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 8), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 9), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 11), IBoard::PLAYER_B);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, FindPatternSixInRow4)
{
    //						   1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x x x . x . . . . . . . . .|
    //	3 |. x x x . . x . . . . . . . .|
    //	4 |. x x x . . o . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|

    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 6), IBoard::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));

    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 6), IBoard::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
}

TEST_F(Threat3CaseATest, ThreatUpDetalisAsterisesTest1)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . x x x . . . . . . x x x .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . x . . . . . o . . . .|
    // 4 |. . . x . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . o . .|
    // 6 |. x . . . . . . . . . . . o .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . o . . . .|
    // 11|. . . x . . . . . . . . . . .|
    // 12|. . x . . . . . . . . . o . .|
    // 13|. x . . . . . . . . . . . o .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    ThreatFinder::ThreatUpDetails threatUpDetails;

    // For now cant see the reason for this test. * seems to not have usage.
    // Continue this test if needed.

    m_board->putMove(IBoard::PositionXY(0, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(0, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(0, 4), IBoard::PLAYER_A);

    m_board->putMove(IBoard::PositionXY(0, 11), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(0, 12), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(0, 13), IBoard::PLAYER_A);

    m_board->putMove(IBoard::PositionXY(3, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(6, 1), IBoard::PLAYER_A);

    m_board->putMove(IBoard::PositionXY(3, 10), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(5, 12), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(6, 13), IBoard::PLAYER_B);

    m_board->putMove(IBoard::PositionXY(11, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(12, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(13, 1), IBoard::PLAYER_A);

    m_board->putMove(IBoard::PositionXY(11, 11), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(12, 12), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(13, 13), IBoard::PLAYER_B);
}

TEST_F(Threat3CaseATest, GetPieces1)
{
    // .xxx..*
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. x x x . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 6);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    //    Normal: .xxx..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.xxx..
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

TEST_F(Threat3CaseATest, GetPieces2)
{
    // |.xx.x.*
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. x x . x . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 6);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);

    m_threatFinder->findThreatPattern(elX3, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    //    Normal: .xxx..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.xxx..
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

TEST_F(Threat3CaseATest, GetPieces3)
{
    // *.x.xx.|
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . x . x x .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix2   = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 9);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 11);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 14);
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 10);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 12);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 13);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 14);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);

    m_threatFinder->findThreatPattern(elX3, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    //    Normal: .xxx..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.xxx..
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

TEST_F(Threat3CaseATest, GetPieces4)
{
    // *..xxx..*
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . x x x . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 10);
    const IBoard::PositionXY elAsterix2   = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 9);
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(1, 8);
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(1, 9);
    const IBoard::PositionXY elExtendGap2 = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 7);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 10);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);

    m_threatFinder->findThreatPattern(elX3, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    //    Normal: .xxx..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.xxx..
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

TEST_F(Threat3CaseATest, GetPieces5)
{
    // |.x.xx.*o
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. x . x x . . o . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(1, 6);
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(1, 2);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(1, 5);
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 1);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 3);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
    const IBoard::PositionXY end          = IBoard::PositionXY(1, 6);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);

    m_threatFinder->findThreatPattern(elX3, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    //    Normal: .xxx..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.xxx..
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

TEST_F(Threat3CaseATest, GetPieces6)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
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
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(5, 0);
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(0, 5);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(1, 4);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(5, 0);
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = IBoard::PositionXY(0, 5);
    const IBoard::PositionXY elX1         = IBoard::PositionXY(2, 3);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(3, 2);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(4, 1);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 5);
    const IBoard::PositionXY end          = IBoard::PositionXY(5, 0);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);

    m_threatFinder->findThreatPattern(elX3, ThreatFinder::RISING, IBoard::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    //    Normal: .xxx..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.xxx..
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

TEST_F(Threat3CaseATest, GetPieces7)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . x . . . .|
    // 2 |. . . . . . . . . . . x . . .|
    // 3 |. . . . . . . . . . . . x . .|
    // 4 |. . . . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(0, 9);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(4, 13);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(5, 14);
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(0, 9);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(4, 13);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(5, 14);
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = IBoard::PositionXY(5, 14);
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 10);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(2, 11);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(3, 12);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 9);
    const IBoard::PositionXY end          = IBoard::PositionXY(5, 14);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);

    m_threatFinder->findThreatPattern(elX3, ThreatFinder::FALLING, IBoard::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    //    Normal: .xxx..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.xxx..
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

TEST_F(Threat3CaseATest, GetPieces8)
{
    // This the case where threat begins at (0, 13) and ends at (6, 7).
    // Only symmetric side exists (see that we start at 2,11)

    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . * .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . x . . .|
    // 3 |. . . . . . . . . . . . . . .|
    // 4 |. . . . . . . . . x . . . . .|
    // 5 |. . . . . . . . x . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . x . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elAsterix2   = IBoard::PositionXY(0, 13);
    const IBoard::PositionXY elGap1       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = IBoard::PositionXY(1, 12);
    const IBoard::PositionXY elGap7       = IBoard::PositionXY(3, 10);
    const IBoard::PositionXY elGap8       = IBoard::PositionXY(6, 7);
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(2, 11);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(4, 9);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(5, 8);
    const IBoard::PositionXY X4           = IBoard::PositionXY(7, 6);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 13);
    const IBoard::PositionXY end          = IBoard::PositionXY(6, 7);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_board->putMove(X4, IBoard::PLAYER_A);

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
    ASSERT_TRUE(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    //    Normal: .xxx..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.xxx..
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

TEST_F(Threat3CaseATest, GetPieces9)
{
    // This the case where threat begins at (0, 13) and ends at (6, 7).
    // Only symmetric side exists (see that we start at 2,11)

    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . x . . .|
    // 3 |. . . . . . . . . . . . . . .|
    // 4 |. . . . . . . . . x . . . . .|
    // 5 |. . . . . . . . x . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . x . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . * . . . . . . . . . .|

    // 0. Define expectation.
    const IBoard::PositionXY elAsterix1   = IBoard::PositionXY(9, 4);
    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap1       = IBoard::PositionXY(3, 10);
    const IBoard::PositionXY elGap2       = IBoard::PositionXY(6, 7);
    const IBoard::PositionXY elGap3       = IBoard::PositionXY(8, 5);
    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elX1         = IBoard::PositionXY(4, 9);
    const IBoard::PositionXY elX2         = IBoard::PositionXY(5, 8);
    const IBoard::PositionXY elX3         = IBoard::PositionXY(7, 6);
    const IBoard::PositionXY X4           = IBoard::PositionXY(2, 11);
    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const IBoard::PositionXY beginning    = IBoard::PositionXY(3, 10);
    const IBoard::PositionXY end          = IBoard::PositionXY(9, 4);

    // 1. Create a threat.
    m_board->putMove(elX1, IBoard::PLAYER_A);
    m_board->putMove(elX2, IBoard::PLAYER_A);
    m_board->putMove(elX3, IBoard::PLAYER_A);
    m_board->putMove(X4, IBoard::PLAYER_A);

    m_threatFinder->findThreatPattern(elX3, ThreatFinder::RISING, IBoard::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[3]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    //    Normal: .xxx..*
    ASSERT_TRUE(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    ASSERT_TRUE(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    ASSERT_TRUE(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    ASSERT_TRUE(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    ASSERT_TRUE(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);

    //    Symmetric: *.xxx..
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
