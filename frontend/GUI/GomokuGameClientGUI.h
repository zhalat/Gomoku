#pragma once
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <thread>
#include "Interfaces/IGame.h"
#include "protobuf/messages.pb.h"


class GomokuGameClientGUI final : public IGameInteraction
{
public:
    GomokuGameClientGUI(IBoard::Player humanColor);
    GomokuGameClientGUI(const GomokuGameClientGUI&) = delete;
    GomokuGameClientGUI(GomokuGameClientGUI&&) = delete;
    GomokuGameClientGUI& operator=(const GomokuGameClientGUI&) = delete;
    GomokuGameClientGUI& operator=(GomokuGameClientGUI&&) = delete;
    virtual ~GomokuGameClientGUI() = default;

    void setBoard(IBoard* board)
    {
        assert(board);
        m_board = board;
    }

private:
    static constexpr auto k_SOCKET_GUI_NAME = "/tmp/GomokuGuiSocket";
    static constexpr auto k_SOCKET_TYPE = AF_LOCAL;
    static constexpr IBoard::PositionXY k_XY_OUT_OF_BOARD = IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD);
    mutable message::Header m_msgHeader;
    mutable message::MsgQuery m_msgQuery;
    mutable message::MsgNotify m_msgNotify;

    IBoard::PositionXY getUserMove() const override;
    bool getIsPlayAgain() const override;
    void invalidUserMoveNotify() const override;
    void cpuMoveNotify(IBoard::PositionXY xy) const override;
    void humanMoveNotify(IBoard::PositionXY xy) const override;
    void winnerNotify(IBoard::Player player,vector<IBoard::PositionXY> winnerMark) const override;
    void stalemateNotify() const override;
    void restartGameNotify() const override;
    void endGameNotify() const override;

    IBoard* m_board{nullptr};
    const IBoard::Player m_humanColor{};

    //socket
    struct sockaddr_un m_sockName{};

    //send data over a socket.
    //header&data consist message.
    //wantResp- set to true if you expect response. False otherwise.
    //resp - container for data server response.
    template<class T>
    int sendMsgToServer(const std::string header, const std::string data, bool wantResp, T resp) const
    {
        int stat{-1};
        int sockData{-1};

        sockData = socket(k_SOCKET_TYPE, SOCK_STREAM, 0);
        stat = connect(sockData, (const struct sockaddr *)&m_sockName, sizeof(m_sockName));
        if (stat == -1)
        {
            close(sockData);
            return -1;
        }

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		cout << "Sending..."<< endl;

		ssize_t bytesSent = 0;
		bytesSent = write(sockData, header.data(), header.size());
		if(bytesSent != header.size())
		{
			close(sockData);
			return -1;
		}

		bytesSent = write(sockData, data.data(), data.size());
		if(bytesSent != data.size())
		{
			close(sockData);
			return -1;
		}

		if(wantResp)
		{

		}


    	return 0;
    }
};

