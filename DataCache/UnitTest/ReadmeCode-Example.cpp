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
    class MyObject
        : public  DataCache::UsingDataCacheIn<MyObject>
        , private DataCache::DataBlock<MyObject, Fields::field_1, Fields::field_1_type>
        , private DataCache::DataBlock<MyObject, Fields::field_2, Fields::field_2_type>
    {
    public:
        void Foo(void);
    };

    void MyObject::Foo(void)
    {
		// the only inconvenience is we have to use our OID to
		// get the location of our fields we want to modify here.
		auto& field1 = get<Fields::field_1_type>(oid(), Fields::field_1);
		auto& field2 = get<Fields::field_2_type>(oid(), Fields::field_2);
        
		field1 += field2;
		field2 /= 2;
    }
    
    TEST(verifyReadmeExampleCodeCompiles)
    {
        MyObject object;
    }
}