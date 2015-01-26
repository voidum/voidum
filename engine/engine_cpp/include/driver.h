#ifndef _SPIRITIUM_DRIVER_
#define _SPIRITIUM_DRIVER_
#define _SPIRITIUM_TRAITS_DRIVER_

#include "base.h"

namespace spiritium
{
	class Bridge;

#ifndef _SPIRITIUM_TRAITS_PACKAGE_
	class Package;
#endif

#ifndef _SPIRITIUM_TRAITS_TASK_
	class Task;
#endif

	//driver {base}
	class SPIRITIUM_API Driver
	{
	public:
		Driver();
		virtual ~Driver();

	public:
		//load driver
		static Driver* Load(const std::string& runtime);

	public:
		//get runtime
		virtual const std::string& GetRuntime() = 0;

	public:
		//create bridge
		virtual Bridge* CreateBridge() = 0;

		//create package
		virtual Package* CreatePackage() = 0;

		//create task
		virtual Task* CreateTask() = 0;
	};
}

#endif