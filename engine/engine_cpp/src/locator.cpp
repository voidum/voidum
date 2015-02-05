#include "locator.h"

namespace voidum
{
	Locator::Locator() { }

	Locator::~Locator() { }

	int Locator::GetTarget()
	{
		return _Target;
	}

	void Locator::SetTarget(int target)
	{
		_Target = target;
	}

	const text& Locator::GetSource()
	{
		return _Source;
	}

	void Locator::SetSource(const text& source)
	{
		_Source = source;
	}

	const text& Locator::Request(const text& message)
	{
		message;
		return "";
	}
}