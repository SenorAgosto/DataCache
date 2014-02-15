#pragma once
#include <DataCache/Details/DataBlockCollection.hpp>
#include <DataCache/Exception/Exceptions.hpp>

#include <cstddef>
#include <memory>
#include <unordered_map>


namespace DataCache { namespace Testing {

    class DataCacheAccessor;
}}

namespace DataCache {

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

        template<typename FieldType>
        const Details::DataBlockCollection<FieldType>& get_collection(const std::size_t fieldId) const;
        
        template<typename FieldType>
        Details::DataBlockCollection<FieldType>& get_collection(const std::size_t fieldId);
        
        template<typename FieldType>
        const FieldType& get(const std::size_t oid, const std::size_t fieldId) const;
        
        template<typename FieldType>
        FieldType& get(const std::size_t oid, const std::size_t fieldId);
        
    private:
        friend class Testing::DataCacheAccessor;
        std::size_t next_id() const;

    private:
        using FieldId = std::size_t;
        using BlockCollectionHandle = std::unique_ptr<Details::DataBlockCollectionInterface>;
        std::unordered_map<FieldId, BlockCollectionHandle> blockMap_;
    };
    
    template<typename FieldType>
    std::size_t DataCache::register_field(void)
    {
        auto fieldId = next_id();
        blockMap_.emplace(fieldId, BlockCollectionHandle(new Details::DataBlockCollection<FieldType>()));
        
        return fieldId;
    }

    template<typename FieldType>
    const Details::DataBlockCollection<FieldType>& DataCache::get_collection(const std::size_t fieldId) const
    {
        auto collection_iter = blockMap_.find(fieldId);
        if(collection_iter == blockMap_.end())
        {
            throw Exception::AccessingUnRegisteredFieldId(fieldId);
        }
        
        const auto typed_collection = static_cast<Details::DataBlockCollection<FieldType>*>(collection_iter->second.get());
        return *typed_collection;
    }
    
    template<typename FieldType>
    Details::DataBlockCollection<FieldType>& DataCache::get_collection(const std::size_t fieldId)
    {
        auto collection_iter = blockMap_.find(fieldId);
        if(collection_iter == blockMap_.end())
        {
            throw Exception::AccessingUnRegisteredFieldId(fieldId);
        }
        
        auto typed_collection = static_cast<Details::DataBlockCollection<FieldType>*>(collection_iter->second.get());
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

}
