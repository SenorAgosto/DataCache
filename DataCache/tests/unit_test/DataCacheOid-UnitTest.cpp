#include <UnitTest++/UnitTest++.h>
#include <DataCache/src/DataCacheOid.hpp>

#include <DataCache/Testing/OidGeneratorResetter.hpp>

namespace {
    
    struct ObjectIdFixture
    {
        DataCache::Testing::OidGeneratorResetter oidResetter;
    };
    
    TEST(verifyObjectIdInstantiation)
    {
        DataCache::DataCacheOid id;
    }
    
    TEST_FIXTURE(ObjectIdFixture, verifyObjectIdInstantiationIsWhatIsIncrementedAsExpected)
    {
        DataCache::DataCacheOid id;
        CHECK_EQUAL(0U, id.oid());
        
        DataCache::DataCacheOid id2;
        CHECK_EQUAL(1U, id2.oid());
    }
    
    class MyObject : DataCache::DataCacheOid
    {
    };
    
    TEST_FIXTURE(ObjectIdFixture, verifyObjectsInheritingFromDataCacheOidIncrementOid)
    {
        MyObject object;
        CHECK_EQUAL(1U, DataCache::OidGenerator::GetObjectId());
        
        MyObject object2;
        CHECK_EQUAL(3U, DataCache::OidGenerator::GetObjectId());
    }
}
