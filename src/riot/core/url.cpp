#include <riot/core/url.h>
#include <sstream>
#include <iterator>

#define URL_BUFFER_MAX_LENGTH 256

namespace riot
{
	const std::map<region_t, const char*> url::m_region_mapping = {
		{ region_t::NA, 	"na" },
		{ region_t::EUW, 	"euw"},
		{ region_t::EUNE,	"eune" },
		{ region_t::BR, 	"br" },
		{ region_t::KR, 	"kr" },
		{ region_t::LAN, 	"lan" },
		{ region_t::LAS, 	"las" },
		{ region_t::OCE, 	"oce" },
		{ region_t::TR, 	"tr" },
		{ region_t::RU, 	"ru" },
	};


	std::string url::form( 	region_t region, 
				bool static_data,
				const endpoint_t& endpoint,
				const version_t& version,
				const api_key_t& api_key,
				const std::vector<std::string>& path,
				const std::map<std::string, std::string> params )
	{
		char buffer[URL_BUFFER_MAX_LENGTH];

		if( static_data )
		{
			snprintf( 	buffer, 
					URL_BUFFER_MAX_LENGTH,
					"https://%s.api.pvp.net/api/lol/static-data/%s/v%s/%s",
					m_region_mapping.at( region ),
					m_region_mapping.at( region ),
					version.c_str(),
					endpoint.c_str() );
		}
		else
		{
			snprintf( 	buffer, 
					URL_BUFFER_MAX_LENGTH,
					"https://%s.api.pvp.net/api/lol/%s/v%s/%s",
					m_region_mapping.at( region ),
					m_region_mapping.at( region ),
					version.c_str(),
					endpoint.c_str() );
		}

		std::string url( buffer );
		
		for( auto& part : path )
		{
			url += "/" + part;
		}

		url += "?api_key=" + api_key + "&";

		for( auto& kv : params )
		{
			url += kv.first + "=" + kv.second + "&";
		}

		url.erase( url.end() - 1 );
		
		return url;
	}

	std::string url::collapse( const std::vector<std::string>& strings )
	{
		std::ostringstream stream;
		std::copy( strings.begin(), strings.end(), std::ostream_iterator<std::string>( stream, "," ) );
		std::string collapsed = stream.str();
		collapsed.erase( collapsed.end() - 1 );

		return collapsed;
	}
}