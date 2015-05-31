#include "host.h"
#include "engine.h"
#include "getter.h"
#include "package.h"

namespace voidum
{
	Host* Host::Find(const text& name)
	{
		auto hosts = Getter::Engine::GetHosts()();
    return hosts->Find(
      [&name](Host* host) {
        return host->GetName() == name;
      });
	}

  Host* Host::Find(const Package& package) 
  {
    auto hosts = Getter::Engine::GetHosts()();
    return hosts->Find([&package](Host* host) {
      return host->Contains(&package);
    });
  }

  Host::Host(const text& name) 
  {
    packages_ = new List<Package>();
    name_ = name;
  }
  
  Host::~Host() { }

	const text& Host::GetName()
	{
		return name_;
	}

  const text& Host::GetEndPoint()
	{
		return endpoint_;
	}

  bool Host::Contains(const Package* package)
  {
    return packages_->Contains(package);
  }

  Package* Host::GetPackage(const text& name) 
  {
    name.size();
    return nullptr;
  }

  void Host::Enable()
	{
    auto hosts = Getter::Engine::GetHosts()();
    hosts->Add(this);
	}

  void Host::Disable()
	{
    auto hosts = Getter::Engine::GetHosts()();
    hosts->Remove(this);
	}
}