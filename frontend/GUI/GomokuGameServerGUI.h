#pragma once
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <atomic>
#include <QObject>
#include <QTimer>
#include <QVariant>
//#include <QSoundEffect>
#include "Interfaces/IGame.h"
#include "protobuf/messages.pb.h"


class GomokuGameServerGUI : public QObject
{
    Q_OBJECT

public:
    GomokuGameServerGUI();
    GomokuGameServerGUI(const GomokuGameServerGUI&) = delete;
    GomokuGameServerGUI(GomokuGameServerGUI&&) = delete;
    GomokuGameServerGUI& operator=(const GomokuGameServerGUI&) = delete;
    GomokuGameServerGUI& operator=(GomokuGameServerGUI&&) = delete;
    virtual ~GomokuGameServerGUI() = default;
    void listening();

private:
    static constexpr auto k_SOCKET_GUI_NAME = "/tmp/GomokuGuiSocket";
    static constexpr auto k_SOCKET_TYPE = AF_LOCAL;
    static constexpr IBoard::PositionXY k_XY_OUT_OF_BOARD = IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD);
    mutable message::Header m_msgHeader;
    mutable message::MsgQuery m_msgQuery;
    mutable message::MsgNotify m_msgNotify;

    //socket
    struct sockaddr_un m_sockName{};
    int m_sockMaster{-1};
    std::atomic<bool> m_isRunning{true};
    int m_msgHeadSize{-1};
};

