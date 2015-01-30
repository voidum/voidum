#ifndef _SPIRITIUM_ERROR_
#define _SPIRITIUM_ERROR_

#include "base.h"

namespace spiritium
{
	//service error
	class SPIRITIUM_API Error
	{
	private:
		int _What;

	public:
		Error(int what);
		~Error();

	public:
		int What();

	public:
		static void Throw(int what);
	};
}

#endif