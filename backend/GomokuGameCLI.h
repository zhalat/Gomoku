#pragma once
#include <iostream>
#include "Interfaces/IGame.h"

class GomokuGameCLI final : public IGameInteraction
{
public:
    // BackEnd -> CLI.
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
    static const constexpr char * FAREWELL              = "\n--->>Bye!\n";

    // CLI -> BackEnd.
    static const constexpr char * NEW_GAME = "--->>NewGame.";

    GomokuGameCLI(IBoard::Player humanColor);
    GomokuGameCLI(const GomokuGameCLI&) = delete;
    GomokuGameCLI(GomokuGameCLI&&) = delete;
    GomokuGameCLI& operator=(const GomokuGameCLI&) = delete;
    GomokuGameCLI& operator=(GomokuGameCLI&&) = delete;
    virtual ~GomokuGameCLI() = default;

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

