#pragma once
#include <DataCache/Testing/ObjectCounterResetter.hpp>

namespace DataCache { namespace Testing {
  
    // A convenience wrapper around ObjectCounter<CountAllObjects>
    // so client unit test implementers don't have to remember
    // to use the DataCache::CountAllObjects tag type.
    class DataCacheOidResetter : public ObjectCounterResetter<Details::CountAllObjects>
    {
    };
}}