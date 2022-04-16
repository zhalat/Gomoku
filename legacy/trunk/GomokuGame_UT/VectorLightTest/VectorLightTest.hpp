/*
 * VectorLight.hpp
 *
 *  Created on: sep 29, 2016
 *      Author: zby
 */

#ifndef TEST_VECTOR_LIGHT_H_
#define TEST_VECTOR_LIGHT_H_

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
#include "VectorLight.hpp"
#include "Board.hpp"

class VectorLightTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( VectorLightTest );

	CPPUNIT_TEST( InitTest );
	CPPUNIT_TEST( InsertTest );
	CPPUNIT_TEST( HasNextVectorLightIteratorTest );
	CPPUNIT_TEST( IsPresentTest );
	CPPUNIT_TEST( RemoveTest1 );
	CPPUNIT_TEST( RemoveTest2 );
	CPPUNIT_TEST( IsSpaceTest );
	CPPUNIT_TEST( GetNumberOfElementsTest );
	CPPUNIT_TEST( ClearTest );

	CPPUNIT_TEST_SUITE_END();

    public:

        void setUp( )
        {
            m_pVectorLight = new VectorLight( Board::PositionField::INVALID_FIELD );
        };

        void tearDown( )
        {
            delete m_pVectorLight;
        };

    	void InitTest();
    	void InsertTest();
    	void HasNextVectorLightIteratorTest();
    	void IsPresentTest();
    	void RemoveTest1();
    	void RemoveTest2();
    	void IsSpaceTest();
    	void GetNumberOfElementsTest();
    	void ClearTest();

    private:
        VectorLight* m_pVectorLight;
};

#endif /* TEST_VECTOR_LIGHT_H_ */
