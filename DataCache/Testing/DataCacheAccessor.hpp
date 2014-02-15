#pragma once

namespace DataCache { namespace Testing {

    // A test helper for getting access to private data on the <DataCache>
    class DataCacheAccessor
    {
    public:
        DataCacheAccessor(DataCache& cache)
            : cache_(cache)
        {
        }

    private:
        DataCache& cache_;
    };
}}
