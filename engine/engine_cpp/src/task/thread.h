#ifndef _VOIDUM_THREAD_
#define _VOIDUM_THREAD_

#include "base.h"

namespace voidum
{
	class Task;

	class Thread
	{
	private:
		Task* task_;

	public:
		Thread();
		~Thread();

	public:
    //get task on thread
		Task* GetTask();

    //set task on thread
		void SetTask(Task* task);

	public:
    //test if this is current thread
    virtual bool IsCurrent() = 0;

    //start thread
		virtual void Start() = 0;

    //stop thread
    virtual void Stop() = 0;

    //suspend thread
    virtual void Suspend() = 0;

    //resume thread
    virtual void Resume() = 0;
  };
}

#endif