#include "thread.h"
#include "task.h"
#include "worker_cq.h"
#include <process.h>

namespace voidum
{
	uint32 Thread::Handler(raw sender)
	{
		Thread* thread = (Thread*)sender;
		for (;;)
		{
			if (thread->_Task == nullptr)
			{
				if (thread->_IsTemp)
					break;
				auto worker = dynamic_cast<WorkerCQ*>(
					Worker::Instance());
				auto task = worker->GetFirstTask();
				if (task != nullptr)
					thread->_Task = task;
				else
				{
					//todo: get monitor freq
					Sleep(25);
				}
				continue;
			}
			thread->_Task->Invoke();
			thread->_Task = nullptr;
		}
		return 0;
	}

	Thread::Thread()
	{
		_Handle = nullptr;
		_IsSuspend = false;
		_IsTemp = false;
		_Task = nullptr;
		_CPUs = 0;
	}

	Thread::~Thread()
	{
	}

	HANDLE Thread::GetHandle()
	{
		return _Handle;
	}

	Task* Thread::GetTask()
	{
		return _Task;
	}

	uint32 Thread::GetCPUs()
	{
		return _CPUs;
	}

	bool Thread::IsSuspend()
	{
		return _IsSuspend;
	}

	bool Thread::IsTemp()
	{
		return _IsTemp;
	}

	void Thread::SetTask(Task* task)
	{
		_Task = task;
	}

	void Thread::SetCPUs(uint32 mask)
	{
		_CPUs = mask;
		if (_Handle != nullptr)
			SetThreadAffinityMask(_Handle, _CPUs);
	}

	void Thread::SetTemp(bool value)
	{
		_IsTemp = value;
	}

	void Thread::Start()
	{
		if (_Handle == nullptr)
		{
			_Handle = (HANDLE)_beginthreadex(
				nullptr, 0, Thread::Handler, this, 0, 0);
			SetCPUs(_CPUs);
		}
	}

	void Thread::Terminate()
	{
		if (TerminateThread(_Handle, 0) != 0)
		{
			WaitForSingleObject(_Handle, INFINITE);
			CloseHandle(_Handle);
		}
	}

	void Thread::Suspend()
	{
		SuspendThread(_Handle);
		_IsSuspend = true;
	}

	bool Thread::Resume()
	{
		if (_IsSuspend)
		{
			ResumeThread(_Handle);
			_IsSuspend = false;
			return true;
		}
		return false;
	}
}