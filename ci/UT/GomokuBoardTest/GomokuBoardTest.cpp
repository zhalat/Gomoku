#include <assert.h>
#include "Board.hpp"
#include "GomokuBoard.hpp"

//#include "CppUTest/TestHarness.h"
//#include "CppUTest/SimpleString.h"
//#include "CppUTest/PlatformSpecificFunctions.h"
//#include "CppUTest/TestMemoryAllocator.h"
//#include "CppUTest/MemoryLeakDetector.h"

//TEST_GROUP(GomokuBoardTest)
//{
//    void setup() { m_GomokuBoard = new GomokuBoard(6); }
//
//    void teardown() { delete m_GomokuBoard; }
//
    GomokuBoard* m_GomokuBoard = new GomokuBoard(6);;
//};
//
//TEST(GomokuBoardTest, ConstructorConnectionCorrectnessTest)
//{
//    // Checking if constructor made edge connections correctly for gomoku board.
//    Board::PositionField fieldA(0);
//    Board::PositionField fieldB(0);
//
//    // Check all corners.
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 1;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 6;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 7;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 2;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 12;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 30;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 5;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 4;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 10;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 11;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 2;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 3;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 6;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 30;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 30;
//    fieldB.m_field = 30;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 24;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 25;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 31;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 0;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 32;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 18;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 35;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 34;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 28;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 29;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 0;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 30;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 33;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 23;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    // verges.
//    fieldA.m_field = 6;
//    fieldB.m_field = 6;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 0;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 1;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 7;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 13;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 12;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 11;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 17;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 3;
//    fieldB.m_field = 3;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 2;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 8;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 9;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 10;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 4;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 1;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 34;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 29;
//    fieldB.m_field = 29;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 22;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 23;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 28;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 34;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 18;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 24;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 30;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 34;
//    fieldB.m_field = 34;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 27;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 28;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 29;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 33;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 32;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 3;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    // in the middle.
//    fieldA.m_field = 7;
//    fieldB.m_field = 7;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 0;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 1;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 2;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 8;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 6;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 12;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 13;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 14;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 3;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 15;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    ;
//    fieldA.m_field = 7;
//    fieldB.m_field = 18;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 28;
//    fieldB.m_field = 28;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 21;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 22;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 23;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 27;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 28;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 33;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 34;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 25;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 15;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 17;
//    LONGS_EQUAL(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
//}
//
//TEST(GomokuBoardTest, CopyConstructorTest)
//{
//    // Create GomokuBoard on the base of existing board.
//    GomokuBoard* gboardCopy = NULL;
//    gboardCopy              = new GomokuBoard(static_cast<GomokuBoard&>(*m_GomokuBoard));
//    assert(gboardCopy != NULL);
//
//    // Check size.
//    LONGS_EQUAL(gboardCopy->GetSize(), m_GomokuBoard->GetSize());
//
//    // Check connections.
//    Board::PositionField fieldA(0);
//    Board::PositionField fieldB(0);
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 1;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 6;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 7;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 2;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 12;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 30;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 0;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 5;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 4;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 10;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 11;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 2;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 3;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 6;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 30;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 5;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 30;
//    fieldB.m_field = 30;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 24;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 25;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 31;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 0;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 32;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 18;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 30;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 35;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 34;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 28;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 29;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 0;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 30;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 33;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 35;
//    fieldB.m_field = 23;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    // verges.
//    fieldA.m_field = 6;
//    fieldB.m_field = 6;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 0;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 1;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 7;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 13;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 12;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 11;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 6;
//    fieldB.m_field = 17;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 3;
//    fieldB.m_field = 3;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 2;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 8;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 9;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 10;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 4;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 1;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 3;
//    fieldB.m_field = 34;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 29;
//    fieldB.m_field = 29;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 22;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 23;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 28;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 34;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 18;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 24;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 29;
//    fieldB.m_field = 30;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 34;
//    fieldB.m_field = 34;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 27;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 28;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 29;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 33;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 32;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 3;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 34;
//    fieldB.m_field = 5;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    // in the middle.
//    fieldA.m_field = 7;
//    fieldB.m_field = 7;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 0;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 1;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 2;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 8;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 6;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 12;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 13;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 14;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 3;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 15;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 7;
//    fieldB.m_field = 18;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    fieldA.m_field = 28;
//    fieldB.m_field = 28;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 21;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 22;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 23;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 27;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 29;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 33;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 34;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 35;
//    LONGS_EQUAL(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 25;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 15;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//    fieldA.m_field = 28;
//    fieldB.m_field = 17;
//    LONGS_EQUAL(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
//
//    delete gboardCopy;
//}
//
//TEST(GomokuBoardTest, PutMoveTest)
//{
//    const Board::PositionXY validXY(0, 0);
//    const Board::PositionXY invalid1XY(5, 6);
//    const Board::PositionXY invalid2XY(6, 5);
//
//    const Board::Player invalidPlayer = Board::PLAYER_EMPTY;
//    const Board::Player validPlayerA  = Board::PLAYER_A;
//    const Board::Player validPlayerB  = Board::PLAYER_B;
//
//    // Check invalid position.
//    LONGS_EQUAL(false, m_GomokuBoard->PutMove(invalid1XY, validPlayerA));
//    LONGS_EQUAL(false, m_GomokuBoard->PutMove(invalid2XY, validPlayerB));
//
//    // Check invalid player.
//    LONGS_EQUAL(false, m_GomokuBoard->PutMove(validXY, invalidPlayer));
//
//    // Check some valid moves.
//    LONGS_EQUAL(true, m_GomokuBoard->PutMove(validXY, validPlayerA));
//    LONGS_EQUAL(true, m_GomokuBoard->PutMove(Board::PositionXY(5, 0), validPlayerA));
//    LONGS_EQUAL(true, m_GomokuBoard->PutMove(Board::PositionXY(0, 5), validPlayerA));
//    LONGS_EQUAL(true, m_GomokuBoard->PutMove(Board::PositionXY(5, 5), validPlayerA));
//
//    LONGS_EQUAL(true, m_GomokuBoard->PutMove(Board::PositionXY(3, 0), validPlayerB));
//    LONGS_EQUAL(true, m_GomokuBoard->PutMove(Board::PositionXY(0, 2), validPlayerB));
//    LONGS_EQUAL(true, m_GomokuBoard->PutMove(Board::PositionXY(3, 2), validPlayerB));
//    LONGS_EQUAL(true, m_GomokuBoard->PutMove(Board::PositionXY(5, 2), validPlayerB));
//    LONGS_EQUAL(true, m_GomokuBoard->PutMove(Board::PositionXY(3, 5), validPlayerB));
//
//    // Trying put move on not vacant place.
//
//    // Try to put PlayerA to a place occuped by PlayerA.
//    LONGS_EQUAL(false, m_GomokuBoard->PutMove(Board::PositionXY(0, 0), validPlayerA));
//    // Try to put PlayerB to a place occuped by PlayerB.
//    LONGS_EQUAL(false, m_GomokuBoard->PutMove(Board::PositionXY(3, 0), validPlayerB));
//    // Try to put PlayerB to a place occuped by PlayerA.
//    LONGS_EQUAL(false, m_GomokuBoard->PutMove(Board::PositionXY(0, 0), validPlayerB));
//    // Try to put PlayerA to a place occuped by PlayerB.
//    LONGS_EQUAL(false, m_GomokuBoard->PutMove(Board::PositionXY(3, 0), validPlayerA));
//}
//
//TEST(GomokuBoardTest, GetMoveTest)
//{
//    // Define some positions.
//    const Board::PositionXY xy1(0, 0);
//    const Board::PositionXY xy2(3, 3);
//    const Board::PositionXY xy3(5, 5);
//
//    const Board::Player invalidPlayer = Board::PLAYER_EMPTY;
//    const Board::Player validPlayerA  = Board::PLAYER_A;
//    const Board::Player validPlayerB  = Board::PLAYER_B;
//
//    // Check if vacant fields.
//    LONGS_EQUAL(Board::PLAYER_EMPTY, m_GomokuBoard->GetMove(xy1));
//    LONGS_EQUAL(Board::PLAYER_EMPTY, m_GomokuBoard->GetMove(xy2));
//    LONGS_EQUAL(Board::PLAYER_EMPTY, m_GomokuBoard->GetMove(xy3));
//
//    m_GomokuBoard->PutMove(xy1, validPlayerA);
//    LONGS_EQUAL(Board::PLAYER_A, m_GomokuBoard->GetMove(xy1));
//    m_GomokuBoard->PutMove(xy2, validPlayerA);
//    LONGS_EQUAL(Board::PLAYER_A, m_GomokuBoard->GetMove(xy2));
//    m_GomokuBoard->PutMove(xy3, validPlayerB);
//    LONGS_EQUAL(Board::PLAYER_B, m_GomokuBoard->GetMove(xy3));
//}
//
//TEST(GomokuBoardTest, GetLastMoveTest)
//{
//    Board::PositionXY lastMove;
//
//    // Check empty board.
//    LONGS_EQUAL(false, m_GomokuBoard->GetLastMove(lastMove));
//
//    // Check if last accepted move is available thru GetLastMove()
//    m_GomokuBoard->PutMove(Board::PositionXY(0, 0), Board::PLAYER_A);
//    LONGS_EQUAL(true, m_GomokuBoard->GetLastMove(lastMove));
//    CHECK_TRUE(Board::PositionXY(0, 0) == lastMove);
//
//    m_GomokuBoard->PutMove(Board::PositionXY(2, 5), Board::PLAYER_B);
//    LONGS_EQUAL(true, m_GomokuBoard->GetLastMove(lastMove));
//    CHECK_TRUE(Board::PositionXY(2, 5) == lastMove);
//
//    // Not accepted move shall not modyfy last move.
//    m_GomokuBoard->PutMove(Board::PositionXY(0, 0), Board::PLAYER_A);
//    LONGS_EQUAL(true, m_GomokuBoard->GetLastMove(lastMove));
//    CHECK_TRUE(Board::PositionXY(2, 5) == lastMove);
//}
//
//TEST(GomokuBoardTest, VacantFieldsTest)
//{
//    using namespace graph;
//
//    // Clear board should has size x size vacant fields.
//    const uint32_t maxVacantFields = m_GomokuBoard->GetSize() * m_GomokuBoard->GetSize();
//    LONGS_EQUAL(maxVacantFields, m_GomokuBoard->VacantFields());
//
//    uint32_t vacantFields = maxVacantFields;
//
//    // Go through all fields of board and put move sequentially.
//    for(Node i = 0; i < m_GomokuBoard->GetSize(); ++i)
//    {
//        for(Node j = 0; j < m_GomokuBoard->GetSize(); ++j)
//        {
//            const Board::PositionXY xy(i, j);
//
//            m_GomokuBoard->PutMove(xy, Board::PLAYER_A);
//            vacantFields--;
//            LONGS_EQUAL(vacantFields, m_GomokuBoard->VacantFields());
//        }
//    }
//}
//
//TEST(GomokuBoardTest, EdgeDistanceTest)
//{
//    const Board::PositionXY inTheMiddle(4, 1);
//
//    LONGS_EQUAL(static_cast<uint32_t>(4), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::UP));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::DOWN));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::LEFT));
//    LONGS_EQUAL(static_cast<uint32_t>(4), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(4), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::UP_RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::UP_LEFT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::DOWN_RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::DOWN_LEFT));
//
//    const Board::PositionXY atTheCorner(0, 5);
//
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->EdgeDistance(atTheCorner, Board::UP));
//    LONGS_EQUAL(static_cast<uint32_t>(5), m_GomokuBoard->EdgeDistance(atTheCorner, Board::DOWN));
//    LONGS_EQUAL(static_cast<uint32_t>(5), m_GomokuBoard->EdgeDistance(atTheCorner, Board::LEFT));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->EdgeDistance(atTheCorner, Board::RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->EdgeDistance(atTheCorner, Board::UP_RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->EdgeDistance(atTheCorner, Board::UP_LEFT));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->EdgeDistance(atTheCorner, Board::DOWN_RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(5), m_GomokuBoard->EdgeDistance(atTheCorner, Board::DOWN_LEFT));
//}
//
//TEST(GomokuBoardTest, NeighbourDistanceTest)
//{
//    // Put some moves:
//    m_GomokuBoard->PutMove(Board::PositionXY(0, 5), Board::PLAYER_B);
//    m_GomokuBoard->PutMove(Board::PositionXY(1, 2), Board::PLAYER_B);
//    m_GomokuBoard->PutMove(Board::PositionXY(3, 4), Board::PLAYER_A);
//    m_GomokuBoard->PutMove(Board::PositionXY(4, 1), Board::PLAYER_A);
//
//    // From this vacant position distance will be computed.
//    const Board::PositionXY pointOfView1(4, 5);
//
//    LONGS_EQUAL(static_cast<int32_t>(-1), m_GomokuBoard->NeighbourDistance(pointOfView1, Board::UP, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2), m_GomokuBoard->NeighbourDistance(pointOfView1, Board::DOWN, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(3), m_GomokuBoard->NeighbourDistance(pointOfView1, Board::LEFT, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2),
//                m_GomokuBoard->NeighbourDistance(pointOfView1, Board::RIGHT, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2),
//                m_GomokuBoard->NeighbourDistance(pointOfView1, Board::UP_RIGHT, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(0),
//                m_GomokuBoard->NeighbourDistance(pointOfView1, Board::UP_LEFT, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2),
//                m_GomokuBoard->NeighbourDistance(pointOfView1, Board::DOWN_RIGHT, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2),
//                m_GomokuBoard->NeighbourDistance(pointOfView1, Board::DOWN_LEFT, Board::PLAYER_A));
//
//    // From this non-vacant position distance will be computed.
//    const Board::PositionXY pointOfView2(0, 5);
//
//    LONGS_EQUAL(static_cast<int32_t>(-2), m_GomokuBoard->NeighbourDistance(pointOfView2, Board::UP, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2), m_GomokuBoard->NeighbourDistance(pointOfView2, Board::DOWN, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2), m_GomokuBoard->NeighbourDistance(pointOfView2, Board::LEFT, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2),
//                m_GomokuBoard->NeighbourDistance(pointOfView2, Board::RIGHT, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2),
//                m_GomokuBoard->NeighbourDistance(pointOfView2, Board::UP_RIGHT, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2),
//                m_GomokuBoard->NeighbourDistance(pointOfView2, Board::UP_LEFT, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(-2),
//                m_GomokuBoard->NeighbourDistance(pointOfView2, Board::DOWN_RIGHT, Board::PLAYER_A));
//    LONGS_EQUAL(static_cast<int32_t>(3),
//                m_GomokuBoard->NeighbourDistance(pointOfView2, Board::DOWN_LEFT, Board::PLAYER_A));
//}
//
//TEST(GomokuBoardTest, InRowTest)
//{
//    // Put some moves:
//    m_GomokuBoard->PutMove(Board::PositionXY(0, 0), Board::PLAYER_B);
//    m_GomokuBoard->PutMove(Board::PositionXY(1, 1), Board::PLAYER_B);
//    m_GomokuBoard->PutMove(Board::PositionXY(2, 2), Board::PLAYER_B);
//    m_GomokuBoard->PutMove(Board::PositionXY(3, 3), Board::PLAYER_A);
//    m_GomokuBoard->PutMove(Board::PositionXY(4, 4), Board::PLAYER_B);
//    m_GomokuBoard->PutMove(Board::PositionXY(5, 5), Board::PLAYER_B);
//    m_GomokuBoard->PutMove(Board::PositionXY(2, 3), Board::PLAYER_A);
//    m_GomokuBoard->PutMove(Board::PositionXY(4, 3), Board::PLAYER_A);
//    m_GomokuBoard->PutMove(Board::PositionXY(5, 3), Board::PLAYER_A);
//
//    const Board::PositionXY pointOfView1(0, 0);
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::UP));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::DOWN));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::LEFT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::UP_RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::UP_LEFT));
//    LONGS_EQUAL(static_cast<uint32_t>(3), m_GomokuBoard->InRow(pointOfView1, Board::DOWN_RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::DOWN_LEFT));
//
//    const Board::PositionXY pointOfView2(3, 3);
//    LONGS_EQUAL(static_cast<uint32_t>(2), m_GomokuBoard->InRow(pointOfView2, Board::UP));
//    LONGS_EQUAL(static_cast<uint32_t>(3), m_GomokuBoard->InRow(pointOfView2, Board::DOWN));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::LEFT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::UP_RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::UP_LEFT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::DOWN_RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::DOWN_LEFT));
//
//    // Point of view form vacant field.
//    const Board::PositionXY pointOfView3(3, 2);
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::UP));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::DOWN));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::LEFT));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::UP_RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::UP_LEFT));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::DOWN_RIGHT));
//    LONGS_EQUAL(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::DOWN_LEFT));
//}
//
//TEST(GomokuBoardTest, IsOnEdgeTest)
//{
//    // Define some positions.
//    const Board::PositionXY xyEdgeUp(0, 2);
//    const Board::PositionXY xyEdgeDown(5, 2);
//    const Board::PositionXY xyEdgeLeft(2, 0);
//    const Board::PositionXY xyEdgeRight(2, 5);
//    const Board::PositionXY xyEdgeCornerUpLeft(0, 0);
//    const Board::PositionXY xyEdgeCornerUpRight(0, 5);
//    const Board::PositionXY xyEdgeCornerDownLeft(5, 0);
//    const Board::PositionXY xyEdgeCornerDownRight(5, 5);
//    const Board::PositionXY xyEdgeInTheMiddle(3, 3);
//
//    LONGS_EQUAL(Board::EDGE_UP, m_GomokuBoard->IsOnEdge(xyEdgeUp));
//    LONGS_EQUAL(Board::EDGE_DOWN, m_GomokuBoard->IsOnEdge(xyEdgeDown));
//    LONGS_EQUAL(Board::EDGE_LEFT, m_GomokuBoard->IsOnEdge(xyEdgeLeft));
//    LONGS_EQUAL(Board::EDGE_RIGHT, m_GomokuBoard->IsOnEdge(xyEdgeRight));
//    LONGS_EQUAL(Board::CORNER_UP_LEFT, m_GomokuBoard->IsOnEdge(xyEdgeCornerUpLeft));
//    LONGS_EQUAL(Board::CORNER_UP_RIGHT, m_GomokuBoard->IsOnEdge(xyEdgeCornerUpRight));
//    LONGS_EQUAL(Board::CORNER_DOWN_LEFT, m_GomokuBoard->IsOnEdge(xyEdgeCornerDownLeft));
//    LONGS_EQUAL(Board::CORNER_DOWN_RIGHT, m_GomokuBoard->IsOnEdge(xyEdgeCornerDownRight));
//    LONGS_EQUAL(Board::EDGE_NONE, m_GomokuBoard->IsOnEdge(xyEdgeInTheMiddle));
//}
//
//TEST(GomokuBoardTest, GoDirectionTest)
//{
//    // Check position on corner.
//    const Board::PositionXY xyCorner(0, 5);
//
//    LONGS_EQUAL(false, m_GomokuBoard->CanIGo(xyCorner, Board::UP));
//    LONGS_EQUAL(false, m_GomokuBoard->CanIGo(xyCorner, Board::UP_RIGHT));
//    LONGS_EQUAL(false, m_GomokuBoard->CanIGo(xyCorner, Board::DOWN_RIGHT));
//    LONGS_EQUAL(false, m_GomokuBoard->CanIGo(xyCorner, Board::RIGHT));
//    LONGS_EQUAL(false, m_GomokuBoard->CanIGo(xyCorner, Board::UP_LEFT));
//
//    LONGS_EQUAL(true, m_GomokuBoard->CanIGo(xyCorner, Board::LEFT));
//    Board::PositionXY xyCornerLeft(xyCorner);
//    m_GomokuBoard->GoDirection(xyCornerLeft, Board::LEFT);
//    CHECK_TRUE(Board::PositionXY(0, 4) == xyCornerLeft);
//
//    LONGS_EQUAL(true, m_GomokuBoard->CanIGo(xyCorner, Board::DOWN));
//    Board::PositionXY xyCornerDown(xyCorner);
//    m_GomokuBoard->GoDirection(xyCornerDown, Board::DOWN);
//    CHECK_TRUE(Board::PositionXY(1, 5) == xyCornerDown);
//
//    LONGS_EQUAL(true, m_GomokuBoard->CanIGo(xyCorner, Board::DOWN_LEFT));
//    Board::PositionXY xyCornerDownLeft(xyCorner);
//    m_GomokuBoard->GoDirection(xyCornerDownLeft, Board::DOWN_LEFT);
//    CHECK_TRUE(Board::PositionXY(1, 4) == xyCornerDownLeft);
//
//    // Check position on board frame.
//    const Board::PositionXY xyFrame(3, 0);
//
//    LONGS_EQUAL(false, m_GomokuBoard->CanIGo(xyFrame, Board::LEFT));
//    LONGS_EQUAL(false, m_GomokuBoard->CanIGo(xyFrame, Board::DOWN_LEFT));
//    LONGS_EQUAL(false, m_GomokuBoard->CanIGo(xyFrame, Board::UP_LEFT));
//
//    LONGS_EQUAL(true, m_GomokuBoard->CanIGo(xyFrame, Board::UP));
//    Board::PositionXY xyFrameUp(xyFrame);
//    m_GomokuBoard->GoDirection(xyFrameUp, Board::UP);
//    CHECK_TRUE(Board::PositionXY(2, 0) == xyFrameUp);
//
//    LONGS_EQUAL(true, m_GomokuBoard->CanIGo(xyFrame, Board::UP_RIGHT));
//    Board::PositionXY xyFrameUpRight(xyFrame);
//    m_GomokuBoard->GoDirection(xyFrameUpRight, Board::UP_RIGHT);
//    CHECK_TRUE(Board::PositionXY(2, 1) == xyFrameUpRight);
//
//    LONGS_EQUAL(true, m_GomokuBoard->CanIGo(xyFrame, Board::RIGHT));
//    Board::PositionXY xyFrameRight(xyFrame);
//    m_GomokuBoard->GoDirection(xyFrameRight, Board::RIGHT);
//    CHECK_TRUE(Board::PositionXY(3, 1) == xyFrameRight);
//
//    LONGS_EQUAL(true, m_GomokuBoard->CanIGo(xyFrame, Board::DOWN_RIGHT));
//    Board::PositionXY xyFrameDownRight(xyFrame);
//    m_GomokuBoard->GoDirection(xyFrameDownRight, Board::DOWN_RIGHT);
//    CHECK_TRUE(Board::PositionXY(4, 1) == xyFrameDownRight);
//
//    LONGS_EQUAL(true, m_GomokuBoard->CanIGo(xyFrame, Board::DOWN));
//    Board::PositionXY xyFrameDown(xyFrame);
//    m_GomokuBoard->GoDirection(xyFrameDown, Board::DOWN);
//    CHECK_TRUE(Board::PositionXY(4, 0) == xyFrameDown);
//}
//
//TEST(GomokuBoardTest, RemoveMoveTest)
//{
//    const Board::PositionXY xy1(0, 0);
//    const Board::PositionXY xy2(1, 1);
//    const Board::PositionXY vacant(2, 2);
//
//    const Board::Player validPlayerA = Board::PLAYER_A;
//    const Board::Player validPlayerB = Board::PLAYER_B;
//
//    // Put some moves.
//    m_GomokuBoard->PutMove(xy1, validPlayerA);
//    m_GomokuBoard->PutMove(xy2, validPlayerB);
//
//    // Remove sequentally all of them.
//    LONGS_EQUAL(true, m_GomokuBoard->RemoveMove(xy1));
//    LONGS_EQUAL(true, m_GomokuBoard->RemoveMove(xy2));
//
//    // Trying removing vacant field.
//    LONGS_EQUAL(false, m_GomokuBoard->RemoveMove(vacant));
//}
//
//TEST(GomokuBoardTest, RemoveNLastMoveTest)
//{
//    const Board::Player playerA = Board::PLAYER_A;
//    const uint32_t cntrA        = 4;
//    const Board::PositionXY xyA1(0, 0);
//    const Board::PositionXY xyA2(1, 1);
//    const Board::PositionXY xyA3(2, 2);
//    const Board::PositionXY xyA4(3, 3);
//
//    const Board::Player playerB = Board::PLAYER_B;
//    const uint32_t cntrB        = 3;
//    const Board::PositionXY xyB1(0, 5);
//    const Board::PositionXY xyB2(1, 5);
//    const Board::PositionXY xyB3(2, 5);
//
//    // Put some moves.
//    const uint32_t cntrEmpty = 0;
//    LONGS_EQUAL(cntrEmpty, m_GomokuBoard->GetMoveNumber());
//    m_GomokuBoard->PutMove(xyA1, playerA);
//    m_GomokuBoard->PutMove(xyA2, playerA);
//    m_GomokuBoard->PutMove(xyA3, playerA);
//    m_GomokuBoard->PutMove(xyA4, playerA);
//    m_GomokuBoard->PutMove(xyB1, playerB);
//    m_GomokuBoard->PutMove(xyB2, playerB);
//    m_GomokuBoard->PutMove(xyB3, playerB);
//
//    LONGS_EQUAL(cntrA + cntrB, m_GomokuBoard->GetMoveNumber());
//
//    // Remove all playerB moves.
//    LONGS_EQUAL(true, m_GomokuBoard->RemoveNLastMove(cntrB));
//    LONGS_EQUAL(cntrA, m_GomokuBoard->GetMoveNumber());
//    // Remove all playerA moves.
//    LONGS_EQUAL(true, m_GomokuBoard->RemoveNLastMove(cntrA));
//    LONGS_EQUAL(cntrEmpty, m_GomokuBoard->GetMoveNumber());
//}
//
//TEST(GomokuBoardTest, OppositePlayerTest)
//{
//    const Board::Player playerA = Board::PLAYER_A;
//    const Board::Player playerB = Board::PLAYER_B;
//
//    LONGS_EQUAL(playerB, m_GomokuBoard->OppositePlayer(playerA));
//    LONGS_EQUAL(playerA, m_GomokuBoard->OppositePlayer(playerB));
//}
//
//TEST(GomokuBoardTest, GetFirstMoveTest)
//{
//    uint32_t moveCntr = 0;
//
//    // No move on board.
//    CHECK_TRUE(0 == m_GomokuBoard->GetMoveNumber());
//    Board::PositionXY firstMove;
//    CHECK_TRUE(false == m_GomokuBoard->GetFirstMove(firstMove));
//
//    m_GomokuBoard->PutMove(Board::PositionXY(4, 4), Board::PLAYER_B);
//    moveCntr++;
//    m_GomokuBoard->PutMove(Board::PositionXY(5, 5), Board::PLAYER_B);
//    moveCntr++;
//    m_GomokuBoard->PutMove(Board::PositionXY(2, 3), Board::PLAYER_A);
//    moveCntr++;
//
//    CHECK_TRUE(moveCntr == m_GomokuBoard->GetMoveNumber());
//    CHECK_TRUE(true == m_GomokuBoard->GetFirstMove(firstMove));
//    CHECK_TRUE(firstMove == Board::PositionXY(4, 4));
//}
