#ifndef _SPIRITIUM_ENGINE_
#define _SPIRITIUM_ENGINE_

#include "base.h"
#include <atomic>
#include <list>

namespace spiritium
{
	class Driver;
	class Package;
	class Setting;
	class Worker;

	//engine
	class SPIRITIUM_API Engine : Uncopiable
	{
		friend class Driver;
		friend class Package;
		friend class Setting;
		friend class Worker;

	private:
		static std::atomic<Engine*> _Instance;
		static std::mutex _CtorRoot;

	public:
		static Engine* Instance();

	private:
		std::mutex _SyncRoot;
		std::list<Driver*> _Drivers;
		std::list<Package*> _Packages;
		Worker* _Worker;
		Setting* _Setting;

	private:
		Engine();

	public:
		~Engine();

	public:
		//get spiritium version
		const std::string& GetVersion();

	public:
		//start engine
		void Start();

		//stop engine
		void Stop();
	};
}

#endif