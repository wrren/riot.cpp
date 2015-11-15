#ifndef RIOT_SUMMONER_H
#define RIOT_SUMMONER_H

#include <riot/dto/dto.h>

namespace riot
{
	/// Recent Game Forward-Declaration
	class recent_games;

	/**
	 *	League of Legends Summoner Data
	 */
	class summoner : public dto_complex
	{
	public:
		
		dto_uint64 	id{ "id" };
		dto_string 	name{ "name" };
		dto_uint 	icon{ "profileIconId" };
		dto_uint	level{ "summonerLevel" };
		dto_uint64	modified{ "revisionDate" };

		/**
		 *	Default Constructor
		 */
		summoner( const std::string& key = "" ) : dto_complex( key )
		{}

		/**
		 *	Get a list of games recently played by this summoner
		 */
		recent_games get_recent_games() const;
		
	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return { &id, &name, &icon, &level, &modified };
		}
	};
	
	/**
	 *	Contains the functions for retrieving summoners from the summoner endpoint
	 */
	class summoner_retriever : public dto_retriever
	{
	public:

		/// Endpoint Name
		static const endpoint_t 	endpoint;
		static const version_t 		version;

		/**
		 *	Default Constructor
		 */
		summoner_retriever( riot_client* client );

		/**
		 *	Retrieve a set of summoners by their names
		 * @param names 	Names to search for
		 * @return 		List of summoners found
		 */
		std::vector<summoner> by_name( const std::vector<std::string>& names ) const;

		/**
		 *	Retrieve a set of summoners by their ID
		 * @param names 	IDs to search for
		 * @return 		List of summoners found
		 */
		std::vector<summoner> by_id( const std::vector<uint64_t>& ids ) const;
	};
}

#endif // RIOT_SUMMONER_H
