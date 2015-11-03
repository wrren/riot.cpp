#ifndef RIOT_DTO_MAP_H
#define RIOT_DTO_MAP_H

#include <riot/dto/dto_base.h>

namespace riot
{
	/**
	 *	Map of keys to DTO objects that attempts to parse as many from the JSON result as possible
	 */
	template<typename T>
	class dto_map : public dto_base
	{
	public:

		/**
		 *	Default Constructor
		 * @param search_keys 	Object keys to search for
		 * @param optional 	Indicates whether this is an optional field
		 * @param encode 	true - Keys will be lower-cased and collapsed, false - keys used as-is
		 * @param key		Map object key
		 */
		dto_map( 	const std::vector<std::string>& search_keys, 
				presence optional = REQUIRED,
				bool encode = true, 
				const std::string& key = "" ) : 
		dto_base( key, optional ),
		m_keys( search_keys ),
		m_encode( encode )
		{}

		/**
		 *	Parse the array from the given JSON data
		 * @param json JSON Data
		 * @return 	true - If parsing was successful, false otherwise.
		 */
		virtual bool parse( const rapidjson::Value& json ) override
		{
			if( json.IsObject() && json.HasMember( key() ) )
			{
				for( auto& k : m_keys )
				{
					T v( m_encode ? encode( k ) : k );
					v.set_client( client() );
					if( v.parse( json[key()] ) )
					{
						m_values.push_back( v );
					}
				}

				return true;
			}
			else if( json.IsObject() )
			{
				for( auto& k : m_keys )
				{
					T v( m_encode ? encode( k ) : k );
					v.set_client( client() );
					if( v.parse( json ) )
					{
						m_values.push_back( v );
					}
				}

				return true;
			}

			return optional();
		}

		/**
		 *	Values Accessor
		 */
		const std::vector<T>& values() const
		{
			return m_values;
		}

	private:

		static std::string encode( const std::string& in )
		{
			std::string encoded( in );
			std::transform( encoded.begin(), encoded.end(), encoded.begin(), ::tolower );
			return str_replace( encoded, " ", "" );
		}

		/// Encode search keys during parse phase
		bool 				m_encode;
		/// Target Keys
		std::vector<std::string> 	m_keys;
		/// Parsed Vector
		std::vector<T> 			m_values;
	};
}

#endif // RIOT_DTO_MAP_H
