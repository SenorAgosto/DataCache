#include <DataCache/Details/DefaultDataCache.hpp>
#include <DataCache/DataCache.hpp>

namespace DataCache { namespace Details {
  
    DataCache& DefaultDataCache(void)
    {
        static DataCache cache_;
        return cache_;
    }
}}