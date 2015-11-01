#ifndef RIOT_MATCH_H
#define RIOT_MATCH_H

#include <riot/dto/dto.h>

namespace riot
{
	/**
	 *	Represents a single match in the game
	 */
	class match : public dto_object
	{
	public:

		dto_uint id{ "id" };

	protected:

		/**
		 *	Get child objects
		 */
		virtual std::vector<dto_base*> get_children() override
		{
			return{ &id };
		}
	};
}

#endif // RIOT_MATCH_H
