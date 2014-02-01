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

    struct MyNoIncrementType : public DataCache::ObjectCounter<MyNoIncrementType>
    {
        using base_t = DataCache::ObjectCounter<MyNoIncrementType>;
        
        MyNoIncrementType()
            : base_t(DataCache::Details::NoIncrement())
        {
        }
                         
    };
    
    struct ObjectCountFixture
        : DataCache::Testing::ObjectCounterResetter<MyCountedType>
        , DataCache::Testing::ObjectCounterResetter<MyCountedType2>
    {
    };

    TEST(verifyObjectCounterInstantiationWithMultipleCountedTypes)
    {
        MyCountedType object;
        CHECK_EQUAL(1U, object.count());
        
        MyCountedType2 object2;
        CHECK_EQUAL(1U, object.count());
    }
    
    TEST_FIXTURE(ObjectCountFixture, verifyObjectCounter)
    {
        MyCountedType object;
        CHECK_EQUAL(1U, object.count());
        
        MyCountedType2 object2;
        CHECK_EQUAL(1U, object2.count());
        
        MyCountedType object3;
        CHECK_EQUAL(2U, object3.count());
        
        MyCountedType2 object4;
        CHECK_EQUAL(2U, object4.count());
    }
    
    TEST_FIXTURE(ObjectCountFixture, verifyObjectCounterNoIncrementConstructor)
    {
        MyNoIncrementType object;
        CHECK_EQUAL(0U, object.count());
        
        MyNoIncrementType object2;
        CHECK_EQUAL(0U, object2.count());
    }
}