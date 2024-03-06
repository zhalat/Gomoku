#pragma once
#include <iostream>
#include <vector>
#include <climits>
#include "Interfaces/IIterator.h"

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
    Graph(const Graph& g);
    Graph(Graph&& g);
    Graph& operator=(const Graph& g)=delete;
    Graph& operator=(const Graph&& g)=delete;
    virtual ~Graph();

    bool addEdge(Node x, Node y, EdgeVal a);
    bool deleteEdge(Node x, Node y);
    bool adjacent(Node x, Node y) const;
    unsigned int getEdgeCntr() const;
    vector<Node> neighbors(Node k) const;
    NodeVal getNodeValue(Node k) const;
    void setNodeValue(Node k, NodeVal a);
    EdgeVal getEdgeValue(Node x, Node y) const;
    bool setEdgeValue(Node x, Node y, EdgeVal a);
    IIterator<graph::Node>* getIterator() const;
    void resetInstance();

   private:
    EdgeVal** m_ppEdgeMatrix;
    NodeVal* m_pNodeValue;
    unsigned int m_edgeCntr;
    unsigned int m_size;

    IIterator<graph::Node>* m_pIterator;

    //----My friends-----------------------------------------------------------:
    friend ostream & operator<<(ostream & stream, const Graph& graph)
    {
        vector<Node> vlist;
        for(Node i = 0; i < graph.m_size; i++)
        {
            vlist = graph.neighbors(i);
            cout << "Node: " << i;
            for(vector<Node>::iterator it = vlist.begin(); it != vlist.end(); ++it)
                cout << "->" << *it << "(" << graph.m_ppEdgeMatrix[i][*it] << ")";
            cout << endl;
        }
        return stream;
    }
};

}