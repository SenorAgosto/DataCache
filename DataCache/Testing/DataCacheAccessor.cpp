#include <DataCache/Testing/DataCacheAccessor.hpp>
#include <DataCache/DataCache.hpp>

namespace DataCache { namespace Testing {
    
    DataCacheAccessor::DataCacheAccessor(DataCache& cache)
        : cache_(cache)
    {
    }
    
    void DataCacheAccessor::clear(void)
    {
        cache_.blockMap_.clear();
    }
}}
