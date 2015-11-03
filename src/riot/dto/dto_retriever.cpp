#include <riot/dto/dto_retriever.h>
#include <riot/riot.h>

namespace riot
{
	dto_retriever::dto_retriever( riot_client* client ) :
	m_client( client )
	{}

	region_t dto_retriever::region() const
	{
		return m_client->region();
	}

	const api_key_t& dto_retriever::key() const
	{
		return m_client->key();
	}

	riot_client* dto_retriever::client() const
	{
		return m_client;
	}
}