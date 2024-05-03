#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "ThreatTracker.h"
#include "Interfaces/IBoard.h"
#include "Heuristics/AlphaBeta.h"
#include "Heuristics/MinMax.h"
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

//---------------------------------Test: Anomaly single alpha or minmax---------------------------------
class AnomalyRealGame : public ::testing::TestWithParam<TestMovies>
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
        m_minMax = make_unique<MinMax>(k_DEFAULT_DEPTH, "MinMax");

        m_alphaBeta->setStates(*m_board,*m_trackerCpu,*m_trackerHuman);
        m_minMax->setStates(*m_board,*m_trackerCpu,*m_trackerHuman);
    }

    void TearDown()
    {

    }

public:
    static constexpr uint32_t k_DEFAULT_DEPTH = 3;
    static constexpr uint32_t k_BOARD_SIZE = 19;
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
    unique_ptr<MinMax> m_minMax;
};

INSTANTIATE_TEST_SUITE_P(
        AnomalyParameters,
        AnomalyRealGame,
        ::testing::Values
        (
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
            //5 |. . . . . . x o . . . . . . .|
            //6 |. . . . . . o x . . . . . . .|
            //7 |. . . . . . o x o . . . . . .|
            //8 |. . . . . o o x . x . . . . .|
            //9 |. . . . . . o x . x . . . . .|
            //10|. . . . . . x o . . . . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu{IBoard::PositionXY(7, 7),IBoard::PositionXY(8, 9),IBoard::PositionXY(6, 7),IBoard::PositionXY(5, 6),
                       IBoard::PositionXY(8, 7),IBoard::PositionXY(9, 7),IBoard::PositionXY(9, 9),IBoard::PositionXY(10, 6)},
                .m_human{IBoard::PositionXY(6, 6),IBoard::PositionXY(8, 6),IBoard::PositionXY(7, 6),IBoard::PositionXY(7, 8),
                         IBoard::PositionXY(5, 7),IBoard::PositionXY(10, 7),IBoard::PositionXY(9, 6),IBoard::PositionXY(8, 5)},
                .m_expectedMove{IBoard::PositionXY(7, 4),IBoard::PositionXY(11, 8)},
            },
            //Anomaly description:
            /*
             * In provided situation, CPU (x) is next move which was (9,7).
             * This is trap as then Human(7,9),Cpu(6,8), Human(7,8)- do you see two deadly threats? double 3 and (7,11)
             * and dragon (8,7). This anomaly is not deviation. Its because depth was set to 3 which is too shallow.
             * Depth 5 should solve the issue.
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
            //7 |. . . . . . . . . . . . . . .|
            //8 |. . . . . . . . . o o o x . .|
            //9 |. . . . . . . . o x x o . . .|
            //10|. . . . . o x x x x o . . . .|
            //11|. . . . . . . . . . . . . . .|
            //12|. . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu{ IBoard::PositionXY(9, 9),IBoard::PositionXY(10, 8),IBoard::PositionXY(10, 9),IBoard::PositionXY(10, 7),
                        IBoard::PositionXY(10, 6),IBoard::PositionXY(9, 10),IBoard::PositionXY(8, 12)},
                .m_human{IBoard::PositionXY(9, 8),IBoard::PositionXY(8, 10),IBoard::PositionXY(8, 9),IBoard::PositionXY(10, 10),
                         IBoard::PositionXY(10, 5),IBoard::PositionXY(8, 11),IBoard::PositionXY(9, 11)},
                .m_expectedMove{IBoard::PositionXY(7, 11),IBoard::PositionXY(6, 11),IBoard::PositionXY(7, 9)},
            },
            //Anomaly description:
            /* CPU started. CPU ('x'). Next move is for 'x':
             * In provided situation, CPU (x) had winning situation but couldn't finish it.
             * It put (11, 12) while the best is (9,10)
             *
             */
            //                       1 1 1 1 1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . . . . . .|
            //2 |. . . . . . . . . . . . . . . . . . .|
            //3 |. . . . . . . . . . . . . . . . . . .|
            //4 |. . . . . . . . . . . . . . . . . . .|
            //5 |. . . . . . . . . . . . . . . . . . .|
            //6 |. . . . . . . . . o . . . . . . . . .|
            //7 |. . . . . . . . x x o . . . . . . . .|
            //8 |. . . . . . . . o x o . . . . . . . .|
            //9 |. . . . . . . o x x . . . . . . . . .|
            //10|. . . . . . . . o x x x o . . . . . .|
            //11|. . . . . . . . . o o x . . . . . . .|
            //12|. . . . . . . . . . x x o . . . . . .|
            //13|. . . . . . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . . . . . .|
            //15|. . . . . . . . . . . . . . . . . . .|
            //16|. . . . . . . . . . . . . . . . . . .|
            //17|. . . . . . . . . . . . . . . . . . .|
            //18|. . . . . . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu{ IBoard::PositionXY(8, 9),IBoard::PositionXY(9, 9),IBoard::PositionXY(10, 9),IBoard::PositionXY(10, 10),
                        IBoard::PositionXY(9, 8),IBoard::PositionXY(12, 10),IBoard::PositionXY(7, 9),IBoard::PositionXY(11, 11),
                        IBoard::PositionXY(7, 8),IBoard::PositionXY(12, 11),IBoard::PositionXY(10, 11)},
                .m_human{ IBoard::PositionXY(8, 8),IBoard::PositionXY(8, 10),IBoard::PositionXY(10, 8),IBoard::PositionXY(11, 9),
                          IBoard::PositionXY(9, 7),IBoard::PositionXY(11, 10),IBoard::PositionXY(6, 9),IBoard::PositionXY(10, 12),
                          IBoard::PositionXY(7, 10),IBoard::PositionXY(12, 12),IBoard::PositionXY(9, 11)},
                .m_expectedMove{IBoard::PositionXY(9, 10)},
            },
            //Anomaly description:
            /* CPU started. CPU ('x'). Next move is for 'x':
             * In provided situation, human has winning threat but could be easily mitigated.
             * So the best move is (11,8) but cpu took (7,11)
             */
            //                       1 1 1 1 1 1 1 1 1
            //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8
            //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //0 |. . . . . . . . . . . . . . . . . . .|
            //1 |. . . . . . . . . . . . . . . . . . .|
            //2 |. . . . . . . . . . . . . . . . . . .|
            //3 |. . . . . . . . . . . . . . . . . . .|
            //4 |. . . . . . . . . . . . . . . . . . .|
            //5 |. . . . . . . . . . . . . . . . . . .|
            //6 |. . . . . . . . . . . . . . . . . . .|
            //7 |. . . . . . . . . . . . . . . . . . .|
            //8 |. . . . . . . . . . x x . . . . . . .|
            //9 |. . . . . . . . . x o x . . . . . . .|
            //10|. . . . . . . . . o x . . . . . . . .|
            //11|. . . . . . . . o o o o x . . . . . .|
            //12|. . . . . . . . . . . . . . . . . . .|
            //13|. . . . . . . . . . . . . . . . . . .|
            //14|. . . . . . . . . . . . . . . . . . .|
            //15|. . . . . . . . . . . . . . . . . . .|
            //16|. . . . . . . . . . . . . . . . . . .|
            //17|. . . . . . . . . . . . . . . . . . .|
            //18|. . . . . . . . . . . . . . . . . . .|
            //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
            TestMovies
            {
                .m_cpu{ IBoard::PositionXY(9, 9), IBoard::PositionXY(10, 10), IBoard::PositionXY(9, 11),
                        IBoard::PositionXY(8, 10), IBoard::PositionXY(11, 12), IBoard::PositionXY(8, 11)},
                .m_human{ IBoard::PositionXY(10, 9), IBoard::PositionXY(11, 11),IBoard::PositionXY(11, 9),
                          IBoard::PositionXY(11, 10), IBoard::PositionXY(9, 10), IBoard::PositionXY(11, 8)},
                .m_expectedMove{IBoard::PositionXY(11, 7)},
            }

        )
);

TEST_P(AnomalyRealGame, TestName)
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

        m_board->putMove(humanMove, m_trackerHuman->getPlayer());
        m_trackerHuman->updateScore(humanMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
        m_trackerCpu->updateScore(humanMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    }

    const uint32_t maxCandidatesNumber =30U;
    ISearchTree::PriorityQueueScore nBestMove{maxCandidatesNumber};

    //INTRO: Use minmax to generate candidates
    nBestMove.clearAll();
    m_minMax->setStates(*m_board, *m_trackerCpu, *m_trackerHuman);
    m_minMax->setDepth(3);
    m_minMax->setInitialPlayer( m_trackerCpu->getPlayer());
    m_minMax->findBestMove(nBestMove);

    vector<IBoard::PositionXY> alphaBetaCandidates;
    for(int i=0; i<nBestMove.size(); ++i)
    {
        const auto el = nBestMove.topData();
        nBestMove.popData();
        alphaBetaCandidates.push_back(el.m_move);
    }

    //AlphaBeta for finding best on high depth
    nBestMove.clearAll();
    m_alphaBeta->setStates(*m_board, *m_trackerCpu, *m_trackerHuman);
    m_alphaBeta->setDepth(5);
    m_alphaBeta->setInitialPlayer( m_trackerCpu->getPlayer());
    m_alphaBeta->findBestMove(nBestMove,alphaBetaCandidates);
    const IBoard::PositionXY best = nBestMove.topData().m_move;

    for(int i=0; i<nBestMove.size(); ++i)
    {
        const auto el = nBestMove.topData();
        nBestMove.popData();
    }

    ASSERT_TRUE(isOnTheList(params.m_expectedMove, best));
}
