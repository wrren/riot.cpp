#ifndef RIOT_DTO_H
#define RIOT_DTO_H

#include <riot/core/core.h>
#include <riot/core/json.h>
#include <riot/core/url.h>

namespace riot
{
	/**
	 *	Base class for data transfer objects
	 */
	class dto_base
	{
	public:

		/**
		 *	Construct a DTO object that's associated with the
		 *	given key
		 * @param key 	Object Key
		 */
		dto_base( const std::string& key = "" );

		/**
		 *	Parse a value or object from the given JSON
		 * @param json 	JSON Data
		 * @return 	true - If parsing was successful, false otherwise.
		 */
		virtual bool parse( const rapidjson::Value& json ) = 0;

		/**
		 *	Get this object's key
		 * @return Object Key
		 */
		const char* key() const;

	private:

		/// Object Key
		std::string m_key;
	};

	/**
	 *	Complex object types
	 */
	class dto_object : public dto_base
	{
	public:

		/**
		 *	Default Constructor
		 */
		dto_object( const std::string& key ) : dto_base( key )
		{}

		/**
		 *	Parse a object from the given JSON
		 * @param json 	JSON Data
		 * @return 	true - If parsing was successful, false otherwise.
		 */
		virtual bool parse( const rapidjson::Value& json ) override
		{
			for( auto& child : get_children() )
			{
				if( child->parse( json ) == false )
				{
					return false;
				}
			}

			return true;
		}

	protected:

		/**
		 *	Get all child DTO objects for this type
		 * @return vector of child DTO objects
		 */
		virtual std::vector<dto_base*> get_children() = 0;
	};

	/**
	 *	Vector of DTO objects under a given key
	 */
	template<typename T>
	class dto_vector : public dto_base
	{
	public:

		/**
		 *	Default Constructor
		 */
		dto_vector( const std::string& key = "" ) : dto_base( key )
		{}

		/**
		 *	Parse the array from the given JSON data
		 * @param json JSON Data
		 * @return 	true - If parsing was successful, false otherwise.
		 */
		virtual bool parse( const rapidjson::Value& json ) override
		{
			if( json.IsObject() && json.HasMember( key() ) && json[key()].IsArray() )
			{
				for( rapidjson::SizeType i = 0; i < json[key()].Size(); i++ )
				{
					T v;

					if( v.parse( json[key()][i] ) == false )
					{
						return false;
					}

					m_values.push_back( v );
				}

				return true;
			}
			else if( json.IsArray() )
			{
				for( rapidjson::SizeType i = 0; i < json.Size(); i++ )
				{
					T v;

					if( v.parse( json[i] ) == false )
					{
						return false;
					}

					m_values.push_back( v );
				}

				return true;
			}

			return false;
		}

		/**
		 *	Values Accessor
		 */
		const std::vector<T>& values() const
		{
			return m_values;
		}

	private:

		/// Parsed Vector
		std::vector<T> m_values;
	};

	/**
	 *	Map of keys to DTO objects that attempts to parse as many from the JSON result as possible
	 */
	template<typename T>
	class dto_map : public dto_base
	{
	public:

		/**
		 *	Default Constructor
		 */
		dto_map( const std::vector<std::string>& search_keys, const std::string& key = "" ) : 
		dto_base( key ),
		m_keys( search_keys )
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
					T v( k );

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
					T v( k );

					if( v.parse( json ) )
					{
						m_values.push_back( v );
					}
				}

				return true;
			}

			return false;
		}

		/**
		 *	Values Accessor
		 */
		const std::vector<T>& values() const
		{
			return m_values;
		}

	private:

		/// Target Keys
		std::vector<std::string> 	m_keys;
		/// Parsed Vector
		std::vector<T> 			m_values;
	};

	template<typename T, typename enable = void>
	class dto_value
	{};

	/**
	 *	Integral type specialization
	 */
	template<typename T>
	class dto_value<T, typename std::enable_if<std::is_integral<T>::value>::type> : public dto_base
	{
	public:

		/**
		 *	Default Constructor
		 */
		dto_value( const std::string& key = "" ) : dto_base( key )
		{}

		/**
		 *	Parse the value from the given JSON data
		 * @param json 	JSON Data
		 * @return 	true - If parsing was successful, false otherwise.
		 */
		virtual bool parse( const rapidjson::Value& json ) override
		{
			if( json.IsObject() && json.HasMember( key() ) && json[key()].IsInt() )
			{
				m_value = json[key()].GetInt();
				return true;
			}
			else if( json.IsInt() )
			{
				m_value = json.GetInt();
				return true;
			}

			return false;
		}

		/**
		 *	Conversion Operator
		 */
		operator T() const
		{
			return m_value;
		}

	private:

		/// Value
		T m_value;
	};

	/**
	 *	Float type specialization
	 */
	template<typename T>
	class dto_value<T, typename std::enable_if<std::is_floating_point<T>::value>::type> : public dto_base
	{
	public:

		/**
		 *	Default Constructor
		 */
		dto_value( const std::string& key = "" ) : dto_base( key )
		{}

		/**
		 *	Parse the value from the given JSON data
		 * @param json 	JSON Data
		 * @return 	true - If parsing was successful, false otherwise.
		 */
		virtual bool parse( const rapidjson::Value& json ) override
		{
			if( json.IsObject() && json.HasMember( key() ) && json[key()].IsDouble() )
			{
				m_value = json[key()].GetDouble();
				return true;
			}
			else if( json.IsDouble() )
			{
				m_value = json.GetDouble();
				return true;
			}

			return false;
		}

		/**
		 *	Conversion Operator
		 */
		operator T() const
		{
			return m_value;
		}

	private:

		/// Value
		T m_value;
	};

	/**
	 *	Boolean type specialization
	 */
	template<typename T>
	class dto_value<T, typename std::enable_if<std::is_same<T, bool>::value>::type> : public dto_base
	{
	public:

		/**
		 *	Default Constructor
		 */
		dto_value( const std::string& key = "" ) : dto_base( key )
		{}

		/**
		 *	Parse the value from the given JSON data
		 * @param json 	JSON Data
		 * @return 	true - If parsing was successful, false otherwise.
		 */
		virtual bool parse( const rapidjson::Value& json ) override
		{
			if( json.IsObject() && json.HasMember( key() ) && json[key()].IsBool() )
			{
				m_value = json[key()].GetBool();
				return true;
			}
			else if( json.IsBool() )
			{
				m_value = json.GetBool();
				return true;
			}

			return false;
		}

		/**
		 *	Conversion Operator
		 */
		operator T() const
		{
			return m_value;
		}

	private:

		/// Parsed Value
		T m_value;
	};

	/**
	 *	String type specialization
	 */
	template<typename T>
	class dto_value<T, typename std::enable_if<std::is_same<T, std::string>::value>::type> : public dto_base
	{
	public:

		/**
		 *	Default Constructor
		 */
		dto_value( const std::string& key = "" ) : dto_base( key )
		{}

		/**
		 *	Parse the value from the given JSON data
		 * @param json 	JSON Data
		 * @return 	true - If parsing was successful, false otherwise.
		 */
		virtual bool parse( const rapidjson::Value& json ) override
		{
			if( json.IsObject() && json.HasMember( key() ) && json[key()].IsString() )
			{
				m_value = json[key()].GetString();
				return true;
			}
			else if( json.IsString() )
			{
				m_value = json.GetString();
				return true;
			}

			return false;
		}

		/**
		 *	Conversion Operator
		 */
		operator const T&() const
		{
			return m_value;
		}

	private:

		/// Parsed Value
		T m_value;
	};

	/**
	 *	Base class for retrievers. Retrievers encapsulate the functions that allow DTOs
	 *	to be retrieved from the Riot API
	 */
	class dto_retriever
	{
	public:

		/**
		 *	Construct a retriever, passing references to the current target
		 *	region and api key
		 */
		dto_retriever( region_t& region, api_key_t& key );

	protected:

		/**
		 *	Get the current target region
		 */
		const region_t& region() const;

		/**
		 *	Get the current API key
		 */
		const api_key_t& key() const;

	private:

		/// Target Region
		region_t& 	m_region;
		/// API Key
		api_key_t&	m_key;
	};

	// Convenience Type Definitions
	typedef dto_value<uint32_t> 	dto_uint;
	typedef dto_value<int32_t>	dto_int;
	typedef dto_value<double>	dto_double;
	typedef dto_value<std::string> 	dto_string;
	typedef dto_value<bool>		dto_bool;
}

#endif // RIOT_DTO_H
