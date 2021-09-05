#pragma once

#include "SearchTreeAlgorithmIf.hpp"  // For SearchTreeAlgorithmIf definitions.
#include "VectorUnique.hpp"           // For VectorUnique definitions.
#include "Logger.hpp"                 // For debbuging.
#include "StateEvaluation.hpp"        // For StateEvaluation definitions.

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: MinMax
///
/// MinMax class definition.
///
/// @par Full Description.
/// Min-max algorithm.
/// Implemented as singleton pattern.
///////////////////////////////////////////////////////////////////////////////////////////
class MinMax : public SearchTreeAlgorithmIf
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
    /// Finds N-best possible moves, put them to priority queue
    /// and returns the one on the top.
    /// You can provide as default argument:
    /// - init candidates - then best moves are searched only amoung them.
    /// - nothing - internal algorithm is used to get init candidates.
    ///
    /// @param rBestMove 	   [in/out] Contener for n-best move.
    ///						            The top(best) is returned.
    /// @param rInitCandidates [in] Candidates amoung which best move is searching.
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
    /// Generate list of candidate moves.
    ///
    /// @retval Candidate moves list.
    ///////////////////////////////////////////////////////////////////////
    virtual vector<Board::PositionField> GenerateCand() const;

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: Score::GetInstance
    //
    /// Get instance of Score.
    ///
    /// @par Full Description
    /// Get instance of Score.
    ///
    /// @return pointer to Score instance.
    /////////////////////////////////////////////////////////////////////////////
    static MinMax * GetInstance();

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: SearchTreeAlgorithmIf::UpdateCand
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
    VectorUniqueType UpdateCand(const VectorUniqueType & rCandidates, uint32_t position) const;

    /// Only for unit test. DO NOT USE IT.
    void BoardScoreCopyInitUT() { BoardScoreCopy(); }
    void ResetInstance()
    {
        // Do not use ~MinMax due to it calls its ancesstors destructor
        delete m_pBoardScoreCpuCopy;
        delete m_pBoardScoreHumanCopy;
        delete m_pBoardCopy;

        m_pBoardScoreCpuCopy   = NULL;
        m_pBoardScoreHumanCopy = NULL;
        m_pBoardCopy           = NULL;
    }

    /// Destructor.
    virtual ~MinMax()
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
    MinMax(const uint32_t deep, const char * const pName) :
        SearchTreeAlgorithmIf(deep, pName), m_pBoardScoreCpuCopy(NULL), m_pBoardScoreHumanCopy(NULL), m_pBoardCopy(NULL)
    {
        memset(m_SnapshotContainerCpu, 0, sizeof(m_SnapshotContainerCpu));
        memset(m_SnapshotContainerHuman, 0, sizeof(m_SnapshotContainerHuman));
        m_pStateEvaluationIf = StateEvaluation::GetInstance();
        assert(NULL != m_pStateEvaluationIf);
    }

    /// Private copy constructor - forbid copying.
    MinMax(const MinMax &) : SearchTreeAlgorithmIf(0, NULL) { assert(false); }

    /// Private assign operator - forbid copying.
    MinMax & operator=(const MinMax &) { assert(false); }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: MinMax::GameTreeBrowsingBasic
    //
    /// Browses the game-tree to find best move.
    ///
    /// @par Full Description
    /// Generates game-tree (up to depth) and assess each leaf (using score
    /// to evaluate how good the leaf is.).
    /// This is a classic min-max algorithm with 'snapshoot' as time improving.
    ///
    /// @param rCandidates      Initial movements candidate list.
    /// @param bestMoves        [Out] n-best moves.
    /// @param treeTracker      Keeps the moves to reach a leaf of tree.
    /// @param deep             Shall be set to 0 for the first invoke.
    ///                         This parameter is used by recurrence to find out how
    ///                         deep recurrence currently is.
    ///
    /// @retval Best of move and its score assessment.
    ///////////////////////////////////////////////////////////////////////
    ScoreForMove GameTreeBrowsing(VectorUniqueType & rCandidates, PriorityQueueScore & bestMoves,
                                  vector<Board::PositionXY> & treeTracker, const uint32_t deep = 0);

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
