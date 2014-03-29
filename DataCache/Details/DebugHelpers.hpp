#pragma once
#include <cstddef>

namespace DataCache { namespace Details {
    
    // Used to verify we aren't requesting a create with a duplicated OID.
    void CheckNonDuplicateOidWhenInDebug(const std::size_t oid, const std::size_t blockSize);
    
    // Used to verify we are requesting the next OID in the sequence without skipping any.
    void CheckOidIncreasedByOneInDebug(const std::size_t blockSize, const std::size_t oid);
}}
