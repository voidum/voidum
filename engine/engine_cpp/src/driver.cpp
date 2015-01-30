#include "driver.h"
#include "engine.h"
#include "locator.h"

namespace spiritium
{
	Driver* Driver::Load(const text& runtime)
	{
		//todo: get current process directory
		//todo: consider set work directory in setting
		text path = "" + runtime; 
		textw path_w = U8ToU16(path);
		HMODULE module = LoadLibraryW(path_w.c_str());
		if (module != nullptr)
			return nullptr;
		using action = Driver*(*)();
		action handler = (action)GetProcAddress(module, "GetDriverInstance");
		auto driver = (handler == nullptr ? nullptr : handler());
		if (driver == nullptr)
			FreeLibrary(module);
		return driver;
	}

	Driver* Driver::Find(const text& runtime)
	{
		using iter = std::list<Driver*>::iterator;
		auto engine = Engine::Instance();
		auto drivers = engine->_Drivers;
		std::lock_guard<std::mutex> lock(engine->_SyncRoot);
		for (iter i = drivers.begin(); i != drivers.end(); i++)
		{
			auto driver = *i;
			if (driver->GetRuntime() == runtime)
				return driver;
		}
		return nullptr;
	}

	Driver* Driver::Find(int host)
	{
		using iter = std::list<Driver*>::iterator;
		auto engine = Engine::Instance();
		auto drivers = engine->_Drivers;
		std::lock_guard<std::mutex> lock(engine->_SyncRoot);
		for (iter i = drivers.begin(); i != drivers.end(); i++)
		{
			auto driver = *i;
			if (driver->GetHostMode() == host)
				return driver;
		}
		return nullptr;
	}

	int Driver::Count()
	{
		auto engine = Engine::Instance();
		return engine->_Drivers.size();
	}

	void Driver::DisableAll()
	{
		using iter = std::list<Driver*>::iterator;
		auto engine = Engine::Instance();
		auto drivers = engine->_Drivers;
		engine->_SyncRoot.lock();
		for (iter i = drivers.begin(); i != drivers.end(); i++)
			ClearObject(*i);
		drivers.clear();
		engine->_SyncRoot.unlock();
	}

	Driver::Driver() { }

	Driver::~Driver() { }

	void Driver::Enable()
	{
		auto driver = Find(GetRuntime());
		if (driver != nullptr)
		{
			auto engine = Engine::Instance();
			engine->_SyncRoot.lock();
			engine->_Drivers.push_back(this);
			engine->_SyncRoot.unlock();
		}
	}

	void Driver::Disable()
	{
		typedef std::list<Driver*>::iterator iter;
		auto engine = Engine::Instance();
		auto drivers = engine->_Drivers;
		engine->_SyncRoot.lock();
		for (iter i = drivers.begin(); i != drivers.end(); i++)
		{
			auto driver = *i;
			if (driver->GetRuntime() != GetRuntime())
			{
				drivers.erase(i);
				break;
			}
		}
		engine->_SyncRoot.unlock();
	}

	int Driver::GetHostMode()
	{
		return HOST_LOCAL;
	}

	Locator* Driver::CreateLocator()
	{
		return new Locator();
	}
}