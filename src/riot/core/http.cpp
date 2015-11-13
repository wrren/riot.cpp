#include <riot/core/http.h>
#include <riot/dto/dto_exception.h>
#include <curl/curl.h>

#include <thread>
#include <map>
#include <string>
#include <iostream>

namespace riot
{
	namespace http
	{
		size_t request_write_callback( void* data, size_t size, size_t nmemb, void* obj )
		{
			( ( std::string* ) obj )->append( ( char* ) data, size * nmemb );
			return size * nmemb;
		}

		size_t request_header_callback( void* data, size_t size, size_t nmemb, void* obj )
		{
			( ( std::string* ) obj )->append( ( char* ) data, size * nmemb );
			return size * nmemb;
		}

		std::map<std::string, std::string> parse_headers( const std::string& header_buffer )
		{
			const std::string keyval_sep = ":";
			const std::string header_sep = "\r\n";

			std::map<std::string, std::string> headers;

			std::string::size_type start = 0;

			auto trim = []( const std::string& in )
			{
				auto start 	= in.find_first_not_of( " " );
				auto end 	= in.find_last_not_of( " " );

				return in.substr( start, end - start + 1 );
			};

			do
			{
				if( start > 0 )
				{
					start += header_sep.length();
				}

				auto keyval_sep_pos 	= header_buffer.find( keyval_sep, start + 1 );
				auto header_sep_pos 	= header_buffer.find( header_sep, start + 1 );
				
				if( keyval_sep_pos != std::string::npos )
				{
					auto key = header_buffer.substr( start, keyval_sep_pos - start );
					auto val = header_buffer.substr( keyval_sep_pos + 1, header_sep_pos - keyval_sep_pos - 1 );
					headers[trim(key)] = trim(val);
					continue;
				}

				break;
			} while( ( start = header_buffer.find( header_sep, start + 1 ) ) != std::string::npos );

			return headers;
		}

		json request( const std::string& url, bool retry )
		{
			CURL* curl = curl_easy_init();

			if( curl == NULL )
			{
				return json( json::CLIENT_ERROR );
			}

			CURLcode result;
			long status_code = 0;
			std::string read_buffer, header_buffer;

			curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
			curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1 );
			curl_easy_setopt( curl, CURLOPT_WRITEDATA, &read_buffer );
			curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, request_write_callback );
			curl_easy_setopt( curl, CURLOPT_HEADERFUNCTION, &request_header_callback ); // our static function
			curl_easy_setopt( curl, CURLOPT_WRITEHEADER, &header_buffer );

			result = curl_easy_perform( curl );

			curl_easy_getinfo( curl, CURLINFO_RESPONSE_CODE, &status_code );

			json response( status_code );

			if( result == CURLE_OK && status_code == 200 )
			{
				response.parse( read_buffer );
			}
			else if( status_code == 400 )
			{
				throw dto_exception( dto_exception::REQUEST_EXCEPTION, "Bad Request" );
			}
			else if( status_code == 401 )
			{
				throw dto_exception( dto_exception::AUTHORIZATION_EXCEPTION, "Authorization Error - Check API Key" );
			}
			else if( status_code == 429 )
			{
				auto headers = parse_headers( header_buffer );

				if( headers.find( "Retry-After" ) != headers.end() )
				{
					try
					{
						std::chrono::seconds wait_for( std::stoi( headers["Retry-After"] ) );

						if( retry )
						{
							std::this_thread::sleep_for( wait_for );
							return request( url, retry );
						}
						throw dto_rate_exception( wait_for );
					}
					catch( std::invalid_argument e )
					{
						std::cerr << "Failed to parse Retry-After header, aborting request..." << std::endl;
					}				
				}
				
				throw dto_exception( dto_exception::RATE_LIMIT_EXCEPTION, "Rate Limit Exceeded" );
			}
			
			curl_easy_cleanup( curl );

			return response;
		}	
	}
	
}