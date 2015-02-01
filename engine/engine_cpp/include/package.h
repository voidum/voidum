#ifndef _SPIRITIUM_PACKAGE_
#define _SPIRITIUM_PACKAGE_

#include "base.h"
#include <list>

namespace spiritium
{
	class Driver;
	class Locator;
	class Service;

	//package
	class SPIRITIUM_API Package : Uncopiable
	{
	public:
		//load package
		static Package* Load(const text& target, int host = HOST_LOCAL);

		//find package
		static Package* Find(const text& name);

	protected:
		//package name
		std::string _Name;

		//package services
		std::list<Service*> _Services;

		//locator for package
		Locator* _Locator;

		//driver for package
		Driver* _Driver;

	protected:
		Package();

	public:
		virtual ~Package();

	protected:
		//parse define and update package
		virtual bool Parse(const text& define);

	public:
		//get package name
		const text& GetName();

		//get service by name
		Service* GetService(const text& name);

		//get locator
		Locator* GetLocator();

		//get driver
		Driver* GetDriver();

	public:
		//mount package
		virtual bool Mount() = 0;

		//unmount package
		virtual void Unmount() = 0;
	};
}

#endif