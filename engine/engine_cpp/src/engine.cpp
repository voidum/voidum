#include "engine.h"
#include "driver.h"
#include "package.h"
#include "setting.h"
#include "worker_cq.h"

namespace spiritium
{
	std::atomic<Engine*> Engine::_Instance{ nullptr };

	std::mutex Engine::_CtorRoot{};

	Engine* Engine::Instance()
	{
		Engine* engine = _Instance;
		if (engine == nullptr) {
			std::lock_guard<std::mutex> lock(_CtorRoot);
			if ((engine = _Instance) == nullptr) {
				_Instance = engine = new Engine();
			}
		}
		return _Instance;
	}

	Engine::Engine()
	{
		_Worker = new WorkerCQ();
		_Setting = new Setting();
	}

	Engine::~Engine()
	{
		Driver::DisableAll();
		Package::DetachAll();
		ClearObject(_Worker);
		ClearObject(_Setting);
	}

	const std::string& Engine::GetVersion()
	{
		return VERSION;
	}

	void Engine::Start()
	{
		_Worker->Start();
	}

	void Engine::Stop()
	{
		_Worker->Stop();
	}
}