#pragma once
#include <cstddef>

namespace DataCache { namespace Testing {
  
    template<class BaseType>
    class UsingDataCacheInAccessor
    {
    public:
        UsingDataCacheInAccessor(const BaseType& object);
        
        // Return the DataCache assigned ID for the local field ID.
        std::size_t registered_id(const std::size_t localFieldId);
        
    private:
        const BaseType& object_;
    };
    
    template<class BaseType>
    UsingDataCacheInAccessor<BaseType>::UsingDataCacheInAccessor(const BaseType& object)
        : object_(object)
    {
    }
    
    template<class BaseType>
    std::size_t UsingDataCacheInAccessor<BaseType>::registered_id(const std::size_t localFieldId)
    {
        return object_.registered_id(localFieldId);
    }
}}