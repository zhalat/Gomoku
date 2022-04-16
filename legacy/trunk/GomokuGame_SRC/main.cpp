//============================================================================
// Name        : GomokuGame.cpp
// Author      : Zbigniew Halat
// Version     : 001 - start at 04-01-2015
// Version     :
// Version     :
// Copyright   : Your copyright notice
// Description : Gomoku game implementation
//============================================================================

#include <stdlib.h>          // For atexit(), atoi()
#include <ctime>             // For time to set seed for random.
#include <cstdlib>           // For srand().
#include "GomokuGame.hpp"    // For GomokuGame.
#include "MinMax.hpp"        // For MinMax.
#include "TwoPlayerGame.hpp"

// Singleton remover.
void MinMaxSingletonRemove()
{
    MinMax* pMinMax = MinMax::GetInstance();
    pMinMax->~MinMax();
}

void ScoreSingletonRemove()
{
    Score* pScore = Score::GetInstance();
    pScore->~Score();
}

int main( int argc, char *argv[] )
{
	srand( time( NULL ) );

    //*************************************************************************************************************************
    // atexit block: int atexit (void (*func)(void));
    // The function pointed by func is automatically called without arguments when the program terminates normally.
    // Note that calling order is reversed - the last registration will be removed as the first.
    //*************************************************************************************************************************

    // Avoid memory leak. Call singletons' destructor.
    atexit ( MinMaxSingletonRemove );
    atexit ( ScoreSingletonRemove );
    //*************************************************************************************************************************

    // Notice that first arg is always program name.
    const uint32_t expectedArg = 6;

    assert( expectedArg == argc );

    // Retrieve and valid passed arguments.
    const uint32_t boardSize = static_cast<uint32_t>( atoi( *( ++argv ) ) );
    const char* pHumanColor = *( ++argv );
    const uint32_t gameLevel = static_cast<uint32_t>( atoi( *( ++argv ) ) );
    const bool isRandomize = static_cast<bool>( atoi( *( ++argv ) ) );
    const uint32_t maxTime = static_cast<uint32_t>( atoi( *( ++argv ) ) );

    const bool isBoardSizeValid = ( ( boardSize >= GomokuBoard::MIN_GOMOKU_BOARD_SIZE ) && ( boardSize <= GomokuBoard::MAX_GOMOKU_BOARD_SIZE) );
    const bool isHumanColorValid = ( Board::PLAYER_EMPTY != Board::String2Player( pHumanColor ) );
    const bool isGameLevelValid = ( gameLevel < TwoPlayersGame::LEVEL_LAST );

    assert( isBoardSizeValid && isGameLevelValid && isHumanColorValid );

    GomokuGame GomokuGame;
    GomokuGame.Init( boardSize,											// Board size.
    			     Board::String2Player( pHumanColor ),				// Human color.
    			     static_cast<TwoPlayersGame::Level>( gameLevel ), 	// Game level.
    			     isRandomize,									    // If true game is randomized.
    			     maxTime,											// Max time for CPU move. 0 disabled.
    			     std::cin,											// Input stream.
    			     std::cout );										// Output stream.
    GomokuGame.Play();

    return 0;
}

/***************************************************************************
 *   Copyright (C) 2018 by Zbigniew Halat                                  *
 *   zby.halat@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/
