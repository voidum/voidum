#ifndef _SPIRITIUM_BASE_
#define _SPIRITIUM_BASE_

#pragma warning(disable:4172)
#pragma warning(disable:4251)
#pragma warning(disable:4275)

#include "const.h"
#include "text.h"

namespace spiritium
{
	//restrict copy
	class Uncopiable
	{
	protected:
		Uncopiable();
		~Uncopiable();

	private:
		Uncopiable(const Uncopiable&);
		Uncopiable& operator=(const Uncopiable&);
	};

	//clear object
	template<typename T>
	void ClearObject(T& target)
	{
		delete target;
		target = nullptr;
	}

	//clear array
	template<typename T>
	void ClearArray(T& target)
	{
		delete[] target;
		target = nullptr;
	}
}

#endif