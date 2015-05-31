#ifndef _VOIDUM_MESSAGE_
#define _VOIDUM_MESSAGE_

#include "base.h"

namespace voidum
{
  class VOIDUM_API Message
  {
  private:
    raw data_;
    uint64 length_;

  public:
    Message();
    ~Message();

  public:
    void Write(raw data, uint64 length, uint64 offset = 0);

    raw Read(uint64 length, uint64 offset = 0);
  };
}

#endif