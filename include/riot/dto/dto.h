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
			return m_decoder( key(), optional(), m_value, json );
		}

		/**
		 *	Get access to the underlying value
		 */
		operator const T&() const 	{ return m_value; }
		operator T&() 			{ return m_value; }

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
