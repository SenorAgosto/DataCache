#pragma once
#include "DataCache/Source/OidGenerator.hpp"
#include <cstddef>

namespace DataCache { namespace Testing {

    class OidGeneratorResetter
    {
    public:
        OidGeneratorResetter(const std::size_t resetValue = 0)
        {
            OidGenerator::currentOid_ = resetValue;
        }
    };
}}
