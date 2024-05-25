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
#include <QString>
#include <QTimer>
#include <QVariantList>
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

    //GUI->backend (can be invoked in .qml)
    Q_INVOKABLE void frontend_board_restarted();
    Q_INVOKABLE void frontend_human_move(int humanX, int humanY);
    Q_INVOKABLE void frontend_is_play_again(int answer);

signals:
	//backend->GUI (can be send to .qml)
    void backendevent_restart(); 											//emits at startup
    void backendevent_human_won(const QVariantList& positions); 			//emits when human won
    void backendevent_cpu_won(const QVariantList& positions);   			//emits when cpu won
    void backendevent_stalemate();											//emits when stalemate
    void backendevent_cpu_move(const int cpuRow, const int cpuColumn);		//emits when cpu puts new move
    void backendevent_human_move_invalid();									//emits when human puts invalid new move
    void backendevent_is_play_again();                                      //emits when game is  end to decide if play again

private:
    static constexpr auto k_SOCKET_GUI_NAME = "/tmp/GomokuGuiSocket";
    static constexpr auto k_SOCKET_TYPE = AF_LOCAL;
    static constexpr IBoard::PositionXY k_XY_OUT_OF_BOARD = IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD);
    mutable message::Header m_msgHeader;
    mutable message::MsgQuery m_msgQuery;
    mutable message::MsgNotify m_msgNotify;
    mutable message::MsgAnswer m_msgAnswer;


    void doNotify(const message::MsgID id, const std::string& msgData);
    void doQuery(const message::MsgID id, const std::string& msgData, int socketId);

    //socket
    struct sockaddr_un m_sockName{};
    int m_sockMaster{-1};
    std::atomic<bool> m_isRunning{true};
    int m_msgHeadSize{-1};

    //data GUI->Backend, helper data
    std::atomic<bool> m_isNewHumanMove{false};
    IBoard::PositionXY m_lastHumanMove{k_XY_OUT_OF_BOARD};
    std::atomic<bool> m_isNewHumanDecisionPlayOrStop{false};
    int m_playOrStop{-1};
};

