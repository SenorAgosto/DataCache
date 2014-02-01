#include <UnitTest++/UnitTest++.h>

#include <DataCache/ObjectCounter.hpp>
#include <DataCache/Testing/ObjectCounterResetter.hpp>

namespace {

    struct MyCountedType : public DataCache::ObjectCounter<MyCountedType>
    {
    };
    
    struct MyCountedType2 : public DataCache::ObjectCounter<MyCountedType2>
    {
    };
    
    TEST(verifyObjectCounterInstantiationWithMultipleCountedTypes)
    {
        MyCountedType object;
        CHECK_EQUAL(1U, object.Count());
        
        MyCountedType2 object2;
        CHECK_EQUAL(1U, object.Count());
    }
    
    struct ObjectCountFixture
        : DataCache::Testing::ObjectCounterResetter<MyCountedType>
        , DataCache::Testing::ObjectCounterResetter<MyCountedType2>
    {
    };
    
    TEST_FIXTURE(ObjectCountFixture, verifyObjectCounter)
    {
        MyCountedType object;
        CHECK_EQUAL(1U, object.Count());
        
        MyCountedType2 object2;
        CHECK_EQUAL(1U, object2.Count());
        
        MyCountedType object3;
        CHECK_EQUAL(2U, object3.Count());
        
        MyCountedType2 object4;
        CHECK_EQUAL(2U, object4.Count());
    }
}