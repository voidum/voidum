#ifndef _SPIRITIUM_WORKER_
#define _SPIRITIUM_WORKER_

#include "base.h"

namespace spiritium
{
	class Engine;
	class Thread;
	class Task;

	class Worker : Uncopiable
	{
		friend class Engine;
		friend class Task;

	public:
		static Worker* Instance();

	public:
		Worker();
		virtual ~Worker();

	public:
		//start worker
		virtual void Start() = 0;

		//stop worker
		virtual void Stop() = 0;

	protected:
		//get task at current thread
		virtual Task* GetCurrentTask() = 0;

	protected:
		//start task
		virtual void StartTask(Task* task) = 0;

		//stop task
		virtual void StopTask(Task* task) = 0;

		//pause task
		virtual void PauseTask(Task* task) = 0;

		//resume task
		virtual bool ResumeTask(Task* task) = 0;
	};
}

#endif