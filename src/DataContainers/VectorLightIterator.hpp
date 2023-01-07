#if !defined(VECTOR_LIGHT_ITERATOR_)
#define VECTOR_LIGHT_ITERATOR_

#include "IteratorIf.hpp"   // For IteratorIf declaration.
#include "VectorLight.hpp"  // For VectorLight definitions.

class VectorLightIterator : public IteratorIf<uint32_t>
{
   public:
    virtual bool HasNext() const;
    virtual uint32_t GetNext();
    virtual uint32_t GetIndex() const;
    virtual void SetToBase();

    VectorLightIterator(const uint32_t (&rDataArray)[VectorLight::VECTOR_SIZE], const uint32_t & rCursor,
                        const uint32_t emptyVal) :
        m_rDataArray(rDataArray), m_rCursor(rCursor), m_Cntr(0), m_ReleasedSpace(emptyVal)
    {
        // Nothing to do.
    }

    virtual ~VectorLightIterator() {}

   private:
    const uint32_t (&m_rDataArray)[VectorLight::VECTOR_SIZE];
    const uint32_t & m_rCursor;
    uint32_t m_Cntr;
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