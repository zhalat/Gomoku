#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "VectorLight.h"
#include "GomokuBoard.h"

static void checkConnection(GomokuBoard& board);

class GomokuBoardTest : public ::testing::Test
{
public:
    static constexpr uint32_t k_TEST_BOARD_SIZE{6};
    void SetUp() { m_GomokuBoard = new GomokuBoard(k_TEST_BOARD_SIZE); }
    void TearDown() { delete m_GomokuBoard; }
    GomokuBoard* m_GomokuBoard {nullptr};
};

TEST_F(GomokuBoardTest, ConstructorConnectionCorrectnessTest)
{
    checkConnection(*m_GomokuBoard);
}

TEST_F(GomokuBoardTest, CopyConstructorTest)
{
    GomokuBoard* gboardCopy = NULL;
    gboardCopy              = new GomokuBoard(static_cast<GomokuBoard&>(*m_GomokuBoard));
    assert(gboardCopy != NULL);
    ASSERT_EQ(gboardCopy->getSize(), m_GomokuBoard->getSize());

    checkConnection(*m_GomokuBoard);

    delete gboardCopy;
}

TEST_F(GomokuBoardTest, PutMoveTest)
{
    const Board::PositionXY validXY(static_cast<uint32_t>(0), static_cast<uint32_t>(0));
    const Board::PositionXY invalid1XY(static_cast<uint32_t>(5), static_cast<uint32_t>(6));
    const Board::PositionXY invalid2XY(static_cast<uint32_t>(6), static_cast<uint32_t>(5));

    const Board::Player invalidPlayer = Board::PLAYER_EMPTY;
    const Board::Player validPlayerA  = Board::PLAYER_A;
    const Board::Player validPlayerB  = Board::PLAYER_B;

    // Check invalid position.
    ASSERT_EQ(false, m_GomokuBoard->putMove(invalid1XY, validPlayerA));
    ASSERT_EQ(false, m_GomokuBoard->putMove(invalid2XY, validPlayerB));

    // Check invalid player.
    ASSERT_EQ(false, m_GomokuBoard->putMove(validXY, invalidPlayer));

    // Check some valid moves.
    ASSERT_EQ(true, m_GomokuBoard->putMove(validXY, validPlayerA));
    ASSERT_EQ(true, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(5), static_cast<uint32_t>(0)), validPlayerA));
    ASSERT_EQ(true, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(0), static_cast<uint32_t>(5)), validPlayerA));
    ASSERT_EQ(true, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(5), static_cast<uint32_t>(5)), validPlayerA));

    ASSERT_EQ(true, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(3), static_cast<uint32_t>(0)), validPlayerB));
    ASSERT_EQ(true, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(0), static_cast<uint32_t>(2)), validPlayerB));
    ASSERT_EQ(true, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(3), static_cast<uint32_t>(2)), validPlayerB));
    ASSERT_EQ(true, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(5), static_cast<uint32_t>(2)), validPlayerB));
    ASSERT_EQ(true, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(3), static_cast<uint32_t>(5)), validPlayerB));

    // Trying put move on not vacant place.

    // Try to put PlayerA to a place occuped by PlayerA.
    ASSERT_EQ(false, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(0), static_cast<uint32_t>(0)), validPlayerA));
    // Try to put PlayerB to a place occuped by PlayerB.
    ASSERT_EQ(false, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(3), static_cast<uint32_t>(0)), validPlayerB));
    // Try to put PlayerB to a place occuped by PlayerA.
    ASSERT_EQ(false, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(0), static_cast<uint32_t>(0)), validPlayerB));
    // Try to put PlayerA to a place occuped by PlayerB.
    ASSERT_EQ(false, m_GomokuBoard->putMove(Board::PositionXY(static_cast<uint32_t>(3), static_cast<uint32_t>(0)), validPlayerA));
}

TEST_F(GomokuBoardTest, getMoveTest)
{
    // Define some positions.
    const Board::PositionXY xy1(0, 0);
    const Board::PositionXY xy2(3, 3);
    const Board::PositionXY xy3(5, 5);

    const Board::Player invalidPlayer = Board::PLAYER_EMPTY;
    const Board::Player validPlayerA  = Board::PLAYER_A;
    const Board::Player validPlayerB  = Board::PLAYER_B;

    // Check if vacant fields.
    ASSERT_EQ(Board::PLAYER_EMPTY, m_GomokuBoard->getMove(xy1));
    ASSERT_EQ(Board::PLAYER_EMPTY, m_GomokuBoard->getMove(xy2));
    ASSERT_EQ(Board::PLAYER_EMPTY, m_GomokuBoard->getMove(xy3));

    m_GomokuBoard->putMove(xy1, validPlayerA);
    ASSERT_EQ(Board::PLAYER_A, m_GomokuBoard->getMove(xy1));
    m_GomokuBoard->putMove(xy2, validPlayerA);
    ASSERT_EQ(Board::PLAYER_A, m_GomokuBoard->getMove(xy2));
    m_GomokuBoard->putMove(xy3, validPlayerB);
    ASSERT_EQ(Board::PLAYER_B, m_GomokuBoard->getMove(xy3));
}

TEST_F(GomokuBoardTest, GetLastMoveTest)
{
    Board::PositionXY lastMove;

    // Check empty board.
    ASSERT_EQ(false, m_GomokuBoard->getLastMove(lastMove));

    // Check if last accepted move is available thru getLastMove()
    m_GomokuBoard->putMove(Board::PositionXY(0, 0), Board::PLAYER_A);
    ASSERT_EQ(true, m_GomokuBoard->getLastMove(lastMove));
    ASSERT_TRUE(Board::PositionXY(0, 0) == lastMove);

    m_GomokuBoard->putMove(Board::PositionXY(2, 5), Board::PLAYER_B);
    ASSERT_EQ(true, m_GomokuBoard->getLastMove(lastMove));
    ASSERT_TRUE(Board::PositionXY(2, 5) == lastMove);

    // Not accepted move shall not modyfy last move.
    m_GomokuBoard->putMove(Board::PositionXY(0, 0), Board::PLAYER_A);
    ASSERT_EQ(true, m_GomokuBoard->getLastMove(lastMove));
    ASSERT_TRUE(Board::PositionXY(2, 5) == lastMove);
}

TEST_F(GomokuBoardTest, VacantFieldsTest)
{
    using namespace graph;

    // clear board should has m_size x m_size vacant fields.
    const uint32_t maxVacantFields = m_GomokuBoard->getSize() * m_GomokuBoard->getSize();
    ASSERT_EQ(maxVacantFields, m_GomokuBoard->vacantFields());

    uint32_t vacantFields = maxVacantFields;

    // Go through all fields of board and put move sequentially.
    for(Node i = 0; i < m_GomokuBoard->getSize(); ++i)
    {
        for(Node j = 0; j < m_GomokuBoard->getSize(); ++j)
        {
            const Board::PositionXY xy(i, j);

            m_GomokuBoard->putMove(xy, Board::PLAYER_A);
            vacantFields--;
            ASSERT_EQ(vacantFields, m_GomokuBoard->vacantFields());
        }
    }
}

TEST_F(GomokuBoardTest, EdgeDistanceTest)
{
    const Board::PositionXY inTheMiddle(4, 1);

    ASSERT_EQ(static_cast<uint32_t>(4), m_GomokuBoard->edgeDistance(inTheMiddle, Board::UP));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->edgeDistance(inTheMiddle, Board::DOWN));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->edgeDistance(inTheMiddle, Board::LEFT));
    ASSERT_EQ(static_cast<uint32_t>(4), m_GomokuBoard->edgeDistance(inTheMiddle, Board::RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(4), m_GomokuBoard->edgeDistance(inTheMiddle, Board::UP_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->edgeDistance(inTheMiddle, Board::UP_LEFT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->edgeDistance(inTheMiddle, Board::DOWN_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->edgeDistance(inTheMiddle, Board::DOWN_LEFT));

    const Board::PositionXY atTheCorner(0, 5);

    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->edgeDistance(atTheCorner, Board::UP));
    ASSERT_EQ(static_cast<uint32_t>(5), m_GomokuBoard->edgeDistance(atTheCorner, Board::DOWN));
    ASSERT_EQ(static_cast<uint32_t>(5), m_GomokuBoard->edgeDistance(atTheCorner, Board::LEFT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->edgeDistance(atTheCorner, Board::RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->edgeDistance(atTheCorner, Board::UP_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->edgeDistance(atTheCorner, Board::UP_LEFT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->edgeDistance(atTheCorner, Board::DOWN_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(5), m_GomokuBoard->edgeDistance(atTheCorner, Board::DOWN_LEFT));
}

TEST_F(GomokuBoardTest, NeighbourDistanceTest)
{
    // Put some moves:
    m_GomokuBoard->putMove(Board::PositionXY(0, 5), Board::PLAYER_B);
    m_GomokuBoard->putMove(Board::PositionXY(1, 2), Board::PLAYER_B);
    m_GomokuBoard->putMove(Board::PositionXY(3, 4), Board::PLAYER_A);
    m_GomokuBoard->putMove(Board::PositionXY(4, 1), Board::PLAYER_A);

    // From this vacant position distance will be computed.
    const Board::PositionXY pointOfView1(4, 5);

    ASSERT_EQ(static_cast<int32_t>(-1), m_GomokuBoard->neighbourDistance(pointOfView1, Board::UP, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2), m_GomokuBoard->neighbourDistance(pointOfView1, Board::DOWN, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(3), m_GomokuBoard->neighbourDistance(pointOfView1, Board::LEFT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
              m_GomokuBoard->neighbourDistance(pointOfView1, Board::RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
              m_GomokuBoard->neighbourDistance(pointOfView1, Board::UP_RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(0),
              m_GomokuBoard->neighbourDistance(pointOfView1, Board::UP_LEFT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
              m_GomokuBoard->neighbourDistance(pointOfView1, Board::DOWN_RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
              m_GomokuBoard->neighbourDistance(pointOfView1, Board::DOWN_LEFT, Board::PLAYER_A));

    // From this non-vacant position distance will be computed.
    const Board::PositionXY pointOfView2(0, 5);

    ASSERT_EQ(static_cast<int32_t>(-2), m_GomokuBoard->neighbourDistance(pointOfView2, Board::UP, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2), m_GomokuBoard->neighbourDistance(pointOfView2, Board::DOWN, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2), m_GomokuBoard->neighbourDistance(pointOfView2, Board::LEFT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
              m_GomokuBoard->neighbourDistance(pointOfView2, Board::RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
              m_GomokuBoard->neighbourDistance(pointOfView2, Board::UP_RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
              m_GomokuBoard->neighbourDistance(pointOfView2, Board::UP_LEFT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(-2),
              m_GomokuBoard->neighbourDistance(pointOfView2, Board::DOWN_RIGHT, Board::PLAYER_A));
    ASSERT_EQ(static_cast<int32_t>(3),
              m_GomokuBoard->neighbourDistance(pointOfView2, Board::DOWN_LEFT, Board::PLAYER_A));
}

TEST_F(GomokuBoardTest, InRowTest)
{
    // Put some moves:
    m_GomokuBoard->putMove(Board::PositionXY(0, 0), Board::PLAYER_B);
    m_GomokuBoard->putMove(Board::PositionXY(1, 1), Board::PLAYER_B);
    m_GomokuBoard->putMove(Board::PositionXY(2, 2), Board::PLAYER_B);
    m_GomokuBoard->putMove(Board::PositionXY(3, 3), Board::PLAYER_A);
    m_GomokuBoard->putMove(Board::PositionXY(4, 4), Board::PLAYER_B);
    m_GomokuBoard->putMove(Board::PositionXY(5, 5), Board::PLAYER_B);
    m_GomokuBoard->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_GomokuBoard->putMove(Board::PositionXY(4, 3), Board::PLAYER_A);
    m_GomokuBoard->putMove(Board::PositionXY(5, 3), Board::PLAYER_A);

    const Board::PositionXY pointOfView1(0, 0);
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView1, Board::UP));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView1, Board::DOWN));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView1, Board::LEFT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView1, Board::RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView1, Board::UP_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView1, Board::UP_LEFT));
    ASSERT_EQ(static_cast<uint32_t>(3), m_GomokuBoard->inRow(pointOfView1, Board::DOWN_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView1, Board::DOWN_LEFT));

    const Board::PositionXY pointOfView2(3, 3);
    ASSERT_EQ(static_cast<uint32_t>(2), m_GomokuBoard->inRow(pointOfView2, Board::UP));
    ASSERT_EQ(static_cast<uint32_t>(3), m_GomokuBoard->inRow(pointOfView2, Board::DOWN));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView2, Board::LEFT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView2, Board::RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView2, Board::UP_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView2, Board::UP_LEFT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView2, Board::DOWN_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(1), m_GomokuBoard->inRow(pointOfView2, Board::DOWN_LEFT));

    // Point of view form vacant field.
    const Board::PositionXY pointOfView3(3, 2);
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->inRow(pointOfView3, Board::UP));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->inRow(pointOfView3, Board::DOWN));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->inRow(pointOfView3, Board::LEFT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->inRow(pointOfView3, Board::RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->inRow(pointOfView3, Board::UP_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->inRow(pointOfView3, Board::UP_LEFT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->inRow(pointOfView3, Board::DOWN_RIGHT));
    ASSERT_EQ(static_cast<uint32_t>(0), m_GomokuBoard->inRow(pointOfView3, Board::DOWN_LEFT));
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

    ASSERT_EQ(Board::EDGE_UP, m_GomokuBoard->isOnEdge(xyEdgeUp));
    ASSERT_EQ(Board::EDGE_DOWN, m_GomokuBoard->isOnEdge(xyEdgeDown));
    ASSERT_EQ(Board::EDGE_LEFT, m_GomokuBoard->isOnEdge(xyEdgeLeft));
    ASSERT_EQ(Board::EDGE_RIGHT, m_GomokuBoard->isOnEdge(xyEdgeRight));
    ASSERT_EQ(Board::CORNER_UP_LEFT, m_GomokuBoard->isOnEdge(xyEdgeCornerUpLeft));
    ASSERT_EQ(Board::CORNER_UP_RIGHT, m_GomokuBoard->isOnEdge(xyEdgeCornerUpRight));
    ASSERT_EQ(Board::CORNER_DOWN_LEFT, m_GomokuBoard->isOnEdge(xyEdgeCornerDownLeft));
    ASSERT_EQ(Board::CORNER_DOWN_RIGHT, m_GomokuBoard->isOnEdge(xyEdgeCornerDownRight));
    ASSERT_EQ(Board::EDGE_NONE, m_GomokuBoard->isOnEdge(xyEdgeInTheMiddle));
}

TEST_F(GomokuBoardTest, goDirectionTest)
{
    // Check position on corner.
    const Board::PositionXY xyCorner(0, 5);

    ASSERT_EQ(false, m_GomokuBoard->canIGo(xyCorner, Board::UP));
    ASSERT_EQ(false, m_GomokuBoard->canIGo(xyCorner, Board::UP_RIGHT));
    ASSERT_EQ(false, m_GomokuBoard->canIGo(xyCorner, Board::DOWN_RIGHT));
    ASSERT_EQ(false, m_GomokuBoard->canIGo(xyCorner, Board::RIGHT));
    ASSERT_EQ(false, m_GomokuBoard->canIGo(xyCorner, Board::UP_LEFT));

    ASSERT_EQ(true, m_GomokuBoard->canIGo(xyCorner, Board::LEFT));
    Board::PositionXY xyCornerLeft(xyCorner);
    m_GomokuBoard->goDirection(xyCornerLeft, Board::LEFT);
    ASSERT_TRUE(Board::PositionXY(0, 4) == xyCornerLeft);

    ASSERT_EQ(true, m_GomokuBoard->canIGo(xyCorner, Board::DOWN));
    Board::PositionXY xyCornerDown(xyCorner);
    m_GomokuBoard->goDirection(xyCornerDown, Board::DOWN);
    ASSERT_TRUE(Board::PositionXY(1, 5) == xyCornerDown);

    ASSERT_EQ(true, m_GomokuBoard->canIGo(xyCorner, Board::DOWN_LEFT));
    Board::PositionXY xyCornerDownLeft(xyCorner);
    m_GomokuBoard->goDirection(xyCornerDownLeft, Board::DOWN_LEFT);
    ASSERT_TRUE(Board::PositionXY(1, 4) == xyCornerDownLeft);

    // Check position on board frame.
    const Board::PositionXY xyFrame(3, 0);

    ASSERT_EQ(false, m_GomokuBoard->canIGo(xyFrame, Board::LEFT));
    ASSERT_EQ(false, m_GomokuBoard->canIGo(xyFrame, Board::DOWN_LEFT));
    ASSERT_EQ(false, m_GomokuBoard->canIGo(xyFrame, Board::UP_LEFT));

    ASSERT_EQ(true, m_GomokuBoard->canIGo(xyFrame, Board::UP));
    Board::PositionXY xyFrameUp(xyFrame);
    m_GomokuBoard->goDirection(xyFrameUp, Board::UP);
    ASSERT_TRUE(Board::PositionXY(2, 0) == xyFrameUp);

    ASSERT_EQ(true, m_GomokuBoard->canIGo(xyFrame, Board::UP_RIGHT));
    Board::PositionXY xyFrameUpRight(xyFrame);
    m_GomokuBoard->goDirection(xyFrameUpRight, Board::UP_RIGHT);
    ASSERT_TRUE(Board::PositionXY(2, 1) == xyFrameUpRight);

    ASSERT_EQ(true, m_GomokuBoard->canIGo(xyFrame, Board::RIGHT));
    Board::PositionXY xyFrameRight(xyFrame);
    m_GomokuBoard->goDirection(xyFrameRight, Board::RIGHT);
    ASSERT_TRUE(Board::PositionXY(3, 1) == xyFrameRight);

    ASSERT_EQ(true, m_GomokuBoard->canIGo(xyFrame, Board::DOWN_RIGHT));
    Board::PositionXY xyFrameDownRight(xyFrame);
    m_GomokuBoard->goDirection(xyFrameDownRight, Board::DOWN_RIGHT);
    ASSERT_TRUE(Board::PositionXY(4, 1) == xyFrameDownRight);

    ASSERT_EQ(true, m_GomokuBoard->canIGo(xyFrame, Board::DOWN));
    Board::PositionXY xyFrameDown(xyFrame);
    m_GomokuBoard->goDirection(xyFrameDown, Board::DOWN);
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
    m_GomokuBoard->putMove(xy1, validPlayerA);
    m_GomokuBoard->putMove(xy2, validPlayerB);

    // remove sequentally all of them.
    ASSERT_EQ(true, m_GomokuBoard->removeMove(xy1));
    ASSERT_EQ(true, m_GomokuBoard->removeMove(xy2));

    // Trying removing vacant field.
    ASSERT_EQ(false, m_GomokuBoard->removeMove(vacant));
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
    ASSERT_EQ(cntrEmpty, m_GomokuBoard->getMoveNumber());
    m_GomokuBoard->putMove(xyA1, playerA);
    m_GomokuBoard->putMove(xyA2, playerA);
    m_GomokuBoard->putMove(xyA3, playerA);
    m_GomokuBoard->putMove(xyA4, playerA);
    m_GomokuBoard->putMove(xyB1, playerB);
    m_GomokuBoard->putMove(xyB2, playerB);
    m_GomokuBoard->putMove(xyB3, playerB);

    ASSERT_EQ(cntrA + cntrB, m_GomokuBoard->getMoveNumber());

    // remove all playerB moves.
    ASSERT_EQ(true, m_GomokuBoard->removeNLastMove(cntrB));
    ASSERT_EQ(cntrA, m_GomokuBoard->getMoveNumber());
    // remove all playerA moves.
    ASSERT_EQ(true, m_GomokuBoard->removeNLastMove(cntrA));
    ASSERT_EQ(cntrEmpty, m_GomokuBoard->getMoveNumber());
}

TEST_F(GomokuBoardTest, OppositePlayerTest)
{
    const Board::Player playerA = Board::PLAYER_A;
    const Board::Player playerB = Board::PLAYER_B;

    ASSERT_EQ(playerB, m_GomokuBoard->oppositePlayer(playerA));
    ASSERT_EQ(playerA, m_GomokuBoard->oppositePlayer(playerB));
}

TEST_F(GomokuBoardTest, GetFirstMoveTest)
{
    uint32_t moveCntr = 0;

    // No move on board.
    ASSERT_TRUE(0 == m_GomokuBoard->getMoveNumber());
    Board::PositionXY firstMove;
    ASSERT_TRUE(false == m_GomokuBoard->getFirstMove(firstMove));

    m_GomokuBoard->putMove(Board::PositionXY(4, 4), Board::PLAYER_B);
    moveCntr++;
    m_GomokuBoard->putMove(Board::PositionXY(5, 5), Board::PLAYER_B);
    moveCntr++;
    m_GomokuBoard->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    moveCntr++;

    ASSERT_TRUE(moveCntr == m_GomokuBoard->getMoveNumber());
    ASSERT_TRUE(true == m_GomokuBoard->getFirstMove(firstMove));
    ASSERT_TRUE(firstMove == Board::PositionXY(4, 4));
}

void checkConnection(GomokuBoard& board)
{
    // Checking if constructor correctly made edges connections.
    uint32_t fieldA(0);
    uint32_t fieldB(0);

    // Check all corners.
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 0;
    fieldB = 1;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 0;
    fieldB = 6;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 0;
    fieldB = 7;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 0;
    fieldB = 2;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 0;
    fieldB = 5;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 0;
    fieldB = 12;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 0;
    fieldB = 30;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 0;
    fieldB = 35;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));

    fieldA = 5;
    fieldB = 5;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 5;
    fieldB = 4;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 5;
    fieldB = 10;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 5;
    fieldB = 11;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 5;
    fieldB = 2;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 5;
    fieldB = 3;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 5;
    fieldB = 6;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 5;
    fieldB = 30;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 5;
    fieldB = 35;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));

    fieldA = 30;
    fieldB = 30;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 30;
    fieldB = 24;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 30;
    fieldB = 25;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 30;
    fieldB = 31;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 30;
    fieldB = 5;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 30;
    fieldB = 0;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 30;
    fieldB = 32;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 30;
    fieldB = 18;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 30;
    fieldB = 35;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));

    fieldA = 35;
    fieldB = 35;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 35;
    fieldB = 34;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 35;
    fieldB = 28;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 35;
    fieldB = 29;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 35;
    fieldB = 5;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 35;
    fieldB = 0;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 35;
    fieldB = 30;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 35;
    fieldB = 33;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 35;
    fieldB = 23;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));

    // verges.
    fieldA = 6;
    fieldB = 6;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 6;
    fieldB = 0;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 6;
    fieldB = 1;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 6;
    fieldB = 7;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 6;
    fieldB = 13;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 6;
    fieldB = 12;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 6;
    fieldB = 5;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 6;
    fieldB = 11;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 6;
    fieldB = 17;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));

    fieldA = 3;
    fieldB = 3;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 3;
    fieldB = 2;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 3;
    fieldB = 8;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 3;
    fieldB = 9;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 3;
    fieldB = 10;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 3;
    fieldB = 4;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 3;
    fieldB = 5;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 3;
    fieldB = 1;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 3;
    fieldB = 34;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));

    fieldA = 29;
    fieldB = 29;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 29;
    fieldB = 22;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 29;
    fieldB = 23;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 29;
    fieldB = 28;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 29;
    fieldB = 34;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 29;
    fieldB = 35;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 29;
    fieldB = 18;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 29;
    fieldB = 24;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 29;
    fieldB = 30;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));

    fieldA = 34;
    fieldB = 34;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 34;
    fieldB = 27;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 34;
    fieldB = 28;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 34;
    fieldB = 29;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 34;
    fieldB = 33;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 34;
    fieldB = 35;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 34;
    fieldB = 32;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 34;
    fieldB = 3;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 34;
    fieldB = 5;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));

    // in the middle.
    fieldA = 7;
    fieldB = 7;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 7;
    fieldB = 0;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 7;
    fieldB = 1;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 7;
    fieldB = 2;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 7;
    fieldB = 8;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 7;
    fieldB = 6;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 7;
    fieldB = 12;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 7;
    fieldB = 13;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 7;
    fieldB = 14;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 7;
    fieldB = 3;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 7;
    fieldB = 15;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));

    fieldA = 7;
    fieldB = 18;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));

    fieldA = 28;
    fieldB = 28;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 21;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 22;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 23;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 27;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 28;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 33;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 34;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 35;
    ASSERT_EQ(true, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 25;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 15;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
    fieldA = 28;
    fieldB = 17;
    ASSERT_EQ(false, board.m_pBoardStructure->adjacent(fieldA, fieldB));
}