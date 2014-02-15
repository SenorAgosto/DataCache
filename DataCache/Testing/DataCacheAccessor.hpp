#pragma once

namespace DataCache {
    class DataCache;
}

namespace DataCache { namespace Testing {

    // A test helper for getting access to private data on the <DataCache>
    class DataCacheAccessor
    {
    public:
        DataCacheAccessor(DataCache& cache);
        void clear(void);

    private:
        DataCache& cache_;
    };
}}
