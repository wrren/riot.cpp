#ifndef RIOT_INT_KEY_H
#define RIOT_INT_KEY_H

#include <riot/core/core.h>
#include <catch.hpp>

/**
 *	Get access to the test API key for integration tests	
 */
class int_key
{
public:

	/**
	 *	Set the integration test API key
	 */
	static void set_key( const riot::api_key_t& key );

	/**
	 *	Get the integration test api key
	 */
	static const riot::api_key_t& get_key();

private:

	/// Configured Key
	static riot::api_key_t m_key;
};

#endif // RIOT_INT_KEY_H