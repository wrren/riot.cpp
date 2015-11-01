#ifndef RIOT_H
#define RIOT_H

#include <riot/core/core.h>

namespace riot
{
	/**
	 *	Main interface for Riot API interactions
	 */
	class riot_client
	{
	public:

		/**
		 *	Construct a Riot API Client that will connect to the
		 *	API server for the given region using the provided API key
		 * @param region 	API Server Region
		 * @param api_key 	Client API Key
		 */
		riot_client( 	region connect_region, 
				const api_key_t& api_key );

	private:

		/// Target API Server Region
		region m_region;
		/// API Client Key
		api_key_t m_key;
	};
}

#endif // RIOT_H
