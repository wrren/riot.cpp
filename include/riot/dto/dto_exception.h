#ifndef RIOT_DTO_EXCEPTION_H
#define RIOT_DTO_EXCEPTION_H

#include <stdexcept>
#include <chrono>

namespace riot
{
	/**
	 *	Base exception class for DTO exception types
	 */
	class dto_exception : public std::runtime_error
	{
	public:

		/**
		 *	Possible Exception Types
		 */
		enum type_t
		{
			AUTHORIZATION_EXCEPTION,	// Bad API key or unauthorized action
			RATE_LIMIT_EXCEPTION,		// Rate limit exceeded
			REQUEST_EXCEPTION,		// Bad or missing parameter
			SERVER_EXCEPTION		// Server is fauly or unavailable
		};

		/**
		 *	Construct a DTO exception with the given type and error message
		 * @param type 	Exception Type
		 * @param what 	Human-readable error message
		 */
		dto_exception( type_t type, const char* what );

		/**
		 *	Get the exception type
		 */
		type_t type() const;

	private:

		/// Exception Type
		const type_t m_type;
	};

	/**
	 *	Exception type indicating that the request rate limit was exceeded
	 */
	class dto_rate_exception : dto_exception
	{
	public:

		/**
		 *	Construct a rate exception with the specified wait duration
		 * @param wait_for Duration for which the client must wait before making another request
		 */
		dto_rate_exception( const std::chrono::seconds& wait_for );

		/**
		 *	Get the duration for which the client should wait before making another request
		 * @return 	Wait Duration
		 */
		const std::chrono::seconds& wait_for() const;

	private:

		/// Duration for which to wait before making another request
		std::chrono::seconds m_wait_for;
	};
}

#endif // RIOT_DTO_EXCEPTION_H