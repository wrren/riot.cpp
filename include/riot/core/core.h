#ifndef RIOT_CORE_H
#define RIOT_CORE_H

#include <string>
#include <vector>
#include <map>
#include <sstream>

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

	/// Replace sections of string
	std::string str_replace( const std::string& in, const std::string& find, const std::string& replacement );

	/// Convert a vector of values into a vector of strings
	template<typename T>
	std::vector<std::string> str_convert( const std::vector<T>& in )
	{
		std::vector<std::string> out;

		for( auto& v : in )
		{
			std::stringstream ss;
			ss << v;
			out.push_back( ss.str() );
		}

		return out;
	}

	template<typename T, typename U>
	std::vector<std::string> str_convert( const std::vector<T>& in, std::function<U ( const T& )> func )
	{
		std::vector<std::string> out;

		for( auto& v : in )
		{
			std::stringstream ss;
			ss << func( v );
			out.push_back( ss.str() );
		}

		return out;
	}
}

#endif // RIOT_CORE_H
