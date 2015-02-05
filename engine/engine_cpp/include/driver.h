#ifndef _VOIDUM_DRIVER_
#define _VOIDUM_DRIVER_

#include "base.h"

namespace voidum
{
	class Package;
	class Task;

	//driver {base}
	class VOIDUM_API Driver
	{
	public:
		//load driver
		static Driver* Load(const text& runtime);

	public:
		//find driver by runtime
		static Driver* Find(const text& runtime);

	public:
		Driver();
		virtual ~Driver();

	public:
		//get runtime
		virtual const text& GetRuntime() = 0;

	public:
		//create package
		virtual Package* CreatePackage() = 0;

		//create task
		virtual Task* CreateTask() = 0;

	public:
		//enable driver
		void Enable();

		//disable driver
		void Disable();
	};
}

#endif