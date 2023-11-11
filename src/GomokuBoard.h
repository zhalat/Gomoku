#pragma once

#include "Interfaces/IBoard.h"
#include "Interfaces/IObserver.h"

using namespace std;
class TestUtility;

class GomokuBoard
    : public IBoard
    , public Observer::IObserverSubject
{
   public:
    static constexpr uint32_t k_MAX_GOMOKU_BOARD_SIZE       = 19;
    static constexpr uint32_t MIN_GOMOKU_BOARD_SIZE       = 5;
    static constexpr uint32_t k_MAX_GOMOKU_BOARD_SQARE_SIZE = k_MAX_GOMOKU_BOARD_SIZE* k_MAX_GOMOKU_BOARD_SIZE;
    static constexpr uint32_t k_MIN_GOMOKU_BOARD_SQARE_SIZE = MIN_GOMOKU_BOARD_SIZE* MIN_GOMOKU_BOARD_SIZE;

    bool putMove(const PositionXY xy, const Player player) override;
    Player getMove(const PositionXY xy) const override;
    bool removeMove(const PositionXY xy) const override;
    bool removeNLastMove(const unsigned n) override;
    bool getLastMove(PositionXY & xy) const override;
    bool getFirstMove(PositionXY & xy) const override;
    uint32_t getMoveNumber() const override;
    uint32_t vacantFields() const override ;
    uint32_t edgeDistance(const PositionXY xy, const Direction direction) const override;
    int32_t neighbourDistance(const PositionXY xy, const Direction direction, const Player player) const override;
    uint32_t inRow(const PositionXY xy, const Direction direction) const override;
    OnEdge isOnEdge(const PositionXY xy) const override;
    bool isOnBoard(const PositionXY xy) const override;
    bool canIGo(const PositionXY xy, const Direction direction) const override;
    void goDirection(PositionXY & xy, const Direction direction, const uint32_t steps = 1) const override;
    IBoard & clone() const override;
    vector<graph::Node> getNeighborhood(const PositionXY xy) const override;
    void resetInstance() override;
    uint32_t getSize() const override { return m_size; }
    IIterator<graph::Node> * getIterator() const override { return m_pIterator; }
    void registerObserver(const Observer::IObserver & observer) override;
    bool removeObserver(const Observer::IObserver & observer) override;
    void announce() const override;

    GomokuBoard(uint32_t size);
    GomokuBoard(const GomokuBoard & board);
    GomokuBoard(const GomokuBoard &&) = delete;
    GomokuBoard & operator=(const GomokuBoard &) = delete;
    GomokuBoard & operator=(const GomokuBoard &&) = delete;
    ~GomokuBoard(void)
    {
        delete m_pBoardStructure;
        m_pBoardStructure = nullptr;

        delete m_pIterator;
        m_pIterator = nullptr;

        delete[] m_pNeighbours;
        m_pNeighbours = nullptr;
    };

   private:
    size_t m_size;
    vector<PositionXY> m_moveHistory;
    graph::Graph * m_pBoardStructure;
    IIterator<graph::Node> * m_pIterator;
    Neighbours * m_pNeighbours;

    friend TestUtility;
};
