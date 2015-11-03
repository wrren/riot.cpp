#ifndef RIOT_MATCH_TEAM_H
#define RIOT_MATCH_TEAM_H

#include <riot/dto/dto.h>

namespace riot
{
	/**
	 *	Team participating in a match
	 */
	class match_team : public dto_complex
	{
	public:

		/// Default Constructor
		match_team( const std::string& key = "" );

		/// Team ID
		dto_uint 	id{ "teamId" };
		/// Number of baron kills
		dto_uint 	baron_kills{ "baronKills" };
		/// Number of dragon kills
		dto_uint 	dragon_kills{ "dragonKills" };
		/// Indicates whether the team won the match
		dto_bool 	winner{ "winner" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &baron_kills, &dragon_kills, &winner };
		}
	};

}

#endif // RIOT_MATCH_TEAM_H
