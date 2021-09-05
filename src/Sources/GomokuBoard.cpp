/////////////////////////////////////////////////////////////////////////////////////////
/// @file GomokuBoard.hpp
///
/// GomokuBoard class implementation.
///
/// @par Full Description.
/// Providing board for gomoku game.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 06-Jan-2015 Initial revision.
/// - zhalat 26-Sep-2016 Quick access for field's neighbourhood.
/// @endif
///
///    @ingroup.
///
/// @par non-Copyright (c) 2015 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <sstream>
#include "string"
#include <assert.h>  // For assert.

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "GomokuBoard.hpp"    // GomokuBoard declaration.
#include "BoardIterator.hpp"  // For BoardIterator declaration.

// FORWARD REFERENCES
using std::string;

/// Constructor for GomokuBoard.
GomokuBoard::GomokuBoard(uint32_t size)
{
    // Prevent creating Gomoku board if MAX_GOMOKU_BOARD_SIZE exceeded or 0.
    std::ostringstream s;
    s << "size exceed - max limit. Max: " << MAX_GOMOKU_BOARD_SIZE;
    string s_throw = s.str();
    if(size > MAX_GOMOKU_BOARD_SIZE || size < 1)
        throw s_throw;

    using namespace graph;

    // Create graph for Gomoku board.
    const uint32_t graphSize = size * size;
    m_pBoardStructure        = new Graph(graphSize);
    assert(m_pBoardStructure);

    m_Size = size;

    // Connect graph node to create Gomoku board square of size x size.
    for(Node i = 0; i < size; ++i)
    {
        for(Node j = 0; j < size; ++j)
        {
            // Left-up corner.
            if(0 == i && 0 == j)
            {
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size + 1, Graph::EdgeConnect);
            }
            // Right-up corner.
            else if(0 == i && (size - 1) == j)
            {
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size - 1, Graph::EdgeConnect);
            }
            // Left-down corner.
            else if((size - 1) == i && 0 == j)
            {
                m_pBoardStructure->AddEdge(size * i + j, size * (i - 1) + j, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * (i - 1) + j + 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
            }
            // Right-down corner.
            else if((size - 1) == i && (size - 1) == j)
            {
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
            }
            // North
            else if(0 == i)
            {
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size + 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
            }
            // South
            else if((size - 1) == i)
            {
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size + 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
            }
            // West
            else if(0 == j)
            {
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size + 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size + 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
            }
            // East
            else if((size - 1) == j)
            {
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
            }
            // Rest in the middle
            else
            {
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - size + 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size + 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j + size - 1, Graph::EdgeConnect);
                m_pBoardStructure->AddEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
            }

            // Set board's fields as not occupied (NONE).
            m_pBoardStructure->Set_node_value(size * i + j, static_cast<NodeVal>(PLAYER_EMPTY));
        }
    }

    // Create iterator for board
    m_pIterator = new BoardIterator(*m_pBoardStructure);

    // Create an array for quick access to neighbors for each node.
    /// Note: You can fetch the same data by GetNeighborhood(const PositionXY)
    /// but this should be more effective.
    m_pNeighbours            = new Neighbours[graphSize];
    Neighbours * pNeighbours = &m_pNeighbours[0];

    for(uint32_t i = 0; i < graphSize; ++i, pNeighbours++)
    {
        pNeighbours->m_Field = static_cast<PositionField>(i);

        uint32_t index = 0;

        const vector<Node> neighboursList = m_pBoardStructure->Neighbors(static_cast<Node>(i));
        assert(neighboursList.size() <= MAX_NEIGHBOURS);
        for(vector<Node>::const_iterator cit = neighboursList.begin(); cit != neighboursList.end(); ++cit)
        {
            pNeighbours->m_Neighbourhood[index++] = *cit;
        }

        pNeighbours->m_NeighbourhoodSize = neighboursList.size();
    }
}

/// Copy constructor.
GomokuBoard::GomokuBoard(const GomokuBoard & rBoard)
{
    m_Size = rBoard.m_Size;

    m_MoveHistory = rBoard.m_MoveHistory;

    // Create board graph on the base of reference graph.
    m_pBoardStructure = new graph::Graph(*rBoard.m_pBoardStructure);

    // Create iterator for board
    m_pIterator = new BoardIterator(*m_pBoardStructure);

    // Create and copy Neighborhood of each fields for quick access.
    m_pNeighbours                  = new Neighbours[m_Size * m_Size];
    const uint32_t regionSizeToCpy = sizeof(Neighbours) * m_Size * m_Size;
    memcpy(m_pNeighbours, rBoard.m_pNeighbours, regionSizeToCpy);

    // Copy observers.
    // m_ObserverClient = rBoard.m_ObserverClient;
}

/// Put a move.
bool GomokuBoard::PutMove(const PositionXY xy, const Player player)
{
    bool retVal = false;

    const PositionField field(this->GetSize(), xy);

    // Validate input parameters. Player musn't be NONE.
    bool isParameterValid = (IsOnBoard(xy)) && (PLAYER_EMPTY != player);

    if(!isParameterValid)
    {
        retVal = false;
    }
    else if(PLAYER_EMPTY == m_pBoardStructure->Get_node_value(field))
    {
        // Put current move on board.
        m_pBoardStructure->Set_node_value(field, static_cast<graph::NodeVal>(player));

        // Save position of this move.
        m_MoveHistory.push_back(xy);

        retVal = true;
    }

    return retVal;
}

/// Put a move.
bool GomokuBoard::PutMove(const PositionField field, const Player player)
{
    bool retVal = false;

    // Validate input parameters. Player musn't be NONE.
    bool isParameterValid = (IsOnBoard(field)) && (PLAYER_EMPTY != player);

    if(!isParameterValid)
    {
        retVal = false;
    }
    else if(PLAYER_EMPTY == m_pBoardStructure->Get_node_value(field))
    {
        // Put current move on board & notify observers.
        m_pBoardStructure->Set_node_value(field, static_cast<graph::NodeVal>(player));
        Announce();

        // Save position of this move.
        const PositionXY xy = PositionXY(this->GetSize(), field);
        m_MoveHistory.push_back(xy);

        retVal = true;
    }

    return retVal;
}

/// Returns player who occupies given position.
Board::Player GomokuBoard::GetMove(const PositionXY xy) const
{
    // Validate input parameters.
    if(false == IsOnBoard(xy))
    {
        cout << "stop" << endl;
    }

    assert(IsOnBoard(xy));

    Player retVal = PLAYER_EMPTY;

    // Convert xy to field representation.
    PositionField field(this->GetSize(), xy);

    // Check to whom given field belongs to.
    retVal = static_cast<Player>(m_pBoardStructure->Get_node_value(field));

    return retVal;
}

/// Returns player who occupies given field.
Board::Player GomokuBoard::GetMove(const PositionField field) const
{
    // Validate input parameters.
    assert(IsOnBoard(field));

    Player retVal = PLAYER_EMPTY;

    // Check to whom given field belongs to.
    retVal = static_cast<Player>(m_pBoardStructure->Get_node_value(field));

    return retVal;
}

/// Removes move.
bool GomokuBoard::RemoveMove(const PositionXY xy) const
{
    assert(IsOnBoard(xy));

    bool retVal = false;

    const PositionField field(this->GetSize(), xy);

    // Check if given position is free.
    if(PLAYER_EMPTY != m_pBoardStructure->Get_node_value(field))
    {
        m_pBoardStructure->Set_node_value(field, static_cast<graph::NodeVal>(PLAYER_EMPTY));
        retVal = true;
    }

    return retVal;
}

/// Removes N last movies.
bool GomokuBoard::RemoveNLastMove(const int n)
{
    assert(n >= 0);
    bool retVal = false;

    for(uint32_t i = 0; i < n; ++i)
    {
        const PositionXY xy = m_MoveHistory.back();
        m_MoveHistory.pop_back();
        retVal = RemoveMove(xy);

        if(!retVal)
        {
            break;
        }
    }

    return retVal;
}

/// Last move being put into board.
bool GomokuBoard::GetLastMove(PositionXY & xy) const
{
    bool retVal = false;

    // Check if there are move on the board.
    if(m_MoveHistory.size() > 0)
    {
        retVal = true;

        xy = m_MoveHistory.back();
    }

    return retVal;
}

/// First move being put into board.
bool GomokuBoard::GetFirstMove(PositionXY & xy) const
{
    bool retVal = false;

    // Check if there are no moves on the board.
    if(m_MoveHistory.size() > 0)
    {
        retVal = true;

        xy = m_MoveHistory.front();
    }

    return retVal;
}

/// Gets number of movies on the borad.
uint32_t GomokuBoard::GetMoveNumber() const
{
    return m_MoveHistory.size();
}

/// Compute amount of vacant fields.
uint32_t GomokuBoard::VacantFields() const
{
    using namespace graph;

    uint32_t retVal = 0;

    // Go through all fields of board.
    for(Node i = 0; i < m_Size; ++i)
    {
        for(Node j = 0; j < m_Size; ++j)
        {
            const PositionXY xy(i, j);
            const PositionField field(this->GetSize(), xy);

            // Count vacant fields.
            if(PLAYER_EMPTY == m_pBoardStructure->Get_node_value(field))
            {
                ++retVal;
            }
        }
    }

    return retVal;
}

/// Distance to an edge of board.
uint32_t GomokuBoard::EdgeDistance(const PositionXY xy, const Direction direction) const
{
    uint32_t retVal = 0;

    // Don't analyze sth which is out of board.
    assert(IsOnBoard(xy));

    PositionXY tempXY = xy;

    for(;;)
    {
        // Prevent going out of board frame.
        if(!CanIGo(tempXY, direction))
        {
            break;
        }

        // Crawl towards the edge.
        GoDirection(tempXY, direction);

        ++retVal;
    }

    return retVal;
}

/// Distance to neighbour.
int32_t GomokuBoard::NeighbourDistance(const PositionXY xy, const Direction direction, const Player player) const
{
    int32_t retVal = 0;

    // Don't analyze sth which is out of board.
    assert(IsOnBoard(xy));

    PositionXY tempXY = xy;

    for(;;)
    {
        // Check if we reached the edge of board. If so, stop counting.
        if(!CanIGo(tempXY, direction))
        {
            retVal = NO_NEIGHBOR_FOUND;
            break;
        }

        // Crawl towards specified directon.
        GoDirection(tempXY, direction);

        // Check who current position belongs to.
        const Player currentPlayer = GetMove(tempXY);

        if(PLAYER_EMPTY == currentPlayer)  // this position is empt so, go further.
        {
            ++retVal;
        }
        else if(currentPlayer == player)  // player has been encauntered. Stop browsing.
        {
            break;
        }
        else  // !player has been encauntered. Stop browsing.
        {
            retVal = OPPONENT_NEIGHBOR_FOUND;
            break;
        }
    }

    return retVal;
}

/// From given position, checks how many the same figure (X or O) are placed in a row.
uint32_t GomokuBoard::InRow(const PositionXY xy, const Direction direction) const
{
    int32_t retVal = 0;

    // Don't analyze sth which is out of board.
    assert(IsOnBoard(xy));

    PositionXY tempXY = xy;

    // Remember who's field. This player will be matter of finding.
    const Player playerInRow = GetMove(xy);

    if(PLAYER_EMPTY != playerInRow)
    {
        // It's assumed that xy points player move. This will be the first element of row.
        retVal = 1;

        for(;;)
        {
            if(!CanIGo(tempXY, direction))  // Check if we can go further
            {
                break;
            }
            else
            {
                GoDirection(tempXY, direction);  // Crawl towards specified direction.

                if(playerInRow == GetMove(tempXY))  // Check if who's move here.
                {
                    ++retVal;
                }
                else
                {
                    break;
                }
            }
        }
    }

    return retVal;
}

/// Checks if position is on the edge of board.
Board::OnEdge GomokuBoard::IsOnEdge(const PositionXY xy) const
{
    // Don't analyze sth which is out of board.
    assert(IsOnBoard(xy));

    OnEdge retVal = EDGE_NONE;

    // Check where on the boards' frame xy is located.
    if((0 == xy.m_x) && (0 == xy.m_y))  // up left corner.
    {
        retVal = CORNER_UP_LEFT;
    }
    else if((0 == xy.m_x) && ((m_Size - 1) == xy.m_y))  // up right corner.
    {
        retVal = CORNER_UP_RIGHT;
    }
    else if(((m_Size - 1) == xy.m_x) && (0 == xy.m_y))
    {
        retVal = CORNER_DOWN_LEFT;
    }
    else if(((m_Size - 1) == xy.m_x) && ((m_Size - 1) == xy.m_y))
    {
        retVal = CORNER_DOWN_RIGHT;
    }
    else if(0 == xy.m_x)
    {
        retVal = EDGE_UP;
    }
    else if((m_Size - 1) == xy.m_x)
    {
        retVal = EDGE_DOWN;
    }
    else if(0 == xy.m_y)
    {
        retVal = EDGE_LEFT;
    }
    else if((m_Size - 1) == xy.m_y)
    {
        retVal = EDGE_RIGHT;
    }

    return retVal;
}

/// Checks if position is on board.
bool GomokuBoard::IsOnBoard(const PositionXY xy) const
{
    const bool isInputParamValid = (xy.m_x < m_Size) && (xy.m_y < m_Size);
    return isInputParamValid;
}

bool GomokuBoard::IsOnBoard(const PositionField field) const
{
    const bool isInputParamValid = (field.m_field < (m_Size * m_Size));
    return isInputParamValid;
}

/// Check if moving towards direction is possible.
bool GomokuBoard::CanIGo(const PositionXY xy, const Direction direction) const
{
    PositionXY tempXY = xy;
    GoDirection(tempXY, direction);

    return IsOnBoard(tempXY);
}

/// Go to one step toward direction.
void GomokuBoard::GoDirection(PositionXY & xy, const Direction direction, const uint32_t steps) const
{
    // Crawl towards the edge.
    switch(direction)
    {
        case UP:
            xy.m_x -= steps;
            break;

        case DOWN:
            xy.m_x += steps;
            break;

        case LEFT:
            xy.m_y -= steps;
            break;

        case RIGHT:
            xy.m_y += steps;
            break;

        case UP_RIGHT:
            xy.m_x -= steps;
            xy.m_y += steps;
            break;

        case UP_LEFT:
            xy.m_x -= steps;
            xy.m_y -= steps;
            break;

        case DOWN_RIGHT:
            xy.m_x += steps;
            xy.m_y += steps;
            break;

        case DOWN_LEFT:
            xy.m_x += steps;
            xy.m_y -= steps;
            break;

        default:
            assert(false);
    }
}

/// Clone current state of Board.
Board & GomokuBoard::Clone() const
{
    Board * retVal = new GomokuBoard(*this);
    assert(retVal);

    return *retVal;
}

/// Gets the neighborhood of provided position.
const Board::Neighbours & GomokuBoard::GetNeighborhood(const PositionField field) const
{
    const uint32_t index = static_cast<uint32_t>(field);
    assert((m_Size * m_Size) > index);

    const Board::Neighbours & retVal = m_pNeighbours[index];
    return retVal;
}

/// Gets the neighborhood of provided position.
vector<graph::Node> GomokuBoard::GetNeighborhood(const PositionXY xy) const
{
#warning "Should be retval reference & ??"
    PositionField field        = PositionField(this->GetSize(), xy);
    vector<graph::Node> retVal = m_pBoardStructure->Neighbors(field);
    return retVal;
}

/// Revert board to initial state.
void GomokuBoard::ResetInstance()
{
    using namespace graph;
    for(Node i = 0; i < m_Size; ++i)
    {
        for(Node j = 0; j < m_Size; ++j)
        {
            // Set board's fields as not occupied (NONE).
            m_pBoardStructure->Set_node_value(m_Size * i + j, static_cast<NodeVal>(PLAYER_EMPTY));
        }
    }

    m_MoveHistory.clear();
    // m_pBoardStructure->ResetInstance();
    m_pIterator->SetToBase();
}

/// Observer register.
void GomokuBoard::RegisterObserver(const Observer::ObserverIf & rObserver)
{
    m_ObserverClient.push_back(&rObserver);
}

/// Removing observer.
bool GomokuBoard::RemoveObserver(const Observer::ObserverIf & rObserver)
{
    bool retVal = false;

    // Remove from the list iff it exists.
    for(std::vector<const Observer::ObserverIf *>::iterator it = m_ObserverClient.begin(); it != m_ObserverClient.end();
        ++it)
    {
        if(&rObserver == *it)
        {
            m_ObserverClient.erase(it);
            retVal = true;
            break;
        }
    }

    return retVal;
}

/// Notify observers.
void GomokuBoard::Announce() const
{
    // Notify all observers.
    for(std::vector<const Observer::ObserverIf *>::const_iterator cit = m_ObserverClient.begin();
        cit != m_ObserverClient.end(); ++cit)
    {
        (*cit)->Update();
    }
}

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
