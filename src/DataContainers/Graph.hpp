#pragma once
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

}