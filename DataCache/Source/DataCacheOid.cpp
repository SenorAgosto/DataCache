#include <DataCache/DataCacheOid.hpp>

namespace DataCache {

    namespace {
        // perform the oid offset that we would like to use
        // in the DataCache. In this case, we would like
        // OIDs to start at 0.
        inline std::size_t offset_oid(std::size_t value)
        {
            return value - 1;
        }
    }
    
    DataCacheOid::DataCacheOid()
        : oid_(offset_oid(count()))
    {
    }

    DataCacheOid::DataCacheOid(const DataCacheOid& cache)
        : oid_(offset_oid(count()))
    {
    }
    
    DataCacheOid::DataCacheOid(DataCacheOid&& cache)
        : ObjectCounter<Details::CountAllObjects>(Details::NoIncrement())
        , oid_(cache.oid_)
    {
    }
    
    DataCacheOid& DataCacheOid::operator=(const DataCacheOid& cache)
    {
        oid_ = offset_oid(count());
        return *this;
    }
    
    DataCacheOid& DataCacheOid::operator=(DataCacheOid&& cache)
    {
        oid_ = std::move(cache.oid_);
        return *this;
    }

}
