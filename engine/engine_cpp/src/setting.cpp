#include "setting.h"
#include "engine.h"

namespace spiritium
{
	Setting* Setting::Instance()
	{
		auto engine = Engine::Instance();
		return engine->GetSetting();
	}

	Setting::Setting() { }

	Setting::~Setting() { }

	bool Setting::IsSilent()
	{
		return _IsSilent;
	}

	void Setting::IsSilent(bool value)
	{
		_IsSilent = value;
	}

	bool Setting::IsRealTime()
	{
		return _IsRealTime;
	}

	void Setting::IsRealTime(bool value)
	{
		_IsRealTime = value;
	}
}