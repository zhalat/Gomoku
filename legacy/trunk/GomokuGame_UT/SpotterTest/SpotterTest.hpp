/*
 * SpotterTest.cpp
 *
 *  Created on: 31 oct, 2016
 *      Author: halsoft
 */

#ifndef TEST_SPOTTER_H_
#define TEST_SPOTTER_H_

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

#include "SingleList.hpp"
#include "Spotter.hpp"
#include "BoardScore.hpp"
#include "Board.hpp"


class SpotterTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( SpotterTest );

	CPPUNIT_TEST( ExecuteTest_FindingTwoListThreats1 );
	CPPUNIT_TEST( ExecuteTest_FindingTwoListThreats2 );
	CPPUNIT_TEST( ExecuteTest_ThreatGetPromotion1 );
	CPPUNIT_TEST( ExecuteTest_ThreatGetPromotion2 );
	CPPUNIT_TEST( ExecuteTest_ThreatGetDissmision1 );
	CPPUNIT_TEST( ExecuteTest_ThreatGetDissmision2 );
	CPPUNIT_TEST( ExecuteTest_ThreatGetDissmision3 );

	CPPUNIT_TEST( PromotionTHREAT_2_CASE_BTest1 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_BTest2 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_BTest3 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_CTest1 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_CTest2 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_ATest1 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_ATest2 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_ATest3 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_ATest4 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_ATest5 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_ATest6 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_AATest1 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_AATest2 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_AATest3 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_AATest4 );
	CPPUNIT_TEST( PromotionTHREAT_2_CASE_AATest5 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_BTest1 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_BTest2 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_CTest1 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_CTest2 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_CTest3 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_CTest4 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_ATest1 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_ATest2 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_ATest3 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_ATest4 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_ATest5 );
	CPPUNIT_TEST( PromotionTHREAT_3_CASE_ATest6 );
	CPPUNIT_TEST( PromotionTHREAT_4_CASE_BTest1 );
	CPPUNIT_TEST( PromotionTHREAT_4_CASE_BTest2 );
	CPPUNIT_TEST( PromotionTHREAT_4_CASE_CTest1 );
	CPPUNIT_TEST( PromotionTHREAT_4_CASE_CTest2 );
	CPPUNIT_TEST( PromotionTHREAT_4_CASE_ATest1 );

	CPPUNIT_TEST( DismissalTHREAT_2_CASE_BTest1 );
	CPPUNIT_TEST( DismissalTHREAT_2_CASE_CTest1 );
	CPPUNIT_TEST( DismissalTHREAT_2_CASE_ATest1 );
	CPPUNIT_TEST( DismissalTHREAT_2_CASE_ATest2 );
	CPPUNIT_TEST( DismissalTHREAT_2_CASE_ATest3 );
	CPPUNIT_TEST( DismissalTHREAT_2_CASE_AATest1 );
	CPPUNIT_TEST( DismissalTHREAT_2_CASE_AATest2 );
	CPPUNIT_TEST( DismissalTHREAT_3_CASE_BTest1 );
	CPPUNIT_TEST( DismissalTHREAT_3_CASE_BTest2 );
	CPPUNIT_TEST( DismissalTHREAT_3_CASE_CTest1 );
	CPPUNIT_TEST( DismissalTHREAT_3_CASE_CTest2 );
	CPPUNIT_TEST( DismissalTHREAT_3_CASE_CTest3 );
	CPPUNIT_TEST( DismissalTHREAT_3_CASE_ATest1 );
	CPPUNIT_TEST( DismissalTHREAT_3_CASE_ATest2 );
	CPPUNIT_TEST( DismissalTHREAT_3_CASE_ATest3 );
	CPPUNIT_TEST( DismissalTHREAT_3_CASE_ATest4 );
	CPPUNIT_TEST( DismissalTHREAT_4_CASE_BTest1 );
	CPPUNIT_TEST( DismissalTHREAT_4_CASE_BTest2 );
	CPPUNIT_TEST( DismissalTHREAT_4_CASE_BTest3 );
	CPPUNIT_TEST( DismissalTHREAT_4_CASE_CTest1 );
	CPPUNIT_TEST( DismissalTHREAT_4_CASE_CTest2 );
	CPPUNIT_TEST( DismissalTHREAT_4_CASE_CTest3 );
	CPPUNIT_TEST( DismissalTHREAT_4_CASE_ATest1 );
	CPPUNIT_TEST( DismissalTHREAT_4_CASE_ATest2 );

	//Spotter Test Edge.
	//The test shows how threat behaves when my move is put on the threat edge
	//like: .x.x.x.
	//a new move:
	//	  .x.x.x.x.
	CPPUNIT_TEST( EdgeTHREAT_2_CASE_BTest1 );
	CPPUNIT_TEST( EdgeTHREAT_2_CASE_BTest2 );
	CPPUNIT_TEST( EdgeTHREAT_2_CASE_AATest1 );
	CPPUNIT_TEST( EdgeTHREAT_2_CASE_AATest2 );
	CPPUNIT_TEST( EdgeTHREAT_2_CASE_ATest1 );
	CPPUNIT_TEST( EdgeTHREAT_2_CASE_ATest2 );
	CPPUNIT_TEST( EdgeTHREAT_3_CASE_BTest1 );
	CPPUNIT_TEST( EdgeTHREAT_3_CASE_BTest2 );
	CPPUNIT_TEST( EdgeTHREAT_3_CASE_AATest1 );
	CPPUNIT_TEST( EdgeTHREAT_3_CASE_AATest2 );

	CPPUNIT_TEST_SUITE_END();

    public:

        void setUp()
        {
            m_pBoard = new GomokuBoard( BOARD_SIZE );
        	m_pBoardScore = new BoardScore( Board::PLAYER_A );
        	m_pBoardScore->SetBoard( *m_pBoard );

        	SetBoard( *m_pBoard );

        	m_pSpotter = new Spotter( *m_pBoardScore );
        };

        void tearDown()
        {
            delete m_pBoard;
        	delete m_pBoardScore;
        	delete m_pSpotter;
        };

        void ExecuteTest_FindingTwoListThreats1();
        void ExecuteTest_FindingTwoListThreats2();
        void ExecuteTest_ThreatGetPromotion1();
        void ExecuteTest_ThreatGetPromotion2();
        void ExecuteTest_ThreatGetDissmision1();
        void ExecuteTest_ThreatGetDissmision2();
        void ExecuteTest_ThreatGetDissmision3();

        void PromotionTHREAT_2_CASE_BTest1();
        void PromotionTHREAT_2_CASE_BTest2();
        void PromotionTHREAT_2_CASE_BTest3();
        void PromotionTHREAT_2_CASE_CTest1();
        void PromotionTHREAT_2_CASE_CTest2();
        void PromotionTHREAT_2_CASE_ATest1();
        void PromotionTHREAT_2_CASE_ATest2();
        void PromotionTHREAT_2_CASE_ATest3();
        void PromotionTHREAT_2_CASE_ATest4();
        void PromotionTHREAT_2_CASE_ATest5();
        void PromotionTHREAT_2_CASE_ATest6();
        void PromotionTHREAT_2_CASE_AATest1();
        void PromotionTHREAT_2_CASE_AATest2();
        void PromotionTHREAT_2_CASE_AATest3();
        void PromotionTHREAT_2_CASE_AATest4();
        void PromotionTHREAT_2_CASE_AATest5();
        void PromotionTHREAT_3_CASE_BTest1();
        void PromotionTHREAT_3_CASE_BTest2();
        void PromotionTHREAT_3_CASE_CTest1();
        void PromotionTHREAT_3_CASE_CTest2();
        void PromotionTHREAT_3_CASE_CTest3();
        void PromotionTHREAT_3_CASE_CTest4();
        void PromotionTHREAT_3_CASE_ATest1();
        void PromotionTHREAT_3_CASE_ATest2();
        void PromotionTHREAT_3_CASE_ATest3();
        void PromotionTHREAT_3_CASE_ATest4();
        void PromotionTHREAT_3_CASE_ATest5();
        void PromotionTHREAT_3_CASE_ATest6();
        void PromotionTHREAT_4_CASE_BTest1();
        void PromotionTHREAT_4_CASE_BTest2();
        void PromotionTHREAT_4_CASE_CTest1();
        void PromotionTHREAT_4_CASE_CTest2();
        void PromotionTHREAT_4_CASE_ATest1();

        void DismissalTHREAT_2_CASE_BTest1();
        void DismissalTHREAT_2_CASE_CTest1();
        void DismissalTHREAT_2_CASE_ATest1();
        void DismissalTHREAT_2_CASE_ATest2();
        void DismissalTHREAT_2_CASE_ATest3();
        void DismissalTHREAT_2_CASE_AATest1();
        void DismissalTHREAT_2_CASE_AATest2();
        void DismissalTHREAT_3_CASE_BTest1();
        void DismissalTHREAT_3_CASE_BTest2();
        void DismissalTHREAT_3_CASE_CTest1();
        void DismissalTHREAT_3_CASE_CTest2();
        void DismissalTHREAT_3_CASE_CTest3();
        void DismissalTHREAT_3_CASE_ATest1();
        void DismissalTHREAT_3_CASE_ATest2();
        void DismissalTHREAT_3_CASE_ATest3();
        void DismissalTHREAT_3_CASE_ATest4();
        void DismissalTHREAT_4_CASE_BTest1();
        void DismissalTHREAT_4_CASE_BTest2();
        void DismissalTHREAT_4_CASE_BTest3();
        void DismissalTHREAT_4_CASE_CTest1();
        void DismissalTHREAT_4_CASE_CTest2();
        void DismissalTHREAT_4_CASE_CTest3();
        void DismissalTHREAT_4_CASE_ATest1();
        void DismissalTHREAT_4_CASE_ATest2();

    	//Spotter Test Edge.
        void EdgeTHREAT_2_CASE_BTest1();
        void EdgeTHREAT_2_CASE_BTest2();
        void EdgeTHREAT_2_CASE_AATest1();
        void EdgeTHREAT_2_CASE_AATest2();
        void EdgeTHREAT_2_CASE_ATest1();
        void EdgeTHREAT_2_CASE_ATest2();
        void EdgeTHREAT_3_CASE_BTest1();
		void EdgeTHREAT_3_CASE_BTest2();
		void EdgeTHREAT_3_CASE_AATest1();
		void EdgeTHREAT_3_CASE_AATest2();

    private:
        void SetBoard( const Board& rBoard );

        static const uint32_t BOARD_SIZE = 15;

        Board* m_pBoard;
        BoardScore* m_pBoardScore;
        Spotter* m_pSpotter;
};

#endif /* TEST_SPOTTER_H_ */
