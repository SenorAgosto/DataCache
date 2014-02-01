#pragma once
#include <DataCache/Details/ObjectCounterTagTypes.hpp>

#include <atomic>
#include <cstdint>

namespace DataCache { namespace Testing {
    
    template<typename CountedType>
    class ObjectCounterResetter;
}}

namespace DataCache {

    // For any given type, create a thread-safe static counter of the objects.
    //
    // Usage:
    //     class MyClass : private ObjectCounter<MyClass>
    //     {
    //     };
    template<typename CountedType>
    class ObjectCounter
    {
    public:
        
        ObjectCounter()
        {
            ++count_;
        }
    
        inline std::size_t count(void) const
        {
            return count_;
        }

    protected:
        
        // A constructor which does not increment the object counter.
        //
        // This is to be used by derived types to implement
        // copy/move constructors and operators. It indicates that
        // we do not wish to increment the object count.
        ObjectCounter(Details::NoIncrement)
        {
        }
        
    private:
        // declare a friend for resetting from unit tests.
        friend class Testing::ObjectCounterResetter<CountedType>;
        
        ObjectCounter(const ObjectCounter&) = delete;
        ObjectCounter& operator=(const ObjectCounter&) = delete;
        
    private:
        static std::atomic<std::size_t> count_;
    };
    
    // initialize the static data member for type CountedType.
    template<typename CountedType>
    std::atomic<std::size_t> ObjectCounter<CountedType>::count_(0);
}