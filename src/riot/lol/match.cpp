#include <riot/lol/match.h>
#include <riot/core/core.h>
#include <riot/riot.h>

namespace riot
{
	const endpoint_t match::retriever::endpoint = "match";
	const version_t match::retriever::version = "2.2";

	match::match( const std::string& key ) :
	dto_complex( key )
	{}

	match::retriever::retriever( riot_client* client ) :
	dto_retriever( client )
	{}

	match match::retriever::by_id( uint64_t id ) const
	{
		std::string id_string = str_convert( id );
		match m;
		m.set_client( client() );

		auto response = http::request(	url::form( region(), false, endpoint, version, key(), { id_string } ),
						client()->options().wait_on_rate_limit );

		if( response.ok() )
		{
			m.parse( response.document() );
		}
		else
		{
			throw std::runtime_error( "API Request Failure" );
		}
		
		return m;
	}
}