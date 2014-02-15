#include <DataCache/DataCache.hpp>
#include "RegisteredFieldId.hpp"
#include "DataCacheOid.hpp"

namespace DataCache {
    
    std::size_t DataCache::next_field_id(void) const
    {
        return RegisteredFieldId();
    }
    
    std::size_t DataCache::next_oid(void) const
    {
        return DataCacheOid();
    }
}
