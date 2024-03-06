//#include "IBoard.hpp"  // for IBoard definitions.
//#include "Threat4CaseC.hpp"
//#include "GomokuBoard.hpp"
//#include <assert.h>  // for assert.
////----------------------------------------------------------
//#include "CppUTest/TestHarness.h"
//#include "CppUTest/SimpleString.h"
//#include "CppUTest/PlatformSpecificFunctions.h"
//#include "CppUTest/TestMemoryAllocator.h"
//#include "CppUTest/MemoryLeakDetector.h"
//
//TEST_GROUP(Threat4CaseCTest)
//{
//    void setup()
//    {
//        m_board = new GomokuBoard(15);
//
//        m_threatFinder = new Threat4CaseC();
//        m_threatFinder->setBoard(m_board);
//    }
//
//    void teardown()
//    {
//        delete m_board;
//        delete m_threatFinder;
//    }
//
//   public:
//    GomokuBoard* m_board;
//    ThreatFinder* m_threatFinder;
//};
//
//TEST(Threat4CaseCTest, FindPatternOnHorizontalTrendTest1)
//{
//    // step by step build OXX.XXO and verify if pattern is found.
//
//    // a:   .X.....
//    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//
//    // b:   .XX....
//    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//
//    // c:   .XX.X..
//    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//
//    // d:   .XX.XX.
//    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//
//    // e:   OXX.XX.
//    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//
//    // e:   OXX.XXO
//    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//}
//
//TEST(Threat4CaseCTest, FindPatternOnHorizontalTrendTest2)
//{
//    // Check each pattern variations:
//    // OXXXX.O
//    // OXXX.XO
//    // OXX.XXO
//    // OX.XXXO
//    // O.XXXXO
//    m_board->putMove(IBoard::PositionXY(0, 1), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(0, 2), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(0, 3), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(0, 4), IBoard::PLAYER_A);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//
//    m_board->putMove(IBoard::PositionXY(0, 0), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(0, 6), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 0), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//
//    m_board->putMove(IBoard::PositionXY(1, 1), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(1, 0), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//
//    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(2, 0), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//
//    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(3, 3), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(3, 4), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(3, 5), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(3, 0), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(3, 6), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//
//    m_board->putMove(IBoard::PositionXY(4, 2), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(4, 3), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(4, 4), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(4, 5), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(4, 0), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(4, 6), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//}
//
//TEST(Threat4CaseCTest, FindPatternAbuttedToBoardFrameTest1)
//{
//    //(frame)XXXX(frame)
//    m_board->putMove(IBoard::PositionXY(3, 0), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(0, 3), IBoard::PLAYER_A);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 0), ThreatFinder::RISING, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 1), ThreatFinder::RISING, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 2), ThreatFinder::RISING, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 3), ThreatFinder::RISING, IBoard::PLAYER_A));
//
//    // (frame)XXX.X(frame)
//    m_board->putMove(IBoard::PositionXY(4, 0), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(0, 4), IBoard::PLAYER_A);
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 1), ThreatFinder::RISING, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 2), ThreatFinder::RISING, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 4), ThreatFinder::RISING, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 0), ThreatFinder::RISING, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 4), ThreatFinder::RISING, IBoard::PLAYER_A));
//
//    // (frame)XXXX.(frame)
//    m_board->putMove(IBoard::PositionXY(14, 10), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(13, 11), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(12, 12), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(11, 13), IBoard::PLAYER_A);
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(14, 10), ThreatFinder::RISING, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(13, 11), ThreatFinder::RISING, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(12, 12), ThreatFinder::RISING, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(11, 13), ThreatFinder::RISING, IBoard::PLAYER_A));
//}
//
//TEST(Threat4CaseCTest, FindPatternAbuttedToBoardFrameTest2)
//{
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . o . . .|
//    // 1 |. . . . . . . . . . . o o . .|
//    // 2 |. . . . . . . . . . . . o o .|
//    // 3 |. . . . . . . . . . . . . o o|
//    // 4 |. . . . . . . . . . . . . . o|
//    // 5 |. . . . . . . . . . . . . . .|
//    // 6 |. . . . . . . . . . . . . . .|
//    // 7 |. . . . . . . . . . . . . . .|
//    // 8 |. . . . . . . . . . . . . . .|
//    // 9 |. . . . . . . . . . . . . . .|
//    // 10|o o o o . . . . . . . . . . .|
//    // 11|o o o o x . . . . . . . . . .|
//    // 12|. o o o o x . . . . . . . . .|
//    // 13|. . . . . . . . . . . . . . .|
//    // 14|. . . . . . . . . . . . . . .|
//    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
//
//    //(frame)OOOO(frame)
//    m_board->putMove(IBoard::PositionXY(0, 11), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(1, 12), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(2, 13), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(3, 14), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(0, 11), ThreatFinder::FALLING, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 12), ThreatFinder::FALLING, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 13), ThreatFinder::FALLING, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 14), ThreatFinder::FALLING, IBoard::PLAYER_B));
//
//    //(frame).OOOO(frame)
//    m_board->putMove(IBoard::PositionXY(1, 11), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(2, 12), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(3, 13), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(4, 14), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 11), ThreatFinder::FALLING, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(2, 12), ThreatFinder::FALLING, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(3, 13), ThreatFinder::FALLING, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(4, 14), ThreatFinder::FALLING, IBoard::PLAYER_B));
//
//    //(frame)OOOO.
//    m_board->putMove(IBoard::PositionXY(10, 0), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(10, 1), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(10, 2), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(10, 3), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(10, 0), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(10, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(10, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(10, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//
//    //(frame)OOOO.
//    m_board->putMove(IBoard::PositionXY(11, 0), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(11, 1), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(11, 2), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(11, 3), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(11, 4), IBoard::PLAYER_A);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(11, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(11, 0), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(11, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(11, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(11, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//
//    //(frame).OOOOX
//    m_board->putMove(IBoard::PositionXY(12, 1), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(12, 2), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(12, 3), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(12, 4), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(12, 5), IBoard::PLAYER_A);
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(12, 1), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(12, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(12, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        true, m_threatFinder->findThreatPattern(IBoard::PositionXY(12, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(12, 5), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//}
//
//TEST(Threat4CaseCTest, FindPatternAbuttedToBoardFrameTest3)
//{
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . . . . .|
//    // 1 |. . . . . . . . . . . . . . .|
//    // 2 |. . . . . . . . . . . . . . .|
//    // 3 |. . . . . . . . . . . . . . .|
//    // 4 |. . . . . . . . . . . . . . .|
//    // 5 |. . . . . . . . . . . . . . .|
//    // 6 |. . . . . . . . . . . . . . .|
//    // 7 |. . . . . . . . . . . . . . .|
//    // 8 |. . . . . . . . . . . . . . .|
//    // 9 |. . . . . . . . . . . . . . .|
//    // 10|. . . . . . . . . . x . . . .|
//    // 11|. . . . . . . . . . . o . . .|
//    // 12|. . . . . . . . . . . . o . .|
//    // 13|. . . . . . . . . . . . . o .|
//    // 14|. . . . . . . . . . . . . . o|
//    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
//
//    m_board->putMove(IBoard::PositionXY(10, 10), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(11, 11), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(12, 12), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(13, 13), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(14, 14), IBoard::PLAYER_B);
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(11, 11), ThreatFinder::FALLING, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(12, 12), ThreatFinder::FALLING, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(13, 13), ThreatFinder::FALLING, IBoard::PLAYER_B));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(14, 14), ThreatFinder::FALLING, IBoard::PLAYER_B));
//}
//
//TEST(Threat4CaseCTest, CheckingAgainstSixInRowTest1)
//{
//    // OXXX.XXO
//    m_board->putMove(IBoard::PositionXY(1, 1), IBoard::PLAYER_B);
//    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(1, 6), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(1, 7), IBoard::PLAYER_A);
//    m_board->putMove(IBoard::PositionXY(1, 8), IBoard::PLAYER_B);
//
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 2), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 3), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 4), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 6), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//    CPPUNIT_ASSERT_EQUAL(
//        false, m_threatFinder->findThreatPattern(IBoard::PositionXY(1, 7), ThreatFinder::HORIZONTAL, IBoard::PLAYER_A));
//}
//
//TEST(Threat4CaseCTest, GetPieces1)
//{
//    // oxxxx.o
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . . . . .|
//    // 1 |o x x x x . o . . . . . . . .|
//    // 2 |. . . . . . . . . . . . . . .|
//    // 3 |. . . . . . . . . . . . . . .|
//
//    // 0. Define expectation.
//    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 5);
//    const IBoard::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 1);
//    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 2);
//    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 3);
//    const IBoard::PositionXY elX4         = IBoard::PositionXY(1, 4);
//    const IBoard::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elO1         = IBoard::PositionXY(1, 0);
//    const IBoard::PositionXY elO2         = IBoard::PositionXY(1, 6);
//    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
//    const IBoard::PositionXY end          = IBoard::PositionXY(1, 6);
//
//    // 1. Create a threat.
//    m_board->putMove(elX1, IBoard::PLAYER_A);
//    m_board->putMove(elX2, IBoard::PLAYER_A);
//    m_board->putMove(elX3, IBoard::PLAYER_A);
//    m_board->putMove(elX4, IBoard::PLAYER_A);
//    m_board->putMove(elO1, IBoard::PLAYER_B);
//    m_board->putMove(elO2, IBoard::PLAYER_B);
//    m_threatFinder->findThreatPattern(elX2, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);
//
//    // 2. Get elements.
//    ThreatFinder::ThreatLocation threatLocation;
//    m_threatFinder->getThreatFields(threatLocation);
//
//    // 3. Make verification.
//    // a. Check '*':
//    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
//    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);
//
//    // b. Check 'x':
//    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
//    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
//    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
//    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
//    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);
//
//    // c. Check '.':
//    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
//    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
//    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
//    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
//    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
//    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
//    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
//    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
//    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
//    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);
//
//    // d. Extend gaps:
//    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
//    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);
//
//    // d. Check 'o':
//    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
//    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);
//
//    // e. Check begin & end:
//    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
//    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
//}
//
//TEST(Threat4CaseCTest, GetPieces2)
//{
//    // |.xxx.o
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . . . . .|
//    // 1 |. x x x x o . . . . . . . . .|
//    // 2 |. . . . . . . . . . . . . . .|
//    // 3 |. . . . . . . . . . . . . . .|
//
//    // 0. Define expectation.
//    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 0);
//    const IBoard::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 1);
//    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 2);
//    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 3);
//    const IBoard::PositionXY elX4         = IBoard::PositionXY(1, 4);
//    const IBoard::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elO1         = IBoard::PositionXY(1, 5);
//    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 0);
//    const IBoard::PositionXY end          = IBoard::PositionXY(1, 5);
//
//    // 1. Create a threat.
//    m_board->putMove(elX1, IBoard::PLAYER_A);
//    m_board->putMove(elX2, IBoard::PLAYER_A);
//    m_board->putMove(elX3, IBoard::PLAYER_A);
//    m_board->putMove(elX4, IBoard::PLAYER_A);
//    m_board->putMove(elO1, IBoard::PLAYER_B);
//    m_threatFinder->findThreatPattern(elX2, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);
//
//    // 2. Get elements.
//    ThreatFinder::ThreatLocation threatLocation;
//    m_threatFinder->getThreatFields(threatLocation);
//
//    // 3. Make verification.
//    // a. Check '*':
//    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
//    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);
//
//    // b. Check 'x':
//    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
//    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
//    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
//    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
//    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);
//
//    // c. Check '.':
//    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
//    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
//    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
//    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
//    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
//    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
//    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
//    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
//    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
//    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);
//
//    // d. Extend gaps:
//    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
//    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);
//
//    // d. Check 'o':
//    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
//    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);
//
//    // e. Check begin & end:
//    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
//    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
//}
//
//TEST(Threat4CaseCTest, GetPieces3)
//{
//    // oxx.xx|
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . . . . .|
//    // 1 |. . . . . . . . . o x x . x x|
//    // 2 |. . . . . . . . . . . . . . .|
//    // 3 |. . . . . . . . . . . . . . .|
//
//    // 0. Define expectation.
//    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 12);
//    const IBoard::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 10);
//    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 11);
//    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 13);
//    const IBoard::PositionXY elX4         = IBoard::PositionXY(1, 14);
//    const IBoard::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elO1         = IBoard::PositionXY(1, 9);
//    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 9);
//    const IBoard::PositionXY end          = IBoard::PositionXY(1, 14);
//
//    // 1. Create a threat.
//    m_board->putMove(elX1, IBoard::PLAYER_A);
//    m_board->putMove(elX2, IBoard::PLAYER_A);
//    m_board->putMove(elX3, IBoard::PLAYER_A);
//    m_board->putMove(elX4, IBoard::PLAYER_A);
//    m_board->putMove(elO1, IBoard::PLAYER_B);
//
//    m_threatFinder->findThreatPattern(elX1, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);
//
//    // 2. Get elements.
//    ThreatFinder::ThreatLocation threatLocation;
//    m_threatFinder->getThreatFields(threatLocation);
//
//    // 3. Make verification.
//    // a. Check '*':
//    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
//    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);
//
//    // b. Check 'x':
//    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
//    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
//    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
//    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
//    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);
//
//    // c. Check '.':
//    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
//    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
//    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
//    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
//    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
//    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
//    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
//    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
//    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
//    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);
//
//    // d. Extend gaps:
//    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
//    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);
//
//    // d. Check 'o':
//    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
//    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);
//
//    // e. Check begin & end:
//    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
//    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
//}
//
//TEST(Threat4CaseCTest, GetPieces4)
//{
//    // ox.xxxo
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . . . . .|
//    // 1 |. . . o x . x x x o . . . . .|
//    // 2 |. . . . . . . . . . . . . . .|
//    // 3 |. . . . . . . . . . . . . . .|
//
//    // 0. Define expectation.
//    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap1       = IBoard::PositionXY(1, 5);
//    const IBoard::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elX1         = IBoard::PositionXY(1, 4);
//    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 6);
//    const IBoard::PositionXY elX3         = IBoard::PositionXY(1, 7);
//    const IBoard::PositionXY elX4         = IBoard::PositionXY(1, 8);
//    const IBoard::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elO1         = IBoard::PositionXY(1, 3);
//    const IBoard::PositionXY elO2         = IBoard::PositionXY(1, 9);
//    const IBoard::PositionXY beginning    = IBoard::PositionXY(1, 3);
//    const IBoard::PositionXY end          = IBoard::PositionXY(1, 9);
//
//    // 1. Create a threat.
//    m_board->putMove(elX1, IBoard::PLAYER_A);
//    m_board->putMove(elX2, IBoard::PLAYER_A);
//    m_board->putMove(elX3, IBoard::PLAYER_A);
//    m_board->putMove(elX4, IBoard::PLAYER_A);
//    m_board->putMove(elO1, IBoard::PLAYER_B);
//    m_board->putMove(elO2, IBoard::PLAYER_B);
//    m_threatFinder->findThreatPattern(elX1, ThreatFinder::HORIZONTAL, IBoard::PLAYER_A);
//
//    // 2. Get elements.
//    ThreatFinder::ThreatLocation threatLocation;
//    m_threatFinder->getThreatFields(threatLocation);
//
//    // 3. Make verification.
//    // a. Check '*':
//    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
//    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);
//
//    // b. Check 'x':
//    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
//    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
//    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
//    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
//    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);
//
//    // c. Check '.':
//    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
//    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
//    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
//    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
//    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
//    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
//    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
//    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
//    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
//    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);
//
//    // d. Extend gaps:
//    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
//    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);
//
//    // d. Check 'o':
//    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
//    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);
//
//    // e. Check begin & end:
//    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
//    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
//}
//
//TEST(Threat4CaseCTest, GetPieces5)
//{
//    // |xxxx.|
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . x . . . . . . . . . .|
//    // 1 |. . . x . . . . . . . . . . .|
//    // 2 |. . x . . . . . . . . . . . .|
//    // 3 |. x . . . . . . . . . . . . .|
//    // 4 |. . . . . . . . . . . . . . .|
//    // 5 |. . . . . . . . . . . . . . .|
//    // 6 |. . . . . . . . . . . . . . .|
//    // 7 |. . . . . . . . . . . . . . .|
//    // 8 |. . . . . . . . . . . . . . .|
//    // 9 |. . . . . . . . . . . . . . .|
//
//    // 0. Define expectation.
//    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap1       = IBoard::PositionXY(4, 0);
//    const IBoard::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elX1         = IBoard::PositionXY(0, 4);
//    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 3);
//    const IBoard::PositionXY elX3         = IBoard::PositionXY(2, 2);
//    const IBoard::PositionXY elX4         = IBoard::PositionXY(3, 1);
//    const IBoard::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 4);
//    const IBoard::PositionXY end          = IBoard::PositionXY(4, 0);
//
//    // 1. Create a threat.
//    m_board->putMove(elX1, IBoard::PLAYER_A);
//    m_board->putMove(elX2, IBoard::PLAYER_A);
//    m_board->putMove(elX3, IBoard::PLAYER_A);
//    m_board->putMove(elX4, IBoard::PLAYER_A);
//
//    m_threatFinder->findThreatPattern(elX2, ThreatFinder::RISING, IBoard::PLAYER_A);
//
//    // 2. Get elements.
//    ThreatFinder::ThreatLocation threatLocation;
//    m_threatFinder->getThreatFields(threatLocation);
//
//    // 3. Make verification.
//    // a. Check '*':
//    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
//    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);
//
//    // b. Check 'x':
//    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
//    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
//    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
//    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
//    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);
//
//    // c. Check '.':
//    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
//    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
//    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
//    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
//    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
//    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
//    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
//    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
//    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
//    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);
//
//    // d. Extend gaps:
//    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
//    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);
//
//    // d. Check 'o':
//    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
//    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);
//
//    // e. Check begin & end:
//    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
//    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
//}
//
//TEST(Threat4CaseCTest, GetPieces6)
//{
//    // |xx.xx|
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . x . . . .|
//    // 1 |. . . . . . . . . . . x . . .|
//    // 2 |. . . . . . . . . . . . . . .|
//    // 3 |. . . . . . . . . . . . . x .|
//    // 4 |. . . . . . . . . . . . . . x|
//    // 5 |. . . . . . . . . . . . . . .|
//    // 6 |. . . . . . . . . . . . . . .|
//    // 7 |. . . . . . . . . . . . . . .|
//    // 8 |. . . . . . . . . . . . . . .|
//    // 9 |. . . . . . . . . . . . . . .|
//
//    // 0. Define expectation.
//    const IBoard::PositionXY elAsterix1   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elAsterix2   = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap1       = IBoard::PositionXY(2, 12);
//    const IBoard::PositionXY elGap2       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap3       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap4       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap5       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap6       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap7       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap8       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap9       = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elGap10      = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap1 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elExtendGap2 = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elX1         = IBoard::PositionXY(0, 10);
//    const IBoard::PositionXY elX2         = IBoard::PositionXY(1, 11);
//    const IBoard::PositionXY elX3         = IBoard::PositionXY(3, 13);
//    const IBoard::PositionXY elX4         = IBoard::PositionXY(4, 14);
//    const IBoard::PositionXY elX5         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elO1         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY elO2         = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
//    const IBoard::PositionXY beginning    = IBoard::PositionXY(0, 10);
//    const IBoard::PositionXY end          = IBoard::PositionXY(4, 14);
//
//    // 1. Create a threat.
//    m_board->putMove(elX1, IBoard::PLAYER_A);
//    m_board->putMove(elX2, IBoard::PLAYER_A);
//    m_board->putMove(elX3, IBoard::PLAYER_A);
//    m_board->putMove(elX4, IBoard::PLAYER_A);
//    m_threatFinder->findThreatPattern(elX4, ThreatFinder::FALLING, IBoard::PLAYER_A);
//
//    // 2. Get elements.
//    ThreatFinder::ThreatLocation threatLocation;
//    m_threatFinder->getThreatFields(threatLocation);
//
//    // 3. Make verification.
//    // a. Check '*':
//    CPPUNIT_ASSERT(elAsterix1 == threatLocation.m_threatDetails.m_asterixes[0]);
//    CPPUNIT_ASSERT(elAsterix2 == threatLocation.m_threatDetails.m_asterixes[1]);
//
//    // b. Check 'x':
//    CPPUNIT_ASSERT(elX1 == threatLocation.m_threatDetails.m_myPawns[0]);
//    CPPUNIT_ASSERT(elX2 == threatLocation.m_threatDetails.m_myPawns[1]);
//    CPPUNIT_ASSERT(elX3 == threatLocation.m_threatDetails.m_myPawns[2]);
//    CPPUNIT_ASSERT(elX4 == threatLocation.m_threatDetails.m_myPawns[3]);
//    CPPUNIT_ASSERT(elX5 == threatLocation.m_threatDetails.m_myPawns[4]);
//
//    // c. Check '.':
//    CPPUNIT_ASSERT(elGap1 == threatLocation.m_threatDetails.m_gaps[0]);
//    CPPUNIT_ASSERT(elGap2 == threatLocation.m_threatDetails.m_gaps[1]);
//    CPPUNIT_ASSERT(elGap3 == threatLocation.m_threatDetails.m_gaps[2]);
//    CPPUNIT_ASSERT(elGap4 == threatLocation.m_threatDetails.m_gaps[3]);
//    CPPUNIT_ASSERT(elGap5 == threatLocation.m_threatDetails.m_gaps[4]);
//    CPPUNIT_ASSERT(elGap6 == threatLocation.m_threatDetails.m_gaps[5]);
//    CPPUNIT_ASSERT(elGap7 == threatLocation.m_threatDetails.m_gaps[6]);
//    CPPUNIT_ASSERT(elGap8 == threatLocation.m_threatDetails.m_gaps[7]);
//    CPPUNIT_ASSERT(elGap9 == threatLocation.m_threatDetails.m_gaps[8]);
//    CPPUNIT_ASSERT(elGap10 == threatLocation.m_threatDetails.m_gaps[9]);
//
//    // d. Extend gaps:
//    CPPUNIT_ASSERT(elExtendGap1 == threatLocation.m_threatDetails.m_extGaps[0]);
//    CPPUNIT_ASSERT(elExtendGap2 == threatLocation.m_threatDetails.m_extGaps[1]);
//
//    // d. Check 'o':
//    CPPUNIT_ASSERT(elO1 == threatLocation.m_threatDetails.m_enemyPawns[0]);
//    CPPUNIT_ASSERT(elO2 == threatLocation.m_threatDetails.m_enemyPawns[1]);
//
//    // e. Check begin & end:
//    CPPUNIT_ASSERT(beginning == threatLocation.m_threatDetails.m_beginningThreat);
//    CPPUNIT_ASSERT(end == threatLocation.m_threatDetails.m_endThreat);
//}
