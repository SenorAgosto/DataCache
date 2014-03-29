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
        using BlocksContainer = std::deque<FieldType>;
        
        // TODO:
        // begin/end
        typename BlocksContainer::iterator begin(void);
        typename BlocksContainer::const_iterator begin(void) const;
        typename BlocksContainer::const_iterator cbegin(void) const;
        
        typename BlocksContainer::iterator end(void);
        typename BlocksContainer::const_iterator end(void) const;
        typename BlocksContainer::const_iterator cend(void) const;
        
        // operator[]   (get specific object without range checking).
        // at() (get specific object with range checking).
        
        // do not expose push()
        
        // Insert a data block into the collection.
        void create_object(const std::size_t oid) override;
        
        // True if collection is empty.
        inline bool empty(void) const;
        
        // Returns the current size of the collection.
        inline std::size_t size(void) const;
        
    private:
        BlocksContainer blocks_;
    };
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::BlocksContainer::iterator DataBlockCollection<FieldType>::begin(void)
    {
        return blocks_.begin();
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::BlocksContainer::const_iterator DataBlockCollection<FieldType>::begin(void) const
    {
        return blocks_.begin();
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::BlocksContainer::const_iterator DataBlockCollection<FieldType>::cbegin(void) const
    {
        return blocks_.cbegin();
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::BlocksContainer::iterator DataBlockCollection<FieldType>::end(void)
    {
        return blocks_.end();
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::BlocksContainer::const_iterator DataBlockCollection<FieldType>::end(void) const
    {
        return blocks_.end();
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::BlocksContainer::const_iterator DataBlockCollection<FieldType>::cend(void) const
    {
        return blocks_.cend();
    }
    
    template<typename FieldType>
    void DataBlockCollection<FieldType>::create_object(const std::size_t oid)
    {
        // Debug Only???
        if(oid < blocks_.size())
        {
            throw Exception::OidOutOfRange(oid);
        }
        
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
    
    template<typename FieldType>
    std::size_t DataBlockCollection<FieldType>::size(void) const
    {
        return blocks_.size();
    }
}}
