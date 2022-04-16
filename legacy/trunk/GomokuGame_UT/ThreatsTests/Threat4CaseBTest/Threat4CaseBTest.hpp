/*
 * Threat4CaseBTest.hpp
 *
 *  Created on: Jan 25, 2016
 *      Author: zby
 */

#ifndef TEST_THREAT_FOUR_H_
#define TEST_THREAT_FOUR_H_

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
#include "Threat4CaseB.hpp"

class ThreatFinder;

class Threat4CaseBTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( Threat4CaseBTest );
	CPPUNIT_TEST( FindThreatFourPatternHorizontalTrend1Test );
	CPPUNIT_TEST( FindThreatFourPatternHorizontalTrend2Test );
	CPPUNIT_TEST( FindThreatFourPatternHorizontalTrend3Test );
	CPPUNIT_TEST( FindThreatFourPatternAbuttedToBoardFrame1Test );
	CPPUNIT_TEST( FindThreatFourPatternAbuttedToBoardFrame2Test );
	CPPUNIT_TEST( FindThreatFourPatternAbuttedToBoardFrame3Test );
	CPPUNIT_TEST( FindThreatFourPatternAbuttedToBoardFrame4Test );
	CPPUNIT_TEST( FindThreatFourPatternAbuttedToBoardFrame5Test );
	CPPUNIT_TEST( FindThreatFourPatternAbuttedToBoardFrame6Test );
	CPPUNIT_TEST( FindThreatSixInRowTest1 );
	CPPUNIT_TEST( FindThreatFourPatternMixTrendTest );

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

			m_pThreatFinder = new Threat4CaseB();
			m_pThreatFinder->SetBoard( m_pGomokuBoard );
        };

        void tearDown( )
        {
        	delete m_pGomokuBoard;
        	delete m_pThreatFinder;
        };

        void FindThreatFourPatternHorizontalTrend1Test();
        void FindThreatFourPatternHorizontalTrend2Test();
        void FindThreatFourPatternHorizontalTrend3Test();
        void FindThreatFourPatternAbuttedToBoardFrame1Test();
        void FindThreatFourPatternAbuttedToBoardFrame2Test();
        void FindThreatFourPatternAbuttedToBoardFrame3Test();
        void FindThreatFourPatternAbuttedToBoardFrame4Test();
        void FindThreatFourPatternAbuttedToBoardFrame5Test();
        void FindThreatFourPatternAbuttedToBoardFrame6Test();
        void FindThreatSixInRowTest1();
        void FindThreatFourPatternMixTrendTest();

        void GetPieces1();
        void GetPieces2();
        void GetPieces3();
        void GetPieces4();
        void GetPieces5();
        void GetPieces6();
        void GetPieces7();

    private:
	    // Board which will be analyzed regarding four pattern.
		GomokuBoard* m_pGomokuBoard;
		ThreatFinder* m_pThreatFinder;
};

#endif /* TEST_THREAT_FOUR_H_ */
