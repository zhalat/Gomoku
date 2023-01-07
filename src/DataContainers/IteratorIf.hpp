#if !defined(ITERATOR_HPP_)
#define ITERATOR_HPP_

#include <stdint.h>

/////////////////////////////////////////////////////////////////////////////
/// ABSTRACT CLASS NAME: Iterator
///
/// Provide interface for each iterators.
///
/// @par Full Description
/// Provide interface for each iterators.
/////////////////////////////////////////////////////////////////////////////
template<class Element>
class IteratorIf
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
    virtual bool HasNext() const = 0;

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
    virtual Element GetNext() = 0;

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
    virtual uint32_t GetIndex() const = 0;

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: SetToBase
    //
    /// Set iterator to beginning of the collection.
    ///
    /// @par Full Description
    /// Set iterator to beginning of the collection.
    /////////////////////////////////////////////////////////////////////////////
    virtual void SetToBase() = 0;

    /////////////////////////////////////////////////////////////////////////////
    // METHOD NAME: IsInUse
    //
    /// Check if iterator is in use.
    ///
    /// @par Full Description
    /// Check if iterator is in use.
    ///
    /// @return True if iterator in use, false otherwise.
    /////////////////////////////////////////////////////////////////////////////
    virtual bool IsInUse() const { return false; }

    // Destructor.
    virtual ~IteratorIf() {}
};

#endif /* ITERATOR_HPP_ */

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