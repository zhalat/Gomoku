/////////////////////////////////////////////////////////////////////////////////////////
/// @file BoardIterator.cpp
///
/// BoardIterator class definition.
///
/// @par Full Description.
/// Providing iterator for board class.
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

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "BoardIterator.hpp"  // For BoardIterator declaration.
#include <assert.h>           // For assert.

// FORWARD REFERENCES
// <none>

/// Check if collection has next element.
bool BoardIterator::HasNext() const
{
    auto iter = m_rGraph.GetIterator();
    return iter->HasNext();
}

/// Get the next element.
graph::Node BoardIterator::GetNext()
{
    auto iter = m_rGraph.GetIterator();
    return iter->GetNext();
}

/// Get index of current element.
uint32_t BoardIterator::GetIndex() const
{
    auto iter = m_rGraph.GetIterator();
    return iter->GetIndex();
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
