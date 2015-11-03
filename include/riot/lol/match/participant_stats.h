#ifndef RIOT_MATCH_PARTICIPANT_STATS_H
#define RIOT_MATCH_PARTICIPANT_STATS_H

#include <riot/dto/dto.h>

namespace riot
{
	/**
	 *	Statistics for each match participant
	 */
	class match_participant_stats : public dto_complex
	{
	public:

		/// Default Constructor
		match_participant_stats( const std::string& key = "" );

		/// Number of kills
		dto_uint64 	kills{ "kills" };
		/// Number of deaths
		dto_uint64 	deaths{ "deaths" };
		/// Number of kill assists
		dto_uint64 	assists{ "assists" };
		/// Maximum champion level achieved
		dto_uint64 	level{ "champLevel" };
		/// Did this participant get the first blood kill
		dto_bool 	first_blood_kill{ "firstBloodKill" };
		/// Longest Killing Spree
		dto_uint64 	longest_killing_spree{ "largestKillingSpree" };
		/// Amount of gold earned
		dto_uint64	gold_earned{ "goldEarned" };	
		/// Amount of gold spent
		dto_uint64 	gold_spent{ "goldSpent" }; 
		/// Total damage dealt
		dto_uint64 	total_damage_dealt{ "totalDamageDealt" };
		/// Total damage dealt to champions
		dto_uint64 	total_damage_dealt_to_champions{ "totalDamageDealtToChampions" };
		/// Total damage taken
		dto_uint64	total_damage_taken{ "totalDamageTaken" };
		/// Number of towers destroyed
		dto_uint64 	tower_kills{ "towerKills" };
		/// Number of wards placed
		dto_uint64 	wards_placed{ "wardsPlaced" };
		/// Number of wards destroyed
		dto_uint64 	wards_destroyed{ "wardsKilled" };
		/// Indicates whether the participant won the match
		dto_bool 	winner{ "winner" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{ 
			return{ &kills, &deaths, &assists, &level, &first_blood_kill,
				&gold_earned, &gold_spent, &total_damage_taken,
				&total_damage_dealt, &total_damage_dealt_to_champions,
				&tower_kills, &wards_destroyed, &wards_placed, &winner }; 
		}	
	};
}

#endif // RIOT_MATCH_PARTICIPANT_STATS_H
