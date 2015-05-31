#ifndef _VOIDUM_SETTING_
#define _VOIDUM_SETTING_

#include "base.h"

namespace voidum
{
  //engine setting
  class VOIDUM_API Setting
  {
  public:
    static Setting* Instance();

  private:
    bool is_silient_;
    bool is_realtime_;

  public:
    Setting();
    ~Setting();

  public:
    bool IsSilent();
    void IsSilent(bool value);

  public:
    bool IsRealTime();
    void IsRealTime(bool value);
  };
}

#endif