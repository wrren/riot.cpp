#include <riot/riot.h>
#include "int_key.h"

using namespace riot;

TEST_CASE( "Retrieve Recent Games", "[dto]" )
{
	riot_client client( region_t::EUW, int_key::get_key() );

	SECTION( "Get Game List" )
	{
		auto res = client.summoner().by_name( { "General Atomic" } );
		REQUIRE( res.size() != 0 );

		auto recent = client.games().by_summoner( { res[0] } );
		REQUIRE( recent.games.size() != 0 );

		REQUIRE( recent.games[0].stats.level.is_present() );
		REQUIRE( recent.games[0].stats.level.get() > 0 );
	}
}