/*
 * MinMax.hpp
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
#include "MinMax.hpp"
#include "Score.hpp"

class MinMaxTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( MinMaxTest );

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
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest3 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest4 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest5 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest6 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest7 );
	CPPUNIT_TEST( GameTreeBrowsingBestMoveTest8 );
	CPPUNIT_TEST( GenerateCandidateExtendGapsTest1 );
	CPPUNIT_TEST( GenerateCandidateExtendGapsTest2 );
	CPPUNIT_TEST( GenerateCandidateExtendGapsTest3 );
	CPPUNIT_TEST( GenerateCandidateExtendGapsTest4 );
	CPPUNIT_TEST( GenerateCandidateExtendGapsTest5 );
	CPPUNIT_TEST( StalemateTest1 );
	CPPUNIT_TEST( StalemateTest2 );
	CPPUNIT_TEST( PerformanceTest1 );

    // Fixing anomalies.
	CPPUNIT_TEST( AnomalyReproduction1 );
	CPPUNIT_TEST( AnomalyReproduction2 );
	CPPUNIT_TEST( AnomalyReproduction3 );
	CPPUNIT_TEST( AnomalyReproduction4 );
	CPPUNIT_TEST( AnomalyReproduction5 );
	CPPUNIT_TEST( AnomalyReproduction6 );


	CPPUNIT_TEST_SUITE_END();

    public:
        void setUp( )
        {
            m_pGomokuBoard = new GomokuBoard( 15 );
            m_pGomokuBoardStalemate = new GomokuBoard( 5 );
        };

        void tearDown( )
        {
            delete m_pGomokuBoard;
            delete m_pGomokuBoardStalemate;
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
        void GameTreeBrowsingBestMoveTest3();
        void GameTreeBrowsingBestMoveTest4();
        void GameTreeBrowsingBestMoveTest5();
        void GameTreeBrowsingBestMoveTest6();
        void GameTreeBrowsingBestMoveTest7();
        void GameTreeBrowsingBestMoveTest8();
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


    private:
        void PutMoves( vector<Board::PositionXY>& list, const Board::Player player );

        // Board for game.
        GomokuBoard* m_pGomokuBoard;
        GomokuBoard* m_pGomokuBoardStalemate;

};

#endif /* TEST_MINMAX_H_ */
