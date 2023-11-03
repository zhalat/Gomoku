//#include "Score.hpp"
//#include "BoardScore.hpp"
//#include "GomokuBoard.hpp"
////----------------------------------------------------------
//#include "CppUTest/TestHarness.h"
//#include "CppUTest/SimpleString.h"
//#include "CppUTest/PlatformSpecificFunctions.h"
//#include "CppUTest/TestMemoryAllocator.h"
//#include "CppUTest/MemoryLeakDetector.h"
//
//TEST_GROUP(ScoreTest)
//{
//    void setup()
//    {
//        m_pGomokuBoard        = new GomokuBoard(15);
//        m_pBoardScoreHuman    = new BoardScore(Board::PLAYER_A);
//        m_pBoardScoreComputer = new BoardScore(Board::PLAYER_B);
//
//        m_pBoardScoreHuman->SetBoard(*m_pGomokuBoard);
//        m_pBoardScoreComputer->SetBoard(*m_pGomokuBoard);
//    };
//
//    void teardown()
//    {
//        delete m_pGomokuBoard;
//        delete m_pBoardScoreHuman;
//        delete m_pBoardScoreComputer;
//    };
//
//    // Board for game.
//    GomokuBoard* m_pGomokuBoard;
//    BoardScore* m_pBoardScoreHuman;
//    BoardScore* m_pBoardScoreComputer;
//};
//
//TEST(ScoreTest, UpdateScoreTest1)
//{
//    // Empty board has zero score.
//    CHECK(0 == m_pBoardScoreHuman->GetScore());     // player A
//    CHECK(0 == m_pBoardScoreComputer->GetScore());  // player B
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    //--------- Following there is a scenario:-------------
//    // a. Human (Player A) creates threat Threat2CaseA.
//    // b. Computer (Player B) creates threat Threat2CaseA, but don't interact with human' threat.
//    // c. Human reinforce previous attack. Threat2CaseA->Threat3CaseA.
//    // d. Computer reinforce previous attack. Threat2CaseA->Threat3CaseA.
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // a. Human (Player A) creates threat Threat2CaseA.
//    humanMoves = {Board::PositionXY(5, 6), Board::PositionXY(6, 7)};
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[0]);
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[1]);
//
//    CHECK(Score::THREAT_2_CASE_A_SCORE == m_pBoardScoreHuman->GetScore());
//    CHECK(0 == m_pBoardScoreComputer->GetScore());
//
//    // b. Computer (Player B) creates threat Threat2CaseA, but don't interact with human' threat.
//    computerMoves = {Board::PositionXY(3, 4), Board::PositionXY(3, 5)};
//
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[0]);
//    m_pGomokuBoard->PutMove(computerMoves[1], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[1]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[1]);
//
//    CHECK(Score::THREAT_2_CASE_A_SCORE == m_pBoardScoreHuman->GetScore());
//    CHECK(Score::THREAT_2_CASE_A_SCORE == m_pBoardScoreComputer->GetScore());
//
//    // c. Human reinforce previous attack. Threat2CaseA->Threat3CaseA.
//    humanMoves.clear();
//    humanMoves = {Board::PositionXY(7, 8)};
//
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[0]);
//
//    CHECK(Score::THREAT_3_CASE_A_SCORE == m_pBoardScoreHuman->GetScore());
//    CHECK(Score::THREAT_2_CASE_A_SCORE == m_pBoardScoreComputer->GetScore());
//
//    // d. Computer reinforce previous attack. Threat2CaseA->Threat3CaseA.
//
//    computerMoves.clear();
//    computerMoves = {Board::PositionXY(3, 3)};
//
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[0]);
//
//    CHECK(Score::THREAT_3_CASE_A_SCORE == m_pBoardScoreHuman->GetScore());
//    CHECK(Score::THREAT_3_CASE_A_SCORE == m_pBoardScoreComputer->GetScore());
//}
//
//TEST(ScoreTest, UpdateScoreTest2)
//{
//    //--------- Following there is a scenario:-------------
//    // a. Human (Player A) creates threat Threat2CaseC.
//    // b. Computer (Player B) blocks attack. Neutral it to zero.
//    // c. Human creates triple Threat2CaseA attack.
//    // d. Computer (Player B) blocks one of third human attack.
//    // c. Human add move which case two deadly threats at once.
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    // a. Human (Player A) creates threat Threat2CaseC.
//    humanMoves = {Board::PositionXY(6, 7), Board::PositionXY(8, 9)};
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[0]);
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[1]);
//
//    CHECK(Score::THREAT_2_CASE_A_SCORE == m_pBoardScoreHuman->GetScore());
//    CHECK(0 == m_pBoardScoreComputer->GetScore());
//
//    // b. Computer (Player B) blocks attack. Neutral it to zero.
//    computerMoves = {Board::PositionXY(7, 8)};
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[0]);
//
//    CHECK(0 == m_pBoardScoreHuman->GetScore());
//    CHECK(0 == m_pBoardScoreComputer->GetScore());
//
//    // c. Human creates triple Threat2CaseA attack.
//    humanMoves = {Board::PositionXY(5, 8), Board::PositionXY(3, 8), Board::PositionXY(2, 7)};
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[0]);
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[1]);
//    m_pGomokuBoard->PutMove(humanMoves[2], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[2]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[2]);
//
//    CHECK((3 * Score::THREAT_2_CASE_A_SCORE + 1 * Score::THREAT_2_CASE_AA_SCORE) == m_pBoardScoreHuman->GetScore());
//    CHECK(0 == m_pBoardScoreComputer->GetScore());
//
//    // d. Computer (Player B) blocks one of third human attack.
//    computerMoves = {Board::PositionXY(4, 8)};
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[0]);
//
//    CHECK((2 * Score::THREAT_2_CASE_A_SCORE + 1 * Score::THREAT_2_CASE_AA_SCORE) == m_pBoardScoreHuman->GetScore());
//    CHECK(0 == m_pBoardScoreComputer->GetScore());
//
//    // c. Human add move which case two deadly threats at once.
//    humanMoves = {Board::PositionXY(4, 9)};
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[0]);
//
//    CHECK((2 * Score::THREAT_3_CASE_A_SCORE + 2 * Score::THREAT_2_CASE_AA_SCORE) == m_pBoardScoreHuman->GetScore());
//    CHECK(0 == m_pBoardScoreComputer->GetScore());
//}
//
//TEST(ScoreTest, UpdateScoreTest3)
//{
//    //--------- Following there is a scenario:-------------
//    // a. Human (Player A) creates threat Threat2CaseA.
//    // b. Computer (Player B) blocks attack in that way that thread is reduced
//    //   to Threat2CaseC.
//    // .                       1 1 1 1 1
//    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. x x . . . . . . . . . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    // a. Human (Player A) creates threat Threat2CaseA.
//    humanMoves = {Board::PositionXY(1, 1), Board::PositionXY(1, 2)};
//
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[0]);
//
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[1]);
//    humanMoves.clear();
//
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//
//    computerMoves = {Board::PositionXY(1, 5)};
//
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    computerMoves.clear();
//
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//}
//
//TEST(ScoreTest, UpdateScoreTest4)
//{
//    //--------- Following there is a scenario:-------------
//    // a. Human (Player A) creates threat Threat2CaseA.
//    // b. Computer (Player B) blocks attack in that way that thread is reduced
//    //   to Threat2CaseC.
//    // .                       1 1 1 1 1
//    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. o . . . . . . . . . . . . .|
//    //  1 |. . . . . . . . . . . . . . .|
//    //  2 |. . . x . . . . . . . . . . .|
//    //  3 |. . . . x . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//    //  6 |. . . . . . . . . . . . . . .|
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    // Precondition:
//    computerMoves = {Board::PositionXY(0, 1)};
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    computerMoves.clear();
//
//    // a. Human (Player A) creates threat Threat2CaseA.
//    humanMoves = {Board::PositionXY(2, 3), Board::PositionXY(3, 4)};
//
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[0]);
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[1]);
//    humanMoves.clear();
//
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//
//    computerMoves = {Board::PositionXY(6, 7)};
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//
//    // .                       1 1 1 1 1
//    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. o . . . . . . . . . . . . .|
//    //  1 |. . . . . . . . . . . . . . .|
//    //  2 |. . . x . . . . . . . . . . .|
//    //  3 |. . . . x . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//    //  6 |. . . . . . . o . . . . . . .|
//
//    computerMoves.clear();
//
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//}
//
//TEST(ScoreTest, UpdateScoreTest5)
//{
//    // UpdateScore shall recognize ALL threads which are on the same level.
//    // The level means: Threat4 or Threat3 or Threat2 threats.
//
//    //--------- Following there is a scenario:-------------
//    // a. Human (Player A) creates threat: Threat2CaseA
//    // b. Human creates the second threat: Threat2CaseC
//    // c. Both of these threats have one (empty) field common. Let's call it '*'.
//    // d. Human put its move onto '*' field. That causes promotion of the threats into
//    //   Threat3CaseA, Threat3CaseC.
//    // e. The Cpu's (Player B) movies are only to force certain threats.
//    //
//    // The state of board:
//    // .                       1 1 1 1 1
//    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |o . . . . . . . o . . . . . .|
//    //  1 |. . . . . . . . . . . . . . .|
//    //  2 |. . x . . . x . . . . . . . .|
//    //  3 |. . . x . x . . . . . . . . .|
//    //  4 |. . . . * . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//    //  6 |. . o . . . . . . . . . . . .|
//    //  7 |. . . . . . . o . . . . . . .|
//    //  8 |. . . . . . . . . . . . . . .|
//    //  9 |. . . . . . . . . . . . . . .|
//    //  10|. . . . . . . . . . . . . . .|
//    //  11|. . . . . . . . . . . . . . .|
//    //  12|. . . . . . . . . . . . . . .|
//    //  13|. . . . . . . . . . . . . . .|
//    //  14|. . . . . . . . . . . . . . .|
//    //    |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    // a. Human (Player A) creates threat Threat2CaseA.
//    humanMoves = {Board::PositionXY(2, 2), Board::PositionXY(3, 3)};
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[0]);
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[1]);
//    humanMoves.clear();
//
//    // b. Human (Player A) creates threat Threat2CaseC.
//    humanMoves = {Board::PositionXY(2, 6), Board::PositionXY(3, 5)};
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[0]);
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[1]);
//    humanMoves.clear();
//
//    // c. The Cpu's (Player B) movies are only to force certain threats.
//    computerMoves = {Board::PositionXY(0, 0), Board::PositionXY(0, 8), Board::PositionXY(6, 2),
//                     Board::PositionXY(7, 7)};
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    m_pGomokuBoard->PutMove(computerMoves[1], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[1]);
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[1]);
//    m_pGomokuBoard->PutMove(computerMoves[2], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[2]);
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[2]);
//    m_pGomokuBoard->PutMove(computerMoves[3], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[3]);
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[3]);
//    computerMoves.clear();
//
//    // Check there is no Threat3 recognized yet.
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//
//    // Put '*' move:
//    humanMoves = {Board::PositionXY(4, 4)};
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[0]);
//    humanMoves.clear();
//
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//}
//
//TEST(ScoreTest, UpdateScoreTest6)
//{
//    // a. create threat THREAT_4_CASE_A
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. x x x x . . . . . . . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    // b. move that doesn't shout threat
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. x x x x . o . . . . . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    // b. move that doesn't shout threat completely
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. x x x x o o . . . . . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    humanMoves = {Board::PositionXY(1, 1), Board::PositionXY(1, 2), Board::PositionXY(1, 3), Board::PositionXY(1, 4)};
//
//    // Put moves sequentially, and update score.
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    m_pGomokuBoard->PutMove(humanMoves[2], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[2]);
//    m_pGomokuBoard->PutMove(humanMoves[3], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[3]);
//    humanMoves.clear();
//
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//
//    computerMoves = {Board::PositionXY(1, 6)};
//
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    computerMoves.clear();
//
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//
//    computerMoves = {Board::PositionXY(1, 5)};
//
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    computerMoves.clear();
//
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//}
//
//TEST(ScoreTest, UpdateScoreTest7)
//{
//    // a. create threat THREAT_4_CASE_C
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. . . . x x . x x . . . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    // b. move that doesn't shout threat completely. Two new THREAT_2_CASE_B threats shall be viable.
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. . . . x x o x x . . . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    humanMoves = {Board::PositionXY(1, 4), Board::PositionXY(1, 5), Board::PositionXY(1, 7), Board::PositionXY(1, 8)};
//
//    // Put moves sequentially, and update score.
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    m_pGomokuBoard->PutMove(humanMoves[2], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[2]);
//    m_pGomokuBoard->PutMove(humanMoves[3], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[3]);
//    humanMoves.clear();
//
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA));
//
//    // Computer puts its move which split existing into two weaker threats.
//    computerMoves = {Board::PositionXY(1, 6)};
//
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    computerMoves.clear();
//
//    // THREAT_4_CASE_A - has been broken into two THREAT_2_CASE_B.
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(2 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//}
//
//TEST(ScoreTest, UpdateScoreTest8)
//{
//    // a. create threats: 2x THREAT_4_CASE_C,
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . x . . . . . . . .|
//    //  1 |. . . . . . x . . . . . . . .|
//    //  2 |. . . . x x . x x . . . . . .|
//    //  3 |. . . . . . x . . . . . . . .|
//    //  4 |. . . . . . x . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    // b. move that doesn't shout threat completely. Three new THREAT_2_CASE_B threats shall be viable.
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . x . . . . . . . .|
//    //  1 |. . . . . . x . . . . . . . .|
//    //  2 |. . . . x x o x x . . . . . .|
//    //  3 |. . . . . . x . . . . . . . .|
//    //  4 |. . . . . . x . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    humanMoves = {Board::PositionXY(2, 4), Board::PositionXY(2, 5), Board::PositionXY(2, 7), Board::PositionXY(2, 8),
//                  Board::PositionXY(0, 6), Board::PositionXY(1, 6), Board::PositionXY(3, 6), Board::PositionXY(4, 6)};
//
//    // Put moves sequentially, and update score.
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    m_pGomokuBoard->PutMove(humanMoves[2], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[2]);
//    m_pGomokuBoard->PutMove(humanMoves[3], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[3]);
//    m_pGomokuBoard->PutMove(humanMoves[4], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[4]);
//    m_pGomokuBoard->PutMove(humanMoves[5], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[5]);
//    m_pGomokuBoard->PutMove(humanMoves[6], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[6]);
//    m_pGomokuBoard->PutMove(humanMoves[7], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[7]);
//    humanMoves.clear();
//
//    // These moves are just to shout down unnecessary threats.
//    computerMoves = {Board::PositionXY(3, 3), Board::PositionXY(3, 9)};
//
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    m_pGomokuBoard->PutMove(computerMoves[1], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[1]);
//
//    // Computer puts its move which split existing into two weaker threats.
//    computerMoves = {Board::PositionXY(2, 6)};
//
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    computerMoves.clear();
//
//    // Three of THREAT_2_CASE_B shall be visable.
//    CHECK(3 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//}
//
//TEST(ScoreTest, UpdateScoreTest9)
//{
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. . . . . . . . . . . . . . .|
//    //  2 |. . . . x x x . x . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    humanMoves = {
//        Board::PositionXY(2, 4),
//        Board::PositionXY(2, 5),
//        Board::PositionXY(2, 6),
//        Board::PositionXY(2, 8),
//    };
//
//    m_pGomokuBoard->PutMove(humanMoves[0], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[0]);
//    m_pGomokuBoard->PutMove(humanMoves[1], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[1]);
//    m_pGomokuBoard->PutMove(humanMoves[2], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[2]);
//    m_pGomokuBoard->PutMove(humanMoves[3], m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[3]);
//
//    // shout down the threat
//    computerMoves = {Board::PositionXY(2, 3), Board::PositionXY(2, 7)};
//
//    m_pGomokuBoard->PutMove(computerMoves[0], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[0]);
//    m_pGomokuBoard->PutMove(computerMoves[1], m_pBoardScoreComputer->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[1]);
//
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. . . . . . . . . . . . . . .|
//    //  2 |. . . o x x x o x . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    CHECK(0 == m_pBoardScoreHuman->GetScore());
//    CHECK(0 == m_pBoardScoreComputer->GetScore());
//}
//
//TEST(ScoreTest, UpdateScoreTest10)
//{
//    // 1. CPU created threat:
//
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . . . . .|
//    // 1 |. . . . . . . . . . . . . . .|
//    // 2 |. . . . . . x . . . . . . . .|
//    // 3 |. . . . . . . . . . . . . . .|
//    // 4 |. . . . . . x . . . . . . . .|
//    // 5 |. . . . . . . . . . . . . . .|
//    // 6 |. . . . . . . . . . . . . . .|
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    computerMoves = {Board::PositionXY(2, 6), Board::PositionXY(4, 6)};
//
//    for(uint32_t i = 0; i < computerMoves.size(); ++i)
//    {
//        m_pGomokuBoard->PutMove(computerMoves[i], m_pBoardScoreComputer->GetPlayer());
//        rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[i]);
//        rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[i]);
//    }
//
//    // 2. Verify the threat.
//
//    // THREAT_2_CASE_A cpu threats
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(1 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//
//    // No human threats.
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//
//    // 3. User blocks cpu attack.
//
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . . . . .|
//    // 1 |. . . . . . . . . . . . . . .|
//    // 2 |. . . . . . x . . . . . . . .|
//    // 3 |. . . . . . . . . . . . . . .|
//    // 4 |. . . . . . x . . . . . . . .|
//    // 5 |. . . . . . o . . . . . . . .|
//    // 6 |. . . . . . . . . . . . . . .|
//
//    const Board::PositionXY humanBlocker = Board::PositionXY(5, 6);
//    m_pGomokuBoard->PutMove(humanBlocker, m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreComputer, humanBlocker);
//    rScore.UpdateScore(*m_pBoardScoreHuman, humanBlocker);
//
//    // 4. Verify the threat.
//
//    // THREAT_2_CASE_B cpu threats
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//    CHECK(1 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//
//    // No human threats.
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//}
//
//TEST(ScoreTest, UpdateScoreTest11)
//{
//    // 1. CPU created threat:
//
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . . . . .|
//    // 1 |. . . . . . . . . . . . . . .|
//    // 2 |. . . . . . o . . . . . . . .|
//    // 3 |. . . . . . . . . . . . . . .|
//    // 4 |. . . . . . o . . . . . . . .|
//    // 5 |. . . . . . . . . . . . . . .|
//    // 6 |. . . . . . . . . . . . . . .|
//
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    computerMoves = {Board::PositionXY(2, 6), Board::PositionXY(4, 6)};
//
//    for(uint32_t i = 0; i < computerMoves.size(); ++i)
//    {
//        m_pGomokuBoard->PutMove(computerMoves[i], m_pBoardScoreComputer->GetPlayer());
//        rScore.UpdateScore(*m_pBoardScoreComputer, computerMoves[i]);
//        rScore.UpdateScore(*m_pBoardScoreHuman, computerMoves[i]);
//    }
//
//    // 2. Verify the threat.
//    // THREAT_2_CASE_A cpu threats
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(1 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//
//    // THREAT_2_CASE_A human threats
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//
//    // 3. HUMAN created threat:
//
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . . . . .|
//    // 1 |. . . . . . . . . . . . . . .|
//    // 2 |. . . . . . o . . x . . . . .|
//    // 3 |. . . . . . . . . . . . . . .|
//    // 4 |. . . . . . o . . x . . . . .|
//    // 5 |. . . . . . . . . . . . . . .|
//    // 6 |. . . . . . . . . . . . . . .|
//
//    humanMoves = {Board::PositionXY(2, 9), Board::PositionXY(4, 9)};
//
//    for(uint32_t i = 0; i < humanMoves.size(); ++i)
//    {
//        m_pGomokuBoard->PutMove(humanMoves[i], m_pBoardScoreHuman->GetPlayer());
//        rScore.UpdateScore(*m_pBoardScoreComputer, humanMoves[i]);
//        rScore.UpdateScore(*m_pBoardScoreHuman, humanMoves[i]);
//    }
//
//    // 4. Verify the threat.
//    // THREAT_2_CASE_A cpu threats
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(1 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//    CHECK(0 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//
//    // THREAT_2_CASE_A human threats
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//}
//
//TEST(ScoreTest, UpdateScoreTest12)
//{
//    // 1. CPU created threat:
//
//    //                       1 1 1 1 1
//    //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    // 0 |. . . . . . . . . . . . . . .|
//    // 1 |. . . . . . . . . . . . . . .|
//    // 2 |. . . . . . . . . . . . . . .|
//    // 3 |. . . . . . . . . . . . . . .|
//    // 4 |. . . . . . . . . . . . . . .|
//    // 5 |. . . . . . . . . . o . . . .|
//    // 6 |. . . . . . . . . . . . . . .|
//    // 7 |. . . . . . . . x . . . . . .|
//    // 8 |. . . . . . . x . . . . . . .|
//    // 9 |. . . . . . . . . . . . . . .|
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    Board::PositionXY tmpMove;
//
//    tmpMove = Board::PositionXY(8, 7);
//    m_pGomokuBoard->PutMove(tmpMove, Board::PLAYER_B);
//    rScore.UpdateScore(*m_pBoardScoreComputer, tmpMove);
//    rScore.UpdateScore(*m_pBoardScoreHuman, tmpMove);
//
//    tmpMove = Board::PositionXY(5, 10);
//    m_pGomokuBoard->PutMove(tmpMove, Board::PLAYER_A);
//    rScore.UpdateScore(*m_pBoardScoreComputer, tmpMove);
//    rScore.UpdateScore(*m_pBoardScoreHuman, tmpMove);
//
//    tmpMove = Board::PositionXY(7, 8);
//    m_pGomokuBoard->PutMove(tmpMove, Board::PLAYER_B);
//    rScore.UpdateScore(*m_pBoardScoreComputer, tmpMove);
//    rScore.UpdateScore(*m_pBoardScoreHuman, tmpMove);
//
//    CHECK(1 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//
//    tmpMove = Board::PositionXY(6, 9);
//    m_pGomokuBoard->PutMove(tmpMove, Board::PLAYER_B);
//    rScore.UpdateScore(*m_pBoardScoreComputer, tmpMove);
//    rScore.UpdateScore(*m_pBoardScoreHuman, tmpMove);
//
//    CHECK(1 == m_pBoardScoreComputer->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//}
//
//TEST(ScoreTest, UpdateScoreTest13)
//{
//    // a. create threat THREAT_3_CASE_AA
//    //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. . x . x . x . . . . . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    // b. add next section to create 3A+2A
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. . x . x . x . x . . . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    // c. add next section to create 3A+3A
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. . x . x . x . x . x . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    // d. put move to create 2x4AA
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. . x . x x x . x . x . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    // d. put move to create 4AA + 3A
//    //     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//    //  0 |. . . . . . . . . . . . . . .|
//    //  1 |. . x . x x x . x x x . . . .|
//    //  2 |. . . . . . . . . . . . . . .|
//    //  3 |. . . . . . . . . . . . . . .|
//    //  4 |. . . . . . . . . . . . . . .|
//    //  5 |. . . . . . . . . . . . . . .|
//
//    // 0. Precondition.
//    vector<Board::PositionXY> humanMoves    = {};
//    vector<Board::PositionXY> computerMoves = {};
//
//    // Get Score class instance.
//    Score& rScore = *Score::GetInstance();
//
//    // 1. Put moves to create threat THREAT_3_CASE_AA:: //  1 |. . x . x . x . . . . . . . .|
//    m_pGomokuBoard->PutMove(Board::PositionXY(1, 2), m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, Board::PositionXY(1, 2));
//    m_pGomokuBoard->PutMove(Board::PositionXY(1, 4), m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, Board::PositionXY(1, 4));
//    m_pGomokuBoard->PutMove(Board::PositionXY(1, 6), m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, Board::PositionXY(1, 6));
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_AA));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//
//    // 2. Put next section:: //  1 |. . x . x . x . x . . . . . .|
//    m_pGomokuBoard->PutMove(Board::PositionXY(1, 8), m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, Board::PositionXY(1, 8));
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_AA));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(1 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//
//    // 3. Put next section:: //  1 |. . x . x . x . x . x . . . .|
//    m_pGomokuBoard->PutMove(Board::PositionXY(1, 10), m_pBoardScoreHuman->GetPlayer());
//    rScore.UpdateScore(*m_pBoardScoreHuman, Board::PositionXY(1, 10));
//    CHECK(2 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_AA));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_AA));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_AA));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_WINNER));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_4_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_C));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_3_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_A));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_B));
//    CHECK(0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat(ThreatFinder::THREAT_2_CASE_C));
//
//    // 4. Put next section:: //  1 |. . x . x x x . x . x . . . .|
//
//    // This test fails because its crates 4AA + 2A instead of 2x4AA.
//    // Such cases should be rather handled as a special cases and recognized entirely rather by common algor.
//
//    //	m_pGomokuBoard->PutMove( Board::PositionXY( 1, 5 ), m_pBoardScoreHuman->GetPlayer() );
//    //	rScore.UpdateScore( *m_pBoardScoreHuman, Board::PositionXY( 1, 5 ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_3_CASE_AA ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_2_CASE_AA ) );
//    //	CHECK( 2 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_4_CASE_AA ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_WINNER ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_4_CASE_A ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_4_CASE_C ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_4_CASE_B ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_3_CASE_C ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_3_CASE_A ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_3_CASE_B ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_2_CASE_A ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_2_CASE_B ) );
//    //	CHECK( 0 == m_pBoardScoreHuman->GetNumberOfRecognizedThreat( ThreatFinder::THREAT_2_CASE_C ) );
//}
