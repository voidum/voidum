#include "message.h"

namespace voidum 
{
  Message::Message()
  {
    data_ = nullptr;
    length_ = 0;
  }

  Message::~Message() 
  {
    if (data_ != nullptr)
      delete data_;
  }

  uint32 Message::Length() 
  {
    return length_;
  }

  raw Message::Read(uint32 offset)
  {
    return offset == 0 ? data_ : (raw)((uint64)data_ + offset);
  }

  void Message::Write(raw data, uint32 length, uint32 offset)
  {
    auto ptr = (byte*)((uint64)data_ + offset);
    memcpy(ptr, data, length);
  }
}