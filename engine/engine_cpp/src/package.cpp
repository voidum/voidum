#include "package.h"
#include "engine.h"
#include "bridge.h"
#include "driver.h"
#include "locator.h"
#include "service.h"

namespace voidum
{
	Package* Package::Load(Bridge* bridge, const text& source)
	{
		auto driver = bridge->Match(source);
		auto package = driver->CreatePackage();
		auto locator = bridge->GetLocator(TARGET_PACKAGE, source);
		auto define = locator->Request("define");
		if (!package->Parse(define))
			ClearObject(package);
		package->_Bridge = bridge;
		package->_Driver = driver;
		return package;
	}

	Package* Package::Find(const text& name)
	{
		auto engine = Engine::Instance();
		return engine->GetPackage(name);
	}

	Package::Package()
	{
	}

	Package::~Package()
	{
	}

	bool Package::Parse(const text& define)
	{
		define.size();
		return false;
	}

	const text& Package::GetIndex()
	{
		return _Index;
	}

	const text& Package::GetName()
	{
		return _Name;
	}

	const text& Package::GetRuntime()
	{
		return _Runtime;
	}

	Service* Package::GetService(const text& name)
	{
		using iter = std::list<Service*>::iterator;
		for (iter i = _Services.begin(); i != _Services.end(); i++)
		{
			auto service = *i;
			if (service->GetName() == name)
				return service;
		}
		return nullptr;
	}

	Service* Package::operator[](const text& name)
	{
		return GetService(name);
	}

	Bridge* Package::GetBridge()
	{
		return _Bridge;
	}

	Driver* Package::GetDriver()
	{
		return _Driver;
	}
}