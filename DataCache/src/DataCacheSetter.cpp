#include <DataCache/Details/DataCacheSetter.hpp>

namespace DataCache { namespace Details {
  
    DataCacheSetter::DataCacheSetter(DataCache*& destination, DataCache& source)
    {
        destination = &source;
    }
}}