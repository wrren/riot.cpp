#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <riot/core/url.h>

using namespace riot;

TEST_CASE( "URL Formation", "[riot]" )
{
	REQUIRE( url::form( region_t::EUW, false, "champion", "1.2", "1234" ) 				== "https://euw.api.pvp.net/api/lol/euw/v1.2/champion?api_key=1234" );
	REQUIRE( url::form( region_t::EUW, false, "champion", "1.2", "1234", { "20" } ) 		== "https://euw.api.pvp.net/api/lol/euw/v1.2/champion/20?api_key=1234" );
	REQUIRE( url::form( region_t::EUW, false, "champion", "1.2", "1234", {}, { { "foo", "bar" } } ) == "https://euw.api.pvp.net/api/lol/euw/v1.2/champion?api_key=1234&foo=bar" );
	REQUIRE( url::form( region_t::NA, false, "champion", "1.2", "1234", {}, { { "foo", "bar" } } )	== "https://na.api.pvp.net/api/lol/na/v1.2/champion?api_key=1234&foo=bar" );
}