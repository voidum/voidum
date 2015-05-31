#include "getter.h"
#include "engine.h"

namespace voidum 
{
  List<Host>* Getter::Engine::GetHosts::operator()() 
  {
    auto engine = voidum::Engine::Instance();
    return engine->hosts_;
  }

  List<Driver>* Getter::Engine::GetDrivers::operator()() 
  {
    auto engine = voidum::Engine::Instance();
    return engine->drivers_;
  }
}