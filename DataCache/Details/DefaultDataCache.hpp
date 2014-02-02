#pragma once

namespace DataCache {
    class DataCache;
}

namespace DataCache { namespace Details {

    // A function creating a function local static instance of DataCache.
    DataCache& DefaultDataCache(void);
}}
