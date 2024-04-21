#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include "ThreatTracker.h"
#include "Interfaces/IBoard.h"
#include "OpenBook.h"

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

class OpenBookTest : public ::testing::TestWithParam< TestMovies >
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(k_BOARD_SIZE);
    }

    void TearDown()
    {}

public:
    static constexpr uint32_t k_BOARD_SIZE = 15;
    unique_ptr<IBoard> m_board;
};

INSTANTIATE_TEST_SUITE_P(
        OpenBookTestParameters,
        OpenBookTest,
        ::testing::Values
        (
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            // 0 |. . . . . . . . . . . . . . .|
            // 1 |. . . . . . . . . . . . . . .|
            // 2 |. . . . . . . . . . . . . . .|
            // 3 |. . . . . . . . . . . . . . .|
            // 4 |. . . . . . A . . . . . . . .|
            // 5 |. . . . . B o C . . . . . . .|
            // 6 |. . . . D . x . E . . . . . .|
            // 7 |. . . . . . . . . . . . . . .|
            // 8 |. . . . . . F . . . . . . . .|
            // 9 |. . . . . . . . . . . . . . .|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(6, 6)},
                .m_human{IBoard::PositionXY(5, 6)},
                .m_expectedMove{IBoard::PositionXY(4, 6), IBoard::PositionXY(5, 5),
                                IBoard::PositionXY(5, 7), IBoard::PositionXY(6, 4),
                                IBoard::PositionXY(6, 8), IBoard::PositionXY(8, 6)}
            },
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            // 0 |. . . . . . . . . . . . . . .|
            // 1 |. . . . . . . . . . . . . . .|
            // 2 |. . . . . . . . . . . . . . .|
            // 3 |. . . . . . . . . . . . . . .|
            // 4 |. . . . . . D . . . . . . . .|
            // 5 |. . . . . . . B . . . . . . .|
            // 6 |. . . . F . x o A . . . . . .|
            // 7 |. . . . . . . C . . . . . . .|
            // 8 |. . . . . . E . . . . . . . .|
            // 9 |. . . . . . . . . . . . . . .|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(6, 6)},
                .m_human{IBoard::PositionXY(6, 7)},
                .m_expectedMove{IBoard::PositionXY(4, 6), IBoard::PositionXY(5, 7),
                                IBoard::PositionXY(6, 4), IBoard::PositionXY(6, 8),
                                IBoard::PositionXY(7, 7), IBoard::PositionXY(8, 6)}
            },
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            // 0 |. . . . . . . . . . . . . . .|
            // 1 |. . . . . . . . . . . . . . .|
            // 2 |. . . . . . . . . . . . . . .|
            // 3 |. . . . . . . . . . . . . . .|
            // 4 |. . . . . . F . . . . . . . .|
            // 5 |. . . . . . . . . . . . . . .|
            // 6 |. . . . E . x . D . . . . . .|
            // 7 |. . . . . C o B . . . . . . .|
            // 8 |. . . . . . A . . . . . . . .|
            // 9 |. . . . . . . . . . . . . . .|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(6, 6)},
                .m_human{IBoard::PositionXY(7, 6)},
                .m_expectedMove{IBoard::PositionXY(4, 6), IBoard::PositionXY(6, 4),
                                IBoard::PositionXY(6, 8), IBoard::PositionXY(7, 5),
                                IBoard::PositionXY(7, 7), IBoard::PositionXY(8, 6)}
            },
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            // 0 |. . . . . . . . . . . . . . .|
            // 1 |. . . . . . . . . . . . . . .|
            // 2 |. . . . . . . . . . . . . . .|
            // 3 |. . . . . . . . . . . . . . .|
            // 4 |. . . . . . E . . . . . . . .|
            // 5 |. . . . . C . . . . . . . . .|
            // 6 |. . . . A o x . F . . . . . .|
            // 7 |. . . . . B . . . . . . . . .|
            // 8 |. . . . . . D . . . . . . . .|
            // 9 |. . . . . . . . . . . . . . .|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(6, 6)},
                .m_human{IBoard::PositionXY(6, 5)},
                .m_expectedMove{IBoard::PositionXY(4, 6), IBoard::PositionXY(5, 5),
                                IBoard::PositionXY(6, 4), IBoard::PositionXY(6, 8),
                                IBoard::PositionXY(7, 5), IBoard::PositionXY(8, 6)}
            },
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            // 0 |. . . . . . . . . . . . . . .|
            // 1 |. . . . . . . . . . . . . . .|
            // 2 |. . . . . . . . . . . . . . .|
            // 3 |. . . . . . . . . . . . . . .|
            // 4 |. . . . . G H . . . . . . . .|
            // 5 |. . . . . I . o . . . . . . .|
            // 6 |. . . . . . x . J . . . . . .|
            // 7 |. . . . M . . K L . . . . . .|
            // 8 |. . . . . N . . . . . . . . .|
            // 9 |. . . . . . . . . . . . . . .|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(6, 6)},
                .m_human{IBoard::PositionXY(5, 7)},
                .m_expectedMove{IBoard::PositionXY(4, 5), IBoard::PositionXY(4, 6), IBoard::PositionXY(5, 5), IBoard::PositionXY(6, 8),
                                IBoard::PositionXY(7, 4), IBoard::PositionXY(7, 7), IBoard::PositionXY(7, 8), IBoard::PositionXY(8, 5)}
            },
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            // 0 |. . . . . . . . . . . . . . .|
            // 1 |. . . . . . . . . . . . . . .|
            // 2 |. . . . . . . . . . . . . . .|
            // 3 |. . . . . . . . . . . . . . .|
            // 4 |. . . . . M . . . . . . . . .|
            // 5 |. . . . N . . I G . . . . . .|
            // 6 |. . . . . . x . H . . . . . .|
            // 7 |. . . . . K . o . . . . . . .|
            // 8 |. . . . . L J . . . . . . . .|
            // 9 |. . . . . . . . . . . . . . .|
            TestMovies
            {
                    .m_cpu{IBoard::PositionXY(6, 6)},
                    .m_human{IBoard::PositionXY(7, 7)},
                    .m_expectedMove{IBoard::PositionXY(4, 5), IBoard::PositionXY(5, 4), IBoard::PositionXY(5, 7), IBoard::PositionXY(5, 8),
                                    IBoard::PositionXY(6, 8), IBoard::PositionXY(7, 5), IBoard::PositionXY(8, 5), IBoard::PositionXY(8, 6)}
            },
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            // 0 |. . . . . . . . . . . . . . .|
            // 1 |. . . . . . . . . . . . . . .|
            // 2 |. . . . . . . . . . . . . . .|
            // 3 |. . . . . . . . . . . . . . .|
            // 4 |. . . . . . . N . . . . . . .|
            // 5 |. . . . L K . . M . . . . . .|
            // 6 |. . . . J . x . . . . . . . .|
            // 7 |. . . . . o . I . . . . . . .|
            // 8 |. . . . . . H G . . . . . . .|
            // 9 |. . . . . . . . . . . . . . .|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(6, 6)},
                .m_human{IBoard::PositionXY(7, 5)},
                .m_expectedMove{IBoard::PositionXY(4, 7), IBoard::PositionXY(5, 8), IBoard::PositionXY(5, 4), IBoard::PositionXY(5, 5),
                                IBoard::PositionXY(6, 4), IBoard::PositionXY(7, 7), IBoard::PositionXY(8, 6), IBoard::PositionXY(8, 7)}
            },
            //                       1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            // 0 |. . . . . . . . . . . . . . .|
            // 1 |. . . . . . . . . . . . . . .|
            // 2 |. . . . . . . . . . . . . . .|
            // 3 |. . . . . . . . . . . . . . .|
            // 4 |. . . . . . J L . . . . . . .|
            // 5 |. . . . . o . K . . . . . . .|
            // 6 |. . . . H . x . . . . . . . .|
            // 7 |. . . . G I . . N . . . . . .|
            // 8 |. . . . . . . M . . . . . . .|
            // 9 |. . . . . . . . . . . . . . .|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(6, 6)},
                .m_human{IBoard::PositionXY(5, 5)},
                .m_expectedMove{IBoard::PositionXY(4, 6), IBoard::PositionXY(4, 7), IBoard::PositionXY(5, 7), IBoard::PositionXY(6, 4),
                                IBoard::PositionXY(7, 4), IBoard::PositionXY(7, 5), IBoard::PositionXY(7, 8), IBoard::PositionXY(8, 7)}
            }
        )
);

TEST_P(OpenBookTest, TestName) {
    TestMovies params = GetParam();

    //cpu move
    for(auto& el : params.m_cpu)
    {
        m_board->putMove(el, IBoard::Player::PLAYER_A);
    }

    //human move
    for(auto& el : params.m_human)
    {
        m_board->putMove(el, IBoard::Player::PLAYER_B);
    }

    if(not params.m_expectedMove.empty())
    {
        const uint32_t maxSamples = 100;
        for(uint32_t i = 0; i < maxSamples; ++i)
        {
            const IBoard::PositionXY xyOpening = OpenBook::getBestThirdWhiteMove(*m_board);
            ASSERT_TRUE(isOnTheList(params.m_expectedMove, xyOpening));
        }
    }
    else
    {
        ASSERT_TRUE(false);
    }
}