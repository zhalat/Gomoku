/*
 * Graph.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: ginar
 */
#include <string.h>
#include "Graph.hpp"
#include "GraphIterator.hpp"

using namespace graph;
using std::vector;

/*
 * @brief    Constructor for graph. Node its connected with itself
 * @param    size of graph
 * @retval    none
 */
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

    // Create iterator for graph.
    m_pIterator = new GraphIterator(pNodeValue, size);
}

/*
 * @brief    Copy constructor for graph.
 * @param    graph to be copied
 * @retval    none
 */
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

    // Create iterator for graph.
    m_pIterator = new GraphIterator(pNodeValue, size);
}

/*
 * @brief    Delete
 * @param    none
 * @retval    none
 */
Graph::~Graph()
{
    // delete node table
    delete[] pNodeValue;
    pNodeValue = NULL;

    // delete connection table
    if(ppEdgeMatrix != NULL)
    {
        for(Node i = 0; i < size; i++)
            delete[] ppEdgeMatrix[i];
    }
    delete[] ppEdgeMatrix;
    ppEdgeMatrix = NULL;
    Ed           = 0;

    // Delete iterator.
    delete m_pIterator;
    m_pIterator = NULL;
}

/*
 * @brief    Add new edge only if doesn't exist. Increment nr of edges
 * @param    x - location of node
 * @param    y - location of node
 * @retval   true-added successfully; false-failure
 */
bool Graph::AddEdge(Node x, Node y, EdgeVal a)
{
    // Argument validation.
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

/*
 * @brief    Delete edge only if exists. Decrement nr of edges
 * @param    x - location of node
 * @param    y - location of node
 * @retval    true-deleted successfully; false-failure
 */
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

/*
 * @brief    Tests whether there is an edge from node x to node y.
 * @param    x - location of node
 * @param    y - location of node
 * @retval    true-there's connection; false-theren's connection
 */
bool Graph::Adjacent(Node x, Node y)
{
    // Argument validation.
    if((x >= size) || (y >= size))
        return false;
    // See if the edge  exists.
    if(ppEdgeMatrix[x][y] != EdgeInit)
        return true;
    else
        return false;
}

/*
 * @brief    Return actual edge number.
 * @param    none
 * @retval    Amount of actual edge
 */
unsigned int Graph::E(void)
{
    return Ed;
}

/*
 * @brief    Return lists k node such that there is an edge from k to kx.
 * @param    node
 * @retval    vector list of connection
 */
vector<Node> Graph::Neighbors(Node k)
{
    vector<Node> vlist;
    // browse thru each nodes to check connections
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

/*
 * @brief    Return nodes' value.
 * @param    node
 * @retval    nodes' value or
 */
NodeVal Graph::Get_node_value(Node k)
{
    return pNodeValue[k];
}

/*
 * @brief    Set nodes' value.
 * @param    node
 * @param    value to node be set
 * @retval    none
 */
void Graph::Set_node_value(Node k, NodeVal a)
{
    // Argument validation.
    if(k < size)
        pNodeValue[k] = a;
}

/*
 * @brief    Get edge between node x and node y.
 * @param    x- node
 * @param    y- node
 * @retval    none
 */
EdgeVal Graph::Get_edge_value(Node x, Node y)
{
    return ppEdgeMatrix[x][y];
}

/*
 * @brief    Set edge between node x and node y.
 * @param    x- node
 * @param    y- node
 * * @param    a- EdgeVal
 * @retval    true- set successfully, false - fail
 */
bool Graph::Set_edge_value(Node x, Node y, EdgeVal a)
{
    // Argument validation.
    if((x >= size) || (y >= size))
        return false;
    else
    {
        ppEdgeMatrix[x][y] = a;
        ppEdgeMatrix[y][x] = a;
    }
    return true;
}

/*
 * @brief    Get iterator.
 * @retval   Pointer to iterator.
 */
IteratorIf<graph::Node> * Graph::GetIterator() const
{
    return m_pIterator;
}

/*
 * @brief    Revert to initial state.
 * @retval   none.
 */
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
