#include <string.h>
#include "Graph.hpp"
#include "GraphIterator.hpp"

using namespace graph;
using std::vector;

Graph::Graph(Node size) : size(size)
{
    ppEdgeMatrix = NULL;
    pNodeValue   = NULL;

    if(0 == size)
        throw "Invalid parameter - size can't be 0";

    ppEdgeMatrix = new EdgeVal *[size];
    for(Node i = 0; i < size; i++)
        ppEdgeMatrix[i] = new EdgeVal[size];
    pNodeValue = new NodeVal[size];

    for(Node i = 0; i < size; i++)
    {
        pNodeValue[i] = NodeValueInit;
        for(Node j = 0; j < size; j++)
            if(i == j)
                ppEdgeMatrix[i][j] = 0;
            else
                ppEdgeMatrix[i][j] = EdgeInit;
    }
    Ed = 0;

    m_pIterator = new GraphIterator(pNodeValue, size);
}

Graph::Graph(const Graph & _g)
{
    ppEdgeMatrix = NULL;
    pNodeValue   = NULL;
    this->size   = _g.size;
    this->Ed     = _g.Ed;

    ppEdgeMatrix = new EdgeVal *[size];
    for(Node i = 0; i < size; i++)
    {
        ppEdgeMatrix[i] = new EdgeVal[size];
        memcpy(&ppEdgeMatrix[i][0], &_g.ppEdgeMatrix[i][0], this->size * sizeof(EdgeVal));
    }

    pNodeValue = new NodeVal[size];
    memcpy(&pNodeValue[0], &_g.pNodeValue[0], this->size * sizeof(NodeVal));

    m_pIterator = new GraphIterator(pNodeValue, size);
}

Graph::~Graph()
{
    delete[] pNodeValue;
    pNodeValue = NULL;

    if(ppEdgeMatrix != NULL)
    {
        for(Node i = 0; i < size; i++)
            delete[] ppEdgeMatrix[i];
    }
    delete[] ppEdgeMatrix;
    ppEdgeMatrix = NULL;
    Ed           = 0;

    delete m_pIterator;
    m_pIterator = NULL;
}

bool Graph::AddEdge(Node x, Node y, EdgeVal a)
{
    if((x >= size) || (y >= size) || (x == y))
        return false;
    // See if the edge already exists.
    if(ppEdgeMatrix[x][y] != EdgeInit)
        return false;

    ppEdgeMatrix[x][y] = a;
    ppEdgeMatrix[y][x] = a;
    Ed++;
    return true;
}

bool Graph::DeleteEdge(Node x, Node y)
{
    // Argument validation.
    if((x >= size) || (y >= size) || (x == y))
        return false;
    // See if the edge  exists.
    if(ppEdgeMatrix[x][y] == EdgeInit)
        return false;

    ppEdgeMatrix[x][y] = EdgeInit;
    ppEdgeMatrix[y][x] = EdgeInit;
    Ed--;
    return true;
}

bool Graph::Adjacent(Node x, Node y)
{
    if((x >= size) || (y >= size))
        return false;
    if(ppEdgeMatrix[x][y] != EdgeInit)
        return true;
    else
        return false;
}

unsigned int Graph::E(void)
{
    return Ed;
}

vector<Node> Graph::Neighbors(Node k)
{
    vector<Node> vlist;
    for(Node i = 0; i < size; i++)
    {
        if(i == k)
            continue;
        else if(ppEdgeMatrix[k][i] != EdgeInit)
        {
            vlist.push_back(i);
        }
    }
    return vlist;
}

NodeVal Graph::Get_node_value(Node k)
{
    return pNodeValue[k];
}

void Graph::Set_node_value(Node k, NodeVal a)
{
    if(k < size)
        pNodeValue[k] = a;
}

EdgeVal Graph::Get_edge_value(Node x, Node y)
{
    return ppEdgeMatrix[x][y];
}

bool Graph::Set_edge_value(Node x, Node y, EdgeVal a)
{
    if((x >= size) || (y >= size))
        return false;
    else
    {
        ppEdgeMatrix[x][y] = a;
        ppEdgeMatrix[y][x] = a;
    }
    return true;
}

IteratorIf<graph::Node> * Graph::GetIterator() const
{
    return m_pIterator;
}

void Graph::ResetInstance()
{
    m_pIterator->SetToBase();

    for(Node i = 0; i < size; i++)
    {
        pNodeValue[i] = NodeValueInit;
        for(Node j = 0; j < size; j++)
            if(i == j)
                ppEdgeMatrix[i][j] = 0;
            else
                ppEdgeMatrix[i][j] = EdgeInit;
    }
    Ed = 0;
}