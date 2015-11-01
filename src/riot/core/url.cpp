#include <riot/core/url.h>

#define URL_BUFFER_MAX_LENGTH 256

namespace riot
{
	const std::map<region, const char*> url::m_region_mapping = {
		{ region::NA, 	"na" },
		{ region::EUW, 	"euw"},
		{ region::EUNE,	"eune" },
		{ region::BR, 	"br" },
		{ region::KR, 	"kr" },
		{ region::LAN, 	"lan" },
		{ region::LAS, 	"las" },
		{ region::OCE, 	"oce" },
		{ region::TR, 	"tr" },
		{ region::RU, 	"ru" },
	};


	std::string url::form( 	region connect_region, 
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
					m_region_mapping.at( connect_region ),
					m_region_mapping.at( connect_region ),
					version.c_str(),
					endpoint.c_str() );
		}
		else
		{
			snprintf( 	buffer, 
					URL_BUFFER_MAX_LENGTH,
					"https://%s.api.pvp.net/api/lol/%s/v%s/%s",
					m_region_mapping.at( connect_region ),
					m_region_mapping.at( connect_region ),
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
}