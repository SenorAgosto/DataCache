#include <UnitTest++/UnitTest++.h>
#include <DataCache/DataCacheOid.hpp>

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
    
    TEST_FIXTURE(ObjectIdFixture, verifyDataCacheOidCopyConstructor)
    {
        MyObject object;
        CHECK_EQUAL(0U, object.oid());
        
        MyObject object2(object);
        CHECK_EQUAL(1U, object2.oid());
    }
    
    TEST_FIXTURE(ObjectIdFixture, verifyDataCacheOidMoveConstructor)
    {
        // rvalue MyObject should create an oid with value 0,
        // The lvalue MyObject should create an oid with value 1,
        // subsequently the move constructor should assume ownership of
        // the rvalue object's oid.
        MyObject object( (MyObject()) );
        CHECK_EQUAL(0U, object.oid());
    }
    
    TEST_FIXTURE(ObjectIdFixture, verifyDataCacheOidAssignmentOperator)
    {
        MyObject object;
        CHECK_EQUAL(0U, object.oid());
        
        MyObject object2 = object;
        CHECK_EQUAL(1U, object2.oid());   // object2 is a copy and gets its own unique oid.
    }
    
    TEST_FIXTURE(ObjectIdFixture, verifyDataCacheOidMoveAssignmentOperator)
    {
        MyObject object;
        CHECK_EQUAL(0U, object.oid());
        
        MyObject object2;
        CHECK_EQUAL(1U, object2.oid());
        
        object = MyObject();            // the rvalue MyObject creates new oid, then we assume it.
        CHECK_EQUAL(2U, object.oid());
        
        object = std::move(object2);
        CHECK_EQUAL(1U, object.oid());
    }
}
