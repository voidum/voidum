#ifndef _SPIRITIUM_LOCATOR_
#define _SPIRITIUM_LOCATOR_

#include "base.h"

namespace spiritium
{
	class Locator
	{
		friend class Driver;

	public:
		static Locator* Create(const text& target, int host = HOST_LOCAL);

	protected:
		std::string _Target;

	protected:
		Locator();

	public:
		virtual ~Locator();

	public:
		//get target
		const text& GetTarget();

	public:
		//request target with message
		virtual const text& Request(const text& message);
	};
}

#endif