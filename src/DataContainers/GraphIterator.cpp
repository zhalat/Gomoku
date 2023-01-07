/////////////////////////////////////////////////////////////////////////////////////////
/// @file GraphIterator.cpp
///
/// GraphIterator class definition.
///
/// @par Full Description.
/// Providing iterator for graph class.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 12-May-2016 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2016 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "GraphIterator.hpp"  // For Graph declaration.
#include <assert.h>           // For assert.

// FORWARD REFERENCES
// <none>

/// Check if collection has next element.
bool GraphIterator::HasNext() const
{
    bool retVal = false;

    if(m_Cntr < m_size)
    {
        retVal = true;
    }

    return retVal;
}

/// Get the next element.
graph::Node GraphIterator::GetNext()
{
    // Make sure that there is an next element.
    assert(HasNext());

    const graph::Node retVal = m_pCollection[m_Cntr];
    ++m_Cntr;

    return retVal;
}

/// Get index of current element.
uint32_t GraphIterator::GetIndex() const
{
    return m_Cntr;
}

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
