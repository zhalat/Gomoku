#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Board.hpp"
#include "GomokuBoard.hpp"

struct GomokuBoardTest : testing::Test
{
    void setup() { m_GomokuBoard = new GomokuBoard(6); }
    void teardown() { delete m_GomokuBoard; }
    GomokuBoard* m_GomokuBoard = new GomokuBoard(6);
};

TEST_F(GomokuBoardTest, ConstructorConnectionCorrectnessTest)
{
    // Checking if constructor correctly made edges connections.
    Board::PositionField fieldA(0);
    Board::PositionField fieldB(0);

    // Check all corners.
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 1;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 6;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 7;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 2;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 5;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 12;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 30;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 35;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 5;
    fieldB.m_field = 5;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 4;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 10;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 11;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 2;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 3;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 6;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 30;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 35;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 30;
    fieldB.m_field = 30;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 24;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 25;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 31;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 5;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 0;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 32;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 18;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 35;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 35;
    fieldB.m_field = 35;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 34;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 28;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 29;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 5;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 0;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 30;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 33;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 23;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));

    // verges.
    fieldA.m_field = 6;
    fieldB.m_field = 6;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 0;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 1;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 7;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 13;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 12;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 5;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 11;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 17;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 3;
    fieldB.m_field = 3;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 2;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 8;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 9;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 10;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 4;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 5;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 1;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 34;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 29;
    fieldB.m_field = 29;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 22;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 23;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 28;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 34;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 35;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 18;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 24;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 30;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 34;
    fieldB.m_field = 34;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 27;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 28;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 29;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 33;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 35;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 32;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 3;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 5;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));

    // in the middle.
    fieldA.m_field = 7;
    fieldB.m_field = 7;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 0;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 1;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 2;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 8;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 6;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 12;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 13;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 14;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 3;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 15;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 7;
    fieldB.m_field = 18;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 28;
    fieldB.m_field = 28;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 21;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 22;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 23;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 27;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 28;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 33;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 34;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 35;
    ASSERT_EQ(true, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 25;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 15;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 17;
    ASSERT_EQ(false, m_GomokuBoard->m_pBoardStructure->Adjacent(fieldA, fieldB));
}

TEST_F(GomokuBoardTest, CopyConstructorTest)
{
    // Create GomokuBoard on the base of existing board.
    GomokuBoard* gboardCopy = NULL;
    gboardCopy              = new GomokuBoard(static_cast<GomokuBoard&>(*m_GomokuBoard));
    assert(gboardCopy != NULL);

    // Check size.
    ASSERT_EQ(gboardCopy->GetSize(), m_GomokuBoard->GetSize());

    // Check connections.
    Board::PositionField fieldA(0);
    Board::PositionField fieldB(0);
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 1;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 6;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 7;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 2;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 5;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 12;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 30;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 0;
    fieldB.m_field = 35;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 5;
    fieldB.m_field = 5;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 4;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 10;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 11;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 2;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 3;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 6;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 30;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 5;
    fieldB.m_field = 35;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 30;
    fieldB.m_field = 30;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 24;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 25;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 31;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 5;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 0;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 32;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 18;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 30;
    fieldB.m_field = 35;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 35;
    fieldB.m_field = 35;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 34;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 28;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 29;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 5;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 0;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 30;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 33;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 35;
    fieldB.m_field = 23;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));

    // verges.
    fieldA.m_field = 6;
    fieldB.m_field = 6;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 0;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 1;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 7;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 13;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 12;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 5;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 11;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 6;
    fieldB.m_field = 17;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 3;
    fieldB.m_field = 3;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 2;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 8;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 9;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 10;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 4;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 5;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 1;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 3;
    fieldB.m_field = 34;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 29;
    fieldB.m_field = 29;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 22;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 23;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 28;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 34;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 35;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 18;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 24;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 29;
    fieldB.m_field = 30;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 34;
    fieldB.m_field = 34;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 27;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 28;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 29;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 33;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 35;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 32;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 3;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 34;
    fieldB.m_field = 5;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));

    // in the middle.
    fieldA.m_field = 7;
    fieldB.m_field = 7;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 0;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 1;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 2;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 8;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 6;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 12;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 13;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 14;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 3;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 15;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 7;
    fieldB.m_field = 18;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));

    fieldA.m_field = 28;
    fieldB.m_field = 28;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 21;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 22;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 23;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 27;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 29;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 33;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 34;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 35;
    ASSERT_EQ(true, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 25;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 15;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));
    fieldA.m_field = 28;
    fieldB.m_field = 17;
    ASSERT_EQ(false, gboardCopy->m_pBoardStructure->Adjacent(fieldA, fieldB));

    delete gboardCopy;
}

TEST_F(GomokuBoardTest, PutMoveTest)
{
    const Board::PositionXY validXY(0, 0);
    const Board::PositionXY invalid1XY(5, 6);
    const Board::PositionXY invalid2XY(6, 5);

    const Board::Player invalidPlayer = Board::PLAYER_EMPTY;
    const Board::Player validPlayerA  = Board::PLAYER_A;
    const Board::Player validPlayerB  = Board::PLAYER_B;

    // Check invalid position.
    ASSERT_EQ(false, m_GomokuBoard->PutMove(invalid1XY, validPlayerA));
    ASSERT_EQ(false, m_GomokuBoard->PutMove(invalid2XY, validPlayerB));

    // Check invalid player.
    ASSERT_EQ(false, m_GomokuBoard->PutMove(validXY, invalidPlayer));

    // Check some valid moves.
    ASSERT_EQ(true, m_GomokuBoard->PutMove(validXY, validPlayerA));
    ASSERT_EQ(true, m_GomokuBoard->PutMove(Board::PositionXY(5, 0), validPlayerA));
    ASSERT_EQ(true, m_GomokuBoard->PutMove(Board::PositionXY(0, 5), validPlayerA));
    ASSERT_EQ(true, m_GomokuBoard->PutMove(Board::PositionXY(5, 5), validPlayerA));

    ASSERT_EQ(true, m_GomokuBoard->PutMove(Board::PositionXY(3, 0), validPlayerB));
    ASSERT_EQ(true, m_GomokuBoard->PutMove(Board::PositionXY(0, 2), validPlayerB));
    ASSERT_EQ(true, m_GomokuBoard->PutMove(Board::PositionXY(3, 2), validPlayerB));
    ASSERT_EQ(true, m_GomokuBoard->PutMove(Board::PositionXY(5, 2), validPlayerB));
    ASSERT_EQ(true, m_GomokuBoard->PutMove(Board::PositionXY(3, 5), validPlayerB));

    // Trying put move on not vacant place.

    // Try to put PlayerA to a place occuped by PlayerA.
    ASSERT_EQ(false, m_GomokuBoard->PutMove(Board::PositionXY(0, 0), validPlayerA));
    // Try to put PlayerB to a place occuped by PlayerB.
    ASSERT_EQ(false, m_GomokuBoard->PutMove(Board::PositionXY(3, 0), validPlayerB));
    // Try to put PlayerB to a place occuped by PlayerA.
    ASSERT_EQ(false, m_GomokuBoard->PutMove(Board::PositionXY(0, 0), validPlayerB));
    // Try to put PlayerA to a place occuped by PlayerB.
    ASSERT_EQ(false, m_GomokuBoard->PutMove(Board::PositionXY(3, 0), validPlayerA));
}

TEST_F(GomokuBoardTest, GetMoveTest)
{
    // Define some positions.
    const Board::PositionXY xy1(0, 0);
    const Board::PositionXY xy2(3, 3);
    const Board::PositionXY xy3(5, 5);

    const Board::Player invalidPlayer = Board::PLAYER_EMPTY;
    const Board::Player validPlayerA  = Board::PLAYER_A;
    const Board::Player validPlayerB  = Board::PLAYER_B;

    // Check if vacant fields.
    ASSERT_EQ(Board::PLAYER_EMPTY, m_GomokuBoard->GetMove(xy1));
    ASSERT_EQ(Board::PLAYER_EMPTY, m_GomokuBoard->GetMove(xy2));
    ASSERT_EQ(Board::PLAYER_EMPTY, m_GomokuBoard->GetMove(xy3));

    m_GomokuBoard->PutMove(xy1, validPlayerA);
    ASSERT_EQ(Board::PLAYER_A, m_GomokuBoard->GetMove(xy1));
    m_GomokuBoard->PutMove(xy2, validPlayerA);
    ASSERT_EQ(Board::PLAYER_A, m_GomokuBoard->GetMove(xy2));
    m_GomokuBoard->PutMove(xy3, validPlayerB);
    ASSERT_EQ(Board::PLAYER_B, m_GomokuBoard->GetMove(xy3));
}

TEST_F(GomokuBoardTest, GetLastMoveTest)
{
    Board::PositionXY lastMove;

    // Check empty board.
    ASSERT_EQ(false, m_GomokuBoard->GetLastMove(lastMove));

    // Check if last accepted move is available thru GetLastMove()
    m_GomokuBoard->PutMove(Board::PositionXY(0, 0), Board::PLAYER_A);
    ASSERT_EQ(true, m_GomokuBoard->GetLastMove(lastMove));
    ASSERT_TRUE(Board::PositionXY(0, 0) == lastMove);

    m_GomokuBoard->PutMove(Board::PositionXY(2, 5), Board::PLAYER_B);
    ASSERT_EQ(true, m_GomokuBoard->GetLastMove(lastMove));
    ASSERT_TRUE(Board::PositionXY(2, 5) == lastMove);

    // Not accepted move shall not modyfy last move.
    m_GomokuBoard->PutMove(Board::PositionXY(0, 0), Board::PLAYER_A);
    ASSERT_EQ(true, m_GomokuBoard->GetLastMove(lastMove));
    ASSERT_TRUE(Board::PositionXY(2, 5) == lastMove);
}

TEST_F(GomokuBoardTest, VacantFieldsTest)
{
    using namespace graph;

    // Clear board should has size x size vacant fields.
    const uint32_t maxVacantFields = m_GomokuBoard->GetSize() * m_GomokuBoard->GetSize();
    ASSERT_EQ(maxVacantFields, m_GomokuBoard->VacantFields());

    uint32_t vacantFields = maxVacantFields;

    // Go through all fields of board and put move sequentially.
    for(Node i = 0; i < m_GomokuBoard->GetSize(); ++i)
    {
        for(Node j = 0; j < m_GomokuBoard->GetSize(); ++j)
        {
            const Board::PositionXY xy(i, j);

            m_GomokuBoard->PutMove(xy, Board::PLAYER_A);
            vacantFields--;
            ASSERT_EQ(vacantFields, m_GomokuBoard->VacantFields());
        }
    }
}

TEST_F(GomokuBoardTest, EdgeDistanceTest)
{
    const Board::PositionXY inTheMiddle(4, 1);

    ASSERT_EQ(static_cast<uint32_t>(4), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::UP));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::DOWN));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::LEFT));
    ASSERT_EQ(static_cast<uint32_t>(4), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(4), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::UP_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::UP_LEFT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::DOWN_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->EdgeDistance(inTheMiddle, Board::DOWN_LEFT));

    const Board::PositionXY atTheCorner(0, 5);

    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->EdgeDistance(atTheCorner, Board::UP));
    ASSERT_EQ(static_cast<uint32_t>(5), m_GomokuBoard->EdgeDistance(atTheCorner, Board::DOWN));
    ASSERT_EQ(static_cast<uint32_t>(5), m_GomokuBoard->EdgeDistance(atTheCorner, Board::LEFT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->EdgeDistance(atTheCorner, Board::RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->EdgeDistance(atTheCorner, Board::UP_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->EdgeDistance(atTheCorner, Board::UP_LEFT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->EdgeDistance(atTheCorner, Board::DOWN_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(5), m_GomokuBoard->EdgeDistance(atTheCorner, Board::DOWN_LEFT));
}

TEST_F(GomokuBoardTest, NeighbourDistanceTest)
{
    // Put some moves:
    m_GomokuBoard->PutMove(Board::PositionXY(0, 5), Board::PLAYER_B);
    m_GomokuBoard->PutMove(Board::PositionXY(1, 2), Board::PLAYER_B);
    m_GomokuBoard->PutMove(Board::PositionXY(3, 4), Board::PLAYER_A);
    m_GomokuBoard->PutMove(Board::PositionXY(4, 1), Board::PLAYER_A);

    // From this vacant position distance will be computed.
    const Board::PositionXY pointOfView1(4, 5);

    ASSERT_EQ(static_cast<int32_t>(-1), m_GomokuBoard->NeighbourDistance(pointOfView1, Board::UP, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2), m_GomokuBoard->NeighbourDistance(pointOfView1, Board::DOWN, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(3), m_GomokuBoard->NeighbourDistance(pointOfView1, Board::LEFT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
                m_GomokuBoard->NeighbourDistance(pointOfView1, Board::RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
                m_GomokuBoard->NeighbourDistance(pointOfView1, Board::UP_RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(0),
                m_GomokuBoard->NeighbourDistance(pointOfView1, Board::UP_LEFT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
                m_GomokuBoard->NeighbourDistance(pointOfView1, Board::DOWN_RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
                m_GomokuBoard->NeighbourDistance(pointOfView1, Board::DOWN_LEFT, Board::PLAYER_A));

    // From this non-vacant position distance will be computed.
    const Board::PositionXY pointOfView2(0, 5);

    ASSERT_EQ(static_cast<int32_t>(-2), m_GomokuBoard->NeighbourDistance(pointOfView2, Board::UP, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2), m_GomokuBoard->NeighbourDistance(pointOfView2, Board::DOWN, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2), m_GomokuBoard->NeighbourDistance(pointOfView2, Board::LEFT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
                m_GomokuBoard->NeighbourDistance(pointOfView2, Board::RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
                m_GomokuBoard->NeighbourDistance(pointOfView2, Board::UP_RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
                m_GomokuBoard->NeighbourDistance(pointOfView2, Board::UP_LEFT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
                m_GomokuBoard->NeighbourDistance(pointOfView2, Board::DOWN_RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(3),
                m_GomokuBoard->NeighbourDistance(pointOfView2, Board::DOWN_LEFT, Board::PLAYER_A));
}

TEST_F(GomokuBoardTest, InRowTest)
{
    // Put some moves:
    m_GomokuBoard->PutMove(Board::PositionXY(0, 0), Board::PLAYER_B);
    m_GomokuBoard->PutMove(Board::PositionXY(1, 1), Board::PLAYER_B);
    m_GomokuBoard->PutMove(Board::PositionXY(2, 2), Board::PLAYER_B);
    m_GomokuBoard->PutMove(Board::PositionXY(3, 3), Board::PLAYER_A);
    m_GomokuBoard->PutMove(Board::PositionXY(4, 4), Board::PLAYER_B);
    m_GomokuBoard->PutMove(Board::PositionXY(5, 5), Board::PLAYER_B);
    m_GomokuBoard->PutMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_GomokuBoard->PutMove(Board::PositionXY(4, 3), Board::PLAYER_A);
    m_GomokuBoard->PutMove(Board::PositionXY(5, 3), Board::PLAYER_A);

    const Board::PositionXY pointOfView1(0, 0);
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::UP));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::DOWN));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::LEFT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::UP_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::UP_LEFT));
    ASSERT_EQ(static_cast<uint32_t>(3), m_GomokuBoard->InRow(pointOfView1, Board::DOWN_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView1, Board::DOWN_LEFT));

    const Board::PositionXY pointOfView2(3, 3);
    ASSERT_EQ(static_cast<uint32_t>(2), m_GomokuBoard->InRow(pointOfView2, Board::UP));
    ASSERT_EQ(static_cast<uint32_t>(3), m_GomokuBoard->InRow(pointOfView2, Board::DOWN));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::LEFT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::UP_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::UP_LEFT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::DOWN_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->InRow(pointOfView2, Board::DOWN_LEFT));

    // Point of view form vacant field.
    const Board::PositionXY pointOfView3(3, 2);
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::UP));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::DOWN));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::LEFT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::UP_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::UP_LEFT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::DOWN_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->InRow(pointOfView3, Board::DOWN_LEFT));
}

TEST_F(GomokuBoardTest, IsOnEdgeTest)
{
    // Define some positions.
    const Board::PositionXY xyEdgeUp(0, 2);
    const Board::PositionXY xyEdgeDown(5, 2);
    const Board::PositionXY xyEdgeLeft(2, 0);
    const Board::PositionXY xyEdgeRight(2, 5);
    const Board::PositionXY xyEdgeCornerUpLeft(0, 0);
    const Board::PositionXY xyEdgeCornerUpRight(0, 5);
    const Board::PositionXY xyEdgeCornerDownLeft(5, 0);
    const Board::PositionXY xyEdgeCornerDownRight(5, 5);
    const Board::PositionXY xyEdgeInTheMiddle(3, 3);

    ASSERT_EQ(Board::EDGE_UP, m_GomokuBoard->IsOnEdge(xyEdgeUp));
    ASSERT_EQ(Board::EDGE_DOWN, m_GomokuBoard->IsOnEdge(xyEdgeDown));
    ASSERT_EQ(Board::EDGE_LEFT, m_GomokuBoard->IsOnEdge(xyEdgeLeft));
    ASSERT_EQ(Board::EDGE_RIGHT, m_GomokuBoard->IsOnEdge(xyEdgeRight));
    ASSERT_EQ(Board::CORNER_UP_LEFT, m_GomokuBoard->IsOnEdge(xyEdgeCornerUpLeft));
    ASSERT_EQ(Board::CORNER_UP_RIGHT, m_GomokuBoard->IsOnEdge(xyEdgeCornerUpRight));
    ASSERT_EQ(Board::CORNER_DOWN_LEFT, m_GomokuBoard->IsOnEdge(xyEdgeCornerDownLeft));
    ASSERT_EQ(Board::CORNER_DOWN_RIGHT, m_GomokuBoard->IsOnEdge(xyEdgeCornerDownRight));
    ASSERT_EQ(Board::EDGE_NONE, m_GomokuBoard->IsOnEdge(xyEdgeInTheMiddle));
}

TEST_F(GomokuBoardTest, GoDirectionTest)
{
    // Check position on corner.
    const Board::PositionXY xyCorner(0, 5);

    ASSERT_EQ(false, m_GomokuBoard->CanIGo(xyCorner, Board::UP));
    ASSERT_EQ(false, m_GomokuBoard->CanIGo(xyCorner, Board::UP_RIGHT));
    ASSERT_EQ(false, m_GomokuBoard->CanIGo(xyCorner, Board::DOWN_RIGHT));
    ASSERT_EQ(false, m_GomokuBoard->CanIGo(xyCorner, Board::RIGHT));
    ASSERT_EQ(false, m_GomokuBoard->CanIGo(xyCorner, Board::UP_LEFT));

    ASSERT_EQ(true, m_GomokuBoard->CanIGo(xyCorner, Board::LEFT));
    Board::PositionXY xyCornerLeft(xyCorner);
    m_GomokuBoard->GoDirection(xyCornerLeft, Board::LEFT);
    ASSERT_TRUE(Board::PositionXY(0, 4) == xyCornerLeft);

    ASSERT_EQ(true, m_GomokuBoard->CanIGo(xyCorner, Board::DOWN));
    Board::PositionXY xyCornerDown(xyCorner);
    m_GomokuBoard->GoDirection(xyCornerDown, Board::DOWN);
    ASSERT_TRUE(Board::PositionXY(1, 5) == xyCornerDown);

    ASSERT_EQ(true, m_GomokuBoard->CanIGo(xyCorner, Board::DOWN_LEFT));
    Board::PositionXY xyCornerDownLeft(xyCorner);
    m_GomokuBoard->GoDirection(xyCornerDownLeft, Board::DOWN_LEFT);
    ASSERT_TRUE(Board::PositionXY(1, 4) == xyCornerDownLeft);

    // Check position on board frame.
    const Board::PositionXY xyFrame(3, 0);

    ASSERT_EQ(false, m_GomokuBoard->CanIGo(xyFrame, Board::LEFT));
    ASSERT_EQ(false, m_GomokuBoard->CanIGo(xyFrame, Board::DOWN_LEFT));
    ASSERT_EQ(false, m_GomokuBoard->CanIGo(xyFrame, Board::UP_LEFT));

    ASSERT_EQ(true, m_GomokuBoard->CanIGo(xyFrame, Board::UP));
    Board::PositionXY xyFrameUp(xyFrame);
    m_GomokuBoard->GoDirection(xyFrameUp, Board::UP);
    ASSERT_TRUE(Board::PositionXY(2, 0) == xyFrameUp);

    ASSERT_EQ(true, m_GomokuBoard->CanIGo(xyFrame, Board::UP_RIGHT));
    Board::PositionXY xyFrameUpRight(xyFrame);
    m_GomokuBoard->GoDirection(xyFrameUpRight, Board::UP_RIGHT);
    ASSERT_TRUE(Board::PositionXY(2, 1) == xyFrameUpRight);

    ASSERT_EQ(true, m_GomokuBoard->CanIGo(xyFrame, Board::RIGHT));
    Board::PositionXY xyFrameRight(xyFrame);
    m_GomokuBoard->GoDirection(xyFrameRight, Board::RIGHT);
    ASSERT_TRUE(Board::PositionXY(3, 1) == xyFrameRight);

    ASSERT_EQ(true, m_GomokuBoard->CanIGo(xyFrame, Board::DOWN_RIGHT));
    Board::PositionXY xyFrameDownRight(xyFrame);
    m_GomokuBoard->GoDirection(xyFrameDownRight, Board::DOWN_RIGHT);
    ASSERT_TRUE(Board::PositionXY(4, 1) == xyFrameDownRight);

    ASSERT_EQ(true, m_GomokuBoard->CanIGo(xyFrame, Board::DOWN));
    Board::PositionXY xyFrameDown(xyFrame);
    m_GomokuBoard->GoDirection(xyFrameDown, Board::DOWN);
    ASSERT_TRUE(Board::PositionXY(4, 0) == xyFrameDown);
}

TEST_F(GomokuBoardTest, RemoveMoveTest)
{
    const Board::PositionXY xy1(0, 0);
    const Board::PositionXY xy2(1, 1);
    const Board::PositionXY vacant(2, 2);

    const Board::Player validPlayerA = Board::PLAYER_A;
    const Board::Player validPlayerB = Board::PLAYER_B;

    // Put some moves.
    m_GomokuBoard->PutMove(xy1, validPlayerA);
    m_GomokuBoard->PutMove(xy2, validPlayerB);

    // Remove sequentally all of them.
    ASSERT_EQ(true, m_GomokuBoard->RemoveMove(xy1));
    ASSERT_EQ(true, m_GomokuBoard->RemoveMove(xy2));

    // Trying removing vacant field.
    ASSERT_EQ(false, m_GomokuBoard->RemoveMove(vacant));
}

TEST_F(GomokuBoardTest, RemoveNLastMoveTest)
{
    const Board::Player playerA = Board::PLAYER_A;
    const uint32_t cntrA        = 4;
    const Board::PositionXY xyA1(0, 0);
    const Board::PositionXY xyA2(1, 1);
    const Board::PositionXY xyA3(2, 2);
    const Board::PositionXY xyA4(3, 3);

    const Board::Player playerB = Board::PLAYER_B;
    const uint32_t cntrB        = 3;
    const Board::PositionXY xyB1(0, 5);
    const Board::PositionXY xyB2(1, 5);
    const Board::PositionXY xyB3(2, 5);

    // Put some moves.
    const uint32_t cntrEmpty = 0;
    ASSERT_EQ(cntrEmpty, m_GomokuBoard->GetMoveNumber());
    m_GomokuBoard->PutMove(xyA1, playerA);
    m_GomokuBoard->PutMove(xyA2, playerA);
    m_GomokuBoard->PutMove(xyA3, playerA);
    m_GomokuBoard->PutMove(xyA4, playerA);
    m_GomokuBoard->PutMove(xyB1, playerB);
    m_GomokuBoard->PutMove(xyB2, playerB);
    m_GomokuBoard->PutMove(xyB3, playerB);

    ASSERT_EQ(cntrA + cntrB, m_GomokuBoard->GetMoveNumber());

    // Remove all playerB moves.
    ASSERT_EQ(true, m_GomokuBoard->RemoveNLastMove(cntrB));
    ASSERT_EQ(cntrA, m_GomokuBoard->GetMoveNumber());
    // Remove all playerA moves.
    ASSERT_EQ(true, m_GomokuBoard->RemoveNLastMove(cntrA));
    ASSERT_EQ(cntrEmpty, m_GomokuBoard->GetMoveNumber());
}

TEST_F(GomokuBoardTest, OppositePlayerTest)
{
    const Board::Player playerA = Board::PLAYER_A;
    const Board::Player playerB = Board::PLAYER_B;

    ASSERT_EQ(playerB, m_GomokuBoard->OppositePlayer(playerA));
    ASSERT_EQ(playerA, m_GomokuBoard->OppositePlayer(playerB));
}

TEST_F(GomokuBoardTest, GetFirstMoveTest)
{
    uint32_t moveCntr = 0;

    // No move on board.
    ASSERT_TRUE(0 == m_GomokuBoard->GetMoveNumber());
    Board::PositionXY firstMove;
    ASSERT_TRUE(false == m_GomokuBoard->GetFirstMove(firstMove));

    m_GomokuBoard->PutMove(Board::PositionXY(4, 4), Board::PLAYER_B);
    moveCntr++;
    m_GomokuBoard->PutMove(Board::PositionXY(5, 5), Board::PLAYER_B);
    moveCntr++;
    m_GomokuBoard->PutMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    moveCntr++;

    ASSERT_TRUE(moveCntr == m_GomokuBoard->GetMoveNumber());
    ASSERT_TRUE(true == m_GomokuBoard->GetFirstMove(firstMove));
    ASSERT_TRUE(firstMove == Board::PositionXY(4, 4));
}
