#include "bridge_local.h"
#include "locator_local.h"

namespace voidum
{
	LocalBridge::LocalBridge(const text& name)
		: Bridge(name)
	{
	}

	LocalBridge::~LocalBridge()
	{
	}

	int LocalBridge::GetHostMode()
	{
		return HOST_LOCAL;
	}

	Locator* LocalBridge::CreateLocator()
	{
		return new LocalLocator();
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