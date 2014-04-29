#include <UnitTest++/UnitTest++.h>
#include <DataCache/DataCache.hpp>
#include <DataCache/Testing/DataCacheAccessor.hpp>

#include <cstdint>

namespace {
    
    static const uint32_t field1 = 1;
    using field1_type = uint32_t;
    
    struct MyClass
        : public DataCache::UsingDataCacheIn<MyClass>
        , private DataCache::DataBlock<MyClass, field1, field1_type>
    {
        MyClass(){}
        
        MyClass(std::size_t oid)
            : DataCache::UsingDataCacheIn<MyClass>(oid, DataCache::Details::NoCreate())
        {
        }
        
        std::size_t Oid(void) const { return oid(); }
    };
    
    TEST(verifyUsingDataCacheInMixinInstantiation)
    {
        MyClass object;
    }
    
    TEST(verifyUsingDataCacheInCopyConstructor)
    {
        MyClass object;
        MyClass object2(object);
        
        CHECK_EQUAL(object.Oid(), object2.Oid());
    }
    
    TEST(verifyUsingDataCacheInMoveConstructor)
    {
        auto cache = DataCache::Testing::DataCacheAccessor(MyClass::GetDataCache());
        auto initialSize = cache.size();
        
        MyClass object((MyClass()));
        
        auto currentSize = cache.size();
        CHECK_EQUAL(initialSize + 1, currentSize);
        CHECK_EQUAL(object.Oid(), object.Oid());
    }
    
    TEST(verifyUsingDataCacheAssignmentOperator)
    {
        MyClass object;
        MyClass object2;
        
        object = object2;
        CHECK_EQUAL(object.Oid(), object2.Oid());
    }
    
    TEST(verifyUsingDataCacheInMoveAssignmentOperator)
    {
        auto cache = DataCache::Testing::DataCacheAccessor(MyClass::GetDataCache());
        auto initialSize = cache.size();
        
        MyClass object = MyClass();
        
        auto currentSize = cache.size();
        CHECK_EQUAL(initialSize + 1, currentSize);
        CHECK_EQUAL(object.Oid(), object.Oid());
    }
    
    TEST(verifyUsingDataCacheInNoCreateConstructor)
    {
        auto cache = DataCache::Testing::DataCacheAccessor(MyClass::GetDataCache());
        auto initialSize = cache.size();
        
        MyClass object;
        MyClass object2(object.Oid());
        
        auto currentSize = cache.size();
        CHECK_EQUAL(initialSize + 1, currentSize);
        CHECK_EQUAL(object.Oid(), object.Oid());
    }
}