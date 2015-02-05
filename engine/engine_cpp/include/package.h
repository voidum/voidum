#ifndef _VOIDUM_PACKAGE_
#define _VOIDUM_PACKAGE_

#include "base.h"
#include <list>

namespace voidum
{
	class Bridge;
	class Driver;
	class Service;

	//package
	class VOIDUM_API Package : Uncopiable
	{
	public:
		//load package
		static Package* Load(Bridge* bridge, const text& target);

		//find package
		static Package* Find(const text& name);

	protected:
		//package index
		text _Index;

		//package name
		text _Name;

		//package runtime
		text _Runtime;

		//package services
		std::list<Service*> _Services;

		//package host mode
		int _Host;

	protected:
		Package();

	public:
		virtual ~Package();

	protected:
		//parse define and update package
		virtual bool Parse(const text& define);

	public:
		//get package index
		const text& GetIndex();

		//get package name
		const text& GetName();

		//get package runtime
		const text& GetRuntime();

		//get service by name
		Service* GetService(const text& name);

		//get host mode
		int GetHostMode();

	public:
		//mount package
		virtual bool Mount() = 0;

		//unmount package
		virtual void Unmount() = 0;
	};
}

#endif