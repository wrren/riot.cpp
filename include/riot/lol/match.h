#ifndef RIOT_MATCH_H
#define RIOT_MATCH_H

#include <riot/dto/dto.h>
#include <riot/lol/summoner.h>
#include <riot/lol/match/participant.h>
#include <riot/lol/match/participant_identity.h>
#include <riot/lol/match/team.h>

namespace riot
{
	/// Client Forward Declaration
	class riot_client;

	/**
	 *	Represents a single match in the game
	 */
	class match : public dto_complex
	{
	public:

		/// Default Constructor
		match( const std::string& key = "" );

		/// Match ID
		dto_uint64 				id{ "matchId" };
		/// Timestamp for the point when the team select lobby was created
		dto_uint64				created{ "matchCreation" };
		/// Match duration in milliseconds
		dto_uint64				duration{ "matchDuration" };
		/// Match Mode ( CLASSIC, ODIN, ARAM, TUTORIAL, ONEFORALL, ASCENSION, FIRSTBLOOD, KINGPORO )
		dto_string 				mode{ "matchMode" };
		/// Match Type ( CUSTOM_GAME, MATCHED_GAME, TUTORIAL_GAME )
		dto_string 				type{ "matchType" };
		/// Match Version
		dto_string 				version{ "matchVersion" };
		/// Queue Type ( CUSTOM, NORMAL_5X5_BLIND, etc. )
		dto_string 				queue{ "queueType" };
		/// Region in which the match was played
		dto_string 				region{ "region" };
		/// Participating Teams
		dto_vector<match_team>			teams{ "teams" };
		/// Match Participants
		dto_vector<match_participant>		participants{ "participants" };
		/// Participant Identity Mappings
		dto_vector<match_participant_identity>	participant_identities{ "participantIdentities" };

		/// Given a summoner, get the matching match participant object for this match
		match_participant get_participant( const summoner& sum ) const;

		/**
		 *	Encapsulates methods for retrieving match objects
		 */
		class retriever : public dto_retriever
		{
		public:

			/// Endpoint Name
			static const endpoint_t 	endpoint;
			static const version_t 		version;

			/// Default Constructor
			retriever( riot_client* client );

			/**
			*	Retrieve the match object with the specified ID
			* @param id 	Match ID
			* @return 	Match object with matching ID
			*/
			match by_id( uint64_t id ) const;

		};

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &id, &created, &duration, &mode, &type, &version, &queue, &region, &teams, &participants, &participant_identities };
		}
	};

	

	
}

#endif // RIOT_MATCH_H
