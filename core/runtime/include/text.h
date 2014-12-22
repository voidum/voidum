#pragma once

#include "const.h"

namespace spiritium
{
	namespace text
	{
		//convert utf8 to utf16
		std::wstring U8ToU16(std::string text);

		//convert utf16 to utf8
		std::string U16ToU8(std::wstring text);
	}
}