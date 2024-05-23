#pragma once

#include "IBoard.h"
#include "ISearchTree.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: IGame
///
/// Board game interface declaration. Solely for board.
///
/// @par Full Description.
/// Abstract class for each 2 players board game. Board state only.
///////////////////////////////////////////////////////////////////////////////////////////
class IGame
{
   public:
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

    virtual void play() = 0;
    virtual bool isWinner(IBoard::Player player) const = 0;
    virtual bool isStalemate() const = 0;
    virtual void restartGame() = 0;

    IGame(uint32_t size,
          IBoard::Player humanColor,
          IGame::Level level,
          bool isRandomize,
          uint32_t maxTime)
    :m_boardSize{size}
    ,m_humanColor{humanColor}
    ,m_computerColor{(humanColor == IBoard::PLAYER_A) ? IBoard::PLAYER_B : IBoard::PLAYER_A}
    ,m_level{level}
    ,m_isRandomize{isRandomize}
    ,m_maxTime{maxTime} {}
    virtual ~IGame()=default;
    IGame(const IGame&) = delete;
    IGame(IGame&&) = delete;
    IGame& operator=(const IGame&) = delete;
    IGame& operator=(IGame&&) = delete;

protected:
    uint32_t m_boardSize{};
    IBoard::Player m_humanColor;
    IBoard::Player m_computerColor;
    IGame::Level m_level;
    bool m_isRandomize{false};
    uint32_t m_maxTime{0};

};

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: IGameInteraction
///
/// Board game interface declaration. Solely for player interaction.
///
/// @par Full Description.
/// Abstract class for each 2 players board game. Interaction only.
///////////////////////////////////////////////////////////////////////////////////////////
class IGameInteraction
{
public:
    virtual IBoard::PositionXY getUserMove() const = 0;
    virtual bool getIsPlayAgain()  = 0;
    virtual void invalidUserMoveNotify() const = 0;
    virtual void cpuMoveNotify(IBoard::PositionXY xy) const = 0;
    virtual void humanMoveNotify(IBoard::PositionXY xy) const =0;
    virtual void winnerNotify(IBoard::Player player, vector<IBoard::PositionXY> winnerMark) const = 0;
    virtual void stalemateNotify() const = 0;
    virtual void restartGameNotify() const = 0;
    virtual void endGameNotify() const = 0;
};
