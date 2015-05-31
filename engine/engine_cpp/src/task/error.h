#ifndef _VOIDUM_ERROR_
#define _VOIDUM_ERROR_

#include "base.h"

namespace voidum
{
	//service error
	class VOIDUM_API Error
	{
	public:
		static void Throw(int what);

	private:
		int _What;

	public:
		Error(int what);
		~Error();

	public:
		int What();
	};
}

#endif