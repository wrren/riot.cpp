#include <riot/riot.h>
#include "int_key.h"

using namespace riot;

TEST_CASE( "Retrieve JSON", "[core]" )
{
	riot_client client( region_t::EUW, int_key::get_key() );

	SECTION( "Get Summoner List" )
	{
		auto res = client.summoners().by_name( { "General Atomic" } );

		REQUIRE( res.size() != 0 );
	}
}