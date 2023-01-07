/*
 * Graph.hpp
 *
 *  Created on: 4 sty 2014
 *      Author: ginar
 *
 *    Class description:
 *        Graph - abstract data representation.
 *
 *    Interface:
 *
 * */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <climits>
#include "IteratorIf.hpp"

namespace graph {

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

typedef int NodeVal;
typedef unsigned int EdgeVal;
typedef unsigned int Node;

class Graph
{
   public:
    static constexpr int EdgeInit      = UINT_MAX;  // means not connected;
    static constexpr int EdgeConnect   = 0x00;      // means connected;
    static constexpr int NodeValueInit = INT_MIN;
    ;

    Graph(unsigned int size);
    Graph(const Graph & _g);
    virtual ~Graph(void);
    bool AddEdge(Node x, Node y, EdgeVal a);
    bool DeleteEdge(Node x, Node y);
    bool Adjacent(Node x, Node y);
    unsigned int E(void);
    vector<Node> Neighbors(Node k);
    NodeVal Get_node_value(Node k);
    void Set_node_value(Node k, NodeVal a);
    EdgeVal Get_edge_value(Node x, Node y);
    bool Set_edge_value(Node x, Node y, EdgeVal a);
    IteratorIf<graph::Node> * GetIterator() const;
    void ResetInstance();

   private:
    EdgeVal ** ppEdgeMatrix;
    NodeVal * pNodeValue;
    unsigned int Ed;
    unsigned int size;

    // Handler to iterator.
    IteratorIf<graph::Node> * m_pIterator;

    //----My friends-----------------------------------------------------------:
    friend ostream & operator<<(ostream & _stream, Graph & _graph)
    {
        vector<Node> vlist;
        for(Node i = 0; i < _graph.size; i++)
        {
            vlist = _graph.Neighbors(i);
            cout << "Node: " << i;
            for(vector<Node>::iterator it = vlist.begin(); it != vlist.end(); ++it)
                cout << "->" << *it << "(" << _graph.ppEdgeMatrix[i][*it] << ")";
            cout << endl;
        }
        return _stream;
    }
};

}  // namespace graph
#endif /* GRAPH_H_ */

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