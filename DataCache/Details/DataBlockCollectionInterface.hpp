#pragma once

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
}}
