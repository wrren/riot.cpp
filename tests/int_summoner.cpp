#include <riot/riot.h>
#include "int_key.h"

using namespace riot;

TEST_CASE( "Retrieve Summoners", "[dto]" )
{
	riot_client client( region_t::EUW, int_key::get_key() );

	SECTION( "Get Summoner List" )
	{
		auto res = client.summoners().by_name( { "General Atomic" } );
		REQUIRE( res.size() != 0 );

		res = client.summoners().by_id( { res[0].id } );
		REQUIRE( res.size() != 0 );
	}
}