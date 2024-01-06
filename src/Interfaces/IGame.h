#pragma once

#include "IBoard.h"
#include "ISearchTree.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Game
///
/// Game interface declaration.
///
/// @par Full Description.
/// Abstract class for each 2 players boad game.
///////////////////////////////////////////////////////////////////////////////////////////
class IGame
{
   public:
    // BackEnd -> GUI.
    static const constexpr char * TERMINATOR_MSG        = "\n##\n";
    static const constexpr char * WINNER_MSG            = "\n--->>Game over. You won.\n";
    static const constexpr char * LOOSER_MSG            = "\n--->>Game over. Computer won.\n";
    static const constexpr char * STALEMATE_MSG         = "\n--->>Game over. Stalemate.\n";
    static const constexpr char * YOUR_MOVE_MSG         = "\n--->>Your move:\n";
    static const constexpr char * LAST_CPU_MOVE_MSG     = "\n--->>Last cpu move:\n";
    static const constexpr char * LAST_HUMAN_MOVE_MSG   = "\n--->>Last human move:\n";
    static const constexpr char * INVALID_MOVE_MSG      = "\n!--->>Invalid move.\n";
    static const constexpr char * INVALID_PARAMETER_MSG = "\n!--->>Invalid parameter.\n";
    static const constexpr char * CHOOSING_COLOR_MSG    = "\n--->>Choose your color: x or o.\n";
    static const constexpr char * WINNER_MOVIES_MARK    = "w";

    // GUI -> BackEnd.
    static const constexpr char * NEW_GAME = "--->>NewGame.";

    enum Level
    {
        LEVEL_NONE   = 0,
        BEGINNER     = 1,
        INTERMEDIATE = 2,
        ADVANCED     = 3,
        EXPERT       = 4,

        // Must be the last
        LEVEL_LAST
    };

    virtual void init(uint32_t size, IBoard::Player humanColor, IGame::Level level,
                      bool isRandomize, uint32_t maxTime = 0, std::istream & inStream = std::cin,
                      std::ostream & outStream = std::cout) = 0;
    virtual void play() = 0;
    virtual bool endGame() = 0;
    virtual void restartGame() = 0;
    virtual IBoard::PositionXY getUserMove() const = 0;
    virtual bool isMoveValid(IBoard::PositionXY xy) const = 0;
    virtual bool isWinner(IBoard::Player player) const = 0;
    virtual bool isStalemate() const = 0;
    virtual ~IGame()=default;
};
