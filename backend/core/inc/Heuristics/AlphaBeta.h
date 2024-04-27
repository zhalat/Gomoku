#pragma once
#include <gtest/gtest_prod.h>
#include "Interfaces/ISearchTree.h"
#include "DataContainers/VectorUnique.h"
#include "EvalBoard.h"
#include "TreeLogger.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: AlphaBeta
///
/// AlphaBeta class definition.
///
/// @par Full Description.
/// Alpha-Beta algorithm. Enhanced MinMax algorithm.
/// Implemented as singleton pattern.
///////////////////////////////////////////////////////////////////////////////////////////
class AlphaBeta : public ISearchTree
{
   public:
    using VectorUniqueType = VectorUnique<uint32_t , GomokuBoard::k_MAX_GOMOKU_BOARD_SQARE_SIZE> ;

    void setStates(const IBoard& board, const ThreatTracker& cpu, const ThreatTracker& human) override;
    vector<IBoard::PositionXY> generateCand() const override;
    IBoard::PositionXY findBestMove(PriorityQueueScore& bestMove, const vector<IBoard::PositionXY> & initCandidates = vector<IBoard::PositionXY>()) override;

    AlphaBeta(const uint32_t depth, std::string name)
    :ISearchTree(depth, name){}
    AlphaBeta(const AlphaBeta &) = delete;
    AlphaBeta(const AlphaBeta &&) = delete;
    AlphaBeta &operator=(const AlphaBeta &) = delete;
    AlphaBeta &operator=(const AlphaBeta &&) = delete;
    virtual ~AlphaBeta() = default;

   private:
    vector<IBoard::PositionXY> updateCand(const vector<IBoard::PositionXY>& candidates, IBoard::PositionXY position) const;
    void updateCand4ExtendGaps(std::vector<IBoard::PositionXY>& candidates) const;
    void updateCand4ThreeListGaps(std::vector<IBoard::PositionXY>& candidates) const;

    ScoreForMove gameTreeBrowsing(vector<IBoard::PositionXY>& candidates, PriorityQueueScore& bestMovies,
                                  vector<IBoard::PositionXY> & treeTracker, int alpha, int beta,
                                  bool isMaximizingPlayer, const uint32_t deep = 0);

    shared_ptr<GomokuBoard> m_boardCpy{nullptr};
    shared_ptr<ThreatTracker> m_cpuCpy{nullptr};
    shared_ptr<ThreatTracker> m_humanCpy{nullptr};
    unique_ptr<EvalBoard> m_evalBoard= make_unique<EvalBoard>();

    TreeLogger m_Logger;
    FRIEND_TEST(UpdateCandTest, TestName);
};