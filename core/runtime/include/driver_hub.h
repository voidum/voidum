#pragma once

#include "driver.h"
#include <list>

namespace spiritium
{
	class SPIRITIUM_API DriverHub
	{
	private:
		std::mutex _SyncRoot;
		std::list<Driver*> _Drivers;

	public:
		DriverHub();
		~DriverHub();

	public:
		Driver* Find(std::string runtime);
		int Count();

	public:
		void Add(Driver* driver);
		void Remove(Driver* driver);
		void RemoveAll();
	};
}