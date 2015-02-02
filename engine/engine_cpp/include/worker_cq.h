#ifndef _VOIDUM_WORKER_CQ_
#define _VOIDUM_WORKER_CQ_

#include "worker.h"
#include <list>
#include <queue>

namespace voidum
{
	//concurrent queue worker
	class WorkerCQ : public Worker
	{
		friend class Thread;

	public:
		static WorkerCQ* Instance();

	public:
		WorkerCQ();

	public:
		virtual ~WorkerCQ();

	private:
		std::mutex _SyncRoot;
		std::list<Thread*> _Threads;
		std::queue<Task*> _Tasks;
		uint32 _LoadFactor;

	private:
		//get thread by task
		Thread* GetThread(Task* task);

		//remove thread
		void RemoveThread(Thread* thread);

		//get first task
		Task* GetFirstTask();

	public:
		//start worker
		virtual void Start();

		//stop worker
		virtual void Stop();

	protected:
		//get task at current thread
		virtual Task* GetCurrentTask();

	protected:
		//start task
		virtual void StartTask(Task* task);

		//stop task
		virtual void StopTask(Task* task);

		//pause task
		virtual void PauseTask(Task* task);

		//resume task
		virtual bool ResumeTask(Task* task);
	};
}

#endif