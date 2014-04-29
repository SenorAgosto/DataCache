#pragma once
#include <DataCache/Details/DataCache.hpp>
#include <DataCache/Details/DefaultDataCache.hpp>
#include <DataCache/Details/DataCacheSetter.hpp>
#include <DataCache/Details/TagTypes.hpp>
#include <DataCache/Exception/Exceptions.hpp>

#include <unordered_map>

namespace DataCache { namespace Details {

    template<class AccessorBaseType, typename AccessorFieldType>
    class FieldRegistrationLatch;
}}

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
        // Returns a single const DataBlock entry from the cache.
        // @oid the object ID to lookup
        // @fieldId the field to get (as FieldType) using local fieldId label.
        template<typename FieldType>
        static inline const FieldType& get_const(const std::size_t oid, const std::size_t fieldId)
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
        static void SetDataCache(Details::DataCache& cache);
        
        // Return a reference to our DataCache
        static inline Details::DataCache& GetDataCache(void);

    protected:
        // Add an entry in the DataCache for this object type.
        UsingDataCacheIn();

        // Create a DataCache reference using already existing cache entry.
        UsingDataCacheIn(const std::size_t oid, Details::NoCreate);
        
        // Copy constructor which assigns the <oid_>
        // based on existing oid.
        UsingDataCacheIn(const UsingDataCacheIn& rhs);
        
        // Move constructor.
        UsingDataCacheIn(UsingDataCacheIn&& rhs);
        
        // Assignment operator.
        UsingDataCacheIn& operator=(const UsingDataCacheIn& rhs);

        // Move Assignment operator.
        UsingDataCacheIn& operator=(UsingDataCacheIn&& rhs);
        
        // Return our object's oid.
        inline std::size_t oid(void) const;

        // Create an entry in the DataCache, type is FieldType and
        template<typename FieldType>
        static void register_field(const std::size_t fieldId)
        {
            auto registeredFieldId = cache_->register_field<FieldType>();
            fieldIdMap_.emplace(fieldId, registeredFieldId);
        }
        
    private:
        
        // Lookup the DataCache registered field ID from the local <fieldId>
        // @fieldId the local field id to find.
        //
        // @return the DataCache assigned field ID.
        static std::size_t registered_id(std::size_t fieldId);

    // instance data
    private:
        std::size_t oid_;
    
    // static data
    private:
        template<class AccessorBaseType> friend class Testing::UsingDataCacheInAccessor;
        template<class AccessorBaseType, typename AccessorFieldType> friend class Details::FieldRegistrationLatch;
        
        static Details::DataCache* cache_;
        
        // Map LocalFieldId's to RegisteredFieldIds.
        // TODO: possibly move this to a policy.
        using RegisteredFieldId = std::size_t;
        using LocalFieldId = std::size_t;
        static std::unordered_map<LocalFieldId, RegisteredFieldId> fieldIdMap_;
    };
    
    template<class BaseType>
    Details::DataCache* UsingDataCacheIn<BaseType>::cache_ = &(Details::DefaultDataCache());
    
    template<class BaseType>
    std::unordered_map<std::size_t, std::size_t> UsingDataCacheIn<BaseType>::fieldIdMap_;
    

    //static
    template<class BaseType>
    void UsingDataCacheIn<BaseType>::SetDataCache(Details::DataCache& cache)
    {
        static Details::DataCacheSetter setter(cache_, cache);
    }
    
    //static
    template<class BaseType>
    inline Details::DataCache& UsingDataCacheIn<BaseType>::GetDataCache(void)
    {
        return *cache_;
    }

    
    template<class BaseType>
    UsingDataCacheIn<BaseType>::UsingDataCacheIn()
        : oid_(cache_->create_object<BaseType>())
    {
    }
    
    template<class BaseType>
    UsingDataCacheIn<BaseType>::UsingDataCacheIn(const std::size_t oid, Details::NoCreate)
        : oid_(oid)
    {
    }
    
    template<class BaseType>
    UsingDataCacheIn<BaseType>::UsingDataCacheIn(const UsingDataCacheIn<BaseType>& rhs)
        : oid_(rhs.oid_)
    {
    }
    
    template<class BaseType>
    UsingDataCacheIn<BaseType>::UsingDataCacheIn(UsingDataCacheIn<BaseType>&& rhs)
        : oid_(std::forward<decltype(oid_)>(rhs.oid_))
    {
    }
    
    template<class BaseType>
    UsingDataCacheIn<BaseType>& UsingDataCacheIn<BaseType>::operator=(const UsingDataCacheIn<BaseType>& rhs)
    {
        oid_ = rhs.oid_;
        return *this;
    }
    
    template<class BaseType>
    UsingDataCacheIn<BaseType>& UsingDataCacheIn<BaseType>::operator=(UsingDataCacheIn<BaseType>&& rhs)
    {
        oid_ = std::forward<decltype(oid_)>(rhs.oid_);
        return *this;
    }
    
    template<class BaseType>
    std::size_t UsingDataCacheIn<BaseType>::oid(void) const
    {
        return oid_;
    }
    
    
    // static
    template<class BaseType>
    std::size_t UsingDataCacheIn<BaseType>::registered_id(std::size_t fieldId)
    {
        auto iter = fieldIdMap_.find(fieldId);
        if(iter == fieldIdMap_.end())
        {
            throw Exception::AccessingUnRegisteredFieldId(fieldId);
        }
        
        auto registeredFieldId = iter->second;
        return registeredFieldId;
    }
    
}
