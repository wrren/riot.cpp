#include <riot/dto/dto.h>

namespace riot
{
	dto_base::dto_base( const std::string& key, dto_base::presence optional ) : 
	m_key( key ),
	m_optional( optional )
	{}

	const char* dto_base::key() const
	{
		return m_key.c_str();
	}

	bool dto_base::optional() const
	{
		return m_optional == dto_base::OPTIONAL;
	}

	dto_retriever::dto_retriever( region_t region, const api_key_t& key ) :
	m_region( region ),
	m_key( key )
	{}

	region_t dto_retriever::region() const
	{
		return m_region;
	}

	const api_key_t& dto_retriever::key() const
	{
		return m_key;
	}
}