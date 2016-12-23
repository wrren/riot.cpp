#ifndef RIOT_STATS_H
#define RIOT_STATS_H

#include <riot/dto/dto.h>
#include <riot/lol/summoner.h>
#include <riot/lol/match/participant.h>
#include <riot/lol/match/participant_identity.h>
#include <riot/lol/match/team.h>

namespace riot
{
	/**
	 *	Contains aggregated statistics
	 */
	class player_stats : public dto_complex
	{

	};

	/**
	 *	Contains user information
	 */
	class user_key : public dto_complex
	{
	public:

		// Player Region
		dto_string region{ "region" };

		// Summoner ID
		dto_uint64 summoner_id{ "summonerId" };
	};

	/**
	 *	Contains aggregated statistics for a given summoner
	 */
	class stats : public dto_complex
	{
	public:

		// Timestamp indicating the last time stats changed for this summoner
		dto_uint64 last_change{ "lastStatsSummaryChangeTimestamp" };
		
		// Aggregate statistics
		player_stats statistics{ "statistics" };

		// User to whom these statistics refer
		user_key user{ "user" };

		// Object Version
		dto_string version{ "version" };
	};

	
}

#endif // RIOT_STATS_H