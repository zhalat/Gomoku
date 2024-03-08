#pragma once
#include <iostream>
#include "Interfaces/IGame.h"

class GomokuGameGUI final : public IGameInteraction
{
public:
    // BackEnd -> CLI.


    // CLI -> BackEnd.


    GomokuGameGUI(IBoard::Player humanColor);
    GomokuGameGUI(const GomokuGameGUI&) = delete;
    GomokuGameGUI(GomokuGameGUI&&) = delete;
    GomokuGameGUI& operator=(const GomokuGameGUI&) = delete;
    GomokuGameGUI& operator=(GomokuGameGUI&&) = delete;
    virtual ~GomokuGameGUI() = default;

    void setBoard(IBoard* board)
    {
        assert(board);
        m_board = board;
    }

private:
    IBoard::PositionXY getUserMove() const override;
    bool getIsPlayAgain() const override;
    void invalidUserMoveNotify() const override;
    void cpuMoveNotify(IBoard::PositionXY xy) const override;
    void humanMoveNotify(IBoard::PositionXY xy) const override;
    void winnerNotify(IBoard::Player player,vector<IBoard::PositionXY> winnerMark) const override;
    void stalemateNotify() const override;
    void restartGameNotify() const override;
    void endGameNotify() const override;

    // Stream from/to data to be read/write.
    std::istream& pInputStream {std::cin};
    std::ostream& pOutputStream {std::cout};
    IBoard* m_board{nullptr};
    const IBoard::Player m_humanColor{};
};

