#pragma once

#include <memory>
#include "Interfaces/IBoard.h"
#include "Interfaces/IGame.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Score
///
/// Gomoku game logic - user interface.
///
/// @par Full Description.
/// Middle implementation of game. Does not decide how user's move are
/// provided (gui/CLI/sockets etc), but implements gomoku general game flow.
///////////////////////////////////////////////////////////////////////////////////////////
class GomokuGame : public IGame
{
   public:
    static constexpr uint32_t k_MIN_BOARD_SIZE       = 5;
    static constexpr uint32_t k_DEFAULT_BOARD_SIZE   = 15;
    static constexpr uint32_t k_MAX_BOARD_SIZE       = 19;
    static constexpr uint32_t k_STOP_TO_BE_DEFENSIVE = 10;

    GomokuGame(uint32_t size,
               IBoard::Player humanColor,
               IGame::Level level,
               bool isRandomize,
               uint32_t maxTime);
    GomokuGame(const GomokuGame&) = delete;
    GomokuGame(GomokuGame&&) = delete;
    GomokuGame& operator=(const GomokuGame&) = delete;
    GomokuGame& operator=(GomokuGame&&) = delete;
    virtual ~GomokuGame() = default;

    void play() override;
    bool isWinner(IBoard::Player player) const override;
    bool isStalemate() const override;
    void restartGame() override;

private:
    void setBoard(const IBoard& board);
    bool isUserMoveValid(IBoard::PositionXY xy) const;
    IBoard::PositionXY getBestMove() const;

    unique_ptr<IBoard> m_board{nullptr};                //game board
    unique_ptr<ISpotter> m_spotterCpu{nullptr};         //finds threads. Cpu pov.
    unique_ptr<ISpotter> m_spotterHuman{nullptr};       //finds threads. Human pov.
    unique_ptr<ThreatTracker> m_trackerCpu{nullptr};    //storages threads for cpu
    unique_ptr<ThreatTracker> m_trackerHuman{nullptr};  //storages threads for human
    unique_ptr<ISearchTree> m_engine{nullptr};          //algorithm for finding best move
};

