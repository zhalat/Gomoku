#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtGui>
#include <thread>
#include <chrono>
#include "GomokuGame.h"
#include "GomokuGameClientGUI.h"
#include "GomokuGameServerGUI.h"

void f1()
{
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

	//starts a game
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	gomokuGame.restartGame();
	gomokuGame.play();
}

void f2(int argc, char *argv[])
{
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

    app.exec();
}

void f3()
{
    GomokuGameServerGUI gomokuGameServerGUI{};
    gomokuGameServerGUI.listening();
}

int main(int argc, char *argv[])
{
	std::thread t1{f1};
	std::thread t2{f2, argc,argv};
	std::thread t3{f3};

	t1.join();
	t2.join();
	t3.join();

	std::cout << "exit!"<<std::endl;
}
