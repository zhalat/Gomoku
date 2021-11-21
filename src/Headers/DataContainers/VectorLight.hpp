#pragma once

#include <assert.h>        // For assert.
#include <string.h>        // For memset.
#include <vector>          // For vector.
#include "GomokuGame.hpp"  // For GomokuGameUI::MAX_BOARD_SIZE.
#include "IteratorIf.hpp"  // For iterator interface.
#include "Board.hpp"       // Board::PositionField.

// FORWARD REFERENCES
class VectorLightTest;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: VectorLight
///
/// Light implementation of vector-like container.
/// Note: There is strong assumption that there will be no more VectorSize elements
/// 	  that are unique. Implementation basis on two array which one keeps the vale and
///		  the second keeps index-where the first array keeps the value.
//		  The solution is very fast due to not use loops.
///
/// @par Full Description.
/// Light, crude vector-like container.
///////////////////////////////////////////////////////////////////////////////////////////
class VectorLight
{
#warning "This class shall be template to support various data-element."
   public:
    static const constexpr uint32_t VECTOR_SIZE = GomokuGame::MAX_BOARD_SIZE * GomokuGame::MAX_BOARD_SIZE;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorLight::Insert
    //
    /// Put data into collection.
    ///
    /// @par Full Description
    /// Put data into collection.
    ///
    /// @param val Data value to be stored.
    ///////////////////////////////////////////////////////////////////////
    void Insert(const uint32_t val);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorLight::GetIterator
    //
    /// Get iterator.
    ///
    /// @par Full Description
    /// Get iterator to go thru collection.
    ///
    /// @retval  Iterator for collection.
    ///////////////////////////////////////////////////////////////////////
    virtual IteratorIf<uint32_t> * GetIterator() const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorLight::IsPresent
    //
    /// Check if val was added into collection.
    ///
    /// @par Full Description
    /// Check if val was added into collection.
    ///
    /// @param True if val is present in collection, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    bool IsPresent(const uint32_t val) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorLight::Remove
    //
    /// If data val does exist in the collection, method removes it.
    ///
    /// @par Full Description
    /// Remove data from collection.
    /// Notice:
    /// Even after removing, the space is not retrieved.
    ///
    /// @param True: val exists and removes, false: val does not exist in collection.
    ///////////////////////////////////////////////////////////////////////
    bool Remove(const uint32_t val);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorLight::IsSpace
    //
    /// Checking if collection has space for one more element.
    ///
    /// @par Full Description
    /// Checking if collection has space for one more element.
    ///
    /// @retval True if at least one element can be added, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    bool IsSpace() const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorLight::GetNumberOfElements
    //
    /// Get element existing in collection.
    ///
    /// @par Full Description
    /// Note: Don't use this value to assess available space in collection.
    /// 	  Always use IsSpace() to check if there is space for an element.
    ///
    /// @retval Valid element in collection.
    ///////////////////////////////////////////////////////////////////////
    uint32_t GetNumberOfElements() const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorLight::Clear
    //
    /// Clear container.
    ///
    /// @par Full Description
    /// After this operation container stays as if was just created.
    ///////////////////////////////////////////////////////////////////////
    void Clear();

    VectorLight(const uint32_t initVal);
    VectorLight(const VectorLight & rVectorLight);
    virtual ~VectorLight();
    VectorLight & operator=(const std::vector<Board::PositionField> & rStlVector);

   private:
    const uint32_t m_InitVal;

    uint32_t m_Array[VECTOR_SIZE];
    uint32_t m_MarkArray[VECTOR_SIZE];
    uint32_t m_Cursor;
    uint32_t m_NumberOfElement;
    IteratorIf<uint32_t> * m_pIterator;

#warning "Such dependency should be removed."
    friend class TEST_VectorLightTest_InitTest_Test;
};

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
