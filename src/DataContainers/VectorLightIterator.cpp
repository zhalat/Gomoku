/////////////////////////////////////////////////////////////////////////////////////////
/// @file VectorLightIterator.cpp
///
/// VectorLightIterator class definition.
///
/// @par Full Description.
/// Providing iterator for VectorLight class.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 30-Sep-2016 Initial revision.
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
#include "VectorLightIterator.hpp"  // For BoardIterator declaration.
#include <assert.h>                 // For assert.

// FORWARD REFERENCES
// <none>

/// Check if collection has next element.
bool VectorLightIterator::HasNext() const
{
    bool retVal = false;

    // Skip all cells that are marked as empty (m_ReleasedSpace value).
    for(uint32_t cntr = m_Cntr; cntr < m_rCursor; ++cntr)
    {
        if(m_ReleasedSpace == m_rDataArray[cntr])
        {
            continue;
        }
        else
        {
            retVal = true;
            break;
        }
    }

    return retVal;
}

/// Get the next element.
uint32_t VectorLightIterator::GetNext()
{
    // Make sure that there is an next element.
    assert(HasNext());

    // Set cursor for the next non empty data.
    for(; m_ReleasedSpace == m_rDataArray[m_Cntr]; ++m_Cntr)
        ;

    const uint32_t retVal = m_rDataArray[m_Cntr];

#warning "Overload ++operator for the class, and do not increment cursor here. This method shall be const"
    ++m_Cntr;

    return retVal;
}

/// Get index of current element.
uint32_t VectorLightIterator::GetIndex() const
{
    return m_Cntr;
}

/// Set iterator to beginning of the collection.
void VectorLightIterator::SetToBase()
{
    m_Cntr = 0;
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
