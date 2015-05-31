#include "setting.h"
#include "engine.h"

namespace voidum
{
  Setting* Setting::Instance()
  {
    auto engine = Engine::Instance();
    return engine->GetSetting();
  }

  Setting::Setting() {}

  Setting::~Setting() {}

  bool Setting::IsSilent()
  {
    return is_silient_;
  }

  void Setting::IsSilent(bool value)
  {
    is_silient_ = value;
  }

  bool Setting::IsRealTime()
  {
    return is_realtime_;
  }

  void Setting::IsRealTime(bool value)
  {
    is_realtime_ = value;
  }
}