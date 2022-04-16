/*
 * ScoreTest.hpp
 *
 *  Created on: Apr 19, 2016
 *      Author: zby
 */

#ifndef TEST_SCORE_H_
#define TEST_SCORE_H_

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
#include "Score.hpp"
#include "BoardScore.hpp"
#include "GomokuBoard.hpp"

class ScoreTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( ScoreTest );

	CPPUNIT_TEST( UpdateScoreTest1 );
	CPPUNIT_TEST( UpdateScoreTest2 );
	CPPUNIT_TEST( UpdateScoreTest3 );
	CPPUNIT_TEST( UpdateScoreTest4 );
	CPPUNIT_TEST( UpdateScoreTest5 );
	CPPUNIT_TEST( UpdateScoreTest6 );
	CPPUNIT_TEST( UpdateScoreTest7 );
	CPPUNIT_TEST( UpdateScoreTest8 );
	CPPUNIT_TEST( UpdateScoreTest9 );
	CPPUNIT_TEST( UpdateScoreTest10 );
	CPPUNIT_TEST( UpdateScoreTest11 );
	CPPUNIT_TEST( UpdateScoreTest12 );
	CPPUNIT_TEST( UpdateScoreTest13 );

	CPPUNIT_TEST_SUITE_END();

    public:
        void setUp( )
        {
            m_pGomokuBoard = new GomokuBoard( 15 );
            m_pBoardScoreHuman = new BoardScore( Board::PLAYER_A );
            m_pBoardScoreComputer = new BoardScore( Board::PLAYER_B );

            m_pBoardScoreHuman->SetBoard(*m_pGomokuBoard);
            m_pBoardScoreComputer->SetBoard(*m_pGomokuBoard);
        };

        void tearDown( )
        {
            delete m_pGomokuBoard;
            delete m_pBoardScoreHuman;
            delete m_pBoardScoreComputer;
        };

        void UpdateScoreTest1();
        void UpdateScoreTest2();
        void UpdateScoreTest3();
        void UpdateScoreTest4();
        void UpdateScoreTest5();
        void UpdateScoreTest6();
        void UpdateScoreTest7();
        void UpdateScoreTest8();
        void UpdateScoreTest9();
        void UpdateScoreTest10();
        void UpdateScoreTest11();
        void UpdateScoreTest12();
        void UpdateScoreTest13();

    private:
        // Board for game.
        GomokuBoard* m_pGomokuBoard;
        BoardScore* m_pBoardScoreHuman;
        BoardScore* m_pBoardScoreComputer;

        void GetVacantFields(vector<Board::PositionXY>& list);
};

#endif /* TEST_SCORE_H_ */
