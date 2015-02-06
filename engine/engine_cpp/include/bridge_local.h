#ifndef _VOIDUM_BRIDGE_LOCAL_
#define _VOIDUM_BRIDGE_LOCAL_

#include "bridge.h"

namespace voidum
{
	class VOIDUM_API LocalBridge : public Bridge
	{
	public:
		LocalBridge(const text& name);
		~LocalBridge();

	public:
		virtual int GetHostMode();
		virtual Locator* CreateLocator();

	public:
		virtual bool Connect(const text& endpoint);
		virtual Driver* Match(const text& target);
	};
}

#endif