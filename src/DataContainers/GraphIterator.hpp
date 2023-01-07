#if !defined(GRAPH_ITERATOR_)
#define GRAPH_ITERATOR_

#include "IteratorIf.hpp"  // For IteratorIf definitions.
#include "Graph.hpp"       // For Graph definitions.

class GraphIterator : public IteratorIf<graph::Node>
{
   public:
    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: HasNext
    //
    /// Check if collection has next element.
    ///
    /// @par Full Description
    /// From current position, check if collection has the next element.
    ///
    /// @return False if current element is the last, true otherwise.
    /////////////////////////////////////////////////////////////////////////////
    virtual bool HasNext() const;

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: GetNext
    //
    /// Get the next element.
    ///
    /// @par Full Description
    /// If exist get the next element from collection.
    ///
    /// @return The next element from collection.
    /////////////////////////////////////////////////////////////////////////////
    virtual graph::Node GetNext();

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: GetIndex
    //
    /// Get index of current element.
    ///
    /// @par Full Description
    /// Provide an index in collection of current element.
    ///
    /// @return Index in collection of current element.
    /////////////////////////////////////////////////////////////////////////////
    virtual uint32_t GetIndex() const;

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: SetToBase
    //
    /// Set iterator to beginning of the collection.
    ///
    /// @par Full Description
    /// Set iterator to beginning of the collection.
    /////////////////////////////////////////////////////////////////////////////
    virtual void SetToBase() { m_Cntr = 0; }

    // Constructor.
    GraphIterator(graph::NodeVal * pCollection, uint32_t size) : m_pCollection(pCollection), m_size(size), m_Cntr(0)
    {
        // Nothing to do.
    }

   private:
    // Element collection.
    graph::NodeVal * m_pCollection;

    // Collection size.
    uint32_t m_size;

    // Counter for current position.
    uint32_t m_Cntr;
};

#endif /* GRAPH_ITERATOR_ */

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