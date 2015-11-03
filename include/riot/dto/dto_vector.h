#ifndef RIOT_DTO_VECTOR_H
#define RIOT_DTO_VECTOR_H

#include <riot/dto/dto_base.h>

namespace riot
{
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
		dto_vector( const std::string& key = "", presence optional = REQUIRED ) : dto_base( key, optional )
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
					v.set_client( client() );
					if( !optional() && v.parse( json[key()][i] ) == false )
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
					v.set_client( client() );
					if( !optional() && v.parse( json[i] ) == false )
					{
						return false;
					}

					m_values.push_back( v );
				}

				return true;
			}

			return optional();
		}

		typename std::vector<T>::iterator begin() 		{ return m_values.begin(); }
		typename std::vector<T>::iterator end() 		{ return m_values.end(); }
		typename std::vector<T>::const_iterator begin() const 	{ return m_values.begin(); }
		typename std::vector<T>::const_iterator end() const	{ return m_values.end(); }

		/// Element Access
		T& operator[]( size_t index )
		{
			return m_values[index];
		}

		/// Vector Size
		typename std::vector<T>::size_type size() const
		{
			return m_values.size();
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
}

#endif // RIOT_DTO_VECTOR_H
