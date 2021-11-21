/////////////////////////////////////////////////////////////////////////////////////////
/// @file VectorLight.cpp
///
/// VectorLight class definition.
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
#include <assert.h>  // For assert.
#include <vector>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "VectorLight.hpp"          // For VectorLight declaration.
#include "VectorLightIterator.hpp"  // For VectorLightIterator constructor.

// FORWARD REFERENCES
// <none>

/// Put data into collection.
void VectorLight::Insert(const uint32_t val)
{
    // To speed up, consider comment this asserts.
    assert(m_Cursor < (VECTOR_SIZE));
    assert(val < VECTOR_SIZE);

    m_Array[m_Cursor] = val;
    m_MarkArray[val]  = m_Cursor;

    m_Cursor++;

    m_NumberOfElement++;
}

/// Get iterator.
IteratorIf<uint32_t> * VectorLight::GetIterator() const
{
    return m_pIterator;
}

/// Check if val was added into collection.
bool VectorLight::IsPresent(const uint32_t val) const
{
    // To speed up, consider comment this asserts.
    assert(val < VECTOR_SIZE);

    const bool retVal = (m_InitVal != m_MarkArray[val]);

    return retVal;
}

/// If data val does exist in the collection, method removes it.
bool VectorLight::Remove(const uint32_t val)
{
    const bool retVal = IsPresent(val);

    if(retVal)
    {
        uint32_t index = m_MarkArray[val];

        m_Array[index]   = m_InitVal;
        m_MarkArray[val] = m_InitVal;
        m_NumberOfElement--;
    }

    return retVal;
}

/// Checking if collection has space for one more element.
bool VectorLight::IsSpace() const
{
    const bool retVal = (m_Cursor < VECTOR_SIZE);
    return retVal;
}

/// Get element existing in collection.
uint32_t VectorLight::GetNumberOfElements() const
{
    return m_NumberOfElement;
}

void VectorLight::Clear()
{
    m_Cursor          = 0;
    m_NumberOfElement = 0;
    memset(m_Array, m_InitVal, sizeof(m_Array));
    memset(m_MarkArray, m_InitVal, sizeof(m_MarkArray));

    m_pIterator->SetToBase();
}

/// Conversion operator from std::vector class.
VectorLight & VectorLight::operator=(const vector<Board::PositionField> & rStlVector)
{
    // Be sure container size if large enough.
    assert(rStlVector.size() <= VECTOR_SIZE);

    for(auto cit = rStlVector.begin(); cit != rStlVector.end(); ++cit)
    {
        const uint32_t data = static_cast<uint32_t>(*cit);
        this->Insert(data);
    }

    return *this;
}

/// Constructor.
VectorLight::VectorLight(const uint32_t initVal) : m_InitVal(initVal)
{
    memset(m_Array, initVal, sizeof(m_Array));
    memset(m_MarkArray, initVal, sizeof(m_MarkArray));
    m_Cursor          = 0;
    m_NumberOfElement = 0;

    // Create iterator for this collection.
    m_pIterator = new VectorLightIterator(m_Array, m_Cursor, m_InitVal);
}

/// Copy constructor.
VectorLight::VectorLight(const VectorLight & VectorLight) : m_InitVal(VectorLight.m_InitVal)
{
    memcpy(m_Array, VectorLight.m_Array, sizeof(m_Array));
    memcpy(m_MarkArray, VectorLight.m_MarkArray, sizeof(VectorLight.m_MarkArray));
    m_Cursor          = VectorLight.m_Cursor;
    m_NumberOfElement = VectorLight.m_NumberOfElement;

    // Create iterator for this collection.
    m_pIterator = new VectorLightIterator(m_Array, m_Cursor, m_InitVal);
}

/// Destructor.
VectorLight::~VectorLight()
{
    delete m_pIterator;
    m_pIterator = NULL;
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
