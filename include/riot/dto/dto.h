#ifndef RIOT_DTO_H
#define RIOT_DTO_H

#include <riot/core/core.h>

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
		dto_base( const std::string& key );

		/**
		 *	Get this object's key
		 * @return Object Key
		 */
		const std::string& key() const;

	private:

		/// Object Key
		std::string m_key;
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
		dto_vector( const std::string& key ) : dto_base( key )
		{}
	};

	template<typename T>
	class dto_value
	{
	public:



	private:

		/// JSON Key
		std::string m_key;
	};
}

#endif // RIOT_DTO_H
