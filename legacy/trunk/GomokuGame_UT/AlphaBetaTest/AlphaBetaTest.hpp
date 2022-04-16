/*
 * AlphaBeta.hpp
 *
 *  Created on: may 29, 2016
 *      Author: zby
 */

#ifndef TEST_MINMAX_H_
#define TEST_MINMAX_H_

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
//-------------------------------
#include "GomokuBoard.hpp"
#include "AlphaBeta.hpp"
#include "Score.hpp"

class AlphaBetaTest: public CppUnit::TestFixture
{
	// all test time 07.01.2018: [2min40sec]  / PerformanceTest1 - off
	// all test time 04.02.2018: [2min10sec]  / PerformanceTest1 - off
	// all test time 17.02.2018: [4min00sec]  / PerformanceTest1 - off
	// all test time 25.02.2018: [2min05sec]  / PerformanceTest1 - off
	// all test time 04.03.2018: [1min45sec]  / PerformanceTest1 - off
	// all test time 11.03.2018: [1min00sec]  / PerformanceTest1 - off

	CPPUNIT_TEST_SUITE( AlphaBetaTest );

	// Legacy from MIN-MAX: Basic tests.
	CPPUNIT_TEST( GenerateCandTestEmptyBoard );
	CPPUNIT_TEST( GenerateCandTestCorner );
	CPPUNIT_TEST( GenerateCandTesCenter );
	CPPUNIT_TEST( GenerateCandTesConcatenatedMoves );
	CPPUNIT_TEST( GenerateCandTesMixed1 );
	CPPUNIT_TEST( GenerateCandTesMixed2 );
	CPPUNIT_TEST( UpdateCandTest1 );
	CPPUNIT_TEST( UpdateCandTest2 );
	CPPUNIT_TEST( SwitchPlayerTest );
	CPPUNIT_TEST( GameTreeBrowsingBasicDeep2Test );
	CPPUNIT_TEST( GameTreeBrowsingBasicDeep3Test );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest1 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest2 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest4 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest5 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest6 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest7 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest8 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest9 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest10 );
	CPPUNIT_TEST( GenerateCandidateExtendGapsTest1 );
	CPPUNIT_TEST( GenerateCandidateExtendGapsTest2 );
	CPPUNIT_TEST( GenerateCandidateExtendGapsTest3 );
	CPPUNIT_TEST( GenerateCandidateExtendGapsTest4 );
	CPPUNIT_TEST( GenerateCandidateExtendGapsTest5 );
	CPPUNIT_TEST( StalemateTest1 );
	CPPUNIT_TEST( StalemateTest2 );
	//CPPUNIT_TEST( PerformanceTest1 );

	// Legacy from MIN-MAX: Fixing anomalies.
	CPPUNIT_TEST( AnomalyReproduction1 );
	CPPUNIT_TEST( AnomalyReproduction2 );
	CPPUNIT_TEST( AnomalyReproduction3 );
	CPPUNIT_TEST( AnomalyReproduction4 );
	CPPUNIT_TEST( AnomalyReproduction5 );
	CPPUNIT_TEST( AnomalyReproduction6 );
	CPPUNIT_TEST( AnomalyReproduction7 );
	CPPUNIT_TEST( AnomalyReproduction8 );
	CPPUNIT_TEST( AnomalyReproduction9 );
	CPPUNIT_TEST( AnomalyReproduction10 );
	CPPUNIT_TEST( AnomalyReproduction11 );

	// ALPHA-BETA: Real game situation test.
	CPPUNIT_TEST( OpeningBoardTest1 );
	CPPUNIT_TEST( FinishWinnerActionsTest1 );
	CPPUNIT_TEST( IssueTest1 );
	CPPUNIT_TEST( IssueTest3 );
	CPPUNIT_TEST( IssueTest4 );
	CPPUNIT_TEST( IssueTest5 );
	CPPUNIT_TEST( IssueTest6 );
	CPPUNIT_TEST( IssueTest7 );
	CPPUNIT_TEST( IssueTest8 );
	CPPUNIT_TEST( IssueTest9 );
	CPPUNIT_TEST( IssueTest10 );
	CPPUNIT_TEST( IssueTest16 );
	CPPUNIT_TEST( IssueTest17 );
	CPPUNIT_TEST( IssueTest19 );
	CPPUNIT_TEST( IssueTest20 );

	// ALPHA-BETA: After adding Dragon & Lizard shoots.
	CPPUNIT_TEST( IssueTest21 );
	CPPUNIT_TEST( IssueTest22 );
	CPPUNIT_TEST( IssueTest23 );

	CPPUNIT_TEST_SUITE_END();

    public:
        void setUp( )
        {
            m_pGomokuBoard = new GomokuBoard( 15 );
            m_pGomokuBoardStalemate = new GomokuBoard( 5 );

            m_pBoardScoreComputer = new BoardScore( Board::PLAYER_A );
            m_pBoardScoreHuman = new BoardScore( Board::PLAYER_B );
            m_pBoardScoreComputerStalmate = new BoardScore( Board::PLAYER_A );
            m_pBoardScoreHumanStalmate = new BoardScore( Board::PLAYER_B );

            m_pBoardScoreComputer->SetBoard( *m_pGomokuBoard );
            m_pBoardScoreHuman->SetBoard( *m_pGomokuBoard );

            m_pBoardScoreComputerStalmate->SetBoard( *m_pGomokuBoardStalemate );
            m_pBoardScoreHumanStalmate->SetBoard( *m_pGomokuBoardStalemate );
        };

        void tearDown( )
        {
            delete m_pGomokuBoard;
            delete m_pGomokuBoardStalemate;
            delete m_pBoardScoreComputer;
            delete m_pBoardScoreHuman;
            delete m_pBoardScoreComputerStalmate;
			delete m_pBoardScoreHumanStalmate;
        };

        void GenerateCandTestEmptyBoard();
        void GenerateCandTestCorner();
        void GenerateCandTesCenter();
        void GenerateCandTesConcatenatedMoves();
        void GenerateCandTesMixed1();
        void GenerateCandTesMixed2();
        void UpdateCandTest1();
        void UpdateCandTest2();
        void SwitchPlayerTest();
        void GameTreeBrowsingBasicDeep2Test();
        void GameTreeBrowsingBasicDeep3Test();
        void GameTreeBrowsingBestMoveTest1();
        void GameTreeBrowsingBestMoveTest2();
        void GameTreeBrowsingBestMoveTest4();
        void GameTreeBrowsingBestMoveTest5();
        void GameTreeBrowsingBestMoveTest6();
        void GameTreeBrowsingBestMoveTest7();
        void GameTreeBrowsingBestMoveTest8();
        void GameTreeBrowsingBestMoveTest9();
        void GameTreeBrowsingBestMoveTest10();
        void GenerateCandidateExtendGapsTest1();
        void GenerateCandidateExtendGapsTest2();
        void GenerateCandidateExtendGapsTest3();
        void GenerateCandidateExtendGapsTest4();
        void GenerateCandidateExtendGapsTest5();
        void StalemateTest1();
        void StalemateTest2();
        void PerformanceTest1();

        // Fixing anomalies.
        void AnomalyReproduction1();
        void AnomalyReproduction2(); //GameRecord3_L2_fixed
        void AnomalyReproduction3(); //GameRecord7_L4_fixed
        void AnomalyReproduction4(); //GameRecord5_L4 need more depth (at least 5)
        void AnomalyReproduction5(); //GameRecord9_L4 resolved btw other anomaly.
        void AnomalyReproduction6(); //GameRecord10_L4 need more depth (at least 5)
        void AnomalyReproduction7();
        void AnomalyReproduction8();
        void AnomalyReproduction9();
        void AnomalyReproduction10();
        void AnomalyReproduction11();

    	// ALPHA-BETA: Real game situation test.
        void OpeningBoardTest1();
        void FinishWinnerActionsTest1();
        void IssueTest1();
        void IssueTest3();
        void IssueTest4();
        void IssueTest5();
        void IssueTest6();
        void IssueTest7();
        void IssueTest8();
        void IssueTest9();
        void IssueTest10();
        void IssueTest16();
        void IssueTest17();
        void IssueTest19();
        void IssueTest20();
        void IssueTest21();
        void IssueTest22();
        void IssueTest23();

    private:
        // This is helpful method getting best candidates for either CPU or Human the same way as Gomoku Game class does.
        void GetInitCandidatesUT( SearchTreeAlgorithmIf::PriorityQueueScore& rInitCandidates, const uint32_t initDepht ) const;

        // Board for game.
        GomokuBoard* m_pGomokuBoard;
        GomokuBoard* m_pGomokuBoardStalemate;

        BoardScore* m_pBoardScoreComputer;
		BoardScore* m_pBoardScoreHuman;
		BoardScore* m_pBoardScoreComputerStalmate;
		BoardScore* m_pBoardScoreHumanStalmate;
};

#endif /* TEST_MINMAX_H_ */
