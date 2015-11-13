#include <riot/dto/dto_exception.h>

namespace riot
{
	dto_exception::dto_exception( dto_exception::type_t type, const char* what ) :
	std::runtime_error( what ),
	m_type( type )
	{}

	dto_exception::type_t dto_exception::type() const
	{
		return m_type;
	}

	dto_rate_exception::dto_rate_exception( const std::chrono::seconds& wait_for ) :
	dto_exception( dto_exception::RATE_LIMIT_EXCEPTION, "Rate Limit Exceeded" ),
	m_wait_for( wait_for )
	{}

	const std::chrono::seconds& dto_rate_exception::wait_for() const
	{
		return m_wait_for;
	}
}