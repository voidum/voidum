#include "driver.h"

namespace spiritium
{
	Driver::Driver() { }

	Driver::~Driver() { }

	Driver* Driver::Load(std::string path)
	{
		std::wstring path_w = text::U8ToU16(path);
		return Load(path_w);
	}

	Driver* Driver::Load(std::wstring path)
	{
		HMODULE module = LoadLibraryW(path.c_str());
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