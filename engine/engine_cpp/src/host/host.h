#ifndef _VOIDUM_HOST_
#define _VOIDUM_HOST_

#include "base.h"
#include "list.h"

namespace voidum
{
  class Driver;
  class Package;
  class Task;

  class VOIDUM_API Host
  {
  public:
    //find host by name
    static Host* Find(const text& name);

    //find host for package
    static Host* Find(const Package& package);

  protected:
    text name_;
    text endpoint_;
    List<Package>* packages_;

  public:
    Host(const text& name);
    virtual ~Host();

  public:
    //get alias name
    const text& GetName();

    //get end point
    const text& GetEndPoint();

  public:
    //test if host has package
    bool Contains(const Package* package);

    //get package by name
    //try to load if found nothing
    Package* GetPackage(const text& name);

  public:
    //get driver
    //todo: consider rename GetDriver
    virtual Driver* GetDriver(const text& runtime) = 0;

    //connect to endpoint
    virtual bool Connect(const text& endpoint) = 0;

    //request source
    virtual const text& Request(const text& source) = 0;

  public:
    //enable host
    void Enable();

    //disable host
    void Disable();
  };
}

#endif