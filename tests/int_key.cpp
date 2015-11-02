#define CATCH_CONFIG_RUNNER

#include "int_key.h"
#include <fstream>
#include <string>
#include <iostream>

riot::api_key_t int_key::m_key = "";

void int_key::set_key( const riot::api_key_t& key )
{
	m_key = key;
}

const riot::api_key_t& int_key::get_key()
{
	return m_key;
}


int main( int argc, char** argv )
{
	std::string pwd( argv[0] );
	const char separator = 
#ifdef _WIN32
	'\\';
#else
	'/';
#endif	
	auto last = pwd.find_last_of( separator );
	std::string api_key_path = pwd.substr( 0, last ) + "/../test_api_key.txt";

	std::ifstream ifs( api_key_path );
	std::string key( 	( std::istreambuf_iterator<char>( ifs ) ),
	       			( std::istreambuf_iterator<char>()    ) );

	ifs.close();

	if( key.length() == 0 )
	{
		throw std::runtime_error( "Please set your test API key in tests/test_api_key.txt" );
	}

	int_key::set_key( key );

	return Catch::Session().run( argc, argv );
}