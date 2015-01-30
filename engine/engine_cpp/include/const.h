#ifndef _SPIRITIUM_CONST_
#define _SPIRITIUM_CONST_

#include <string>
#include <mutex>

#include "windows.h"

#ifdef SPIRITIUM_EXPORTS
#define SPIRITIUM_API __declspec(dllexport)
#else
#define SPIRITIUM_API
#endif

namespace spiritium
{
	//define type alias
	using raw = void*;
	using byte = unsigned char;

	using int8 = signed char;
	using int16 = short;
	using int32 = int;
	using int64 = long long;
	using uint8 = unsigned char;
	using uint16 = unsigned short;
	using uint32 = unsigned int;
	using uint64 = unsigned long long;
	using real32 = float;
	using real64 = double;

	using text = std::string;
	using textw = std::wstring;

	enum State
	{
		STATE_IDLE = 0,
		STATE_QUEUE = 1,
		STATE_BUSY = 2,
		STATE_ROLLBACK = 3,
		STATE_PAUSE = 4
	}; //context state

	enum ControlCode
	{
		CONTROL_NULL = 0,
		CONTROL_PAUSE = 1,
		CONTROL_RESUME = 2,
		CONTROL_CANCEL = 3
	}; //context control code

	enum ReturnCode
	{
		RETURN_ERROR = 0,
		RETURN_NORMAL = 1,
		RETURN_CANCEL = 2,
		RETURN_TERMINATE = 3,
		RETURN_NULLENTRY = 4,
		RETURN_UNHANDLED = 5
	}; //context return code

	const text VERSION = "0.1.0.20150127";
	const int HOST_LOCAL = 0;
}

#endif