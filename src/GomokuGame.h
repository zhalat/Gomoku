#pragma once

#include "Interfaces/IBoard.h"
#include "Interfaces/IGame.h"
#include <memory>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: Score
///
/// Gomoku game logic - user interface.
///
/// @par Full Description.
/// Gomoku game class declaration.
///////////////////////////////////////////////////////////////////////////////////////////
class GomokuGame final : public IGame
{
   public:
    static constexpr uint32_t k_MIN_BOARD_SIZE     = 5;
    static constexpr uint32_t k_DEFAULT_BOARD_SIZE = 15;
    static constexpr uint32_t k_MAX_BOARD_SIZE     = 19;

    // After those moves number cpu can stop to be 	defensive.
    static constexpr uint32_t k_STOP_TO_BE_DEFENSIVE = 10;

    virtual ~GomokuGame() = default;
    void init(const uint32_t size, const IBoard::Player humanColor, const IGame::Level level,
              bool isRandomize, const uint32_t maxTime = 0, std::istream & inStream = std::cin,
              std::ostream & outStream = std::cout) override;
    void play() override;
    bool endGame() override;
    void restartGame() override;
    IBoard::PositionXY getUserMove() const override;
    bool isMoveValid(IBoard::PositionXY xy) const override;
    bool isWinner(IBoard::Player player) const override;
    bool isStalemate() const override;

   private:
    void setDifficultyLevel(const Level level);
    IBoard::PositionXY getBestMove() const;
    ISearchTree::PriorityQueueScore getInitCandidates() const;
    void setBoard(const IBoard& board);

    unique_ptr<IBoard> m_board{nullptr};
    unique_ptr<ISpotter> m_spotterCpu{nullptr};
    unique_ptr<ISpotter> m_spotterHuman{nullptr};
    unique_ptr<ThreatTracker> m_trackerCpu{nullptr};
    unique_ptr<ThreatTracker> m_trackerHuman{nullptr};
    unique_ptr<ISearchTree> m_engine{nullptr};

    IBoard::Player m_computerColor;
    IBoard::Player m_humanColor;
    IGame::Level m_level;
    uint32_t m_boardSize{0};
    Level m_depth{IGame::LEVEL_LAST};
    bool m_isRandomize{false};
    uint32_t m_maxTime{0};

    // Stream from/to data to be read/write.
    std::istream * pInputStream;
    std::ostream * pOutputStream;
};

