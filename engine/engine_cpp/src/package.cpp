#include "package.h"
#include "engine.h"
#include "driver.h"
#include "locator.h"
#include "service.h"

namespace spiritium
{
	Package* Package::Load(const text& target, int host)
	{
		auto locator = Locator::Create(target, host);
		Driver* driver = nullptr;
		if (host == HOST_LOCAL)
		{
			auto runtime = locator->Request("runtime");
			driver = Driver::Find(runtime);
		}
		else
		{
			//driver proxy for special host mode
			driver = Driver::Find(host);
		}
		auto define = locator->Request("define");
		auto package = driver->CreatePackage();
		if (!package->Parse(define))
			ClearObject(package);
		package->_Locator = locator;
		package->_Driver = driver;

		//push??
		return package;
	}

	Package* Package::Find(const text& name)
	{
		using iter = std::list<Package*>::iterator;
		auto engine = Engine::Instance();
		auto packages = engine->_Packages;
		std::lock_guard<std::mutex> lock(engine->_SyncRoot);
		for (iter i = packages.begin(); i != packages.end(); i++)
		{
			auto package = *i;
			if (package->GetName() == name)
				return package;
		}
		return nullptr;
	}

	int Package::Count()
	{
		auto engine = Engine::Instance();
		return engine->_Packages.size();
	}

	void Package::DetachAll()
	{
		using iter = std::list<Package*>::iterator;
		auto engine = Engine::Instance();
		auto packages = engine->_Packages;
		engine->_SyncRoot.lock();
		for (iter i = packages.begin(); i != packages.end(); i++)
			ClearObject(*i);
		packages.clear();
		engine->_SyncRoot.unlock();
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

	const text& Package::GetName()
	{
		return _Name;
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

	Locator* Package::GetLocator()
	{
		return _Locator;
	}

	Driver* Package::GetDriver()
	{
		return _Driver;
	}

	void Package::Attach()
	{
		auto package = Find(_Name);
		if (package != nullptr)
		{
			auto engine = Engine::Instance();
			auto packages = engine->_Packages;
			engine->_SyncRoot.lock();
			packages.push_back(this);
			engine->_SyncRoot.unlock();
		}
	}

	void Package::Detach()
	{
		using iter = std::list<Package*>::iterator;
		auto engine = Engine::Instance();
		auto packages = engine->_Packages;
		engine->_SyncRoot.lock();
		for (iter i = packages.begin(); i != packages.end(); i++)
		{
			auto package = *i;
			if (package->GetName() == _Name)
			{
				packages.erase(i);
				break;
			}
		}
		engine->_SyncRoot.unlock();
	}
}