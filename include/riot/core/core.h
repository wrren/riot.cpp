#ifndef RIOT_CORE_H
#define RIOT_CORE_H

#include <string>
#include <vector>
#include <map>

namespace riot
{
	/**
	 *	There are Riot API servers in multiple regions, choose
	 *	the region closest to you for best performance.
	 */
	enum class region_t
	{
		NA,		// North America
		EUW,		// EU-West
		EUNE,		// EU North-East
		BR,		// Brazil
		KR,		// Korea
		LAN,		// Latin-America North
		LAS,		// Latin-America South
		OCE,		// Oceania
		TR,		// Turkey
		RU 		// Russia
	};

	/// Endpoint Name Type
	typedef std::string 		endpoint_t;
	/// Endpoint Version Type
	typedef std::string 		version_t;
	/// API Key Type
	typedef std::string 		api_key_t;
}

#endif // RIOT_CORE_H
