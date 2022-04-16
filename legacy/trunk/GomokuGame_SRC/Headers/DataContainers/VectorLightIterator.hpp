/////////////////////////////////////////////////////////////////////////////////////////
/// @file VectorLightIterator.hpp
///
/// VectorLightIterator class declaration.
///
/// @par Full Description.
/// Providing iterator for VectorLight class.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 15-Sep-2016 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined ( VECTOR_LIGHT_ITERATOR_ )
#define VECTOR_LIGHT_ITERATOR_

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "IteratorIf.hpp"    // For IteratorIf declaration.
#include "VectorLight.hpp"	 // For VectorLight definitions.

// FORWARD REFERENCES
// <none>

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: VectorLightIterator.
///
/// VectorLightIterator class definition.
///
/// @par Full Description.
/// Providing iterator for VectorLight class.
///////////////////////////////////////////////////////////////////////////////////////////
class VectorLightIterator: public IteratorIf<uint32_t>
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
    virtual uint32_t GetNext();

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
    virtual void SetToBase();

    // Constructor.
    VectorLightIterator( const uint32_t ( &rDataArray )[ VectorLight::VECTOR_SIZE ], const uint32_t& rCursor, const uint32_t emptyVal )
     : m_rDataArray( rDataArray )
     , m_rCursor( rCursor )
     , m_Cntr( 0 )
     , m_ReleasedSpace( emptyVal )
    {
        // Nothing to do.
    }

    // Destructor.
    virtual ~VectorLightIterator()
    {}

private:
    // Element collection.
    const uint32_t ( &m_rDataArray )[ VectorLight::VECTOR_SIZE ];
    const uint32_t& m_rCursor;

    // Counter for current position.
    uint32_t m_Cntr;

    // This value marks released space.
    const uint32_t m_ReleasedSpace;

};

#endif /* VECTOR_LIGHT_ITERATOR_ */

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