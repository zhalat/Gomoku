#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.hpp"
#include "IteratorIf.hpp"

struct Neighbours;
using std::cout;
using std::endl;
using std::vector;

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
    virtual bool PutMove(const PositionXY xy, const Player player) = 0;
    virtual bool PutMove(const PositionField field, const Player player) = 0;
    virtual Player GetMove(const PositionXY xy) const = 0;
    virtual Player GetMove(const PositionField field) const = 0;
    virtual bool RemoveMove(const PositionXY xy) const = 0;
    virtual bool RemoveNLastMove(const int n) = 0;
    virtual bool GetLastMove(PositionXY & xy) const = 0;
    virtual bool GetFirstMove(PositionXY & xy) const = 0;
    virtual uint32_t GetMoveNumber() const = 0;
    virtual uint32_t VacantFields() const = 0;
    virtual uint32_t EdgeDistance(const PositionXY xy, const Direction direction) const = 0;
    virtual int32_t NeighbourDistance(const PositionXY xy, const Direction direction, const Player player) const = 0;
    virtual uint32_t InRow(const PositionXY xy, const Direction direction) const = 0;
    virtual OnEdge IsOnEdge(const PositionXY xy) const = 0;
    virtual bool IsOnBoard(const PositionXY xy) const = 0;
    virtual bool IsOnBoard(const PositionField field) const = 0;
    virtual bool CanIGo(const PositionXY xy, const Direction direction) const = 0;
    virtual void GoDirection(PositionXY & xy, const Direction direction, const uint32_t steps = 1) const = 0;
    virtual Board & Clone() const = 0;
    virtual const Neighbours & GetNeighborhood(const PositionField field) const = 0;
    virtual vector<graph::Node> GetNeighborhood(const PositionXY xy) const = 0;
    virtual void ResetInstance() = 0;
    virtual uint32_t GetSize() const { return m_Size; }
    virtual IteratorIf<graph::Node> * GetIterator() const { return m_pIterator; }
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
        };
    uint32_t m_Size;
    vector<PositionXY> m_MoveHistory;
    graph::Graph * m_pBoardStructure;
    IteratorIf<graph::Node> * m_pIterator;
    Neighbours * m_pNeighbours;

   private:
    static void PrintWhiteMark(std::ostream & _stream, const uint32_t i)
    {
        for(uint32_t j = 0; j < i; ++j)
        {
            _stream << " ";
        }
    }

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

inline Board::PositionXY::PositionXY(const uint32_t boardSize, const PositionField field)
{
    this->m_x = static_cast<uint32_t>(field.m_field / boardSize);
    this->m_y = field.m_field % boardSize;
}
