/*
 * Threat2CaseBTest.hpp
 *
 *  Created on: Mar 26, 2016
 *      Author: Zbigniew Halat
 */

#ifndef TEST_THREAT_2_CASE_A_H_
#define TEST_THREAT_2_CASE_A_H_

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

#include "Board.hpp"
#include "Threat2CaseB.hpp"
#include "GomokuBoard.hpp"

class ThreatFinder;

class Threat2CaseBTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( Threat2CaseBTest );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest1 );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest2 );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest2PlayerB );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest3 );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest4 );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest5 );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest6 );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest7 );
	CPPUNIT_TEST( FindPatternAbuttedToBoardTest1 );
	CPPUNIT_TEST( FindPatternAbuttedToBoardTest2 );
	CPPUNIT_TEST( FindPatternAbuttedToBoardTest3 );
	CPPUNIT_TEST( FindPatternAbuttedToBoardTest4 );
	CPPUNIT_TEST( FindPatternAbuttedToBoardTest5 );
	CPPUNIT_TEST( FindPatternAbuttedToBoardTest6 );
	CPPUNIT_TEST( FindPatternIntruder );
	CPPUNIT_TEST( FindPatternSixInRowTest1 );

	CPPUNIT_TEST( GetPieces1 );
	CPPUNIT_TEST( GetPieces2 );
	CPPUNIT_TEST( GetPieces3 );
	CPPUNIT_TEST( GetPieces4 );
	CPPUNIT_TEST( GetPieces5 );
	CPPUNIT_TEST( GetPieces6 );
	CPPUNIT_TEST( GetPieces7 );
	CPPUNIT_TEST_SUITE_END();

    public:
        void setUp( )
        {
            m_pGomokuBoard = new GomokuBoard( 15 );

			m_pThreatFinder = new Threat2CaseB();
			m_pThreatFinder->SetBoard( m_pGomokuBoard );
        };

        void tearDown( )
        {
            delete m_pGomokuBoard;
        };
        
    private:
        void FindPatternOnHorizontalTrendTest1();
        void FindPatternOnHorizontalTrendTest2();
        void FindPatternOnHorizontalTrendTest2PlayerB();
        void FindPatternOnHorizontalTrendTest3();
        void FindPatternOnHorizontalTrendTest4();
        void FindPatternOnHorizontalTrendTest5();
        void FindPatternOnHorizontalTrendTest6();
        void FindPatternOnHorizontalTrendTest7();
        void FindPatternAbuttedToBoardTest1();
        void FindPatternAbuttedToBoardTest2();
        void FindPatternAbuttedToBoardTest3();
        void FindPatternAbuttedToBoardTest4();
        void FindPatternAbuttedToBoardTest5();
        void FindPatternAbuttedToBoardTest6();
        void FindPatternIntruder();
        void FindPatternSixInRowTest1();

        void GetPieces1();
        void GetPieces2();
        void GetPieces3();
        void GetPieces4();
        void GetPieces5();
        void GetPieces6();
        void GetPieces7();

        // Board which will be analyzed regarding four pattern.
		GomokuBoard* m_pGomokuBoard;
		ThreatFinder* m_pThreatFinder;
};

#endif /* TEST_THREAT_2_CASE_A_H_ */
