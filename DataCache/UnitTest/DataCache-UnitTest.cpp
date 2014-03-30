#include <UnitTest++/UnitTest++.h>

#include <DataCache/DataBlock.hpp>
#include <DataCache/DataCache.hpp>
#include <DataCache/UsingDataCacheIn.hpp>

#include <DataCache/Testing/DataCacheAccessor.hpp>

#include <cstdint>

namespace {
    
    // define a local field ID value.
    enum MyFields {
        field_1 = 0,
        field_2 = 10
    };
    
    // a struct to demonstrate DataBlocks don't
    // have to be a single field. There is a reason
    // they aren't called DataFields ;)
    //
    // Pro tip: When performing operations where
    // locality of reference of operands is important
    // for performance, group these operands together
    // in the same DataBlock.
    struct GroupedDataBlock
    {
        uint64_t value0;
        uint32_t value1;
        uint16_t value2;
        uint16_t value3;
    };
    
    // There is a fairly tight coupling between <DataCache::DataBlock>
    // and <DataCache::UsingDataCacheIn>. UsingDataCacheIn holds the
    // reference to the <DataCache::DataCache> and the mapping between
    // local field ID and the assigned field ID on registration.
    //
    // Here DataCache::UsingDataCacheIn and DataCache::DataBlock are
    // public purely so we can poke values in the unit test. Typically,
    // you'll make these private.
    struct MyObject
        : public DataCache::UsingDataCacheIn<MyObject>
        , public DataCache::DataBlock<MyObject, field_1, uint8_t>
    {
    };
    
    struct MyOtherObject
        : public DataCache::UsingDataCacheIn<MyOtherObject>
        , public DataCache::DataBlock<MyOtherObject, field_1, uint32_t>
        , public DataCache::DataBlock<MyOtherObject, field_2, uint32_t>
    {
    };
    
    struct MyGroupedDataObject
        : public DataCache::UsingDataCacheIn<MyGroupedDataObject>
        , public DataCache::DataBlock<MyGroupedDataObject, field_1, GroupedDataBlock>
    {
    };
    
    struct DataCacheFixture : public DataCache::Testing::DataCacheAccessor
    {
        DataCacheFixture()
            : DataCache::Testing::DataCacheAccessor(MyObject::GetDataCache())
        {
        }
    };
    
    // This test primarily exists to ensure fields get registered.
    TEST(verifyDataBlockInstantiation)
    {
        MyObject object;
        MyOtherObject otherObject;
        MyGroupedDataObject groupedObject;
    }
    
    TEST_FIXTURE(DataCacheFixture, verifyRegistrationOfDataBlock)
    {
//        MyObject object;
//        CHECK_EQUAL(0U, object.registeredId(field_1));
//        
//        MyObject objectB;
//        CHECK_EQUAL(0U, objectB.registeredId(field_1));
//        
//        MyOtherObject object2;
//        CHECK_EQUAL(1U, object2.registeredId(field_1));
//        CHECK_EQUAL(2U, object2.registeredId(field_2));
        
        // TODO:
        // use the accessor to look under the covers of the DataCache to
        // determine that a field with our expected type was registered.
    }
    
    TEST_FIXTURE(DataCacheFixture, verifyDataCacheConstCollection)
    {
        const auto& field1_collection = MyOtherObject::const_collection<uint32_t>(field_1);
        CHECK(!field1_collection.empty());  // not equal because we created one on line 74
    }
    
    TEST_FIXTURE(DataCacheFixture, verifyDataCacheCollection)
    {
        auto& field2_collection = MyOtherObject::collection<uint32_t>(field_2);
        CHECK(!field2_collection.empty());  // not equal because we created one on line 74
    }
}