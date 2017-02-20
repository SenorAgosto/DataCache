#pragma once

namespace DataCache { namespace Details {

    // Forward declare DataCache.
    class DataCache;
    
    // A helper class that can be instantiated as a function local static to create a latch.
    // @destination the save address of <source> into this destination.
    // @source a fully constructed <DataCache> we want to use.
    class DataCacheSetter
    {
    public:
        DataCacheSetter(DataCache*& destination, DataCache& source);
    };
}}
