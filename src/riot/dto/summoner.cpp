#include <riot/dto/summoner.h>
#include <riot/core/json.h>

namespace riot
{
	const endpoint_t summoner_retriever::endpoint 	= "summoner";
	const version_t summoner_retriever::version 	= "1.4";

	summoner_retriever::summoner_retriever( region_t& region, api_key_t& key ) : dto_retriever( region, key )
	{}

	std::vector<summoner> summoner_retriever::by_name( const std::vector<std::string>& names ) const
	{
		dto_map<summoner> summoners( names );

		auto response = json::get( url::form( region(), false, endpoint, version, key(), { url::collapse( names ) } ) );

		if( response.ok() )
		{
			summoners.parse( response.document() );
		}
		
		return summoners.values();
	}
}