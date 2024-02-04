#pragma once

#include <stdint.h>
#include <assert.h>

template<typename T>
class IIterator
{
   public:
    virtual bool hasNext() const = 0;
    virtual T getNext() = 0;
    virtual uint32_t getIndex() const = 0;
    virtual void backToBegin() = 0;
    virtual bool isInUse() const { return false; }

    IIterator() = default;
    virtual ~IIterator()= default;
};
