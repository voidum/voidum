#include "bridge_local.h"

namespace voidum
{
	int LocalBridge::GetHostMode()
	{
		return HOST_LOCAL;
	}

	Locator* LocalBridge::CreateLocator()
	{
		return nullptr;
	}

	bool LocalBridge::Connect(const text& endpoint)
	{
		_EndPoint = endpoint;
		return true;
	}

	Driver* LocalBridge::Match(const text& target)
	{
		target.size();
		//request meta
		//get runtime
		//get driver
		return nullptr;
	}
}