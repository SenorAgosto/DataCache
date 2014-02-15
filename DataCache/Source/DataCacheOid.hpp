#pragma once
#include <DataCache/ObjectCounter.hpp>
#include <cstddef>

namespace DataCache { namespace Testing {
    class DataCacheOidResetter;
}}

namespace DataCache {
    
    // Class for managing Object IDs in the DataCache.
    //
    // Every object stored in the data cache needs
    // a unique OID so it can reference its cached data
    // member fields.
    //
    class DataCacheOid : private ObjectCounter<DataCacheOid>
    {
    public:
        DataCacheOid();
        operator std::size_t();
        
        std::size_t oid(void) const;
        
    private:
        std::size_t oid_;
    };
}
