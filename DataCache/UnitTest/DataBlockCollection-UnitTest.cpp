#include <UnitTest++/UnitTest++.h>
#include <DataCache/Details/DataBlockCollection.hpp>

#include <cstdint>

namespace {
    
    struct MyTestFieldType
    {
        uint64_t part_1;
        uint64_t part_2;
    };
    
    struct DataBlockCollectionFixture
    {
        DataCache::Details::DataBlockCollection<MyTestFieldType> collection;
    };
    
    TEST_FIXTURE(DataBlockCollectionFixture, verifyInstantiationOfDataBlockCollection)
    {
        CHECK(collection.empty());
    }
    
    TEST_FIXTURE(DataBlockCollectionFixture, verifyCreationOfDataBlockInCollection)
    {
        collection.create_object(0);
        collection.create_object(1);
        
        CHECK(!collection.empty());
        CHECK_EQUAL(2U, collection.size());
    }

    TEST_FIXTURE(DataBlockCollectionFixture, verifyCreationThrowsIfOIDsHaveGaps)
    {
        collection.create_object(0);
        CHECK_THROW(collection.create_object(20), DataCache::Exception::OidOutOfRange);
    }

    TEST_FIXTURE(DataBlockCollectionFixture, verifyCreationThrowsIfOidIsDuplicate)
    {
        collection.create_object(0);
        CHECK_THROW(collection.create_object(0), DataCache::Exception::OidOutOfRange);
    }

    TEST_FIXTURE(DataBlockCollectionFixture, verifyIteratorsBeginAndEnd)
    {
        collection.create_object(0);
        collection.create_object(1);
        collection.create_object(2);
        
        std::for_each(collection.begin(), collection.end(), [](MyTestFieldType& field)
        {
            // normally this would be an interesting calculation.
            field.part_1 = 0;
            field.part_2 = 1;
        });
    }

    TEST_FIXTURE(DataBlockCollectionFixture, verifyConstIteratorsBeginAndEnd)
    {
        collection.create_object(0);
        collection.create_object(1);
        collection.create_object(2);
        
        uint64_t total = 0;
        std::for_each(collection.begin(), collection.end(), [&total](const MyTestFieldType& field)
        {
            // normally this would be an interesting calculation.
            total += field.part_1 + field.part_2;
        });
        
        std::for_each(collection.cbegin(), collection.cend(), [&total](const MyTestFieldType& field)
        {
            // normally this would be an interesting calculation.
            total += field.part_1 + field.part_2;
        });
    }
}