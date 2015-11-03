#include <riot/dto/dto.h>
#include <riot/riot.h>

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

	riot_client* dto_base::client() const
	{
		return m_client;
	}

	void dto_base::set_client( riot_client* client )
	{
		m_client = client;
	}
}