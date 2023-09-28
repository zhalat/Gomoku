#pragma once

#include <stdint.h>

template<class Element>
class IteratorIf
{
   public:
    virtual bool HasNext() const = 0;
    virtual Element GetNext() = 0;
    virtual uint32_t GetIndex() const = 0;
    virtual void SetToBase() = 0;
    virtual bool IsInUse() const { return false; }

    virtual ~IteratorIf() {}
};
