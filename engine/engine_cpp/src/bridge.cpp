#include "bridge.h"
#include "engine.h"
#include "locator.h"

namespace voidum
{
	Bridge* Bridge::Find(const text& name)
	{
		auto engine = Engine::Instance();
		return engine->GetBridge(name);
	}

	Bridge::Bridge(const text& name)
	{
		_Name = name;
	}
	
	Bridge::~Bridge() { }

	const text& Bridge::GetName()
	{
		return _Name;
	}

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
		auto engine = Engine::Instance();
		engine->AddBridge(this);
	}

	void Bridge::Disable()
	{
		auto engine = Engine::Instance();
		engine->RemoveBridge(this);
	}
}