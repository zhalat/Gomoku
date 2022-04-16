/*
 * BoardScoreTest.hpp
 *
 *  Created on: Apr 19, 2016
 *      Author: zby
 */

#ifndef TEST_BOARDSCORE_H_
#define TEST_BOARDSCORE_H_

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
#include "BoardScore.hpp"

class BoardScoreTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( BoardScoreTest );

	CPPUNIT_TEST( AddThreatsTest1 );
	CPPUNIT_TEST( RemoveThreatsRemoveAllTest1 );
	CPPUNIT_TEST( RemoveThreatsRemoveAllTest2 );
	CPPUNIT_TEST( RemoveThreatsRemoveAllTest3 );
	CPPUNIT_TEST( RemoveThreatsPartiallyRemoveTest );
	CPPUNIT_TEST( GetNumberOfRecognizedThreatTest );
	CPPUNIT_TEST( GetExGapsTest1 );
	CPPUNIT_TEST( GetGapsUniqueTest1 );
	CPPUNIT_TEST( GetGapsNonUniqueTest1 );
	CPPUNIT_TEST( GetGapsDuplicatedTest1 );
	CPPUNIT_TEST( GetCommonFieldNumber1 );
	CPPUNIT_TEST( GetCommonFieldNumber2 );
	CPPUNIT_TEST( GetCommonFieldNumber3 );
	CPPUNIT_TEST( GetCommonFieldNumber4 );
	CPPUNIT_TEST( GetCommonFieldNumber5 );
	CPPUNIT_TEST( GetCommonFieldNumber6 );
	CPPUNIT_TEST( GetCommonFieldNumber7 );
	CPPUNIT_TEST( GetCommonFieldNumber8 );
	CPPUNIT_TEST( GetCommonFieldNumber9 );
	CPPUNIT_TEST( GetCommonFieldNumber10 );
	CPPUNIT_TEST( GetCommonFieldNumber11 );
	CPPUNIT_TEST( GetCommonFieldNumber12 );
	CPPUNIT_TEST( RealGapsTest1 );
	CPPUNIT_TEST( RealGapsTest2 );

	CPPUNIT_TEST_SUITE_END();

    public:
        void setUp( )
        {
            m_pGomokuBoard = new GomokuBoard( 15 );
            m_pBoardScoreHuman = new BoardScore( Board::PLAYER_A );
            m_pBoardScoreCpu = new BoardScore( Board::PLAYER_B );
            m_pBoardScoreHuman->SetBoard( *m_pGomokuBoard );
            m_pBoardScoreCpu->SetBoard( *m_pGomokuBoard );
        };

        void tearDown( )
        {
            delete m_pGomokuBoard;
            delete m_pBoardScoreHuman;
            delete m_pBoardScoreCpu;
        };

        void AddThreatsTest1();
        void RemoveThreatsRemoveAllTest1();
        void RemoveThreatsRemoveAllTest2();
        void RemoveThreatsRemoveAllTest3();
        void RemoveThreatsPartiallyRemoveTest();
        void GetNumberOfRecognizedThreatTest();
        void GetExGapsTest1();
        void GetExGapsTest2();
        void GetGapsUniqueTest1();
        void GetGapsNonUniqueTest1();
        void GetGapsDuplicatedTest1();
        void GetCommonFieldNumber1();
        void GetCommonFieldNumber2();
        void GetCommonFieldNumber3();
        void GetCommonFieldNumber4();
        void GetCommonFieldNumber5();
        void GetCommonFieldNumber6();
        void GetCommonFieldNumber7();
        void GetCommonFieldNumber8();
        void GetCommonFieldNumber9();
        void GetCommonFieldNumber10();
        void GetCommonFieldNumber11();
        void GetCommonFieldNumber12();
        void RealGapsTest1();
        void RealGapsTest2();

    private:
        // Board for game.
        GomokuBoard* m_pGomokuBoard;
        BoardScore* m_pBoardScoreHuman;
        BoardScore* m_pBoardScoreCpu;
};

#endif /* TEST_BOARDSCORE_H_ */
