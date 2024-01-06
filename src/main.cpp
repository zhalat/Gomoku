#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include "Exceptions.h"
#include "GomokuBoard.h"
#include "GomokuGame.h"
#include <iostream>

int main(int argc, char * argv[])
{
    srand(time(NULL));

    //*************************************************************************************************************************
    // atexit block: int atexit (void (*func)(void));
    // The function pointed by func is automatically called without arguments when the program terminates normally.
    // Note that calling order is reversed - the last registration will be removed as the first.
    //*************************************************************************************************************************

    // Notice that first arg is always program name.
    const uint32_t expectedArg = 6;

    assert(expectedArg == argc);

    // Retrieve and valid passed arguments.
    const uint32_t boardSize = static_cast<uint32_t>(atoi(*(++argv)));
    const char * pHumanColor = *(++argv);
    const uint32_t gameLevel = static_cast<uint32_t>(atoi(*(++argv)));
    const bool isRandomize   = static_cast<bool>(atoi(*(++argv)));
    const uint32_t maxTime   = static_cast<uint32_t>(atoi(*(++argv)));

    if(boardSize < GomokuBoard::k_MIN_GOMOKU_BOARD_SIZE or (boardSize > GomokuBoard::k_MAX_GOMOKU_BOARD_SIZE))
    {
        throw game_except::General{"Invalid parameter: Board size ouf scope."};
    }
    if(!pHumanColor or (IBoard::PLAYER_A != IBoard::String2Player(pHumanColor) and IBoard::PLAYER_B != IBoard::String2Player(pHumanColor)))
    {
        throw game_except::General{"Invalid parameter: Can not convert string into player pawn."};
    }
    if(!static_cast<IGame::Level>(gameLevel<IGame::Level::LEVEL_LAST))
    {
        throw game_except::General{"Invalid parameter: Game level out of scope."};
    }

    GomokuGame GomokuGame{};
    GomokuGame.init(boardSize,
                    IBoard::String2Player(pHumanColor),
                    static_cast<IGame::Level>(gameLevel),
                    isRandomize,
                    maxTime,
                    std::cin,
                    std::cout);
    GomokuGame.play();

    return 0;
}