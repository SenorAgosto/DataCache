#pragma once
#include <DataCache/Details/FieldRegistrationLatch.hpp>

namespace DataCache {
 
    // A mixin which declares a field to be stored in the <DataCache>
    //
    // This class looks up the <DataCache> on <UsingDataCacheIn> and
    // registers a field of the desired <BlockType>. The local fieldId
    // is forwarded to <UsingDataCacheIn> which will maintain the mapping
    // between the local fieldId values and the DataCache assigned value
    // for the field.
    template<class BaseType, std::size_t FieldID, typename FieldType>
    class DataBlock
    {
    public:
        DataBlock()
        {
            static Details::FieldRegistrationLatch<BaseType, FieldType> field(FieldID);
        }
    };
    
}
