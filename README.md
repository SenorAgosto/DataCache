# DataCache

This is a simple toolkit for implementing Data Oriented Designs in C++. 

## Usage

	// Use a traits class to hold mapping of field name to type.
	struct Fields
	{
		// define field names
		enum MyFields {
			field_1,
			field_2
		};

		// define field types
		using field_1_type = uint64_t;
		using field_2_type = uint32_t;
	};
	
    // Declare a type using the DataCache
    class MyObject
        : public  DataCache::UsingDataCacheIn<MyObject>
        , private DataCache::DataBlock<MyObject, Fields::field_1, Fields::field_1_type>
        , private DataCache::DataBlock<MyObject, Fields::field_2, Fields::field_2_type>
    {
    public:
    	void Foo(void);
    };

This bit of code will create a data cache for MyObject fields. A couple of things to note, you must inherit from DataCache::UsingDataCacheIn prior to defining DataCache::DataBlock entries.

Two data caches will be created, one for holding field_1 values for all instances of MyObject, a second for field_2. The point of using Data Oriented Design is to efficiently apply functions on _all_ instances of a class. To do this using DataCache toolbox, request a collection and then simply iterate through it.

    auto& collection = MyObject::collection<Fields::field_1_type>(Fields::field_1);
    std::for_each(begin(collection), end(collection), [](uint64_t value)
    {
    	// do something useful...
    });

This toolkit allows us to mix paradigms easily. Given an object instance, you can still use member methods in the normal object oriented ways.

	void MyObject::Foo(void)
	{
		// the only inconvenience is we have to use our OID to 
		// get the location of our fields we want to modify here.
		auto& field1 = get<Fields::field_1_type>(oid(), Fields::field_1);
		auto& field2 = get<Fields::field_2_type>(oid(), Fields::field_2);

		// Do something useful with field1 and field2...
	}

Potentially, you could mix the member data between the data cache and unorganized heap as well, though we're not sure you really want to do that. If you really want to go that route, I'd recommend a related class with a has-a relationship to separate what is in the DataCache and what isn't.

## Authors

Austin Gilbert <paxos1977@github.com>

## Copyright and License

4-Clause BSD license. See License.md for details.

## Comments

Other licensing available upon request, for a fee.
