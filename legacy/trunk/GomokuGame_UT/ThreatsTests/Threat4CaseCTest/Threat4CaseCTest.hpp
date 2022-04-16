/*
 * Threat4CaseCTest.hpp
 *
 *  Created on: Mar 06, 2016
 *      Author: Zbigniew Halat
 */

#ifndef TEST_THREAT_FOUR_CASE_C_H_
#define TEST_THREAT_FOUR_CASE_C_H_

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
#include "Threat4CaseC.hpp"
#include "GomokuBoard.hpp"

class ThreatFinder;

class Threat4CaseCTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( Threat4CaseCTest );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest1 );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest2 );
	CPPUNIT_TEST( FindPatternAbuttedToBoardFrameTest1 );
	CPPUNIT_TEST( FindPatternAbuttedToBoardFrameTest2 );
	CPPUNIT_TEST( FindPatternAbuttedToBoardFrameTest3 );
	CPPUNIT_TEST( CheckingAgainstSixInRowTest1 );

	CPPUNIT_TEST( GetPieces1 );
	CPPUNIT_TEST( GetPieces2 );
	CPPUNIT_TEST( GetPieces3 );
	CPPUNIT_TEST( GetPieces4 );
	CPPUNIT_TEST( GetPieces5 );
	CPPUNIT_TEST( GetPieces6 );

	CPPUNIT_TEST_SUITE_END();

    public:
        void setUp( )
        {
			m_pGomokuBoard = new GomokuBoard( 15 );

			m_pThreatFinder = new Threat4CaseC();
			m_pThreatFinder->SetBoard( m_pGomokuBoard );
        };

        void tearDown( )
        {
        	delete m_pGomokuBoard;
        	delete m_pThreatFinder;
        };

        void FindPatternOnHorizontalTrendTest1();
        void FindPatternOnHorizontalTrendTest2();
        void FindPatternAbuttedToBoardFrameTest1();
        void FindPatternAbuttedToBoardFrameTest2();
        void FindPatternAbuttedToBoardFrameTest3();
        void CheckingAgainstSixInRowTest1();

        void GetPieces1();
        void GetPieces2();
        void GetPieces3();
        void GetPieces4();
        void GetPieces5();
        void GetPieces6();
		
    private:
	    // Board which will be analyzed regarding four pattern.
		GomokuBoard* m_pGomokuBoard;
		ThreatFinder* m_pThreatFinder;
};

#endif /* TEST_THREAT_FOUR_CASE_C_H_ */
