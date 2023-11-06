#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Board.h"
#include "Score.h"
#include "Spotter.h"
#include <vector>

using namespace std;

class SpotterTest : public ::testing::Test
{
    void SetUp()
    {
        m_board = new GomokuBoard(k_BOARD_SIZE);
        SetBoard(*m_board);
    }

    void TearDown()
    {
        delete m_board;
        m_spotter.resetInstance();
    }

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;

    void SetBoard(const Board& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }
    GomokuBoard* m_board{nullptr};
    //spotter works on m_board indirectly (via Score class)
    Spotter m_spotter{Board::Player::PLAYER_A};
};

uint32_t countThreats(const vector<Spotter::SpottedThreats>& v, ThreatFinder::KindOfThreats m_threatKind)
{
    std::count_if(v.begin(), v.end(), [&m_threatKind](auto& t) { return t.m_threatKind==m_threatKind; });
}

TEST_F(SpotterTest, ExecuteTest_FindingTwoListThreats1)
{
    // Board precondition.
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | x |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);

    // Action1.
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | x | x |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    const Board::PositionXY moveAction1 = Board::PositionXY(2, 3);
    m_board->putMove(moveAction1, Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out=m_spotter.execute(moveAction1, false);

    // ASSERT_TRUE board score to verify if threat has been found.
    ASSERT_TRUE(1 == out.size());
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(SpotterTest, ExecuteTest_FindingTwoListThreats2)
{
    // Board precondition.
    // ----------------------------------------------
    //  |   |   |   | o |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | x |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    m_board->putMove(Board::PositionXY(0, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);

    // Action.
    // ----------------------------------------------
    //  |   |   |   | o |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | x | x  |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    const Board::PositionXY moveAction1 = Board::PositionXY(2, 3);
    m_board->putMove(moveAction1, Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out=m_spotter.execute(moveAction1, false);

    // ASSERT_TRUE board score to verify if threat has been found.
    ASSERT_TRUE(2 == out.size());
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_2_CASE_A));
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, ExecuteTest_ThreatGetPromotion1)
{
    // IGNORE_ALL_LEAKS_IN_TEST();
    // Precondition.
    // ----------------------------------------------
    //  |   |   |   | o |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | x | x |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   | o |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    m_board->putMove(Board::PositionXY(0, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 5), Board::PLAYER_B);

    // We are going to add 'x' to (2,4). But first add existing threat that will be involved. Normally its done by
    // ohter class
    const Board::PositionXY moveAction1 = Board::PositionXY(2, 4);

    const Spotter::RegionToInvestigate regionToInvestigate1{moveAction1, ThreatFinder::THREAT_2_CASE_A,
                                                            ThreatFinder::HORIZONTAL};
    m_spotter.addToExecute(regionToInvestigate1);

    // Action.
    // ----------------------------------------------
    //  |   |   |   | o |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | x | x | x |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   | o |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    m_board->putMove(moveAction1, Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out=m_spotter.execute(moveAction1, false);

    // ThreatFinder::THREAT_2_CASE_A threat will be promoted to ThreatFinder::THREAT_3_CASE_C
    ASSERT_TRUE(0 == countThreats(out, ThreatFinder::THREAT_2_CASE_A));
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_3_CASE_A));
}

TEST_F(SpotterTest, ExecuteTest_ThreatGetPromotion2)
{
    // Precondition.
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | x |   |   |   | x |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x |   | x |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x |   | x |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | x |   |   |   | x |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(5, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(6, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(5, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(6, 2), Board::PLAYER_A);

    // We are going to add 'x' to (4,4). But first add existing threat that will be involved. Normally its done by
    // other class
    const Board::PositionXY moveAction = Board::PositionXY(4, 4);

    const Spotter::RegionToInvestigate regionToInvestigate1{moveAction, ThreatFinder::THREAT_4_CASE_C,
                                                            ThreatFinder::FALLING};
    const Spotter::RegionToInvestigate regionToInvestigate2{moveAction, ThreatFinder::THREAT_4_CASE_C,
                                                            ThreatFinder::RISING};
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // Action.
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | x |   |   |   | x |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x |   | x |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   | x |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x |   | x |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | x |   |   |   | x |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    m_board->putMove(moveAction, Board::PLAYER_A);

    const vector<Spotter::SpottedThreats> out=m_spotter.execute(moveAction, false);

    ASSERT_TRUE(2 == out.size());
    ASSERT_TRUE(2 == countThreats(out, ThreatFinder::THREAT_WINNER));
}

TEST_F(SpotterTest, ExecuteTest_ThreatGetDissmision1)
{
    // Precondition.
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   | o |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   | x | x |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x | o |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 3), Board::PLAYER_A);

    // Following two moves are to shot down unimportant threat on falling trend.
    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(4, 4), Board::PLAYER_B);

    const Spotter::RegionToInvestigate regionToInvestigate1{Board::PositionXY(2, 2), ThreatFinder::THREAT_2_CASE_A,
                                                            ThreatFinder::HORIZONTAL};
    const Spotter::RegionToInvestigate regionToInvestigate2{Board::PositionXY(3, 3), ThreatFinder::THREAT_2_CASE_A,
                                                            ThreatFinder::VERTICAL};
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // Opponent is going put its move (2,3).
    const Board::PositionXY moveAction1 = Board::PositionXY(2, 3);

    // Action.
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   | o |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   | x | x | o |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | x | o |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    m_board->putMove(moveAction1, Board::PLAYER_B);

    // Horizontal threat THREAT_2_CASE_A will be completely shout down.
    // Vertical threat THREAT_2_CASE_A will be dismissed to THREAT_2_CASE_B.
    // For sure, there won't be any promotion.
    const vector<Spotter::SpottedThreats> out=m_spotter.execute(moveAction1, true);

    ASSERT_TRUE(1 == out.size());
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, ExecuteTest_ThreatGetDissmision2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. x x x . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|

    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);

    const Spotter::RegionToInvestigate regionToInvestigate1{Board::PositionXY(1, 2), ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::HORIZONTAL};
    m_spotter.addToExecute(regionToInvestigate1);

    // Action.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. x x x . o . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|

    // Opponent is going put its move (1,5).
    const Board::PositionXY moveAction1 = Board::PositionXY(1, 5);
    m_board->putMove(moveAction1, Board::PLAYER_B);

    const vector<Spotter::SpottedThreats> out=m_spotter.execute(moveAction1, true);

    ASSERT_TRUE(1 == out.size());
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_3_CASE_C));
}

TEST_F(SpotterTest, ExecuteTest_ThreatGetDissmision3)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. x x . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|

    m_board->putMove(Board::PositionXY(1, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 2), Board::PLAYER_A);

    const Spotter::RegionToInvestigate regionToInvestigate1{Board::PositionXY(1, 2), ThreatFinder::THREAT_2_CASE_A,
                                                            ThreatFinder::HORIZONTAL};
    m_spotter.addToExecute(regionToInvestigate1);

    // Action.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. x x . . o . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|

    // Opponent is going put its move (1,5).
    const Board::PositionXY moveAction1 = Board::PositionXY(1, 5);
    m_board->putMove(moveAction1, Board::PLAYER_B);

    const vector<Spotter::SpottedThreats> out=m_spotter.execute(moveAction1, true);
    ASSERT_TRUE(1 == out.size());
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_2_CASE_C));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_BTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . o x x . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out=m_spotter.execute(Board::PositionXY(2, 6), false);
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 = m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_B));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_BTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |x . x . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1=  m_spotter.execute(Board::PositionXY(2, 2), false);
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_B));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_BTest3)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |x . x . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 = m_spotter.execute(Board::PositionXY(2, 2), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2= m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_B));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_BTest4)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(3, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1= m_spotter.execute(Board::PositionXY(1, 3), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_C));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 2);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_C,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_C));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_CTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(3, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1=m_spotter.execute(Board::PositionXY(1, 3), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_C));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(0, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_C,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_C));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_ATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . x . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1=m_spotter.execute(Board::PositionXY(2, 3), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_A));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_ATest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . x . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. x . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(4, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1=m_spotter.execute(Board::PositionXY(1, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_A));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_ATest3)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . x . x .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 11), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 13), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1=m_spotter.execute(Board::PositionXY(2, 13), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 14);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_B));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_ATest4)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . x . x .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 11), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 13), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 = m_spotter.execute(Board::PositionXY(2, 13), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 = m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_AA));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_ATest5)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x . . . x x . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);

    const vector<Spotter::SpottedThreats> out1=m_spotter.execute(Board::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 9), Board::PLAYER_A);

    const vector<Spotter::SpottedThreats> out2=m_spotter.execute(Board::PositionXY(2, 8), false);
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 5);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // Current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x x . . x x . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out3=m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out3.size());
    ASSERT_TRUE(1 == countThreats(out3, ThreatFinder::THREAT_3_CASE_A));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_ATest6)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . x x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);

    const vector<Spotter::SpottedThreats> out1=m_spotter.execute(Board::PositionXY(2, 7), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_AATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . . . x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 2);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, false);

    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x x . . x . . . . . . . . .|

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_AA));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_AATest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . . . x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotter.execute(moveAction, false);

    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . x . x . . . . . . . . .|

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_AA));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_AATest3)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . . . x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, false);

    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . . . x x . . . . . . . .|

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_AATest4)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . . . x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, true);

    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . . . x o . . . . . . . .|

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out2.size());
}

TEST_F(SpotterTest, PromotionTHREAT_2_CASE_AATest5)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . . . x . . o . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_B);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, false);

    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . . . x . x o . . . . . .|

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_BTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x . x x . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_B));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_BTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |x . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(4, 0), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(0, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_B,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_B));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_CTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o . x x x . o . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 9), Board::PLAYER_B);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_C,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // current state.
    //	                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o . x x x x o . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_C));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_CTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|

    m_board->putMove(Board::PositionXY(3, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(0, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_C,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // current state.
    //	                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . x . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_C));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_CTest3)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x . x . x o . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 9), Board::PLAYER_B);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 5);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_C,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // current state.
    //	                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x x x . x o . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_C));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_CTest4)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . x . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|

    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 5);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x x x . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_AA));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_ATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . x x . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|

    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_A));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_ATest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . x x x . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|

    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_A));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_ATest3)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o . x . x x . o . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|

    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 9), Board::PLAYER_B);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o . x . x x x o . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_B));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_ATest4)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . x . . . . . . . . . .|
    //	2 |. . . x . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. x . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(4, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(5, 0);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_A,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . x . . . . . . . . . .|
    //	2 |. . . x . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. x . . . . . . . . . . . . .|
    //	5 |x . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_B));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_ATest5)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x x x . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);
    // current state
    //                           1 1 1 1 1
    //       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //       _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //    0 |. . . . . . . . . . . . . . .|
    //    1 |. . . . . . . . . . . . . . .|
    //    2 |. . . . x x x . x . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_AA));
}

TEST_F(SpotterTest, PromotionTHREAT_3_CASE_ATest6)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . x . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);
    // current state
    //                           1 1 1 1 1
    //       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //       _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //    0 |. . . . . . . . . . . . . . .|
    //    1 |. . . . . . . . . . . . . . .|
    //	  2 |. . . . x . x . x x . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // d. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // e. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // f. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_3_CASE_A));
}

TEST_F(SpotterTest, PromotionTHREAT_4_CASE_BTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x x x . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_4_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x x x x x . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_WINNER));
}

TEST_F(SpotterTest, PromotionTHREAT_4_CASE_BTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . x . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(0, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 1), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(4, 0);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_4_CASE_C,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . x . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |x . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_WINNER));
}

TEST_F(SpotterTest, PromotionTHREAT_4_CASE_CTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x . x x x . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_4_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x x x x . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_WINNER));
}

TEST_F(SpotterTest, PromotionTHREAT_4_CASE_CTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . x . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |x . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(0, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 0), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 2);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_4_CASE_C,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // Current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . x . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |x . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_WINNER));
}

TEST_F(SpotterTest, PromotionTHREAT_4_CASE_ATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_4_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);
    //	                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x x x . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_WINNER));
}

TEST_F(SpotterTest, DismissalTHREAT_2_CASE_BTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . . x o . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction      = Board::PositionXY(2, 3);
    const Board::PositionXY elementOfThreat = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state:
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x . . x o . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // d. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // e. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, true);

    // f. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out2.size());
}

TEST_F(SpotterTest, DismissalTHREAT_2_CASE_CTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o . x . x . o . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 6), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_C));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction      = Board::PositionXY(2, 5);
    const Board::PositionXY elementOfThreat = Board::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat, ThreatFinder::THREAT_2_CASE_C,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out2.size());
}

TEST_F(SpotterTest, DismissalTHREAT_2_CASE_ATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . x x .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 12), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 13), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 13), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction      = Board::PositionXY(2, 10);
    const Board::PositionXY elementOfThreat = Board::PositionXY(2, 13);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);

    // current state:
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . o . x x .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out2.size());
}

TEST_F(SpotterTest, DismissalTHREAT_2_CASE_ATest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . x x .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 12), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 13), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 13), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction      = Board::PositionXY(2, 14);
    const Board::PositionXY elementOfThreat = Board::PositionXY(2, 13);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);

    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . x x o|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_2_CASE_ATest3)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . x . x .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 11), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 13), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 13), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction      = Board::PositionXY(2, 9);
    const Board::PositionXY elementOfThreat = Board::PositionXY(2, 13);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . o . x . x .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_C));
}

TEST_F(SpotterTest, DismissalTHREAT_2_CASE_AATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . . . x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 2);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x o . . x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out2.size());
}

TEST_F(SpotterTest, DismissalTHREAT_2_CASE_AATest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x . . . x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 1), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction       = Board::PositionXY(2, 0);
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 1);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat1, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |o x . . . x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_3_CASE_BTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o x x . x . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_B,
                                                            ThreatFinder::HORIZONTAL};
    const Board::PositionXY elementOfThreat2 = Board::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_3_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o x x o x . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out1.size());
}

TEST_F(SpotterTest, DismissalTHREAT_3_CASE_BTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o x . x x . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_B,
                                                            ThreatFinder::HORIZONTAL};
    const Board::PositionXY elementOfThreat2 = Board::PositionXY(2, 5);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_3_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 4);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o x o x x . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_3_CASE_CTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 1), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(1, 3);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_C,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(0, 4);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |o . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out1.size());
}

TEST_F(SpotterTest, DismissalTHREAT_3_CASE_CTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . x . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |x . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(0, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 0), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(0, 4);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_C,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(1, 3);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);

    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . x . . . . . . . . . .|
    //	1 |. . . o . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |x . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out1.size());
}

TEST_F(SpotterTest, DismissalTHREAT_3_CASE_CTest3)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . x . x . x . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(1, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(1, 7), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(1, 7);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_AA,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(1, 4);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . x o x . x . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_3_CASE_ATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 6);  //. x x x . .  <- that is threat found

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);

    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x . o . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_3_CASE_A));
}

TEST_F(SpotterTest, DismissalTHREAT_3_CASE_ATest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 1);  //. x x x . .  <- that is threat found

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. o x x x . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_3_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_3_CASE_ATest3)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x . . . . . . . . . . .|
    //	3 |. . x . . . . . . . . . . . .|
    //	4 |. x . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 1), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(4, 1);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::RISING};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(0, 5);  //. x x x . .  <- that is threat found

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x . . . . . . . . . . .|
    //	3 |. . x . . . . . . . . . . . .|
    //	4 |. x . . . . . . . . . . . . .|
    //	5 |o . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 = m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_3_CASE_C));
}

TEST_F(SpotterTest, DismissalTHREAT_3_CASE_ATest4)
{
    // Precondition.
    //	.                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x . x . . . . . . . .|

    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::HORIZONTAL};

    const Board::PositionXY elementOfThreat2 = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	.                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x o x . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_4_CASE_BTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x . x o . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    const Board::PositionXY elementOfThreat2 = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x o x o . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_3_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_4_CASE_BTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x . x x o . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    const Board::PositionXY elementOfThreat2 = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x o x x o . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_4_CASE_BTest3) {
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x . x x o . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    const Board::PositionXY elementOfThreat2 = Board::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 4);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x o x x o . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 = m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out1.size());
}

TEST_F(SpotterTest, DismissalTHREAT_4_CASE_CTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x . x x . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_AA,
                                                            ThreatFinder::HORIZONTAL};

    const Board::PositionXY elementOfThreat2 = Board::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_AA,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 4);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x o x x . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_4_CASE_CTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x . x x . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_AA,
                                                            ThreatFinder::HORIZONTAL};

    const Board::PositionXY elementOfThreat2 = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_AA,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x o x x . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(2 == out1.size());
    ASSERT_TRUE(2 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_4_CASE_CTest3)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o x x . x x o . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_C,
                                                            ThreatFinder::HORIZONTAL};

    const Board::PositionXY elementOfThreat2 = Board::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_C,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o x x o x x o . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);
    m_spotter.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out1.size());
}

TEST_F(SpotterTest, DismissalTHREAT_4_CASE_ATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(2, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_A,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 1);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. o x x x x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_B));
}

TEST_F(SpotterTest, DismissalTHREAT_4_CASE_ATest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . x . . . . . . . . . .|
    //	2 |. . . x . . . . . . . . . . .|
    //	3 |. . x . . . . . . . . . . . .|
    //	4 |. x . . . . . . . . . . . . .|
    //	5 |. . . . . . . . . . . . . . .|
    //	6 |. . . . . . . . . . . . . . .|
    //	7 |. . . . . . . . . . . . . . .|
    //	8 |. . . . . . . . . . . . . . .|
    //	9 |. . . . . . . . . . . . . . .|
    //	10|. . . . . . . . . . . . . . .|
    //	11|. . . . . . . . . . . . . . .|
    m_board->putMove(Board::PositionXY(1, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(3, 2), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(4, 1), Board::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const Board::PositionXY elementOfThreat1 = Board::PositionXY(4, 1);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_A,
                                                            ThreatFinder::RISING};

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(5, 0);

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . x . . . . . . . . . .|
    //	2 |. . . x . . . . . . . . . . .|
    //	3 |. . x . . . . . . . . . . . .|
    //	4 |. x . . . . . . . . . . . . .|
    //	5 |o . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, true);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_4_CASE_B));
}

TEST_F(SpotterTest, EdgeTHREAT_2_CASE_BTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . o x x . . . * . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // Action:  oxx...* -> oxx..x* (3B)
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . o x x . . x . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //--------------------------------------------------------------------------------------------

    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 6), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_3_CASE_B));
}

TEST_F(SpotterTest, EdgeTHREAT_2_CASE_BTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . o x . . . x * . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // Action: ox...x* -> ox...xx (2A)
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . o x . . . x x . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //--------------------------------------------------------------------------------------------

    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 9), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 9), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 10);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(SpotterTest, EdgeTHREAT_2_CASE_AATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . . . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // Action: .x...x. -> .x...xx (2A)
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . . . x x . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //--------------------------------------------------------------------------------------------

    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(SpotterTest, EdgeTHREAT_2_CASE_AATest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . . . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // Action: .x...x. -> .x...x.x (2AA + 2A)
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . . . x . x . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //--------------------------------------------------------------------------------------------

    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 10);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
     m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(SpotterTest, EdgeTHREAT_2_CASE_ATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // Action: .xx...* -> .xx...x (2A)
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x x . . . x . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //--------------------------------------------------------------------------------------------

    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out2.size());

    //but 2A shall be still recognizable
    const vector<Spotter::SpottedThreats> out3 =m_spotter.execute(Board::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out3.size());
    ASSERT_TRUE(1 == countThreats(out3, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(SpotterTest, EdgeTHREAT_2_CASE_ATest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . x . . * . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // Action: .x.x..* -> .x.x..x (2x2A)
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . x . . x . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //--------------------------------------------------------------------------------------------

    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(Board::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(SpotterTest, EdgeTHREAT_3_CASE_BTest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x x x . . * . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // Action: oxxx..* -> oxxx..x (none)
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x x x . . x . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //--------------------------------------------------------------------------------------------
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out1.size());
}

TEST_F(SpotterTest, EdgeTHREAT_3_CASE_BTest2)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x x . x . * . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // Action: oxx.x.* -> oxx.x.x (2A)
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x x . x . x . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //--------------------------------------------------------------------------------------------
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_B);
    m_board->putMove(Board::PositionXY(2, 4), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 5), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 7), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(SpotterTest, EdgeTHREAT_3_CASE_AATest1)
{
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . x . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // Action: .x.x.x. -> .x.x.xx (3A)
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x . x . x x . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //--------------------------------------------------------------------------------------------
    m_board->putMove(Board::PositionXY(2, 3), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 6), Board::PLAYER_A);
    m_board->putMove(Board::PositionXY(2, 8), Board::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const Board::PositionXY moveAction = Board::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, Board::PLAYER_A);

    // c. Remove all existing threats.
    m_spotter.resetInstance();

    // c. Tells spotter where should search.
    m_spotter.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotter.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_3_CASE_A));
}

