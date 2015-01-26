#include "driver.h"

namespace spiritium
{
	Driver::Driver() { }

	Driver::~Driver() { }

	Driver* Driver::Load(const std::string& runtime)
	{
		std::string path = "" + runtime;
		std::wstring path_w = text::U8ToU16(path);
		HMODULE module = LoadLibraryW(path_w.c_str());
		if (module == null)
			return null;

		typedef Driver* (*Delegate)();
		Delegate d = (Delegate)GetProcAddress(module, "GetDriverInstance");
		if (d == null)
		{
			FreeLibrary(module);
			return null;
		}

		Driver* drv = d();
		return drv;
	}
}