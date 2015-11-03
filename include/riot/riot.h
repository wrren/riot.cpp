#ifndef RIOT_H
#define RIOT_H

#include <riot/core/core.h>
#include <riot/lol/summoner.h>
#include <riot/lol/team.h>
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
		 *	Construct a Riot API Client that will connect to the
		 *	API server for the given region using the provided API key
		 * @param region 	API Server Region
		 * @param api_key 	Client API Key
		 */
		riot_client( 	region_t connect_region, 
				const api_key_t& api_key );

		/// Access Summoner Retrieval Methods
		const summoner_retriever& summoner() const { return m_summoner; }
		/// Access Team Retrieval Methods
		const team_retriever& team() const { return m_team; }
		/// Access Match Retrieval Methods
		const match_retriever& match() const { return m_match; }

		/// Region Accessors
		const region_t region() const		{ return m_region; }

		/// API Key Accessors
		const api_key_t& key() const		{ return m_key;  }

	private:

		/// Summoner Retriever
		summoner_retriever	m_summoner;
		/// Team Retriever
		team_retriever		m_team;
		/// Match Retriever
		match_retriever		m_match;

		/// Target API Server Region
		region_t m_region;
		/// API Client Key
		api_key_t m_key;
	};
}

#endif // RIOT_H
