#pragma once
#include "GomokuGame.h"

class GomokuGameCLI final : public GomokuGame
{
    public:
    GomokuGameCLI(uint32_t size,
                  IBoard::Player humanColor,
                  IGame::Level level,
                  bool isRandomize,
                  uint32_t maxTime)
    :GomokuGame{size, humanColor, level, isRandomize, maxTime}
    {}
    GomokuGameCLI(const GomokuGameCLI&) = delete;
    GomokuGameCLI(GomokuGameCLI&&) = delete;
    GomokuGameCLI& operator=(const GomokuGameCLI&) = delete;
    GomokuGameCLI& operator=(GomokuGameCLI&&) = delete;
    virtual ~GomokuGameCLI() = default;

    IBoard::PositionXY getUserMove() const override{};
    bool getIsPlayAgain() const override{};
    void invalidUserMoveNotify() const override{};
    void cpuMoveNotify(IBoard::PositionXY xy) const override{};
    void winnerNotify(IBoard::Player player,vector<IBoard::PositionXY> winnerMark) const override{};
    void stalemateNotify() const override{};
    void restartGameNotify() const override{};
    void endGameNotify() const override{};
};

