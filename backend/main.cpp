#include <boost/program_options.hpp>
#include <ctime>
#include <cstdlib>
#include "Exceptions.h"
#include "GomokuBoard.h"
#include "GomokuGame.h"
#include <iostream>

namespace po = boost::program_options;

static void validateSize(unsigned x);
static void validatePlayer(std::string x);
static void validateLevel(unsigned x);
static void validateTime(int x);

int main(int argc, char * argv[])
{
    srand(time(NULL));

    unsigned boardSize{};
    std::string player{};
    unsigned level{};
    int timeLimit{};

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Produce help message. Example: '-s 15 -p x -l 2 -t 0'.")
        ("size,s", po::value<unsigned>(&boardSize)->default_value(15)->notifier(validateSize), "set board size. Min/max <5,15>.")
        ("player,p", po::value<std::string>(&player)->default_value("x")->notifier(validatePlayer), "your color. 'x' or 'o'. Player 'x' starts.")
        ("level,l", po::value<unsigned>(&level)->default_value(2)->notifier(validateLevel), "game difficulties. 1,2,3. The higher the cpu stronger")
        ("time,t", po::value<int>(&timeLimit)->default_value(0)->notifier(validateTime), "time limitation [s] for cpu. 0 means no limit");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
        std::cout<<desc<<std::endl;
        return 0;
    }

    GomokuGame GomokuGame{};
    GomokuGame.init( boardSize,
                     IBoard::String2Player(player.c_str()),
                     static_cast<IGame::Level>(level),
                     true,
                     timeLimit,
                     std::cin,
                     std::cout);
    GomokuGame.play();

    return 0;
}

void validateSize(unsigned x)
{
    if((x < GomokuBoard::k_MIN_GOMOKU_BOARD_SIZE) or (x > GomokuBoard::k_MAX_GOMOKU_BOARD_SIZE))
    {
        cout<<"error validateSize"<<endl;
        throw game_except::General{"Invalid parameter -s: Board size ouf scope. See help"};
    }
}

void validatePlayer(std::string x)
{
    if(IBoard::PLAYER_A != IBoard::String2Player(x.c_str()) and IBoard::PLAYER_B != IBoard::String2Player(x.c_str()))
    {
        cout<<"error validatePlayer"<<endl;
        throw game_except::General{"Invalid parameter -p: Can not convert string into player pawn. See help"};
    }
}

void validateLevel(unsigned x)
{
    if( !static_cast<IGame::Level>(x<IGame::Level::LEVEL_LAST) )
    {
        cout<<"error validateLevel"<<endl;
        throw game_except::General{"Invalid parameter -l: Game level out of scope. See help"};
    }
}

void validateTime(int x)
{
    if( x!=0 and x>100 )
    {
        cout<<"error validateTime"<<endl;
        throw game_except::General{"Invalid parameter -t: Time limit. See help"};
    }
}