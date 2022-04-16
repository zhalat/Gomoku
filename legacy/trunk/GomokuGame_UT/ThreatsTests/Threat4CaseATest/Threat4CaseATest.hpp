/*
 * Threat4CaseATest.hpp
 *
 *  Created on: Mar 03, 2016
 *      Author: Zbigniew Halat
 */

#ifndef TEST_THREAT_FOUR_CASE_A_H_
#define TEST_THREAT_FOUR_CASE_A_H_

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
#include "Threat4CaseA.hpp"
#include "GomokuBoard.hpp"

class ThreatFinder;

class Threat4CaseATest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( Threat4CaseATest );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest1 );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest2 );
	CPPUNIT_TEST( FindPatternAbuttedToBoardFrameTest );
	CPPUNIT_TEST( GetThreatFieldsTest1 );
	CPPUNIT_TEST( GetThreatFieldsTest2 );
	CPPUNIT_TEST( GetThreatFieldsTest3 );
	CPPUNIT_TEST( GetThreatFieldsTest4 );

	CPPUNIT_TEST( GetPieces1 );
	CPPUNIT_TEST( GetPieces2 );

	CPPUNIT_TEST_SUITE_END();

    public:
        void setUp( )
        {
			m_pGomokuBoard = new GomokuBoard( 15 );

			m_pThreatFinder = new Threat4CaseA();
			m_pThreatFinder->SetBoard( m_pGomokuBoard );
        };

        void tearDown( )
        {
        	delete m_pGomokuBoard;
        	delete m_pThreatFinder;
        };
		
        void FindPatternOnHorizontalTrendTest1();
        void FindPatternOnHorizontalTrendTest2();
        void FindPatternAbuttedToBoardFrameTest();
        void GetThreatFieldsTest1();
        void GetThreatFieldsTest2();
        void GetThreatFieldsTest3();
        void GetThreatFieldsTest4();

        void GetPieces1();
        void GetPieces2();

    private:
	    // Board which will be analyzed regarding four pattern.
		GomokuBoard* m_pGomokuBoard;
		ThreatFinder* m_pThreatFinder;
};

#endif /* TEST_THREAT_FOUR_CASE_A_H_ */
