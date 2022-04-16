/*
 * StateEvaluationTest.hpp
 *
 *  Created on: jul 30, 2017
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
#include "StateEvaluation.hpp"

class StateEvaluationTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( StateEvaluationTest );

	// Head shot 4BC tests.
	CPPUNIT_TEST( IsHeadShot4BCPossibleTest1 );
	CPPUNIT_TEST( IsHeadShot4BCPossibleTest2 );
	CPPUNIT_TEST( IsHeadShot4BCPossibleTest3 );
	CPPUNIT_TEST( IsHeadShot4BCPossibleTest4 );
	CPPUNIT_TEST( IsHeadShot4BCPossibleTest5 );
	CPPUNIT_TEST( IsHeadShot4BCPossibleTest6 );
	CPPUNIT_TEST( IsHeadShot4BCPossibleTest7 );
	CPPUNIT_TEST( IsHeadShot4BCPossibleTest8 );
	CPPUNIT_TEST( IsHeadShot4BCPossibleTest9 );

	// Head shot 3A tests.
	CPPUNIT_TEST( IsHeadShot3APossibleTest1 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest2 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest3 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest4 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest5 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest6 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest7 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest8 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest9 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest10 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest11 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest12 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest13 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest14 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest15 );
	CPPUNIT_TEST( IsHeadShot3APossibleTest16 );

	// Head shot 3AA tests.
	CPPUNIT_TEST( IsHeadShot3AAPossibleTest1 );
	CPPUNIT_TEST( IsHeadShot3AAPossibleTest2 );
	CPPUNIT_TEST( IsHeadShot3AAPossibleTest3 );
	CPPUNIT_TEST( IsHeadShot3AAPossibleTest4 );
	CPPUNIT_TEST( IsHeadShot3AAPossibleTest5 );
	CPPUNIT_TEST( IsHeadShot3AAPossibleTest6 );
	CPPUNIT_TEST( IsHeadShot3AAPossibleTest7 );
	CPPUNIT_TEST( IsHeadShot3AAPossibleTest8 );
	CPPUNIT_TEST( IsHeadShot3AAPossibleTest9 );

	//  Head shot Dragon tests.
	CPPUNIT_TEST( IsHeadShotDragonPossibleTest1 );
	CPPUNIT_TEST( IsHeadShotDragonPossibleTest2 );
	CPPUNIT_TEST( IsHeadShotDragonPossibleTest3 );
	CPPUNIT_TEST( IsHeadShotDragonPossibleTest4 );
	CPPUNIT_TEST( IsHeadShotDragonPossibleTest5 );
	CPPUNIT_TEST( IsHeadShotDragonPossibleTest6 );
	CPPUNIT_TEST( IsHeadShotDragonPossibleTest7 );
	CPPUNIT_TEST( IsHeadShotDragonPossibleTest8 );

	// Head shot Lizard tests.
	CPPUNIT_TEST( IsHeadShotLizardPossibleTest1 );
	CPPUNIT_TEST( IsHeadShotLizardPossibleTest2 );
	CPPUNIT_TEST( IsHeadShotLizardPossibleTest3 );
	CPPUNIT_TEST( IsHeadShotLizardPossibleTest4 );
	CPPUNIT_TEST( IsHeadShotLizardPossibleTest5 );
	CPPUNIT_TEST( IsHeadShotLizardPossibleTest6 );
	CPPUNIT_TEST( IsHeadShotLizardPossibleTest7 );

	// Double 3A at one stroke tests.
	CPPUNIT_TEST( IsDouble3AOneStrokePossibleTest1 );
	CPPUNIT_TEST( IsDouble3AOneStrokePossibleTest2 );
	CPPUNIT_TEST( IsDouble3AOneStrokePossibleTest3 );
	CPPUNIT_TEST( IsDouble3AOneStrokePossibleTest4 );
	CPPUNIT_TEST( IsDouble3AOneStrokePossibleTest5 );
	CPPUNIT_TEST( IsDouble3AOneStrokePossibleTest6 );
	CPPUNIT_TEST( IsDouble3AOneStrokePossibleTest7 );
	CPPUNIT_TEST( IsDouble3AOneStrokePossibleTest8 );
    CPPUNIT_TEST( IsDouble3AOneStrokePossibleTest9 );

	// Double 3A mitigation tests.
	CPPUNIT_TEST( IsDoubleThreatMitigationPossibleTest1 );
	CPPUNIT_TEST( IsDoubleThreatMitigationPossibleTest2a );
	CPPUNIT_TEST( IsDoubleThreatMitigationPossibleTest2b );
	CPPUNIT_TEST( IsDoubleThreatMitigationPossibleTest3 );
	CPPUNIT_TEST( IsDoubleThreatMitigationPossibleTest4 );
	CPPUNIT_TEST( IsDoubleThreatMitigationPossibleTest5 );
	CPPUNIT_TEST( IsDoubleThreatMitigationPossibleTest6 );
	CPPUNIT_TEST( IsDoubleThreatMitigationPossibleTest7 );
	CPPUNIT_TEST( IsDoubleThreatMitigationPossibleTest8 );

	// Single 3A mitigation tests.
	CPPUNIT_TEST( IsSingle3AThreatMitigationPossibleTest1 );
	CPPUNIT_TEST( IsSingle3AThreatMitigationPossibleTest2 );
	CPPUNIT_TEST( IsSingle3AThreatMitigationPossibleTest3 );
	CPPUNIT_TEST( IsSingle3AThreatMitigationPossibleTest4 );
	CPPUNIT_TEST( IsSingle3AThreatMitigationPossibleTest5 );
	CPPUNIT_TEST( IsSingle3AThreatMitigationPossibleTest6 );
	CPPUNIT_TEST( IsSingle3AThreatMitigationPossibleTest7 );
	CPPUNIT_TEST( IsSingle3AThreatMitigationPossibleTest8 );
	CPPUNIT_TEST( IsSingle3AThreatMitigationPossibleTest9 );

	CPPUNIT_TEST_SUITE_END();

	void IsHeadShot4BCPossibleTest1();
	void IsHeadShot4BCPossibleTest2();
	void IsHeadShot4BCPossibleTest3();
	void IsHeadShot4BCPossibleTest4();
	void IsHeadShot4BCPossibleTest5();
	void IsHeadShot4BCPossibleTest6();
	void IsHeadShot4BCPossibleTest7();
	void IsHeadShot4BCPossibleTest8();
	void IsHeadShot4BCPossibleTest9();
	void IsHeadShot3APossibleTest1();
	void IsHeadShot3APossibleTest2();
	void IsHeadShot3APossibleTest3();
	void IsHeadShot3APossibleTest4();
	void IsHeadShot3APossibleTest5();
	void IsHeadShot3APossibleTest6();
	void IsHeadShot3APossibleTest7();
	void IsHeadShot3APossibleTest8();
	void IsHeadShot3APossibleTest9();
	void IsHeadShot3APossibleTest10();
	void IsHeadShot3APossibleTest11();
	void IsHeadShot3APossibleTest12();
	void IsHeadShot3APossibleTest13();
	void IsHeadShot3APossibleTest14();
	void IsHeadShot3APossibleTest15();
	void IsHeadShot3APossibleTest16();
	void IsHeadShot3AAPossibleTest1();
	void IsHeadShot3AAPossibleTest2();
	void IsHeadShot3AAPossibleTest3();
	void IsHeadShot3AAPossibleTest4();
	void IsHeadShot3AAPossibleTest5();
	void IsHeadShot3AAPossibleTest6();
	void IsHeadShot3AAPossibleTest7();
	void IsHeadShot3AAPossibleTest8();
	void IsHeadShot3AAPossibleTest9();
	void IsHeadShotDragonPossibleTest1();
	void IsHeadShotDragonPossibleTest2();
	void IsHeadShotDragonPossibleTest3();
	void IsHeadShotDragonPossibleTest4();
	void IsHeadShotDragonPossibleTest5();
	void IsHeadShotDragonPossibleTest6();
	void IsHeadShotDragonPossibleTest7();
	void IsHeadShotDragonPossibleTest8();
	void IsHeadShotLizardPossibleTest1();
	void IsHeadShotLizardPossibleTest2();
	void IsHeadShotLizardPossibleTest3();
	void IsHeadShotLizardPossibleTest4();
	void IsHeadShotLizardPossibleTest5();
	void IsHeadShotLizardPossibleTest6();
	void IsHeadShotLizardPossibleTest7();
	void IsDouble3AOneStrokePossibleTest1();
	void IsDouble3AOneStrokePossibleTest2();
	void IsDouble3AOneStrokePossibleTest3();
	void IsDouble3AOneStrokePossibleTest4();
	void IsDouble3AOneStrokePossibleTest5();
	void IsDouble3AOneStrokePossibleTest6();
	void IsDouble3AOneStrokePossibleTest7();
	void IsDouble3AOneStrokePossibleTest8();
	void IsDouble3AOneStrokePossibleTest9();
	void IsDoubleThreatMitigationPossibleTest1();
	void IsDoubleThreatMitigationPossibleTest2a();
	void IsDoubleThreatMitigationPossibleTest2b();
	void IsDoubleThreatMitigationPossibleTest3();
	void IsDoubleThreatMitigationPossibleTest4();
	void IsDoubleThreatMitigationPossibleTest5();
	void IsDoubleThreatMitigationPossibleTest6();
	void IsDoubleThreatMitigationPossibleTest7();
	void IsDoubleThreatMitigationPossibleTest8();
	void IsSingle3AThreatMitigationPossibleTest1();
	void IsSingle3AThreatMitigationPossibleTest2();
	void IsSingle3AThreatMitigationPossibleTest3();
	void IsSingle3AThreatMitigationPossibleTest4();
	void IsSingle3AThreatMitigationPossibleTest5();
	void IsSingle3AThreatMitigationPossibleTest6();
	void IsSingle3AThreatMitigationPossibleTest7();
	void IsSingle3AThreatMitigationPossibleTest8();
	void IsSingle3AThreatMitigationPossibleTest9();

    public:
        void setUp( )
        {
            m_pGomokuBoard = new GomokuBoard( 15 );
        };

        void tearDown( )
        {
            delete m_pGomokuBoard;
        };

    private:
        // Board for game.
        GomokuBoard* m_pGomokuBoard;
};

#endif /* TEST_MINMAX_H_ */
