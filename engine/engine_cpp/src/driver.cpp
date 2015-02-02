#include "driver.h"
#include "engine.h"
#include "locator.h"

namespace voidum
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
		auto engine = Engine::Instance();
		return engine->GetDriver(runtime);
	}

	Driver* Driver::Find(int host)
	{
		auto engine = Engine::Instance();
		return engine->GetDriver(host);
	}

	Driver::Driver() { }

	Driver::~Driver() { }

	int Driver::GetHostMode()
	{
		return HOST_LOCAL;
	}

	Locator* Driver::CreateLocator()
	{
		return new Locator();
	}

	void Driver::Enable()
	{
		auto engine = Engine::Instance();
		engine->AddDriver(this);
	}

	void Driver::Disable()
	{
		auto engine = Engine::Instance();
		engine->RemoveDriver(this);
	}
}