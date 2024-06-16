#pragma once

#include <assert.h>
#include <string.h>
#include <list>
#include <algorithm>

template<typename T, uint32_t Size>
class VectorUnique
{
   public:
    using iterator = typename std::list<T>::iterator;

    static const constexpr uint32_t EMPTY_VAL     = 0xAAAAAAAA;
    static const constexpr uint32_t NON_EMPTY_VAL = 0x55555555;

    VectorUnique():m_size(Size){clear();};
    virtual ~VectorUnique(){clear();};
    VectorUnique(const VectorUnique &&) = delete;
    VectorUnique(const VectorUnique &) = delete;
    VectorUnique & operator=(const VectorUnique &) = delete;
    VectorUnique & operator=(const VectorUnique &&) = delete;

    bool isPresent(const T val) const;
    void insert(const T val);
    bool remove(const T val);
    bool isSpace() const;
    uint32_t getNumberOfElements() const;
    void clear();
    iterator getIteratorBegin()
    {
        return m_list.begin();
    }
    iterator getIteratorEnd()
    {
        return m_list.end();
    }

    VectorUnique & operator=(const std::vector<T> & stlVector)
    {
        this->clear();

        assert(stlVector.size() <= this->m_size);
        for(auto cit = stlVector.begin(); cit != stlVector.end(); ++cit)
        {
            T data = *cit;
            this->insert(data);
        }

        return *this;
    }

   private:
    const uint32_t m_size;
    uint32_t m_MarkArray[Size];
    std::list<T> m_list;
};

template<typename T, uint32_t Size>
bool VectorUnique<T, Size>::isPresent(const T val) const
{
    // T must provide operator to convert T -> uint32_t
    const uint32_t convertVal = static_cast<uint32_t>(val);

    const bool retVal = (NON_EMPTY_VAL == m_MarkArray[convertVal]);
    return retVal;
}

template<typename T, uint32_t Size>
void VectorUnique<T, Size>::insert(const T val)
{
    // T must provide operator to convert T -> uint32_t
    const uint32_t convertVal = static_cast<uint32_t>(val);
    m_MarkArray[convertVal]   = NON_EMPTY_VAL;

    m_list.push_back(val);
}

template<typename T, uint32_t Size>
bool VectorUnique<T, Size>::remove(const T val)
{
    bool retVal = false;

    const bool isOK = isPresent(val);
    if(isOK)
    {
        // T must provide operator to convert T -> uint32_t
        const uint32_t convertVal = static_cast<uint32_t>(val);
        m_MarkArray[convertVal]   = EMPTY_VAL;

        typename std::list<T>::iterator iter = std::find(m_list.begin(), m_list.end(), val);
        const bool isOk = iter != m_list.end();
        assert(isOk);
        iter = m_list.erase(iter);

        retVal = true;
    }

    return retVal;
}

template<typename T, uint32_t Size>
bool VectorUnique<T, Size>::isSpace() const
{
    const bool isSpace = (m_list.size() < m_size);
    return isSpace;
}

template<typename T, uint32_t Size>
uint32_t VectorUnique<T, Size>::getNumberOfElements() const
{
    const uint32_t retVal = m_list.size();
    return retVal;
}

template<typename T, uint32_t Size>
void VectorUnique<T, Size>::clear()
{
    memset(m_MarkArray, EMPTY_VAL, sizeof(m_MarkArray[0]) * m_size);
    m_list.clear();
}
