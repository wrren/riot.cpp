#include <riot/dto/match.h>

namespace riot
{
	participant_identity::participant_identity( const std::string& key ) :
	dto_object( key, dto_base::REQUIRED )
	{}

	participant::participant( const std::string& key ) : 
	dto_object( key, dto_base::REQUIRED )
	{}
}