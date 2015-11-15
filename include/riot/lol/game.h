#ifndef RIOT_API_GAME_H
#define RIOT_API_GAME_H

#include <riot/dto/dto.h>
#include <riot/lol/summoner.h>

namespace riot
{
	/**
	 *	In-depth statistics on a game played by a particular summoner.
	 */
	class game_stats : public dto_complex
	{
	public:

		/**
		 *	Default Constructor
		 */
		game_stats( const std::string& key = "" );
		
		enum position_t
		{
			POSITION_TOP = 1,
			POSITION_MID = 2,
			POSITION_JUNGLE = 3,
			POSITION_BOT = 4
		};

		enum role_t
		{
			ROLE_DUO = 1,
			ROLE_SUPPORT = 2,
			ROLE_CARRY = 3,
			ROLE_SOLO = 4
		};

		dto_uint kills{ "championsKilled", dto_base::OPTIONAL };
		dto_uint deaths{ "numDeaths", dto_base::OPTIONAL };
		dto_uint assists{ "assists", dto_base::OPTIONAL };

		dto_uint position{ "playerPosition", dto_base::OPTIONAL };
		dto_uint role{ "playerRole", dto_base::OPTIONAL };
		dto_uint time_played{ "timePlayed", dto_base::OPTIONAL };
		dto_uint total_score{ "totalPlayerScore", dto_base::OPTIONAL };
		dto_uint score_rank{ "totalScoreRank", dto_base::OPTIONAL };
		dto_bool won{ "win", dto_base::OPTIONAL };

		dto_uint double_kills{ "doubleKills", dto_base::OPTIONAL };
		dto_uint triple_kills{ "tripleKills", dto_base::OPTIONAL };
		dto_uint quadra_kills{ "quadraKills", dto_base::OPTIONAL };
		dto_uint penta_kills{ "pentaKills", dto_base::OPTIONAL };
		dto_uint killing_sprees{ "killingSprees", dto_base::OPTIONAL };
		dto_uint unreal_kills{ "unrealKills", dto_base::OPTIONAL };
		dto_uint largest_critical_strike{ "largestCriticalStrike", dto_base::OPTIONAL };
		dto_uint largest_killing_spree{ "largestKillingSpree", dto_base::OPTIONAL };
		dto_uint largest_multi_kill{ "largestMultiKill", dto_base::OPTIONAL };

		dto_uint magic_damage_dealt{ "magicDamageDealtPlayer", dto_base::OPTIONAL };
		dto_uint magic_damage_dealt_to_champions{ "magicDamageDealtToChampions", dto_base::OPTIONAL };
		dto_uint magic_damage_received{ "magicDamageTaken", dto_base::OPTIONAL };

		dto_uint q_casts{ "spell1Cast", dto_base::OPTIONAL };
		dto_uint w_casts{ "spell2Cast", dto_base::OPTIONAL };
		dto_uint e_casts{ "spell3Cast", dto_base::OPTIONAL };
		dto_uint r_casts{ "spell4Cast", dto_base::OPTIONAL };

		dto_uint physical_damage_dealt{ "physicalDamageDealtPlayer", dto_base::OPTIONAL };
		dto_uint physical_damage_dealt_to_champions{ "physicalDamageDealtToChampions", dto_base::OPTIONAL };
		dto_uint physical_damage_received{ "physicalDamageTaken", dto_base::OPTIONAL };

		dto_uint true_damage_dealt{ "trueDamageDealtPlayer", dto_base::OPTIONAL };
		dto_uint true_damage_dealt_to_champions{ "trueDamageDealtToChampions", dto_base::OPTIONAL };
		dto_uint true_damage_received{ "trueDamageTaken", dto_base::OPTIONAL };

		dto_uint total_damage_dealt{ "totalDamageDealtPlayer", dto_base::OPTIONAL };
		dto_uint total_damage_dealt_to_champions{ "totalDamageDealtToChampions", dto_base::OPTIONAL };
		dto_uint total_damage_received{ "totalDamageTaken", dto_base::OPTIONAL };
		dto_uint total_heal{ "totalHeal", dto_base::OPTIONAL };

		dto_uint items_bought{ "numItemsBought", dto_base::OPTIONAL };
		dto_uint sight_wards{ "sightWardsBought", dto_base::OPTIONAL };
		dto_uint vision_wards{ "visionWardsBought", dto_base::OPTIONAL };
		dto_uint wards_killed{ "wardKilled", dto_base::OPTIONAL };
		dto_uint wards_placed{ "wardPlaced", dto_base::OPTIONAL };

		dto_uint turrets_destroyed{ "turretsKilled", dto_base::OPTIONAL };
		dto_uint inhibitors_destroyed{ "barracksKilled", dto_base::OPTIONAL };
		dto_uint combat_score{ "combatPlayerScore", dto_base::OPTIONAL };
		dto_uint consumables{ "consumablesPurchased", dto_base::OPTIONAL };
		dto_uint damage_to_players{ "damageDealtPlayer", dto_base::OPTIONAL };
		dto_uint first_blood{ "firstBlood", dto_base::OPTIONAL };
		dto_uint gold{ "gold", dto_base::OPTIONAL };
		dto_uint gold_earned{ "goldEarned", dto_base::OPTIONAL };
		dto_uint gold_spent{ "goldSpent", dto_base::OPTIONAL };
		dto_uint tier_3_items{ "legendaryItemsCreated", dto_base::OPTIONAL };
		dto_uint level{ "level", dto_base::OPTIONAL };
		
		dto_uint minions_denied{ "minionsDenied", dto_base::OPTIONAL };
		dto_uint minions_killed{ "minionsKilled", dto_base::OPTIONAL };
		dto_uint jungle_monsters_killed{ "neutralMinionsKilled", dto_base::OPTIONAL };
		dto_uint enemy_jungle_monsters_killed{ "neutralMinionsKilledEnemyJungle", dto_base::OPTIONAL };
		dto_uint allied_jungle_monsters_killed{ "neutralMinionsKilledYourJungle", dto_base::OPTIONAL };
		dto_bool nexus_killing_blow{ "nexusKilled", dto_base::OPTIONAL };
		dto_uint super_monster_kills{ "superMonsterKilled", dto_base::OPTIONAL };

	private:

		/**
		 *	Get child objects for deserialization
		 */
		virtual std::vector<dto_base*> get_children() override;
	};

	/**
	 *	Represents a single game of League of Legends played by a summoner. Includes
	 *	various statistics related to performance and activities.
	 */
	class game : public dto_complex
	{
	public:

		/**
		 *	Indicates whether the summoner played on the red or blue side
		 */
		enum team_id
		{
			TEAM_BLUE = 100,
			TEAM_RED = 200
		};

		/**
		 *	Default Constructor
		 */
		game( const std::string& key = "" );

		/// Game Unique ID
		dto_uint64	id{ "gameId" };
		/// ID of the champion played
		dto_uint	champion{ "championId" };
		/// Timestamp indicating when the game ended/when stats were compiled
		dto_uint64	ended{ "createDate" };
		/// Game Mode ( CLASSIC, ARAM, TUTORIAL, etc. )
		dto_string	mode{ "gameMode" };
		/// Type of game played ( CUSTOM_GAME, MATCHED_GAME, etc. )
		dto_string	type{ "gameType" };
		/// Indicaes whether the game was marked as invalid
		dto_bool	invalid{ "invalid" };
		/// Number of influence points earned by the summoner
		dto_uint	ip_earned{ "ipEarned" };
		/// Indicates which side the summoner played on
		dto_uint	team{ "teamId" };
		/// Game Stats
		game_stats	stats{ "stats" };

	private:

		/**
		 *	Get child objects for deserialization
		 */
		virtual std::vector<dto_base*> get_children() override;
	};

	/**
	 *	Object type returned by the game endpoint. Contains the recent games
	 *	played by the summoner with the given ID
	 */
	class recent_games : public dto_complex
	{
	public:

		/// Recent Games
		dto_vector<game> games{ "games" };
		/// Summoner ID
		dto_uint64 summoner{ "summonerId" };

	private:

		/**
		 *	Get child objects for deserialization
		 */
		virtual std::vector<dto_base*> get_children() override;
	};

	/**
	 *	Contains methods for retrieving games
	 */
	class game_retriever : public dto_retriever
	{
	public:
		/// Game Endpoint Name
		static const endpoint_t	endpoint;
		/// Game Endpoint Version
		static const version_t	version;

		/// Default Constructor
		game_retriever( riot_client* client );

		/**
		 *	Retrieve all recent games for the summoner with the specified ID
		 * @param id 	Match ID
		 * @return 	Recent games played by the summoner
		 */
		recent_games by_summoner( uint64_t id ) const;

		/**
		 *	Retrieve all recent games played by the specified summoner
		 * @param s	Summoner
		 * @return 	Recent games played by the summoner
		 */
		recent_games by_summoner( const summoner& s ) const;
	};
}

#endif // RIOT_API_GAME_H
