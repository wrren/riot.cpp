#ifndef RIOT_DTO_RETRIEVER_H
#define RIOT_DTO_RETRIEVER_H

#include <riot/core/core.h>

namespace riot
{
	/// Client Forward-Declaration
	class riot_client;

	/**
	 *	Base class for retrievers. Retrievers encapsulate the functions that allow DTOs
	 *	to be retrieved from the Riot API
	 */
	class dto_retriever
	{
	public:

		/**
		 *	Construct a retriever, passing a pointer to the parent api client
		 */
		dto_retriever( riot_client* client );

		/// Target API Region Accessor
		region_t region() const;

		/// API Key Accessor
		const api_key_t& key() const;

		/// Client Accessor
		riot_client* client() const;
		
	private:

		/// Riot Client
		riot_client*	m_client;
		/// Target Region
		region_t 	m_region;
		/// API Key
		api_key_t	m_key;
	};
}

#endif // RIOT_DTO_RETRIEVER_H
