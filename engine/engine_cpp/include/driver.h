#ifndef _SPIRITIUM_DRIVER_
#define _SPIRITIUM_DRIVER_

#include "base.h"

namespace spiritium
{
	class Locator;
	class Package;
	class Task;

	//driver {base}
	class SPIRITIUM_API Driver
	{
	public:
		//load driver
		static Driver* Load(const text& runtime);

	public:
		//find driver by runtime
		static Driver* Find(const text& runtime);

		//find driver by host mode
		static Driver* Find(int host);

		//count drivers
		static int Count();

		//disable all drivers
		static void DisableAll();

	public:
		Driver();
		virtual ~Driver();

	public:
		//enable driver
		void Enable();

		//disable driver
		void Disable();

	public:
		//get host mode
		virtual int GetHostMode();

		//create locator
		virtual Locator* CreateLocator();

	public:
		//get runtime
		virtual const text& GetRuntime() = 0;

		//create package
		virtual Package* CreatePackage() = 0;

		//create task
		virtual Task* CreateTask() = 0;
	};
}

#endif