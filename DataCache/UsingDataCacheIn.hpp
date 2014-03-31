#pragma once
#include <DataCache/DataCache.hpp>
#include <DataCache/Details/DefaultDataCache.hpp>
#include <DataCache/Details/DataCacheSetter.hpp>
#include <DataCache/Exception/Exceptions.hpp>

#include <unordered_map>

namespace DataCache { namespace Testing {
    
    template<class BaseType>
    class UsingDataCacheInAccessor;
}}

namespace DataCache {
    
    // A mixin indicating use of DataCache by a client class.
    //
    // Use this mixin to indicate we need to store data fields
    // for BaseType in the <DataCache>. This class handles the
    // BaseType local field IDs to DataCache registered field IDs.
    // It is also utilized by <DataBlock> mixin to connect to the
    // DataCache as a reference to the DataCache is held shere.
    template<class BaseType>
    class UsingDataCacheIn
    {
    public:
        // Create an entry in the DataCache, type is FieldType and
        template<typename FieldType>
        static void register_field(const std::size_t fieldId)
        {
            auto registeredFieldId = cache_->register_field<FieldType>();
            fieldIdMap_.emplace(fieldId, registeredFieldId);
        }

        // Returns a single const DataBlock entry from the cache.
        // @oid the object ID to lookup
        // @fieldId the field to get (as FieldType) using local fieldId label.
        template<typename FieldType>
        static inline const FieldType& get(const std::size_t oid, const std::size_t fieldId)
        {
            return cache_->get<FieldType>(oid, registered_id(fieldId));
        }
        
        // Returns a single DataBlock entry from the cache.
        // @oid the object ID to lookup
        // @fieldId the field to get (as FieldType) using local fieldId label.
        template<typename FieldType>
        static inline FieldType& get(const std::size_t oid, const std::size_t fieldId)
        {
            return cache_->get<FieldType>(oid, registered_id(fieldId));
        }
        
        template<typename FieldType>
        static inline const Details::DataBlockCollection<FieldType>& const_collection(const std::size_t fieldId)
        {
            return cache_->get_collection<FieldType>(registered_id(fieldId));
        }
        
        template<typename FieldType>
        static inline Details::DataBlockCollection<FieldType>& collection(const std::size_t fieldId)
        {
            return cache_->get_collection<FieldType>(registered_id(fieldId));
        }
        
        // Allow overriding of the DataCache we are working with.
        //
        // This can be called only once per program, and must
        // happen prior to any BaseType allocations.
        static void SetDataCache(DataCache& cache)
        {
            static Details::DataCacheSetter setter(cache_, cache);
        }
        
        // Return a reference to our DataCache
        static DataCache& GetDataCache(void)
        {
            return *cache_;
        }

    protected:
        // Add an entry in the DataCache for this object type.
        UsingDataCacheIn()
            : oid_(cache_->create_object<BaseType>())
        {
        }
        
        // Return our object's oid.
        std::size_t oid(void) const
        {
            return oid_;
        }
        
    private:
        
        // Lookup the DataCache registered field ID from the local <fieldId>
        // @fieldId the local field id to find.
        //
        // @return the DataCache assigned field ID.
        static std::size_t registered_id(std::size_t fieldId)
        {
            auto iter = fieldIdMap_.find(fieldId);
            if(iter == fieldIdMap_.end())
            {
                throw Exception::AccessingUnRegisteredFieldId(fieldId);
            }
            
            auto registeredFieldId = iter->second;
            return registeredFieldId;
        }

    // instance data
    private:
        std::size_t oid_;
    
    // static data
    private:
        template<class AccessorBaseType> friend class Testing::UsingDataCacheInAccessor;
        
        static DataCache* cache_;
        
        // Map LocalFieldId's to RegisteredFieldIds.
        // TODO: possibly move this to a policy.
        using RegisteredFieldId = std::size_t;
        using LocalFieldId = std::size_t;
        static std::unordered_map<LocalFieldId, RegisteredFieldId> fieldIdMap_;
    };
    
    template<class BaseType>
    DataCache* UsingDataCacheIn<BaseType>::cache_ = &(Details::DefaultDataCache());
    
    template<class BaseType>
    std::unordered_map<std::size_t, std::size_t> UsingDataCacheIn<BaseType>::fieldIdMap_;
}