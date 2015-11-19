#ifndef RIOT_DTO_H
#define RIOT_DTO_H

#include <riot/dto/dto_base.h>
#include <riot/dto/dto_retriever.h>
#include <riot/dto/dto_vector.h>
#include <riot/dto/dto_map.h>
#include <riot/dto/dto_complex.h>
#include <riot/dto/dto_decoder.h>

#include <riot/core/core.h>
#include <riot/core/json.h>
#include <riot/core/url.h>

namespace riot
{
	/**
	 *	Exception type thrown by DTO functions
	 */
	class dto_exception : std::runtime_error
	{
		enum class type
		{
			INVALID_CREDENTIALS,
			API_LIMIT_EXCEEDED,
			DATA_NOT_FOUND
		};

		/**
		 *	Default Constructor
		 */
		dto_exception( type t, const std::string& what ) :
		std::runtime_error( what ),
		m_type( t )
		{}

	private:

		/// Exception Type
		type m_type;
	};

	/**
	 *	Base class for simple types that can be encoded/decoded from a data stream
	 */
	template<typename T, typename Decoder>
	class dto : public dto_base
	{
	public:

		/// Default Constructor
		dto( const std::string& key = "", presence optional = dto_base::REQUIRED ) :
		dto_base( key, optional )
		{}

		/**
		 *	Parse a object from the given JSON
		 * @param json 	JSON Data
		 * @return 	true - If parsing was successful, false otherwise.
		 */
		virtual bool parse( const rapidjson::Value& json ) override
		{
			if( !m_decoder( key(), m_value, json ) && !optional() )
			{
				set_present( false );
				return false;
			}
			else
			{
				set_present( true );
				return true;
			}
		}

		/**
		 *	Get access to the underlying value
		 */
		const T& operator()() const	{ return m_value; }
		T& operator()()			{ return m_value; }
		operator const T&() const 	{ return m_value; }
		operator T&() 			{ return m_value; }
		const T& get() const 		{ return m_value; }
		T& get() 			{ return m_value; }

	private:

		/// Decoder Type
		Decoder m_decoder;
		/// Contained Value
		T m_value;
	};

	// Convenience Type Definitions
	typedef dto<bool, dto_bool_decoder>		dto_bool;
	typedef dto<int32_t, dto_int_decoder> 		dto_int;
	typedef dto<uint32_t, dto_uint_decoder> 	dto_uint;
	typedef dto<int64_t, dto_int64_decoder> 	dto_int64;
	typedef dto<uint64_t, dto_uint64_decoder> 	dto_uint64;
	typedef dto<double, dto_double_decoder>		dto_double;
	typedef dto<std::string, dto_string_decoder>	dto_string;
}

#endif // RIOT_DTO_H
