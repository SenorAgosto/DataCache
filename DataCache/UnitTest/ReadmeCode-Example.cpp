#include <UnitTest++/UnitTest++.h>
#include <DataCache/DataCache.hpp>

namespace {

    // Use a traits class to hold mapping of field name to type.
    struct Fields
    {
        // define field names
        enum MyFields {
            field_1,
            field_2
        };
        
        // define field types
        using field_1_type = uint64_t;
        using field_2_type = uint32_t;
    };
    
    // Declare a type using the DataCache
    struct MyObject
    : public DataCache::UsingDataCacheIn<MyObject>
    , public DataCache::DataBlock<MyObject, Fields::field_1, Fields::field_1_type>
    , public DataCache::DataBlock<MyObject, Fields::field_2, Fields::field_2_type>
    {
        void Foo(void);
    };

    TEST(verifyReadmeExampleCodeCompiles)
    {
        MyObject object;
    }
}