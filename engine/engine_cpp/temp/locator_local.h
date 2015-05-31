#ifndef _VOIDUM_LOCATOR_LOCAL_
#define _VOIDUM_LOCATOR_LOCAL_

#include "locator.h"

namespace voidum
{
	class VOIDUM_API LocalLocator : public Locator
	{
	public:
		virtual const text& Request(const text& message);
	};
}

#endif