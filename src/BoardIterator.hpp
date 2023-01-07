/////////////////////////////////////////////////////////////////////////////////////////
/// @file BoardIterator.hpp
///
/// BoardIterator class declaration.
///
/// @par Full Description.
/// Providing iterator for board class.
/// Because Board is composed from graph structure, board'iterator
/// uses graph iterator by delegation.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 15-May-2016 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined(BOARD_ITERATOR_)
#define BOARD_ITERATOR_

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "IteratorIf.hpp"  // For IteratorIf declaration.
#include "Graph.hpp"       // For Graph declaration.

// FORWARD REFERENCES
// <none>

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: BoardIterator.
///
/// BoardIterator class definition.
///
/// @par Full Description.
/// Providing iterator for board class.
/// Because Board is composed from graph structure, board'iterator
/// uses graph iterator by delegation.
///////////////////////////////////////////////////////////////////////////////////////////
class BoardIterator : public IteratorIf<graph::Node>
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
    /// Use delegation as Board uses graph iterator.
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
    /// Use delegation as Board uses graph iterator.
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
    /// Use delegation as Board uses graph iterator.
    /////////////////////////////////////////////////////////////////////////////
    virtual void SetToBase()
    {
        auto iter = m_rGraph.GetIterator();
        iter->SetToBase();
    }

    // Constructor.
    BoardIterator(graph::Graph & rGraph) : m_rGraph(rGraph)
    {
        // Nothing to do.
    }

   private:
    // Element collection.
    const graph::Graph & m_rGraph;
};

#endif /* BOARD_ITERATOR_ */

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
