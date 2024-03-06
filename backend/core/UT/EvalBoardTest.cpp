#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include "ThreatTracker.h"
#include "Interfaces/IBoard.h"
#include "Heuristics/EvalBoard.h"
#include "Score.h"
#include "Spotter.h"

using namespace std;

struct TestMovies
{
    vector<IBoard::PositionXY> m_cpu;
    vector<IBoard::PositionXY> m_human;
    vector<IBoard::PositionXY> m_expectedMove;
};

static bool isOnTheList(const vector<IBoard::PositionXY>& vct, const IBoard::PositionXY& x)
{
    auto it = std::find_if(vct.begin(), vct.end(), [x](const IBoard::PositionXY& el)
    {
        return x == el;
    });

    return it != vct.end();
}

//---------------------------------Test: HeadShot4BC---------------------------------
class HeadShot4BCTest : public ::testing::TestWithParam< TestMovies >
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu   = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman   = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu   = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_evalBoard = make_unique<EvalBoard>();
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        m_evalBoard->setBoards(*m_board.get(),*m_trackerCpu.get(),*m_trackerHuman.get());
        SetBoard(*m_board);
    }

    void TearDown()
    {}

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;
    void SetBoard(const IBoard& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }

    // IBoard for game.
    unique_ptr<IBoard> m_board;
    unique_ptr<ISpotter> m_spotterCpu;
    unique_ptr<ISpotter> m_spotterHuman;
    unique_ptr<ThreatTracker> m_trackerCpu;
    unique_ptr<ThreatTracker> m_trackerHuman;
    unique_ptr<EvalBoard> m_evalBoard;
};

INSTANTIATE_TEST_CASE_P(
    HeadShot4BCTestParameters,
    HeadShot4BCTest,
    ::testing::Values
    (
        //set1
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . o x x x . . . . . .|
        //6 |. . . . . . . . . x . . . . .|
        //7 |. . . . . . . . . x . . . . .|
        //8 |. . . . . . . . . x . . . . .|
        //9 |. . . . . . . . . o . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(5, 6),IBoard::PositionXY(5, 7),IBoard::PositionXY(5, 8), IBoard::PositionXY(6, 9),IBoard::PositionXY(7, 9),IBoard::PositionXY(8, 9)},
            .m_human{IBoard::PositionXY(5, 5),IBoard::PositionXY(9, 9)},
            .m_expectedMove{IBoard::PositionXY(5, 9)},
        },
        //set2
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . o x x x . . . . . . .|
        //6 |. . . . . . . . . x . . . . .|
        //7 |. . . . . . . . . x . . . . .|
        //8 |. . . . . . . . . x . . . . .|
        //9 |. . . . . . . . . o . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(5, 5),IBoard::PositionXY(5, 6),IBoard::PositionXY(5, 7), IBoard::PositionXY(6, 9),IBoard::PositionXY(7, 9),IBoard::PositionXY(8, 9)},
            .m_human{IBoard::PositionXY(5, 4),IBoard::PositionXY(9, 9)},
            .m_expectedMove{IBoard::PositionXY(5, 9)},
        },
        //set3
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . o x x x . . . . . . . .|
        //6 |. . . . . . . . . x . . . . .|
        //7 |. . . . . . . . . x . . . . .|
        //8 |. . . . . . . . . x . . . . .|
        //9 |. . . . . . . . . o . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(5, 4),IBoard::PositionXY(5, 5),IBoard::PositionXY(5, 6), IBoard::PositionXY(6, 9),IBoard::PositionXY(7, 9),IBoard::PositionXY(8, 9)},
            .m_human{IBoard::PositionXY(5, 3),IBoard::PositionXY(9, 9)},
            .m_expectedMove{},

        },
        //set4
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . x . . . . . . . . . .|
        // 1 |. . . x . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . x . . . . . . . . . . .|
        // 4 |x . . . x . . . . . . . . . .|
        // 5 |. . . . . x . . . . . . . . .|
        // 6 |. . . . . . o . . . . . . . .|
        // 7 |. . . . . . . . . . . . . . .|
        // 8 |. . . . . . . . . . . . . . .|
        // 9 |. . . . . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 0),IBoard::PositionXY(1, 3),IBoard::PositionXY(0, 4), IBoard::PositionXY(3, 3),IBoard::PositionXY(4, 4),IBoard::PositionXY(5, 5)},
            .m_human{IBoard::PositionXY(6, 6)},
            .m_expectedMove{IBoard::PositionXY(2, 2)},
        },
        //set5
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . . . x x . . . . . .|
        //6 |. . . . . . . . . x . . . . .|
        //7 |. . . . . . . . . x . . . . .|
        //8 |. . . . . . . . . x . . . . .|
        //9 |. . . . . . . . . o . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(5, 7),IBoard::PositionXY(5, 8),IBoard::PositionXY(6, 9), IBoard::PositionXY(7, 9),IBoard::PositionXY(8, 9)},
            .m_human{IBoard::PositionXY(9, 9)},
            .m_expectedMove{},
        },
        //set6
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. o . . . . . . . . . . . . .|
        // 1 |. o . . . . . . . . . . . . .|
        // 2 |. o . . . . . . . . . . . . .|
        // 3 |. o . . . . . . . . . . . . .|
        // 4 |. . . . . . . . . . . . . . .|
        // 5 |. . . . . . . x x . x o . . .|
        // 6 |. . . . . . . . . x . . . . .|
        // 7 |. . . . . . . . . x . . . . .|
        // 8 |. . . . . . . . . x . . . . .|
        // 9 |. . . . . . . . . o . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. x x x x . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(11, 1),IBoard::PositionXY(11, 2),IBoard::PositionXY(11, 3), IBoard::PositionXY(11, 4),
                   IBoard::PositionXY(5, 7),IBoard::PositionXY(5, 8),IBoard::PositionXY(5, 10),IBoard::PositionXY(6, 9),IBoard::PositionXY(7, 9),IBoard::PositionXY(8, 9)},
            .m_human{IBoard::PositionXY(0, 1),IBoard::PositionXY(1, 1),IBoard::PositionXY(2, 1),IBoard::PositionXY(3, 1),
                    IBoard::PositionXY(5, 10),IBoard::PositionXY(9, 9)},
            .m_expectedMove{},
        },
        //set7
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. o x x x . . x x x o . . . .|
        // 4 |. . . . . . . . . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . . . . . . . . . . . . .|
        // 7 |. . . . . . . . . . . . . . .|
        // 8 |. . . . . . . . . . . . . . .|
        // 9 |. . . . . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(3, 2),IBoard::PositionXY(3, 3),IBoard::PositionXY(3, 4), IBoard::PositionXY(3, 7), IBoard::PositionXY(3, 8),IBoard::PositionXY(3, 9)},
            .m_human{IBoard::PositionXY(3, 1),IBoard::PositionXY(3, 10)},
            .m_expectedMove{},
        },

        //set8
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. o x x x . . . . x x x o . .|
        // 4 |. . . . . . . . . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . . . . . . . . . . . . .|
        // 7 |. . . . . . . . . . . . . . .|
        // 8 |. . . . . . . . . . . . . . .|
        // 9 |. . . . . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(3, 2),IBoard::PositionXY(3, 3),IBoard::PositionXY(3, 4), IBoard::PositionXY(3, 9), IBoard::PositionXY(3, 10),IBoard::PositionXY(3, 11)},
            .m_human{IBoard::PositionXY(3, 1),IBoard::PositionXY(3, 12)},
            .m_expectedMove{},
        },
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. o x x x . . . x x x o . . .|
        // 4 |. . . . . . . . . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . . . . . . . . . . . . .|
        // 7 |. . . . . . . . . . . . . . .|
        // 8 |. . . . . . . . . . . . . . .|
        // 9 |. . . . . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(3, 2),IBoard::PositionXY(3, 3),IBoard::PositionXY(3, 4), IBoard::PositionXY(3, 8), IBoard::PositionXY(3, 9),IBoard::PositionXY(3, 10)},
            .m_human{IBoard::PositionXY(3, 1),IBoard::PositionXY(3, 11)},
            .m_expectedMove{IBoard::PositionXY(3, 6)},
        }
    )
);

TEST_P(HeadShot4BCTest, TestName) {
    TestMovies params = GetParam();

    //cpu move
    for(auto& el : params.m_cpu)
    {
        m_board->putMove(el, m_trackerCpu->getPlayer());
        m_trackerCpu->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    //human move
    for(auto& el : params.m_human)
    {
        m_board->putMove(el, m_trackerHuman->getPlayer());
        m_trackerCpu->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    IBoard::PositionXY result;

    if(not params.m_expectedMove.empty())
    {
        ASSERT_TRUE(m_evalBoard->isHeadShot4BCPossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,result));
        ASSERT_FALSE(m_evalBoard->isHeadShot4BCPossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
    else
    {
        ASSERT_FALSE(m_evalBoard->isHeadShot4BCPossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_FALSE(m_evalBoard->isHeadShot4BCPossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
}

//---------------------------------Test: HeadShot3A---------------------------------
class HeadShot3ATest : public ::testing::TestWithParam< TestMovies >
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu   = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman   = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu   = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_evalBoard = make_unique<EvalBoard>();
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        m_evalBoard->setBoards(*m_board.get(),*m_trackerCpu.get(),*m_trackerHuman.get());
        SetBoard(*m_board);
    }

    void TearDown()
    {}

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;
    void SetBoard(const IBoard& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }

    // IBoard for game.
    unique_ptr<IBoard> m_board;
    unique_ptr<ISpotter> m_spotterCpu;
    unique_ptr<ISpotter> m_spotterHuman;
    unique_ptr<ThreatTracker> m_trackerCpu;
    unique_ptr<ThreatTracker> m_trackerHuman;
    unique_ptr<EvalBoard> m_evalBoard;
};

INSTANTIATE_TEST_CASE_P(
    HeadShot3ATestParameters,
    HeadShot3ATest,
    ::testing::Values
    (
        //set1
        //	                       1 1 1 1 1
        //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //	0 |x . . . . . . . . . . . . . .|
        //	1 |x . . . . . . . . . . . . . .|
        //	2 |x . . . . . . . . . . . . . .|
        //	3 |x . . . . . . . . . . . . . .|
        //	4 |. . . . . . . x x . . . . . .|
        //	5 |. . . . . . . . . . . . . . .|
        //	6 |. . . . . . . . . x . . . . .|
        //	7 |. . . . . . . . . x . . . . .|
        //	8 |. . . . . . . . . x . . . . .|
        //	9 |. . . . . . . . . o . . . . .|
        //	10|. . . . . . . . . . . . . . .|
        //	11|. . . . . . . . . . . . . . .|
        //	12|. . . . . . . . x x x . . . .|
        //	13|. . . . . . . . . . . . . . .|
        //	14|. . . . . . . . . . . . . . .|
        //	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(0, 0),IBoard::PositionXY(1, 0),IBoard::PositionXY(2, 0), IBoard::PositionXY(3, 0),
                   IBoard::PositionXY(4, 7),IBoard::PositionXY(4, 8),IBoard::PositionXY(6, 9), IBoard::PositionXY(7, 9),
                   IBoard::PositionXY(8, 9),IBoard::PositionXY(12, 8),IBoard::PositionXY(12, 9), IBoard::PositionXY(12, 10)},
            .m_human{IBoard::PositionXY(9, 9)},
            .m_expectedMove{IBoard::PositionXY(4, 9)},
        },
        //set2
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . x . . . . . . . . . .|
        // 1 |. x . x . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . x . . . . . . . . . . .|
        // 4 |x . . . . . . . . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . . . . . . . . . . . . .|
        // 7 |. . . . . . . . . . . . . . .|
        // 8 |. . . . . . . . . . . . . . .|
        // 9 |. . . . . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(0, 4),IBoard::PositionXY(1, 1),IBoard::PositionXY(1, 3), IBoard::PositionXY(3, 3),
                   IBoard::PositionXY(4, 0)},
            .m_human{},
            .m_expectedMove{IBoard::PositionXY(2, 2)},
        },
        //set3
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . . x x . . . . . . .|
        // 5 |. . . . . . . . . . o o o . .|
        // 6 |. . . . . . . . . x . . . . .|
        // 7 |. . . . . . . . . x . . . . .|
        // 8 |. . . . . . . . . x . . . . .|
        // 9 |. . . . . . . . . o . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 6),IBoard::PositionXY(4, 7),IBoard::PositionXY(6, 9), IBoard::PositionXY(7, 9),
                   IBoard::PositionXY(8, 9)},
            .m_human{IBoard::PositionXY(5, 10),IBoard::PositionXY(5, 11),IBoard::PositionXY(5, 12),IBoard::PositionXY(9, 9)},
            .m_expectedMove{},
        },
        //set4
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . x . . . . . . .|
        // 1 |. . . . . . . x . . . . . . .|
        // 2 |. . . . . x x . . . . . . . .|
        // 3 |. . . . . . . x . . . . . . .|
        // 4 |. . . . . . . . . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . . . . . . . . . . . . .|
        // 7 |. . . . . . . . . . . . . . .|
        // 8 |. . . . . . . . . . . . . . .|
        // 9 |. . . . . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(0, 7),IBoard::PositionXY(1, 7),IBoard::PositionXY(2, 5), IBoard::PositionXY(2, 6),
                   IBoard::PositionXY(3, 7)},
            .m_human{},
            .m_expectedMove{IBoard::PositionXY(2, 7)},
        },
        //set5
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . x . .|
        // 2 |. . . . . . . . . . . x . . .|
        // 3 |. . . . . . . . . . x . . . .|
        // 4 |. . . . . . x x . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . . . . . . . x . . . . .|
        // 7 |. . . . . . . . . x . . . . .|
        // 8 |. . . . . . . . . x . . . . .|
        // 9 |. . . . . . . . . o . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 6),IBoard::PositionXY(4, 7),IBoard::PositionXY(1, 12),IBoard::PositionXY(2, 11),
                   IBoard::PositionXY(3, 10),IBoard::PositionXY(6, 9),IBoard::PositionXY(7, 9),IBoard::PositionXY(8, 9)},
            .m_human{IBoard::PositionXY(9, 9)},
            .m_expectedMove{IBoard::PositionXY(4, 9)},
        },
        //set6
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . . . . . . . . . . .|
        // 5 |. . . . . x x . . . . . . . .|
        // 6 |. . . . . . . . . x . . . . .|
        // 7 |. . . . . . . . . x . . . . .|
        // 8 |. . . . . . . . . x . . . . .|
        // 9 |. . . . . . . . . o . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(5, 5),IBoard::PositionXY(5, 6),IBoard::PositionXY(6, 9),IBoard::PositionXY(7, 9),
                   IBoard::PositionXY(8, 9)},
            .m_human{IBoard::PositionXY(9, 9)},
            .m_expectedMove{},
        },
        //set7
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . x . x . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . . . . . . . x . . . . .|
        // 7 |. . . . . . . . . x . . . . .|
        // 8 |. . . . . . . . . x . . . . .|
        // 9 |. . . . . . . . . o . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 5),IBoard::PositionXY(4, 7),IBoard::PositionXY(6, 9),IBoard::PositionXY(7, 9),
                   IBoard::PositionXY(8, 9)},
            .m_human{IBoard::PositionXY(9, 9)},
            .m_expectedMove{},
        },
        //set8
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . . . x x . . . . . .|
        // 5 |. . . . . . . x o . o o . . .|
        // 6 |. . . . . . . . . x . . . . .|
        // 7 |. . . . . . . . . x . . . . .|
        // 8 |. . . . . . . . . x . . . . .|
        // 9 |. . . . . . . . . o . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 7),IBoard::PositionXY(4, 8),IBoard::PositionXY(5, 7),IBoard::PositionXY(6, 9),
                   IBoard::PositionXY(7, 9),IBoard::PositionXY(8, 9)},
            .m_human{IBoard::PositionXY(9, 9),IBoard::PositionXY(5, 8),IBoard::PositionXY(5, 10),IBoard::PositionXY(5, 11)},
            .m_expectedMove{IBoard::PositionXY(4, 9)},
        },
        //set9
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . x x . . . . . . . .|
        // 5 |. . . . . . . . . . x x . . .|
        // 6 |. . . . . . . . . x . . . . .|
        // 7 |. . . . . . . . . x . . . . .|
        // 8 |. . . . . . . . . x . . . . .|
        // 9 |. . . . . . . . . o . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 5),IBoard::PositionXY(4, 6),IBoard::PositionXY(5, 10),IBoard::PositionXY(5, 11),
                   IBoard::PositionXY(6, 9),IBoard::PositionXY(8, 9),IBoard::PositionXY(7, 9),},
            .m_human{IBoard::PositionXY(9, 9)},
            .m_expectedMove{IBoard::PositionXY(5, 9)},
        },
        //set10
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . o . . . .|
        // 4 |. . . . . x x . . . . . . . .|
        // 5 |. . . . . . . . o . x x . . .|
        // 6 |. . . . . . . o . x . . . . .|
        // 7 |. . . . . . . . . x . . . . .|
        // 8 |. . . . . . . . . x . . . . .|
        // 9 |. . . . . . . . . o . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 5),IBoard::PositionXY(4, 6),IBoard::PositionXY(5, 10),IBoard::PositionXY(5, 11),
                   IBoard::PositionXY(6, 9),IBoard::PositionXY(8, 9),IBoard::PositionXY(7, 9),},
            .m_human{IBoard::PositionXY(9, 9),IBoard::PositionXY(3, 10),IBoard::PositionXY(5, 8),IBoard::PositionXY(6, 7)},
            .m_expectedMove{},
        },
        //set11
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . o . .|
        // 3 |. . . . . . . . . . . o . . .|
        // 4 |. . . . . x x . . . o . . . .|
        // 5 |. . . . . . . . . . x x . . .|
        // 6 |. . . . . . . . . x . . . . .|
        // 7 |. . . . . . . . . x . . . . .|
        // 8 |. . . . . . . . . x . . . . .|
        // 9 |. . . . . . . . . o . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 5),IBoard::PositionXY(4, 6),IBoard::PositionXY(5, 10),IBoard::PositionXY(5, 11),
                   IBoard::PositionXY(6, 9),IBoard::PositionXY(8, 9),IBoard::PositionXY(7, 9),},
            .m_human{IBoard::PositionXY(9, 9),IBoard::PositionXY(4, 10),IBoard::PositionXY(3, 11),IBoard::PositionXY(2, 10)},
            .m_expectedMove{IBoard::PositionXY(5, 9)},
        },
        //set12
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . . . x x . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . . . . . . . x . . . . .|
        // 7 |. . . . . . . o . x . . . . .|
        // 8 |. . . . . . o . . x . . . . .|
        // 9 |. . . . . o . . . o . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 7),IBoard::PositionXY(4, 8),
                   IBoard::PositionXY(6, 9),IBoard::PositionXY(8, 9),IBoard::PositionXY(7, 9),},
            .m_human{IBoard::PositionXY(9, 9),IBoard::PositionXY(9, 5),IBoard::PositionXY(8, 6),IBoard::PositionXY(7, 7)},
            .m_expectedMove{IBoard::PositionXY(4, 9)},
        },
        //set13
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . x . . . . . . .|
        // 4 |. . . . . . . x . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . x . x . x . . . . . . . .|
        // 7 |. . . . . . . . . . . . . . .|
        // 8 |. . . . . . . . . . . . . . .|
        // 9 |. . . . . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(3, 7),IBoard::PositionXY(4, 7),IBoard::PositionXY(6, 2),IBoard::PositionXY(6, 4),IBoard::PositionXY(6, 6),},
            .m_human{},
            .m_expectedMove{},
        },
        //set14
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . . . . . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . o x x x . . . x x . . . .|
        // 7 |. . . . . . . . . . . . . . .|
        // 8 |. . . . . . . . . . . . . . .|
        // 9 |. . . . . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(6, 3),IBoard::PositionXY(6, 4),IBoard::PositionXY(6, 5),IBoard::PositionXY(6, 9),IBoard::PositionXY(6, 10)},
            .m_human{IBoard::PositionXY(6, 2)},
            .m_expectedMove{},
        },
        //set15
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . . . . . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . x . x . x . x x . . . .|
        // 7 |. . . . . . . . . . . . . . .|
        // 8 |. . . . . . . . . . . . . . .|
        // 9 |. . . . . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(6, 3),IBoard::PositionXY(6, 5),IBoard::PositionXY(6, 7),IBoard::PositionXY(6, 9),IBoard::PositionXY(6, 10)},
            .m_human{},
            .m_expectedMove{},
        }
    )
);

TEST_P(HeadShot3ATest, TestName) {
    TestMovies params = GetParam();

    //cpu move
    for(auto& el : params.m_cpu)
    {
        m_board->putMove(el, m_trackerCpu->getPlayer());
        m_trackerCpu->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    //human move
    for(auto& el : params.m_human)
    {
        m_board->putMove(el, m_trackerHuman->getPlayer());
        m_trackerCpu->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }
    IBoard::PositionXY result;

    if(not params.m_expectedMove.empty())
    {
        ASSERT_TRUE(m_evalBoard->isHeadShot3APossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,result));
        ASSERT_FALSE(m_evalBoard->isHeadShot3APossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
    else
    {
        ASSERT_FALSE(m_evalBoard->isHeadShot3APossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_FALSE(m_evalBoard->isHeadShot3APossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
}

//---------------------------------Test: HeadShot3AA---------------------------------
class HeadShot3AATest : public ::testing::TestWithParam<TestMovies>
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu   = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman   = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu   = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_evalBoard = make_unique<EvalBoard>();
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        m_evalBoard->setBoards(*m_board.get(),*m_trackerCpu.get(),*m_trackerHuman.get());
        SetBoard(*m_board);
    }

    void TearDown()
    {}

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;
    void SetBoard(const IBoard& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }

    // IBoard for game.
    unique_ptr<IBoard> m_board;
    unique_ptr<ISpotter> m_spotterCpu;
    unique_ptr<ISpotter> m_spotterHuman;
    unique_ptr<ThreatTracker> m_trackerCpu;
    unique_ptr<ThreatTracker> m_trackerHuman;
    unique_ptr<EvalBoard> m_evalBoard;
};

INSTANTIATE_TEST_CASE_P(
    HeadShot3AATestParameters,
    HeadShot3AATest,
    ::testing::Values
    (
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //	  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . x . . . .|
        // 3 |. . . . . . . . . x . . . . .|
        // 4 |. . . . . . x x . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . x . . . . . . . . . . .|
        // 7 |. . . x . . . . . . . . . . .|
        // 8 |. . . x . . . . . . . . . . .|
        // 9 |. . . o . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(6, 3),IBoard::PositionXY(7, 3),IBoard::PositionXY(8, 3),IBoard::PositionXY(4, 6),
                   IBoard::PositionXY(4, 7),IBoard::PositionXY(3, 9),IBoard::PositionXY(2, 10)},
            .m_human{IBoard::PositionXY(9, 3)},
            .m_expectedMove{},
        },
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //	  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . x . . . . .|
        // 3 |. . . . . . . . x . . . . . .|
        // 4 |. . . . . x x . . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . x . . . . . . . . . . .|
        // 7 |. . . x . . . . . . . . . . .|
        // 8 |. . . x . . . . . . . . . . .|
        // 9 |. . . o . . . . . . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
                .m_cpu{IBoard::PositionXY(6, 3),IBoard::PositionXY(7, 3),IBoard::PositionXY(8, 3),IBoard::PositionXY(4, 5),
                       IBoard::PositionXY(4, 6),IBoard::PositionXY(3, 8),IBoard::PositionXY(2, 9)},
                .m_human{IBoard::PositionXY(9, 3)},
                .m_expectedMove{},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . x x . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . o x . x . . . . . . . .|
        //7 |. . . . x o x . . . . . . . .|
        //8 |. . . . x . o . . . . . . . .|
        //9 |. . . . o . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(8, 4),IBoard::PositionXY(7, 4),IBoard::PositionXY(6, 4),IBoard::PositionXY(7, 6),
                   IBoard::PositionXY(6, 6),IBoard::PositionXY(4, 7),IBoard::PositionXY(4, 8)},
            .m_human{IBoard::PositionXY(9, 4),IBoard::PositionXY(7, 5) ,IBoard::PositionXY(6, 3),IBoard::PositionXY(8, 6)},
            .m_expectedMove{},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . x x . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . . x . x . . . . . . . .|
        //7 |. . . . x . x . . . . . . . .|
        //8 |. . . . o . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(7, 4),IBoard::PositionXY(6, 4),IBoard::PositionXY(7, 6),IBoard::PositionXY(6, 6),
                   IBoard::PositionXY(4, 7),IBoard::PositionXY(4, 8)},
            .m_human{IBoard::PositionXY(8, 4)},
            .m_expectedMove{},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . x . . . . . . . .|
        //3 |. . . . . . x . . . . . . . .|
        //4 |. . . . . . . x x . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . . x . . . . . . . . . .|
        //7 |. . . . x . . . . . . . . . .|
        //8 |. . . . x . . . . . . . . . .|
        //9 |. . . . o . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . x x x . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(13, 5),IBoard::PositionXY(13, 6),IBoard::PositionXY(13, 7),IBoard::PositionXY(8, 4),
                   IBoard::PositionXY(7, 4),IBoard::PositionXY(6, 4),IBoard::PositionXY(4, 7),IBoard::PositionXY(4, 8),
                   IBoard::PositionXY(3, 6),IBoard::PositionXY(2, 6)},
            .m_human{IBoard::PositionXY(9, 4)},
            .m_expectedMove{IBoard::PositionXY(4, 4)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . x . . . . . . . .|
        //3 |. . . . . . x . . . . . . . .|
        //4 |. . . . . . . x x . . . . . .|
        //5 |. . . . x . . . . . . . . . .|
        //6 |. . . . x . . . . . . . . . .|
        //7 |. . . . x . . . . . . . . . .|
        //8 |. . . . o . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(5, 4),IBoard::PositionXY(6, 4),IBoard::PositionXY(7, 4),IBoard::PositionXY(4, 7),
                   IBoard::PositionXY(4, 8),IBoard::PositionXY(3, 6),IBoard::PositionXY(2, 6)},
            .m_human{IBoard::PositionXY(8, 4)},
            .m_expectedMove{IBoard::PositionXY(4, 4)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . x . . . . . . . . . .|
        //4 |. . . . . . x . x . . . . . .|
        //5 |. . . . x . x . . . . . . . .|
        //6 |. . . . x . . . . . . . . . .|
        //7 |. . . . o . . . . . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(3, 4),IBoard::PositionXY(4, 6),IBoard::PositionXY(4, 8),IBoard::PositionXY(5, 4),
                   IBoard::PositionXY(5, 6),IBoard::PositionXY(6, 4)},
            .m_human{IBoard::PositionXY(7, 4)},
            .m_expectedMove{IBoard::PositionXY(4, 4)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . x . . . . . . . .|
        //2 |. . . . . . x . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . . . x x . . . . . .|
        //6 |. . . . x . . . . . . . . . .|
        //7 |. . . . x . . . . . . . . . .|
        //8 |. . . . x . . . . . . . . . .|
        //9 |. . . . o . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(8, 4),IBoard::PositionXY(7, 4),IBoard::PositionXY(6, 4),IBoard::PositionXY(5, 7),
                   IBoard::PositionXY(5, 8),IBoard::PositionXY(2, 6),IBoard::PositionXY(1, 6)},
            .m_human{IBoard::PositionXY(9, 4)},
            .m_expectedMove{},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . x . . . . . . . .|
        //4 |. o o o . . x . . . . . . . .|
        //5 |. . . . . . . x x . . . . . .|
        //6 |. . . . x . . . . . . . . . .|
        //7 |. . . . x . . . . . . . . . .|
        //8 |. . . . x . . . . . . . . . .|
        //9 |. . . . o . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(3, 6),IBoard::PositionXY(4, 6),IBoard::PositionXY(5, 7),IBoard::PositionXY(5, 8),
                   IBoard::PositionXY(4, 6),IBoard::PositionXY(6, 4),IBoard::PositionXY(7, 4),IBoard::PositionXY(8, 4)},
            .m_human{IBoard::PositionXY(4, 1),IBoard::PositionXY(4, 2),IBoard::PositionXY(4, 3),IBoard::PositionXY(9, 4)},
            .m_expectedMove{},
        }
    )
);

TEST_P(HeadShot3AATest, TestName) {
    TestMovies params = GetParam();

    //cpu move
    for(auto& el : params.m_cpu)
    {
        m_board->putMove(el, m_trackerCpu->getPlayer());
        m_trackerCpu->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    //human move
    for(auto& el : params.m_human)
    {
        m_board->putMove(el, m_trackerHuman->getPlayer());
        m_trackerCpu->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }
    IBoard::PositionXY result;

    if(not params.m_expectedMove.empty())
    {
        ASSERT_TRUE(m_evalBoard->isHeadShot3AAPossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,result));
        ASSERT_FALSE(m_evalBoard->isHeadShot3AAPossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
    else
    {
        ASSERT_FALSE(m_evalBoard->isHeadShot3AAPossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_FALSE(m_evalBoard->isHeadShot3AAPossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
}

//---------------------------------Test: HeadShot Dragon---------------------------------
class HeadShotDragonTest : public ::testing::TestWithParam<TestMovies>
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu   = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman   = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu   = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_evalBoard = make_unique<EvalBoard>();
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        m_evalBoard->setBoards(*m_board.get(),*m_trackerCpu.get(),*m_trackerHuman.get());
        SetBoard(*m_board);
    }

    void TearDown()
    {}

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;
    void SetBoard(const IBoard& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }

    // IBoard for game.
    unique_ptr<IBoard> m_board;
    unique_ptr<ISpotter> m_spotterCpu;
    unique_ptr<ISpotter> m_spotterHuman;
    unique_ptr<ThreatTracker> m_trackerCpu;
    unique_ptr<ThreatTracker> m_trackerHuman;
    unique_ptr<EvalBoard> m_evalBoard;
};

INSTANTIATE_TEST_CASE_P(
    HeadShotDragonTestParameters,
    HeadShotDragonTest,
    ::testing::Values
    (
        //set1
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . o . . . . . . . . . .|
        //6 |. . . . . x x o . . . . . . .|
        //7 |. . . . . o x o . . . . . . .|
        //8 |. . . . . x x x o . . . . . .|
        //9 |. . . . . . o . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(6, 5),IBoard::PositionXY(6, 6),IBoard::PositionXY(7, 6),IBoard::PositionXY(8, 5),
                   IBoard::PositionXY(8, 6),IBoard::PositionXY(8, 7)},
            .m_human{IBoard::PositionXY(5, 4),IBoard::PositionXY(6, 7),IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 7),
                     IBoard::PositionXY(8, 8),IBoard::PositionXY(9, 6)},
            .m_expectedMove{IBoard::PositionXY(5, 6),IBoard::PositionXY(8, 3)},
        },
        //set2
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . x . . . . . . . .|
        //5 |. . . . o . . . . . . . . . .|
        //6 |. . . . . x . o . . . . . . .|
        //7 |. . . . . o x o . . . . . . .|
        //8 |. . . . . x x x o . . . . . .|
        //9 |. . . . . . o . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 6),IBoard::PositionXY(6, 5),IBoard::PositionXY(7, 6),IBoard::PositionXY(8, 5),
                   IBoard::PositionXY(8, 6),IBoard::PositionXY(8, 7)},
            .m_human{IBoard::PositionXY(5, 4),IBoard::PositionXY(6, 7),IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 7),
                     IBoard::PositionXY(8, 8),IBoard::PositionXY(9, 6)},
            .m_expectedMove{IBoard::PositionXY(5, 6),IBoard::PositionXY(8, 3)},
        },
        //set3
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . o . . . . . . . .|
        //5 |. . . . . . x . . . . . . . .|
        //6 |. . . . o x x . x . . . . . .|
        //7 |. . . . o o . . . . . . . . .|
        //8 |. . . . . x . . . . . . . . .|
        //9 |. . . . . . x . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(5, 6),IBoard::PositionXY(6, 5),IBoard::PositionXY(6, 6),IBoard::PositionXY(6, 8),
                   IBoard::PositionXY(8, 5),IBoard::PositionXY(9, 6)},
            .m_human{IBoard::PositionXY(4, 6),IBoard::PositionXY(6, 4),IBoard::PositionXY(7, 4),IBoard::PositionXY(7, 5)},
            .m_expectedMove{IBoard::PositionXY(6, 7),IBoard::PositionXY(7, 6)},
        },
        //set4
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . o . . . . . . .|
        //5 |. . . . o . . . . . . . . . .|
        //6 |. . . . . x x . . . . . . . .|
        //7 |. . . . . o x o . . . . . . .|
        //8 |. . . . . x x x o . . . . . .|
        //9 |. . . . . . o . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(6, 5),IBoard::PositionXY(6, 6),IBoard::PositionXY(7, 6),IBoard::PositionXY(8, 5),
                   IBoard::PositionXY(8, 6),IBoard::PositionXY(8, 7)},
            .m_human{IBoard::PositionXY(4, 7),IBoard::PositionXY(5, 4),IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 7),
                     IBoard::PositionXY(8, 8),IBoard::PositionXY(9, 6)},
            .m_expectedMove{},
        },
        //set5
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . o o . .|
        //4 |. . . . . . . . . . . x . . .|
        //5 |. . . . . . . . . . x x . . .|
        //6 |. . . . . . o x o x o x . . .|
        //7 |. . . . . . o x x x o x . . .|
        //8 |. . . o x x x o x o x o . . .|
        //9 |. . o . . o o x x o x . . . .|
        //10|. . . . . x o o o . x . . . .|
        //11|. . . . . . . . x . o . . . .|
        //12|. . . . . . . . . o . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{ IBoard::PositionXY(7, 7),   IBoard::PositionXY(7, 9),  IBoard::PositionXY(8, 8),  IBoard::PositionXY(9, 7),
                    IBoard::PositionXY(5, 11),  IBoard::PositionXY(6, 7),  IBoard::PositionXY(9, 8),  IBoard::PositionXY(8, 6),
                    IBoard::PositionXY(10, 5),  IBoard::PositionXY(8, 10), IBoard::PositionXY(8, 5),  IBoard::PositionXY(8, 4),
                    IBoard::PositionXY(10, 10), IBoard::PositionXY(9, 10), IBoard::PositionXY(7, 8),  IBoard::PositionXY(7, 11),
                    IBoard::PositionXY(6, 11),  IBoard::PositionXY(4, 11), IBoard::PositionXY(5, 10), IBoard::PositionXY(6, 9)},
            .m_human{IBoard::PositionXY(6, 8),  IBoard::PositionXY(7, 6),   IBoard::PositionXY(6, 6),  IBoard::PositionXY(10, 6),
                     IBoard::PositionXY(6, 10), IBoard::PositionXY(8, 7),   IBoard::PositionXY(9, 6),  IBoard::PositionXY(10, 8),
                     IBoard::PositionXY(9, 9),  IBoard::PositionXY(10, 7),  IBoard::PositionXY(9, 5),  IBoard::PositionXY(8, 3),
                     IBoard::PositionXY(9, 2),  IBoard::PositionXY(11, 10), IBoard::PositionXY(8, 9),  IBoard::PositionXY(7, 10),
                     IBoard::PositionXY(8, 11), IBoard::PositionXY(11, 8), IBoard::PositionXY(3, 11),  IBoard::PositionXY(12, 9), IBoard::PositionXY(3, 12)},
            .m_expectedMove{},
        },
        //set6
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . o . . . . . . . . . . .|
        //3 |. . . o x x x . . . . . . . .|
        //4 |. . o . . o o x . . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . . . . . . . . . . . . .|
        //7 |. . . . . . . . . . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(3, 4),IBoard::PositionXY(3, 5),IBoard::PositionXY(3, 6),IBoard::PositionXY(4, 7)},
            .m_human{IBoard::PositionXY(2, 3),IBoard::PositionXY(3, 3),IBoard::PositionXY(4, 2),IBoard::PositionXY(4, 5),
                     IBoard::PositionXY(4, 6)},
            .m_expectedMove{},
        },
        //set7
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . o . . . . . x . . . . .|
        //3 |. . . o x x x o x o x . . . .|
        //4 |. . o . . o o x x o x . . . .|
        //5 |. . . . . x o o o . x . . . .|
        //6 |. . . . . . . . x . o . . . .|
        //7 |. . . . . . . . . o . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(2, 9),IBoard::PositionXY(3, 4),IBoard::PositionXY(3, 5),IBoard::PositionXY(3, 6),IBoard::PositionXY(3, 8),
                   IBoard::PositionXY(3, 10),IBoard::PositionXY(4, 7),IBoard::PositionXY(4, 8),IBoard::PositionXY(5,5) ,IBoard::PositionXY(5, 10),
                   IBoard::PositionXY(6, 8),IBoard::PositionXY(4, 10)},
            .m_human{IBoard::PositionXY(2, 3),IBoard::PositionXY(3, 3),IBoard::PositionXY(3, 9),IBoard::PositionXY(4, 2),IBoard::PositionXY(4, 5),
                     IBoard::PositionXY(4, 6),IBoard::PositionXY(4, 9),IBoard::PositionXY(5, 6),IBoard::PositionXY(5,7) ,IBoard::PositionXY(5, 8),
                     IBoard::PositionXY(6, 10),IBoard::PositionXY(7, 9),IBoard::PositionXY(3, 7)},
            .m_expectedMove{},
        },
        //set8
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . x .|
        //5 |. . . . o . . . . . . . . x .|
        //6 |. . . . . x x o . . . . . x .|
        //7 |. . . . . o x o . . . . . x .|
        //8 |. . . . . x x x o . . . . o .|
        //9 |. . . . . . o . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 13),IBoard::PositionXY(5, 13),IBoard::PositionXY(6, 13),IBoard::PositionXY(7, 13),IBoard::PositionXY(6, 5),
                   IBoard::PositionXY(6, 6),IBoard::PositionXY(7, 6),IBoard::PositionXY(8, 5),IBoard::PositionXY(8,6) ,IBoard::PositionXY(8, 7)},
            .m_human{IBoard::PositionXY(5, 4),IBoard::PositionXY(6, 7),IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 7),IBoard::PositionXY(8, 8),
                     IBoard::PositionXY(9, 6),IBoard::PositionXY(8, 13)},
            .m_expectedMove{IBoard::PositionXY(5, 6),IBoard::PositionXY(8, 3)},
        }
    )
);

TEST_P(HeadShotDragonTest, TestName) {
    TestMovies params = GetParam();

    //cpu move
    for(auto& el : params.m_cpu)
    {
        m_board->putMove(el, m_trackerCpu->getPlayer());
        m_trackerCpu->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    //human move
    for(auto& el : params.m_human)
    {
        m_board->putMove(el, m_trackerHuman->getPlayer());
        m_trackerCpu->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    IBoard::PositionXY result;

    if(not params.m_expectedMove.empty())
    {
        ASSERT_TRUE(m_evalBoard->isHeadShotDragonPossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,result));
        ASSERT_FALSE(m_evalBoard->isHeadShotDragonPossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
    else
    {
        ASSERT_FALSE(m_evalBoard->isHeadShotDragonPossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_FALSE(m_evalBoard->isHeadShotDragonPossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
}

//---------------------------------Test: HeadShot Lizard---------------------------------
class HeadShotLizardTest : public ::testing::TestWithParam<TestMovies>
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu   = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman   = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu   = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_evalBoard = make_unique<EvalBoard>();
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        m_evalBoard->setBoards(*m_board.get(),*m_trackerCpu.get(),*m_trackerHuman.get());
        SetBoard(*m_board);
    }

    void TearDown()
    {}

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;
    void SetBoard(const IBoard& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }

    // IBoard for game.
    unique_ptr<IBoard> m_board;
    unique_ptr<ISpotter> m_spotterCpu;
    unique_ptr<ISpotter> m_spotterHuman;
    unique_ptr<ThreatTracker> m_trackerCpu;
    unique_ptr<ThreatTracker> m_trackerHuman;
    unique_ptr<EvalBoard> m_evalBoard;
};

INSTANTIATE_TEST_CASE_P(
        HeadShotLizardTestParameters,
        HeadShotLizardTest,
        ::testing::Values
        (
            //set0
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . . . . . . . .|
            //3 |. . . . . . . . . . . . . . .|
            //4 |. . . . . . . . . . . . . . .|
            //5 |. . . . . . . . . . . . . . .|
            //6 |. . . . x o . . . . . . . . .|
            //7 |. . . o x x x . . . . . . . .|
            //8 |. . . . x o x . . . . . . . .|
            //9 |. . . o o . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(6, 4),IBoard::PositionXY(7, 4),IBoard::PositionXY(8, 4),IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 6),IBoard::PositionXY(8, 6)},
                .m_human{IBoard::PositionXY(6, 5),IBoard::PositionXY(7, 3),IBoard::PositionXY(8, 5),IBoard::PositionXY(9, 3),IBoard::PositionXY(9, 4)},
                .m_expectedMove{IBoard::PositionXY(4, 4),IBoard::PositionXY(7, 7)}
            },
            //set1
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . . . . . . . .|
            //3 |. . . . . . . . . . . . . . .|
            //4 |. . . . . . . o x o . . . . .|
            //5 |. . . . . . . . . . . . . . .|
            //6 |. . . . . . . . . . . . . . .|
            //7 |. . . . . . x o x o x . . . .|
            //8 |. . . . . x . . . . . x . . .|
            //9 |. . . . x . . . . . . . x . .|
            //10|. . . o . . . . . . . . . o .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(4, 8),IBoard::PositionXY(7, 6),IBoard::PositionXY(7, 8),IBoard::PositionXY(7, 10),IBoard::PositionXY(8, 5),IBoard::PositionXY(8, 11),
                       IBoard::PositionXY(9, 4),IBoard::PositionXY(9, 12)},
                .m_human{IBoard::PositionXY(4, 7),IBoard::PositionXY(4, 9),IBoard::PositionXY(7, 7),IBoard::PositionXY(7, 9),IBoard::PositionXY(10, 3),IBoard::PositionXY(10, 13),},
                .m_expectedMove{IBoard::PositionXY(6, 7),IBoard::PositionXY(6, 9)}
            },
            //set2
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . o o . . . . . . . . . .|
            //3 |. . . x o . . . . . . . . . .|
            //4 |. . . . o . . x . . . . . . .|
            //5 |. . . . . . x . . . . . . . .|
            //6 |. . . x o . . . . . . . . . .|
            //7 |. . . x . . . x x x o . . . .|
            //8 |. . . o o . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(3, 3),IBoard::PositionXY(4, 7),IBoard::PositionXY(5, 6),IBoard::PositionXY(6, 3),
                       IBoard::PositionXY(7, 3),IBoard::PositionXY(7, 7),IBoard::PositionXY(7, 8),IBoard::PositionXY(7, 9)},
                .m_human{IBoard::PositionXY(2, 3),IBoard::PositionXY(2, 4),IBoard::PositionXY(3, 4),IBoard::PositionXY(4, 4),
                         IBoard::PositionXY(6, 4),IBoard::PositionXY(8, 3),IBoard::PositionXY(8, 4),IBoard::PositionXY(7, 10),
                        IBoard::PositionXY(6, 6),IBoard::PositionXY(6, 7),IBoard::PositionXY(6, 8),IBoard::PositionXY(6, 9),IBoard::PositionXY(6, 10)},
                .m_expectedMove{}
            },
            //set3
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . o . . . . . . . . . .|
            //1 |. . . . o . . . . . . . . . .|
            //2 |. . . o o . . . . . . . . . .|
            //3 |. . . x o . . . . . . . . . .|
            //4 |. . . . o . . x . . . . . . .|
            //5 |. . . . . . x . . . . . . . .|
            //6 |. . . x o . o o o o o . . . .|
            //7 |. . . x o . . x x x o . . . .|
            //8 |. . . o o . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(3, 3),IBoard::PositionXY(4, 7),IBoard::PositionXY(5, 6),IBoard::PositionXY(6, 3),
                       IBoard::PositionXY(7, 3),IBoard::PositionXY(7, 7),IBoard::PositionXY(7, 8),IBoard::PositionXY(7, 9)},
                .m_human{IBoard::PositionXY(0, 4),IBoard::PositionXY(1, 4),IBoard::PositionXY(2, 3),IBoard::PositionXY(2, 4),IBoard::PositionXY(3, 4),IBoard::PositionXY(4, 4),
                         IBoard::PositionXY(6, 4),IBoard::PositionXY(8, 3),IBoard::PositionXY(8, 4),IBoard::PositionXY(6, 6),IBoard::PositionXY(6, 7),IBoard::PositionXY(6, 8)
                        ,IBoard::PositionXY(6, 9),IBoard::PositionXY(6, 10),IBoard::PositionXY(7, 10),IBoard::PositionXY(7, 4)},
                .m_expectedMove{}
            },
            //set4
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . . . . . . . .|
            //3 |. . . . . . . . . . . . . . .|
            //4 |. . . . . . . o . . . . . . .|
            //5 |. . . . o . . . . . . . . . .|
            //6 |. . . . . x x . . . . . . . .|
            //7 |. . . . . o x o . . . . . . .|
            //8 |. . . . . x x x o . . . . . .|
            //9 |. . . . . . o . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(6, 5),IBoard::PositionXY(6, 6),IBoard::PositionXY(7, 6),IBoard::PositionXY(8, 5),IBoard::PositionXY(8, 6),IBoard::PositionXY(8, 7)},
                .m_human{IBoard::PositionXY(4, 7),IBoard::PositionXY(5, 4),IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 7),IBoard::PositionXY(8, 8),IBoard::PositionXY(9, 6)},
                .m_expectedMove{}
            },
            //set5
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . o x x x . . . . .|
            //3 |. . . . . . . . . . . . . . .|
            //4 |. . . . . . . . . . . . . x .|
            //5 |. . . . . . . . . . . . . x .|
            //6 |. . . . x o . . . . . . . x .|
            //7 |. . . o x x x . . . . . . o .|
            //8 |. . . . x o x . . . . . . . .|
            //9 |. . . o o . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(2, 7),IBoard::PositionXY(2, 8),IBoard::PositionXY(2, 9),IBoard::PositionXY(4, 13),IBoard::PositionXY(5, 13),IBoard::PositionXY(6, 13),
                         IBoard::PositionXY(6, 4),IBoard::PositionXY(7, 4),IBoard::PositionXY(8, 4),IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 6),IBoard::PositionXY(8, 6)},
                .m_human{IBoard::PositionXY(2, 6),IBoard::PositionXY(7, 13),IBoard::PositionXY(6, 5),IBoard::PositionXY(7, 3),IBoard::PositionXY(8, 5),IBoard::PositionXY(9, 3),
                         IBoard::PositionXY(9, 4)},
                .m_expectedMove{IBoard::PositionXY(4, 4),IBoard::PositionXY(7, 7)}
            },
            //set6
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . . . . . . . .|
            //3 |. . . . . . . . . . . . . . .|
            //4 |. . . . . . . . . . . . . . .|
            //5 |. . . . . . o o . . . . . . .|
            //6 |. . . . . . . x o . . . . . .|
            //7 |. . . . . o x x x . . . . . .|
            //8 |. . . . . o . x . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(6, 7),IBoard::PositionXY(7, 7),IBoard::PositionXY(8, 7),IBoard::PositionXY(7, 6),IBoard::PositionXY(7, 8)},
                .m_human{IBoard::PositionXY(5, 6),IBoard::PositionXY(5, 7),IBoard::PositionXY(6, 8),IBoard::PositionXY(7, 5),IBoard::PositionXY(8, 5)},
                .m_expectedMove{}
            }
        )
);

TEST_P(HeadShotLizardTest, TestName) {
    TestMovies params = GetParam();

    //cpu move
    for(auto& el : params.m_cpu)
    {
        m_board->putMove(el, m_trackerCpu->getPlayer());
        m_trackerCpu->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    //human move
    for(auto& el : params.m_human)
    {
        m_board->putMove(el, m_trackerHuman->getPlayer());
        m_trackerCpu->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }
    IBoard::PositionXY result;

    if(not params.m_expectedMove.empty())
    {
        ASSERT_TRUE(m_evalBoard->isHeadShotLizardPossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,result));
        ASSERT_FALSE(m_evalBoard->isHeadShotLizardPossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
    else
    {
        ASSERT_FALSE(m_evalBoard->isHeadShotLizardPossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_FALSE(m_evalBoard->isHeadShotLizardPossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
}

//---------------------------------Test: Double3A ---------------------------------
class Double3AOneStrokeTest : public ::testing::TestWithParam<TestMovies>
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu   = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman   = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu   = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_evalBoard = make_unique<EvalBoard>();
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        m_evalBoard->setBoards(*m_board.get(),*m_trackerCpu.get(),*m_trackerHuman.get());
        SetBoard(*m_board);
    }

    void TearDown()
    {}

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;
    void SetBoard(const IBoard& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }

    // IBoard for game.
    unique_ptr<IBoard> m_board;
    unique_ptr<ISpotter> m_spotterCpu;
    unique_ptr<ISpotter> m_spotterHuman;
    unique_ptr<ThreatTracker> m_trackerCpu;
    unique_ptr<ThreatTracker> m_trackerHuman;
    unique_ptr<EvalBoard> m_evalBoard;
};

INSTANTIATE_TEST_CASE_P(
    Double3AOneStrokeTestParameters,
    Double3AOneStrokeTest,
    ::testing::Values
    (
        //set0
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . . x . x . . . . . . . .|
        //7 |. . . x . . . x . . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(7, 3),IBoard::PositionXY(6, 4),IBoard::PositionXY(6, 6),IBoard::PositionXY(7, 7)},
            .m_human{},
            .m_expectedMove{IBoard::PositionXY(5, 5)}
        },
        //set1
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . x . . . . . . . .|
        //2 |. . . . . . x . . . . . . . .|
        //3 |. . . . . . x . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . . x . . . x . . . . . .|
        //7 |. . . x . . . . . x . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(7, 3),IBoard::PositionXY(6, 4),IBoard::PositionXY(6, 8),IBoard::PositionXY(7, 9),
                     IBoard::PositionXY(1, 6),IBoard::PositionXY(2, 6),IBoard::PositionXY(3, 6)},
            .m_human{},
            .m_expectedMove{IBoard::PositionXY(4, 6)}
        },
        //set2
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |x . . . . o o o . . . . . . .|
        //1 |x . . . . . . . . . . . . . .|
        //2 |x . . . . . . . . . . . . . .|
        //3 |x . . . . . . . . . . . . . .|
        //4 |. . . . . x . . . . . . . . .|
        //5 |. . . . . . . . x . . . . . .|
        //6 |. . . x . . . . . x . . . . .|
        //7 |. . . . . . . . . . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(6, 3),IBoard::PositionXY(4, 5),IBoard::PositionXY(5, 8),IBoard::PositionXY(6, 9),
                     IBoard::PositionXY(0, 0),IBoard::PositionXY(1, 0),IBoard::PositionXY(2, 0),IBoard::PositionXY(3, 0)},
            .m_human{IBoard::PositionXY(0, 5),IBoard::PositionXY(0, 6),IBoard::PositionXY(0, 7)},
            .m_expectedMove{IBoard::PositionXY(3, 6)}
        },
        //set3
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . . x . x . . . . . .|
        //6 |. . . . . . . . . x . . . . .|
        //7 |. . . . . . . . . . . . . . .|
        //8 |. . . x . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(8, 3),IBoard::PositionXY(5, 6),IBoard::PositionXY(5, 8),IBoard::PositionXY(6, 9)},
            .m_human{},
            .m_expectedMove{}
        },
        //set4
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . o . . .|
        //4 |. . . . . . . . . . . o . . .|
        //5 |. . . . . . . . . . . o . . .|
        //6 |. . . . . . . . . . . . . . .|
        //7 |. . . . x . . . . . . . . . .|
        //8 |. . . x . . . x . . . . . . .|
        //9 |. . . . . . . . x . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(7, 4),IBoard::PositionXY(8, 3),IBoard::PositionXY(8, 7),IBoard::PositionXY(9, 8)},
            .m_human{IBoard::PositionXY(3, 11),IBoard::PositionXY(4, 11),IBoard::PositionXY(5, 11)},
            .m_expectedMove{IBoard::PositionXY(6, 5)}
        },
        //set5
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . x . . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . . . . . x . . . . . . .|
        //7 |. . . . x . . . . . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . x . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(7, 4),IBoard::PositionXY(6, 7),IBoard::PositionXY(4, 7),IBoard::PositionXY(9, 10)},
            .m_human{},
            .m_expectedMove{}
        },
        //set6
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . x . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . . x . . . . . . . .|
        //6 |. . . x . . . . . . . . . . .|
        //7 |. . . . . . . . x . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(3, 6),IBoard::PositionXY(5, 6),IBoard::PositionXY(6, 3),IBoard::PositionXY(7, 8)},
            .m_human{},
            .m_expectedMove{IBoard::PositionXY(4, 5)}
        },
        //set7
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . x . . . x . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . . x . x . . . . . . . .|
        //7 |. . . . . . . . . . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(3, 3),IBoard::PositionXY(3, 7),IBoard::PositionXY(6, 4),IBoard::PositionXY(6, 6)},
            .m_human{},
            .m_expectedMove{IBoard::PositionXY(5, 5)}
        },
        //set8
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . x . . x . . x . . . . .|
        //6 |. . . . . . . . . . . . . . .|
        //7 |. . . . . . . . . . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(5, 3),IBoard::PositionXY(5, 6),IBoard::PositionXY(5, 9)},
            .m_human{},
            .m_expectedMove{}
        }
    )
);

TEST_P(Double3AOneStrokeTest, TestName) {
    TestMovies params = GetParam();

    //cpu move
    for(auto& el : params.m_cpu)
    {
        m_board->putMove(el, m_trackerCpu->getPlayer());
        m_trackerCpu->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    //human move
    for(auto& el : params.m_human)
    {
        m_board->putMove(el, m_trackerHuman->getPlayer());
        m_trackerCpu->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }
    IBoard::PositionXY result;

    if(not params.m_expectedMove.empty())
    {
        ASSERT_TRUE(m_evalBoard->isDouble3AOneStrokePossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,result));
        ASSERT_FALSE(m_evalBoard->isDouble3AOneStrokePossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
    else
    {
        ASSERT_FALSE(m_evalBoard->isDouble3AOneStrokePossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_FALSE(m_evalBoard->isDouble3AOneStrokePossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
}

//---------------------------------Test: Double3A Mitigation---------------------------------
class Double3AMitigationTest : public ::testing::TestWithParam<TestMovies>
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu   = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman   = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu   = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_evalBoard = make_unique<EvalBoard>();
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        m_evalBoard->setBoards(*m_board.get(),*m_trackerCpu.get(),*m_trackerHuman.get());
        SetBoard(*m_board);
    }

    void TearDown()
    {}

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;
    void SetBoard(const IBoard& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }

    // IBoard for game.
    unique_ptr<IBoard> m_board;
    unique_ptr<ISpotter> m_spotterCpu;
    unique_ptr<ISpotter> m_spotterHuman;
    unique_ptr<ThreatTracker> m_trackerCpu;
    unique_ptr<ThreatTracker> m_trackerHuman;
    unique_ptr<EvalBoard> m_evalBoard;
};

INSTANTIATE_TEST_CASE_P(
    Double3AMitigationTestParameters,
    Double3AMitigationTest,
    ::testing::Values
    (
        //set0
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . . . . . x . . . . .|
        //6 |. . . . . x . . . o . . . . .|
        //7 |. . . . x . x . . o . . . . .|
        //8 |. . . x . . . x . o . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(5, 9),IBoard::PositionXY(6, 5),IBoard::PositionXY(7, 4),IBoard::PositionXY(7, 6),IBoard::PositionXY(8, 3),IBoard::PositionXY(8, 7)},
            .m_human{IBoard::PositionXY(6, 9),IBoard::PositionXY(7, 9),IBoard::PositionXY(8, 9)},
            .m_expectedMove{}
        },
        //set1
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . x o o o . . . . . . . .|
        //7 |. . . . x x . x . . . . . . .|
        //8 |. . . . . . . x . . . . . . .|
        //9 |. . . . . . . x . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(6, 3),IBoard::PositionXY(7, 4),IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 7),IBoard::PositionXY(8, 7),IBoard::PositionXY(9, 7)},
            .m_human{IBoard::PositionXY(6, 4),IBoard::PositionXY(6, 5),IBoard::PositionXY(6, 6)},
            .m_expectedMove{IBoard::PositionXY(6, 7)}
        },
        //set2
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . x . . . . . . . . . . .|
        //3 |. . . . x . . . . . . . . . .|
        //4 |. . . . . x . . . . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . x o o o . . . . . . . .|
        //7 |. . . . x x . x . . . . . . .|
        //8 |. . . . . . . x . . . . . . .|
        //9 |. . . . . . . x . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(6, 3),IBoard::PositionXY(7, 4),IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 7),IBoard::PositionXY(8, 7),IBoard::PositionXY(9, 7),
                     IBoard::PositionXY(2, 3),IBoard::PositionXY(3, 4),IBoard::PositionXY(4, 5)},
            .m_human{IBoard::PositionXY(6, 4),IBoard::PositionXY(6, 5),IBoard::PositionXY(6, 6)},
            .m_expectedMove{}
        },
        //set3
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . x . . . . . . . . . .|
        //6 |. . . . . o o o x . . . . . .|
        //7 |. . . . x . . . . . . . . . .|
        //8 |. x x . x . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(5, 4),IBoard::PositionXY(6, 8),IBoard::PositionXY(7, 4),IBoard::PositionXY(8, 1),IBoard::PositionXY(8, 2),IBoard::PositionXY(8, 4)},
            .m_human{IBoard::PositionXY(6, 5),IBoard::PositionXY(6, 6),IBoard::PositionXY(6, 7)},
            .m_expectedMove{}
        },
        //set4
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . x . x . . . . . . .|
        //6 |. . . . . . . . . . . . . . .|
        //7 |. . . . . x . x . . . . . . .|
        //8 |. . . . x . . . x . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(5, 5),IBoard::PositionXY(5, 7),IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 7),IBoard::PositionXY(8, 4),IBoard::PositionXY(8, 8)},
            .m_human{},
            .m_expectedMove{IBoard::PositionXY(6, 6)}
        },
        //set5
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . o . . . . . .|
        //1 |. . . . . . . . o . . . . . .|
        //2 |. . . . . . . . o . . . . . .|
        //3 |. . . . . . . . o . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
        //5 |. . . . . . . . . . . . . . .|
        //6 |. . . . . x . . . . . . . . .|
        //7 |. . . . x . x . . . . . . . .|
        //8 |. . . x . . . x . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(6, 5),IBoard::PositionXY(7, 4),IBoard::PositionXY(7, 6),IBoard::PositionXY(8, 3),IBoard::PositionXY(8, 7)},
            .m_human{IBoard::PositionXY(0, 8),IBoard::PositionXY(1, 8),IBoard::PositionXY(2, 8),IBoard::PositionXY(3, 8)},
            .m_expectedMove{}
        },
        //set6
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . x . . . . . . . .|
        //5 |. . . x o o . . o x . . . . .|
        //6 |. . . . . . x . x . . . . . .|
        //7 |. . . . . . x . . x . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(4, 6),IBoard::PositionXY(5, 3),IBoard::PositionXY(5, 9),IBoard::PositionXY(6, 6),IBoard::PositionXY(6, 8),
                     IBoard::PositionXY(7, 6),IBoard::PositionXY(7, 9)},
            .m_human{IBoard::PositionXY(5, 4),IBoard::PositionXY(5, 5),IBoard::PositionXY(5, 8)},
            .m_expectedMove{}
        },
        //set7
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . x . . . . . . . .|
        //5 |. . . x o o . . o x . . . . .|
        //6 |. . . . . . x . . . . . . . .|
        //7 |. . . . x x x . . . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(4, 6),IBoard::PositionXY(5, 3),IBoard::PositionXY(5, 9),IBoard::PositionXY(6, 6),IBoard::PositionXY(7, 4),
                     IBoard::PositionXY(7, 5),IBoard::PositionXY(7, 6)},
            .m_human{IBoard::PositionXY(5, 4),IBoard::PositionXY(5, 5),IBoard::PositionXY(5, 8)},
            .m_expectedMove{}
        },
        //set8
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . x . . . . . . . .|
        //5 |. . . x o o . . o x . . . . .|
        //6 |. . . . . . x . . . . . . . .|
        //7 |. . . . . . x x x . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu  {IBoard::PositionXY(4, 6),IBoard::PositionXY(5, 3),IBoard::PositionXY(5, 9),IBoard::PositionXY(6, 6),IBoard::PositionXY(7, 8),
                     IBoard::PositionXY(7, 7),IBoard::PositionXY(7, 6)},
            .m_human{IBoard::PositionXY(5, 4),IBoard::PositionXY(5, 5),IBoard::PositionXY(5, 8)},
            .m_expectedMove{IBoard::PositionXY(5, 6)}
        }
    )
);

TEST_P(Double3AMitigationTest, TestName) {
    TestMovies params = GetParam();

    //cpu move
    for(auto& el : params.m_cpu)
    {
        m_board->putMove(el, m_trackerCpu->getPlayer());
        m_trackerCpu->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    //human move
    for(auto& el : params.m_human)
    {
        m_board->putMove(el, m_trackerHuman->getPlayer());
        m_trackerCpu->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }
    IBoard::PositionXY result;

    if(not params.m_expectedMove.empty())
    {
        ASSERT_TRUE(m_evalBoard->isDouble3AMitigationPossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,result));
        ASSERT_FALSE(m_evalBoard->isDouble3AMitigationPossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
    else
    {
        ASSERT_FALSE(m_evalBoard->isDouble3AMitigationPossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_FALSE(m_evalBoard->isDouble3AMitigationPossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
}

//---------------------------------Test: BlockAndAttack3A---------------------------------
class BlockAndAttack3ATest : public ::testing::TestWithParam<TestMovies>
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu   = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman   = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu   = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_evalBoard = make_unique<EvalBoard>();
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        m_evalBoard->setBoards(*m_board.get(),*m_trackerCpu.get(),*m_trackerHuman.get());
        SetBoard(*m_board);
    }

    void TearDown()
    {}

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;
    void SetBoard(const IBoard& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }

    // IBoard for game.
    unique_ptr<IBoard> m_board;
    unique_ptr<ISpotter> m_spotterCpu;
    unique_ptr<ISpotter> m_spotterHuman;
    unique_ptr<ThreatTracker> m_trackerCpu;
    unique_ptr<ThreatTracker> m_trackerHuman;
    unique_ptr<EvalBoard> m_evalBoard;
};

INSTANTIATE_TEST_CASE_P(
        BlockAndAttack3ATestParameters,
        BlockAndAttack3ATest,
        ::testing::Values
        (
            //set 0
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . . . . . . . .|
            //3 |. . . . . . . . . . . . . . .|
            //4 |. . . . . . o . . . . . . . .|
            //5 |. . . . . o . . . . . . . . .|
            //6 |. . . . . x x x . . . . . . .|
            //7 |. . . . . . . . . . . . . . .|
            //8 |. . . . . . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(6,5),IBoard::PositionXY(6,6),IBoard::PositionXY(6,7)},
                .m_human{IBoard::PositionXY(4,6),IBoard::PositionXY(5,5)},
                .m_expectedMove{IBoard::PositionXY(6,4)}
            },
            //set 1
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . . . . . . . .|
            //3 |. . . . . . . o . . . . . . .|
            //4 |. . . . . . . . . . . . . . .|
            //5 |. . . . . o . . . . . . . . .|
            //6 |. . . . . x x x . . . . . . .|
            //7 |. . . . . . . . . . . . . . .|
            //8 |. . . . . . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(6,5),IBoard::PositionXY(6,6),IBoard::PositionXY(6,7)},
                .m_human{IBoard::PositionXY(3,7),IBoard::PositionXY(5,5)},
                .m_expectedMove{IBoard::PositionXY(6,4)}
            },
            //set 2
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . o . . . . . .|
            //3 |. . . . . . . . . . . . . . .|
            //4 |. . . . . . . . . . . . . . .|
            //5 |. . . . . o . . . . . . . . .|
            //6 |. . . . . x x x . . . . . . .|
            //7 |. . . . . . . . . . . . . . .|
            //8 |. . . . . . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(6,5),IBoard::PositionXY(6,6),IBoard::PositionXY(6,7)},
                .m_human{IBoard::PositionXY(2,8),IBoard::PositionXY(5,5)},
                .m_expectedMove{}
            },
            //set 3
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . x . . . . . .|
            //3 |. . . . . . . o . . . . . . .|
            //4 |. . . . . . o . . . . . . . .|
            //5 |. . . . . o . . . . . . . . .|
            //6 |. . . . . x x x . . . . . . .|
            //7 |. . . . . . . . . . . . . . .|
            //8 |. . . . . . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(6,5),IBoard::PositionXY(6,6),IBoard::PositionXY(6,7),IBoard::PositionXY(2,8)},
                .m_human{IBoard::PositionXY(3,7),IBoard::PositionXY(4,6),IBoard::PositionXY(5,5)},
                .m_expectedMove{IBoard::PositionXY(6,4)}
            },
            //set 4
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . o . . . . . . . . . .|
            //1 |. . x . x x . . . . . . . . .|
            //2 |. . . . . . . . . . . . . . .|
            //3 |. o . . . . . . . . . . . . .|
            //4 |o . . . . . . . . . . . . . .|
            //5 |. . . . . . . . . . . . . . .|
            //6 |. . . . . . . . . . . . . . .|
            //7 |. . . . . . . . . . . . . . .|
            //8 |. . . . . . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(1,2),IBoard::PositionXY(1,4),IBoard::PositionXY(1,5)},
                .m_human{IBoard::PositionXY(0,4),IBoard::PositionXY(3,1),IBoard::PositionXY(4,0)},
                .m_expectedMove{IBoard::PositionXY(1,3)}
            },
            //set 5
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . x . . . . . .|
            //3 |. . . . . . . . . . . . . . .|
            //4 |. . . . . o . . . . . . . . .|
            //5 |. . . . o . . . . . . . . . .|
            //6 |. . . . . x x x . . . . . . .|
            //7 |. . . . . . . . . . . . . . .|
            //8 |. . . . . . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(6,5),IBoard::PositionXY(6,6),IBoard::PositionXY(6,7)},
                .m_human{IBoard::PositionXY(4,5),IBoard::PositionXY(5,4)},
                .m_expectedMove{}
            },
            //set 6
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . x . . . . . .|
            //3 |. . . . . . . o . . . . . . .|
            //4 |. . . . . . o . . . . . . . .|
            //5 |. . . . . o . . . . . . . . .|
            //6 |. . . . . . . . . . . . . . .|
            //7 |. . . . x x x . . . . . . . .|
            //8 |. . . . . . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(7,4),IBoard::PositionXY(7,5),IBoard::PositionXY(7,6),IBoard::PositionXY(2,8)},
                .m_human{IBoard::PositionXY(3,7),IBoard::PositionXY(4,6),IBoard::PositionXY(5,5)},
                .m_expectedMove{IBoard::PositionXY(7,3)}
            },
            //set 7
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . x . . . . . .|
            //3 |. . . . . . . o . . . . . . .|
            //4 |. . . . . . o . . . . . . . .|
            //5 |. . . . . o . . . . . . . . .|
            //6 |. . . . . . . . . . . . . . .|
            //7 |. . . . x x . x . . . . . . .|
            //8 |. . . . . . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(7,4),IBoard::PositionXY(7,5),IBoard::PositionXY(7,7),IBoard::PositionXY(2,8)},
                .m_human{IBoard::PositionXY(3,7),IBoard::PositionXY(4,6),IBoard::PositionXY(5,5)},
                .m_expectedMove{IBoard::PositionXY(7,3)}
            },
            //set 8
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . .|
            //2 |. . . . . . . . x . . . . . .|
            //3 |. . . . . . . o . . . . . . .|
            //4 |. . . . . . o . . . . . x . .|
            //5 |. . . . . o . . . . . . x . .|
            //6 |. . . . . . . . . . . . x . .|
            //7 |. . . . x x . x . . . . . . .|
            //8 |. . . . . . . . . . . . . . .|
            //9 |. . . . . . . . . . . . . . .|
            //10|. . . . . . . . . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu  {IBoard::PositionXY(7,4),IBoard::PositionXY(7,5),IBoard::PositionXY(7,7),IBoard::PositionXY(2,8),
                        IBoard::PositionXY(4,12),IBoard::PositionXY(5,12),IBoard::PositionXY(6,12)},
                .m_human{IBoard::PositionXY(3,7),IBoard::PositionXY(4,6),IBoard::PositionXY(5,5)},
                .m_expectedMove{IBoard::PositionXY(7,3)}
            }
        )
);

TEST_P(BlockAndAttack3ATest, TestName) {
    TestMovies params = GetParam();

    //cpu move
    for(auto& el : params.m_cpu)
    {
        m_board->putMove(el, m_trackerCpu->getPlayer());
        m_trackerCpu->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    //human move
    for(auto& el : params.m_human)
    {
        m_board->putMove(el, m_trackerHuman->getPlayer());
        m_trackerCpu->updateScore(el, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(el, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }
    IBoard::PositionXY result;

    if(not params.m_expectedMove.empty())
    {
        ASSERT_TRUE(m_evalBoard->isBlockAndAttack3APossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,result));
        ASSERT_FALSE(m_evalBoard->isBlockAndAttack3APossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
    else
    {
        ASSERT_FALSE(m_evalBoard->isBlockAndAttack3APossible(true, result, *m_board, *m_trackerCpu, *m_trackerHuman));
        ASSERT_FALSE(m_evalBoard->isBlockAndAttack3APossible(false, result, *m_board, *m_trackerCpu, *m_trackerHuman));
    }
}