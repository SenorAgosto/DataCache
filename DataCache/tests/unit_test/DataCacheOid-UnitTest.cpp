#include "./platform/UnitTestSupport.hpp"
#include <DataCache/src/DataCacheOid.hpp>

#include <DataCache/Testing/DataCacheOidResetter.hpp>

namespace {
    
    struct ObjectIdFixture : private DataCache::Testing::DataCacheOidResetter
    {
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
    
    class MyObject : public DataCache::DataCacheOid
    {
    };
   
	class MyObject2 : public DataCache::DataCacheOid
    {
    }; 

    TEST_FIXTURE(ObjectIdFixture, verifyObjectsInheritingFromDataCacheOidIncrementOid)
    {
        MyObject object;
        CHECK_EQUAL(0U, object.oid());
        
        MyObject2 object2;
        CHECK_EQUAL(1U, object2.oid());
    }
}
