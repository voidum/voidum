#ifndef _SPIRITIUM_THREAD_
#define _SPIRITIUM_THREAD_

#include "base.h"

namespace spiritium
{
	class Task;

	class Thread
	{
	private:
		static uint32 WINAPI Handler(raw sender);

	private:
		HANDLE _Handle;
		uint32 _CPUs;
		Task* _Task;
		bool _IsSuspend;
		bool _IsTemp;

	public:
		Thread();
		~Thread();

	public:
		HANDLE GetHandle();

		Task* GetTask();

		uint32 GetCPUs();

		bool IsSuspend();

		bool IsTemp();

	public:
		void SetTask(Task* task);

		void SetCPUs(uint32 mask);

		void SetTemp(bool value);

	public:
		void Start();

		void Terminate();

		void Suspend();

		bool Resume();
	};
}

#endif