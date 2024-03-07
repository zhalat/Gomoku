#pragma once

#include <memory>
#include "Interfaces/IBoard.h"
#include "Interfaces/IGame.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: GomokuGame
///
/// Gomoku game logic
///
/// @par Full Description.
/// The class provide gomoku game logic flow.
/// It doesn't know how to interact with players. Any players interactions are
/// delegated to concrete class which must be provided and implement IGameInteraction interface.
/// Design pattern: Template method.
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
               uint32_t maxTime,
               IGameInteraction& gameInteraction);
    GomokuGame(const GomokuGame&) = delete;
    GomokuGame(GomokuGame&&) = delete;
    GomokuGame& operator=(const GomokuGame&) = delete;
    GomokuGame& operator=(GomokuGame&&) = delete;
    virtual ~GomokuGame() = default;

    //IGame:
    void play() override;
    bool isWinner(IBoard::Player player) const override;
    bool isStalemate() const override;
    void restartGame() override;

    IBoard* getBoard() const
    {
        return m_board.get();
    }

private:
    void setBoard(const IBoard& board);
    bool isUserMoveValid(IBoard::PositionXY xy) const;
    IBoard::PositionXY getBestMove() const;
    IGameInteraction& m_gameInteraction;

    unique_ptr<ISpotter> m_spotterCpu{nullptr};         //finds threads. Cpu pov.
    unique_ptr<ISpotter> m_spotterHuman{nullptr};       //finds threads. Human pov.
    unique_ptr<ThreatTracker> m_trackerCpu{nullptr};    //storages threads for cpu
    unique_ptr<ThreatTracker> m_trackerHuman{nullptr};  //storages threads for human
    unique_ptr<ISearchTree> m_engine{nullptr};          //algorithm for finding best move
    unique_ptr<IBoard> m_board{nullptr};                //game board
};

