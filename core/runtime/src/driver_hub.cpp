#include "driver_hub.h"

namespace spiritium
{
	DriverHub::DriverHub()
	{
	}

	DriverHub::~DriverHub()
	{
		RemoveAll();
	}

	Driver* DriverHub::Find(std::string runtime)
	{
		typedef std::list<Driver*>::iterator iter;
		std::lock_guard<std::mutex> lock(_SyncRoot);
		for (iter i = _Drivers.begin(); i != _Drivers.end(); i++)
		{
			Driver* temp = *i;
			if (temp->GetRuntimeId() == runtime)
				return temp;
		}
		return null;
	}

	int DriverHub::Count()
	{
		std::lock_guard<std::mutex> lock(_SyncRoot);
		return _Drivers.size();
	}

	void DriverHub::Add(Driver* driver)
	{
		typedef std::list<Driver*>::iterator iter;
		std::lock_guard<std::mutex> lock(_SyncRoot);
		for (iter i = _Drivers.begin(); i != _Drivers.end(); i++)
			if ((*i)->GetRuntimeId() == driver->GetRuntimeId())
				return;
		_Drivers.push_back(driver);
	}

	void DriverHub::Remove(Driver* driver)
	{
		typedef std::list<Driver*>::iterator iter;
		std::lock_guard<std::mutex> lock(_SyncRoot);
		for (iter i = _Drivers.begin(); i != _Drivers.end(); i++)
		{
			Driver* temp = *i;
			if (temp->GetRuntimeId() == driver->GetRuntimeId())
			{
				Clear(temp);
				_Drivers.erase(i);
				return;
			}
		}
	}

	void DriverHub::RemoveAll()
	{
		typedef std::list<Driver*>::iterator iter;
		std::lock_guard<std::mutex> lock(_SyncRoot);
		for (iter i = _Drivers.begin(); i != _Drivers.end(); i++)
			Clear(*i);
		_Drivers.clear();
	}
}