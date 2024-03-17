#include "Exceptions.h"
#include "GomokuGameClientGUI.h"

template<class T>
static ssize_t getMessageSize(const T& message)
{
    std::string serializedMsg;
    message.SerializeToString(&serializedMsg);
    return serializedMsg.size();
}

GomokuGameClientGUI::GomokuGameClientGUI(IBoard::Player humanColor)
:m_humanColor{humanColor}
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    memset(&m_sockName, 0, sizeof(m_sockName));
    m_sockName.sun_family = k_SOCKET_TYPE;
    strncpy(m_sockName.sun_path, k_SOCKET_GUI_NAME, sizeof(m_sockName.sun_path)-1);
}

IBoard::PositionXY GomokuGameClientGUI::getUserMove() const
{
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgQuery.set_k_id(message::MsgID::USR_MOVE_QUERY);
	if(!m_msgQuery.SerializeToString(&serializedMessage))
	{
		throw game_except::General{"Message data query serialization error."};
	}

	//header
	m_msgHeader.set_m_msgid(message::MsgID::USR_MOVE_QUERY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
	{
		throw game_except::General{"Message header query serialization error."};
	}

	IBoard::PositionXY resp;
	const int stat = sendMsgToServer(serializedHeader, serializedMessage, true, resp);

}

bool GomokuGameClientGUI::getIsPlayAgain() const{};
void GomokuGameClientGUI::invalidUserMoveNotify() const{};
void GomokuGameClientGUI::cpuMoveNotify(IBoard::PositionXY xy) const{};
void GomokuGameClientGUI::humanMoveNotify(IBoard::PositionXY xy) const{};
void GomokuGameClientGUI::winnerNotify(IBoard::Player player,vector<IBoard::PositionXY> winnerMark) const{};
void GomokuGameClientGUI::stalemateNotify() const{};
void GomokuGameClientGUI::restartGameNotify() const{};
void GomokuGameClientGUI::endGameNotify() const{};
