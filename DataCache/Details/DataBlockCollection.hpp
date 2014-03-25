#pragma once
#include <DataCache/Details/DataBlockCollectionInterface.hpp>
#include <DataCache/Exception/Exceptions.hpp>

#include <deque>

namespace DataCache { namespace Details {

    // FieldType needs to be default constructable.
    template<typename FieldType>
    class DataBlockCollection : public DataBlockCollectionInterface
    {
    public:
        // TODO:
        // begin/end
        // cbegin/cend
        // operator[]   (no range checking).
        // at() (range checking).
        
        // do not expose push()
        
        // Insert a data block into the collection.
        void create_object(const std::size_t oid) override;
        
        // True if collection is empty.
        inline bool empty(void) const;
        
    private:
        std::deque<FieldType> blocks_;
    };
    
    template<typename FieldType>
    void DataBlockCollection<FieldType>::create_object(const std::size_t oid)
    {
        blocks_.emplace_back();
        
        // Debug Only???
        if(blocks_.size() <= oid)
        {
            throw Exception::OidOutOfRange(oid);
        }
    }
    
    template<typename FieldType>
    bool DataBlockCollection<FieldType>::empty(void) const
    {
        return blocks_.empty();
    }
    
}}
