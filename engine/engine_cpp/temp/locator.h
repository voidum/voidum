#ifndef _VOIDUM_LOCATOR_
#define _VOIDUM_LOCATOR_

#include "base.h"

namespace voidum
{
	class Locator
	{
	protected:
		int _Target;

		std::string _Source;

	protected:
		Locator();

	public:
		virtual ~Locator();

	public:
		//get target
		int GetTarget();

		//set target
		void SetTarget(int target);

	public:
		//get source
		const text& GetSource();

		//set source
		void SetSource(const text& source);

	public:
		//request message
		virtual const text& Request(const text& message) = 0;
	};
}

#endif