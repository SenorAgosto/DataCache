#include <UnitTest++/UnitTest++.h>
#include <DataCache/DataCacheOid.hpp>

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
        // the move constructor should subsequently assume ownership of
        // that oid.
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
        
        object = MyObject();
        CHECK_EQUAL(2U, object.oid());
        
        object = std::move(object2);
        CHECK_EQUAL(1U, object.oid());
    }
}
