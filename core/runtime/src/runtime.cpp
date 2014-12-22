#include "runtime.h"
#include "driver_hub.h"

namespace spiritium
{
	std::atomic<Runtime*> Runtime::_Instance{ nullptr };
	std::mutex Runtime::_SyncRoot{};

	Runtime* Runtime::Instance() 
	{
		Runtime* runtime = _Instance;
		if (runtime == nullptr) {
			std::lock_guard<std::mutex> lock(_SyncRoot);
			if ((runtime = _Instance) == nullptr) {
				_Instance = runtime = new Runtime();
			}
		}
		return _Instance;
	}

	Runtime::Runtime()
	{
		_DriverHub = new DriverHub();
	}

	Runtime::~Runtime()
	{
		Clear(_DriverHub);
	}
}