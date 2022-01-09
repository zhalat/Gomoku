
#include <string.h>
#include <cassert>
#include "Graph.h"
#include "GraphIterator.hpp"

using namespace graph;

/*
 * @brief    Constructor for graph. Node it's connected with itself
 * @param    size Number of graph's node
 */
Graph::Graph(Node size) : m_size(size)
{
    m_ppEdgeMatrix = NULL;
    m_pNodeValue   = NULL;

    if(0 == size)
        throw InvalidGraphSizeExcept();

    m_ppEdgeMatrix = new EdgeVal *[size];
    for(Node i = 0; i < size; i++)
        m_ppEdgeMatrix[i] = new EdgeVal[size];
    m_pNodeValue = new NodeVal[size];

    for(Node i = 0; i < size; i++)
    {
        m_pNodeValue[i] = k_nodeInitVal;
        for(Node j = 0; j < size; j++)
            if(i == j)
                m_ppEdgeMatrix[i][j] = k_edgeConnectVal;
            else
                m_ppEdgeMatrix[i][j] = k_edgeDisconnectVal;
    }
    m_edgeCntr = 0;

    // Create iterator for graph.
    m_pIterator = new GraphIterator(m_pNodeValue, size);
}

/*
 * @brief    Copy constructor for graph.
 * @param    graph to be copied
 */
Graph::Graph(const Graph & graph)
{
    m_ppEdgeMatrix   = NULL;
    m_pNodeValue     = NULL;
    this->m_size     = graph.m_size;
    this->m_edgeCntr = graph.m_edgeCntr;

    m_ppEdgeMatrix = new EdgeVal *[m_size];
    for(Node i = 0; i < m_size; i++)
    {
        m_ppEdgeMatrix[i] = new EdgeVal[m_size];
        memcpy(&m_ppEdgeMatrix[i][0], &graph.m_ppEdgeMatrix[i][0], this->m_size * sizeof(EdgeVal));
    }

    m_pNodeValue = new NodeVal[m_size];
    memcpy(&m_pNodeValue[0], &graph.m_pNodeValue[0], this->m_size * sizeof(NodeVal));

    // Create iterator for graph.
    m_pIterator = new GraphIterator(m_pNodeValue, m_size);
}

Graph::~Graph()
{
    // delete node table
    delete[] m_pNodeValue;
    m_pNodeValue = NULL;

    // delete connection table
    if(m_ppEdgeMatrix != NULL)
    {
        for(Node i = 0; i < m_size; i++)
            delete[] m_ppEdgeMatrix[i];
    }
    delete[] m_ppEdgeMatrix;
    m_ppEdgeMatrix = NULL;
    m_edgeCntr     = 0;

    // Delete iterator.
    delete m_pIterator;
    m_pIterator = NULL;
}

/*
 * @brief    Add new edge only if doesn't exist. Increment nr of edges
 * @param    nodeX node x to be connected
 * @param    nodeY node y to be connected
 * @retval   true-added successfully; false-failure
 */
bool Graph::addEdge(Node nodeX, Node nodeY, EdgeVal val)
{
    // Argument validation.
    if((nodeX >= m_size) || (nodeY >= m_size) || (nodeX == nodeY))
        return false;
    // See if the edge already exists.
    if(m_ppEdgeMatrix[nodeX][nodeY] != k_edgeDisconnectVal)
        return false;

    m_ppEdgeMatrix[nodeX][nodeY] = val;
    m_ppEdgeMatrix[nodeY][nodeX] = val;
    m_edgeCntr++;
    return true;
}

/*
 * @brief    Delete edge only if exists. Decrement nr of edges
 * @param    nodeX node x to be disconnected
 * @param    nodeY node y to be disconnected
 * @retval    true-deleted successfully; false-failure
 */
bool Graph::deleteEdge(Node nodeX, Node nodeY)
{
    // Argument validation.
    if((nodeX >= m_size) || (nodeY >= m_size) || (nodeX == nodeY))
        return false;
    // See if the edge  exists.
    if(m_ppEdgeMatrix[nodeX][nodeY] == k_edgeDisconnectVal)
        return false;

    m_ppEdgeMatrix[nodeX][nodeY] = k_edgeDisconnectVal;
    m_ppEdgeMatrix[nodeY][nodeX] = k_edgeDisconnectVal;
    m_edgeCntr--;
    return true;
}

/*
 * @brief    Tests whether there is an edge from node x to node y.
 * @param    nodeX node x to be checked
 * @param    nodeX node y to be checked
 * @retval    true-there's connection; false-theren's connection
 */
bool Graph::adjacent(Node nodeX, Node nodeY) const
{
    // Argument validation.
    if((nodeX >= m_size) || (nodeY >= m_size))
        return false;
    // See if the edge  exists.
    if(m_ppEdgeMatrix[nodeX][nodeY] != k_edgeDisconnectVal)
        return true;
    else
        return false;
}

/*
 * @brief    Get active edge number.
 * @retval   Number of active edges
 */
unsigned int Graph::getEdgeCntr() const
{
    return m_edgeCntr;
}

/*
 * @brief    Return list of nodes heaving connection to given node
 * @param    node
 * @retval   list of nodes connected to node
 */
vector<Node> Graph::getNeighbors(Node node) const
{
    vector<Node> vlist;
    // browse thru each nodes to check connections
    for(Node i = 0; i < m_size; i++)
    {
        if(i == node)
            continue;
        else if(m_ppEdgeMatrix[node][i] != k_edgeDisconnectVal)
        {
            vlist.push_back(i);
        }
    }
    return vlist;
}

/*
 * @brief    Return nodes' value.
 * @param    node
 * @retval   value assigned to node
 */
NodeVal Graph::getNodeValue(Node node) const
{
    return m_pNodeValue[node];
}

/*
 * @brief    Set nodes' value.
 * @param    node Node to be set
 * @param    value of node be set
 */
void Graph::setNodeValue(Node node, NodeVal value)
{
    assert(node < m_size);
    m_pNodeValue[node] = value;
}

/*
 * @brief    Get edge between node x and node y.
 * @param    nodeX
 * @param    nodeY
 */
EdgeVal Graph::getEdgeValue(Node nodeX, Node nodeY) const
{
    return m_ppEdgeMatrix[nodeX][nodeY];
}

/*
 * @brief    Set edge between node x and node y.
 * @param    nodeX
 * @param    nodeY
 * @param    value edge value
 * @retval   true- set successfully, false - fail
 */
bool Graph::setEdgeValue(Node nodeX, Node nodeY, EdgeVal value)
{
    if((nodeX >= m_size) || (nodeY >= m_size))
        return false;
    else if(nodeX == nodeY)
    {
        return false;
    }
    else
    {
        m_ppEdgeMatrix[nodeX][nodeY] = value;
        m_ppEdgeMatrix[nodeY][nodeX] = value;
    }
    return true;
}

/*
 * @brief    Get iterator.
 * @retval   Pointer to iterator.
 */
auto Graph::getIterator() const
{
    return m_pIterator;
}

/*
 * @brief    Revert to initial state.
 * @retval   none.
 */
void Graph::reset()
{
    for(Node i = 0; i < m_size; i++)
    {
        m_pNodeValue[i] = k_nodeInitVal;
        for(Node j = 0; j < m_size; j++)
            if(i == j)
                m_ppEdgeMatrix[i][j] = 0;
            else
                m_ppEdgeMatrix[i][j] = k_edgeDisconnectVal;
    }
    m_edgeCntr = 0;
}
