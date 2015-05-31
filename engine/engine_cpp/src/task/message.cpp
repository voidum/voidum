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
}