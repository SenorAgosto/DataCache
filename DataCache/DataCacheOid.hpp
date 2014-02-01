#pragma once
#include <cstddef>

namespace DataCache {

    // Object Id base class.
    //
    // Every object stored in the data cache needs
    // to inherit from DataCacheOid. All data cache
    // entries are referenced using the object's <oid_>
    class DataCacheOid
    {
    public:
        DataCacheOid();
        
        inline std::size_t oid(void) const { return oid_; }
        
    private:
        std::size_t oid_;
    };
}
