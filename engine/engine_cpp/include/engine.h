#ifndef _SPIRITIUM_ENGINE_
#define _SPIRITIUM_ENGINE_

#include "base.h"
#include "list.h"

namespace spiritium
{
	class Driver;
	class Package;
	class Task;
	class Worker;

	//engine
	class SPIRITIUM_API Engine : Uncopiable
	{
	private:
		Engine();
	public:
		~Engine();

	private:
		static std::atomic<Engine*> _Instance;
		static std::mutex _SyncRoot;

	public:
		static Engine* Instance();

	private:
		List<Driver>* _Drivers;
		List<Package>* _Packages;
		List<Task>* _Tasks;
		Worker* _Worker;

	public:
		//get spiritium version
		const std::string& GetVersion();

	public:
		//online engine
		void Online();

		//offline engine
		void Offline();

		//enable/disable driver
		void Drive(Driver* driver, bool enable = true);

		//get driver by runtime
		Driver* GetDriver(const std::string& runtime);

		//get package by name
		Package* GetPackage(const std::string& name);

	public:
		//get worker
		Worker* GetWorker();

		//set worker
		void SetWorker(Worker* worker);
	};
}

#endif