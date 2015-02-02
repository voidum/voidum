#include "engine.h"
#include "driver.h"
#include "package.h"
#include "setting.h"
#include "worker_cq.h"

namespace voidum
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
		RemoveAllDrivers(true);
		RemoveAllPackages(true);
		ClearObject(_Worker);
		ClearObject(_Setting);
	}

	const std::string& Engine::GetVersion()
	{
		return VERSION;
	}

	Setting* Engine::GetSetting()
	{
		return _Setting;
	}

	Worker* Engine::GetWorker()
	{
		return _Worker;
	}

	void Engine::SetWorker(Worker* worker)
	{
		_Worker = worker;
	}

	Driver* Engine::GetDriver(const text& runtime)
	{
		using iter = std::list<Driver*>::iterator;
		std::lock_guard<std::mutex> lock(_SyncRoot);
		for (iter i = _Drivers.begin(); i != _Drivers.end(); i++) {
			auto temp = *i;
			if (temp->GetRuntime() == runtime)
				return temp;
		}
		return nullptr;
	}

	Driver* Engine::GetDriver(int host)
	{
		using iter = std::list<Driver*>::iterator;
		std::lock_guard<std::mutex> lock(_SyncRoot);
		for (iter i = _Drivers.begin(); i != _Drivers.end(); i++) {
			auto temp = *i;
			if (temp->GetHostMode() == host)
				return temp;
		}
		return nullptr;
	}

	void Engine::AddDriver(Driver* driver)
	{
		using iter = std::list<Driver*>::iterator;
		std::lock_guard<std::mutex> lock(_SyncRoot);
		for (iter i = _Drivers.begin(); i != _Drivers.end(); i++) {
			auto temp = *i;
			if (temp == driver ||
				temp->GetRuntime() == driver->GetRuntime())
				return;
		}
		_Drivers.push_back(driver);
	}

	void Engine::RemoveDriver(Driver* driver, bool clear)
	{
		using iter = std::list<Driver*>::iterator;
		_SyncRoot.lock();
		for (iter i = _Drivers.begin(); i != _Drivers.end(); i++) {
			auto temp = *i;
			if (temp == driver ||
				temp->GetRuntime() == driver->GetRuntime()) {
				if (clear)
					ClearObject(temp);
				_Drivers.erase(i);
				break;
			}
		}
		_SyncRoot.unlock();
	}

	void Engine::RemoveAllDrivers(bool clear)
	{
		using iter = std::list<Driver*>::iterator;
		_SyncRoot.lock();
		if (clear) {
			for (iter i = _Drivers.begin(); i != _Drivers.end(); i++)
				ClearObject(*i);
		}
		_Drivers.clear();
		_SyncRoot.unlock();
	}

	Package* Engine::GetPackage(const text& name)
	{
		using iter = std::list<Package*>::iterator;
		std::lock_guard<std::mutex> lock(_SyncRoot);
		for (iter i = _Packages.begin(); i != _Packages.end(); i++)
		{
			auto temp = *i;
			if (temp->GetName() == name)
				return temp;
		}
		return nullptr;
	}

	void Engine::AddPackage(Package* package)
	{
		using iter = std::list<Package*>::iterator;
		std::lock_guard<std::mutex> lock(_SyncRoot);
		for (iter i = _Packages.begin(); i != _Packages.end(); i++) {
			auto temp = *i;
			if (temp == package ||
				temp->GetName() == package->GetName())
				return;
		}
		_Packages.push_back(package);
	}

	void Engine::RemovePackage(Package* package, bool clear)
	{
		using iter = std::list<Package*>::iterator;
		_SyncRoot.lock();
		for (iter i = _Packages.begin(); i != _Packages.end(); i++) {
			auto temp = *i;
			if (temp == package ||
				temp->GetName() == package->GetName()) {
				if (clear)
					ClearObject(temp);
				_Packages.erase(i);
				break;
			}
		}
		_SyncRoot.unlock();
	}

	void Engine::RemoveAllPackages(bool clear)
	{
		using iter = std::list<Package*>::iterator;
		_SyncRoot.lock();
		if (clear) {
			for (iter i = _Packages.begin(); i != _Packages.end(); i++)
				ClearObject(*i);
		}
		_Packages.clear();
		_SyncRoot.unlock();
	}

	void Engine::Start()
	{
		if (_Worker != nullptr)
			_Worker->Start();
	}

	void Engine::Stop()
	{
		if (_Worker != nullptr)
			_Worker->Stop();
	}
}