#ifndef RIOT_DTO_BASE_H
#define RIOT_DTO_BASE_H

#include <riot/core/core.h>
#include <rapidjson/document.h>

namespace riot
{
	class riot_client;

	/**
	 *	Base class for data transfer objects
	 */
	class dto_base
	{
	public:

		/**
		 *	Indicates whether a DTO field is optional or required. Optional fields
		 *	that fail to parse or are not present will not raise an error
		 */
		enum presence
		{
			OPTIONAL,
			REQUIRED
		};

		/**
		 *	Construct a DTO object that's associated with the
		 *	given key
		 * @param key 	Object Key
		 */
		dto_base( const std::string& key = "", presence optional = REQUIRED );

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

		/**
		 *	Check whether this field has been marked as optional
		 */
		bool optional() const;

		/**
		 *	For optional fields, indicates whether the data associated with
		 *	the field was parsed.
		 * @return true - If the data for this field was present, false if it was missing
		 */
		bool is_present() const;

		/// Client Accessors
		riot_client* client() const;
		void set_client( riot_client* client );

	protected:

		/**
		 *	Set whether the data for this field was present during parsing
		 * @param present true - If the data for the field was present, false otherwise
		 */
		void set_present( bool present );

	private:

		/// Client Handle
		riot_client*	m_client;
		/// For optional fields, indicates whether the field data was present during parsing
		bool		m_present;
		/// Object Key
		std::string 	m_key;
		/// Indicates whether this is an optional field
		presence	m_optional;
	};
}

#endif // RIOT_DTO_BASE_H

