#include "bridge.h"
#include "engine.h"
#include "locator.h"

namespace voidum
{
	Bridge* Bridge::Find(int host)
	{
		auto engine = Engine::Instance();
		return engine->GetBridge(host);
	}

	Bridge::Bridge() { }
	
	Bridge::~Bridge() { }

	const text& Bridge::GetEndPoint()
	{
		return _EndPoint;
	}

	Locator* Bridge::GetLocator(int target, const text& source)
	{
		auto locator = CreateLocator();
		locator->SetTarget(target);
		locator->SetSource(source);
		return locator;
	}

	void Bridge::Enable()
	{
		//add bridge into engine
	}

	void Bridge::Disable()
	{
		//remove bridge from engine
	}
}