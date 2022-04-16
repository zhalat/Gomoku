/*
 * SingleListTest.cpp
 *
 *  Created on: 31 oct, 2016
 *      Author: halsoft
 */

#ifndef TEST_SINGLE_LIST_H_
#define TEST_SINGLE_LIST_H_

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
#include "SingleListIterator.hpp"

class SingleListTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( SingleListTest );

	CPPUNIT_TEST( IsEmptyTest );
	CPPUNIT_TEST( AddToTailTest );
	CPPUNIT_TEST( AddToHeadTest );
	CPPUNIT_TEST( RemoveFromTailTest );
	CPPUNIT_TEST( RemoveFromHeadTest);
	CPPUNIT_TEST( IsPresentTest );
	CPPUNIT_TEST( RemoveNodeTest );
	CPPUNIT_TEST( SizeTest );

	CPPUNIT_TEST_SUITE_END();

    public:

        void setUp()
        {
            m_pSingleList = new SingleList<uint32_t>;
        };

        void tearDown()
        {
            delete m_pSingleList;
        };

    	void IsEmptyTest();
    	void AddToTailTest();
    	void AddToHeadTest();
    	void RemoveFromTailTest();
    	void RemoveFromHeadTest();
    	void IsPresentTest();
    	void RemoveNodeTest();
    	void SizeTest();

    private:
        SingleList<uint32_t>* m_pSingleList;
};

#endif /* TEST_SINGLE_LIST_H_ */
