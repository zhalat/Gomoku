#pragma once

#include "Board.hpp"
#include "ObserverIf.hpp"

class GomokuBoard
    : public Board
    , public Observer::ObserverSubjectIf
{
   public:
    /// Max/Min size of board.
    static constexpr uint32_t MAX_GOMOKU_BOARD_SIZE       = 19;
    static constexpr uint32_t MIN_GOMOKU_BOARD_SIZE       = 5;
    static constexpr uint32_t MAX_GOMOKU_BOARD_SQARE_SIZE = MAX_GOMOKU_BOARD_SIZE * MAX_GOMOKU_BOARD_SIZE;

    virtual bool PutMove(const PositionXY xy, const Player player);
    virtual bool PutMove(const PositionField field, const Player player);
    virtual Player GetMove(const PositionXY xy) const;
    virtual Player GetMove(const PositionField field) const;
    virtual bool RemoveMove(const PositionXY xy) const;
    virtual bool RemoveNLastMove(const int n);
    virtual bool GetLastMove(PositionXY & xy) const;
    virtual bool GetFirstMove(PositionXY & xy) const;
    virtual uint32_t GetMoveNumber() const;
    virtual uint32_t VacantFields() const;
    virtual uint32_t EdgeDistance(const PositionXY xy, const Direction direction) const;
    virtual int32_t NeighbourDistance(const PositionXY xy, const Direction direction, const Player player) const;
    virtual uint32_t InRow(const PositionXY xy, const Direction direction) const;
    virtual OnEdge IsOnEdge(const PositionXY xy) const;
    virtual bool IsOnBoard(const PositionXY xy) const;
    virtual bool IsOnBoard(const PositionField field) const;
    virtual bool CanIGo(const PositionXY xy, const Direction direction) const;
    virtual void GoDirection(PositionXY & xy, const Direction direction, const uint32_t steps = 1) const;
    virtual Board & Clone() const;
    virtual const Neighbours & GetNeighborhood(const PositionField field) const;
    virtual vector<graph::Node> GetNeighborhood(const PositionXY xy) const;
    virtual void ResetInstance();
    virtual void RegisterObserver(const Observer::ObserverIf & rObserver);
    virtual bool RemoveObserver(const Observer::ObserverIf & rObserver);
    virtual void Announce() const;
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
};
