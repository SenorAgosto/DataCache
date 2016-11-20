#pragma once
#include <DataCache/ObjectCounter.hpp>
#include <cstddef>

namespace DataCache {
    
    class RegisteredFieldId : ObjectCounter<RegisteredFieldId>
    {
    public:
        RegisteredFieldId();
        operator std::size_t();
        
        std::size_t oid(void) const;
        
    private:
        std::size_t oid_;
    };
}