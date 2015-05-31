#ifndef _VOIDUM_TEXT_
#define _VOIDUM_TEXT_

#include "const.h"

namespace voidum
{
  //convert utf8 to utf16
  textw U8ToU16(const text& text);

  //convert utf16 to utf8
  text U16ToU8(const textw& text);
}

#endif