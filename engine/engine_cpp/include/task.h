#ifndef _VOIDUM_TASK_
#define _VOIDUM_TASK_

#include "base.h"

namespace voidum
{
	class Bridge;
	class Memory;
	class Service;

	class VOIDUM_API Task
	{
		friend class Worker;
		friend class Thread;

	public:
		//get task at current thread
		static Task* Current();

	protected:
		text _Index;
		Memory* _Memory;
		bool _HasProtect;
		Service* _Service;

	protected:
		Task();

	public:
		virtual ~Task();

	public:
		//bind task with service
		virtual bool Bind(Service* service);

	protected:
		//invoke task
		void Invoke();

		//invoke custom process
		virtual void OnProcess() = 0;

		//invoke custom rollback
		virtual void OnRollback() = 0;

		//invoke custom process safely
		void OnSafeProcess();

		//invoke custom process safely
		void OnSafeRollback();

	public:
		//get memory for task
		Memory* GetMemory();

	public:
		//start
		void Start();

		//stop
		void Stop(uint32 wait = 0);

		//pause
		void Pause(uint32 wait = 0);

		//resume
		void Resume();

	public:
		//wait for task return
		void Join();

		//sync memory
		void Sync();
	};
}

#endif