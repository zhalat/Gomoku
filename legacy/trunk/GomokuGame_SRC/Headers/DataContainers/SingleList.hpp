/////////////////////////////////////////////////////////////////////////////////////////
/// @file SingleList.hpp
///
/// Single list.
///
/// @par Full Description.
/// Light, crude single list container.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 31-Oct-2014 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#ifndef SINGLE_LIST
#define SINGLE_LIST

// SYSTEM INCLUDES
#include <assert.h>           		// For assert.
#include <iostream>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "SingleListIterator.hpp"

// FORWARD REFERENCES
// <none>

template <class parNode>
class Node
{
public:
    parNode m_Data;
    Node* m_pNext;
    Node( parNode input, Node* ptr = NULL )
    {
        m_Data = input;
        m_pNext = ptr;
    }
};

template <class parList>
class SingleList
{
public:
    void AddToTail( const parList data );
    void AddToHead( const parList data );
    parList RemoveFromTail();
    parList RemoveFromHead();
    parList RemoveNode( const parList data );
    bool IsEmpty() const;
    bool IsPresent( const parList data ) const;
    uint32_t Size() const;
    IteratorIf<parList>* GetIterator() const;

    // Default constructor.
    SingleList()
     : m_pHead( NULL )
	 , m_pTail( NULL )
	 , m_pIterator( NULL )
    {
    	// Create iterator for this collection.
    	m_pIterator = new SingleListIterator<parList>( &m_pHead, &m_pTail );
    	assert( m_pIterator );
    }

    virtual ~SingleList();

private:
    // Prevent either copying or assigning (>= C++11).
    SingleList( const SingleList& ) = delete;
    SingleList& operator=( const SingleList& ) = delete;

    Node<parList>* m_pHead;
    Node<parList>* m_pTail;

    // Handler to iterator.
    IteratorIf<parList>* m_pIterator;
};

// ~SingleList:
template <class parList>
SingleList<parList>::~SingleList()
{
    if( !IsEmpty() )
    {
        Node<parList>* ptr = m_pHead;
        for( ; NULL != ptr; )
        {
            ptr = m_pHead->m_pNext;
            delete m_pHead;
            m_pHead = ptr;
        }
    }

    delete m_pIterator;
}

// IsEmpty:
template <class parList>
bool SingleList<parList>::IsEmpty() const
{
    if( ( NULL == m_pHead ) && ( NULL == m_pTail ) )
    	return true;
    else
    	return false;
}

// AddToTail:
template <class parList>
void SingleList<parList>::AddToTail( parList data )
{
    if( IsEmpty() )
    {
        m_pTail = m_pHead = new Node<parList>( data, NULL );
    }
    else
    {
        m_pTail = m_pTail->m_pNext = new Node<parList>( data, NULL );
    }
}

// AddToHead:
template <class parList>
void SingleList<parList>::AddToHead( parList data )
{
    if( IsEmpty() )
    {
        m_pTail = m_pHead = new Node<parList>( data, NULL );
    }
    else
    {
        Node<parList>* ptr = new Node<parList>( data, NULL );
        ptr->m_pNext = m_pHead;
        m_pHead = ptr;
    }
}

// RemoveFromTail:
template <class parList>
parList SingleList<parList>::RemoveFromTail()
{
    parList tempElement;
    if( IsEmpty() )
    {
    	assert( false );
    }
    else
    {
        if( m_pTail == m_pHead )
        {
            tempElement = m_pTail->m_Data;
            delete m_pHead;
            m_pTail = m_pHead = NULL;
        }
        else
        {
            Node<parList> *ptr;
            for( ptr = m_pHead; ptr->m_pNext != m_pTail; ptr = ptr->m_pNext )
            {
            	// nothing to do.
            }

            tempElement = m_pTail->m_Data;
            delete m_pTail;
            m_pTail = ptr;
            m_pTail->m_pNext = NULL;
        }
    }
    return tempElement;
}

// RemoveFromHead:
template <class parList>
parList SingleList<parList>::RemoveFromHead()
{
    parList tempElement;
    if( IsEmpty() )
    {
    	assert( false );
    }
    else
    {
        if ( m_pTail == m_pHead )
        {
            tempElement = m_pHead->m_Data;
            delete m_pHead;
            m_pTail = m_pHead = NULL;
        }
        else
        {
            tempElement = m_pHead->m_Data;
            Node<parList>* ptr = m_pHead->m_pNext;
            delete m_pHead;
            m_pHead = ptr;
        }
    }
    return tempElement;
}

// IsPresent:
template <class parList>
bool SingleList<parList>::IsPresent( parList data ) const
{
    Node<parList> *ptr;
    for( ptr = m_pHead; NULL != ptr; ptr = ptr->m_pNext )
    {
        if ( ptr->m_Data == data )
        	return true;
    }
    return false;
}

template <class parList>
uint32_t SingleList<parList>::Size() const
{
	uint32_t retVal = 0;

	if ( !IsEmpty() )
	{
		// One element is for sure, even if pHead == pTail
		++retVal;

		for( Node<parList>* ptr = m_pHead; ptr != m_pTail; ptr = ptr->m_pNext )
		{
			++retVal;
		}
	}

	return retVal;
}

// RemoveNode:
template <class parList>
parList SingleList<parList>::RemoveNode( parList data )
{
    parList tempElement;

    if( IsPresent( data ) && ( m_pTail == m_pHead ) )
    {
        tempElement = RemoveFromHead();
        m_pTail = m_pHead = NULL;
    }
    else if ( IsPresent(data) )
    {
        Node<parList>* ptr = NULL;
        Node<parList>* ptrShadow = m_pHead;

        for( ptr = m_pHead; NULL != ptr; ptr=ptr->m_pNext )
        {
            if( ( ptr->m_Data == data ) && ( ptr == m_pHead ) )
            {
            	tempElement = RemoveFromHead();
                break;
            }
            else if( ptr->m_Data == data )
            {
                tempElement = ptr->m_Data;
                ptrShadow->m_pNext = ptr->m_pNext;
                delete ptr;
                break;
            }
            else if ( ptr!=m_pHead )
            {
                ptrShadow = ptrShadow->m_pNext;
            }
        }
    }
    else
    {
        assert( false );
    }
    return tempElement;
}

// GetIterator.
template <class parList>
IteratorIf<parList>* SingleList<parList>::GetIterator() const
{
	IteratorIf<parList>* retVal = NULL;

	// Don't give handle for iteratr while it is in use by another.
	if( !m_pIterator->IsInUse() )
	{
		retVal = m_pIterator;
	}

	return retVal;
}

#endif // SINGLE_LIST

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