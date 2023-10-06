#pragma once

#include <assert.h>
#include <string.h>
#include <vector>
#include "Interfaces/IIterator.h"
#include "VectorLightIterator.h"

template<size_t size>
class VectorLight
{
   public:
    void insert(const uint32_t val)
    {
        assert(m_cursor < size);
        assert(val < size);
        m_array[m_cursor] = val;
        m_markArray[val] = m_cursor;
        m_cursor++;
        m_numberOfElement++;
    }

    virtual IIterator<uint32_t>* getIterator() const
    {
        return m_pIterator;
    }

    bool isPresent(const uint32_t val) const
    {
        assert(val < size);
        const bool retVal = (m_initVal != m_markArray[val]);
        return retVal;
    }

    bool remove(const uint32_t val)
    {
        const bool retVal = isPresent(val);
        if(isPresent(val))
        {
            uint32_t index = m_markArray[val];
            m_array[index]   = m_initVal;
            m_markArray[val] = m_initVal;
            m_numberOfElement--;
        }
        return retVal;
    }

    bool isSpace() const
    {
        const bool retVal = (m_cursor < size);
        return retVal;
    }

    uint32_t getNumberOfElements() const
    {
        return m_numberOfElement;
    }
    void clear()
    {
        m_cursor          = 0;
        m_numberOfElement = 0;
        memset(m_array, m_initVal, sizeof(m_array));
        memset(m_markArray, m_initVal, sizeof(m_markArray));
        m_pIterator->backToBegin();
    }

    VectorLight(const uint32_t initVal)
    : m_initVal(initVal)
    {
        memset(m_array, initVal, sizeof(m_array));
        memset(m_markArray, initVal, sizeof(m_markArray));
        m_cursor          = 0;
        m_numberOfElement = 0;

        m_pIterator = new VectorLightIterator<size>(m_array, m_cursor, m_initVal);
    }

    VectorLight(const VectorLight & ref)
    {
        memcpy(m_array, ref.m_array, sizeof(m_array));
        memcpy(m_markArray, ref.m_markArray, sizeof(ref.m_markArray));
        m_cursor          = ref.m_cursor;
        m_numberOfElement = ref.m_numberOfElement;

        m_pIterator = new VectorLightIterator<size>(m_array, m_cursor, m_initVal);
    }

    virtual ~VectorLight()
    {
        delete m_pIterator;
        m_pIterator = NULL;
    }

    VectorLight & operator=(const std::vector<uint32_t> & stlVct)
    {
        // Be sure container size if large enough.
        assert(stlVct.size() <= size);

        for(auto cit = stlVct.begin(); cit != stlVct.end(); ++cit)
        {
            const uint32_t data = static_cast<uint32_t>(*cit);
            this->insert(data);
        }
        return *this;
    }

   private:
    const uint32_t m_initVal;

    uint32_t m_array[size];
    uint32_t m_markArray[size];
    uint32_t m_cursor;
    uint32_t m_numberOfElement;
    IIterator<uint32_t> * m_pIterator;

};
