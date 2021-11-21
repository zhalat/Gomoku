#pragma once

#include "SearchTreeAlgorithmIf.hpp"  // For SearchTreeAlgorithmIf definitions.
#include "VectorUnique.hpp"           // For VectorUnique definitions.
#include "Logger.hpp"                 // For debbuging.
#include "StateEvaluation.hpp"        // For StateEvaluation definitions.

// FORWARD REFERENCES
class AlphaBetaTest;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: AlphaBeta
///
/// AlphaBeta class definition.
///
/// @par Full Description.
/// Alpha-Beta algorithm. Enhanced MinMax algorithm.
/// Implemented as singleton pattern.
///////////////////////////////////////////////////////////////////////////////////////////
class AlphaBeta : public SearchTreeAlgorithmIf
{
   public:
    typedef VectorUnique<Board::PositionField, GomokuBoard::MAX_GOMOKU_BOARD_SQARE_SIZE> VectorUniqueType;
    typedef std::list<Board::PositionField>::iterator VectorUniqueTypeIterator;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::FindBestMove
    //
    /// Finds the best possible move.
    ///
    /// @par Full Description
    /// You can provide as default argument:
    ///  - init candidates - then best moves are searched only among them.
    ///  - nothing - internal algorithm is used to get init candidates.
    ///
    /// @param rBestMove 	   [in/out] Container for n-best move.
    ///						            The top(best) is returned.
    /// @param rInitCandidates [in] Candidates among which best move is searching.
    ///
    /// @retval Best move.
    ///////////////////////////////////////////////////////////////////////
    virtual Board::PositionXY FindBestMove(
        PriorityQueueScore & rBestMove,
        const vector<Board::PositionXY> & rInitCandidates = vector<Board::PositionXY>());

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::GenerateCand
    //
    /// Generate list of candidate moves.
    ///
    /// @par Full Description
    /// Generate list of candidate moves. It is done only once at the beginning
    /// stage so performance is not critical.
    ///
    /// @retval Candidate moves list.
    ///////////////////////////////////////////////////////////////////////
    virtual vector<Board::PositionField> GenerateCand() const;

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: AlphaBeta::GetInstance
    //
    /// Get instance of Score.
    ///
    /// @par Full Description
    /// Get instance of Score.
    ///
    /// @return pointer to AlphaBeta instance.
    /////////////////////////////////////////////////////////////////////////////
    static AlphaBeta * GetInstance();

    /// Only for unit test. DO NOT USE IT.
    void BoardScoreCopyInitUT() { BoardScoreCopy(); }
    void ResetInstance()
    {
        // Do not use ~AlphaBeta due to it calls its ancesstors destructor
        delete m_pBoardScoreCpuCopy;
        delete m_pBoardScoreHumanCopy;
        delete m_pBoardCopy;

        m_pBoardScoreCpuCopy   = NULL;
        m_pBoardScoreHumanCopy = NULL;
        m_pBoardCopy           = NULL;
    }

    /// Destructor.
    virtual ~AlphaBeta()
    {
        delete m_pBoardScoreCpuCopy;
        delete m_pBoardScoreHumanCopy;
        delete m_pBoardCopy;

        m_pBoardScoreCpuCopy   = NULL;
        m_pBoardScoreHumanCopy = NULL;
        m_pBoardCopy           = NULL;
    }

   private:
    /// Constructor.
    AlphaBeta(const uint32_t deep, const char * const pName) :
        SearchTreeAlgorithmIf(deep, pName), m_pBoardScoreCpuCopy(NULL), m_pBoardScoreHumanCopy(NULL), m_pBoardCopy(NULL)
    {
        memset(m_SnapshotContainerCpu, 0, sizeof(m_SnapshotContainerCpu));
        memset(m_SnapshotContainerHuman, 0, sizeof(m_SnapshotContainerHuman));
        m_pStateEvaluationIf = StateEvaluation::GetInstance();
        assert(NULL != m_pStateEvaluationIf);
    }

    /// Private copy constructor - forbid copying.
    AlphaBeta(const AlphaBeta &) : SearchTreeAlgorithmIf(0, NULL) { assert(false); }

    /// Private assign operator - forbid copying.
    AlphaBeta & operator=(const AlphaBeta &) { assert(false); }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: AlphaBeta::UpdateCand
    //
    /// Update candidate list for a new members.
    ///
    /// @par Full Description
    /// Update candidate list for a new members.
    /// From current candidate list removes position that has just been put into
    /// the board and adds its neighborhood.
    ///
    /// @param rCandidates  Initial movements candidate list.
    /// @param position     Position that has just been put into board.
    ///
    /// @retval Updated candidate list.
    ///////////////////////////////////////////////////////////////////////
    VectorUniqueType UpdateCand(const VectorUniqueType & rCandidates, const uint32_t position) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: AlphaBeta::GameTreeBrowsing
    //
    /// Performs creates game tree and goes thru it to find best move.
    ///
    /// @par Full Description
    /// Performs creates game tree and goes thru it to find best move.
    ///
    /// @param rCandidates 			   Initial movements candidate list.
    /// @param rBestMovesPriorityQueue n-best movies.
    /// @param rTreeTracker            Keeps all movies from root up to leaf.
    /// @param alpha				   Indicator.
    /// @param beta					   Indicator.
    /// @param isMaximizingPlayer	   Player point of view. True for CPU.
    /// @param deep					   Current tree depth.
    ///
    /// @retval The best move.
    ///////////////////////////////////////////////////////////////////////
    ScoreForMove GameTreeBrowsing(VectorUniqueType & rCandidates, PriorityQueueScore & rBestMovesPriorityQueue,
                                  vector<Board::PositionXY> & rTreeTracker, int alpha, int beta,
                                  bool isMaximizingPlayer, const uint32_t deep = 0);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: AlphaBeta::UpdateCand4ExtendGaps
    //
    /// Update candidate list for extended gaps.
    ///
    /// @par Full Description
    /// Update candidate list for extended gaps.
    ///
    /// @param rCandidates Initial movements candidate list.
    ///
    ///////////////////////////////////////////////////////////////////////
    void UpdateCand4ExtendGaps(VectorUniqueType & rCandidates) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: AlphaBeta::UpdateCand4ThreeListGaps
    //
    /// Update candidate list for gaps of 3ABC.
    ///
    /// @par Full Description
    /// Update candidate list for gaps of 3ABC.
    ///
    /// @param rCandidates Initial movements candidate list.
    ///
    ///////////////////////////////////////////////////////////////////////
    void UpdateCand4ThreeListGaps(VectorUniqueType & rCandidates) const;

    /// Do deep copy of Board Score(m_pBoardScore) in order not using original board.
    void BoardScoreCopy();

    /// Managing snapshots.
    void MakeSnapshot(uint32_t depth);
    void RetreiveSnapshot(uint32_t depth);
    void RemoveSnapshot(uint32_t depth);

    // BoardScore state - copy.
    BoardScore * m_pBoardScoreCpuCopy;
    BoardScore * m_pBoardScoreHumanCopy;
    Board * m_pBoardCopy;

    // For managing snapshots.
    BoardScore * m_SnapshotContainerCpu[SearchTreeAlgorithmIf::DEPTH_MAX];
    BoardScore * m_SnapshotContainerHuman[SearchTreeAlgorithmIf::DEPTH_MAX];

    // For debbugging. Record game tree.
    Logger m_Logger;

    // For UT.
    friend class TEST_AlphaBetaTest_UpdateCandTest1_Test;
    friend class TEST_AlphaBetaTest_UpdateCandTest2_Test;
};

/***************************************************************************
 *   Copyright (C) 2018 by Zbigniew Halat                                  *
 *   zby.halat@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/
