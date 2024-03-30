#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtGui>
#include <QQmlContext>
#include <thread>
#include <chrono>
#include "GomokuGame.h"
#include "GomokuGameClientGUI.h"
#include "GomokuGameServerGUI.h"

void f1(GomokuGame& gomokuGame)
{
    //starts a game
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    gomokuGame.restartGame();
    gomokuGame.play();
}

void f2(GomokuGameServerGUI& gomokuGameServerGUI)
{
    //Interacts with GUI. GUI->Backend & GUI<-Backend
    //gets query from  backend
    gomokuGameServerGUI.listening();
}

int main(int argc, char *argv[])
{
	//-------backend----------------------
    unsigned boardSize{19};
    std::string player{"o"};
    unsigned level{2};
    unsigned timeLimit{0};

    GomokuGameClientGUI gomokuGameClientGUI{IBoard::String2Player(player.c_str())};
    GomokuGame gomokuGame{ boardSize,
                           IBoard::String2Player(player.c_str()),
                           static_cast<IGame::Level>(level),
                           true,
                           timeLimit,
                           gomokuGameClientGUI };
    gomokuGameClientGUI.setBoard(gomokuGame.getBoard());

	//-------intermediate(sockets)----------------------
    GomokuGameServerGUI gomokuGameServerGUI{};

    //-------frontend (GUI QT)----------------------
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/GomokuGui/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);
    engine.rootContext()->setContextProperty( "gomokuGameServerGUI", &gomokuGameServerGUI );

	//-------Threads----------------------
    std::thread t1{f1, std::ref(gomokuGame)};
    std::thread t2{f2, std::ref(gomokuGameServerGUI)};
    app.exec();
    t1.join();
    t2.join();

    std::cout << "exit!"<<std::endl;
}
