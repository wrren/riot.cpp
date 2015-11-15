#include <riot/lol/game.h>
#include <riot/riot.h>

namespace riot
{
	game_stats::game_stats( const std::string& key ) :
	dto_complex( key )
	{}

	std::vector<dto_base*> game_stats::get_children()
	{
		return{ 	&kills, &deaths, &assists,
				&position, &role, &time_played,
				&total_score, &score_rank, &won,
				&double_kills, &triple_kills, &quadra_kills, &penta_kills,
				&killing_sprees, &unreal_kills,
				&largest_critical_strike, &largest_killing_spree, &largest_multi_kill,
				&magic_damage_dealt, &magic_damage_dealt_to_champions, &magic_damage_received,
				&q_casts, &w_casts, &e_casts, &r_casts,
				&physical_damage_dealt, &physical_damage_dealt_to_champions, &physical_damage_received,
				&true_damage_dealt, &true_damage_dealt_to_champions, &true_damage_received,
				&total_damage_dealt, &total_damage_dealt_to_champions, &total_damage_received,
				&total_heal, &items_bought, &sight_wards, &vision_wards, &wards_killed, &wards_placed,
				&turrets_destroyed, &inhibitors_destroyed,
				&combat_score, &consumables,
				&damage_to_players, &first_blood, &gold,
				&gold_earned, &gold_spent, &tier_3_items, &level, &minions_denied, &minions_killed,
				&jungle_monsters_killed, &enemy_jungle_monsters_killed,	&allied_jungle_monsters_killed,
				&nexus_killing_blow, &super_monster_kills };
	}

	game::game( const std::string& key ) :
	dto_complex( key )
	{}

	std::vector<dto_base*> game::get_children()
	{
		return{ &id, &champion, &ended, &mode, &type,
			&invalid, &ip_earned, &team, &stats };
	}

	std::vector<dto_base*> recent_games::get_children()
	{
		return{ &games, &summoner };
	}

	const endpoint_t game_retriever::endpoint	= "game";
	const version_t game_retriever::version		= "1.3";

	game_retriever::game_retriever( riot_client* client ) :
	dto_retriever( client )
	{}

	recent_games game_retriever::by_summoner( uint64_t id ) const
	{
		std::string id_string = str_convert( id );
		recent_games r;
		r.set_client( client() );

		auto response = http::request( url::form( region(), false, endpoint, version, key(), { "by-summoner", id_string, "recent" } ),
				client()->options().wait_on_rate_limit );

		if( response.ok() )
		{
			r.parse( response.document() );
		}
		else
		{
			throw std::runtime_error( "API Request Failure" );
		}

		return r;
	}

	recent_games game_retriever::by_summoner( const summoner& s ) const
	{
		return by_summoner( s.id );
	}
}
