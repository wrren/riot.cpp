# Riot C++11 API

Shared library and tests for the [Riot Developer API](https://developer.riotgames.com) using
C++11 features.

## How to Build

* ```cd build && cmake .. && make```
* Outputs libs to the ```lib``` directory
* Add ```include``` and ```deps/rapidjson/include``` to your project include path

## How to Use

* Sign up for a developer account and get your API key
* Initialize a ```riot_client``` object, providing a target region and your API key
* Retrieve data using the various ```riot_client``` endpoint members

## Example

```cpp

#include <riot/riot.h>

using namespace riot;

#include <iostream>

int main( int argc, char** argv )
{
	if( argc != 3 )
	{
		std::cerr << "Please Provide an API Key and Summoner Name" << std::endl;
		return 1;
	}

	riot_client client( region_t::EUW, argv[1] );

	auto summoners = client.summoner().by_name( { argv[2] } );

	for( summoner& s : summoners )
	{
		std::cout << "Found Summoner: " << s.name.get() << std::endl;

		auto teams = client.team().by_summoner( { s } );

		for( team& t : teams )
		{
			std::cout << "Summoner " << s.name.get() << " is on Team " << t.name.get() << std::endl;

			if( t.history.size() > 0 )
			{
				auto m = client.match().by_id( t.history[0].id );

				std::cout << "Team " << t.name.get() << " Last Played on " << m.queue.get() << " Queue" << std::endl;
			}
		}
	}

	return 0;
}

```