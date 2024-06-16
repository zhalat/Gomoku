#pragma once

#include <assert.h>
#include "SingleListIterator.h"

template<class parNode>
class Node
{
   public:
    parNode m_Data;
    Node * m_pNext;
    Node(parNode input, Node * ptr = NULL)
    {
        m_Data  = input;
        m_pNext = ptr;
    }
};

template<class parList>
class SingleList
{
   public:
    SingleList() : m_pHead(NULL), m_pTail(NULL), m_pIterator(NULL)
    {
        m_pIterator = new SingleListIterator<parList>(&m_pHead, &m_pTail);
        assert(m_pIterator);
    }
    SingleList(const SingleList &&) = delete;
    SingleList(const SingleList &) = delete;
    SingleList & operator=(const SingleList &) = delete;
    SingleList & operator=(const SingleList &&) = delete;
    virtual ~SingleList();

    void addToTail(const parList data);
    void addToHead(const parList data);
    parList removeFromTail();
    parList removeFromHead();
    parList removeNode(const parList data);
    bool isEmpty() const;
    bool isPresent(const parList data) const;
    uint32_t size() const;
    IIterator<parList> * getIterator() const;

   private:
    Node<parList> * m_pHead;
    Node<parList> * m_pTail;
    IIterator<parList> * m_pIterator;
};

template<class parList>
SingleList<parList>::~SingleList()
{
    if(!isEmpty())
    {
        Node<parList> * ptr = m_pHead;
        for(; NULL != ptr;)
        {
            ptr = m_pHead->m_pNext;
            delete m_pHead;
            m_pHead = ptr;
        }
    }

    delete m_pIterator;
    m_pIterator = NULL;
}

template<class parList>
bool SingleList<parList>::isEmpty() const
{
    if((NULL == m_pHead) && (NULL == m_pTail))
        return true;
    else
        return false;
}

template<class parList>
void SingleList<parList>::addToTail(parList data)
{
    if(isEmpty())
    {
        m_pTail = m_pHead = new Node<parList>(data, NULL);
    }
    else
    {
        m_pTail = m_pTail->m_pNext = new Node<parList>(data, NULL);
    }
}

template<class parList>
void SingleList<parList>::addToHead(parList data)
{
    if(isEmpty())
    {
        m_pTail = m_pHead = new Node<parList>(data, NULL);
    }
    else
    {
        Node<parList> * ptr = new Node<parList>(data, NULL);
        ptr->m_pNext        = m_pHead;
        m_pHead             = ptr;
    }
}

template<class parList>
parList SingleList<parList>::removeFromTail()
{
    parList tempElement;
    if(isEmpty())
    {
        assert(false);
    }
    else
    {
        if(m_pTail == m_pHead)
        {
            tempElement = m_pTail->m_Data;
            delete m_pHead;
            m_pTail = m_pHead = NULL;
        }
        else
        {
            Node<parList> * ptr;
            for(ptr = m_pHead; ptr->m_pNext != m_pTail; ptr = ptr->m_pNext)
            {
                // nothing to do.
            }

            tempElement = m_pTail->m_Data;
            delete m_pTail;
            m_pTail          = ptr;
            m_pTail->m_pNext = NULL;
        }
    }
    return tempElement;
}

template<class parList>
parList SingleList<parList>::removeFromHead()
{
    parList tempElement;
    if(isEmpty())
    {
        assert(false);
    }
    else
    {
        if(m_pTail == m_pHead)
        {
            tempElement = m_pHead->m_Data;
            delete m_pHead;
            m_pTail = m_pHead = NULL;
        }
        else
        {
            tempElement         = m_pHead->m_Data;
            Node<parList> * ptr = m_pHead->m_pNext;
            delete m_pHead;
            m_pHead = ptr;
        }
    }
    return tempElement;
}

template<class parList>
bool SingleList<parList>::isPresent(parList data) const
{
    Node<parList> * ptr;
    for(ptr = m_pHead; NULL != ptr; ptr = ptr->m_pNext)
    {
        if(ptr->m_Data == data)
            return true;
    }
    return false;
}

template<class parList>
uint32_t SingleList<parList>::size() const
{
    uint32_t retVal = 0;

    if(!isEmpty())
    {
        // One element is for sure, even if pHead == pTail
        ++retVal;

        for(Node<parList> * ptr = m_pHead; ptr != m_pTail; ptr = ptr->m_pNext)
        {
            ++retVal;
        }
    }

    return retVal;
}

template<class parList>
parList SingleList<parList>::removeNode(parList data)
{
    parList tempElement;

    if(isPresent(data) && (m_pTail == m_pHead))
    {
        tempElement = removeFromHead();
        m_pTail = m_pHead = NULL;
    }
    else if(isPresent(data))
    {
        Node<parList> * ptr       = NULL;
        Node<parList> * ptrShadow = m_pHead;

        for(ptr = m_pHead; NULL != ptr; ptr = ptr->m_pNext)
        {
            if((ptr->m_Data == data) && (ptr == m_pHead))
            {
                tempElement = removeFromHead();
                break;
            }
            else if(ptr->m_Data == data)
            {
                tempElement        = ptr->m_Data;
                ptrShadow->m_pNext = ptr->m_pNext;
                delete ptr;
                break;
            }
            else if(ptr != m_pHead)
            {
                ptrShadow = ptrShadow->m_pNext;
            }
        }
    }
    else
    {
        assert(false);
    }
    return tempElement;
}

template<class parList>
IIterator<parList> * SingleList<parList>::getIterator() const
{
    IIterator<parList> * retVal = NULL;

    // Don't give handler for iteratr while it is in use by another.
    if(!m_pIterator->isInUse())
    {
        retVal = m_pIterator;
    }
    else
    {
        assert(false);
    }

    return retVal;
}

