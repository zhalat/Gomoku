#pragma once
#include <assert.h>
#include "Interfaces/IIterator.h"
#include "VectorLight.h"

template<size_t size>
class VectorLightIterator : public IIterator<uint32_t>
{
   public:
    bool hasNext() const override
    {
        bool retVal = false;
        for(uint32_t cntr = m_cntr; cntr < m_cursor; ++cntr)
        {
            if(m_empty == m_dataArray[cntr])         // Skip all cells that are marked as empty (m_empty value).
            {
                continue;
            }
            else
            {
                retVal = true;
                break;
            }
        }

        return retVal; 
    }

    uint32_t getNext()
    {
        const bool isNextOk = hasNext();
        assert(isNextOk);

        // Set cursor for the next non empty data.
        for(; m_empty == m_dataArray[m_cntr]; ++m_cntr);
        const uint32_t retVal = m_dataArray[m_cntr];
        ++m_cntr;
        return retVal;
    }

    uint32_t getIndex() const
    {
        return m_cntr;
    }

    void backToBegin()
    {
        m_cntr = 0;
    }

    VectorLightIterator(const uint32_t (&dataArray)[size], const uint32_t & cursor,
                        const uint32_t emptyVal) :
            m_dataArray(dataArray), m_cursor(cursor), m_cntr(0), m_empty(emptyVal)
    {
        // Nothing to do.
    }

    virtual ~VectorLightIterator() {}

   private:
    const uint32_t (&m_dataArray)[size];
    const uint32_t & m_cursor;
    uint32_t m_cntr;
    const uint32_t m_empty;
};
