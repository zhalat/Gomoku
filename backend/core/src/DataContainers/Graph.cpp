#include <string.h>
#include "DataContainers/Graph.h"
#include "DataContainers/GraphIterator.h"

using namespace graph;
using std::vector;

Graph::Graph(Node size) : m_size(size)
{
    m_ppEdgeMatrix = NULL;
    m_pNodeValue   = NULL;

    if(0 == size)
        throw "Invalid parameter - m_size can't be 0";

    m_ppEdgeMatrix = new EdgeVal *[size];
    for(Node i = 0; i < size; i++)
        m_ppEdgeMatrix[i] = new EdgeVal[size];
    m_pNodeValue = new NodeVal[size];

    for(Node i = 0; i < size; i++)
    {
        m_pNodeValue[i] = NodeValueInit;
        for(Node j = 0; j < size; j++)
            if(i == j)
                m_ppEdgeMatrix[i][j] = 0;
            else
                m_ppEdgeMatrix[i][j] = EdgeInit;
    }
    m_edgeCntr = 0;

    m_pIterator = new GraphIterator(m_pNodeValue, size);
}

Graph::Graph(const Graph & g)
{
    m_ppEdgeMatrix = NULL;
    m_pNodeValue   = NULL;
    this->m_size   = g.m_size;
    this->m_edgeCntr     = g.m_edgeCntr;

    m_ppEdgeMatrix = new EdgeVal *[m_size];
    for(Node i = 0; i < m_size; i++)
    {
        m_ppEdgeMatrix[i] = new EdgeVal[m_size];
        memcpy(&m_ppEdgeMatrix[i][0], &g.m_ppEdgeMatrix[i][0], this->m_size * sizeof(EdgeVal));
    }

    m_pNodeValue = new NodeVal[m_size];
    memcpy(&m_pNodeValue[0], &g.m_pNodeValue[0], this->m_size * sizeof(NodeVal));

    m_pIterator = new GraphIterator(m_pNodeValue, m_size);
}

Graph::Graph(Graph&& g)
{
    this->m_size   = g.m_size;
    this->m_edgeCntr     = g.m_edgeCntr;
    m_ppEdgeMatrix = g.m_ppEdgeMatrix;
    m_pNodeValue = g.m_pNodeValue;

    g.m_ppEdgeMatrix = nullptr;
    g.m_pNodeValue = nullptr;
}

Graph::~Graph()
{
    delete[] m_pNodeValue;
    m_pNodeValue = NULL;

    if(m_ppEdgeMatrix != NULL)
    {
        for(Node i = 0; i < m_size; i++)
            delete[] m_ppEdgeMatrix[i];
    }
    delete[] m_ppEdgeMatrix;
    m_ppEdgeMatrix = NULL;
    m_edgeCntr           = 0;

    delete m_pIterator;
    m_pIterator = NULL;
}

bool Graph::addEdge(Node x, Node y, EdgeVal a)
{
    if((x >= m_size) || (y >= m_size) || (x == y))
        return false;
    // See if the edge already exists.
    if(m_ppEdgeMatrix[x][y] != EdgeInit)
        return false;

    m_ppEdgeMatrix[x][y] = a;
    m_ppEdgeMatrix[y][x] = a;
    m_edgeCntr++;
    return true;
}

bool Graph::deleteEdge(Node x, Node y)
{
    // Argument validation.
    if((x >= m_size) || (y >= m_size) || (x == y))
        return false;
    // See if the edge  exists.
    if(m_ppEdgeMatrix[x][y] == EdgeInit)
        return false;

    m_ppEdgeMatrix[x][y] = EdgeInit;
    m_ppEdgeMatrix[y][x] = EdgeInit;
    m_edgeCntr--;
    return true;
}

bool Graph::adjacent(Node x, Node y) const
{
    if((x >= m_size) || (y >= m_size))
        return false;
    if(m_ppEdgeMatrix[x][y] != EdgeInit)
        return true;
    else
        return false;
}

unsigned int Graph::getEdgeCntr() const
{
    return m_edgeCntr;
}

vector<Node> Graph::neighbors(Node k) const
{
    vector<Node> vlist;
    for(Node i = 0; i < m_size; i++)
    {
        if(i == k)
            continue;
        else if(m_ppEdgeMatrix[k][i] != EdgeInit)
        {
            vlist.push_back(i);
        }
    }
    return vlist;
}

NodeVal Graph::getNodeValue(Node k) const
{
    return m_pNodeValue[k];
}

void Graph::setNodeValue(Node k, NodeVal a)
{
    if(k < m_size)
        m_pNodeValue[k] = a;
}

EdgeVal Graph::getEdgeValue(Node x, Node y) const
{
    return m_ppEdgeMatrix[x][y];
}

bool Graph::setEdgeValue(Node x, Node y, EdgeVal a)
{
    if((x >= m_size) || (y >= m_size))
        return false;
    else
    {
        m_ppEdgeMatrix[x][y] = a;
        m_ppEdgeMatrix[y][x] = a;
    }
    return true;
}

IIterator<graph::Node> * Graph::getIterator() const
{
    return m_pIterator;
}

void Graph::resetInstance()
{
    m_pIterator->backToBegin();

    for(Node i = 0; i < m_size; i++)
    {
        m_pNodeValue[i] = NodeValueInit;
        for(Node j = 0; j < m_size; j++)
            if(i == j)
                m_ppEdgeMatrix[i][j] = 0;
            else
                m_ppEdgeMatrix[i][j] = EdgeInit;
    }
    m_edgeCntr = 0;
}