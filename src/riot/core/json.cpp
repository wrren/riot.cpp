#include <riot/core/core.h>
#include <riot/core/json.h>
#include <curl/curl.h>

namespace riot
{
	json::json( int status ) :
	m_status( status )
	{}

	json json::get( const std::string& url )
	{
		CURL* curl = curl_easy_init();

		if( curl == NULL )
		{
			return json( json::CLIENT_ERROR );
		}

		CURLcode result;
		std::string read_buffer;

		curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
		curl_easy_setopt( curl, CURLOPT_WRITEDATA, &read_buffer );
		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, json::write_callback );

		result = curl_easy_perform( curl );

		json response( result );

		if( result == CURLE_OK )
		{
			response.parse( read_buffer );
		}
		
		curl_easy_cleanup( curl );

		return response;
	}
		
	bool json::ok() const
	{
		return m_document.HasParseError();
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
		m_document.Parse( response.c_str() );
	}

	size_t json::write_callback( void* data, size_t size, size_t nmemb, void* obj )
	{
		( ( std::string* ) obj )->append( ( char* ) data, size * nmemb );
		return size * nmemb;
	}
}