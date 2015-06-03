#ifndef _VOIDUM_TASK_
#define _VOIDUM_TASK_

#include "base.h"

namespace voidum
{
  class Context;
  class Memory;
	class Service;

	class VOIDUM_API Task
	{
		friend class Worker;

	public:
		//create task for service
		static Task* Create(Service* service);

		//get task at current thread
		static Task* Current();

	protected:
		text index_;
    bool protect_;
    Service* service_;
    Memory* memory_;

	protected:
		Task();

	public:
		virtual ~Task();

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
		//get memory of task
		Memory* GetMemory();

    //get context of task
    Context* GetContext();

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

    void TryHold();
	};
}

#endif