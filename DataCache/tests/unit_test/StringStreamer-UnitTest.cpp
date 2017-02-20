#include "./platform/UnitTestSupport.hpp"
#include <DataCache/StringStreamer.hpp>

#include <cstdint>
#include <iostream>

namespace {

    struct MyStreamableType
    {
        uint32_t a;
        uint32_t b;
    };
    
    std::ostream& operator<<(std::ostream& os, const MyStreamableType& s)
    {
        os << "(" << s.a << ", " << s.b << ")";
        return os;
    }

    
    TEST(verifyStringStreamerInstantiation)
    {
        DataCache::StringStreamer s;
    }
    
    TEST(verifyStringStreamerStringConversionOperatorPostConstruction)
    {
        DataCache::StringStreamer s;
        std::string value = s;
        
        CHECK(value.empty());
    }
    
    TEST(verifyStringStreamerInsertionOperator)
    {
        std::string s = DataCache::StringStreamer()
            << 10
            << " "
            << 20;
        
        CHECK_EQUAL("10 20", s);
    }
    
    TEST(verifyStringStreamerInsertionOperatorWithCustomInsertionFunction)
    {
        MyStreamableType object;
        object.a = 100;
        object.b = 200;
        
        std::string s = DataCache::StringStreamer() << object;
        CHECK_EQUAL("(100, 200)", s);
    }
}