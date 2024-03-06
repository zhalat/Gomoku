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

//---------------------------------Test: GenerateCandTest---------------------------------
class GenerateCandTest : public ::testing::TestWithParam<TestMovies>
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

INSTANTIATE_TEST_CASE_P(
    GenerateCandTestParameters,
    GenerateCandTest,
    ::testing::Values
    (
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
            .m_cpu{},
            .m_human{},
            .m_expectedMove{},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |x + . . . . . . . . . . . . .|
        //1 |+ + . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
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
            .m_cpu{IBoard::PositionXY(0, 0)},
            .m_human{},
            .m_expectedMove{IBoard::PositionXY(0, 1),IBoard::PositionXY(1, 0),IBoard::PositionXY(1, 1)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . + + + . . . . . . . . .|
        //2 |. . . + x + . . . . . . . . .|
        //3 |. . . + + + . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
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
            .m_cpu{IBoard::PositionXY(2, 4)},
            .m_human{},
            .m_expectedMove{IBoard::PositionXY(1, 3),IBoard::PositionXY(1, 4),IBoard::PositionXY(1, 5),IBoard::PositionXY(2, 3),
                            IBoard::PositionXY(2, 5),IBoard::PositionXY(3, 3),IBoard::PositionXY(3, 4),IBoard::PositionXY(3, 5)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . + . . . . . . . . . . . .|
        //1 |. . . + + + . . . . . . . . .|
        //2 |. . . + x + + . . . . . . . .|
        //3 |. . . + + x + . . . . . . . .|
        //4 |. . . . + + + . . . . . . . .|
        //5 |. . . . . . . + . . . . . . .|
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
            .m_cpu{IBoard::PositionXY(2, 4),IBoard::PositionXY(3, 5)},
            .m_human{},
            .m_expectedMove{IBoard::PositionXY(1, 3),IBoard::PositionXY(1, 4),IBoard::PositionXY(1, 5),IBoard::PositionXY(2, 3),
                            IBoard::PositionXY(2, 5),IBoard::PositionXY(2, 6),IBoard::PositionXY(3, 3),IBoard::PositionXY(3, 4),
                            IBoard::PositionXY(3, 6),IBoard::PositionXY(4, 4),IBoard::PositionXY(4, 5),IBoard::PositionXY(4, 6),
                            IBoard::PositionXY(0, 2),IBoard::PositionXY(5, 7)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. + x + x + . . . . . . . . .|
        //1 |. + + + o + . . . . . . . . .|
        //2 |. . . + + + . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . . . . . . . . . .|
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
            .m_cpu{IBoard::PositionXY(0, 2),IBoard::PositionXY(0, 4)},
            .m_human{IBoard::PositionXY(1, 4)},
            .m_expectedMove{IBoard::PositionXY(0, 1),IBoard::PositionXY(0, 3),IBoard::PositionXY(0, 5),IBoard::PositionXY(1, 1),
                            IBoard::PositionXY(1, 2),IBoard::PositionXY(1, 3),IBoard::PositionXY(1, 5),IBoard::PositionXY(2, 3),
                            IBoard::PositionXY(2, 4),IBoard::PositionXY(2, 5),IBoard::PositionXY(0, 0),IBoard::PositionXY(0, 6)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . + + + . . . . . . . . . .|
        //3 |. . + o + + . . . . + . . . .|
        //4 |. . + + x + . + + + . . . . .|
        //5 |. . . + + + + + x + . . . . .|
        //6 |. . . . . + + x + + . . . . .|
        //7 |. . . . . + x + + . . . . . .|
        //8 |. . . . . + + + . . . . . . .|
        //9 |. . . . + . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies
        {
            .m_cpu{IBoard::PositionXY(4, 4),IBoard::PositionXY(5, 8),IBoard::PositionXY(6, 7),IBoard::PositionXY(7, 6)},
            .m_human{IBoard::PositionXY(3, 3)},
            .m_expectedMove{IBoard::PositionXY(2, 2), IBoard::PositionXY(2, 3), IBoard::PositionXY(2, 4),IBoard::PositionXY(3, 2),
                            IBoard::PositionXY(3, 4), IBoard::PositionXY(3, 5), IBoard::PositionXY(4, 2),IBoard::PositionXY(4, 3),
                            IBoard::PositionXY(4, 5), IBoard::PositionXY(5, 3), IBoard::PositionXY(5, 4),IBoard::PositionXY(5, 5),
                            IBoard::PositionXY(3, 10), IBoard::PositionXY(4, 7), IBoard::PositionXY(4, 8),IBoard::PositionXY(4, 9),
                            IBoard::PositionXY(5, 6), IBoard::PositionXY(5, 7), IBoard::PositionXY(5, 9),IBoard::PositionXY(9, 4),
                            IBoard::PositionXY(6, 5), IBoard::PositionXY(6, 6), IBoard::PositionXY(6, 8),IBoard::PositionXY(6, 9),
                            IBoard::PositionXY(7, 5), IBoard::PositionXY(7, 7), IBoard::PositionXY(7, 8),IBoard::PositionXY(8, 5),
                            IBoard::PositionXY(8, 6), IBoard::PositionXY(8, 7)}
        }
    )
);

TEST_P(GenerateCandTest, TestName)
{
    // The scenario:
    // 1. Put on the board some moves.
    // 2. Run generateCand()
    // 3. Vector 'cands' should contain unique candidates which are the closest neighborhood and extended gaps.

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

    m_alphaBeta->setStates(*m_board, *m_trackerCpu, *m_trackerHuman);

    if(not params.m_expectedMove.empty())
    {
        vector<IBoard::PositionXY> cands = m_alphaBeta->generateCand();
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,cands));
    }
    else
    {
        vector<IBoard::PositionXY> cands = m_alphaBeta->generateCand();
        ASSERT_TRUE(cands.empty());
    }
}

//---------------------------------Test: UpdateCandTest---------------------------------
class UpdateCandTest : public ::testing::TestWithParam<TestMovies2>
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

INSTANTIATE_TEST_CASE_P(
    UpdateCandTestParameters,
    UpdateCandTest,
    ::testing::Values
    (
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. + . + . * . . . . . . . . .|
        //2 |* . + + + . + . . . . . . . .|
        //3 |. * + x + + . . . . . . . . .|
        //4 |* * # + x + * . . . . . . . .|
        //5 |. * + x + + . . . . . . . . .|
        //6 |* . + + + . + . . . . . . . .|
        //7 |. + . + . * . . . . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies2
        {
            .m_cpu{IBoard::PositionXY(3, 3),IBoard::PositionXY(4, 4),IBoard::PositionXY(5, 3)},
            .m_human{},
            .m_isExtraMoveCpu = true,
            .m_expectedMove{IBoard::PositionXY(2, 2),IBoard::PositionXY(2, 3),IBoard::PositionXY(2, 4),IBoard::PositionXY(3, 1),
                            IBoard::PositionXY(3, 2),IBoard::PositionXY(3, 4),IBoard::PositionXY(3, 5),IBoard::PositionXY(4, 1),
                            IBoard::PositionXY(4, 3),IBoard::PositionXY(4, 5),IBoard::PositionXY(5, 1),IBoard::PositionXY(5, 2),
                            IBoard::PositionXY(5, 4),IBoard::PositionXY(5, 5),IBoard::PositionXY(6, 2),IBoard::PositionXY(6, 3),
                            IBoard::PositionXY(6, 4),

                            IBoard::PositionXY(1, 1),IBoard::PositionXY(1, 3),IBoard::PositionXY(1, 5),IBoard::PositionXY(2, 0),
                            IBoard::PositionXY(2, 6),IBoard::PositionXY(4, 0),IBoard::PositionXY(4, 6),IBoard::PositionXY(6, 0),
                            IBoard::PositionXY(6, 6),IBoard::PositionXY(7, 1),IBoard::PositionXY(7, 3),IBoard::PositionXY(7, 5)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. + . + . . . . . . . . . . .|
        //2 |. . + + + . + . . . . . . . .|
        //3 |. * + x + + . . . . . . . . .|
        //4 |. * # + x + . . . . . . . . .|
        //5 |. * + x + + . . . . . . . . .|
        //6 |. . + + + . + . . . . . . . .|
        //7 |. + . + . . . . . . . . . . .|
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies2
        {
            .m_cpu{IBoard::PositionXY(3, 3),IBoard::PositionXY(4, 4),IBoard::PositionXY(5, 3)},
            .m_human{},
            .m_isExtraMoveCpu = false,
            .m_expectedMove{IBoard::PositionXY(2, 2),IBoard::PositionXY(2, 3),IBoard::PositionXY(2, 4),IBoard::PositionXY(3, 1),
                            IBoard::PositionXY(3, 2),IBoard::PositionXY(3, 4),IBoard::PositionXY(3, 5),IBoard::PositionXY(4, 1),
                            IBoard::PositionXY(4, 3),IBoard::PositionXY(4, 5),IBoard::PositionXY(5, 1),IBoard::PositionXY(5, 2),
                            IBoard::PositionXY(5, 4),IBoard::PositionXY(5, 5),IBoard::PositionXY(6, 2),IBoard::PositionXY(6, 3),
                            IBoard::PositionXY(6, 4),

                            IBoard::PositionXY(1, 1),IBoard::PositionXY(1, 3),IBoard::PositionXY(2, 6),
                            IBoard::PositionXY(7, 1),IBoard::PositionXY(7, 3),IBoard::PositionXY(6, 6)},
        }
    )
);

TEST_P(UpdateCandTest, TestName)
{
    // The scenario:
    // 1. On the board where are 3 move run initCandidates = GenerateCand()
    // 2. The result is initCandidates vector which contains (unique) neighborhood of each move (see '+')
    // 3. Put a new move PositionXY(4, 2) (see '#')
    // 4. The result shall be that the neighbor shall be removed from initCandidates and
    //    his unique neighbors will be added to initial initCandidates.(see '*')
    const IBoard::PositionXY newMove = IBoard::PositionXY(4, 2);
    TestMovies2 params = GetParam();

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

    m_alphaBeta->setStates(*m_board, *m_trackerCpu, *m_trackerHuman);
    SetBoard(*m_alphaBeta->m_boardCpy.get());//score shall use m_boardCpy not original m_board
    const vector<IBoard::PositionXY> initCands = m_alphaBeta->generateCand();

    //add newMove
    const IBoard::Player extraPlayerMove = params.m_isExtraMoveCpu==m_trackerCpu->getPlayer()? m_trackerCpu->getPlayer(): m_trackerHuman->getPlayer();
    m_alphaBeta->m_boardCpy->putMove(newMove, extraPlayerMove);
    m_alphaBeta->m_cpuCpy->updateScore(newMove, false, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    m_alphaBeta->m_humanCpy->updateScore(newMove, true, ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);

    if(not params.m_expectedMove.empty())
    {
        const vector<IBoard::PositionXY> updatedCands = m_alphaBeta->updateCand(initCands,newMove);
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,updatedCands));
    }
    else
    {
        const vector<IBoard::PositionXY> updatedCands = m_alphaBeta->updateCand(initCands, newMove);
        ASSERT_TRUE(updatedCands.empty());
    }

    SetBoard(*m_alphaBeta->m_boardCpy.get());//at the end set score to use original m_board
}

//---------------------------------Test: FindBestMoveTest---------------------------------
class FindBestMoveTest : public ::testing::TestWithParam<TestMovies3>
{
    void SetUp()
    {
        m_board = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        SetBoard(*m_board);
        m_alphaBeta = make_unique<AlphaBeta>(k_DEFAULT_DEPTH, "AlphaBeta");
        m_alphaBeta->setStates(*m_board,*m_trackerCpu,*m_trackerHuman);
        m_alphaBeta->setInitialPlayer(IBoard::Player::PLAYER_A);
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

INSTANTIATE_TEST_CASE_P(
    FindBestMoveTestParameters,
    FindBestMoveTest,
    ::testing::Values
    (
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . x . . . . . . . . . . . .|
        //3 |. . . x . . . . . . . . . . .|
        //4 |. . . . x . . . . . . . . . .|
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
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(2, 2),IBoard::PositionXY(3, 3),IBoard::PositionXY(4, 4)},
            .m_human{},
            .m_depth{1,2,3},
            .m_expectedMove{IBoard::PositionXY(1, 1), IBoard::PositionXY(5, 5)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. o . . . . . . . . . . . . .|
        //1 |. x . . . . x . . . . . . . .|
        //2 |. x . . . . x . . . . . . . .|
        //3 |. x . . . . . . . . . . . . .|
        //4 |. x . . . . . . . . . . . . .|
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
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(1, 1), IBoard::PositionXY(2, 1), IBoard::PositionXY(3, 1), IBoard::PositionXY(4, 1), IBoard::PositionXY(1, 6), IBoard::PositionXY(2, 6)},
            .m_human{IBoard::PositionXY(0, 1)},
            .m_depth{1,2,3,4},
            .m_expectedMove{IBoard::PositionXY(5, 1)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . x . x . . . . . . . . .|
        //5 |. . x . . . x . . . . . . . .|
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
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(5, 2), IBoard::PositionXY(4, 3), IBoard::PositionXY(5, 6), IBoard::PositionXY(4, 5)},
            .m_human{},
            .m_depth{1,2,3,4},
            .m_expectedMove{IBoard::PositionXY(3, 4)},
        },
        //                       1 1 1 1 1
        //   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //0 |. . . . . . . . . . . . . . .|
        //1 |. . . . . . . . . . . . . . .|
        //2 |. . . . . . . . . . . . . . .|
        //3 |. . . . . . . . . . . . . . .|
        //4 |. . . . . . o . . . . . . . .|
        //5 |. . . . . o . o . . . . . . .|
        //6 |. . . . . . x . . . . . . . .|
        //7 |. . . . . x . . . . . . . . .|
        //8 |. . . . x . . . . . . . . . .|
        //9 |. . . x . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(6, 6), IBoard::PositionXY(7, 5), IBoard::PositionXY(8, 4),IBoard::PositionXY(9, 3)},
            .m_human{IBoard::PositionXY(5, 7), IBoard::PositionXY(4, 6), IBoard::PositionXY(5, 5)},
            .m_depth{1,2,3,4},
            .m_expectedMove{IBoard::PositionXY(10, 2)},
        },
        //                       1 1 1 1 1
        //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //	0 |. . . . . . . . . . . . . . .|
        //	1 |. . . . . . . . . . . . . . .|
        //	2 |. . . . . . . . . . . . . . .|
        //	3 |. . . . . . . . . . . . . . .|
        //	4 |. . . . . . . . . . . . . . .|
        //	5 |. . . . . x . . . . . . . . .|
        //	6 |. . . . . x x x o . . . . . .|
        //	7 |. . . . . . . x . . . . . . .|
        //	8 |. . . . . . . . o . . . . . .|
        //	9 |. . . . . . . o o . . . . . .|
        //	10|. . . . . . . . o . . . . . .|
        //	11|. . . . . . . . . . . . . . .|
        //	12|. . . . . . . . . . . . . . .|
        //	13|. . . . . . . . . . . . . . .|
        //	14|. . . . . . . . . . . . . . .|
        //	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(5, 5), IBoard::PositionXY(6, 5), IBoard::PositionXY(6, 6),IBoard::PositionXY(6, 7), IBoard::PositionXY(7, 7)},
            .m_human{IBoard::PositionXY(6, 8), IBoard::PositionXY(8, 8), IBoard::PositionXY(9, 8),IBoard::PositionXY(10, 8), IBoard::PositionXY(9, 7)},
            .m_depth{1,2,3,4},
            .m_expectedMove{IBoard::PositionXY(7, 8)},
        },
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . . . . x . . . . . .|
        // 5 |. . . . . . . x . . . . . . .|
        // 6 |. . . . . . x . . . . . . . .|
        // 7 |. . . . . x . . . . . . . . .|
        // 8 |. . . . . . . . . . . . . . .|
        // 9 |. . . . . . . o o o o . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(5, 7), IBoard::PositionXY(6, 6), IBoard::PositionXY(7, 5),IBoard::PositionXY(4, 8)},
            .m_human{IBoard::PositionXY(9, 7), IBoard::PositionXY(9, 8), IBoard::PositionXY(9, 9),IBoard::PositionXY(9, 10)},
            .m_depth{1,2,3,4},
            .m_expectedMove{IBoard::PositionXY(3, 9),IBoard::PositionXY(8, 4)},
        },
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . . . . . . . . . . .|
        // 5 |. . . . . . . . . . . . . . .|
        // 6 |. . . . . . x . . . . . . . .|
        // 7 |. . . . . x . . . . . . . . .|
        // 8 |. . . . x . o . . . . . . . .|
        // 9 |. . . . . . . o . . . . . . .|
        // 10|. . . . . . . . o . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . o . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(8, 4), IBoard::PositionXY(7, 5), IBoard::PositionXY(6, 6)},
            .m_human{IBoard::PositionXY(8, 6), IBoard::PositionXY(9, 7), IBoard::PositionXY(10, 8),IBoard::PositionXY(12, 10)},
            .m_depth{1,2,3,4},
            .m_expectedMove{IBoard::PositionXY(11, 9)},
        },
        //                        1 1 1 1 1
        //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //    _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        // 0 |. . . . . . . . . . . . . . .|
        // 1 |. . . . . . . . . . . . . . .|
        // 2 |. . . . . . . . . . . . . . .|
        // 3 |. . . . . . . . . . . . . . .|
        // 4 |. . . . . . . . . . x . . . .|
        // 5 |. . . . . . . . . o . . . . .|
        // 6 |. . . . . . . . o . . . . . .|
        // 7 |. . . . . . x o . . . . . . .|
        // 8 |. . . . . x o o o . . . . . .|
        // 9 |. . . . . x x x o . . . . . .|
        // 10|. . . . . . . . . . . . . . .|
        // 11|. . . . . . . . . . . . . . .|
        // 12|. . . . . . . . . . . . . . .|
        // 13|. . . . . . . . . . . . . . .|
        // 14|. . . . . . . . . . . . . . .|
        //   |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(9, 5), IBoard::PositionXY(9, 6), IBoard::PositionXY(9, 7),IBoard::PositionXY(8, 5), IBoard::PositionXY(7, 6), IBoard::PositionXY(4, 10)},
            .m_human{IBoard::PositionXY(9, 8), IBoard::PositionXY(8, 6), IBoard::PositionXY(8, 7),
                     IBoard::PositionXY(7, 7), IBoard::PositionXY(6, 8), IBoard::PositionXY(5, 9),
                     IBoard::PositionXY(8, 8)},
            .m_depth{1,2,3,4},
            .m_expectedMove{IBoard::PositionXY(9, 4)},
        },
        //		                   1 1 1 1 1
        //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //	0 |. . . . . . . . . . . . . . .|
        //	1 |. . . . . . . . . . . . . . .|
        //	2 |. . . . . . . . . . . . . . .|
        //	3 |. . . . . . . . . o . . . . .|
        //	4 |. . . . . . . . o . o . . . .|
        //	5 |. . . . . . . . . . . . . . .|
        //	6 |. . . . . . . . . o . . . . .|
        //	7 |. . . . x . . . . o . . . . .|
        //	8 |. . . . . x . . . . . . . . .|
        //	9 |. . . . . . . . . . . . . . .|
        //	10|. . . . . x . . . . . . . . .|
        //	11|. . . . x . . . . . . . . . .|
        //	12|. . . . . . . . . . . . . . .|
        //	13|. . . . . . . . . . . . . . .|
        //	14|. . . . . . . . . . . . . . .|
        //	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(7, 4), IBoard::PositionXY(8, 5), IBoard::PositionXY(10, 5),IBoard::PositionXY(11, 4)},
            .m_human{IBoard::PositionXY(3, 9), IBoard::PositionXY(4, 8), IBoard::PositionXY(4, 10),IBoard::PositionXY(6, 9), IBoard::PositionXY(7, 9)},
            .m_depth{1,2,3,4},
            .m_expectedMove{IBoard::PositionXY(4, 9),IBoard::PositionXY(4, 7)},
        },
        //		                   1 1 1 1 1
        //	   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
        //	   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        //	0 |. . . . . . . . . . . . . . .|
        //	1 |. . . . . . . . . . . . . . .|
        //	2 |. . . . . . . . . . . . . . .|
        //	3 |. . . . . . . . . x x . o . .|
        //	4 |. . . . . . . . o o . . . . .|
        //	5 |. . . . . . . . . x . . . . .|
        //	6 |. . . . . . . . x . . . . . .|
        //	7 |. . . . . . . x . . . . . . .|
        //	8 |. . . . . . o . . . . . . . .|
        //	9 |. . . . . . . . . . . . . . .|
        //	10|. . . . . . . . . . . . . . .|
        //	11|. . . . . . . . . . . . . . .|
        //	12|. . . . . . . . . . . . . . .|
        //	13|. . . . . . . . . . . . . . .|
        //	14|. . . . o o o . . . . . . . .|
        //	  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(3, 9), IBoard::PositionXY(3, 10), IBoard::PositionXY(5, 9),IBoard::PositionXY(6, 8), IBoard::PositionXY(7, 7)},
            .m_human{IBoard::PositionXY(14, 4), IBoard::PositionXY(14, 5), IBoard::PositionXY(14, 6),IBoard::PositionXY(8, 6),  IBoard::PositionXY(4, 11), IBoard::PositionXY(4, 9),IBoard::PositionXY(3, 12)},
            .m_depth{1,2,3,4},
            .m_expectedMove{IBoard::PositionXY(4, 10),IBoard::PositionXY(14, 3),IBoard::PositionXY(14, 7)},
        }
    )
);

TEST_P(FindBestMoveTest, TestName)
{
    TestMovies3 params = GetParam();

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

    ISearchTree::PriorityQueueScore nBestMove{2};
    if(not params.m_expectedMove.empty())
    {
        for(const auto depth : params.m_depth)
        {
           // cout<<*m_board<<endl;
            m_alphaBeta->setStates(*m_board, *m_trackerCpu, *m_trackerHuman);

            m_alphaBeta->setDepth(depth);
            nBestMove.clearAll();
            IBoard::PositionXY best = m_alphaBeta->findBestMove(nBestMove);
            ASSERT_TRUE(isOnTheList(params.m_expectedMove,best));
        }
    }
    else
    {
        EXPECT_TRUE(false);
    }
}

//---------------------------------Test: StalemateTest---------------------------------
class StalemateTest : public ::testing::TestWithParam<TestMovies3>
{
    void SetUp()
    {
        m_board = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        SetBoard(*m_board);
        m_alphaBeta = make_unique<AlphaBeta>(k_DEFAULT_DEPTH, "AlphaBeta");
        m_alphaBeta->setStates(*m_board,*m_trackerCpu,*m_trackerHuman);
        m_alphaBeta->setInitialPlayer(IBoard::Player::PLAYER_A);
    }

    void TearDown()
    {

    }

public:
    static constexpr uint32_t k_DEFAULT_DEPTH = 3;
    static constexpr uint32_t k_BOARD_SIZE = 5;
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

INSTANTIATE_TEST_CASE_P(
    StalemateTestParameters,
    StalemateTest,
    ::testing::Values
    (
        //	   0 1 2 3 4
        //	   _ _ _ _ _
        //	0 |x o x x x|
        //	1 |x x o x x|
        //	2 |x x x o x|
        //	3 |x x x x o|
        //	4 |o . . . o|
        //	  |_ _ _ _ _|
        TestMovies3
        {
            .m_cpu{IBoard::PositionXY(0, 0),  IBoard::PositionXY(0, 2),
                   IBoard::PositionXY(0, 3), IBoard::PositionXY(0, 4),
                   IBoard::PositionXY(1, 0), IBoard::PositionXY(1, 1),
                   IBoard::PositionXY(1, 3), IBoard::PositionXY(1, 4),
                   IBoard::PositionXY(2, 0), IBoard::PositionXY(2, 1), IBoard::PositionXY(2, 2),
                    IBoard::PositionXY(2, 4),
                   IBoard::PositionXY(3, 0), IBoard::PositionXY(3, 1), IBoard::PositionXY(3, 2),
                   IBoard::PositionXY(3, 3)},

            .m_human{IBoard::PositionXY(0, 1),IBoard::PositionXY(1, 2),IBoard::PositionXY(2, 3),IBoard::PositionXY(3, 4),IBoard::PositionXY(4, 0), IBoard::PositionXY(4, 4)},
            .m_depth{1,2,3,4},
            .m_expectedMove{IBoard::PositionXY(4, 1),IBoard::PositionXY(4, 2),IBoard::PositionXY(4, 3)},
        }
    )
);

TEST_P(StalemateTest, TestName)
{
    TestMovies3 params = GetParam();

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

    const uint32_t maxCandidatesNumber = 20U;
    ISearchTree::PriorityQueueScore nBestMove{maxCandidatesNumber};
    for(const auto depth : params.m_depth)
    {
        //Check result - shall not crash.
        m_alphaBeta->setStates(*m_board, *m_trackerCpu, *m_trackerHuman);

        m_alphaBeta->setDepth(depth);
        nBestMove.clearAll();
        IBoard::PositionXY best = m_alphaBeta->findBestMove(nBestMove);
        ASSERT_TRUE(isOnTheList(params.m_expectedMove,best));
    }
}

//---------------------------------Bug Fix: BugsTest---------------------------------
class BugsTest : public ::testing::TestWithParam<TestMovies3>
{
    void SetUp()
    {
        m_board = make_unique<GomokuBoard>(k_BOARD_SIZE);
        m_spotterCpu = make_unique<Spotter>(IBoard::PLAYER_A);
        m_spotterHuman = make_unique<Spotter>(IBoard::PLAYER_B);
        m_trackerCpu = make_unique<ThreatTracker>(IBoard::PLAYER_A,*m_spotterCpu.get());
        m_trackerHuman = make_unique<ThreatTracker>(IBoard::PLAYER_B,*m_spotterHuman.get());
        m_trackerCpu->setBoard(*m_board.get());
        m_trackerHuman->setBoard(*m_board.get());
        SetBoard(*m_board);
        m_alphaBeta = make_unique<AlphaBeta>(k_DEFAULT_DEPTH, "AlphaBeta");
        m_alphaBeta->setStates(*m_board,*m_trackerCpu,*m_trackerHuman);
        m_alphaBeta->setInitialPlayer(IBoard::Player::PLAYER_A);
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

INSTANTIATE_TEST_CASE_P(
    BugsTestParameters,
    BugsTest,
    ::testing::Values
    (
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
        //8 |. . . . . . . . . . . . . . .|
        //9 |. . . . . . . . . . . . . . .|
        //10|. . . . . . . . . . . . . . .|
        //11|. . . . . . . . . . . . . . .|
        //12|. . . . . . . . . . . . . . .|
        //13|. . . . . . . . . . . . . . .|
        //14|. . . . . . . . . . . . . . .|
        //  |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
        TestMovies3
        {
            .m_cpu{},
            .m_human{},
            .m_depth{},
            .m_expectedMove{}
        }
    )
);

TEST_P(BugsTest, Bug1)
{
    TestMovies3 params = GetParam();

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

    const uint32_t maxCandidatesNumber = 20U;
    ISearchTree::PriorityQueueScore nBestMove{maxCandidatesNumber};
    for(const auto depth : params.m_depth)
    {
        //Check result - shall not crash.
        m_alphaBeta->setStates(*m_board, *m_trackerCpu, *m_trackerHuman);

        m_alphaBeta->setDepth(depth);
        nBestMove.clearAll();
        IBoard::PositionXY best = m_alphaBeta->findBestMove(nBestMove);
    }
}