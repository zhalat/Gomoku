#include "GomokuGameGUI.h"
#include "Exceptions.h"
#include "protobuf/messages.pb.h"
#include <cstdlib>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_GUI_NAME = "/tmp/GomokuGuiSocket"
#define SOCKET_TYPE = AF_LOCAL
static message::Header msgHeader;
static message::MoveXy msgMoveXy;
static message::MsgQuery msgQuery;
static message::MsgNotify msgNotify;

template<class T>
static ssize_t getMessageSize(const T& message)
{
    std::string serializedMsg;
    message.SerializeToString(&serializedMsg);
    return serializedMsg.size();
}


static const IBoard::PositionXY k_XY_OUT_OF_BOARD = IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD);

GomokuGameGUI::GomokuGameGUI(IBoard::Player humanColor)
:m_humanColor{humanColor}
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

IBoard::PositionXY GomokuGameGUI::getUserMove() const{};
bool GomokuGameGUI::getIsPlayAgain() const{};
void GomokuGameGUI::invalidUserMoveNotify() const{};
void GomokuGameGUI::cpuMoveNotify(IBoard::PositionXY xy) const{};
void GomokuGameGUI::humanMoveNotify(IBoard::PositionXY xy) const{};
void GomokuGameGUI::winnerNotify(IBoard::Player player,vector<IBoard::PositionXY> winnerMark) const{};
void GomokuGameGUI::stalemateNotify() const{};
void GomokuGameGUI::restartGameNotify() const{};
void GomokuGameGUI::endGameNotify() const{};