/*
 * OpenBookTest.cpp
 *
 *  Created on: 31 dec, 2016
 *      Author: halsoft
 */

#ifndef TEST_OPEN_BOOK_H_
#define TEST_OPEN_BOOK_H_

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
#include "Board.hpp"
#include "GomokuBoard.hpp"
#include "OpenBook.hpp"

class OpenBookTest: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( OpenBookTest );

	CPPUNIT_TEST( DirectOpeningGame1 );
	CPPUNIT_TEST( DirectOpeningGame2 );
	CPPUNIT_TEST( DirectOpeningGame3 );
	CPPUNIT_TEST( DirectOpeningGame4 );
	CPPUNIT_TEST( IndirectOpeningGame1 );
	CPPUNIT_TEST( IndirectOpeningGame2 );
	CPPUNIT_TEST( IndirectOpeningGame3 );
	CPPUNIT_TEST( IndirectOpeningGame4 );

	CPPUNIT_TEST_SUITE_END();

    public:

        void setUp()
        {
            m_pBoard = new GomokuBoard( BOARD_SIZE );
        };

        void tearDown()
        {
            delete m_pBoard;
        };

    private:
    	void DirectOpeningGame1();
    	void DirectOpeningGame2();
    	void DirectOpeningGame3();
    	void DirectOpeningGame4();
    	void IndirectOpeningGame1();
    	void IndirectOpeningGame2();
    	void IndirectOpeningGame3();
    	void IndirectOpeningGame4();

        static const uint32_t BOARD_SIZE = 15;
        Board* m_pBoard;
};

#endif /* TEST_OPEN_BOOK_H_ */
