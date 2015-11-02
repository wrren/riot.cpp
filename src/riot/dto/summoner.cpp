#include <riot/dto/summoner.h>
#include <riot/core/json.h>

namespace riot
{
	const endpoint_t summoner_retriever::endpoint 	= "summoner";
	const version_t summoner_retriever::version 	= "1.4";

	summoner_retriever::summoner_retriever( region_t region, const api_key_t& key ) : dto_retriever( region, key )
	{}

	std::vector<summoner> summoner_retriever::by_name( const std::vector<std::string>& names ) const
	{
		dto_map<summoner> summoners( names );

		auto response = json::get( url::form( region(), false, endpoint, version, key(), { "by-name", url::collapse( names ) } ) );

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

	std::vector<summoner> summoner_retriever::by_id( const std::vector<uint64_t>& ids ) const
	{
		std::vector<std::string> id_strings( str_convert( ids ) );
		dto_map<summoner> summoners( id_strings );

		auto response = json::get( url::form( region(), false, endpoint, version, key(), { url::collapse( id_strings ) } ) );

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