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
    
    std::size_t DataCacheAccessor::size(void) const
    {
        std::size_t size = 0;
        
        const auto iter = cache_.blockMap_.begin();
        const auto end = cache_.blockMap_.end();
        
        if(iter != end)
        {
            auto& collection = cache_.get_collection<void*>(iter->first);
            size = collection.size();
        }
        
        return size;
    }
}}
