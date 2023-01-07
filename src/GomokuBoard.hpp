/////////////////////////////////////////////////////////////////////////////////////////
/// @file GomokuBoard.hpp
///
/// GomokuBoard class definition.
///
/// @par Full Description.
/// Providing board for gomoku game.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 06-Jan-2015 Initial revision.
/// - zhalat 20-Sep-2016 Add GetNeighborhood() to quick get neighborhood.
/// - zhalat 04-Feb-2018 VectorLight repleaced by VectorUnique.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2015 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined(GOMOKUBOARD_HPP_)
#define GOMOKUBOARD_HPP_

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Board.hpp"       // For Board definitions.
#include "ObserverIf.hpp"  // For Observer design pattern interface.

// FORWARD REFERENCES
class TEST_GomokuBoardTest_ConstructorInvalidParameterTest;
class TEST_GomokuBoardTest_ConstructorConnectionCorrectnessTest;
class TEST_GomokuBoardTest_CopyConstructorTest;
class TEST_GomokuBoardTest_PutMoveTest;
class TEST_GomokuBoardTest_GetLastMoveTest;
class TEST_GomokuBoardTest_VacantFieldsTest;
class TEST_GomokuBoardTest_EdgeDistanceTest;
class TEST_GomokuBoardTest_NeighbourDistanceTest;
class TEST_GomokuBoardTest_InRowTest;
class TEST_GomokuBoardTest_IsOnEdgeTest;
class TEST_GomokuBoardTest_GoDirectionTest;
class TEST_GomokuBoardTest_RemoveMoveTest;
class TEST_GomokuBoardTest_RemoveNLastMoveTest;
class TEST_GomokuBoardTest_OppositePlayerTest;
class TEST_GomokuBoardTest_GetFirstMoveTest;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: GomokuBoard.
///
/// GomokuBoard class.
///
/// @par Full Description.
/// Providing board for gomoku game.
///////////////////////////////////////////////////////////////////////////////////////////
class GomokuBoard
    : public Board
    , public Observer::ObserverSubjectIf
{
   public:
    /// Max/Min size of board.
    static constexpr uint32_t MAX_GOMOKU_BOARD_SIZE       = 19;
    static constexpr uint32_t MIN_GOMOKU_BOARD_SIZE       = 5;
    static constexpr uint32_t MAX_GOMOKU_BOARD_SQARE_SIZE = MAX_GOMOKU_BOARD_SIZE * MAX_GOMOKU_BOARD_SIZE;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::PutMove
    //
    /// Put a move.
    ///
    /// @par Full Description
    /// Insert a move for specified position.
    ///
    /// @param  xy  Row/column position.
    /// @param player Player name/sign.
    ///
    /// @retval True if position is vacant and not out of scope. False otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool PutMove(const PositionXY xy, const Player player);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::PutMove
    //
    /// Put a move.
    ///
    /// @par Full Description
    ///    Insert a move for specified position.
    ///
    /// @param PositionField  Move position.
    /// @param player Player name/sign.
    ///
    /// @retval True if operation was successful. False otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool PutMove(const PositionField field, const Player player);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetMove
    //
    /// Get a move.
    ///
    /// @par Full Description
    /// Get a move form specified position.
    ///
    /// @param  xy  Row/column position.
    ///
    /// @retval  Name/sign of player from specified position.
    ///////////////////////////////////////////////////////////////////////
    virtual Player GetMove(const PositionXY xy) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetMove
    //
    /// Get a move.
    ///
    /// @par Full Description
    /// Get a move form specified field.
    ///
    /// @param  field  field number. Numberig is consequetive starting form (0,0).
    ///
    /// @retval  Name/sign of player from specified position.
    ///////////////////////////////////////////////////////////////////////
    virtual Player GetMove(const PositionField field) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::RemoveMove
    //
    /// Removes move.
    ///
    /// @par Full Description
    /// Removes a move form specified position.
    ///
    /// @param  xy  Row/column position.
    ///
    /// @retval  False if position xy was vacant true otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool RemoveMove(const PositionXY xy) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::RemoveMove
    //
    /// Removes N last movies.
    ///
    /// @par Full Description
    /// Removes N last movies.
    ///
    /// @param  n  Number of last moves to be removed.
    ///
    /// @retval  True if successful, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool RemoveNLastMove(const int n);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetLastMove
    //
    /// Return the last move being put into board.
    ///
    /// @par Full Description
    /// Return the last move being put onto board.
    /// Input parameters are modified to reflect position of the last move.
    ///
    /// @param  xy  Row/column position.
    /// @retval   True if success, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetLastMove(PositionXY & xy) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetFirstMove
    //
    /// Return the first move being put into board.
    ///
    /// @par Full Description
    /// Return the first move being put onto board.
    ///
    /// @param  xy  Row/column position.
    /// @retval   True if success, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetFirstMove(PositionXY & xy) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetMoveNumber
    //
    /// Gets number of movies on the borad.
    ///
    /// @par Full Description
    /// Gets number of movies on the borad.
    ///
    /// @retval Amount of movies on the borad.
    ///////////////////////////////////////////////////////////////////////
    virtual uint32_t GetMoveNumber() const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::VacantFields
    //
    /// Compute amount of vacant fields.
    ///
    /// @par Full Description
    /// Compute amount of vacant fields.
    ///
    /// @retval  Number of vacant fields.
    ///////////////////////////////////////////////////////////////////////
    virtual uint32_t VacantFields() const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::EdgeDistance
    //
    /// Distance to a edge of board.
    ///
    /// @par Full Description
    /// Compute number of fields from the given position to edge of board.
    /// direction points direction to be taken into account.
    ///
    /// @param  xy  Row/column position.
    /// @param  direction Direction to be taken into account.
    ///
    /// @retval  Number of fields between x,y position and board edge from direction
    ///          perspective.
    ///////////////////////////////////////////////////////////////////////
    virtual uint32_t EdgeDistance(const PositionXY xy, const Direction direction) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::NeighbourDistance
    //
    /// Distance to neighbour.
    ///
    /// @par Full Description
    /// Compute number of fields from the given position to position of neighbour move concerning
    /// to given direction. Neighborhood is consisted of the 'player' parameter.
    ///
    /// @param  xy  Row/column position..
    /// @param  direction   Direction to be taken into account.
    /// @param  player      Figure that describes neighborhood.
    ///
    /// @retval Number of fields between x,y position and the closest player from direction perspective
    ///         or
    ///         -1 if from dir perspective there is opponent player figure.
    ///         or
    ///         -2 if there is no figure till the edge of board
    ///////////////////////////////////////////////////////////////////////
    virtual int32_t NeighbourDistance(const PositionXY xy, const Direction direction, const Player player) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::InRow
    //
    /// From given position, checks how many the same figure (X or O) are placed in a row.
    ///
    /// @par Full Description
    /// From given position, checks how many the same figure (X or O) are placed in a row (the same line).
    /// 'direction' points direction to be taken into account.
    ///
    /// @param  xy  Row/column position.
    /// @param  direction Direction to be taken into account.
    ///
    /// @retval Number of figures in the same line.
    ///////////////////////////////////////////////////////////////////////
    virtual uint32_t InRow(const PositionXY xy, const Direction direction) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::IsOnEdge
    //
    /// Checks if position is on the edge of board.
    ///
    /// @par Full Description
    /// Checks if position is on the edge of board.
    /// If so, points certain edge or corner.
    ///
    /// @param  xy  Row/column position.
    ///
    /// @retval     Edge(left/right/up/down) or corner (left_up/left_down/right_up/right_down)
    ///////////////////////////////////////////////////////////////////////
    virtual OnEdge IsOnEdge(const PositionXY xy) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::IsOnBoard
    //
    /// Checks if position is on board.
    ///
    /// @par Full Description
    /// Checks if position is on board.
    ///
    /// @param  xy  Row/column position.
    /// @retval     true - if position is on board, false if otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool IsOnBoard(const PositionXY xy) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::IsOnBoard
    //
    /// Checks if position is on board.
    ///
    /// @par Full Description
    /// Checks if position is on board. Position given by absolute field number.
    ///
    /// @param  field  field number. Numberig is consequetive starting form (0,0).
    /// @retval true - if position is on board, false if otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool IsOnBoard(const PositionField field) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::CanIGo
    //
    /// Check if moving towards direction is possible.
    ///
    /// @par Full Description
    /// Check if moving one step further towards direction is possible.
    ///
    /// @param  xy  Row/column position.
    /// @param  direction to be checked.
    ///
    /// @retval true if setp doesn't exceed from board frame, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool CanIGo(const PositionXY xy, const Direction direction) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GoDirection
    //
    /// Go to step toward direction.
    ///
    /// @par Full Description
    /// Passed xy is modyfied to go one step to direction.
    ///
    /// @param  xy  Row/column position.
    /// @param  direction Direction to be taken into account.
    /// @param  steps Number of steps. Default 1 step.
    ///////////////////////////////////////////////////////////////////////
    virtual void GoDirection(PositionXY & xy, const Direction direction, const uint32_t steps = 1) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: GomokuBoard::Clone
    //
    /// Clone current state of Board.
    ///
    /// @par Full Description
    /// Clone current state of Board.
    ///
    /// @retval Reference to clone of current state of Board.
    ///////////////////////////////////////////////////////////////////////
    virtual Board & Clone() const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetNeighborhood
    //
    /// Gets the neighborhood of provided position.
    ///
    /// @par Full Description
    /// Gets the neighborhood of provided position.
    /// Neighborhood is considered as fields directly belong to provided location.
    ///
    /// @param  field  	   Position from which neighbors will be fetching.
    ///
    /// @retval Reference to container where neighbours are ketp.
    ///////////////////////////////////////////////////////////////////////
    virtual const Neighbours & GetNeighborhood(const PositionField field) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetNeighborhood
    //
    /// Gets the neighborhood of provided position.
    ///
    /// @par Full Description
    /// Gets the neighborhood of provided position.
    /// Neighborhood is considered as fields directly belong to xy.
    ///
    /// @param  xy  Row/column position.
    ///
    /// @retval Neighborhood.
    ///////////////////////////////////////////////////////////////////////
    virtual vector<graph::Node> GetNeighborhood(const PositionXY xy) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::ResetInstance
    //
    /// Revert board to initial state.
    ///
    /// @par Full Description
    /// Revert board to initial state.
    ///////////////////////////////////////////////////////////////////////
    virtual void ResetInstance();

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: ObserverSubjectIf::RegisterObserver
    //
    /// Observer register.
    ///
    /// @par Full Description
    /// Add observer to list of notified objects.
    ///
    /// @param rObserver An observer object.
    /////////////////////////////////////////////////////////////////////////////
    virtual void RegisterObserver(const Observer::ObserverIf & rObserver);

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: ObserverSubjectIf::RemoveObserver
    //
    /// Removing observer.
    ///
    /// @par Full Description
    /// Remove observer from  the list of notified objects.
    ///
    /// @return True if registration successful, false otherwise.
    /////////////////////////////////////////////////////////////////////////////
    virtual bool RemoveObserver(const Observer::ObserverIf & rObserver);

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: ObserverSubjectIf::Announce
    //
    /// Notify observers.
    ///
    /// @par Full Description
    /// Send to observer message that the state of object has changed.
    /////////////////////////////////////////////////////////////////////////////
    virtual void Announce() const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: GomokuBoard::GomokuBoard()
    //
    /// Constructor for GomokuBoard.
    ///
    /// @par Full Description
    /// Constructor for GomokuBoard. Connecting node to Gomoku-board representation.
    /// Board is square of size x size. All node value are vacant (set to NONE).
    ///
    /// @param   Size of board max 30, min 1.
    ///////////////////////////////////////////////////////////////////////
    GomokuBoard(uint32_t size);

    /// Copy constructor
    GomokuBoard(const GomokuBoard & rBoard);

    /// Destructor.
    virtual ~GomokuBoard(void)
    {
        delete m_pBoardStructure;
        m_pBoardStructure = NULL;

        delete m_pIterator;
        m_pIterator = NULL;

        delete[] m_pNeighbours;
        m_pNeighbours = NULL;
    };

   private:
    /// Friends class declaration.
#warning "TODO: Such dependency should be removed."
};

#endif /* GOMOKUBOARD_HPP_ */

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
