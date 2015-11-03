#ifndef RIOT_MATCH_PARTICIPANT_H
#define RIOT_MATCH_PARTICIPANT_H

#include <riot/lol/match/participant_stats.h>

namespace riot
{
	/**
	 *	Represents a single participant in a match
	 */
	class match_participant : public dto_complex
	{
	public:

		/// Default Constructor
		match_participant( const std::string& key = "" );

		/// Participant ID
		dto_uint64 			id{ "participantId" };
		/// Champion ID
		dto_uint 			champion{ "championId" };
		/// Statistics About this Participant
		match_participant_stats 	stats{ "stats" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &champion, &stats, &id };
		}
	};
}

#endif // RIOT_MATCH_PARTICIPANT_H
