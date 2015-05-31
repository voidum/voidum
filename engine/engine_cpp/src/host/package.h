#ifndef _VOIDUM_PACKAGE_
#define _VOIDUM_PACKAGE_

#include "base.h"
#include "list.h"

namespace voidum
{
  class Host;
  class Driver;
  class Service;

	//package
	class VOIDUM_API Package : Uncopiable
	{
	protected:
		text name_;
		text runtime_;
		List<Service>* services_;

    Host* host_;
    Driver* driver_;

	protected:
		Package();

	public:
		virtual ~Package();

  public:
    bool Parse(const text& meta);

  public:
		//get package name
		const text& GetName();

		//get package runtime
		const text& GetRuntime();

	public:
		//get service by name
		Service* GetService(const text& name);

		//get service by name
		Service* operator [] (const text& name);

  public:
    //get host
    Host* GetHost();

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