#ifndef _SPIRITIUM_TEXT_
#define _SPIRITIUM_TEXT_

#include "const.h"

namespace spiritium
{
	namespace text
	{
		//convert utf8 to utf16
		std::wstring U8ToU16(const std::string& text);

		//convert utf16 to utf8
		std::string U16ToU8(const std::wstring& text);
	}
}

#endif