#include <sstream>
#include <assert.h>
#include <algorithm>
#include "Exceptions.h"
#include "GomokuBoard.h"
#include "BoardIterator.h"

using namespace std;
using namespace graph;

GomokuBoard::GomokuBoard(uint32_t size)
{
    if((size > k_MAX_GOMOKU_BOARD_SIZE) or (size < k_MIN_GOMOKU_BOARD_SIZE))
        throw game_except::General("IBoard size must be <" + string(to_string(k_MIN_GOMOKU_BOARD_SIZE)) + "," + string(to_string(k_MAX_GOMOKU_BOARD_SIZE)) + ">");

    // Create graph for Gomoku board.
    const uint32_t graphSize = size * size;
    m_pBoardStructure        = new Graph(graphSize);
    assert(m_pBoardStructure);

    m_size = size;

    // Connect graph node to create Gomoku board
    for(Node i = 0; i < size; ++i)
    {
        for(Node j = 0; j < size; ++j)
        {
            // Left-up corner.
            if(0 == i && 0 == j)
            {
                m_pBoardStructure->addEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size + 1, Graph::EdgeConnect);
            }
            // Right-up corner.
            else if(0 == i && (size - 1) == j)
            {
                m_pBoardStructure->addEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size - 1, Graph::EdgeConnect);
            }
            // Left-down corner.
            else if((size - 1) == i && 0 == j)
            {
                m_pBoardStructure->addEdge(size * i + j, size * (i - 1) + j, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * (i - 1) + j + 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
            }
            // Right-down corner.
            else if((size - 1) == i && (size - 1) == j)
            {
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
            }
            // North
            else if(0 == i)
            {
                m_pBoardStructure->addEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size + 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
            }
            // South
            else if((size - 1) == i)
            {
                m_pBoardStructure->addEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size + 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
            }
            // West
            else if(0 == j)
            {
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size + 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size + 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
            }
            // East
            else if((size - 1) == j)
            {
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
            }
            // Rest in the middle
            else
            {
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - size + 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size + 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j + size - 1, Graph::EdgeConnect);
                m_pBoardStructure->addEdge(size * i + j, size * i + j - 1, Graph::EdgeConnect);
            }

            // Set board's fields as not occupied (NONE).
            m_pBoardStructure->setNodeValue(size * i + j, static_cast<NodeVal>(PLAYER_EMPTY));
        }
    }

    // Create iterator for board
    m_pIterator = new BoardIterator(*m_pBoardStructure);

    // Create an array for quick access for neighborship.
    /// Note: You can fetch the same data by getNeighborhood(const PositionXY)
    /// but this should be more effective.
    m_pNeighbours            = new Neighbours[graphSize];
    Neighbours * pNeighbours = &m_pNeighbours[0];

    for(uint32_t i = 0; i < graphSize; ++i, pNeighbours++)
    {
        pNeighbours->m_field = PositionXY{static_cast<uint32_t>(i/m_size),static_cast<uint32_t>(i%m_size)};
        uint32_t index = 0;
        const vector<Node> neighboursList = m_pBoardStructure->neighbors(static_cast<Node>(i));
        assert(neighboursList.size() <= k_MAX_NEIGHBOURS);
        pNeighbours->m_neighbourhoodSize = neighboursList.size();
        for(const auto& el: neighboursList)
        {
            pNeighbours->m_neighbourhood[index++] = PositionXY{static_cast<uint32_t>(el/m_size),static_cast<uint32_t>(el%m_size)};
        }
    }
}

GomokuBoard::GomokuBoard(const GomokuBoard & board)
{
    m_size = board.m_size;
    m_moveHistory = board.m_moveHistory;
    m_pBoardStructure = new graph::Graph(*board.m_pBoardStructure);
    m_pIterator = new BoardIterator(*m_pBoardStructure);
    m_pNeighbours                  = new Neighbours[m_size * m_size];
    const uint32_t regionSizeToCpy = sizeof(Neighbours) * m_size * m_size;
    memcpy(m_pNeighbours, board.m_pNeighbours, regionSizeToCpy);

    // Copy observers.
    // m_observerClient = board.m_observerClient;
}

bool GomokuBoard::putMove(const PositionXY xy, const Player player)
{
    bool retVal = false;

    // Validate input parameters. Player musn't be NONE.
    bool isParameterValid = (isOnBoard(xy)) && (PLAYER_EMPTY != player);
    if(!isParameterValid)
    {
        retVal = false;
    }
    else if(PLAYER_EMPTY == m_pBoardStructure->getNodeValue(xy.convert2Linear(m_size)))
    {
        // Put current move on board.
        m_pBoardStructure->setNodeValue(xy.convert2Linear(m_size), static_cast<graph::NodeVal>(player));

        // Save position of this move.
        m_moveHistory.push_back(xy);
        announce();

        retVal = true;
    }

    return retVal;
}

IBoard::Player GomokuBoard::getMove(const PositionXY xy) const
{
    Player retVal = PLAYER_EMPTY;
    if(false == isOnBoard(xy))
    {
        cout << "stop" << endl;
        return retVal;
    }

    retVal = static_cast<Player>(m_pBoardStructure->getNodeValue(xy.convert2Linear(m_size)));
    return retVal;
}

bool GomokuBoard::removeMove(const PositionXY xy)
{
    bool retVal = false;
    if(false==isOnBoard(xy)) return retVal;

    // Check if given position is free.
    if(PLAYER_EMPTY != m_pBoardStructure->getNodeValue(xy.convert2Linear(m_size)))
    {
        m_pBoardStructure->setNodeValue(xy.convert2Linear(m_size), static_cast<graph::NodeVal>(PLAYER_EMPTY));
        retVal = true;
    }

    return retVal;
}

bool GomokuBoard::removeNLastMove(const unsigned n)
{
    bool retVal = false;

    for(uint32_t i = 0; i < n; ++i)
    {
        const PositionXY xy = m_moveHistory.back();
        m_moveHistory.pop_back();
        retVal = removeMove(xy);

        if(!retVal)
        {
            break;
        }
    }

    return retVal;
}

bool GomokuBoard::getLastMove(PositionXY & xy) const
{
    bool retVal = false;

    // Check if there are move on the board.
    if(m_moveHistory.size() > 0)
    {
        retVal = true;

        xy = m_moveHistory.back();
    }

    return retVal;
}

bool GomokuBoard::getFirstMove(PositionXY & xy) const
{
    bool retVal = false;

    // Check if there are no moves on the board.
    if(m_moveHistory.size() > 0)
    {
        retVal = true;

        xy = m_moveHistory.front();
    }

    return retVal;
}

uint32_t GomokuBoard::getMoveNumber() const
{
    return m_moveHistory.size();
}

uint32_t GomokuBoard::vacantFields() const
{
    uint32_t retVal = 0;

    // Go through all fields of board.
    for(size_t i = 0; i < m_size; ++i)
    {
        for(size_t j = 0; j < m_size; ++j)
        {
            const PositionXY xy(i, j);
            // Count vacant fields.
            if(PLAYER_EMPTY == m_pBoardStructure->getNodeValue(xy.convert2Linear(m_size)))
            {
                ++retVal;
            }
        }
    }

    return retVal;
}

uint32_t GomokuBoard::edgeDistance(const PositionXY xy, const Direction direction) const
{
    uint32_t retVal = 0;

    // Don't analyze sth which is out of board.
    assert(isOnBoard(xy));

    PositionXY tempXY = xy;

    for(;;)
    {
        // Prevent going out of board frame.
        if(!canIGo(tempXY, direction))
        {
            break;
        }

        // Crawl towards the edge.
        goDirection(tempXY, direction);

        ++retVal;
    }

    return retVal;
}

int32_t GomokuBoard::neighbourDistance(const PositionXY xy, const Direction direction, const Player player) const
{
    int32_t retVal = 0;

    // Don't analyze sth which is out of board.
    assert(isOnBoard(xy));

    PositionXY tempXY = xy;

    for(;;)
    {
        // Check if we reached the edge of board. If so, stop counting.
        if(!canIGo(tempXY, direction))
        {
            retVal = k_NEIGHBOR_NOT_FOUND;
            break;
        }

        // Crawl towards specified directon.
        goDirection(tempXY, direction);

        // Check who current position belongs to.
        const Player currentPlayer = getMove(tempXY);

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
            retVal = k_NEIGHBOR_OPPONENT_FOUND;
            break;
        }
    }

    return retVal;
}

uint32_t GomokuBoard::inRow(const PositionXY xy, const Direction direction) const
{
    int32_t retVal = 0;

    // Don't analyze sth which is out of board.
    assert(isOnBoard(xy));

    PositionXY tempXY = xy;

    // Remember who's field. This player will be matter of finding.
    const Player playerInRow = getMove(xy);

    if(PLAYER_EMPTY != playerInRow)
    {
        // It's assumed that xy points player move. This will be the first element of row.
        retVal = 1;

        for(;;)
        {
            if(!canIGo(tempXY, direction))  // Check if we can go further
            {
                break;
            }
            else
            {
                goDirection(tempXY, direction);  // Crawl towards specified direction.

                if(playerInRow == getMove(tempXY))  // Check if who's move here.
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

IBoard::OnEdge GomokuBoard::isOnEdge(const PositionXY xy) const
{
    // Don't analyze sth which is out of board.
    assert(isOnBoard(xy));

    OnEdge retVal = EDGE_NONE;

    // Check where on the boards' frame xy is located.
    if((0 == xy.m_x) && (0 == xy.m_y))  // up left corner.
    {
        retVal = CORNER_UP_LEFT;
    }
    else if((0 == xy.m_x) && ((m_size - 1) == xy.m_y))  // up right corner.
    {
        retVal = CORNER_UP_RIGHT;
    }
    else if(((m_size - 1) == xy.m_x) && (0 == xy.m_y))
    {
        retVal = CORNER_DOWN_LEFT;
    }
    else if(((m_size - 1) == xy.m_x) && ((m_size - 1) == xy.m_y))
    {
        retVal = CORNER_DOWN_RIGHT;
    }
    else if(0 == xy.m_x)
    {
        retVal = EDGE_UP;
    }
    else if((m_size - 1) == xy.m_x)
    {
        retVal = EDGE_DOWN;
    }
    else if(0 == xy.m_y)
    {
        retVal = EDGE_LEFT;
    }
    else if((m_size - 1) == xy.m_y)
    {
        retVal = EDGE_RIGHT;
    }

    return retVal;
}

bool GomokuBoard::isOnBoard(const PositionXY xy) const
{
    const bool isInputParamValid = (xy.m_x < m_size) && (xy.m_y < m_size);
    return isInputParamValid;
}

bool GomokuBoard::canIGo(const PositionXY xy, const Direction direction) const
{
    PositionXY tempXY = xy;
    goDirection(tempXY, direction);

    return isOnBoard(tempXY);
}

void GomokuBoard::goDirection(PositionXY & xy, const Direction direction, const uint32_t steps) const
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

std::shared_ptr<IBoard> GomokuBoard::clone() const
{
    std::shared_ptr<IBoard> retVal = std::make_shared<GomokuBoard>(*this);
    return retVal;
}

vector<graph::Node> GomokuBoard::getNeighborhood(const PositionXY xy) const
{
    return m_pBoardStructure->neighbors(xy.convert2Linear(m_size));
}

void GomokuBoard::resetInstance()
{
    for(Node i = 0; i < m_size; ++i)
    {
        for(Node j = 0; j < m_size; ++j)
        {
            m_pBoardStructure->setNodeValue(m_size * i + j, static_cast<NodeVal>(PLAYER_EMPTY));
        }
    }

    m_moveHistory.clear();
    m_pIterator->backToBegin();
}

void GomokuBoard::registerObserver(const Observer::IObserver & observer)
{
    auto lambda = [&observer](const Observer::IObserver* it)-> bool
    {
        if(&observer==it)
            return true;
    };

    const auto it = std::find_if(m_observerClient.begin(), m_observerClient.end(),lambda);
    if (it == m_observerClient.end())
    {
        m_observerClient.push_back(&observer);
    }
}

bool GomokuBoard::removeObserver(const Observer::IObserver & observer)
{
    bool retVal = false;

    // remove from the list iff it exists.
    for(std::vector<const Observer::IObserver *>::iterator it = m_observerClient.begin(); it != m_observerClient.end();
        ++it)
    {
        if(&observer == *it)
        {
            m_observerClient.erase(it);
            retVal = true;
            break;
        }
    }

    return retVal;
}

void GomokuBoard::announce() const
{
    for(std::vector<const Observer::IObserver *>::const_iterator cit = m_observerClient.begin();
        cit != m_observerClient.end(); ++cit)
    {
        (*cit)->update();
    }
}
