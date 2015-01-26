#ifndef _SPIRITIUM_CONST_
#define _SPIRITIUM_CONST_

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

	typedef const std::string& ctext;

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
}

#endif