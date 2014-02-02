#pragma once
#include <deque>

namespace DataCache { namespace Details {

    // A base class for type erasure that defines no interface.
    //
    // Derived classes will be cast to their concrete types prior to
    // use.
    class DataBlockCollectionInterface
    {
    public:
        virtual ~DataBlockCollectionInterface() = 0;
    };
    
    template<class FieldType>
    class DataBlockCollection : public DataBlockCollectionInterface
    {
    private:
        std::deque<FieldType> blocks_;
    };
}}
