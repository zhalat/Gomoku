#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Board.h"
#include "GomokuBoard.h"
#include "Threats/Threat4CaseB.h"

class Threat4CaseBTest : public ::testing::Test
{
    void SetUp()
    {
        m_board = new GomokuBoard(15);
        m_threatFinder = new Threat4CaseB();
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

TEST_F(Threat4CaseBTest, FindThreatFourPatternHorizontalTrend1Test)
{
    // step by step build OX.XXX and verify if pattern is found.

    // a:   .X....
    m_board->putMove(Board::PositionXY(4, 4), Board::PLAYER_A);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // b:   OX....
    m_board->putMove(Board::PositionXY(4, 3), Board::PLAYER_B);
    // no action due to opponent move

    // c:   OX.X..
    m_board->putMove(Board::PositionXY(4, 6), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // d:   OX.XX.
    m_board->putMove(Board::PositionXY(4, 7), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // e:   OX.XXX. - now pattern is completed.
    m_board->putMove(Board::PositionXY(4, 8), Board::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 8), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // f:   OX.XXXX. - now pattern is completed.
    m_board->putMove(Board::PositionXY(4, 9), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 9), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 8), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
}

TEST_F(Threat4CaseBTest, FindThreatFourPatternHorizontalTrend2Test)
{
    // step by step build XOOOO. and verify if pattern is founded.

    // a:   .O....
    m_board->putMove(Board::PositionXY(0, 5), Board::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_B));

    // b:   XO....
    m_board->putMove(Board::PositionXY(0, 4), Board::PLAYER_A);
    // no action due to opponent move

    // c:   XOO...
    m_board->putMove(Board::PositionXY(0, 6), Board::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_B));

    // d:   XOOO..
    m_board->putMove(Board::PositionXY(0, 7), Board::PLAYER_B);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_B));

    // e:   XOOOO. - now pattern is completed.
    m_board->putMove(Board::PositionXY(0, 8), Board::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 8), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
}

TEST_F(Threat4CaseBTest, FindThreatFourPatternHorizontalTrend3Test)
{
    // .XX.X.
    m_board->putMove(Board::PositionXY(0, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(0, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(0, 6), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // OXX.XX.
    m_board->putMove(Board::PositionXY(0, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(0, 7), Board::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // O.XX.X.
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 7), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 5), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // OXXX.X.
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // XX.X.OXXX..
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 9), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 10), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(2, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // XX.X.OXXXX.
    m_board->putMove(Board::PositionXY(2, 11), Board::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(2, 11), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // OX..XXO
    m_board->putMove(Board::PositionXY(3, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(3, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 7), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 8), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(3, 3), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // OXX.XXO
    m_board->putMove(Board::PositionXY(3, 4), Board::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
}

TEST_F(Threat4CaseBTest, FindThreatFourPatternAbuttedToBoardFrame1Test)
{
    // Prepare state where four pattern is exactly sticking to board frame.
    // XXX.X0(board frame)
    m_board->putMove(Board::PositionXY(1, 9), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 10), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 11), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 13), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 14), Board::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 10), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // Prepare state where four pattern is exactly sticking to board frame.
    // (board frame)XXX.X0
    m_board->putMove(Board::PositionXY(1, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 5), Board::PLAYER_B);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(1, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
}

TEST_F(Threat4CaseBTest, FindThreatFourPatternAbuttedToBoardFrame2Test)
{
    // Prepare state where four pattern is exactly sticking to board frame and frame board is considered as opposite
    // player. (board frame)XXXX.
    m_board->putMove(Board::PositionXY(0, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 3), Board::PLAYER_A);
    ASSERT_TRUE(
        m_threatFinder->findThreatPattern(Board::PositionXY(0, 0), ThreatFinder::FALLING, Board::PLAYER_A));  // begin
    ASSERT_TRUE(
        m_threatFinder->findThreatPattern(Board::PositionXY(2, 2), ThreatFinder::FALLING, Board::PLAYER_A));  // middle
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::FALLING,
                                                  Board::PLAYER_A));  // before end

    // Do the same but symmetrical.
    // .XXXX(board frame)
    m_board->putMove(Board::PositionXY(11, 11), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(12, 12), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(13, 13), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(14, 14), Board::PLAYER_A);
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(11, 11), ThreatFinder::FALLING,
                                                  Board::PLAYER_A));  // begin
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(12, 12), ThreatFinder::FALLING,
                                                  Board::PLAYER_A));  // middle
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(14, 14), ThreatFinder::FALLING,
                                                  Board::PLAYER_A));  // before end
}

TEST_F(Threat4CaseBTest, FindThreatFourPatternAbuttedToBoardFrame3Test)
{
    // Prepare state where four pattern is exactly sticking to board frame and frame board is considered as opposite
    // player. O.XXXX(board frame)
    m_board->putMove(Board::PositionXY(0, 14), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 13), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 12), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 11), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(5, 9), Board::PLAYER_B);
    ASSERT_TRUE(
        m_threatFinder->findThreatPattern(Board::PositionXY(0, 14), ThreatFinder::RISING, Board::PLAYER_A));  // begin
    ASSERT_TRUE(
        m_threatFinder->findThreatPattern(Board::PositionXY(1, 13), ThreatFinder::RISING, Board::PLAYER_A));  // middle
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 11), ThreatFinder::RISING,
                                                  Board::PLAYER_A));  // before end

    // Do the same but symmetrical.
    // (board frame)XXXX.O
    m_board->putMove(Board::PositionXY(14, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(13, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(12, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(11, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(9, 5), Board::PLAYER_B);
    ASSERT_TRUE(
        m_threatFinder->findThreatPattern(Board::PositionXY(14, 0), ThreatFinder::RISING, Board::PLAYER_A));  // begin
    ASSERT_TRUE(
        m_threatFinder->findThreatPattern(Board::PositionXY(13, 1), ThreatFinder::RISING, Board::PLAYER_A));  // middle
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(11, 3), ThreatFinder::RISING,
                                                  Board::PLAYER_A));  // before end
}

TEST_F(Threat4CaseBTest, FindThreatFourPatternAbuttedToBoardFrame4Test)
{
    // Prepare state where four pattern is exactly sticking to board frame and frame board is considered as opposite
    // player. (board frame).XXXXO
    m_board->putMove(Board::PositionXY(1, 13), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 12), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 11), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 10), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(5, 9), Board::PLAYER_B);
    ASSERT_TRUE(
        m_threatFinder->findThreatPattern(Board::PositionXY(1, 13), ThreatFinder::RISING, Board::PLAYER_A));  // begin
    ASSERT_TRUE(
        m_threatFinder->findThreatPattern(Board::PositionXY(3, 11), ThreatFinder::RISING, Board::PLAYER_A));  // middle
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 10), ThreatFinder::RISING,
                                                  Board::PLAYER_A));  // before end

    // Do the same but symmetrical.
    // (board frame).XXXXO
    m_board->putMove(Board::PositionXY(13, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(12, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(11, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(10, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(9, 5), Board::PLAYER_B);
    ASSERT_TRUE(
        m_threatFinder->findThreatPattern(Board::PositionXY(13, 1), ThreatFinder::RISING, Board::PLAYER_A));  // begin
    ASSERT_TRUE(
        m_threatFinder->findThreatPattern(Board::PositionXY(11, 3), ThreatFinder::RISING, Board::PLAYER_A));  // middle
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(10, 4), ThreatFinder::RISING,
                                                  Board::PLAYER_A));  // before end
}

TEST_F(Threat4CaseBTest, FindThreatFourPatternAbuttedToBoardFrame5Test)
{
    // Prepare state where four pattern is exactly sticking to board frame and frame board is considered as opposite
    // player. OXXXX(board frame).
    m_board->putMove(Board::PositionXY(10, 10), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(11, 11), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(12, 12), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(13, 13), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(14, 14), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(11, 11), ThreatFinder::FALLING,
                                                   Board::PLAYER_A));  // begin
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(12, 12), ThreatFinder::FALLING,
                                                   Board::PLAYER_A));  // middle
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(14, 14), ThreatFinder::FALLING,
                                                   Board::PLAYER_A));  // before end

    // (board frame)XXXXO.
    m_board->putMove(Board::PositionXY(0, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 4), Board::PLAYER_B);
    ASSERT_FALSE(
        m_threatFinder->findThreatPattern(Board::PositionXY(0, 0), ThreatFinder::FALLING, Board::PLAYER_A));  // begin
    ASSERT_FALSE(
        m_threatFinder->findThreatPattern(Board::PositionXY(2, 2), ThreatFinder::FALLING, Board::PLAYER_A));  // middle
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(4, 4), ThreatFinder::FALLING,
                                                   Board::PLAYER_A));  // before end
}

TEST_F(Threat4CaseBTest, FindThreatFourPatternAbuttedToBoardFrame6Test)
{
    // (frame)XXXX(frame)
    m_board->putMove(Board::PositionXY(3, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(0, 3), Board::PLAYER_A);
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(2, 1), ThreatFinder::RISING, Board::PLAYER_A));
}

TEST_F(Threat4CaseBTest, FindThreatSixInRowTest1)
{
    // a:   .O....
    m_board->putMove(Board::PositionXY(0, 5), Board::PLAYER_B);
    // b:   XO....
    m_board->putMove(Board::PositionXY(0, 4), Board::PLAYER_A);
    // c:   XOO...
    m_board->putMove(Board::PositionXY(0, 6), Board::PLAYER_B);
    // d:   XOOO..
    m_board->putMove(Board::PositionXY(0, 7), Board::PLAYER_B);
    // e:   XOOOO. - now pattern is completed.
    m_board->putMove(Board::PositionXY(0, 8), Board::PLAYER_B);
    // f:   XOOOO.O - six in row.
    m_board->putMove(Board::PositionXY(0, 10), Board::PLAYER_B);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(0, 8), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    ASSERT_FALSE(
        m_threatFinder->findThreatPattern(Board::PositionXY(0, 10), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
}

TEST_F(Threat4CaseBTest, FindThreatFourPatternMixTrendTest)
{
    // some complicated situations.
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 5), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(3, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 6), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(4, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(5, 4), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(5, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(5, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(6, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(6, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(6, 6), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(6, 7), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(7, 2), Board::PLAYER_A);

    // Check situation form (6,2) position.
#warning "TODO: 6 pawns in row are improperly handled. This probably should be recognized by PostConditionConstrain()."
    // ASSERT_FALSE( m_threatFinder->findThreatPattern( Board::PositionXY( 6, 2 ), ThreatFinder::VERTICAL,
    // Board::PLAYER_A ) );
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(6, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(6, 2), ThreatFinder::RISING, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(6, 2), ThreatFinder::FALLING, Board::PLAYER_A));

    // Check situation form (3,3) position.
    m_board->putMove(Board::PositionXY(3, 3), Board::PLAYER_A);

    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::VERTICAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::RISING, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::FALLING, Board::PLAYER_A));

    // Change a little bit situation.
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_B);

    // Again check situation form (3,3) position.
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::VERTICAL, Board::PLAYER_A));
    ASSERT_TRUE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::RISING, Board::PLAYER_A));
    ASSERT_FALSE(m_threatFinder->findThreatPattern(Board::PositionXY(3, 3), ThreatFinder::FALLING, Board::PLAYER_A));
}

TEST_F(Threat4CaseBTest, GetPieces1)
{
    // oxxx.x*
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . o x x x . x . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = Board::PositionXY(1, 10);
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(1, 8);
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
    const Board::PositionXY elX1         = Board::PositionXY(1, 5);
    const Board::PositionXY elX2         = Board::PositionXY(1, 6);
    const Board::PositionXY elX3         = Board::PositionXY(1, 7);
    const Board::PositionXY elX4         = Board::PositionXY(1, 9);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = Board::PositionXY(1, 4);
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(1, 4);
    const Board::PositionXY end          = Board::PositionXY(1, 10);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elO1, Board::PLAYER_B);
    m_threatFinder->findThreatPattern(elX4, ThreatFinder::HORIZONTAL, Board::PLAYER_A);

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

TEST_F(Threat4CaseBTest, GetPieces2)
{
    // oxx..xo
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . o x x x . x o . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = Board::PositionXY(1, 10);
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(1, 8);
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
    const Board::PositionXY elX1         = Board::PositionXY(1, 5);
    const Board::PositionXY elX2         = Board::PositionXY(1, 6);
    const Board::PositionXY elX3         = Board::PositionXY(1, 7);
    const Board::PositionXY elX4         = Board::PositionXY(1, 9);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = Board::PositionXY(1, 4);
    const Board::PositionXY elO2         = Board::PositionXY(1, 10);
    const Board::PositionXY beginning    = Board::PositionXY(1, 4);
    const Board::PositionXY end          = Board::PositionXY(1, 10);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elO1, Board::PLAYER_B);
    m_board->putMove(elO2, Board::PLAYER_B);
    m_threatFinder->findThreatPattern(elX3, ThreatFinder::HORIZONTAL, Board::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat4CaseBTest, GetPieces3)
{
    // |xxx.x*
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |x x x . x * . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = Board::PositionXY(1, 5);
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(1, 3);
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
    const Board::PositionXY elX4         = Board::PositionXY(1, 4);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(1, 0);
    const Board::PositionXY end          = Board::PositionXY(1, 5);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_threatFinder->findThreatPattern(elX3, ThreatFinder::HORIZONTAL, Board::PLAYER_A);

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

TEST_F(Threat4CaseBTest, GetPieces4)
{
    // |xxx.xo
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |x x x . x o . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = Board::PositionXY(1, 5);
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(1, 3);
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
    const Board::PositionXY elX4         = Board::PositionXY(1, 4);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = Board::PositionXY(1, 5);
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(1, 0);
    const Board::PositionXY end          = Board::PositionXY(1, 5);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elO1, Board::PLAYER_B);
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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat4CaseBTest, GetPieces5)
{
    // |x.xxx|
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . x . . . . . . . . . .|
    // 1 |. . . x . . . . . . . . . . .|
    // 2 |. . x . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|
    // 4 |x . . . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(3, 1);
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
    const Board::PositionXY elX4         = Board::PositionXY(4, 0);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(0, 4);
    const Board::PositionXY end          = Board::PositionXY(4, 0);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_threatFinder->findThreatPattern(elX4, ThreatFinder::RISING, Board::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[0]);
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat4CaseBTest, GetPieces6)
{
    // |.xxxxo
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . x . . . .|
    // 2 |. . . . . . . . . . . x . . .|
    // 3 |. . . . . . . . . . . . x . .|
    // 4 |. . . . . . . . . . . . . x .|
    // 5 |. . . . . . . . . . . . . . o|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(0, 9);
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
    const Board::PositionXY elX2         = Board::PositionXY(2, 11);
    const Board::PositionXY elX3         = Board::PositionXY(3, 12);
    const Board::PositionXY elX4         = Board::PositionXY(4, 13);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = Board::PositionXY(5, 14);
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(0, 9);
    const Board::PositionXY end          = Board::PositionXY(5, 14);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elO1, Board::PLAYER_B);
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::FALLING, Board::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST_F(Threat4CaseBTest, GetPieces7)
{
    //  *xx.xxo
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . x x . x x o . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|
    // 4 |. . . . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = Board::PositionXY(1, 3);
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(1, 6);
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
    const Board::PositionXY elX3         = Board::PositionXY(1, 7);
    const Board::PositionXY elX4         = Board::PositionXY(1, 8);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = Board::PositionXY(1, 9);
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(1, 3);
    const Board::PositionXY end          = Board::PositionXY(1, 9);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elO1, Board::PLAYER_B);
    m_threatFinder->findThreatPattern(elX4, ThreatFinder::HORIZONTAL, Board::PLAYER_A);

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
    ASSERT_TRUE(ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    ASSERT_TRUE(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    ASSERT_TRUE(end == threatLocation.m_threatDetails.m_endThreat);
}
