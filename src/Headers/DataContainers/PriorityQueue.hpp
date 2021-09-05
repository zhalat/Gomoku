#ifndef PRIORITY_QUEUE_CONTAINER
#define PRIORITY_QUEUE_CONTAINER

#include <assert.h>   // For assert.
#include <queue>      // For priority_queue
#include <algorithm>  // For std::min_element

template<typename T, typename Sequence = std::vector<T>, typename Compare = std::less<typename Sequence::value_type>>
class PriorityQueue : public std::priority_queue<T, Sequence, Compare>
{
   public:
    PriorityQueue(uint32_t size) : m_Size(size)
    {
        // nothing to do
    }

    void PushData(const T & rData)
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

    T PopData()
    {
        T retVal = std::priority_queue<T>::top();
        std::priority_queue<T>::pop();
        return retVal;
    }

    uint32_t GetSize() const
    {
        uint32_t retVal = this->size();
        return retVal;
    }

    uint32_t GetContainerSize() const { return m_Size; }

    void ClearAll() { this->c.clear(); }

   private:
    const uint32_t m_Size;
};
#endif  // PRIORITY_QUEUE_CONTAINER

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