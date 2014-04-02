#include <DataCache/Testing/DataCacheAccessor.hpp>
#include <DataCache/Details/DataCache.hpp>

namespace DataCache { namespace Testing {
    
    DataCacheAccessor::DataCacheAccessor(Details::DataCache& cache)
        : cache_(cache)
    {
    }
    
    void DataCacheAccessor::clear(void)
    {
        cache_.blockMap_.clear();
    }
}}
