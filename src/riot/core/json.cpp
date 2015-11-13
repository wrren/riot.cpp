#include <riot/core/core.h>
#include <riot/core/json.h>

namespace riot
{
	json::json( int status ) :
	m_status( status )
	{}
		
	bool json::ok() const
	{
		return !m_document.HasParseError();
	}

	int json::status() const
	{
		return m_status;
	}
		
	const rapidjson::Document& json::document() const
	{
		return m_document;
	}

	void json::parse( const std::string& response )
	{
		m_document.Parse<0>( response.c_str() );
	}
}