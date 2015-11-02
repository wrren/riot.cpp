#include <riot/core/core.h>

namespace riot
{
	std::string str_replace( const std::string& in, const std::string& find, const std::string& replacement )
	{
		size_t start_pos = 0;
		std::string modified( in );

		while( ( start_pos = modified.find( find, start_pos ) ) != std::string::npos ) 
		{
			modified.replace( start_pos, find.length(), replacement );
			start_pos += replacement.length();
		}

		return modified;
	}
}