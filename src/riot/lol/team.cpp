#include <riot/lol/team.h>
#include <riot/riot.h>

namespace riot
{
	const endpoint_t team_retriever::endpoint 	= "team";
	const version_t team_retriever::version 	= "2.4";

	match match_summary::get_match() const
	{
		return client()->match().by_id( { this->id } );
	}

	team_retriever::team_retriever( riot_client* client ) : dto_retriever( client )
	{}

	std::vector<team> team_retriever::by_summoner( const std::vector<summoner>& s ) const
	{
		std::vector<std::string> summoners( str_convert<summoner, uint64_t>( s, []( const summoner& sum ) -> uint64_t
		{
			return sum.id;
		} ) );

		dto_map<dto_vector<team>> teams( summoners );
		teams.set_client( client() );

		auto response = json::get( url::form( region(), false, endpoint, version, key(), { "by-summoner", url::collapse( summoners ) } ) );

		if( response.ok() )
		{
			teams.parse( response.document() );
		}
		else
		{
			throw std::runtime_error( "API Request Failure" );
		}
		
		std::vector<team> result;

		for( dto_vector<team> t : teams.values() )
		{
			result.insert( result.end(), t.values().begin(), t.values().end() );
		}

		return result;
	}

	std::vector<team> team_retriever::by_id( const std::vector<uint64_t>& ids ) const
	{
		std::vector<std::string> id_strings( str_convert( ids ) );
		dto_map<dto_vector<team>> teams( id_strings );
		teams.set_client( client() );
		
		auto response = json::get( url::form( region(), false, endpoint, version, key(), { url::collapse( id_strings ) } ) );

		if( response.ok() )
		{
			teams.parse( response.document() );
		}
		else
		{
			throw std::runtime_error( "API Request Failure" );
		}
		
		std::vector<team> result;

		for( dto_vector<team> t : teams.values() )
		{
			result.insert( result.end(), t.values().begin(), t.values().end() );
		}

		return result;
	}
}