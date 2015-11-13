#ifndef RIOT_API_REQUEST_H
#define RIOT_API_REQUEST_H

#include <riot/core/json.h>
#include <map>

namespace riot
{
	namespace http
	{

		/**
		 *	Initiate a GET request for the provided URL and generate a json response object using
		 *	the result. This function may throw a dto_exception depending on the response received
		 * @param url 	Target URL for the HTTP request
		 * @param retry	If rate limit is hit, should the request stall and retry?
		 * @return 	json response
		 */
		json request( const std::string& uri, bool retry = true );

		/**
		 *	Given a string containing raw encoded HTTP headers, generate a map of key-value
		 * 	pairs mapping header keys to values
		 * @param header_buffer String containing header data
		 * @return 		Header data key-value pairs
		 */
		std::map<std::string, std::string> parse_headers( const std::string& header_buffer );
	};
}

#endif // RIOT_API_REQUEST_H
