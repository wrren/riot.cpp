#ifndef RIOT_DTO_DECODER_H
#define RIOT_DTO_DECODER_H

#include <riot/core/core.h>

namespace riot
{
	/**
	 *	Generic template class that allows various primitive types
	 *	to be easily pulled from a rapidJSON Value object through
	 *	its various Is() and Get() methods
	 */
	template<	typename T, typename U,
			bool (	rapidjson::GenericValue<rapidjson::UTF8<char>,
      				rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> >::*Checker )( void ) const,
			U ( 	rapidjson::GenericValue<rapidjson::UTF8<char>,
      				rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> >::*Decoder )( void ) const>
	class dto_decoder
	{
	public:

		/**
		 *	Decode the target type from the given data
		 * @param key 		Search Key
		 * @param optional	Indicates whether this value must be present
		 * @param value 	Output Value
		 * @param json 		JSON Data
		 * @return 		true - If the data was decoded or is optional, false otherwise.
		 */
		bool operator()( const char* key, bool optional, T& value, const rapidjson::Value& json )
		{
			if( json.IsObject() && json.HasMember( key ) && ( ( json[key] ).*( Checker ) )() )
			{
				value = ( ( json[key] ).*( Decoder ) )();
				return true;
			}
			else if( ( ( json ).*( Checker ) )() )
			{
				value = ( ( json ).*( Decoder ) )();
				return true;
			}

			return optional;
		}	
	};

	typedef dto_decoder<bool, bool, &rapidjson::Value::IsBool, &rapidjson::Value::GetBool> 				dto_bool_decoder;
	typedef dto_decoder<int32_t, int32_t, &rapidjson::Value::IsInt, &rapidjson::Value::GetInt>			dto_int_decoder;
	typedef dto_decoder<uint32_t, uint32_t, &rapidjson::Value::IsUint, &rapidjson::Value::GetUint> 			dto_uint_decoder;
	typedef dto_decoder<int64_t, int64_t, &rapidjson::Value::IsInt64, &rapidjson::Value::GetInt64>			dto_int64_decoder;
	typedef dto_decoder<uint64_t, uint64_t, &rapidjson::Value::IsUint64, &rapidjson::Value::GetUint64> 		dto_uint64_decoder;
	typedef dto_decoder<double, double, &rapidjson::Value::IsDouble, &rapidjson::Value::GetDouble>			dto_double_decoder;
	typedef dto_decoder<std::string, const char*, &rapidjson::Value::IsString, &rapidjson::Value::GetString>	dto_string_decoder;
}

#endif // RIOT_DTO_DECODER_H
