#pragma once
#include <stdexcept>
#include <cstddef>

namespace DataCache { namespace Exception {
    
    class AccessingUnRegisteredFieldId : public std::runtime_error
    {
    public:
        AccessingUnRegisteredFieldId(const std::size_t fieldId);
    };
    
}}