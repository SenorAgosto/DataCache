#pragma once
#include <DataCache/Details/DataBlockCollectionInterface.hpp>
#include <deque>

namespace DataCache { namespace Details {

    template<typename FieldType>
    class DataBlockCollection : public DataBlockCollectionInterface
    {
    public:
        // begin/end
        // cbegin/cend
        // operator[]   (to range check or not).
        
        // do not expose push()
        
        // Insert 
        void create_object(const std::size_t oid);
        
        
        inline bool empty(void) const;
        
    private:
        std::deque<FieldType> blocks_;
    };
    
    template<typename FieldType>
    bool DataBlockCollection<FieldType>::empty(void) const
    {
        return blocks_.empty();
    }
}}
