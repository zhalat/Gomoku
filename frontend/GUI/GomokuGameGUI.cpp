#include "GomokuGameGUI.h"

using namespace std;

// static const IBoard::PositionXY k_XY_OUT_OF_BOARD = IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD);

// GomokuGameCLI::GomokuGameCLI(IBoard::Player humanColor)
// : m_humanColor{humanColor}
// {}

// IBoard::PositionXY GomokuGameCLI::getUserMove() const
// {
//     IBoard::PositionXY retVal = k_XY_OUT_OF_BOARD;
//     uint32_t x               = 0;
//     uint32_t y               = 0;

//     while(true)
//     {
//         pOutputStream << YOUR_MOVE_MSG << TERMINATOR_MSG;
//         pOutputStream.flush();
//         x = 0;
//         y = 0;

//         pInputStream >> x;
//         if(pInputStream.fail())
//         {
//             pOutputStream << INVALID_PARAMETER_MSG << TERMINATOR_MSG;
//             pInputStream.clear();
//             // Ignore to the end of line
//             pInputStream.ignore(INT_MAX, '\n');
//             continue;
//         }

//         pInputStream >> y;
//         if(pInputStream.fail())
//         {
//             pOutputStream << INVALID_PARAMETER_MSG << TERMINATOR_MSG;
//             pInputStream.clear();
//             // Ignore to the end of line
//             pInputStream.ignore(INT_MAX, '\n');
//             continue;
//         }
//         else
//         {
//             break;
//         }

//         pOutputStream.flush();
//     }

//     retVal = IBoard::PositionXY(x, y);
//     return retVal;
// }

// bool GomokuGameCLI::getIsPlayAgain() const
// {


// }

// void GomokuGameCLI::invalidUserMoveNotify() const
// {
//     pOutputStream << INVALID_MOVE_MSG << TERMINATOR_MSG;
//     pOutputStream.flush();
// }

// void GomokuGameCLI::cpuMoveNotify(IBoard::PositionXY xy) const
// {
//     pOutputStream << *m_board;
//     pOutputStream << LAST_CPU_MOVE_MSG << xy;
//     pOutputStream.flush();
// }

// void GomokuGameCLI::humanMoveNotify(IBoard::PositionXY xy) const
// {
//     pOutputStream << *m_board;
//     pOutputStream << LAST_HUMAN_MOVE_MSG << xy;
//     pOutputStream.flush();
// }

// void GomokuGameCLI::winnerNotify(IBoard::Player player,vector<IBoard::PositionXY> winnerMark) const
// {
//     if(m_humanColor==player)
//     {
//         pOutputStream << WINNER_MSG;
//     }
//     else
//     {
//         pOutputStream << LOOSER_MSG;
//     }

//     for(const auto& el: winnerMark)
//     {
//         pOutputStream <<WINNER_MOVIES_MARK<< el;
//     }
//     pOutputStream.flush();
// }

// void GomokuGameCLI::stalemateNotify() const
// {
//     pOutputStream << STALEMATE_MSG;
//     pOutputStream.flush();
// }

// void GomokuGameCLI::restartGameNotify() const
// {
//     pOutputStream.clear();
//     pInputStream.clear();

//     pOutputStream << *m_board;
//     pOutputStream.flush();
// }

// void GomokuGameCLI::endGameNotify() const
// {
//     pOutputStream <<FAREWELL;
// }
