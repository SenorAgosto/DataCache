#pragma once
#include <stdexcept>
#include <cstddef>

namespace DataCache { namespace Exception {
    
    class AccessingUnRegisteredFieldId : public std::runtime_error
    {
    public:
        AccessingUnRegisteredFieldId(const std::size_t fieldId);
    };
    
    class OidOutOfRange : public std::range_error
    {
    public:
        OidOutOfRange(const std::size_t oid);
    };
}}