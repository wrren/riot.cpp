#ifndef RIOT_MATCH_PLAYER_H
#define RIOT_MATCH_PLAYER_H

#include <riot/dto/dto.h>

namespace riot
{
	/**
	 *	Player in a given match
	 */
	class match_player : public dto_complex
	{
	public:

		/// Default Constructor
		match_player( const std::string& key = "" );

		/// URI for player match history
		dto_string	match_history_uri{ "matchHistoryUri" };
		/// Profile Icon ID
		dto_uint	icon{ "profileIcon" };
		/// Summoner ID
		dto_uint64	id{ "summonerId" };
		/// Summoner Name
		dto_string	name{ "summonerName" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{ 
			return{ &id, &name, &icon, &match_history_uri }; 
		}
	};
}

#endif // RIOT_MATCH_PLAYER_H
