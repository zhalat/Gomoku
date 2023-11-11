#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>
#include "IBoard.h"
#include "Score.h"
#include "Spotter.h"
#include "ThreatTracker.h"

using namespace std;

static bool isOntheList(const IBoard::PositionXY xy, const vector<IBoard::PositionXY>& vct);

class ThreatTrackerTest : public ::testing::Test
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(15);
        m_spotterHuman   = make_shared<Spotter>(IBoard::PLAYER_A);
        m_spotterCpu   = make_shared<Spotter>(IBoard::PLAYER_B);
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterHuman.get());
        m_trackerCpu   = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterCpu.get());
        m_trackerHuman->setBoard(*m_board.get());
        m_trackerCpu->setBoard(*m_board.get());
    }

    void TearDown()
    {}

public:
    // IBoard for game.
    unique_ptr<IBoard> m_board;
    shared_ptr<ISpotter> m_spotterHuman;
    shared_ptr<ISpotter> m_spotterCpu;
    unique_ptr<ThreatTracker> m_trackerHuman;
    unique_ptr<ThreatTracker> m_trackerCpu;
};

TEST_F(ThreatTrackerTest, AddThreatsTest1)
{
    // Define some threat pairs [threatBegin, threatEnd]
    const IBoard::PositionXY threat1Begin = IBoard::PositionXY(5, 1);  // assume its Threat2CaseA
    const IBoard::PositionXY threat1End   = IBoard::PositionXY(5, 6);
    const uint32_t threat1Value          = Score::THREAT_2_CASE_A_SCORE;

    const IBoard::PositionXY threat2Begin = IBoard::PositionXY(2, 4);  // assume its Threat2CaseA
    const IBoard::PositionXY threat2End   = IBoard::PositionXY(6, 4);
    const uint32_t threat2Value          = Score::THREAT_2_CASE_A_SCORE;

    const IBoard::PositionXY threat3Begin = IBoard::PositionXY(0, 8);  // assume its Threat2CaseB
    const IBoard::PositionXY threat3End   = IBoard::PositionXY(5, 8);
    const uint32_t threat3Value          = Score::THREAT_2_CASE_B_SCORE;

    const IBoard::PositionXY threat4Begin = IBoard::PositionXY(5, 8);  // assume its Threat3CaseB
    const IBoard::PositionXY threat4End   = IBoard::PositionXY(5, 13);
    const uint32_t threat4Value          = Score::THREAT_3_CASE_B_SCORE;

    const IBoard::PositionXY threat5Begin = IBoard::PositionXY(8, 4);  // assume its Threat4CaseC
    const IBoard::PositionXY threat5End   = IBoard::PositionXY(8, 8);
    const uint32_t threat5Value          = Score::THREAT_4_CASE_C_SCORE;

    // On empty board there are no threats.
    ASSERT_TRUE(0 == m_trackerHuman->getScore());

    ThreatFinder::ThreatLocation threatContainer;

    // Add threat, then check score.
    threatContainer.m_threatDetails.m_beginningThreat = threat1Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat1End;
    threatContainer.m_trend                           = ThreatFinder::HORIZONTAL;
    EXPECT_EQ(true, m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_A));
    ASSERT_TRUE(threat1Value == m_trackerHuman->getScore());

    threatContainer.m_threatDetails.m_beginningThreat = threat2Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat2End;
    threatContainer.m_trend                           = ThreatFinder::VERTICAL;
    EXPECT_EQ(true, m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_A));
    ASSERT_TRUE((threat1Value + threat2Value) == m_trackerHuman->getScore());

    threatContainer.m_threatDetails.m_beginningThreat = threat3Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat3End;
    threatContainer.m_trend                           = ThreatFinder::VERTICAL;
    EXPECT_EQ(true, m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_B));
    ASSERT_TRUE((threat1Value + threat2Value + threat3Value) == m_trackerHuman->getScore());

    threatContainer.m_threatDetails.m_beginningThreat = threat4Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat4End;
    threatContainer.m_trend                           = ThreatFinder::HORIZONTAL;
    EXPECT_EQ(true, m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_B));
    ASSERT_TRUE((threat1Value + threat2Value + threat3Value + threat4Value) == m_trackerHuman->getScore());

    threatContainer.m_threatDetails.m_beginningThreat = threat5Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat5End;
    threatContainer.m_trend                           = ThreatFinder::HORIZONTAL;
    EXPECT_EQ(true, m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_4_CASE_C));
    ASSERT_TRUE((threat1Value + threat2Value + threat3Value + threat4Value + threat5Value) ==
                m_trackerHuman->getScore());
}

TEST_F(ThreatTrackerTest, RemoveThreatsRemoveAllTest1)
{
    // Add one threat and remove it. Score shall be clear.
    // Define threat pairs [threatBegin, threatEnd]
    const IBoard::PositionXY threat1Begin = IBoard::PositionXY(5, 1);  // assume its Threat2CaseC
    const IBoard::PositionXY threat1End   = IBoard::PositionXY(5, 6);

    ThreatFinder::ThreatLocation threatContainer;

    // Add threat, then check score.
    threatContainer.m_threatDetails.m_beginningThreat = threat1Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat1End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(5, 3);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(5, 4);
    threatContainer.m_trend                           = ThreatFinder::HORIZONTAL;

    // Empty board at the begining, so 0 score.
    ASSERT_TRUE(0 == m_trackerHuman->getScore());

    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_C);

    // A new move is a part of threat1 (newMove belongs to the threat).
    const IBoard::PositionXY newMove = IBoard::PositionXY(5, 5);
    ASSERT_TRUE(1 == m_trackerHuman->removeThreats(newMove));
    ASSERT_TRUE(0 == m_trackerHuman->getScore());
}

TEST_F(ThreatTrackerTest, RemoveThreatsRemoveAllTest2)
{
    // Add some threats of the same kind, then remove all of it separately.
    const IBoard::PositionXY threat1Begin = IBoard::PositionXY(3, 2);  // assume its Threat2CaseC
    const IBoard::PositionXY threat1End   = IBoard::PositionXY(3, 6);

    const IBoard::PositionXY threat2Begin = IBoard::PositionXY(7, 2);  // assume its Threat2CaseC
    const IBoard::PositionXY threat2End   = IBoard::PositionXY(7, 6);

    const IBoard::PositionXY threat3Begin = IBoard::PositionXY(3, 9);  // assume its Threat2CaseC
    const IBoard::PositionXY threat3End   = IBoard::PositionXY(7, 9);

    ThreatFinder::ThreatLocation threatContainer;

    // Add threat, then remove it. The score shall be 0.
    threatContainer.m_threatDetails.m_beginningThreat = threat1Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat1End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(3, 3);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(3, 4);
    threatContainer.m_trend                           = ThreatFinder::HORIZONTAL;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_C);

    threatContainer.m_threatDetails.m_beginningThreat = threat2Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat2End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(7, 3);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(7, 5);
    threatContainer.m_trend                           = ThreatFinder::HORIZONTAL;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_C);

    threatContainer.m_threatDetails.m_beginningThreat = threat3Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat3End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(4, 9);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(5, 9);
    threatContainer.m_trend                           = ThreatFinder::VERTICAL;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_C);

    // Each a new move belongs exactly to one of the previously added threat.
    IBoard::PositionXY newMovesList[] = {IBoard::PositionXY(3, 5), IBoard::PositionXY(7, 4), IBoard::PositionXY(6, 9)};

    // Remove sequentially.
    for(uint32_t i = 0; i < NUMELEM(newMovesList); ++i)
    {
        ASSERT_TRUE(1 == m_trackerHuman->removeThreats(newMovesList[i]));
    }

    ASSERT_TRUE(0 == m_trackerHuman->getScore());
}

TEST_F(ThreatTrackerTest, RemoveThreatsRemoveAllTest3)
{
    // Add some threats of the same kind, then remove at one.

    // Add some threats of the same kind, then remove all of it separately.
    const IBoard::PositionXY threat1Begin = IBoard::PositionXY(2, 2);  // assume its Threat3CaseA
    const IBoard::PositionXY threat1End   = IBoard::PositionXY(6, 6);

    const IBoard::PositionXY threat2Begin = IBoard::PositionXY(2, 4);  // assume its Threat3CaseA
    const IBoard::PositionXY threat2End   = IBoard::PositionXY(6, 4);

    const IBoard::PositionXY threat3Begin = IBoard::PositionXY(2, 6);  // assume its Threat3CaseA
    const IBoard::PositionXY threat3End   = IBoard::PositionXY(6, 2);

    const IBoard::PositionXY threat4Begin = IBoard::PositionXY(4, 2);  // assume its Threat3CaseA
    const IBoard::PositionXY threat4End   = IBoard::PositionXY(4, 6);

    const uint32_t numberOfThreats = 4;

    ThreatFinder::ThreatLocation threatContainer;

    // Add threat, then remove it. The socre shall be 0.
    threatContainer.m_threatDetails.m_beginningThreat = threat1Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat1End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(2, 2);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(6, 6);
    threatContainer.m_trend                           = ThreatFinder::FALLING;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_A);

    threatContainer.m_threatDetails.m_beginningThreat = threat2Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat2End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(2, 4);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(6, 4);
    threatContainer.m_trend                           = ThreatFinder::VERTICAL;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_A);

    threatContainer.m_threatDetails.m_beginningThreat = threat3Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat3End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(2, 6);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(6, 2);
    threatContainer.m_trend                           = ThreatFinder::RISING;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_A);

    threatContainer.m_threatDetails.m_beginningThreat = threat4Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat4End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(4, 2);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(4, 6);
    threatContainer.m_trend                           = ThreatFinder::HORIZONTAL;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_A);

    // List contains move but none of them belongs to any threat.
    IBoard::PositionXY newMovesList1[] = {IBoard::PositionXY(1, 7), IBoard::PositionXY(3, 2), IBoard::PositionXY(4, 1),
                                         IBoard::PositionXY(7, 7)};

    // Try remove. Nothing should happen.
    for(uint32_t i = 0; i < NUMELEM(newMovesList1); ++i)
    {
        ASSERT_TRUE(0 == m_trackerHuman->removeThreats(newMovesList1[i]));
    }

    // List contains move that belongs to all threat.
    IBoard::PositionXY newMovesList2[] = {IBoard::PositionXY(4, 4)};
    for(uint32_t i = 0; i < NUMELEM(newMovesList2); ++i)
    {
        ASSERT_TRUE(numberOfThreats == m_trackerHuman->removeThreats(newMovesList2[i]));
    }

    ASSERT_TRUE(0 == m_trackerHuman->getScore());
}

TEST_F(ThreatTrackerTest, RemoveThreatsPartiallyRemoveTest)
{
    // Threats are put of various kind.
    // Some of them are removed.

    // Define threats' locations.
    const IBoard::PositionXY threat1Begin = IBoard::PositionXY(1, 1);  // assume its Threat4CaseA
    const IBoard::PositionXY threat1End   = IBoard::PositionXY(5, 1);
    const uint32_t threat1Value          = Score::THREAT_4_CASE_A_SCORE;

    const IBoard::PositionXY threat2Begin = IBoard::PositionXY(1, 1);  // assume its Threat4CaseB
    const IBoard::PositionXY threat2End   = IBoard::PositionXY(1, 6);
    const uint32_t threat2Value          = Score::THREAT_4_CASE_B_SCORE;

    const IBoard::PositionXY threat3Begin = IBoard::PositionXY(1, 4);  // assume its Threat4CaseC
    const IBoard::PositionXY threat3End   = IBoard::PositionXY(5, 0);
    const uint32_t threat3Value          = Score::THREAT_4_CASE_C_SCORE;

    const IBoard::PositionXY threat4Begin = IBoard::PositionXY(3, 5);  // assume its Threat3CaseB
    const IBoard::PositionXY threat4End   = IBoard::PositionXY(6, 8);
    const uint32_t threat4Value          = Score::THREAT_3_CASE_B_SCORE;

    const IBoard::PositionXY threat5Begin = IBoard::PositionXY(7, 1);  // assume its Threat2CaseA
    const IBoard::PositionXY threat5End   = IBoard::PositionXY(7, 4);
    const uint32_t threat5Value          = Score::THREAT_2_CASE_A_SCORE;

    const uint32_t threatValueSum = threat1Value + threat2Value + threat3Value + threat4Value + threat5Value;

    ThreatFinder::ThreatLocation threatContainer;

    threatContainer.m_threatDetails.m_beginningThreat = threat1Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat1End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(1, 1);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(5, 1);
    threatContainer.m_trend                           = ThreatFinder::VERTICAL;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_4_CASE_A);

    threatContainer.m_threatDetails.m_beginningThreat = threat2Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat2End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(1, 1);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(1, 6);
    threatContainer.m_trend                           = ThreatFinder::HORIZONTAL;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_4_CASE_B);

    threatContainer.m_threatDetails.m_beginningThreat = threat3Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat3End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(1, 4);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(5, 0);
    threatContainer.m_trend                           = ThreatFinder::RISING;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_4_CASE_C);

    threatContainer.m_threatDetails.m_beginningThreat = threat4Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat4End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(3, 5);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(6, 8);
    threatContainer.m_trend                           = ThreatFinder::FALLING;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_B);

    threatContainer.m_threatDetails.m_beginningThreat = threat5Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat5End;
    threatContainer.m_threatDetails.m_myPawns[0]      = IBoard::PositionXY(7, 1);
    threatContainer.m_threatDetails.m_myPawns[1]      = IBoard::PositionXY(7, 4);
    threatContainer.m_trend                           = ThreatFinder::HORIZONTAL;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_A);

    // List contains move that belong to at least one threat.
    IBoard::PositionXY newMovesList[] = {IBoard::PositionXY(1, 1), IBoard::PositionXY(3, 2), IBoard::PositionXY(6, 8),
                                        IBoard::PositionXY(7, 1)};

    ASSERT_TRUE(threatValueSum == m_trackerHuman->getScore());

    // Score that will be subtracted after each move from newMovesList.
    const uint32_t score[] = {threat1Value + threat2Value, threat3Value, threat4Value, threat5Value};

    for(uint32_t i = 0, val = threatValueSum; i < NUMELEM(newMovesList); ++i)
    {
        ASSERT_TRUE(1 <= m_trackerHuman->removeThreats(newMovesList[i]));
        val -= score[i];
        ASSERT_TRUE(val == m_trackerHuman->getScore());
    }
}

TEST_F(ThreatTrackerTest, GetNumberOfRecognizedThreatTest)
{
    // Define five threats and then, add them to BoardScore, and check that
    // four threat are exist.

    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . o . . . . .|
    //	1 |. . x . . . . . x . . . . . .|
    //	2 |. . x x . . . x . . . . . . .|
    //	3 |. . . . . . x . . . . . . . .|
    //	4 |. . . . . x . . . . . . . . .|
    //	5 |. . . . . . . . . . . x x x x|
    //	6 |. . . . . . . . . . . . . . .|

    const uint32_t numberOfThreatsTHREAT_2_CASE_C = 2;
    const uint32_t numberOfThreatsTHREAT_3_CASE_A = 1;
    const uint32_t numberOfThreatsTHREAT_4_CASE_B = 2;

    // Define 4 threats' locations.
    const IBoard::PositionXY threat1Begin = IBoard::PositionXY(2, 1);  // assume its THREAT_2_CASE_C
    const IBoard::PositionXY threat1End   = IBoard::PositionXY(2, 5);

    const IBoard::PositionXY threat2Begin = IBoard::PositionXY(0, 2);  // assume its THREAT_2_CASE_A
    const IBoard::PositionXY threat2End   = IBoard::PositionXY(6, 2);

    const IBoard::PositionXY threat3Begin = IBoard::PositionXY(0, 1);  // assume its THREAT_3_CASE_A
    const IBoard::PositionXY threat3End   = IBoard::PositionXY(5, 6);

    const IBoard::PositionXY threat4Begin = IBoard::PositionXY(0, 9);  // assume its THREAT_4_CASE_B
    const IBoard::PositionXY threat4End   = IBoard::PositionXY(6, 3);

    const IBoard::PositionXY threat5Begin = IBoard::PositionXY(5, 0);  // assume its THREAT_4_CASE_B
    const IBoard::PositionXY threat5End   = IBoard::PositionXY(5, 4);

    ThreatFinder::ThreatLocation threatContainer;

    threatContainer.m_threatDetails.m_beginningThreat = threat1Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat1End;
    threatContainer.m_trend                           = ThreatFinder::HORIZONTAL;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_C);

    threatContainer.m_threatDetails.m_beginningThreat = threat2Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat2End;
    threatContainer.m_trend                           = ThreatFinder::VERTICAL;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_C);

    threatContainer.m_threatDetails.m_beginningThreat = threat3Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat3End;
    threatContainer.m_trend                           = ThreatFinder::FALLING;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_A);

    threatContainer.m_threatDetails.m_beginningThreat = threat4Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat4End;
    threatContainer.m_trend                           = ThreatFinder::RISING;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_4_CASE_B);

    threatContainer.m_threatDetails.m_beginningThreat = threat5Begin;
    threatContainer.m_threatDetails.m_endThreat       = threat5End;
    threatContainer.m_trend                           = ThreatFinder::RISING;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_4_CASE_B);

    ASSERT_TRUE(numberOfThreatsTHREAT_2_CASE_C ==
               m_trackerHuman->getNumberOf(ThreatFinder::THREAT_2_CASE_C));
    ASSERT_TRUE(numberOfThreatsTHREAT_3_CASE_A ==
               m_trackerHuman->getNumberOf(ThreatFinder::THREAT_3_CASE_A));
    ASSERT_TRUE(numberOfThreatsTHREAT_4_CASE_B ==
               m_trackerHuman->getNumberOf(ThreatFinder::THREAT_4_CASE_B));
}

TEST_F(ThreatTrackerTest, GetExGapsTest1)
{
    //	  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |x . x . . . . . . . . x . . x|
    // 1 |. . . o . x x . . o . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. x x . . . . . . x x . . . .|
    // 4 |. . . . . . . . . . . . . . .|
    // 5 |x x x . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . x x x . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|

    ThreatFinder::ThreatLocation threatContainer;
    ThreatFinder::ThreatUpDetails& threatUpDetails = threatContainer.m_threatDetails;

    // Define 7 threats' locations.
    // 1. assume its THREAT_2_CASE_B
    threatUpDetails.m_extGaps[0] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    threatUpDetails.m_extGaps[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_B);

    threatUpDetails.m_extGaps[0] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    threatUpDetails.m_extGaps[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_B);

    // 2. assume its THREAT_2_CASE_C
    threatUpDetails.m_extGaps[0] = IBoard::PositionXY(1, 8);
    threatUpDetails.m_extGaps[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_C);

    // 3. assume its THREAT_2_CASE_A
    threatUpDetails.m_extGaps[0] = IBoard::PositionXY(3, 4);
    threatUpDetails.m_extGaps[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_A);

    threatUpDetails.m_extGaps[0] = IBoard::PositionXY(3, 12);
    threatUpDetails.m_extGaps[1] = IBoard::PositionXY(3, 7);
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_A);

    // 4. assume its THREAT_3_CASE_B
    threatUpDetails.m_extGaps[0] = IBoard::PositionXY(5, 4);
    threatUpDetails.m_extGaps[1] = ThreatFinder::ThreatLocation::k_XY_OUT_OF_BOARD;
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_B);

    // 5. assume its THREAT_3_CASE_A
    threatUpDetails.m_extGaps[0] = IBoard::PositionXY(7, 12);
    threatUpDetails.m_extGaps[1] = IBoard::PositionXY(7, 6);
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_A);

    //-------------------------------------------------------------------------------------
    std::vector<IBoard::PositionXY> exGaps;
    uint32_t expectedExGapsNumber = 0;

    // 1. Check THREAT_2_CASE_B:
    expectedExGapsNumber = 0;
    m_trackerHuman->getExGaps(exGaps, ThreatFinder::THREAT_2_CASE_B);
    ASSERT_TRUE(exGaps.size() == expectedExGapsNumber);
    exGaps.clear();

    // 2. Check THREAT_2_CASE_C:
    expectedExGapsNumber = 1;
    m_trackerHuman->getExGaps(exGaps, ThreatFinder::THREAT_2_CASE_C);
    ASSERT_TRUE(exGaps.size() == expectedExGapsNumber);
    exGaps.clear();

    // 3. Check THREAT_2_CASE_A:
    expectedExGapsNumber = 3;
    m_trackerHuman->getExGaps(exGaps, ThreatFinder::THREAT_2_CASE_A);
    ASSERT_TRUE(exGaps.size() == expectedExGapsNumber);
    IBoard::PositionXY expectedExGapsList2A[] = {IBoard::PositionXY(3, 4), IBoard::PositionXY(3, 12),
                                                IBoard::PositionXY(3, 7)};
    for(uint32_t i = 0; i < NUMELEM(expectedExGapsList2A); ++i)
    {
        const bool isOnGapsList = isOntheList(expectedExGapsList2A[i], exGaps);
        ASSERT_TRUE(isOnGapsList == true);
    }
    exGaps.clear();

    // 4. Check THREAT_3_CASE_B:
    expectedExGapsNumber = 1;
    m_trackerHuman->getExGaps(exGaps, ThreatFinder::THREAT_3_CASE_B);
    ASSERT_TRUE(exGaps.size() == expectedExGapsNumber);
    exGaps.clear();

    // 5. Check THREAT_3_CASE_A:
    expectedExGapsNumber = 2;
    m_trackerHuman->getExGaps(exGaps, ThreatFinder::THREAT_3_CASE_A);
    ASSERT_TRUE(exGaps.size() == expectedExGapsNumber);
    exGaps.clear();
}

TEST_F(ThreatTrackerTest, GetGapsUniqueTest1)
{
    //	.                      1 1 1 1 1
    //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    //	0 |. . . . . . . . . . . . . . .|
    //	1 |. . . . . . x x . . . . . . .|
    //	2 |. . . . . . . . . . . . . . .|
    //	3 |. . . . . . . . . . . . . . .|
    //	4 |. . . . . . . . . . . . . . .|

    ThreatFinder::ThreatLocation threatContainer;
    ThreatFinder::ThreatUpDetails& threatUpDetails = threatContainer.m_threatDetails;

    const vector<IBoard::PositionXY> expected2A{IBoard::PositionXY(1, 3), IBoard::PositionXY(1, 4),
                                               IBoard::PositionXY(1, 5), IBoard::PositionXY(1, 8),
                                               IBoard::PositionXY(1, 9), IBoard::PositionXY(1, 10)};

    // normal side
    threatUpDetails.m_gaps[0] = IBoard::PositionXY(1, 8);
    threatUpDetails.m_gaps[1] = IBoard::PositionXY(1, 9);
    threatUpDetails.m_gaps[2] = IBoard::PositionXY(1, 10);

    // symmetric side
    threatUpDetails.m_gaps[ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2 + 0] = IBoard::PositionXY(1, 3);
    threatUpDetails.m_gaps[ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2 + 1] = IBoard::PositionXY(1, 4);
    threatUpDetails.m_gaps[ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2 + 2] = IBoard::PositionXY(1, 5);

    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_2_CASE_A);

    // Check gaps.
    std::vector<IBoard::PositionXY> gaps;
    m_trackerHuman->getGapsUnique(gaps, ThreatFinder::THREAT_2_CASE_A);
    const uint32_t expectedSize2A = expected2A.size();
    const uint32_t size2A         = gaps.size();
    ASSERT_TRUE(expectedSize2A == size2A);

    for(vector<IBoard::PositionXY>::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1)
    {
        ASSERT_TRUE(isOntheList(*it1, expected2A));
    }
}

TEST_F(ThreatTrackerTest, GetGapsNonUniqueTest1)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . x . . . . . . . . . . . .|
    // 3 |. . . x . . . . . . . . . . .|
    // 4 |. . . . x . . . . . . . . . .|
    // 5 |. . . . . . x x x . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    ThreatFinder::ThreatLocation threatContainer;
    ThreatFinder::ThreatUpDetails& threatUpDetails = threatContainer.m_threatDetails;

    const vector<IBoard::PositionXY> expected3A{IBoard::PositionXY(0, 0), IBoard::PositionXY(1, 1),
                                               IBoard::PositionXY(5, 5), IBoard::PositionXY(6, 6),
                                               IBoard::PositionXY(5, 4),
                                               // IBoard::PositionXY( 5, 5 ), //doubled
                                               IBoard::PositionXY(5, 9), IBoard::PositionXY(5, 10)};

    // 1. Add first threat.
    // a.normal side
    threatUpDetails.m_gaps[0] = IBoard::PositionXY(5, 5);
    threatUpDetails.m_gaps[1] = IBoard::PositionXY(6, 6);

    // b.symmetric side
    threatUpDetails.m_gaps[ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2 + 0] = IBoard::PositionXY(0, 0);
    threatUpDetails.m_gaps[ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2 + 1] = IBoard::PositionXY(1, 1);
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_A);
    threatUpDetails.clearAll();

    // 2. Add second threat.
    // a.normal side
    threatUpDetails.m_gaps[0] = IBoard::PositionXY(5, 9);
    threatUpDetails.m_gaps[1] = IBoard::PositionXY(5, 10);

    // b.symmetric side
    threatUpDetails.m_gaps[ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2 + 0] = IBoard::PositionXY(5, 4);
    threatUpDetails.m_gaps[ThreatFinder::ThreatUpDetails::k_MAX_EMPTY_SPACES / 2 + 1] = IBoard::PositionXY(5, 5);
    m_trackerHuman->addThreats(threatContainer, ThreatFinder::THREAT_3_CASE_A);
    threatUpDetails.clearAll();

    // 3. Check gaps.
    std::vector<IBoard::PositionXY> gaps;
    m_trackerHuman->getGapsUnique(gaps, ThreatFinder::THREAT_3_CASE_A);
    const uint32_t expectedSize3A = expected3A.size();
    const uint32_t size3A         = gaps.size();
    ASSERT_TRUE(expectedSize3A == size3A);

    for(vector<IBoard::PositionXY>::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1)
    {
        ASSERT_TRUE(isOntheList(*it1, expected3A));
    }
}

TEST_F(ThreatTrackerTest, GetGapsDuplicatedTest1)
{
    //                        1 1 1 1 1
    //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . x . . . . . . . . . . .|
    // 2 |. . . x . . . . . . . . . . .|
    // 3 |. . . . . . . . . . . . . . .|
    // 4 |. . . . . . . . . . . . . . .|
    // 5 |. . x + . x . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . x . .|
    // 8 |. . . . . . . + . . o . . . .|
    // 9 |. . . . . . . . . . x . . . .|
    // 10|. . . . . + . x x + . . . . .|
    // 11|. . . . x . . . . . x . . . .|
    // 12|. . . x . . . . . . . x . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const vector<IBoard::PositionXY> expected2AResult{IBoard::PositionXY(5, 3), IBoard::PositionXY(10, 5),
                                                     IBoard::PositionXY(10, 9), IBoard::PositionXY(8, 7)};

    // 2. Put moves.
    vector<IBoard::PositionXY> xyHuman{IBoard::PositionXY(1, 3),   IBoard::PositionXY(2, 3),  IBoard::PositionXY(5, 2),
                                      IBoard::PositionXY(5, 5),   IBoard::PositionXY(7, 12), IBoard::PositionXY(9, 10),
                                      IBoard::PositionXY(10, 7),  IBoard::PositionXY(10, 8), IBoard::PositionXY(11, 4),
                                      IBoard::PositionXY(11, 10), IBoard::PositionXY(12, 3), IBoard::PositionXY(12, 11)};

    const IBoard::PositionXY cpuMove1 = IBoard::PositionXY(8, 10);

    for(uint32_t i = 0; i < xyHuman.size(); ++i)
    {
        m_board->putMove(xyHuman[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyHuman[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyHuman[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    m_board->putMove(cpuMove1, m_trackerCpu->getPlayer());
    m_trackerHuman->updateScore(cpuMove1, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    m_trackerCpu->updateScore(cpuMove1, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

    std::vector<IBoard::PositionXY> duplicatedGaps;
    //----------------------------------------------
    // 3. Checking.

    // 3a. Checking 2B:
    const uint32_t expectedSize2B = 0;
    m_trackerHuman->getGapsDuplicated(duplicatedGaps, ThreatFinder::THREAT_2_CASE_B);
    const uint32_t size2B = duplicatedGaps.size();
    ASSERT_TRUE(expectedSize2B == size2B);
    duplicatedGaps.clear();

    // 3b. Checking 2A:
    const uint32_t expectedSize2A = expected2AResult.size();
    m_trackerHuman->getGapsDuplicated(duplicatedGaps, ThreatFinder::THREAT_2_CASE_A);
    const uint32_t size2A = duplicatedGaps.size();
    ASSERT_TRUE(expectedSize2A == size2A);
    duplicatedGaps.clear();

    for(vector<IBoard::PositionXY>::const_iterator it1 = duplicatedGaps.begin(); it1 != duplicatedGaps.end(); ++it1)
    {
        ASSERT_TRUE(isOntheList(*it1, expected2AResult));
    }
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber1)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . x . . . . . . . . . . . .|
    // 3 |. . x . . . . . . . . . . . .|
    // 4 |. . x . . . . . . . . . . . .|
    // 5 |. . . x . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 1;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{IBoard::PositionXY(2, 2), IBoard::PositionXY(3, 2), IBoard::PositionXY(4, 2),
                                     IBoard::PositionXY(5, 3)};

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber2)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . x . . . . . . . . . .|
    // 3 |. . . . x . . . . . . . . . .|
    // 4 |. . . . x . . . . . . . . . .|
    // 5 |. . . x . x . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 2;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{
        IBoard::PositionXY(2, 4), IBoard::PositionXY(3, 4), IBoard::PositionXY(4, 4),
        IBoard::PositionXY(5, 3), IBoard::PositionXY(5, 5),
    };

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber3)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . o . . . . . . . . .|
    // 2 |. . . . . o . . . . . . . . .|
    // 3 |. . . . . o . . . . . . . . .|
    // 4 |. . . . x o . . . . . . . . .|
    // 5 |. . . x x o . . . . . . . . .|
    // 6 |. . . . x x . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 3;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove1{
        IBoard::PositionXY(4, 4), IBoard::PositionXY(5, 4), IBoard::PositionXY(6, 4),
        IBoard::PositionXY(5, 3), IBoard::PositionXY(6, 5),
    };

    vector<IBoard::PositionXY> xyMove2{
        IBoard::PositionXY(1, 5), IBoard::PositionXY(2, 5), IBoard::PositionXY(3, 5),
        IBoard::PositionXY(4, 5), IBoard::PositionXY(5, 5),
    };

    for(uint32_t i = 0; i < xyMove1.size(); ++i)
    {
        m_board->putMove(xyMove1[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove1[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove1[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

        m_board->putMove(xyMove2[i], m_trackerCpu->getPlayer());
        m_trackerHuman->updateScore(xyMove2[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove2[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber4)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . x . . . . . . . . . . . .|
    // 3 |. . x . . . x x . . . . . . .|
    // 4 |. . x . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . x . . . . . . . . . . .|
    // 7 |. . . . x . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 0;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{
        IBoard::PositionXY(2, 2), IBoard::PositionXY(3, 2), IBoard::PositionXY(4, 2), IBoard::PositionXY(6, 3),
        IBoard::PositionXY(7, 4), IBoard::PositionXY(3, 6), IBoard::PositionXY(3, 7),
    };

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber5)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . . . x . x . . . . . . .|
    // 4 |. . . . . . x . . . . . . . .|
    // 5 |. . . . . . o . . . . . . . .|
    // 6 |. . . . . . x x . x . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 1;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{
        IBoard::PositionXY(3, 5), IBoard::PositionXY(3, 7), IBoard::PositionXY(4, 6),
        IBoard::PositionXY(6, 6), IBoard::PositionXY(6, 7), IBoard::PositionXY(6, 9),
    };

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    const IBoard::PositionXY additional = IBoard::PositionXY(5, 6);
    m_board->putMove(additional, m_trackerCpu->getPlayer());
    m_trackerHuman->updateScore(additional, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    m_trackerCpu->updateScore(additional, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber6)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . x . . . . . . . . . .|
    // 3 |. . . . x . . . . . . . . . .|
    // 4 |. . . x . x . . . . . . . . .|
    // 5 |. . . . x . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 4;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{
        IBoard::PositionXY(2, 4), IBoard::PositionXY(3, 4), IBoard::PositionXY(5, 4),
        IBoard::PositionXY(4, 3), IBoard::PositionXY(4, 5),
    };

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber7)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . x x x . . x . . . . . . .|
    // 2 |. . . . . x . x . . . . . . .|
    // 3 |. . . . . . . x . . . . . . .|
    // 4 |. . . . . . . . x . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 3;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{
        IBoard::PositionXY(1, 2), IBoard::PositionXY(1, 3), IBoard::PositionXY(1, 4), IBoard::PositionXY(1, 7),
        IBoard::PositionXY(2, 5), IBoard::PositionXY(2, 7), IBoard::PositionXY(3, 7), IBoard::PositionXY(4, 8),
    };

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_3_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber8)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . x . . . . . x . . . . .|
    // 4 |. . . . x . . . x . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 0;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{
        IBoard::PositionXY(3, 3),
        IBoard::PositionXY(4, 4),
        IBoard::PositionXY(3, 9),
        IBoard::PositionXY(4, 8),
    };

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber9)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . x . . . . . . . . .|
    // 3 |. . . . x . . . . . . . . . .|
    // 4 |. . . . x . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|


    // 1. Define expectation.
    const uint32_t expectResult = 1;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{
        IBoard::PositionXY(3, 4),
        IBoard::PositionXY(4, 4),
        IBoard::PositionXY(2, 5),
    };

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber10)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . . . . . . . . . . . . .|
    // 3 |. . . x x . . . . . . . . . .|
    // 4 |. . . x . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 3;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{
        IBoard::PositionXY(3, 3),
        IBoard::PositionXY(3, 4),
        IBoard::PositionXY(4, 3),
    };

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber11)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . x . . . . . . . . . . .|
    // 3 |. . . x . . . . . . . . . . .|
    // 4 |. x . . . x . . . . . . . . .|
    // 5 |. . . x . . . . . . . . . . .|
    // 6 |. . . x . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 4;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{
        IBoard::PositionXY(2, 3), IBoard::PositionXY(3, 3), IBoard::PositionXY(5, 3),
        IBoard::PositionXY(6, 3), IBoard::PositionXY(4, 1), IBoard::PositionXY(4, 5),
    };

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, GetCommonFieldNumber12)
{
    //                       1 1 1 1 1
    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |. . . . . . . . . . . . . . .|
    // 1 |. . . . . . . . . . . . . . .|
    // 2 |. . . x x . . . . . . . . . .|
    // 3 |. . . x x . . . . . . . . . .|
    // 4 |. . . . . . . . . . . . . . .|
    // 5 |. . . . . . . . . . . . . . .|
    // 6 |. . . . . . . . . . . . . . .|
    // 7 |. . . . . . . . . . . . . . .|
    // 8 |. . . . . . . . . . . . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . . . . . . . . . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    // 1. Define expectation.
    const uint32_t expectResult = 8;

    // 2. Put moves.
    vector<IBoard::PositionXY> xyMove{
        IBoard::PositionXY(2, 3),
        IBoard::PositionXY(2, 4),
        IBoard::PositionXY(3, 3),
        IBoard::PositionXY(3, 4),
    };

    for(uint32_t i = 0; i < xyMove.size(); ++i)
    {
        m_board->putMove(xyMove[i], m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(xyMove[i], false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(xyMove[i], true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    ASSERT_TRUE(expectResult ==
               m_trackerHuman->getCommonFieldNumber(ThreatFinder::THREAT_2_CASE_A, ThreatFinder::THREAT_2_CASE_A));
}

TEST_F(ThreatTrackerTest, RealGapsTest1)
{
    // Functional test: Test aims to test real gaps form real threats.

    //                        1 1 1 1 1
    //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
    //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    // 0 |+ . . . . . . . . . . . . . .|
    // 1 |. + . . . . . . . . . . . . .|
    // 2 |. . x . . . . . . . . . . . .|
    // 3 |. . . x . . . . . . o . . . .|
    // 4 |. . . . x . . . . . x . . . .|
    // 5 |. . . . + + x x x + + . . . .|
    // 6 |. . . . . . + . . . x . . . .|
    // 7 |. . . . . . . . . . + . . . .|
    // 8 |. . . . . . . . . . + . . . .|
    // 9 |. . . . . . . . . . . . . . .|
    // 10|. . . . . . . . . . . . . . .|
    // 11|. . . . . . . . . . . . . . .|
    // 12|. . . + x + + + x + . . . . .|
    // 13|. . . . . . . . . . . . . . .|
    // 14|. . . . . . . . . . . . . . .|
    //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|

    ThreatFinder::ThreatLocation threatContainer;
    ThreatFinder::ThreatUpDetails& threatUpDetails = threatContainer.m_threatDetails;

    vector<IBoard::PositionXY> xyMoveHuman{
            IBoard::PositionXY(2, 2),
            IBoard::PositionXY(3, 3),
            IBoard::PositionXY(4, 4),
            IBoard::PositionXY(5, 6),
            IBoard::PositionXY(5, 7),
            IBoard::PositionXY(5, 8),
            IBoard::PositionXY(4, 10),
            IBoard::PositionXY(6, 10),
            IBoard::PositionXY(12, 4),
            IBoard::PositionXY(12, 8),
    };

    vector<IBoard::PositionXY> xyMoveCpu{
            IBoard::PositionXY(3, 10),
    };

    // 1. Put move
    for(const auto& el : xyMoveHuman)
    {
        m_board->putMove(el, m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    for(const auto& el : xyMoveCpu)
    {
        m_board->putMove(el, m_trackerCpu->getPlayer());
        m_trackerHuman->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    // 2. Expectation list of:
    // -2B gaps.
    const vector<IBoard::PositionXY> expected2BGapsALL{IBoard::PositionXY(5, 10), IBoard::PositionXY(7, 10),
                                                      IBoard::PositionXY(8, 10)};
    const vector<IBoard::PositionXY> expected2BExGaps{IBoard::PositionXY(8, 10)};

    // -2AA gaps.
    const vector<IBoard::PositionXY> expected2AAGapsALL{IBoard::PositionXY(12, 3), IBoard::PositionXY(12, 5),
                                                       IBoard::PositionXY(12, 6), IBoard::PositionXY(12, 7),
                                                       IBoard::PositionXY(12, 9)};
    const vector<IBoard::PositionXY> expected2AAExGaps{IBoard::PositionXY(12, 6)};

    // -3A gaps.
    const vector<IBoard::PositionXY> expected3AGapsALL{IBoard::PositionXY(0, 0), IBoard::PositionXY(1, 1),
                                                      IBoard::PositionXY(5, 5), IBoard::PositionXY(6, 6),
                                                      IBoard::PositionXY(5, 4),
                                                      // IBoard::PositionXY( 5, 5 ), doubled
                                                      IBoard::PositionXY(5, 9), IBoard::PositionXY(5, 10)};
    const vector<IBoard::PositionXY> expected3AExGaps{IBoard::PositionXY(0, 0), IBoard::PositionXY(6, 6),
                                                     IBoard::PositionXY(5, 4), IBoard::PositionXY(5, 10)};

    // 3. Checking:
    std::vector<IBoard::PositionXY> gaps;
    //----------------------------------------------
    // a. 2B unique gaps.
    m_trackerHuman->getGapsUnique(gaps, ThreatFinder::THREAT_2_CASE_B);
    const uint32_t expectedSize2BUnique = expected2BGapsALL.size();
    const uint32_t size2BUnique         = gaps.size();
    ASSERT_TRUE(expectedSize2BUnique == size2BUnique);

    for(vector<IBoard::PositionXY>::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1)
    {
        ASSERT_TRUE(isOntheList(*it1, expected2BGapsALL));
    }
    gaps.clear();

    // b. 2B extend gaps.
    m_trackerHuman->getExGaps(gaps, ThreatFinder::THREAT_2_CASE_B);
    const uint32_t expectedSize2BExtended = expected2BExGaps.size();
    const uint32_t size2BExtended         = gaps.size();
    ASSERT_TRUE(expectedSize2BExtended == size2BExtended);

    for(vector<IBoard::PositionXY>::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1)
    {
        ASSERT_TRUE(isOntheList(*it1, expected2BExGaps));
    }
    gaps.clear();
    //----------------------------------------------

    // a. 2AA unique gaps.
    m_trackerHuman->getGapsUnique(gaps, ThreatFinder::THREAT_2_CASE_AA);
    const uint32_t expectedSize2AAUnique = expected2AAGapsALL.size();
    const uint32_t size2AAUnique         = gaps.size();
    ASSERT_TRUE(expectedSize2AAUnique == size2AAUnique);

    for(vector<IBoard::PositionXY>::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1)
    {;
        ASSERT_TRUE(isOntheList(*it1, expected2AAGapsALL));
    }
    gaps.clear();

    // b. 2AA extend gaps.
    m_trackerHuman->getExGaps(gaps, ThreatFinder::THREAT_2_CASE_AA);
    const uint32_t expectedSize2AAExtended = expected2AAExGaps.size();
    const uint32_t size2AAExtended         = gaps.size();
    ASSERT_TRUE(expectedSize2AAExtended == size2AAExtended);

    for(vector<IBoard::PositionXY>::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1)
    {
        ASSERT_TRUE(isOntheList(*it1, expected2AAExGaps));
    }
    gaps.clear();
    //----------------------------------------------

    // a. 3A unique gaps.
    m_trackerHuman->getGapsUnique(gaps, ThreatFinder::THREAT_3_CASE_A);
    const uint32_t expectedSize3AUnique = expected3AGapsALL.size();
    const uint32_t size3AUnique         = gaps.size();
    ASSERT_TRUE(expectedSize3AUnique == size3AUnique);

    for(vector<IBoard::PositionXY>::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1)
    {
        ASSERT_TRUE(isOntheList(*it1, expected3AGapsALL));
    }
    gaps.clear();

    // b. 3A extend gaps.
    m_trackerHuman->getExGaps(gaps, ThreatFinder::THREAT_3_CASE_A);
    const uint32_t expectedSize3AExtended = expected3AExGaps.size();
    const uint32_t size3AExtended         = gaps.size();
    ASSERT_TRUE(expectedSize3AExtended == size3AExtended);

    for(vector<IBoard::PositionXY>::const_iterator it1 = gaps.begin(); it1 != gaps.end(); ++it1)
    {
        ASSERT_TRUE(isOntheList(*it1, expected3AExGaps));
    }
    gaps.clear();
}

static bool isOntheList(const IBoard::PositionXY xy, const vector<IBoard::PositionXY>& vct)
{
    return std::find(vct.begin(), vct.end(), xy) != vct.end();
}
