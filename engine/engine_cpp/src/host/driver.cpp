#include "driver.h"
#include "engine.h"
#include "getter.h"

namespace voidum
{
	Driver* Driver::Load(const text& runtime)
	{
    //todo: other OS
    //todo: set path as process path
		text path = "" + runtime; 
		textw path_w = U8ToU16(path);
		HMODULE module = LoadLibraryW(path_w.c_str());
		if (module == nullptr)
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
    auto drivers = Getter::Engine::GetDrivers()();
		return drivers->Find(
      [runtime](Driver* driver) {
        return driver->GetRuntime() == runtime;
      });
	}

	Driver::Driver() { }

	Driver::~Driver() { }

	void Driver::Enable()
	{
    auto drivers = Getter::Engine::GetDrivers()();
    drivers->Add(this);
	}

	void Driver::Disable()
	{
    auto drivers = Getter::Engine::GetDrivers()();
    drivers->Remove(this);
	}
}