#pragma once
#include <type_traits>

// Singleton pattern via CRTP (curiously recurring template pattern)
// thread safe in C++11 and later
template<typename T>
class Singleton
{
   public:
    static T & getInstance() noexcept(std::is_nothrow_constructible<T>::value)
    {
        static T instance;
        return instance;
    }

    // thread local instance
    static thread_local T & getThreadLocalInstance() noexcept(std::is_nothrow_constructible<T>::value)
    {
        static T instance;
        return instance;
    }

   protected:
    Singleton(const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;
    Singleton() noexcept                     = default;
};
