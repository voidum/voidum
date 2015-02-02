#include "locator.h"
#include "driver.h"

namespace voidum
{
	Locator* Locator::Create(const text& target, int host)
	{
		auto driver = Driver::Find(host);
		if (driver == nullptr)
			return nullptr;
		auto locator = driver->CreateLocator();
		locator->_Target = target;
		return locator;
	}

	Locator::Locator() { }

	Locator::~Locator() { }

	const text& Locator::GetTarget()
	{
		return _Target;
	}

	const text& Locator::Request(const text& message)
	{
		message;
		return "";
	}
}