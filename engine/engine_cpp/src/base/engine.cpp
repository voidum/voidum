#include "engine.h"
#include "host.h"
#include "driver.h"
#include "setting.h"
#include "worker_cq.h"

namespace voidum
{
  Engine* Engine::instance_ = nullptr;
  std::once_flag* Engine::once_flag_ = new std::once_flag();

  Engine* Engine::Instance()
  {
    std::call_once(*once_flag_, []() {
      if (instance_ == nullptr)
        instance_ = new Engine();
    });
    return instance_;
  }

	Engine::Engine()
	{
    hosts_ = new List<Host>();
    drivers_ = new List<Driver>();
		worker_ = new WorkerCQ();
		setting_ = new Setting();
	}

	Engine::~Engine()
	{
    delete hosts_;
		delete drivers_;
		delete worker_;
		delete setting_;
	}

	Setting* Engine::GetSetting()
	{
		return setting_;
	}

	Worker* Engine::GetWorker()
	{
		return worker_;
	}

	void Engine::SetWorker(Worker* worker)
	{
		if (worker == nullptr)
			return;
    if (worker_ != nullptr) {
      worker_->Stop();
      delete worker_;
    }
		worker_ = worker;
	}

  void Engine::Start()
  {
    if (instance_->worker_ != nullptr)
      instance_->worker_->Start();
  }

  void Engine::Stop()
  {
    if (instance_->worker_ != nullptr)
      instance_->worker_->Stop();
  }
}