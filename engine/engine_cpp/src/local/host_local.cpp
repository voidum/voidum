#include "host_local.h"

namespace voidum
{
  LocalHost::LocalHost(const text& name)
		: Host(name)
	{
	}

  LocalHost::~LocalHost()
	{
	}

  bool LocalHost::Connect(const text& endpoint)
	{
		endpoint_ = endpoint;
		return true;
	}
}