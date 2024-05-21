#include "Exceptions.h"
#include "GomokuGameClientGUI.h"
#include <QDebug>

GomokuGameClientGUI::GomokuGameClientGUI(IBoard::Player humanColor)
:m_humanColor{humanColor}
{
	qInfo() << "Creating socket client";
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    memset(&m_sockName, 0, sizeof(m_sockName));
    m_sockName.sun_family = k_SOCKET_TYPE;
    strncpy(m_sockName.sun_path, k_SOCKET_GUI_NAME, sizeof(m_sockName.sun_path)-1);
}

IBoard::PositionXY GomokuGameClientGUI::getUserMove() const
{
    qInfo() << "Socket Client: Backend wants human move...";

    m_msgQuery.Clear();
    m_msgHeader.Clear();
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgQuery.set_k_id(message::MsgID::USR_MOVE_QUERY);
	if(!m_msgQuery.SerializeToString(&serializedMessage))
		throw game_except::General{"Socket Client: Get user move creating msg failed"};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::USR_MOVE_QUERY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Socket Client: Get user move creating msg failed"};

    IBoard::PositionXY resp;
    ResponseVariant respVar= resp;
    const int stat = sendMsgToServer(serializedHeader, serializedMessage, true, respVar);
	if(stat<0)
		throw game_except::General{"Socket Client: Get user move failed"};

    resp = std::get<IBoard::PositionXY>(respVar);
	qInfo() << "Socket Client: Human move is: ("<<resp.m_x<<","<<resp.m_y<<")";
    return resp;
}

bool GomokuGameClientGUI::getIsPlayAgain() const
{
    qInfo() << "Socket Client: Ask user if play again";

    m_msgQuery.Clear();
    m_msgHeader.Clear();
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgQuery.set_k_id(message::MsgID::REPLAY_QUERY);
    if(!m_msgQuery.SerializeToString(&serializedMessage))
        throw game_except::General{"Socket Client: 'getIsPlayAgain()' creating msg failed"};

    //header
    m_msgHeader.set_m_msgid(message::MsgID::REPLAY_QUERY);
    m_msgHeader.set_m_msgsize(serializedMessage.size());
    if(!m_msgHeader.SerializeToString(&serializedHeader))
        throw game_except::General{"Socket Client: 'getIsPlayAgain()' creating msg header failed"};

    bool resp{false};
    ResponseVariant respVar = resp;
    const int stat = sendMsgToServer(serializedHeader, serializedMessage, true, respVar);

    if(stat<0)
        throw game_except::General{"Socket Client: 'getIsPlayAgain()' response failed"};

     resp = std::get<bool>(respVar);

    return resp;

};

void GomokuGameClientGUI::invalidUserMoveNotify() const
{
	qWarning() << "Socket Client: Backend noticed invalid human's move ..";

	m_msgNotify.Clear();
    m_msgHeader.Clear();
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::USR_MOVE_INVALID_NOTIFY);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Socket Client: Get invalid human move creating msg failed"};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::USR_MOVE_INVALID_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Socket Client: Get invalid human move creating msg failed"};

    bool none{false};
    ResponseVariant noneVar= none;
    const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, noneVar);

	if(stat<0)
		throw game_except::General{"Socket Client: Invalid human move notify failed"};
};

void GomokuGameClientGUI::cpuMoveNotify(IBoard::PositionXY xy) const
{
    qInfo()<<"Socket Client: CPU move (" << xy.m_x << ", " <<xy.m_y<<")";

    m_msgNotify.Clear();
    m_msgHeader.Clear();
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::CPU_MOVE_NOTIFY);
    message::MoveXy* move1 = m_msgNotify.add_m_movies();
    move1->set_m_x(xy.m_x);
    move1->set_m_y(xy.m_y);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Socket Client: Cpu move notify msg failed"};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::CPU_MOVE_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Socket Client: Cpu move notify msg failed"};

    bool none{false};
    ResponseVariant noneVar= none;
    const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, noneVar);

	if(stat<0)
		throw game_except::General{"Socket Client: Cpu  move notify failed"};
};

void GomokuGameClientGUI::humanMoveNotify(IBoard::PositionXY xy) const
{
	//nothing to do
	qWarning()<<"humanMoveNotify() but it should as it's not handled";
};

void GomokuGameClientGUI::winnerNotify(IBoard::Player player,vector<IBoard::PositionXY> winnerMark) const
{
    qInfo()<<"Socket Client: Winner movies notify";

    m_msgNotify.Clear();
    m_msgHeader.Clear();
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::WINNER_NOTIFY);
    if(player==m_humanColor)
    	m_msgNotify.set_m_playerid(message::PlayerID::HUMAN);
    else
    	m_msgNotify.set_m_playerid(message::PlayerID::CPU);
    message::MoveXy* move1 = m_msgNotify.add_m_movies();
    message::MoveXy* move2 = m_msgNotify.add_m_movies();
    message::MoveXy* move3 = m_msgNotify.add_m_movies();
    message::MoveXy* move4 = m_msgNotify.add_m_movies();
    message::MoveXy* move5 = m_msgNotify.add_m_movies();
    move1->set_m_x(winnerMark[0].m_x);
    move1->set_m_y(winnerMark[0].m_y);
    move2->set_m_x(winnerMark[1].m_x);
    move2->set_m_y(winnerMark[1].m_y);
    move3->set_m_x(winnerMark[2].m_x);
    move3->set_m_y(winnerMark[2].m_y);
    move4->set_m_x(winnerMark[3].m_x);
    move4->set_m_y(winnerMark[3].m_y);
    move5->set_m_x(winnerMark[4].m_x);
    move5->set_m_y(winnerMark[4].m_y);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Socket Client: Winner notification creating msg failed."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::WINNER_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Socket Client: Winner notification creating msg failed."};

    bool none{false};
    ResponseVariant noneVar= none;
    const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, noneVar);

	if(stat<0)
		throw game_except::General{"Socket Client: Winner notification failed."};
};

void GomokuGameClientGUI::stalemateNotify() const
{
    qInfo()<<"Socket Client: Stalemate notify";

    m_msgNotify.Clear();
	m_msgHeader.Clear();
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::STALEMATE_NOTIFY);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Socket Client: Stalemate notification creating msg failed."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::STALEMATE_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Socket Client: Stalemate notification creating msg failed."};

    bool none{false};
    ResponseVariant noneVar= none;
    const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, noneVar);

	if(stat<0)
		throw game_except::General{"Socket Client: Stalemate notification failed."};
};
void GomokuGameClientGUI::restartGameNotify() const
{
    qInfo()<<"Socket Client: Restart game notify";

    m_msgNotify.Clear();
	m_msgHeader.Clear();

    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::RESTART_NOTIFY);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Socket Client: Restart notification creating msg failed."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::RESTART_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Socket Client: Restart notification creating msg failed."};

    bool none{false};
    ResponseVariant noneVar= none;
    const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, noneVar);

	if(stat<0)
		throw game_except::General{"Socket Client: Restart notification failed."};
};

void GomokuGameClientGUI::endGameNotify() const
{
    qInfo()<<"Socket Client: End game notify";

    m_msgNotify.Clear();
	m_msgHeader.Clear();
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::END_NOTIFY);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Socket Client: End game notification creating msg failed."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::END_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Socket Client: End game notification creating msg failed."};

    bool none{false};
    ResponseVariant noneVar= none;
    const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, noneVar);

	if(stat<0)
		throw game_except::General{"Socket Client: End game notification failed."};
};
