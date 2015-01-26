#include "text.h"
#include <codecvt>

namespace spiritium
{
	namespace text
	{
		std::wstring U8ToU16(const std::string& text)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> cvt;
			std::wstring output = cvt.from_bytes(text);
			return output;
		}

		std::string U16ToU8(const std::wstring& text)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> cvt;
			std::string output = cvt.to_bytes(text);
			return output;
		}
	}
}
