#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <memory>
#include "DataContainers/Graph.h"
#include "Interfaces/IIterator.h"

using namespace std;

class IBoard {
public:
    /// Define allowed values on the board.
    enum Player : uint32_t {
        PLAYER_NONE = 0x0,
        PLAYER_A = 0x00000001,  //'x',
        PLAYER_B = 0x00000100,  //'o',
        PLAYER_EMPTY = 0x00010000,  //'.',
        PLAYER_EMPTY_OR_ENEMY = 0x01000000,  //'*',
        WIN_MARK = 0xFFFFFFFF,  //'8',
    };

    /// Define 8-way directions.
    enum Direction : uint8_t {
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
    enum OnEdge : uint8_t {
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

    static constexpr uint32_t k_MAX_NEIGHBOURS = 8;
    static constexpr int32_t k_NEIGHBOR_NOT_FOUND = -2;
    static constexpr int32_t k_NEIGHBOR_OPPONENT_FOUND = -1;

    /// Represents position on a bord as x - row, y - column.
    struct PositionXY {
        static constexpr uint32_t k_INVALID_FIELD = 0xFFFFFFFF;

        uint32_t m_x;
        uint32_t m_y;

        constexpr PositionXY() : m_x(0), m_y(0) {}

        constexpr PositionXY(uint32_t x, uint32_t y) : m_x(x), m_y(y) {}

        bool operator==(const PositionXY &xy) const {
            const bool isEqual = ((this->m_x == xy.m_x) && (this->m_y == xy.m_y));
            return isEqual;
        }

        bool operator!=(const PositionXY &xy) const {
            const bool isNotEqual = !(*this == xy);
            return isNotEqual;
        }

        bool operator<(const PositionXY &xy) const {
            const bool isGrather = ((this->m_x < xy.m_x) || ((this->m_x == xy.m_x) && (this->m_y < xy.m_y)));
            return isGrather;
        }

        bool operator>(const PositionXY &xy) const {
            const bool isLower = ((this->m_x > xy.m_x) || ((this->m_x == xy.m_x) && (this->m_y > xy.m_y)));
            return isLower;
        }

        bool operator<=(const PositionXY &xy) const {
            const bool isLowerOrEqual = ((*this < xy) || (*this == xy));
            return isLowerOrEqual;
        }

        bool operator>=(const PositionXY &xy) const {
            const bool isLowerOrEqual = ((*this > xy) || (*this == xy));
            return isLowerOrEqual;
        }

        constexpr uint32_t convert2Linear(size_t size) const {
            return size * m_x + m_y;
        }
    };

    struct Neighbours {
        Neighbours() = default;

        PositionXY m_field{};
        PositionXY m_neighbourhood[k_MAX_NEIGHBOURS]{};
        uint32_t m_neighbourhoodSize{0};
    };

    inline static Player String2Player(const char *pString) {
        assert(pString);

        Player retVal = PLAYER_EMPTY;

        if (0 == strcmp(pString, "x")) {
            retVal = PLAYER_A;
        } else if (0 == strcmp(pString, "o")) {
            retVal = PLAYER_B;
        } else if (0 == strcmp(pString, ".")) {
            retVal = PLAYER_EMPTY;
        } else if (0 == strcmp(pString, "8")) {
            retVal = WIN_MARK;
        }

        return retVal;
    };

    inline static const char *Player2String(const Player player) {
        const char *retVal = nullptr;

        if (PLAYER_A == player) {
            retVal = "x";
        } else if (PLAYER_B == player) {
            retVal = "o";
        } else if (PLAYER_EMPTY == player) {
            retVal = ".";
        } else if (WIN_MARK == player) {
            retVal = "8";
        }

        return retVal;
    };

    virtual bool putMove(const PositionXY xy, const Player player) = 0;

    virtual Player getMove(const PositionXY xy) const = 0;

    virtual bool removeMove(const PositionXY xy) = 0;

    virtual bool removeNLastMove(const unsigned n) = 0;

    virtual bool getLastMove(PositionXY &xy) const = 0;

    virtual bool getFirstMove(PositionXY &xy) const = 0;

    virtual uint32_t getMoveNumber() const = 0;

    virtual uint32_t vacantFields() const = 0;

    virtual uint32_t edgeDistance(const PositionXY xy, const Direction direction) const = 0;

    virtual int32_t neighbourDistance(const PositionXY xy, const Direction direction, const Player player) const = 0;

    virtual uint32_t inRow(const PositionXY xy, const Direction direction) const = 0;

    virtual OnEdge isOnEdge(const PositionXY xy) const = 0;

    virtual bool isOnBoard(const PositionXY xy) const = 0;

    virtual bool canIGo(const PositionXY xy, const Direction direction) const = 0;

    virtual void goDirection(PositionXY &xy, const Direction direction, const uint32_t steps = 1) const = 0;

    virtual std::shared_ptr<IBoard>clone() const = 0;

    virtual vector<graph::Node> getNeighborhood(const PositionXY xy) const = 0;

    virtual void resetInstance() = 0;

    virtual uint32_t getSize() const = 0;

    virtual IIterator<graph::Node> *getIterator() const = 0;

    virtual Player oppositePlayer(const Player player) {
        Player rival = PLAYER_EMPTY;

        if (PLAYER_A == player) {
            rival = PLAYER_B;
        } else if (PLAYER_B == player) {
            rival = PLAYER_A;
        } else {
            assert(false);
        }

        return rival;
    }

    IBoard() = default;

    IBoard(const IBoard &) = delete;

    IBoard(const IBoard &&) = delete;

    IBoard &operator=(const IBoard &) = delete;

    IBoard &operator=(const IBoard &&) = delete;

    virtual ~IBoard() = default;

private:
    static void printWhiteMark(std::ostream &stream, const uint32_t i) {
        for (uint32_t j = 0; j < i; ++j) {
            stream << " ";
        }
    }

    friend std::ostream &operator<<(std::ostream &stream, const IBoard &board) {
        const uint32_t T = board.getSize() / 10;
        const uint32_t U = board.getSize() % 10;
        IBoard::printWhiteMark(stream, 3);
        for (uint32_t i = 0; i < T; ++i) {
            for (uint32_t j = 0; j < 10; ++j) {
                if (0 == i) {
                    IBoard::printWhiteMark(stream, 2);
                } else {
                    stream << i;
                    IBoard::printWhiteMark(stream, 1);
                }
            }
        }

        for (uint32_t i = 0; i < U; ++i) {
            stream << T;
            IBoard::printWhiteMark(stream, 1);
        }

        stream << std::endl;
        IBoard::printWhiteMark(stream, 3);

        for (uint32_t i = 0; i < board.getSize(); ++i) {
            stream << i % 10;
            IBoard::printWhiteMark(stream, 1);
        }

        stream << endl;
        for (uint32_t j = 0; j < board.getSize(); ++j) {
            if (0 == j) {
                IBoard::printWhiteMark(stream, 3);
                stream << "_";
            } else {
                IBoard::printWhiteMark(stream, 1);
                stream << "_";
            }
        }
        stream << endl;

        for (uint32_t i = 0; i < board.getSize(); ++i) {
            if (i < 10) {
                stream << i;
                IBoard::printWhiteMark(stream, 1);
                stream << "|";
            } else {
                stream << i << "|";
            }

            for (uint32_t j = 0; j < board.getSize(); ++j) {
                const PositionXY xy(i, j);
                const Player player = board.getMove(xy);
                stream << Player2String(player);
                if (board.getSize() - 1 == j) {
                    stream << "|" << endl;
                } else {
                    IBoard::printWhiteMark(stream, 1);
                }
            }
        }

        for (uint32_t j = 0; j < board.getSize(); ++j) {
            if (0 == j) {
                IBoard::printWhiteMark(stream, 2);
                stream << "|_";
            } else if (board.getSize() - 1 == j) {
                IBoard::printWhiteMark(stream, 1);
                stream << "_|";
            } else {
                IBoard::printWhiteMark(stream, 1);
                stream << "_";
            }
        }
        stream << endl;
        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, const PositionXY &xy) {
        stream << "(" << xy.m_x << ", " << xy.m_y << ")" << endl;
        return stream;
    }
};
