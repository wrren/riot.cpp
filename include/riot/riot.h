#ifndef RIOT_H
#define RIOT_H

#include <riot/core/core.h>
#include <riot/lol/summoner.h>
#include <riot/lol/team.h>
#include <riot/lol/game.h>
#include <riot/lol/match.h>

namespace riot
{
	/**
	 *	Main interface for Riot API interactions
	 */
	class riot_client
	{
	public:

		/**
		 *	Client Options
		 */
		struct options_t
		{
			// If true, client requests will sleep the current thread and
			// retry when the rate limit is hit. Otherwise a dto_rate_exception
			// will be thrown
			bool wait_on_rate_limit;
		};

		/**
		 *	Construct a Riot API Client that will connect to the
		 *	API server for the given region using the provided API key
		 * @param region 	API Server Region
		 * @param api_key 	Client API Key
		 * @param options	Client Options
		 */
		riot_client( 	region_t connect_region, 
				const api_key_t& api_key,
				const options_t = options_t{ true } );

		/// Access Summoner Retrieval Methods
		const summoner_retriever& summoner() const;
		
		/// Access Team Retrieval Methods
		const team_retriever& team() const;

		/// Access Game Retrieval Methods
		const game_retriever& games() const;
		
		/// Access Match Retrieval Methods
		const match_retriever& match() const;

		/// Region Accessors
		const region_t region() const;

		/// API Key Accessors
		const api_key_t& key() const;

		/// Client Options
		const options_t& options() const;

	private:

		/// Client Options
		options_t		m_options;
		/// Summoner Retriever
		summoner_retriever	m_summoner;
		/// Team Retriever
		team_retriever		m_team;
		/// Match Retriever
		match_retriever		m_match;
		/// Game Retriever
		game_retriever 		m_games;

		/// Target API Server Region
		region_t m_region;
		/// API Client Key
		api_key_t m_key;
	};
}

#endif // RIOT_H
