#include <riot/lol/summoner.h>
#include <riot/core/core.h>
#include <riot/riot.h>

namespace riot
{
	const endpoint_t summoner::retriever::endpoint 	= "summoner";
	const version_t summoner::retriever::version 	= "1.4";

	recent_games summoner::get_recent_games() const
	{
		return client()->games().by_summoner( *this );
	}

	summoner::retriever::retriever( riot_client* client ) : dto_retriever( client )
	{}

	std::vector<summoner> summoner::retriever::by_name( const std::vector<std::string>& names ) const
	{
		dto_map<summoner> summoners( names );
		summoners.set_client( client() );
		auto response = http::request(	url::form( region(), false, endpoint, version, key(), { "by-name", url::collapse( names ) } ),
						client()->options().wait_on_rate_limit );

		if( response.ok() )
		{
			summoners.parse( response.document() );
		}
		else
		{
			throw std::runtime_error( "API Request Failure" );
		}
		
		return summoners.values();
	}

	std::vector<summoner> summoner::retriever::by_id( const std::vector<uint64_t>& ids ) const
	{
		std::vector<std::string> id_strings( str_convert( ids ) );
		dto_map<summoner> summoners( id_strings );
		summoners.set_client( client() );
		auto response = http::request(	url::form( region(), false, endpoint, version, key(), { url::collapse( id_strings ) } ),
						client()->options().wait_on_rate_limit );

		if( response.ok() )
		{
			summoners.parse( response.document() );
		}
		else
		{
			throw std::runtime_error( "API Request Failure" );
		}
		
		return summoners.values();
	}
}