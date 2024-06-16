#pragma once

#include <assert.h>
#include <queue>
#include <algorithm>

template<typename T, typename Sequence = std::vector<T>, typename Compare = std::less<typename Sequence::value_type>>
class PriorityQueue : public std::priority_queue<T, Sequence, Compare>
{
   public:
    PriorityQueue(uint32_t size) : m_Size(size)
    {
        // nothing to do
    }

    void pushData(const T & rData)
    {
        // If we've reached capacity, find the FIRST smallest object and replace it if 'rData' is larger.
        if(m_Size == this->size())
        {
            // 'c' is the container used by priority_queue and is a protected member.
            auto beg = this->c.begin();
            auto end = this->c.end();
            auto min = std::min_element(beg, end);
            if(rData > *min)
            {
                *min = rData;

                // Re-make the heap, since we 'manually' operated on container.
                // Normally priority queue does it internally.
                std::make_heap(beg, end);
            }
        }
        else
        {
            std::priority_queue<T>::push(rData);
        }
    }

    T popData()
    {
        T retVal = std::priority_queue<T>::top();
        std::priority_queue<T>::pop();
        return retVal;
    }

    T topData()
    {
        T retVal = std::priority_queue<T>::top();
        return retVal;
    }

    uint32_t getSize() const
    {
        uint32_t retVal = this->size();
        return retVal;
    }

    uint32_t getContainerSize() const { return m_Size; }

    void clearAll() { this->c.clear(); }

   private:
    const uint32_t m_Size;
};
