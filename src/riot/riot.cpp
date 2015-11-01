#include <riot/riot.h>

namespace riot
{
	riot_client::riot_client( region connect_region, const api_key_t& key ) :
	m_region( connect_region ),
	m_key( key )
	{}
}