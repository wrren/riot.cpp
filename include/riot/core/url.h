#ifndef RIOT_URL_H
#define RIOT_URL_H

#include <riot/core/core.h>

namespace riot
{
	/**
	 *	Encapsulates convenience functions for generating URLs for Riot API endpoints
	 */
	class url
	{
	public:

		/**
		 *	Form a URL that refers to a Riot API endpoint with the specified parameters
		 * @param region 	Target Riot API Region
		 * @param static_data	Indicates whether we're retrieving data from the static data API
		 * @param endpoint 	Target Endpoint Name
		 * @param version 	Endpoint Version
		 * @param api_key	Riot API Key
		 * @param path 		Addition Path Parameters ( e.g /name/Garen )
		 * @param params 	Additional GET Parameters
		 * @return 		URL String
		 */
		static std::string form( 	region region, 
						bool static_data,
						const endpoint_t& endpoint,
						const version_t& version,
						const api_key_t& api_key,
						const std::vector<std::string>& path = {},
						const std::map<std::string, std::string> params = {} );
		
	private:

		/// Region Mappings
		static const std::map<region, const char*> m_region_mapping;
	};
}

#endif // RIOT_URL_H
