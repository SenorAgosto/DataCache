#pragma once
#include <DataCache/ObjectCounter.hpp>

namespace DataCache { namespace Testing {
  
    // A test helper to reset the static member counter on ObjectCounter<CountedType>.
    template<typename CountedType>
    class ObjectCounterResetter
    {
    public:
        ObjectCounterResetter(std::size_t resetValue = 0)
        {
            DataCache::ObjectCounter<CountedType>::count_ = resetValue;
        }
    };
}}
