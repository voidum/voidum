#ifndef _SPIRITIUM_PACKAGE_
#define _SPIRITIUM_PACKAGE_

#include "base.h"
#include <list>

namespace spiritium
{
	class Locator;
	class Service;

#ifndef _SPIRITIUM_TRAITS_DRIVER_
	class Driver;
#endif;

	//package
	class SPIRITIUM_API Package : Uncopiable
	{
	public:
		//load package
		static Package* Load(const Locator& locator);

	protected:
		//package name
		std::string _Name;

		//package runtime
		std::string _Runtime;

		//package locator
		std::string _Locator;

		//services
		std::list<Service*> _Services;

		//driver
		Driver* _Driver;

	protected:
		Package();

	public:
		virtual ~Package();

	public:
		//get package name
		ctext GetName();

		//get package runtime
		ctext GetRuntime();

		//get package locator
		std::string GetLocator();

		//get service by id
		Service* GetService(ctext id);

		//get driver
		Driver* GetDriver();

	protected:
		//parse meta and update package
		virtual void Parse(ctext meta) = 0;

	public:
		//mount package
		virtual bool Mount() = 0;

		//unmount package
		virtual void Unmount() = 0;
	};
}

#endif