#include "worker_cq.h"
#include "task.h"
#include "thread.h"

namespace voidum
{
	WorkerCQ::WorkerCQ()
	{
		_LoadFactor = 1;
	}

	WorkerCQ::~WorkerCQ() { }

	Thread* WorkerCQ::GetThread(Task* task)
	{
		using iter = std::list<Thread*>::iterator;
		for (iter i = _Threads.begin(); i != _Threads.end(); i++)
		{
			auto thread = *i;
			if (thread->GetTask() == task)
				return thread;
		}
		return nullptr;
	}

	void WorkerCQ::RemoveThread(Thread* thread)
	{
		using iter = std::list<Thread*>::iterator;
		for (iter i = _Threads.begin(); i != _Threads.end(); i++)
		{
			auto thread_temp = *i;
			if (thread_temp == thread) {
				_Threads.erase(i);
				break;
			}
		}
	}

	Task* WorkerCQ::GetFirstTask()
	{
		Task* task = nullptr;
		_SyncRoot.lock();
		if (_Tasks.size() > 0)
		{
			task = _Tasks.front();
			_Tasks.pop();
		}
		_SyncRoot.unlock();
		return task;
	}

	void WorkerCQ::Start()
	{
		SYSTEM_INFO system;
		GetSystemInfo(&system);
		uint32 cpu_total = system.dwNumberOfProcessors;
		_SyncRoot.lock();
		for (uint32 i = 0; i < _LoadFactor; i++)
		{
			uint32 mask = 0x1;
			for (uint32 j = 0; j < cpu_total; j++)
			{
				mask <<= j;
				auto thread = new Thread();
				thread->SetCPUs(mask);
				thread->Start();
				_Threads.push_back(thread);
			}
		}
		_SyncRoot.unlock();
	}

	void WorkerCQ::Stop()
	{
		using iter = std::list<Thread*>::iterator;
		_SyncRoot.lock();
		for (iter i = _Threads.begin(); i != _Threads.end(); i++)
		{
			auto thread = *i;
			thread->Terminate();
			ClearObject(thread);
		}
		_Threads.empty();
		_SyncRoot.unlock();
	}

	Task* WorkerCQ::CurrentTask()
	{
		using iter = std::list<Thread*>::iterator;
		HANDLE handle = GetCurrentThread();
		std::lock_guard<std::mutex> lock(_SyncRoot);
		for (iter i = _Threads.begin(); i != _Threads.end(); i++)
		{
			auto thread = *i;
			if (thread->GetHandle() == handle)
				return thread->GetTask();
		}
		return nullptr;
	}

	void WorkerCQ::StartTask(Task* task)
	{
		_SyncRoot.lock();
		_Tasks.push(task);
		_SyncRoot.unlock();
	}

	void WorkerCQ::StopTask(Task* task)
	{
		_SyncRoot.lock();
		auto thread = GetThread(task);
		if (thread != nullptr)
		{
			if (!thread->IsTemp())
			{
				auto thread_new = new Thread();
				thread_new->SetCPUs(thread->GetCPUs());
				thread_new->Start();
				_Threads.push_back(thread_new);
			}
			thread->Terminate();
			ClearObject(thread);
			RemoveThread(thread);
		}
		_SyncRoot.unlock();
	}

	void WorkerCQ::PauseTask(Task* task)
	{
		_SyncRoot.lock();
		auto thread = GetThread(task);
		if (thread != nullptr)
		{
			if (!thread->IsTemp())
			{
				auto thread_new = new Thread();
				thread_new->SetCPUs(thread->GetCPUs());
				thread_new->Start();
				_Threads.push_back(thread_new);
			}
			thread->SetTemp(true);
			thread->Suspend();
		}
		_SyncRoot.unlock();
	}

	bool WorkerCQ::ResumeTask(Task* task)
	{
		bool done = false;
		_SyncRoot.lock();
		auto thread = GetThread(task);
		if (thread != nullptr)
			done = thread->Resume();
		_SyncRoot.unlock();
		return done;
	}
}