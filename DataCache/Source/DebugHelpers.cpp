#include <DataCache/Details/DebugHelpers.hpp>
#include <DataCache/Exception/Exceptions.hpp>

namespace DataCache { namespace Details {

    void CheckNonDuplicateOidWhenInDebug(const std::size_t oid, const std::size_t blockSize)
    {
        #ifdef DEBUG
        if(oid < blockSize)
        {
            throw Exception::OidOutOfRange(oid);
        }
        #endif
    }
    
    void CheckOidIncreasedByOneInDebug(const std::size_t blockSize, const std::size_t oid)
    {
        #ifdef DEBUG
        if(blockSize <= oid)
        {
            throw Exception::OidOutOfRange(oid);
        }
        #endif
    }

}}