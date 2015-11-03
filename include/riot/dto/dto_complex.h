#ifndef RIOT_DTO_COMPLEX_H
#define RIOT_DTO_COMPLEX_H

#include <riot/dto/dto_base.h>

namespace riot
{
	// Client Forward-Declaration
	class riot_client;

	/**
	 *	Represents a complex dto with nested members that must also be decoded
	 */
	class dto_complex : public dto_base
	{
	public:

		/**
		 *	Default Constructor
		 */
		dto_complex( const std::string& key = "", dto_base::presence optional = dto_base::REQUIRED );

		/**
		 *	Parse a object from the given JSON
		 * @param json 	JSON Data
		 * @return 	true - If parsing was successful, false otherwise.
		 */
		virtual bool parse( const rapidjson::Value& json ) override;

	protected:

		/**
		 *	Get all child DTO objects for this type
		 * @return vector of child DTO objects
		 */
		virtual std::vector<dto_base*> get_children() = 0;
		
	};
}

#endif // RIOT_DTO_COMPLEX_H