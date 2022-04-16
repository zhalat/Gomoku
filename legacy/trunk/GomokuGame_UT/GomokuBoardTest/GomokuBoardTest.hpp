/*
 * Test_GomokuBoard.hpp
 *
 *  Created on: Jan 25, 2015
 *      Author: zby
 */

#ifndef TEST_GOMOKUBOARD_H_
#define TEST_GOMOKUBOARD_H_

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

class GomokuBoardTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( GomokuBoardTest );
	CPPUNIT_TEST( ConstructorInvalidParameterTest );
	CPPUNIT_TEST( ConstructorConnectionCorrectnessTest );
	CPPUNIT_TEST( CopyConstructorTest );
	CPPUNIT_TEST( PutMoveTest );
	CPPUNIT_TEST( GetMoveTest );
	CPPUNIT_TEST( GetLastMoveTest );
	CPPUNIT_TEST( VacantFieldsTest );
	CPPUNIT_TEST( EdgeDistanceTest );
	CPPUNIT_TEST( NeighbourDistanceTest );
	CPPUNIT_TEST( InRowTest );
	CPPUNIT_TEST( IsOnEdgeTest );
	CPPUNIT_TEST( GoDirectionTest );
	CPPUNIT_TEST( RemoveMoveTest );
	CPPUNIT_TEST( RemoveNLastMoveTest );
	CPPUNIT_TEST( OppositePlayerTest );
	CPPUNIT_TEST( GetFirstMoveTest );

	CPPUNIT_TEST_FAIL( GetMoveTestFail );
	CPPUNIT_TEST_SUITE_END();

    public:
        void setUp( )
        {
        	m_GomokuBoard = new GomokuBoard( 6 );
        };

        void tearDown( )
        {
        	delete m_GomokuBoard;
        };

        void ConstructorInvalidParameterTest();
        void ConstructorConnectionCorrectnessTest();
        void CopyConstructorTest();
        void PutMoveTest();
        void GetMoveTest();
        void GetLastMoveTest();
        void VacantFieldsTest();
        void EdgeDistanceTest();
        void NeighbourDistanceTest();
        void InRowTest();
        void IsOnEdgeTest();
        void GoDirectionTest();
        void RemoveMoveTest();
        void RemoveNLastMoveTest();
        void OppositePlayerTest();
        void GetFirstMoveTest();

        void GetMoveTestFail();

    private:
        GomokuBoard* m_GomokuBoard;
};

#endif /* TEST_GOMOKUBOARD_H_ */
