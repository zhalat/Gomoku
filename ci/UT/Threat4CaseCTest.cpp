#include "Board.hpp"  // for Board definitions.
#include "Threat4CaseC.hpp"
#include "GomokuBoard.hpp"
#include <assert.h>  // for assert.
//----------------------------------------------------------
#include "CppUTest/TestHarness.h"
#include "CppUTest/SimpleString.h"
#include "CppUTest/PlatformSpecificFunctions.h"
#include "CppUTest/TestMemoryAllocator.h"
#include "CppUTest/MemoryLeakDetector.h"

TEST_GROUP(Threat4CaseCTest)
{
    void setup()
    {
        m_board = new GomokuBoard(15);

        m_threatFinder = new Threat4CaseC();
        m_threatFinder->SetBoard(m_board);
    }

    void teardown()
    {
        delete m_board;
        delete m_threatFinder;
    }

   public:
    GomokuBoard* m_board;
    ThreatFinder* m_threatFinder;
};

TEST(Threat4CaseCTest, FindPatternOnHorizontalTrendTest1)
{
    // step by step build OXX.XXO and verify if pattern is found.

    // a:   .X.....
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // b:   .XX....
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // c:   .XX.X..
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // d:   .XX.XX.
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // e:   OXX.XX.
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    // e:   OXX.XXO
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(2, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(2, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(2, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(2, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
}

TEST(Threat4CaseCTest, FindPatternOnHorizontalTrendTest2)
{
    // Check each pattern variations:
    // OXXXX.O
    // OXXX.XO
    // OXX.XXO
    // OX.XXXO
    // O.XXXXO
    m_board->putMove(Board::PositionXY(0, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(0, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(0, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(0, 4), Board::PLAYER_A);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(0, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(0, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(0, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(0, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    m_board->putMove(Board::PositionXY(0, 0), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(0, 6), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(0, 0), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(0, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(0, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(0, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(0, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(0, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 0), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 6), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 0), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(2, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    m_board->putMove(Board::PositionXY(3, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 0), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(3, 6), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(3, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));

    m_board->putMove(Board::PositionXY(4, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 0), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(4, 6), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(4, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
}

TEST(Threat4CaseCTest, FindPatternAbuttedToBoardFrameTest1)
{
    //(frame)XXXX(frame)
    m_board->putMove(Board::PositionXY(3, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(0, 3), Board::PLAYER_A);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(3, 0), ThreatFinder::RISING, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 1), ThreatFinder::RISING, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::RISING, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(0, 3), ThreatFinder::RISING, Board::PLAYER_A));

    // (frame)XXX.X(frame)
    m_board->putMove(Board::PositionXY(4, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(0, 4), Board::PLAYER_A);
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(3, 1), ThreatFinder::RISING, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(2, 2), ThreatFinder::RISING, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(0, 4), ThreatFinder::RISING, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(4, 0), ThreatFinder::RISING, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(0, 4), ThreatFinder::RISING, Board::PLAYER_A));

    // (frame)XXXX.(frame)
    m_board->putMove(Board::PositionXY(14, 10), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(13, 11), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(12, 12), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(11, 13), Board::PLAYER_A);
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(14, 10), ThreatFinder::RISING, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(13, 11), ThreatFinder::RISING, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(12, 12), ThreatFinder::RISING, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(11, 13), ThreatFinder::RISING, Board::PLAYER_A));
}

TEST(Threat4CaseCTest, FindPatternAbuttedToBoardFrameTest2)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . o . . .|
    // 1 |. . . . . . . . . . . o o . .|
    // 2 |. . . . . . . . . . . . o o .|
    // 3 |. . . . . . . . . . . . . o o|
    // 4 |. . . . . . . . . . . . . . o|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|o o o o . . . . . . . . . . .|
    // 11|o o o o x . . . . . . . . . .|
    // 12|. o o o o x . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    //(frame)OOOO(frame)
    m_board->putMove(Board::PositionXY(0, 11), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 12), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 13), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(3, 14), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(0, 11), ThreatFinder::FALLING, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(1, 12), ThreatFinder::FALLING, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(2, 13), ThreatFinder::FALLING, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(3, 14), ThreatFinder::FALLING, Board::PLAYER_B));

    //(frame).OOOO(frame)
    m_board->putMove(Board::PositionXY(1, 11), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 12), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(3, 13), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(4, 14), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(1, 11), ThreatFinder::FALLING, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(2, 12), ThreatFinder::FALLING, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(3, 13), ThreatFinder::FALLING, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(4, 14), ThreatFinder::FALLING, Board::PLAYER_B));

    //(frame)OOOO.
    m_board->putMove(Board::PositionXY(10, 0), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(10, 1), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(10, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(10, 3), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(10, 0), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(10, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(10, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(10, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_B));

    //(frame)OOOO.
    m_board->putMove(Board::PositionXY(11, 0), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(11, 1), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(11, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(11, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(11, 4), Board::PLAYER_A);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(11, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(11, 0), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(11, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(11, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(11, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_B));

    //(frame).OOOOX
    m_board->putMove(Board::PositionXY(12, 1), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(12, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(12, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(12, 4), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(12, 5), Board::PLAYER_A);
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(12, 1), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(12, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(12, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        true, m_threatFinder->findThreatPattern(Board::PositionXY(12, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(12, 5), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
}

TEST(Threat4CaseCTest, FindPatternAbuttedToBoardFrameTest3)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|
    // 4 |. . . . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . x . . . .|
    // 11|. . . . . . . . . . . o . . .|
    // 12|. . . . . . . . . . . . o . .|
    // 13|. . . . . . . . . . . . . o .|
    // 14|. . . . . . . . . . . . . . o|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    m_board->putMove(Board::PositionXY(10, 10), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(11, 11), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(12, 12), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(13, 13), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(14, 14), Board::PLAYER_B);
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(11, 11), ThreatFinder::FALLING, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(12, 12), ThreatFinder::FALLING, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(13, 13), ThreatFinder::FALLING, Board::PLAYER_B));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(14, 14), ThreatFinder::FALLING, Board::PLAYER_B));
}

TEST(Threat4CaseCTest, CheckingAgainstSixInRowTest1)
{
    // OXXX.XXO
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 7), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 8), Board::PLAYER_B);

    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(1, 2), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(1, 3), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(1, 4), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(1, 6), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
    CPPUNIT_ASSERT_EQUAL(
        false, m_threatFinder->findThreatPattern(Board::PositionXY(1, 7), ThreatFinder::HORIZONTAL, Board::PLAYER_A));
}

TEST(Threat4CaseCTest, GetPieces1)
{
    // oxxxx.o
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |o x x x x . o . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(1, 5);
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
    const Board::PositionXY elX1         = Board::PositionXY(1, 1);
    const Board::PositionXY elX2         = Board::PositionXY(1, 2);
    const Board::PositionXY elX3         = Board::PositionXY(1, 3);
    const Board::PositionXY elX4         = Board::PositionXY(1, 4);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = Board::PositionXY(1, 0);
    const Board::PositionXY elO2         = Board::PositionXY(1, 6);
    const Board::PositionXY beginning    = Board::PositionXY(1, 0);
    const Board::PositionXY end          = Board::PositionXY(1, 6);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elO1, Board::PLAYER_B);
    m_board->putMove(elO2, Board::PLAYER_B);
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::HORIZONTAL, Board::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST(Threat4CaseCTest, GetPieces2)
{
    // |.xxx.o
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. x x x x o . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(1, 0);
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
    const Board::PositionXY elX1         = Board::PositionXY(1, 1);
    const Board::PositionXY elX2         = Board::PositionXY(1, 2);
    const Board::PositionXY elX3         = Board::PositionXY(1, 3);
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
    m_threatFinder->findThreatPattern(elX2, ThreatFinder::HORIZONTAL, Board::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST(Threat4CaseCTest, GetPieces3)
{
    // oxx.xx|
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . o x x . x x|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(1, 12);
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
    const Board::PositionXY elX3         = Board::PositionXY(1, 13);
    const Board::PositionXY elX4         = Board::PositionXY(1, 14);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = Board::PositionXY(1, 9);
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(1, 9);
    const Board::PositionXY end          = Board::PositionXY(1, 14);

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
    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST(Threat4CaseCTest, GetPieces4)
{
    // ox.xxxo
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . o x . x x x o . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(1, 5);
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
    const Board::PositionXY elX2         = Board::PositionXY(1, 6);
    const Board::PositionXY elX3         = Board::PositionXY(1, 7);
    const Board::PositionXY elX4         = Board::PositionXY(1, 8);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = Board::PositionXY(1, 3);
    const Board::PositionXY elO2         = Board::PositionXY(1, 9);
    const Board::PositionXY beginning    = Board::PositionXY(1, 3);
    const Board::PositionXY end          = Board::PositionXY(1, 9);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_board->putMove(elO1, Board::PLAYER_B);
    m_board->putMove(elO2, Board::PLAYER_B);
    m_threatFinder->findThreatPattern(elX1, ThreatFinder::HORIZONTAL, Board::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST(Threat4CaseCTest, GetPieces5)
{
    // |xxxx.|
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . x . . . . . . . . . .|
    // 1 |. . . x . . . . . . . . . . .|
    // 2 |. . x . . . . . . . . . . . .|
    // 3 |. x . . . . . . . . . . . . .|
    // 4 |. . . . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(4, 0);
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

    m_threatFinder->findThreatPattern(elX2, ThreatFinder::RISING, Board::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
}

TEST(Threat4CaseCTest, GetPieces6)
{
    // |xx.xx|
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . x . . . .|
    // 1 |. . . . . . . . . . . x . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . x .|
    // 4 |. . . . . . . . . . . . . . x|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|

    // 0. Define expectation.
    const Board::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elGap1       = Board::PositionXY(2, 12);
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
    const Board::PositionXY elX1         = Board::PositionXY(0, 10);
    const Board::PositionXY elX2         = Board::PositionXY(1, 11);
    const Board::PositionXY elX3         = Board::PositionXY(3, 13);
    const Board::PositionXY elX4         = Board::PositionXY(4, 14);
    const Board::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    const Board::PositionXY beginning    = Board::PositionXY(0, 10);
    const Board::PositionXY end          = Board::PositionXY(4, 14);

    // 1. Create a threat.
    m_board->putMove(elX1, Board::PLAYER_A);
    m_board->putMove(elX2, Board::PLAYER_A);
    m_board->putMove(elX3, Board::PLAYER_A);
    m_board->putMove(elX4, Board::PLAYER_A);
    m_threatFinder->findThreatPattern(elX4, ThreatFinder::FALLING, Board::PLAYER_A);

    // 2. Get elements.
    ThreatFinder::ThreatLocation threatLocation;
    m_threatFinder->getThreatFields(threatLocation);

    // 3. Make verification.
    // a. Check '*':
    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);

    // b. Check 'x':
    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);

    // c. Check '.':
    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);

    // d. Extend gaps:
    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);

    // d. Check 'o':
    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);

    // e. Check begin & end:
    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
}
