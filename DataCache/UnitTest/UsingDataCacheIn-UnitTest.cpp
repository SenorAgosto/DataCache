#include <UnitTest++/UnitTest++.h>
#include <DataCache/UsingDataCacheIn.hpp>

namespace {
    
    struct MyClass : private DataCache::UsingDataCacheIn<MyClass>
    {
        MyClass(){}
    };
    
    TEST(verifyUsingDataCacheInMixinInstantiation)
    {
        MyClass object;
    }
}