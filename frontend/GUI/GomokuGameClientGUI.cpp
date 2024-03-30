#include "Exceptions.h"
#include "GomokuGameClientGUI.h"

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
		throw game_except::General{"Message data query serialization error."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::USR_MOVE_QUERY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Message header query serialization error."};
    while(1)
    {

         std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
	IBoard::PositionXY resp;
	const int stat = sendMsgToServer(serializedHeader, serializedMessage, true, resp);

	if(stat<0)
		throw game_except::General{"getUserMove:: Sending data over a socket error."};


	return k_XY_OUT_OF_BOARD;
	//return resp;
}

bool GomokuGameClientGUI::getIsPlayAgain() const
{

};

void GomokuGameClientGUI::invalidUserMoveNotify() const
{
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::USR_MOVE_INVALID_NOTIFY);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Message data query serialization error."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::USR_MOVE_INVALID_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Message header query serialization error."};

	int none;
	const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, none);

	if(stat<0)
		throw game_except::General{"invalidUserMoveNotify:: Sending data over a socket error."};
};

void GomokuGameClientGUI::cpuMoveNotify(IBoard::PositionXY xy) const
{
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::CPU_MOVE_NOTIFY);
    message::MoveXy* move1 = m_msgNotify.add_m_movies();
    move1->set_m_x(xy.m_x);
    move1->set_m_y(xy.m_y);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Message data query serialization error."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::CPU_MOVE_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Message header query serialization error."};

	int none;
	const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, none);

	if(stat<0)
		throw game_except::General{"cpuMoveNotify:: Sending data over a socket error."};
};

void GomokuGameClientGUI::humanMoveNotify(IBoard::PositionXY xy) const
{

};

void GomokuGameClientGUI::winnerNotify(IBoard::Player player,vector<IBoard::PositionXY> winnerMark) const
{
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::WINNER_NOTIFY);
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
		throw game_except::General{"Message data query serialization error."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::WINNER_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Message header query serialization error."};

	int none;
	const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, none);

	if(stat<0)
		throw game_except::General{"SwinnerNotify:: Sending data over a socket error."};
};

void GomokuGameClientGUI::stalemateNotify() const
{
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::STALEMATE_NOTIFY);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Message data query serialization error."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::STALEMATE_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Message header query serialization error."};

	int none;
	const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, none);

	if(stat<0)
		throw game_except::General{"stalemateNotify:: Sending data over a socket error."};
};
void GomokuGameClientGUI::restartGameNotify() const
{
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::RESTART_NOTIFY);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Message data query serialization error."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::RESTART_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Message header query serialization error."};

	int none;
	const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, none);

	if(stat<0)
		throw game_except::General{"restartGameNotify:: Sending data over a socket error."};
};

void GomokuGameClientGUI::endGameNotify() const
{
    std::string serializedHeader;
    std::string serializedMessage;

    //data
    m_msgNotify.set_k_id(message::MsgID::END_NOTIFY);
	if(!m_msgNotify.SerializeToString(&serializedMessage))
		throw game_except::General{"Message data query serialization error."};

	//header
	m_msgHeader.set_m_msgid(message::MsgID::END_NOTIFY);
	m_msgHeader.set_m_msgsize(serializedMessage.size());
	if(!m_msgHeader.SerializeToString(&serializedHeader))
		throw game_except::General{"Message header query serialization error."};

	int none;
	const int stat = sendMsgToServer(serializedHeader, serializedMessage, false, none);

	if(stat<0)
		throw game_except::General{"endGameNotify:: Sending data over a socket error."};
};
