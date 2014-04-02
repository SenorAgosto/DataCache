#pragma once
#include <DataCache/Details/DataBlockCollection.hpp>
#include <DataCache/Exception/Exceptions.hpp>

#include <cstddef>
#include <memory>
#include <unordered_map>


namespace DataCache { namespace Testing {

    class DataCacheAccessor;
}}

namespace DataCache { namespace Details {

    // The DataCache maintains the memory organization for the cached fields.
    //
    // The DataCache holds the <DataCacheCollections> which in turn hold the
    // contiguously laid out data fields (which can be groups of intrinsic types
    // or classes).
    //
    // This is the main event for Data Oriented Design.
    class DataCache
    {
    public:
        DataCache() = default;
        
        // Creates a collection of FieldType objects in the DataCache.
        //
        // @return the field ID for the registered field, used to get
        // a handle on the data later.
        template<typename FieldType>
        std::size_t register_field(void);

        // Returns a const collection of fields that can be iterated over enmass.
        template<typename FieldType>
        const DataBlockCollection<FieldType>& get_collection(const std::size_t fieldId) const;
        
        // Returns a collection of fields that can be iterated over to manipulate enmass.
        template<typename FieldType>
        DataBlockCollection<FieldType>& get_collection(const std::size_t fieldId);
        
        // Returns a const reference to a specific field for an object (referenced by OID).
        template<typename FieldType>
        const FieldType& get(const std::size_t oid, const std::size_t fieldId) const;
        
        // Returns a reference to a specific field for an object (referenced by OID).
        template<typename FieldType>
        FieldType& get(const std::size_t oid, const std::size_t fieldId);
        
        // Inserts an object into the DataCache.
        //
        // @return the oid of the object. The OID is used to by the object to
        // access data member fields stored in the cache.
        template<class BaseType>
        std::size_t create_object(void);
        
    private:
        friend class Testing::DataCacheAccessor;
        std::size_t next_field_id() const;
        std::size_t next_oid() const;
        
    private:
        using FieldId = std::size_t;
        using BlockCollectionHandle = std::unique_ptr<DataBlockCollectionInterface>;
        using BlockMapType = std::unordered_map<FieldId, BlockCollectionHandle>;
        
        BlockMapType blockMap_;
    };
    
    template<typename FieldType>
    std::size_t DataCache::register_field(void)
    {
        BlockCollectionHandle handle(new DataBlockCollection<FieldType>());
        
        auto fieldId = next_field_id();
        blockMap_.emplace(fieldId, std::move(handle));
        
        return fieldId;
    }

    template<typename FieldType>
    const DataBlockCollection<FieldType>& DataCache::get_collection(const std::size_t fieldId) const
    {
        auto collection_iter = blockMap_.find(fieldId);
        if(collection_iter == blockMap_.end())
        {
            throw Exception::AccessingUnRegisteredFieldId(fieldId);
        }
        
        const auto typed_collection = static_cast<DataBlockCollection<FieldType>*>(collection_iter->second.get());
        return *typed_collection;
    }
    
    template<typename FieldType>
    DataBlockCollection<FieldType>& DataCache::get_collection(const std::size_t fieldId)
    {
        auto collection_iter = blockMap_.find(fieldId);
        if(collection_iter == blockMap_.end())
        {
            throw Exception::AccessingUnRegisteredFieldId(fieldId);
        }
        
        auto typed_collection = static_cast<DataBlockCollection<FieldType>*>(collection_iter->second.get());
        return *typed_collection;
    }

    template<typename FieldType>
    const FieldType& DataCache::get(const std::size_t oid, const std::size_t fieldId) const
    {
        const auto& collection = get_collection<FieldType>(fieldId);
        return collection[oid];
    }
    
    template<typename FieldType>
    FieldType& DataCache::get(const std::size_t oid, const std::size_t fieldId)
    {
        auto& collection = get_collection<FieldType>(fieldId);
        return collection[oid];
    }

    template<class BaseType>
    std::size_t DataCache::create_object(void)
    {
        // [ARG]:
        // Some careful consideration needs to be put in here.
        // Possibly moving some of the logic here to a policy so it can be overriden.
        // Currently, we are just going to create_object through the base class BlockCollectionHandle.
        // However, it could be possible to something fancier... where we don't necessarily allocate
        // space in every collection but allocate based on the object type.
        //
        // For now, however, to get things up and working, simply add a spot in every collection.
        std::size_t oid = next_oid();
        
        std::for_each(begin(blockMap_), end(blockMap_), [oid](BlockMapType::value_type& pair)
        {
            auto& collection_handle = pair.second;
            collection_handle->create_object(oid);
        });
        
        return oid;
    }
}}
