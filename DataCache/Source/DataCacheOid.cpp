#include "DataCacheOid.hpp"

namespace DataCache {

    DataCacheOid::DataCacheOid()
        : oid_(count() - 1)
    {
    }

    DataCacheOid::operator std::size_t()
    {
        return oid();
    }
    
    std::size_t DataCacheOid::oid(void) const
    {
        return oid_;
    }
}
