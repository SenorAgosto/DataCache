#pragma once
#include <atomic>
#include <cstddef>

namespace DataCache { namespace Testing {
    class OidGeneratorResetter;
}}

namespace DataCache {

    // Singleton used to manage Object IDs in the DataCache
    class OidGenerator
    {
    public:
        OidGenerator()
        {
        }
        
        inline static std::size_t GetObjectId(void)
        {
            return currentOid_++;
        }
        
    private:
        friend class Testing::OidGeneratorResetter;
        
        OidGenerator(const OidGenerator&) = delete;
        OidGenerator& operator=(const OidGenerator&) = delete;
        
    private:
        static std::atomic<std::size_t> currentOid_;
    };
}
