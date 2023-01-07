#if !defined(VECTOR_UNIQUE_)
#define VECTOR_UNIQUE_

#include <assert.h>   // For assert.
#include <string.h>   // For memset.
#include <list>       // For list.
#include <algorithm>  // For find.
#include "Board.hpp"  // Board::PositionField.

// FORWARD REFERENCES
class TEST_VectorUniqueTest_InitTest_TestShell;

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: VectorUnique
///
/// STL list adapted to be VectorUnique.
/// Note: There is strong assumption that there will be no more VectorSize elements
/// 	  that are unique. The aim is to quick determinate if element to be add exist
///       already exists on the list.
///
/// @par Full Description.
/// Based on STL list. Guarantee unique elements on the list.
///////////////////////////////////////////////////////////////////////////////////////////
template<typename T, uint32_t Size>
class VectorUnique
{
   public:
    // Value to fill up initial data.
    static const constexpr uint32_t EMPTY_VAL     = 0xAAAAAAAA;
    static const constexpr uint32_t NON_EMPTY_VAL = 0x55555555;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorUnique::IsPresent
    //
    /// Check if val was added into collection.
    ///
    /// @par Full Description
    /// Check if val was added into collection.
    ///
    /// @param True if val is present in collection, false otherwise.
    ///////////////////////////////////////////////////////////////////////
    bool IsPresent(const T val) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorUnique::Insert
    //
    /// Put data into collection.
    ///
    /// @par Full Description
    /// Put data into collection.
    ///
    /// @param val Data value to be stored.
    ///////////////////////////////////////////////////////////////////////
    void Insert(const T val);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorUnique::Remove
    //
    /// If data val does exist in the collection, method removes it.
    ///
    /// @par Full Description
    /// Remove data from collection.
    ///
    /// @param val Data value to be stored.
    ///
    /// @retval True - vale was removed. False otherwise.
    ///////////////////////////////////////////////////////////////////////
    bool Remove(const T val);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorUnique::Remove
    //
    /// Removes element pointed by iterator. Shifts iterator to next element.
    ///
    /// @par Full Description
    /// Remove data from collection. Useful when 'removes-in-the-loop'.
    ///
    /// @param it Reference to the iterator which value is going to erase.
    /// 		  Method automatically shift iterator to correct position.
    ///
    /// @retval True - value pointed by it was removed. False otherwise.
    ///////////////////////////////////////////////////////////////////////
    bool Remove(typename std::list<T>::iterator & it);

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorUnique::IsSpace
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
    // METHOD NAME: VectorUnique::GetNumberOfElements
    //
    /// Get element existing in collection.
    ///
    /// @par Full Description
    /// Get element existing in collection.
    ///
    /// @retval Valid element in collection.
    ///////////////////////////////////////////////////////////////////////
    uint32_t GetNumberOfElements() const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorUnique::Clear
    //
    /// Clear container.
    ///
    /// @par Full Description
    /// After this operation container stays as if it was just created.
    ///////////////////////////////////////////////////////////////////////
    void Clear();

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorUnique::GetIteratorBegin
    //
    /// Get iterator begin.
    ///
    /// @par Full Description
    /// Get iterator to go thru collection.
    ///
    /// @retval  Iterator for collection.
    ///////////////////////////////////////////////////////////////////////
    typename std::list<T>::iterator GetIteratorBegin()
    {
        typename std::list<T>::iterator iter = m_List.begin();
        return iter;
    }

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: VectorUnique::GetIteratorEnd
    //
    /// Get iterator end.
    ///
    /// @par Full Description
    /// Get iterator to go thru collection.
    ///
    /// @retval  Iterator for collection.
    ///////////////////////////////////////////////////////////////////////
    typename std::list<T>::iterator GetIteratorEnd()
    {
        typename std::list<T>::iterator iter = m_List.end();
        return iter;
    }

    /// Constructor.
    VectorUnique();

    /// Destructor.
    virtual ~VectorUnique();

    /// Assign operator from stl vector.
    VectorUnique & operator=(const std::vector<T> & rStlVector)
    {
        this->Clear();

        assert(rStlVector.size() <= this->m_Size);
        for(auto cit = rStlVector.begin(); cit != rStlVector.end(); ++cit)
        {
            T data = *cit;
            this->Insert(data);
        }

        return *this;
    }

   private:
    const uint32_t m_Size;
    uint32_t m_MarkArray[Size];
    std::list<T> m_List;

    friend TEST_VectorUniqueTest_InitTest_TestShell;
};

template<typename T, uint32_t Size>
bool VectorUnique<T, Size>::IsPresent(const T val) const
{
    // T must provide operator to convert T -> uint32_t
    const uint32_t convertVal = static_cast<uint32_t>(val);

    const bool retVal = (NON_EMPTY_VAL == m_MarkArray[convertVal]);
    return retVal;
}

template<typename T, uint32_t Size>
void VectorUnique<T, Size>::Insert(const T val)
{
    // T must provide operator to convert T -> uint32_t
    const uint32_t convertVal = static_cast<uint32_t>(val);
    m_MarkArray[convertVal]   = NON_EMPTY_VAL;

    m_List.push_back(val);
}

template<typename T, uint32_t Size>
bool VectorUnique<T, Size>::Remove(const T val)
{
    bool retVal = false;

    const bool isOK = IsPresent(val);
    if(isOK)
    {
        // T must provide operator to convert T -> uint32_t
        const uint32_t convertVal = static_cast<uint32_t>(val);
        m_MarkArray[convertVal]   = EMPTY_VAL;

        typename std::list<T>::iterator iter = std::find(m_List.begin(), m_List.end(), val);
        assert(iter != m_List.end());
        iter = m_List.erase(iter);

        retVal = true;
    }

    return retVal;
}

template<typename T, uint32_t Size>
bool VectorUnique<T, Size>::Remove(typename std::list<T>::iterator & it)
{
    bool retVal     = false;
    const T val     = *it;
    const bool isOK = IsPresent(val);
    if(isOK)
    {
        // T must provide operator to convert T -> uint32_t
        const uint32_t convertVal = static_cast<uint32_t>(val);
        m_MarkArray[convertVal]   = EMPTY_VAL;

        typename std::list<T>::iterator iter = std::find(m_List.begin(), m_List.end(), val);
        assert(iter != m_List.end());
        it = m_List.erase(iter);

        retVal = true;
    }

    return retVal;
}

template<typename T, uint32_t Size>
bool VectorUnique<T, Size>::IsSpace() const
{
    const bool isSpace = (m_List.size() < m_Size);
    return isSpace;
}

template<typename T, uint32_t Size>
uint32_t VectorUnique<T, Size>::GetNumberOfElements() const
{
    const uint32_t retVal = m_List.size();
    return retVal;
}

template<typename T, uint32_t Size>
void VectorUnique<T, Size>::Clear()
{
    memset(m_MarkArray, EMPTY_VAL, sizeof(m_MarkArray[0]) * m_Size);
    m_List.clear();
}

template<typename T, uint32_t Size>
VectorUnique<T, Size>::VectorUnique() : m_Size(Size)
{
    Clear();
}

template<typename T, uint32_t Size>
VectorUnique<T, Size>::~VectorUnique()
{
    Clear();
}

#endif /* VECTOR_UNIQUE_ */

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
