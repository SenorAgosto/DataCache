#include <DataCache/DataCacheOid.hpp>
#include "OidGenerator.hpp"

namespace DataCache {

    DataCacheOid::DataCacheOid()
        : oid_(OidGenerator::GetObjectId())
    {
    }

}
