#pragma once

namespace DataCache { namespace Details {
    
    // A helper to invoke BaseType::register_field.
    //
    // It is intended to be used in conjection with a function local
    // static to provide a latch (ensure we register fields only once).
    template<class BaseType, class FieldType>
    class FieldRegistrationLatch
    {
    public:
        FieldRegistrationLatch(const std::size_t fieldId)
        {
            BaseType::template register_field<FieldType>(fieldId);
        }
    };
}}
