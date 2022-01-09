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

using NodeVal = int;
using EdgeVal = unsigned int;
using Node    = unsigned int;

struct InvalidGraphSizeExcept : public std::exception
{
    [[nodiscard]] const char * what() const noexcept override { return "Invalid parameter - size can't be 0"; }
};

class Graph
{
   public:
    static constexpr int k_edgeDisconnectVal = UINT_MAX;  // means not connected;
    static constexpr int k_edgeConnectVal    = 0x00;      // means connected;
    static constexpr int k_nodeInitVal       = INT_MIN;

    Graph(unsigned int size);
    Graph(const Graph & graph);
    virtual ~Graph(void);

    bool addEdge(Node nodeX, Node nodeY, EdgeVal val);
    bool deleteEdge(Node nodeX, Node nodeY);
    bool adjacent(Node nodeX, Node nodeY) const;
    unsigned int getEdgeCntr() const;
    vector<Node> getNeighbors(Node node) const;
    NodeVal getNodeValue(Node node) const;
    void setNodeValue(Node node, NodeVal value);
    EdgeVal getEdgeValue(Node x, Node y) const;
    bool setEdgeValue(Node nodeX, Node nodeY, EdgeVal value);
    auto getIterator() const;
    void reset();

   private:
    EdgeVal ** m_ppEdgeMatrix;
    NodeVal * m_pNodeValue;
    unsigned int m_edgeCntr;
    unsigned int m_size;

    // Handler to iterator.
    IteratorIf<graph::Node> * m_pIterator;

    //----My friends-----------------------------------------------------------:
    friend ostream & operator<<(ostream & stream, Graph & graph)
    {
        vector<Node> vlist;
        for(Node i = 0; i < graph.m_size; i++)
        {
            vlist = graph.getNeighbors(i);
            cout << "Node: " << i;
            for(vector<Node>::iterator it = vlist.begin(); it != vlist.end(); ++it)
                cout << "->" << *it << "(" << graph.m_ppEdgeMatrix[i][*it] << ")";
            cout << endl;
        }
        return stream;
    }
};

}  // namespace graph
