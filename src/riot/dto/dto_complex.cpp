#include <riot/dto/dto_complex.h>

namespace riot
{
	dto_complex::dto_complex( 	const std::string& key, 
					dto_base::presence optional ) :
	dto_base( key, optional )
	{}

	bool dto_complex::parse( const rapidjson::Value& json )
	{
		if( json.IsObject() && json.HasMember( key() ) && json[key()].IsObject() )
		{
			for( auto& child : get_children() )
			{
				child->set_client( client() );
				if( !child->parse( json[key()] ) && !optional() )
				{
					return false;
				}
			}
			
			return true;
		}
		else if( json.IsObject() )
		{
			for( auto& child : get_children() )
			{
				child->set_client( client() );
				if( !child->parse( json ) && !optional()  )
				{
					return false;
				}
			}
			
			return true;
		}

		set_present( false );
		return optional();
	}
}