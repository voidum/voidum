#ifndef _VOIDUM_LOCATOR_
#define _VOIDUM_LOCATOR_

#include "base.h"

namespace voidum
{
	class Locator
	{
		friend class Driver;

	public:
		static Locator* Create(const text& target, int host = LOCAL_HOST);

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