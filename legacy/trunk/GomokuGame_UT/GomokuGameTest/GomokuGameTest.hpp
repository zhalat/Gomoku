/*
 * GomokuGameTest.hpp
 *
 *  Created on: Apr 19, 2016
 *      Author: zby
 */

#ifndef TEST_GOMOKUGAME_H_
#define TEST_GOMOKUGAME_H_

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
#include "Score.hpp"
#include "GomokuBoard.hpp"
#include "GomokuGame.hpp"

class GomokuGameTest: public CppUnit::TestFixture
{
	static const uint32_t BOARD_SIZE = 15;
	static const Board::Player humanColor = Board::PLAYER_A;

	CPPUNIT_TEST_SUITE( GomokuGameTest );
	//ToDo
	CPPUNIT_TEST_SUITE_END();

    public:
        void setUp()
        {
            m_pGame = new GomokuGame();
            m_pGame->Init( BOARD_SIZE, humanColor, TwoPlayersGame::BEGINNER, false );
        };

        void tearDown( )
        {
            delete m_pGame;
        };


        GomokuGameTest()
        {
        	m_pGame = NULL;
        }

    private:
        GomokuGame* m_pGame;
};

#endif /* TEST_GOMOKUGAME_H_ */
