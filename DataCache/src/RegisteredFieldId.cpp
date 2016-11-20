#include "RegisteredFieldId.hpp"

namespace DataCache {

    RegisteredFieldId::RegisteredFieldId()
        : oid_(count() - 1)
    {
    }
    
    RegisteredFieldId::operator std::size_t()
    {
        return oid();
    }
    
    std::size_t RegisteredFieldId::oid(void) const
    {
        return oid_;
    }
}