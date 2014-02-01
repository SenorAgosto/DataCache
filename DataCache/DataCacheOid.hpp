#pragma once
#include <DataCache/ObjectCounter.hpp>
#include <cstddef>

namespace DataCache { namespace Testing {
    class DataCacheOidResetter;
}}

namespace DataCache {
    
    // Object Id base class.
    //
    // Every object stored in the data cache needs
    // to inherit from DataCacheOid. All data cache
    // entries are referenced using the object's <oid_>
    //
    // The copy constructor and assignment operators create
    // new OIDs. The move constructor and assignment operators
    // use the same oid as the moved object, assuming ownership
    // of the DataCache locations referenced by this OID.
    class DataCacheOid : private ObjectCounter<Details::CountAllObjects>
    {
    public:
        DataCacheOid();
        
        DataCacheOid(const DataCacheOid& cache);
        DataCacheOid(DataCacheOid&& cache);
        
        DataCacheOid& operator=(const DataCacheOid& cache);
        DataCacheOid& operator=(DataCacheOid&&);
        
        inline std::size_t oid(void) const { return oid_; }
        
    private:
        friend class Testing::DataCacheOidResetter;

    private:
        std::size_t oid_;
    };
}
