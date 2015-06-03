#include "thread.h"
#include "task.h"

namespace voidum
{
	Thread::Thread()
	{
		task_ = nullptr;
	}

	Thread::~Thread()
	{
	}

	Task* Thread::GetTask()
	{
		return task_;
	}

	void Thread::SetTask(Task* task)
	{
    task_ = task;
	}
}