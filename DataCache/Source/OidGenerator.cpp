#include "./OidGenerator.hpp"

namespace DataCache {
    
    //static
    std::atomic<std::size_t> OidGenerator::currentOid_(0);
}
