#pragma once
#include "Interfaces/IIterator.h"
#include "DataContainers/Graph.h"

class GraphIterator : public IIterator<graph::Node>
{
   public:
    inline bool hasNext() const override
    {
        return (m_cntr < m_size);
    }

    inline graph::Node getNext() override
    {
        const bool isNextOk = hasNext();
        assert(isNextOk);
        const graph::Node retVal = m_collection[m_cntr];
        ++m_cntr;
        return retVal;
    }

    inline uint32_t getIndex() const override
    {
        return m_cntr;
    }

    inline void backToBegin() override { m_cntr = 0; }

    GraphIterator(graph::NodeVal * collection, uint32_t size)
     : m_collection(collection)
     , m_size(size)
    {
        assert(m_collection);
    }

   private:
    graph::NodeVal * const m_collection{nullptr};
    uint32_t m_size {0};
    uint32_t m_cntr {0};
};
