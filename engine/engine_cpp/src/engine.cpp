#include "engine.h"

namespace spiritium
{
	std::atomic<Engine*> Engine::_Instance{ nullptr };
	std::mutex Engine::_SyncRoot{};

	Engine* Engine::Instance()
	{
		Engine* engine = _Instance;
		if (engine == nullptr) {
			std::lock_guard<std::mutex> lock(_SyncRoot);
			if ((engine = _Instance) == nullptr) {
				_Instance = engine = new Engine();
			}
		}
		return _Instance;
	}

	Engine::Engine()
	{
		_Drivers = new List<Driver>();
		_Packages = new List<Package>();
		_Tasks = new List<Task>();
	}

	Engine::~Engine()
	{
		Clear(_Drivers);
	}
}