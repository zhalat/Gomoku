#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "ThreatTracker.h"
#include "Interfaces/IBoard.h"
#include "Heuristics/AlphaBeta.h"
#include "Score.h"
#include "Spotter.h"

using namespace std;

struct TestMovies
{
    vector<IBoard::PositionXY> m_cpu;
    vector<IBoard::PositionXY> m_human;
    vector<IBoard::PositionXY> m_expectedMove;
};

struct TestMovies2
{
    vector<IBoard::PositionXY> m_cpu;
    vector<IBoard::PositionXY> m_human;
    bool m_isExtraMoveCpu;
    vector<IBoard::PositionXY> m_expectedMove;
};

struct TestMovies3
{
    vector<IBoard::PositionXY> m_cpu;
    vector<IBoard::PositionXY> m_human;
    vector<unsigned int> m_depth;
    vector<IBoard::PositionXY> m_expectedMove;
};

static bool isOnTheList(const std::vector<IBoard::PositionXY>& vct1, const std::vector<IBoard::PositionXY>& vct2)
{
    if (vct1.size() != vct2.size()) {
        return false; // Different sizes, they can't be the same
    }

    // Create copies of the vectors to sort, so we don't modify the original vectors
    std::vector<IBoard::PositionXY> sortedVct1 = vct1;
    std::vector<IBoard::PositionXY> sortedVct2 = vct2;

    std::sort(sortedVct1.begin(), sortedVct1.end());
    std::sort(sortedVct2.begin(), sortedVct2.end());

    return std::equal(sortedVct1.begin(), sortedVct1.end(), sortedVct2.begin());
}

static bool isOnTheList(const vector<IBoard::PositionXY>& vct, const IBoard::PositionXY& x)
{
    auto it = std::find_if(vct.begin(), vct.end(), [x](const IBoard::PositionXY& el)
    {
        return x == el;
    });

    return it != vct.end();
}

//---------------------------------Test: Anomaly---------------------------------
class Anomaly : public ::testing::TestWithParam<TestMovies>
{
    void SetUp()
    {
        m_board     = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu   = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman   = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu   = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        SetBoard(*m_board);
        m_alphaBeta = make_unique<AlphaBeta>(k_DEFAULT_DEPTH, "AlphaBeta");
        m_alphaBeta->setStates(*m_board,*m_trackerCpu,*m_trackerHuman);
    }

    void TearDown()
    {

    }

public:
    static constexpr uint32_t k_DEFAULT_DEPTH = 3;
    static constexpr uint32_t k_BOARD_SIZE = 15;
    void SetBoard(const IBoard& rBoard)
    {
        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            Score::getInstance()->setBoard(rBoard);
        }
    }

    unique_ptr<IBoard> m_board;
    unique_ptr<ISpotter> m_spotterCpu;
    unique_ptr<ISpotter> m_spotterHuman;
    unique_ptr<ThreatTracker> m_trackerCpu;
    unique_ptr<ThreatTracker> m_trackerHuman;
    unique_ptr<AlphaBeta> m_alphaBeta;
};

INSTANTIATE_TEST_SUITE_P(
        AnomalyParameters,
        Anomaly,
        ::testing::Values
        (
//            //Anomaly description:
//            /*
//             * In provided situation, CPU (x) is next move which was (7,9).
//             * That is not best move as human has unblocked open 3-th threat.
//             * Notice: m_trackerCpu - does see it.
//             *
//             */
//            //                       1 1 1 1 1
//            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
//            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
//            //0 |. . . . . . . . . . . . . . .|
//            //1 |. . . . . . . . . . . . . . .|
//            //2 |. . . . . . . . . . . . . . .|
//            //3 |. . . . . . . . . . . . . . .|
//            //4 |. . . . . . . . . . . . . . .|
//            //5 |. . . . . . x o . . . . . . .|
//            //6 |. . . . . . o x . . . . . . .|
//            //7 |. . . . . . o x o . . . . . .|
//            //8 |. . . . . o o x . x . . . . .|
//            //9 |. . . . . . o x . x . . . . .|
//            //10|. . . . . . x o . . . . . . .|
//            //11|. . . . . . . . . . . . . . .|
//            //12|. . . . . . . . . . . . . . .|
//            //13|. . . . . . . . . . . . . . .|
//            //14|. . . . . . . . . . . . . . .|
//            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
//            TestMovies
//            {
//                    .m_cpu{IBoard::PositionXY(7, 7),IBoard::PositionXY(8, 9),IBoard::PositionXY(6, 7),IBoard::PositionXY(5, 6),
//                           IBoard::PositionXY(8, 7),IBoard::PositionXY(9, 7),IBoard::PositionXY(9, 9),IBoard::PositionXY(10, 6)},
//                    .m_human{IBoard::PositionXY(6, 6),IBoard::PositionXY(8, 6),IBoard::PositionXY(7, 6),IBoard::PositionXY(7, 8),
//                             IBoard::PositionXY(5, 7),IBoard::PositionXY(10, 7),IBoard::PositionXY(9, 6),IBoard::PositionXY(8, 5)},
//                    .m_expectedMove{IBoard::PositionXY(7, 4),IBoard::PositionXY(11, 8)},
//            },

                //Anomaly description:
                /*
                 * In provided situation, CPU (x) is next move which was (7,9).
                 * That is not best move as human has unblocked open 3-th threat.
                 * Notice: m_trackerCpu - does see it.
                 *
                 */
                //                       1 1 1 1 1
                //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
                //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
                //0 |. . . . . . . . . . . . . . .|
                //1 |. . . . . . . . . . . . . . .|
                //2 |. . . . . . . . . . . . . . .|
                //3 |. . . . . . . . . . . . . . .|
                //4 |. . . . . . . . . . . . . . .|
                //5 |. . . . . . . . . . . . . . .|
                //6 |. . . . . . . . . . . . . . .|
                //7 |. . . . . . . . . o . . . . .|
                //8 |. . . . . . . . . o o o x . .|
                //9 |. . . . . . . x o x x o . . .|
                //10|. . . . . o x x x x o . . . .|
                //11|. . . . . . . . . . . . . . .|
                //12|. . . . . . . . . . . . . . .|
                //13|. . . . . . . . . . . . . . .|
                //14|. . . . . . . . . . . . . . .|
                //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
                TestMovies
                {
                    .m_cpu{ IBoard::PositionXY(9, 9),IBoard::PositionXY(10, 8),IBoard::PositionXY(10, 9),IBoard::PositionXY(10, 7),
                            IBoard::PositionXY(10, 6),IBoard::PositionXY(9, 10),IBoard::PositionXY(8, 12),IBoard::PositionXY(9, 7)},

                    .m_human{IBoard::PositionXY(9, 8),IBoard::PositionXY(8, 10),IBoard::PositionXY(8, 9),IBoard::PositionXY(10, 10),
                             IBoard::PositionXY(10, 5),IBoard::PositionXY(8, 11),IBoard::PositionXY(9, 11),IBoard::PositionXY(7, 9)},

                    .m_expectedMove{IBoard::PositionXY(7, 4),IBoard::PositionXY(11, 8)},
                }
        )
);

TEST_P(Anomaly, TestName)
{
    TestMovies params = GetParam();
    EXPECT_EQ(params.m_cpu.size(), params.m_cpu.size());

    for(int i=0; i<params.m_cpu.size(); ++i)
    {
        const auto cpuMove= params.m_cpu[i];
        const auto humanMove= params.m_human[i];

        m_board->putMove(cpuMove, m_trackerCpu->getPlayer());
        m_trackerCpu->updateScore(cpuMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerHuman->updateScore(cpuMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

        cout<<*m_board<<endl;
        cout<<*m_trackerCpu<<endl;
        cout<<*m_trackerHuman<<endl;

        m_board->putMove(humanMove, m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(humanMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(humanMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

        cout<<*m_board<<endl;
        cout<<*m_trackerCpu<<endl;
        cout<<*m_trackerHuman<<endl;
    }

    //Now findBestMove.
    const uint32_t maxCandidatesNumber = 20U;
    ISearchTree::PriorityQueueScore nBestMove{maxCandidatesNumber};
    m_alphaBeta->setStates(*m_board, *m_trackerCpu, *m_trackerHuman);
    m_alphaBeta->setDepth(1);

    m_alphaBeta->setInitialPlayer( m_trackerCpu->getPlayer());
    IBoard::PositionXY best = m_alphaBeta->findBestMove(nBestMove);


    cout<<*m_board<<endl;
    cout<<*m_trackerCpu<<endl;
    cout<<*m_trackerHuman<<endl;

    cout<<best<<endl;

    //ASSERT_TRUE(isOnTheList(params.m_expectedMove, best));
}

