#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "Interfaces/IBoard.h"
#include "Score.h"
#include "Spotter.h"

using namespace std;

class SpotterTest : public ::testing::Test
{
    void SetUp()
    {
        SetBoard(*m_board);
    }

    void TearDown()
    {
        delete m_board;
        m_spotterA.resetInstance();
        m_spotterB.resetInstance();
    }

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;

    void SetBoard(const IBoard& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }

    GomokuBoard* m_board= new GomokuBoard(k_BOARD_SIZE);
    Spotter m_spotterA{IBoard::Player::PLAYER_A};
    Spotter m_spotterB{IBoard::Player::PLAYER_B};
};

uint32_t countThreats(const vector<Spotter::SpottedThreats>& v, ThreatFinder::KindOfThreats m_threatKind)
{
    const uint32_t retVal = std::count_if(v.begin(), v.end(), [&m_threatKind](auto& t) { return t.m_threatKind==m_threatKind; });
    return retVal;
}

TEST_F(SpotterTest, ExecuteTest_FindingTwoListThreats1)
{
    // IBoard precondition.
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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);

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
    const IBoard::PositionXY moveAction1 = IBoard::PositionXY(2, 3);
    m_board->putMove(moveAction1, IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out=m_spotterA.execute(moveAction1, false);

    // ASSERT_TRUE board score to verify if threat has been found.
    ASSERT_TRUE(1 == out.size());
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(SpotterTest, ExecuteTest_FindingTwoListThreats2)
{
    // IBoard precondition.
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
    m_board->putMove(IBoard::PositionXY(0, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);

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
    const IBoard::PositionXY moveAction1 = IBoard::PositionXY(2, 3);
    m_board->putMove(moveAction1, IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out=m_spotterA.execute(moveAction1, false);

    // ASSERT_TRUE board score to verify if threat has been found.
    ASSERT_TRUE(2 == out.size());
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_2_CASE_A));
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_2_CASE_B));

    //----------------------The same but switch players-------------
    // IBoard precondition.
    // ----------------------------------------------
    //  |   |   |   | x |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | o |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | o |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    m_board->putMove(IBoard::PositionXY(0, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_B);

    // Action.
    // ----------------------------------------------
    //  |   |   |   | x |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   | o |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   | o | o  |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    //  |   |   |   |   |   |   |   |   |   |   |
    // ----------------------------------------------
    const IBoard::PositionXY moveAction2 = IBoard::PositionXY(2, 3);
    m_board->putMove(moveAction2, IBoard::PLAYER_B);
    const vector<Spotter::SpottedThreats> out2=m_spotterB.execute(moveAction2, false);
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
    m_board->putMove(IBoard::PositionXY(0, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 5), IBoard::PLAYER_B);

    // We are going to add 'x' to (2,4). But first add existing threat that will be involved. Normally its done by
    // ohter class
    const IBoard::PositionXY moveAction1 = IBoard::PositionXY(2, 4);

    const Spotter::RegionToInvestigate regionToInvestigate1{moveAction1, ThreatFinder::THREAT_2_CASE_A,
                                                            ThreatFinder::HORIZONTAL};
    m_spotterA.addToExecute(regionToInvestigate1);

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
    m_board->putMove(moveAction1, IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out=m_spotterA.execute(moveAction1, false);

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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(6, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(5, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(6, 2), IBoard::PLAYER_A);

    // We are going to add 'x' to (4,4). But first add existing threat that will be involved. Normally its done by
    // other class
    const IBoard::PositionXY moveAction = IBoard::PositionXY(4, 4);

    const Spotter::RegionToInvestigate regionToInvestigate1{moveAction, ThreatFinder::THREAT_4_CASE_C,
                                                            ThreatFinder::FALLING};
    const Spotter::RegionToInvestigate regionToInvestigate2{moveAction, ThreatFinder::THREAT_4_CASE_C,
                                                            ThreatFinder::RISING};
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

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
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    const vector<Spotter::SpottedThreats> out=m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 3), IBoard::PLAYER_A);

    // Following two moves are to shot down unimportant threat on falling trend.
    m_board->putMove(IBoard::PositionXY(1, 1), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(4, 4), IBoard::PLAYER_B);

    const Spotter::RegionToInvestigate regionToInvestigate1{IBoard::PositionXY(2, 2), ThreatFinder::THREAT_2_CASE_A,
                                                            ThreatFinder::HORIZONTAL};
    const Spotter::RegionToInvestigate regionToInvestigate2{IBoard::PositionXY(3, 3), ThreatFinder::THREAT_2_CASE_A,
                                                            ThreatFinder::VERTICAL};
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

    // Opponent is going put its move (2,3).
    const IBoard::PositionXY moveAction1 = IBoard::PositionXY(2, 3);

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
    m_board->putMove(moveAction1, IBoard::PLAYER_B);

    // Horizontal threat THREAT_2_CASE_A will be completely shout down.
    // Vertical threat THREAT_2_CASE_A will be dismissed to THREAT_2_CASE_B.
    // For sure, there won't be any promotion.
    const vector<Spotter::SpottedThreats> out=m_spotterA.execute(moveAction1, true);

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

    m_board->putMove(IBoard::PositionXY(1, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);

    const Spotter::RegionToInvestigate regionToInvestigate1{IBoard::PositionXY(1, 2), ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::HORIZONTAL};
    m_spotterA.addToExecute(regionToInvestigate1);

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
    const IBoard::PositionXY moveAction1 = IBoard::PositionXY(1, 5);
    m_board->putMove(moveAction1, IBoard::PLAYER_B);

    const vector<Spotter::SpottedThreats> out=m_spotterA.execute(moveAction1, true);

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

    m_board->putMove(IBoard::PositionXY(1, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 2), IBoard::PLAYER_A);

    const Spotter::RegionToInvestigate regionToInvestigate1{IBoard::PositionXY(1, 2), ThreatFinder::THREAT_2_CASE_A,
                                                            ThreatFinder::HORIZONTAL};
    m_spotterA.addToExecute(regionToInvestigate1);

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
    const IBoard::PositionXY moveAction1 = IBoard::PositionXY(1, 5);
    m_board->putMove(moveAction1, IBoard::PLAYER_B);

    const vector<Spotter::SpottedThreats> out=m_spotterA.execute(moveAction1, true);
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
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out=m_spotterA.execute(IBoard::PositionXY(2, 6), false);
    ASSERT_TRUE(1 == countThreats(out, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 = m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 0), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1=  m_spotterA.execute(IBoard::PositionXY(2, 2), false);
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 0), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 = m_spotterA.execute(IBoard::PositionXY(2, 2), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2= m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1= m_spotterA.execute(IBoard::PositionXY(1, 3), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_C));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 2);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_C,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1=m_spotterA.execute(IBoard::PositionXY(1, 3), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_C));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(0, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_C,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1=m_spotterA.execute(IBoard::PositionXY(2, 3), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1=m_spotterA.execute(IBoard::PositionXY(1, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 11), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 13), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1=m_spotterA.execute(IBoard::PositionXY(2, 13), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 14);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 11), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 13), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 = m_spotterA.execute(IBoard::PositionXY(2, 13), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 = m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);

    const vector<Spotter::SpottedThreats> out1=m_spotterA.execute(IBoard::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 9), IBoard::PLAYER_A);

    const vector<Spotter::SpottedThreats> out2=m_spotterA.execute(IBoard::PositionXY(2, 8), false);
    ASSERT_TRUE(1 == out2.size());
    ASSERT_TRUE(1 == countThreats(out2, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 5);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // Current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x x . . x x . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out3=m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);

    const vector<Spotter::SpottedThreats> out1=m_spotterA.execute(IBoard::PositionXY(2, 7), false);
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
    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 2);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2=m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_B);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(4, 0), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(0, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_B,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 9), IBoard::PLAYER_B);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_C,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // current state.
    //	                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o . x x x x o . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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

    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(0, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_C,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

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
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 9), IBoard::PLAYER_B);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 5);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_C,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // current state.
    //	                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x x x . x o . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 5);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . x x x . x . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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

    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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

    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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

    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 9), IBoard::PLAYER_B);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o . x . x x x o . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(5, 0);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_A,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);
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
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 8);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);
    // current state
    //                           1 1 1 1 1
    //       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //       _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //    0 |. . . . . . . . . . . . . . .|
    //    1 |. . . . . . . . . . . . . . .|
    //    2 |. . . . x x x . x . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);
    // current state
    //                           1 1 1 1 1
    //       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //       _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //    0 |. . . . . . . . . . . . . . .|
    //    1 |. . . . . . . . . . . . . . .|
    //	  2 |. . . . x . x . x x . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // d. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // e. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_4_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x x x x x . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(0, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(4, 0);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_4_CASE_C,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

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
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_4_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x x x x . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(0, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 0), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 2);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_4_CASE_C,
                                                           ThreatFinder::RISING};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

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
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_4_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);
    //	                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x x x . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction      = IBoard::PositionXY(2, 3);
    const IBoard::PositionXY elementOfThreat = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state:
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . o x . . x o . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // d. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // e. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 6), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_C));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction      = IBoard::PositionXY(2, 5);
    const IBoard::PositionXY elementOfThreat = IBoard::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat, ThreatFinder::THREAT_2_CASE_C,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 12), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 13), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 13), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction      = IBoard::PositionXY(2, 10);
    const IBoard::PositionXY elementOfThreat = IBoard::PositionXY(2, 13);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);

    // current state:
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . o . x x .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 12), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 13), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 13), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction      = IBoard::PositionXY(2, 14);
    const IBoard::PositionXY elementOfThreat = IBoard::PositionXY(2, 13);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);

    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . . . . x x o|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 11), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 13), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 13), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction      = IBoard::PositionXY(2, 9);
    const IBoard::PositionXY elementOfThreat = IBoard::PositionXY(2, 13);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . . . . . . . o . x . x .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 2);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. x o . . x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 1), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 5), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction       = IBoard::PositionXY(2, 0);
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 1);
    const Spotter::RegionToInvestigate regionToInvestigate{elementOfThreat1, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |o x . . . x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_B,
                                                            ThreatFinder::HORIZONTAL};
    const IBoard::PositionXY elementOfThreat2 = IBoard::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_3_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o x x o x . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_B,
                                                            ThreatFinder::HORIZONTAL};
    const IBoard::PositionXY elementOfThreat2 = IBoard::PositionXY(2, 5);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_3_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 4);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o x o x x . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 1), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(1, 3);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_C,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(0, 4);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . x . . . . . . . . . . .|
    //	2 |. . x . . . . . . . . . . . .|
    //	3 |. x . . . . . . . . . . . . .|
    //	4 |o . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(0, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 0), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(0, 4);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_C,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(1, 3);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);

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
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(1, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(1, 7), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(1, 7);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_AA,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(1, 4);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . x o x . x . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 6);  //. x x x . .  <- that is threat found

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);

    // Precondition.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x . o . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 1);  //. x x x . .  <- that is threat found

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. o x x x . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(4, 1);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::RISING};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(0, 5);  //. x x x . .  <- that is threat found

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
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
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 = m_spotterA.execute(moveAction, true);

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

    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::HORIZONTAL};

    const IBoard::PositionXY elementOfThreat2 = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_3_CASE_A,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	.                       1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x o x . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    const IBoard::PositionXY elementOfThreat2 = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x x o x o . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    const IBoard::PositionXY elementOfThreat2 = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x o x x o . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    const IBoard::PositionXY elementOfThreat2 = IBoard::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_B,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 4);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x o x x o . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 = m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 6);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_AA,
                                                            ThreatFinder::HORIZONTAL};

    const IBoard::PositionXY elementOfThreat2 = IBoard::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_AA,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 4);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . x x o x x . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_AA,
                                                            ThreatFinder::HORIZONTAL};

    const IBoard::PositionXY elementOfThreat2 = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_AA,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . . x x o x x . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 7);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_C,
                                                            ThreatFinder::HORIZONTAL};

    const IBoard::PositionXY elementOfThreat2 = IBoard::PositionXY(2, 4);
    const Spotter::RegionToInvestigate regionToInvestigate2{elementOfThreat2, ThreatFinder::THREAT_4_CASE_C,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 5);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. . o x x o x x o . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);
    m_spotterA.addToExecute(regionToInvestigate2);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(2, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(2, 3);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_A,
                                                            ThreatFinder::HORIZONTAL};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 1);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
    // current state.
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . . . . . . . . . .|
    //	2 |. o x x x x . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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
    m_board->putMove(IBoard::PositionXY(1, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(3, 2), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(4, 1), IBoard::PLAYER_A);

    // Assume that creating threat is recognized correctly.
    const IBoard::PositionXY elementOfThreat1 = IBoard::PositionXY(4, 1);
    const Spotter::RegionToInvestigate regionToInvestigate1{elementOfThreat1, ThreatFinder::THREAT_4_CASE_A,
                                                            ThreatFinder::RISING};

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(5, 0);

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_B);
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
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate1);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, true);

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

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 6), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, false);

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

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 9), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 9), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_B));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 10);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, false);

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

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, false);

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

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_AA));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 10);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
     m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, false);

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

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(0 == out2.size());

    //but 2A shall be still recognizable
    const vector<Spotter::SpottedThreats> out3 =m_spotterA.execute(IBoard::PositionXY(2, 4), false);
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

    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(IBoard::PositionXY(2, 4), false);
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_2_CASE_A));

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_2_CASE_A,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out2 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_B);
    m_board->putMove(IBoard::PositionXY(2, 4), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 5), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 7), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_B,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

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
    m_board->putMove(IBoard::PositionXY(2, 3), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 6), IBoard::PLAYER_A);
    m_board->putMove(IBoard::PositionXY(2, 8), IBoard::PLAYER_A);
    // Assume that creating threat is recognized correctly.

    // Do some actions:
    // a. define some constants.
    const IBoard::PositionXY moveAction = IBoard::PositionXY(2, 9);
    const Spotter::RegionToInvestigate regionToInvestigate{moveAction, ThreatFinder::THREAT_3_CASE_AA,
                                                           ThreatFinder::HORIZONTAL};

    // b. Put a new move which is
    m_board->putMove(moveAction, IBoard::PLAYER_A);

    // c. Remove all existing threats.
    m_spotterA.resetInstance();

    // c. Tells spotter where should search.
    m_spotterA.addToExecute(regionToInvestigate);

    // d. Run spotter.
    const vector<Spotter::SpottedThreats> out1 =m_spotterA.execute(moveAction, false);

    // e. ASSERT_TRUE if threat change its strength.
    ASSERT_TRUE(1 == out1.size());
    ASSERT_TRUE(1 == countThreats(out1, ThreatFinder::THREAT_3_CASE_A));
}

