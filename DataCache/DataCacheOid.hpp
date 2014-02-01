#pragma once
#include <DataCache/ObjectCounter.hpp>
#include <cstddef>

namespace DataCache { namespace Testing {
    class DataCacheOidResetter;
}}

namespace DataCache {

    // A tag type indicating that we should increment the type when
    // any object is created.
    struct CountAllObjects {};
    
    // Object Id base class.
    //
    // Every object stored in the data cache needs
    // to inherit from DataCacheOid. All data cache
    // entries are referenced using the object's <oid_>
    class DataCacheOid : private ObjectCounter<CountAllObjects>
    {
    public:
        DataCacheOid();
        
        inline std::size_t oid(void) const { return oid_; }
        
    private:
        friend class Testing::DataCacheOidResetter;
        
    private:
        std::size_t oid_;
    };
}
