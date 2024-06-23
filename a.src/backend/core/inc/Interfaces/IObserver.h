#pragma once

#include <vector>

namespace Observer {
class IObserver
{
   public:
    virtual void update() const = 0;
};

class IObserverSubject
{
   protected:
    std::vector<const IObserver *> m_observerClient;

   public:
    virtual void registerObserver(const IObserver & observer) = 0;
    virtual bool removeObserver(const IObserver & observer) = 0;
    virtual void announce() const = 0;
};
};
