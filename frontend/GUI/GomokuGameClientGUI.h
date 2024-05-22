#pragma once
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <QDebug>
#include "Exceptions.h"
#include "Interfaces/IGame.h"
#include "protobuf/messages.pb.h"

class GomokuGameClientGUI final : public IGameInteraction
{
public:
    using ResponseVariant = std::variant<IBoard::PositionXY, bool>;
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
    mutable message::MsgAnswer m_msgAnswer;

    IBoard::PositionXY getUserMove() const override;
    bool getIsPlayAgain()  override;
    void invalidUserMoveNotify() const override;
    void cpuMoveNotify(IBoard::PositionXY xy) const override;
    void humanMoveNotify(IBoard::PositionXY xy) const override;
    void winnerNotify(IBoard::Player player,vector<IBoard::PositionXY> winnerMark) const override;
    void stalemateNotify() const override;
    void restartGameNotify() const override;
    void endGameNotify() const override;

    IBoard* m_board{nullptr};
    IBoard::Player m_humanColor{};

    //socket
    struct sockaddr_un m_sockName{};

    //send data over a socket.
    //header&data consist message.
    //wantResp- set to true if you expect response. False otherwise.
    //resp - container for data server response.
    template<class T>
    int sendMsgToServer(const std::string header, const std::string data, bool wantResp, T& resp) const
    {
         int stat{-1};
         int sockData{-1};
         const auto headSize = getMessageSize(m_msgHeader);

         qInfo() << "Socket client: Connecting  to " << k_SOCKET_GUI_NAME;
         sockData = socket(k_SOCKET_TYPE, SOCK_STREAM, 0);
         stat = connect(sockData, (const struct sockaddr *)&m_sockName, sizeof(m_sockName));
         if (stat == -1)
         {
        	 qCritical() << "Connection failed";
             close(sockData);
             return -1;
         }

         std::this_thread::sleep_for(std::chrono::milliseconds(20));

         qDebug() << "Socket Client: sending header";
         ssize_t bytesSent = 0;
         bytesSent = write(sockData, header.data(), headSize);
         if(bytesSent != headSize)
         {
        	 qCritical() << "Sending header failed";
            close(sockData);
            return -2;
         }

         qDebug() << "Socket Client: sending data";
         bytesSent = write(sockData, data.data(), data.size());
         if(bytesSent != data.size())
         {
        	 qCritical() << "Sending data failed";
            close(sockData);
            return -3;
         }

         if(wantResp)
         {
        	 qInfo() << "Socket Client: Waiting for response...";

            //1.read msg header
            std::string receivedHeaderMessage(headSize,'\0');
            ssize_t bytesRead = read(sockData, &receivedHeaderMessage[0], headSize);
            qDebug() << "Socket Client: Got response header";
            if(bytesRead!=headSize)
            {
            	qCritical() << "Socket Client: Invalid header size. Has been split?";
                close(sockData);
                return -4;
            }

             if(not m_msgHeader.ParseFromString(receivedHeaderMessage))
             {
             	qCritical() << "Socket Client: Can not parse header";
                close(sockData);
                return -5;
             }

             const uint32_t length = m_msgHeader.m_msgsize();
             const uint32_t id = m_msgHeader.m_msgid();
    		 qDebug() << "Socket Client answer: Msg ID:" << id;
    		 qDebug() << "Socket Client answer: Msg size:" << length;

             if(id >= message::MsgID::KEEP_ME_LAST)
             {
            	 qCritical() << "Socket Client: Got invalid header ID";
                close(sockData);
                return -6;
             }

             //2.read msg data
             std::string receivedMessage(length,'\0');
             bytesRead = read(sockData, &receivedMessage[0], length);
             qDebug() << "Socket Client: Got response data";
            if(bytesRead!=length)
            {
            	qCritical() << "Socket Client: Invalid header size. Has been split?";
                close(sockData);
                return -7;
            }

            if(id == message::MsgID::USR_MOVE_ANSWER)
            {
                if(m_msgAnswer.ParseFromString(receivedMessage))
                {
                    if (std::holds_alternative<IBoard::PositionXY>(resp))
                    {
                        auto& moveResp = std::get<IBoard::PositionXY>(resp);
                        moveResp.m_x = m_msgAnswer.m_move().m_x();
                        moveResp.m_y = m_msgAnswer.m_move().m_y();
                        qDebug() << "Socket Client: Human move ("<< moveResp.m_x<<","<< moveResp.m_y <<")";
                    }
                }
                else
                {
                	qCritical() << "Socket Client: Can not parse USR_MOVE_ANSWER message";
                }
            }
            else if(id == message::MsgID::REPLAY_ANSWER)
            {
                if(m_msgAnswer.ParseFromString(receivedMessage))
                {
                    if (std::holds_alternative<bool>(resp))
                    {
                        auto& isPlayResp = std::get<bool>(resp);
                        isPlayResp = m_msgAnswer.m_isplayagain();
                        qDebug() << "Socket Client: Is play again?: "<< (isPlayResp==true ? "yes":"no");
                    }
                }
                else
                {
                    qCritical() << "Socket Client: Can not parse REPLAY_ANSWER message";
                }
            }
            else
            {
            	qWarning() << "Socket Client: Got invalid message id:" <<id<<". Ignoring..";
            }

         }

         close(sockData);
        return 0;
    }

    template<class T>
    ssize_t getMessageSize(const T& message) const
    {
        std::string serializedMsg;
        message.SerializeToString(&serializedMsg);
        return serializedMsg.size();
    }
};

