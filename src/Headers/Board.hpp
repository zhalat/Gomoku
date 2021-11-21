/////////////////////////////////////////////////////////////////////////////////////////
/// @file Board.hpp
///
/// Board interface declaration.
///
/// @par Full Description.
/// Abstract class for each board game.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 04-Jan-2015 Initial revision.
/// - zhalat 27-Apr-2015 Extended interface for methods computing
///                      distance on a board.
/// - zhalt 16-Jan-2016  Adjust file for coding standard.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2015 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined(BOARD_HPP_)
#define BOARD_HPP_

// SYSTEM INCLUDES
#include <vector>    // For vector declaration.
#include <iostream>  // For cout.
#include <stdio.h>   // For sprintf().
#include <assert.h>  // For assert.

// C PROJECT INCLUDES
#include <string.h>  // For memset()

// C++ PROJECT INCLUDES
#include "Graph.hpp"       // For Graph declaration.
#include "IteratorIf.hpp"  // For BoardIterator declaration.

// FORWARD REFERENCES
struct Neighbours;
using std::cout;
using std::endl;
using std::vector;
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
/// CLASS NAME: Board.
///
/// Board class definition.
///
/// @par Full Description.
/// Abstract class for each board game.
///////////////////////////////////////////////////////////////////////////////////////////
class Board
{
   public:
    /// Define allowed values on the board.
    enum Player
    {
        PLAYER_NONE           = 0x0,
        PLAYER_A              = 0x00000001,  //'x',
        PLAYER_B              = 0x00000100,  //'o',
        PLAYER_EMPTY          = 0x00010000,  //'.',
        PLAYER_EMPTY_OR_ENEMY = 0x01000000,  //'*',
        WIN_MARK              = 0xFFFFFFFF,  //'8',
    };

    /// Define 8-way directions.
    enum Direction
    {
        DIRECTION_NONE,
        UP,
        UP_RIGHT,
        LEFT,
        DOWN_RIGHT,
        DOWN,
        DOWN_LEFT,
        RIGHT,
        UP_LEFT
    };

    /// Define position on edge of board
    enum OnEdge
    {
        EDGE_NONE,
        EDGE_UP,
        EDGE_DOWN,
        EDGE_LEFT,
        EDGE_RIGHT,
        CORNER_UP_LEFT,
        CORNER_UP_RIGHT,
        CORNER_DOWN_LEFT,
        CORNER_DOWN_RIGHT,
    };

    /// Represents position on a bord as x - row, y - column.
    struct PositionField;
    struct PositionXY
    {
        // Invalid field.
        static constexpr uint32_t INVALID_FIELD = 0xFFFFFFFF;

        uint32_t m_x;
        uint32_t m_y;

        constexpr PositionXY(uint32_t x = 0, uint32_t y = 0) : m_x(x), m_y(y) {}

        // Converter PositionField2PositionXY.
        PositionXY(const uint32_t boardSize, const PositionField field);

        bool operator==(const PositionXY & xy) const
        {
            const bool isEqual = ((this->m_x == xy.m_x) && (this->m_y == xy.m_y));

            return isEqual;
        }

        bool operator!=(const PositionXY & xy) const
        {
            const bool isNotEqual = !(*this == xy);

            return isNotEqual;
        }

        bool operator<(const PositionXY & xy) const
        {
            const bool isGrather = ((this->m_x < xy.m_x) || ((this->m_x == xy.m_x) && (this->m_y < xy.m_y)));

            return isGrather;
        }

        bool operator>(const PositionXY & xy) const
        {
            const bool isLower = ((this->m_x > xy.m_x) || ((this->m_x == xy.m_x) && (this->m_y > xy.m_y)));

            return isLower;
        }

        bool operator<=(const PositionXY & xy) const
        {
            const bool isLowerOrEqual = ((*this < xy) || (*this == xy));

            return isLowerOrEqual;
        }

        bool operator>=(const PositionXY & xy) const
        {
            const bool isLowerOrEqual = ((*this > xy) || (*this == xy));

            return isLowerOrEqual;
        }
    };

    /// Represents position on a board as field number.
    /// Fields are consecutive starting from 0 which is (0,0)  and the last field is (m_Size-1, m_Size-1).
    struct PositionField
    {
        // Invalid field.
        static constexpr uint32_t INVALID_FIELD = 0xFFFFFFFF;

        uint32_t m_field;

        PositionField(uint32_t field = 0) : m_field(field) {}

        // Converter: PositionXY2PositionField.
        PositionField(const uint32_t boardSize, const PositionXY & xy) { this->m_field = boardSize * xy.m_x + xy.m_y; }

        // Converter: PositionField2Node. Usefull in unit tests.
        operator graph::Node() const { return m_field; }

        // operator == - for unit tests.
    };

    // Max number of neighbours for certain field.
    // It depends on the structure of board.
    static constexpr uint32_t MAX_NEIGHBOURS = 8;

    // Neighbours of field.
    struct Neighbours
    {
        PositionField m_Field;
        PositionField m_Neighbourhood[MAX_NEIGHBOURS];
        uint32_t m_NeighbourhoodSize;

        Neighbours()
        {
            memset(m_Neighbourhood, 0x00, sizeof(m_Neighbourhood));
            m_Field             = 0;
            m_NeighbourhoodSize = 0;
        }
    };

    /// Value for vacant positions.
    static constexpr uint32_t GOMOKU_BOARD_CLEAR = 0xFFFFFFFF;

    // Constants to for finding neighbors.
    static constexpr int32_t NO_NEIGHBOR_FOUND       = -2;
    static constexpr int32_t OPPONENT_NEIGHBOR_FOUND = -1;

    inline static Player String2Player(const char * pString)
    {
        assert(pString);

        Player retVal = PLAYER_EMPTY;

        if(0 == strcmp(pString, "x"))
        {
            retVal = PLAYER_A;
        }
        else if(0 == strcmp(pString, "o"))
        {
            retVal = PLAYER_B;
        }
        else if(0 == strcmp(pString, "."))
        {
            retVal = PLAYER_EMPTY;
        }
        else if(0 == strcmp(pString, "8"))
        {
            retVal = WIN_MARK;
        }

        return retVal;
    };

    inline static const char * Player2String(const Player player)
    {
        const char * retVal = NULL;

        if(PLAYER_A == player)
        {
            retVal = "x";
        }
        else if(PLAYER_B == player)
        {
            retVal = "o";
        }
        else if(PLAYER_EMPTY == player)
        {
            retVal = ".";
        }
        else if(WIN_MARK == player)
        {
            retVal = "8";
        }

        return retVal;
    };

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::PutMove
    //
    /// Put a move.
    ///
    /// @par Full Description
    ///    Insert a move for specified position.
    ///
    /// @param  xy  Row/column position.
    /// @param player Player name/sign.
    ///
    /// @retval True if position is vacant and not out of scope. False otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool PutMove(const PositionXY xy, const Player player) = 0;

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
    virtual bool PutMove(const PositionField field, const Player player) = 0;

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
    virtual Player GetMove(const PositionXY xy) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetMove
    //
    /// Get a move.
    ///
    /// @par Full Description
    /// Get a move form specified field.
    ///
    /// @param  field  field number. Numbering is consecutive starting form (0,0).
    ///
    /// @retval  Name/sign of player from specified position.
    ///////////////////////////////////////////////////////////////////////
    virtual Player GetMove(const PositionField field) const = 0;

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
    virtual bool RemoveMove(const PositionXY xy) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::RemoveMove
    //
    /// Removes N last movies.
    ///
    /// @par Full Description
    /// Removes N last movies.
    ///
    /// @param  n  Number of moves to be removed.
    ///
    /// @retval  True if successful, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool RemoveNLastMove(const int n) = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetLastMove
    //
    /// Return the last move being put into board.
    ///
    /// @par Full Description
    ///    Return the last move being put onto board.
    /// Input parameters are modified to reflect position of the last move.
    ///
    /// @param  xy  Row/column position.
    /// @retval   True if success, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetLastMove(PositionXY & xy) const = 0;

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
    virtual bool GetFirstMove(PositionXY & xy) const = 0;

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
    virtual uint32_t GetMoveNumber() const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::VacantFields
    //
    /// Compute amount of vacant fields.
    ///
    /// @par Full Description
    ///    Compute amount of vacant fields.
    ///
    /// @retval  Number of vacant fields.
    ///////////////////////////////////////////////////////////////////////
    virtual uint32_t VacantFields() const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::EdgeDistance
    //
    /// Distance to a edge of board.
    ///
    /// @par Full Description
    ///    Compute number of fields from the given position to edge of board.
    /// direction points direction to be taken into account.
    ///
    /// @param  xy  Row/column position.
    /// @param  direction Direction to be taken into account.
    ///
    /// @retval  Number of fields between x,y position and board edge from direction
    ///          perspective.
    //////////////////////////////////////////////////////////////////////
    virtual uint32_t EdgeDistance(const PositionXY xy, const Direction direction) const = 0;

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
    /// @param  direction     Direction to be taken into account.
    /// @param  player      Figure that describes neighborhood.
    ///
    /// @retval Number of fields between x,y position and the closest player from direction perspective
    ///            or
    ///            -1 if from dir perspective there is opponent player figure.
    ///            or
    ///            -2 if there is no figure till the edge of board
    ///////////////////////////////////////////////////////////////////////
    virtual int32_t NeighbourDistance(const PositionXY xy, const Direction direction, const Player player) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::InRow
    //
    /// From given position, checks how many the same figure (X or O) are placed in a row.
    ///
    /// @par Full Description
    ///    From given position, checks how many the same figure (X or O) are placed in a row (the same line).
    /// 'direction' points direction to be taken into account.
    ///
    /// @param  xy  Row/column position.
    /// @param  direction Direction to be taken into account.
    ///
    /// @retval Number of figures in the same line.
    ///////////////////////////////////////////////////////////////////////
    virtual uint32_t InRow(const PositionXY xy, const Direction direction) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::IsOnEdge
    //
    /// Checks if position is on the edge of board.
    ///
    /// @par Full Description
    ///    Checks if position is on the edge of board.
    /// If so, points certain edge or corner.
    ///
    /// @param  xy  Row/column position.
    ///
    /// @retval      Edge(left/right/up/down) or corner (left_up/left_down/right_up/right_down)
    ///////////////////////////////////////////////////////////////////////
    virtual OnEdge IsOnEdge(const PositionXY xy) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::IsOnBoard
    //
    /// Checks if position is on board.
    ///
    /// @par Full Description
    /// Checks if position is on board.
    ///
    /// @param  xy  Row/column position.
    /// @retval      true - if position is on board, false if otherwise.
    ///////////////////////////////////////////////////////////////////////
    virtual bool IsOnBoard(const PositionXY xy) const = 0;

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
    virtual bool IsOnBoard(const PositionField field) const = 0;

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
    virtual bool CanIGo(const PositionXY xy, const Direction direction) const = 0;

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
    virtual void GoDirection(PositionXY & xy, const Direction direction, const uint32_t steps = 1) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::Clone
    //
    /// Clone current state of Board.
    ///
    /// @par Full Description
    /// Deep copy of board state.
    ///
    /// @retval Pointer to clone of current state of Board.
    ///////////////////////////////////////////////////////////////////////
    virtual Board & Clone() const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetNeighborhood
    //
    /// Gets the neighborhood of provided position.
    ///
    /// @par Full Description
    /// Gets the neighborhood of provided position.
    /// Neighborhood is considered as fields directly belong to provided location.
    /// Note: You can fetch the same data by GetNeighborhood(const PositionXY)
    /// but this should be a little more effective.
    ///
    /// @param  field  	   Position from which neighbors will be fetching.
    ///
    /// @retval Reference to container where neighbours are ketp.
    ///////////////////////////////////////////////////////////////////////
    virtual const Neighbours & GetNeighborhood(const PositionField field) const = 0;

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
    virtual vector<graph::Node> GetNeighborhood(const PositionXY xy) const = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::ResetInstance
    //
    /// Revert board to initial state.
    ///
    /// @par Full Description
    /// Revert board to initial state.
    ///////////////////////////////////////////////////////////////////////
    virtual void ResetInstance() = 0;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetSize
    //
    /// Return size of board.
    ///
    /// @par Full Description
    ///    Return size of board of size x size.
    ///
    /// @retval  Size of board. Thats means length edge of board.
    ///////////////////////////////////////////////////////////////////////
    virtual uint32_t GetSize() const { return m_Size; }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::GetIterator
    //
    /// Get iterator.
    ///
    /// @par Full Description
    /// Get iterator.
    /// Because Board keeps data in graph, Board iterator just use Graph
    /// iterator (by delegation).
    ///
    /// @retval  Iterator for board.
    ///////////////////////////////////////////////////////////////////////
    virtual IteratorIf<graph::Node> * GetIterator() const { return m_pIterator; }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::OppositePlayer
    //
    /// Gets opposite player.
    ///
    /// @par Full Description
    /// Gets opposite player.
    ///
    /// @param player Current player.
    ///
    /// @retval Rival player.
    ///////////////////////////////////////////////////////////////////////
    virtual Player OppositePlayer(const Player player)
    {
        Player rival = PLAYER_EMPTY;

        if(PLAYER_A == player)
        {
            rival = PLAYER_B;
        }
        else if(PLAYER_B == player)
        {
            rival = PLAYER_A;
        }
        else
        {
            assert(false);
        }

        return rival;
    }

    /// Destructor.
    virtual ~Board(){

    };

    /// Constructor.
    Board() :
        m_Size(0),
        m_pBoardStructure(NULL),
        m_pIterator(NULL),
        m_pNeighbours(NULL){
            // None.
        };

    // protected:
    // Board size.
    uint32_t m_Size;

    // Keeps move sequence.
    vector<PositionXY> m_MoveHistory;

    // Handler for board structure.
    graph::Graph * m_pBoardStructure;

    // Handler to iterator.
    IteratorIf<graph::Node> * m_pIterator;

    // Neighborhood of each fields for quick access.
    Neighbours * m_pNeighbours;

   private:
    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Board::PrintWhiteMark
    //
    /// Prints white marks.
    ///
    /// @par Full Description
    ///    Prints white marks.
    ///
    /// @param   Number of white marks to print.
    ///////////////////////////////////////////////////////////////////////
    static void PrintWhiteMark(std::ostream & _stream, const uint32_t i)
    {
        for(uint32_t j = 0; j < i; ++j)
        {
            _stream << " ";
        }
    }

    /// ------ Friends.
    friend std::ostream & operator<<(std::ostream & _stream, const Board & rBoard)
    {
        // Number of tens of board size.
        const uint32_t T = rBoard.GetSize() / 10;

        // Number of unity of board size.
        const uint32_t U = rBoard.GetSize() % 10;

        // Print columns' numbers related to number of tens of board size: 0,0,0,0,0,0,0,1,1,1,1,1,1..
        // Instead of printing 0 - print white space.

        // Adjustment.
        Board::PrintWhiteMark(_stream, 3);

        for(uint32_t i = 0; i < T; ++i)
        {
            for(uint32_t j = 0; j < 10; ++j)
            {
                if(0 == i)
                {
                    // Must be to two to keep adjustment.
                    Board::PrintWhiteMark(_stream, 2);
                }
                else
                {
                    _stream << i;
                    Board::PrintWhiteMark(_stream, 1);
                }
            }
        }

        for(uint32_t i = 0; i < U; ++i)
        {
            _stream << T;
            Board::PrintWhiteMark(_stream, 1);
        }

        // Print columns' numbers related to number of unit of board size: 0,1,2,3,4,5,6,7,8,9,0,1,2,3..

        // Adjustment.
        _stream << std::endl;
        Board::PrintWhiteMark(_stream, 3);

        for(uint32_t i = 0; i < rBoard.GetSize(); ++i)
        {
            _stream << i % 10;
            Board::PrintWhiteMark(_stream, 1);
        }

        _stream << endl;

        // Print '_ _' sign under each column numbers - top.
        for(uint32_t j = 0; j < rBoard.GetSize(); ++j)
        {
            if(0 == j)
            {
                Board::PrintWhiteMark(_stream, 3);
                _stream << "_";
            }
            else
            {
                Board::PrintWhiteMark(_stream, 1);
                _stream << "_";
            }
        }
        _stream << endl;

        // Print main content of Board.
        for(uint32_t i = 0; i < rBoard.GetSize(); ++i)
        {
            // Print rows' numbers.
            if(i < 10)
            {
                _stream << i;
                Board::PrintWhiteMark(_stream, 1);
                _stream << "|";
            }
            else
            {
                _stream << i << "|";
            }

            for(uint32_t j = 0; j < rBoard.GetSize(); ++j)
            {
                // Print to whom (i,j) field belongs.
                const PositionXY xy(i, j);

                const Player player = rBoard.GetMove(xy);

                _stream << Player2String(player);

                if(rBoard.GetSize() - 1 == j)
                {
                    // Close current row and go to cursor to next row.
                    _stream << "|" << endl;
                }
                else
                {
                    Board::PrintWhiteMark(_stream, 1);
                }
            }
        }

        // Print the bottom frame.
        for(uint32_t j = 0; j < rBoard.GetSize(); ++j)
        {
            if(0 == j)
            {
                Board::PrintWhiteMark(_stream, 2);
                _stream << "|_";
            }
            else if(rBoard.GetSize() - 1 == j)
            {
                Board::PrintWhiteMark(_stream, 1);
                _stream << "_|";
            }
            else
            {
                Board::PrintWhiteMark(_stream, 1);
                _stream << "_";
            }
        }
        _stream << endl;

        return _stream;
    }

    friend std::ostream & operator<<(std::ostream & _stream, const PositionXY & rPositionXY)
    {
        _stream << "(" << rPositionXY.m_x << ", " << rPositionXY.m_y << ")" << endl;
        return _stream;
    }
};

// Converter PositionField2PositionXY.
// Is defined here due to PositionField definition must be known.
inline Board::PositionXY::PositionXY(const uint32_t boardSize, const PositionField field)
{
    this->m_x = static_cast<uint32_t>(field.m_field / boardSize);
    this->m_y = field.m_field % boardSize;
}

#endif /* BOARD_HPP_ */

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
