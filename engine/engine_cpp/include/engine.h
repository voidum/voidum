#ifndef _VOIDUM_ENGINE_
#define _VOIDUM_ENGINE_

#include "base.h"
#include <atomic>
#include <list>

namespace voidum
{
	class Bridge;
	class Driver;
	class Package;
	class Setting;
	class Worker;

	//engine
	class VOIDUM_API Engine : Uncopiable
	{
	private:
		static std::atomic<Engine*> _Instance;
		static std::mutex _CtorRoot;

	public:
		static Engine* Instance();

	private:
		std::mutex _SyncRoot;

	private:
		std::list<Bridge*> _Bridges;
		std::list<Driver*> _Drivers;
		std::list<Package*> _Packages;
		Worker* _Worker;
		Setting* _Setting;

	private:
		Engine();

	public:
		~Engine();

	public:
		//get version
		const std::string& GetVersion();

	public:
		//get setting
		Setting* GetSetting();

	public:
		//get worker
		Worker* GetWorker();

		//set worker
		void SetWorker(Worker* worker);

	public:
		//get bridge by name
		Bridge* GetBridge(const text& name);

		//add bridge
		void AddBridge(Bridge* bridge);

		//remove bridge
		void RemoveBridge(Bridge* bridge, bool clear = false);

		//remove all bridges
		void RemoveAllBridges(bool clear = false);

	public:
		//get driver by runtime
		Driver* GetDriver(const text& runtime);

		//add driver
		void AddDriver(Driver* driver);

		//remove driver
		void RemoveDriver(Driver* driver, bool clear = false);

		//remove all drivers
		void RemoveAllDrivers(bool clear = false);

	public:
		//get package by name
		Package* GetPackage(const text& name);

		//add package
		void AddPackage(Package* package);

		//remove package
		void RemovePackage(Package* package, bool clear = false);

		//remove all packages
		void RemoveAllPackages(bool clear = false);

	public:
		//start engine
		void Start();

		//stop engine
		void Stop();
	};
}

#endif