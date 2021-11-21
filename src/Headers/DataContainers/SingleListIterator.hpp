#if !defined(SINGLE_LIST_ITERATOR_)
#define SINGLE_LIST_ITERATOR_

#include <stddef.h>
#include "IteratorIf.hpp"  // For IteratorIf declaration.

// FORWARD REFERENCES
template<class parNode>
class Node;

template<class parList>
class SingleListIterator : public IteratorIf<parList>
{
   public:
    virtual bool HasNext() const;
    virtual parList GetNext();
    virtual uint32_t GetIndex() const;
    virtual void SetToBase();
    virtual bool IsInUse();

    // Constructor.
    SingleListIterator(Node<parList> ** ppHead, Node<parList> ** ppTail) :
        m_ppHead(ppHead), m_ppTail(ppTail), m_ppCursor(ppHead), m_Cntr(0)
    {
        // Nothing to do.
    }

    // Destructor.
    virtual ~SingleListIterator()
    {
        m_ppHead   = NULL;
        m_ppTail   = NULL;
        m_ppCursor = NULL;
        m_Cntr     = 0;
    }

   private:
    // Prevent either copying or assigning (>= C++11).
    SingleListIterator(const SingleListIterator &) = delete;
    SingleListIterator & operator=(const SingleListIterator &) = delete;

    Node<parList> ** m_ppHead;
    Node<parList> ** m_ppTail;
    Node<parList> ** m_ppCursor;
    uint32_t m_Cntr;
};

template<class parList>
bool SingleListIterator<parList>::HasNext() const
{
    bool retVal = false;

    if((m_ppCursor != NULL) && (*m_ppCursor != NULL))
    {
        retVal = true;
    }

    return retVal;
}

template<class parList>
parList SingleListIterator<parList>::GetNext()
{
    // Make sure that there is an next element.
    assert(HasNext());

    assert(m_ppCursor);

    const parList retVal = (*m_ppCursor)->m_Data;
    m_ppCursor           = &((*m_ppCursor)->m_pNext);
    m_Cntr++;

    return retVal;
}

template<class parList>
uint32_t SingleListIterator<parList>::GetIndex() const
{
    return m_Cntr;
}

template<class parList>
void SingleListIterator<parList>::SetToBase()
{
    m_ppCursor = m_ppHead;
    m_Cntr     = 0;
}

template<class parList>
bool SingleListIterator<parList>::IsInUse()
{
    return (m_Cntr != 0);
}

#endif /* SINGLE_LIST_ITERATOR_ */

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