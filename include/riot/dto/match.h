#ifndef RIOT_MATCH_H
#define RIOT_MATCH_H

#include <riot/dto/dto.h>

namespace riot
{
	/**
	 *	Matches a participant ID to player data
	 */
	class participant_identity : public dto_object
	{
	public:	

		/// Default Constructor
		participant_identity( const std::string& key = "" );

		/// Participant ID
		dto_uint64	id{ "participantId" };
		/// Player Data
		match_player	player{ "player" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &id, &player };
		}
	};

	/**
	 *	Represents a single participant in a match
	 */
	class participant : public dto_object
	{
	public:

		/// Default Constructor
		participant( const std::string& key = "" );

		/// Participant ID
		dto_uint64 		id{ "participantId" };
		/// Champion ID
		dto_uint 		champion{ "championId" };
		/// Statistics About this Participant
		participant_stats 	stats{ "stats" };
		/// Action Timeline
		participant_timeline	timeline{ "timeline" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &champion, &stats, &timeline };
		}
	};

	class match_team : public dto_object
	{
	public:

		
	};

	/**
	 *	Represents a single match in the game
	 */
	class match : public dto_object
	{
	public:

		/// Match ID
		dto_uint64 		id{ "matchId" };
		/// Timestamp for the point when the team select lobby was created
		dto_uint64		created{ "matchCreation" };
		/// Match duration in milliseconds
		dto_uint64		duration{ "matchDuration" };
		/// Match Mode ( CLASSIC, ODIN, ARAM, TUTORIAL, ONEFORALL, ASCENSION, FIRSTBLOOD, KINGPORO )
		dto_string 		mode{ "matchMode" };
		/// Match Type ( CUSTOM_GAME, MATCHED_GAME, TUTORIAL_GAME )
		dto_string 		type{ "matchType" };
		/// Match Version
		dto_string 		version{ "matchVersion" };
		/// Queue Type ( CUSTOM, NORMAL_5X5_BLIND, etc. )
		dto_string 		queue{ "queueType" };
		/// Region in which the match was played
		dto_string 		region{ "region" };
		/// Match Event Timeline
		match_timeline		timeline{ "timeline" };
		/// Participating Teams
		dto_vector<match_team>	teams{ "teams" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &id, &created, &duration, &mode, &type, &version, &queue, &region, &timeline };
		}
	};
}

#endif // RIOT_MATCH_H
