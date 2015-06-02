#ifndef _VOIDUM_MESSAGE_
#define _VOIDUM_MESSAGE_

#include "base.h"

namespace voidum
{
  class VOIDUM_API Message
  {
  private:
    raw data_;
    uint32 length_;

  public:
    Message();
    ~Message();

  public:
    uint32 Length();

    raw Read(uint32 offset = 0);

    void Write(raw data, uint32 length, uint32 offset = 0);
  };
}

#endif