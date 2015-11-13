#include <catch.hpp>
#include <riot/core/http.h>

using namespace riot;

TEST_CASE( "Header Parsing", "[riot]" )
{
	std::string headers_raw = "content-type: text/javascript\r\ncontent-length: 45";

	auto headers = http::parse_headers( headers_raw );

	REQUIRE( headers.find( "content-type" ) != headers.end() );
	REQUIRE( headers["content-type"] == "text/javascript" );

	REQUIRE( headers.find( "content-length" ) != headers.end() );
	REQUIRE( headers["content-length"] == "45" );
}