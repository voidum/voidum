#include "package.h"
#include "host.h"
#include "driver.h"
#include "service.h"

namespace voidum
{
	Package::Package()
	{
	}

	Package::~Package()
	{
	}

	bool Package::Parse(const text& meta)
	{
    meta.size();
		return false;
	}

	const text& Package::GetName()
	{
		return name_;
	}

	const text& Package::GetRuntime()
	{
		return runtime_;
	}

	Service* Package::GetService(const text& name)
	{
    return services_->Find(
      [name](Service* service) {
        return service->GetName() == name;
      });
  }

	Service* Package::operator[](const text& name)
	{
		return GetService(name);
	}

	Host* Package::GetHost()
	{
    if (host_ == nullptr)
      host_ = Host::Find(*this);
    return host_;
	}

	Driver* Package::GetDriver()
	{
    if (driver_ == nullptr) {
      auto host = GetHost();
      driver_ = host->GetDriver(runtime_);
    }
    return driver_;
	}
}