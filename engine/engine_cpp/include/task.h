#ifndef _SPIRITIUM_TASK_
#define _SPIRITIUM_TASK_

#include "base.h"

namespace spiritium
{
	class SPIRITIUM_API Task
	{
	private:
		int _Index;

	public:
		const int& GetIndex();
	};
}

#endif