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
				if( !optional() && child->parse( json[key()] ) == false )
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
				if( !optional() && child->parse( json ) == false )
				{
					return false;
				}
			}
			
			return true;
		}

		return optional();
	}
}