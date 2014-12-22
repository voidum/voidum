#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)

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

	//clear target
	template<typename T>
	void Clear(T& target, bool array = false)
	{
		if (array)
			delete[] target;
		else
			delete target;
		target = null;
	}
}