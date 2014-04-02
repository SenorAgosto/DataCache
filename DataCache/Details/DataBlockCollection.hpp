#pragma once
#include <DataCache/Details/DataBlockCollectionInterface.hpp>
#include <DataCache/Details/DebugHelpers.hpp>

#include <deque>

namespace DataCache { namespace Details {

    // FieldType needs to be default constructable.
    template<typename FieldType>
    class DataBlockCollection : public DataBlockCollectionInterface
    {
    public:
        using BlocksContainer = std::deque<FieldType>;

        using iterator = typename BlocksContainer::iterator;
        using const_iterator = typename BlocksContainer::const_iterator;
        
        DataBlockCollection();
        
        // begin iterators
        iterator begin(void);
        const_iterator begin(void) const;
        const_iterator cbegin(void) const;
        
        // end iterators
        iterator end(void);
        const_iterator end(void) const;
        const_iterator cend(void) const;
        
        // operator[] without range checking.
        const FieldType& operator[](const std::size_t location) const;
        FieldType& operator[](const std::size_t location);
        
        // at() with range checking...
        const FieldType& at(const std::size_t location) const;
        FieldType& at(const std::size_t location);
        
        // True if collection is empty.
        inline bool empty(void) const;
        
        // Returns the current size of the collection.
        inline std::size_t size(void) const;
        
        
        
        // Insert a data block into the collection.
        //
        // We pass <oid> here because future implementations
        // of DataCache may use sparse collections to avoid
        // allocating memory when the allocated object is
        // not the correct type. Or something like that.
        void create_object(const std::size_t oid) override;
        
    private:
        BlocksContainer blocks_;
    };
    
    template<typename FieldType>
    DataBlockCollection<FieldType>::DataBlockCollection()
    {
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::iterator DataBlockCollection<FieldType>::begin(void)
    {
        return blocks_.begin();
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::const_iterator DataBlockCollection<FieldType>::begin(void) const
    {
        return blocks_.begin();
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::const_iterator DataBlockCollection<FieldType>::cbegin(void) const
    {
        return blocks_.cbegin();
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::iterator DataBlockCollection<FieldType>::end(void)
    {
        return blocks_.end();
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::const_iterator DataBlockCollection<FieldType>::end(void) const
    {
        return blocks_.end();
    }
    
    template<typename FieldType>
    typename DataBlockCollection<FieldType>::const_iterator DataBlockCollection<FieldType>::cend(void) const
    {
        return blocks_.cend();
    }

    template<typename FieldType>
    const FieldType& DataBlockCollection<FieldType>::operator[](const std::size_t location) const
    {
        return blocks_[location];
    }
    
    template<typename FieldType>
    FieldType& DataBlockCollection<FieldType>::operator[](const std::size_t location)
    {
        return blocks_[location];
    }
    
    template<typename FieldType>
    const FieldType& DataBlockCollection<FieldType>::at(const std::size_t location) const
    {
        return blocks_.at(location);
    }
    
    template<typename FieldType>
    FieldType& DataBlockCollection<FieldType>::at(const std::size_t location)
    {
        return blocks_.at(location);
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
    
    template<typename FieldType>
    void DataBlockCollection<FieldType>::create_object(const std::size_t oid)
    {
        CheckNonDuplicateOidWhenInDebug(oid, blocks_.size());
        
        blocks_.emplace_back();
        
        CheckOidIncreasedByOneInDebug(blocks_.size(), oid);
    }
    
    // Free-Function begin()
    template<typename FieldType>
    inline typename DataBlockCollection<FieldType>::iterator begin(DataBlockCollection<FieldType>& collection)
    {
        return collection.begin();
    }
    
    // Free-Function const begin()
    template<typename FieldType>
    inline typename DataBlockCollection<FieldType>::const_iterator begin(const DataBlockCollection<FieldType>& collection)
    {
        return collection.cbegin();
    }
    
    // Free-Function end()
    template<typename FieldType>
    inline typename DataBlockCollection<FieldType>::iterator end(DataBlockCollection<FieldType>& collection)
    {
        return collection.end();
    }
    
    // Free-Function const end()
    template<typename FieldType>
    inline typename DataBlockCollection<FieldType>::const_iterator end(const DataBlockCollection<FieldType>& collection)
    {
        return collection.cend();
    }
}}
