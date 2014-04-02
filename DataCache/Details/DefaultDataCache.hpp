#pragma once

namespace DataCache { namespace Details {

    // Forward Declare DataCache
    class DataCache;
    
    // A function creating a function local static instance of DataCache.
    DataCache& DefaultDataCache(void);
}}
