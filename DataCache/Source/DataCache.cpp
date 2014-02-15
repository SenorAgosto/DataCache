#include <DataCache/DataCache.hpp>
#include "RegisteredFieldId.hpp"

namespace DataCache {
    
    std::size_t DataCache::next_id(void) const
    {
        return RegisteredFieldId();
    }    
}
