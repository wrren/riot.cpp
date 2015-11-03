#ifndef RIOT_MATCH_PARTICIPANT_IDENTITY_H
#define RIOT_MATCH_PARTICIPANT_IDENTITY_H

#include <riot/lol/match/player.h>

namespace riot
{
	/**
	 *	Matches a participant ID to player data
	 */
	class match_participant_identity : public dto_complex
	{
	public:	

		/// Default Constructor
		match_participant_identity( const std::string& key = "" );

		/// Participant ID
		dto_uint64	id{ "participantId" };
		/// Player Data
		match_player	player{ "player" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override { return{ &id, &player }; }
	};
}

#endif // RIOT_MATCH_PARTICIPANT_IDENTITY_H
