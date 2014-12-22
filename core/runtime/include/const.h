#pragma once

#include <string>
#include <atomic>
#include <mutex>
#include "windows.h"

#ifdef SPIRITIUM_EXPORTS
#define SPIRITIUM_API __declspec(dllexport)
#else
#define SPIRITIUM_API
#endif

namespace spiritium
{
	//define null
	#define null 0

	//define type alias
	typedef void* raw;
	typedef unsigned char byte;

	typedef signed char int8;
	typedef short int16;
	typedef int int32;
	typedef long long int64;
	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;
	typedef unsigned long long uint64;
	typedef float real32;
	typedef double real64;

	enum State
	{
		SF_STATE_IDLE = 0,
		SF_STATE_QUEUE = 1,
		SF_STATE_BUSY = 2,
		SF_STATE_ROLLBACK = 3,
		SF_STATE_PAUSE = 4
	}; //context state

	enum ControlCode
	{
		SF_CTRL_NULL = 0,
		SF_CTRL_PAUSE = 1,
		SF_CTRL_RESUME = 2,
		SF_CTRL_CANCEL = 3
	}; //context control code

	enum ReturnCode
	{
		SF_RETURN_ERROR = 0,
		SF_RETURN_NORMAL = 1,
		SF_RETURN_CANCEL = 2,
		SF_RETURN_TERMINATE = 3,
		SF_RETURN_NULLENTRY = 4,
		SF_RETURN_UNHANDLED = 5
	}; //context return code
}