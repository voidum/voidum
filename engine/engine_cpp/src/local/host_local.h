#ifndef _VOIDUM_HOST_LOCAL_
#define _VOIDUM_HOST_LOCAL_

#include "host.h"

namespace voidum
{
	class VOIDUM_API LocalHost : public Host
	{
	public:
		LocalHost(const text& name);
		~LocalHost();

	public:
		virtual bool Connect(const text& endpoint);
	};
}

#endif