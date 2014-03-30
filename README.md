# DataCache

This is a simple toolkit for implementing Data Oriented Designs in C++. 

## Usage

	// For convenience, declare an enum for field names.
	enum MyFields {
		field_1,
		field_2
	};

    // Declare a type using the DataCache
    struct MyObject
        : public DataCache::UsingDataCacheIn<MyObject>
        , public DataCache::DataBlock<MyObject, field_1, uint64_t>
        , public DataCache::DataBlock<MyObject, field_2, uint32_t>
    {
    };

This bit of code will create a data cache for MyObject fields. A couple of things to note, you must inherit from DataCache::UsingDataCacheIn prior to defining DataCache::DataBlock entries.

Two data caches will be created, one for holding field_1 values for all instances of MyObject, a second for field_2. The point of using Data Oriented Design is to efficiently apply functions on _all_ instances of a class. To do this using DataCache toolbox, request a collection and then simply iterate through it.

    auto collection = MyObject::collection<uint64_t>(field_1);
    std::for_each(collection.begin(), collection.end(), [](uint64_t value)
    {
    	// do something useful...
    });

This toolkit allows us to mix paradigms easily. Given an object instance, you can still use member methods in the normal object oriented ways.

    // Declare a type using the DataCache
    struct MyObject
        : public DataCache::UsingDataCacheIn<MyObject>
        , public DataCache::DataBlock<MyObject, field_1, uint64_t>
        , public DataCache::DataBlock<MyObject, field_2, uint32_t>
    {
    	void Foo(void)
    	{
    		// the only inconvenience is we have to use our OID to 
    		// get the location of our fields we want to modify here.
    		auto& field1 = get(oid(), field_1);
    		auto& field2 = get(oid(), field_2);

    		field1 += field2;
    		field2 /= 2;
    	}
    };

Potentially, you could mix the member data between the data cache and unorganized heap as well, though we're not sure you really want to do that. If you really want to go that route, I'd recommend a related class with a has-a relationship to separate what is in the DataCache and what isn't.

## Authors

Austin Gilbert <paxos1977@github.com>

## Copyright and License

4-Clause BSD license. See License.md for details.

## Comments

Other licensing available upon request, for a fee.
