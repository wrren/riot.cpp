#include <riot/dto/dto.h>

namespace riot
{
	dto_base::dto_base( const std::string& key ) : m_key( key )
	{}

	const char* dto_base::key() const
	{
		return m_key.c_str();
	}

	dto_retriever::dto_retriever( region_t& region, api_key_t& key ) :
	m_region( region ),
	m_key( key )
	{}

	const region_t& dto_retriever::region() const
	{
		return m_region;
	}

	const api_key_t& dto_retriever::key() const
	{
		return m_key;
	}
}