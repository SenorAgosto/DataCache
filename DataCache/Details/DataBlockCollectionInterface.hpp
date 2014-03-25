#pragma once
#include <cstddef>

namespace DataCache { namespace Details {
  
    // A base class for type erasure that defines minimal interface.
    //
    // Derived classes will be cast to their concrete types prior to
    // use, other than calling create_object()
    class DataBlockCollectionInterface
    {
    public:
        virtual ~DataBlockCollectionInterface() = 0;
        virtual void create_object(const std::size_t oid) = 0;
    };
}}
