#pragma once
#include <assert.h>
#include <string>
#include <vector>
#include <memory>
#include "Interfaces/IBoard.h"
#include "Interfaces/IEvalBoard.h"
#include "ThreatTracker.h"
#include "DataContainers/PriorityQueue.h"

using std::vector;
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MINUS_INFINITY std::numeric_limits<int>::min()
#define PLUS_INFINITY std::numeric_limits<int>::max()

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: ISearchTree
///
/// ISearchTree interface definition.
///
/// @par Full Description.
/// Abstract class for each search tree algorithm implementation.
///////////////////////////////////////////////////////////////////////////////////////////
class ISearchTree
{
   public:
    static constexpr uint32_t k_MAX_NUMBER_OF_CANDIDATES = 300;
    static constexpr uint32_t k_DEFAULT_DEPTH = 2;
    static constexpr uint32_t k_MAX_DEPTH = 8;

    struct ScoreForMove
    {
        int m_score {0};
        IBoard::PositionXY m_move {IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD)};

        ScoreForMove(const int score = 0)
        {
            m_score = score;
            m_move  = {IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD)};
        }

        bool operator<(const ScoreForMove& rX) const
        {
            const bool isGrather = (this->m_score < rX.m_score);
            return isGrather;
        }

        bool operator>(const ScoreForMove & rX) const
        {
            const bool isLess = (this->m_score > rX.m_score);
            return isLess;
        }
    };
    using PriorityQueueScore = PriorityQueue<ScoreForMove, std::vector<ScoreForMove>>;

    virtual IBoard::PositionXY findBestMove(PriorityQueueScore& bestMove, const vector<IBoard::PositionXY> & initCandidates = vector<IBoard::PositionXY>()) = 0;
    virtual vector<IBoard::PositionXY> generateCand() const = 0;
    virtual void setStates(const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) = 0;

    void setDepth(const uint32_t deep) { m_depth = deep; }
    uint32_t getDepth() { return m_depth; }
    void setInitialPlayer(const IBoard::Player initPlayer) { m_currentPlayerTurn = initPlayer; }
    void switchPlayer()
    {
        if(IBoard::PLAYER_A == m_currentPlayerTurn)
        {
            m_currentPlayerTurn = IBoard::PLAYER_B;
        }
        else if(IBoard::PLAYER_B == m_currentPlayerTurn)
        {
            m_currentPlayerTurn = IBoard::PLAYER_A;
        }
        else
        {
            assert(false);
        }
    }
    IBoard::Player whoIsTurn() const { return m_currentPlayerTurn; }
    inline bool isMaxPlayerTurn() const
    {
        const bool retVal = (m_currentPlayerTurn == m_cpu->getPlayer());
        return retVal;
    }
    std::string getName() const { return m_name; }
    void startTimer(){};
    bool isTimerElapsed() const {};

    ISearchTree(const uint32_t depth, std::string name)
    :m_depth(depth)
    ,m_name(name)
    {}
    ISearchTree(const ISearchTree &) = delete;
    ISearchTree(const ISearchTree &&) = delete;
    ISearchTree &operator=(const ISearchTree &) = delete;
    ISearchTree &operator=(const ISearchTree &&) = delete;
    virtual ~ISearchTree() = default;

   protected:
    uint32_t m_depth;
    std::string m_name;
    IBoard::Player m_currentPlayerTurn {IBoard::PLAYER_EMPTY};
    const IBoard* m_board {nullptr};
    const ThreatTracker* m_cpu {nullptr};
    const ThreatTracker* m_human {nullptr};
    unique_ptr<IEvalBoard> m_evalBoard {nullptr};
};
