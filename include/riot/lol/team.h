#ifndef RIOT_TEAM_H
#define RIOT_TEAM_H

#include <riot/dto/dto.h>
#include <riot/lol/summoner.h>
#include <riot/lol/match.h>

namespace riot
{
	/**
	 *	Basic match summary for a team
	 */
	class match_summary : public dto_complex
	{
	public:

		/// Default Constructor
		match_summary( const std::string& key = "" ) : dto_complex( key )
		{}

		/// Game ID
		dto_uint64 	id{ "gameId" };
		/// Play Date Timestamp
		dto_uint64	date{ "date" };
		/// Total number of kills by subject team
		dto_uint 	kills{ "kills" };
		/// Total number of deaths suffered by subject team
		dto_uint 	deaths{ "deaths" };
		/// Kills by opposing team
		dto_uint 	opposing_kills{ "opposingTeamKills" };
		/// Indicates whether the team won the game
		dto_bool 	win{ "win" };

		/// Retrieve the full match data for this match
		match 		get_match() const;

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &id, &date, &kills, &deaths, &opposing_kills, &win };
		}
	};

	/**
	 *	Team Member Summary
	 */
	class team_member : public dto_complex
	{
	public:

		/// Default Constructor
		team_member( const std::string& key = "" ) : dto_complex( key )
		{}

		/// Summoner ID
		dto_uint64	id{ "playerId" };
		/// Date on which the player joined the team
		dto_uint64 	joined{ "joinDate" };
		/// Date on which the player was invited to the team
		dto_uint64 	invited{ "inviteDate" };
		/// Member Status
		dto_string 	status{ "status" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &id, &joined, &invited, &status };
		}
	};

	/**
	 *	Team game roster object
	 */
	class roster : public dto_complex
	{
	public:

		/// Default Constructor
		roster( const std::string& key = "" ) : dto_complex( key )
		{}

		/// Team Owner Summoner ID
		dto_uint64 		owner{ "ownerId" };
		/// Play Date Timestamp
		dto_vector<team_member>	members{ "memberList" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &owner, &members };
		}
	};

	/**
	 *	Contains team performance statistics
	 */
	class team_stats : public dto_complex
	{
	public:

		/// Default Constructor
		team_stats( const std::string& key = "" ) : dto_complex( key )
		{}

		/// Game Type ( RANKED_TEAM_5x5, etc. )
		dto_string 	type{ "teamStatType" };
		/// Average Number of Games Played
		dto_uint 	average_games{ "averageGamesPlayed" };
		/// Games Lost
		dto_uint 	losses{ "losses" };
		/// Games Won
		dto_uint 	wins{ "wins" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &average_games, &losses, &wins };
		}	
	};

	/**
	 *	League of Legends Summoner Data
	 */
	class team : public dto_complex
	{
	public:
		
		/// Team ID
		dto_string 			id{ "fullId" };
		/// Last Game Played Timestamp
		dto_uint64			last_game{ "lastGameDate" };
		/// Create Date Timestamp
		dto_uint64 			created_date{ "createDate" };
		/// Team Name
		dto_string 			name{ "name" };
		/// Team Match History
		dto_vector<match_summary> 	history{ "matchHistory" };
		/// Team Roster
		roster 				roster{ "roster" };
		/// Team Status
		dto_string 			status{ "status" };
		/// Team Statistics
		dto_vector<team_stats>		statistics{ "teamStatDetails" };

		/**
		 *	Default Constructor
		 */
		team( const std::string& key = "" ) : dto_complex( key )
		{}
		
	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return { &id, &last_game, &created_date, &name, &history, &roster, &status, &statistics };
		}
	};

	/// Client Forward-Declaration
	class riot_client;

	/**
	 *	Contains the functions for retrieving teams from the team endpoint
	 */
	class team_retriever : public dto_retriever
	{
	public:

		/// Endpoint Name
		static const endpoint_t 	endpoint;
		static const version_t 		version;

		/**
		 *	Default Constructor
		 */
		team_retriever( riot_client* client );

		/**
		 *	Retrieve a set of teams by their summoner members
		 * @param summoners 	Names to search for
		 * @return 		List of teams found
		 */
		std::vector<team> by_summoner( const std::vector<summoner>& summoners ) const;

		/**
		 *	Retrieve a set of teams by their ID
		 * @param names 	IDs to search for
		 * @return 		List of teams found
		 */
		std::vector<team> by_id( const std::vector<uint64_t>& ids ) const;
	};
}

#endif // RIOT_TEAM_H