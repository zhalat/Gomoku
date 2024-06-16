#pragma once

#include <stddef.h>
#include "Interfaces/IIterator.h"

template<class parNode>
class Node;

template<class parList>
class SingleListIterator : public IIterator<parList>
{
   public:
    bool hasNext() const override;
    parList getNext() override;
    uint32_t getIndex() const override;
    void backToBegin() override;
    bool isInUse() const  override;

    SingleListIterator(Node<parList> ** ppHead, Node<parList> ** ppTail) :
        m_ppHead(ppHead), m_ppTail(ppTail), m_ppCursor(ppHead)
    {}

    virtual ~SingleListIterator()
    {
        m_ppHead   = NULL;
        m_ppTail   = NULL;
        m_ppCursor = NULL;
        m_cntr     = 0;
    }

   private:
    SingleListIterator(const SingleListIterator &&) = delete;
    SingleListIterator(const SingleListIterator &) = delete;
    SingleListIterator & operator=(const SingleListIterator &) = delete;
    SingleListIterator & operator=(const SingleListIterator &&) = delete;

    Node<parList> ** m_ppHead{nullptr};
    Node<parList> ** m_ppTail{nullptr};
    Node<parList> ** m_ppCursor{nullptr};
    uint32_t m_cntr{0};
};

template<class parList>
bool SingleListIterator<parList>::hasNext() const
{
    bool retVal = false;

    if((m_ppCursor != NULL) && (*m_ppCursor != NULL))
    {
        retVal = true;
    }

    return retVal;
}

template<class parList>
parList SingleListIterator<parList>::getNext()
{
    const bool isNextOk = hasNext();
    assert(isNextOk);
    assert(m_ppCursor);

    const parList retVal = (*m_ppCursor)->m_Data;
    m_ppCursor           = &((*m_ppCursor)->m_pNext);
    m_cntr++;

    return retVal;
}

template<class parList>
uint32_t SingleListIterator<parList>::getIndex() const
{
    return m_cntr;
}

template<class parList>
void SingleListIterator<parList>::backToBegin()
{
    m_ppCursor = m_ppHead;
    m_cntr     = 0;
}

template<class parList>
bool SingleListIterator<parList>::isInUse() const
{
    return (m_cntr != 0);
}
