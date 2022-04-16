/*
 * Threat3CaseAATest.hpp
 *
 *  Created on: Mar 12, 2016
 *      Author: Zbigniew Halat
 */

#ifndef TEST_THREAT_3_CASE_AA_H_
#define TEST_THREAT_3_CASE_AA_H_

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
#include "Threat3CaseAA.hpp"
#include "GomokuBoard.hpp"

class ThreatFinder;

class Threat3CaseAATest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( Threat3CaseAATest );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest1 );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest2 );
	CPPUNIT_TEST( FindPatternOnHorizontalTrendTest3 );

	CPPUNIT_TEST( GetPieces1 );
	CPPUNIT_TEST( GetPieces2 );

    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp( )
        {
            m_pGomokuBoard = new GomokuBoard( 15 );

			m_pThreatFinder = new Threat3CaseAA();
			m_pThreatFinder->SetBoard( m_pGomokuBoard );
        };

        void tearDown( )
        {
            delete m_pGomokuBoard;
            delete m_pThreatFinder;
        };
        
        void FindPatternOnHorizontalTrendTest1();
        void FindPatternOnHorizontalTrendTest2();
        void FindPatternOnHorizontalTrendTest3();

        void GetPieces1();
        void GetPieces2();

    private:


        // Board which will be analyzed regarding four pattern.
        GomokuBoard* m_pGomokuBoard;
		ThreatFinder* m_pThreatFinder;
};

#endif /* TEST_THREAT_3_CASE_AA_H_ */
