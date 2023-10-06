#pragma once

#include "Interfaces/IIterator.h"
#include "DataContainers/Graph.h"

class BoardIterator : public IIterator<graph::Node>
{
   public:
    inline bool hasNext() const override
    {
        return m_graph.getIterator()->hasNext();
    }
    inline graph::Node getNext() override
    {
        return m_graph.getIterator()->getNext();
    }
    inline uint32_t getIndex() const override
    {
        return m_graph.getIterator()->getIndex();
    }
    inline void backToBegin() override
    {
        return m_graph.getIterator()->backToBegin();
    }

    BoardIterator(graph::Graph & graph) : m_graph(graph){}
    BoardIterator(const BoardIterator &) = delete;
    BoardIterator(const BoardIterator &&) = delete;
    BoardIterator & operator=(const BoardIterator &) = delete;
    BoardIterator & operator=(const BoardIterator &&) = delete;
    ~BoardIterator() = default;

   private:
    const graph::Graph & m_graph;
};
