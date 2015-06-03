#include "task.h"
#include "memory.h"
#include "context.h"
#include "error.h"
#include "host.h"
#include "driver.h"
#include "package.h"
#include "service.h"
#include "setting.h"
#include "worker.h"

#include <windows.h>

namespace voidum
{
	Task* Task::Create(Service* service)
	{
		auto package = service->GetPackage();
    auto driver = package->GetDriver();
		auto task = driver->CreateTask();
    task->service_ = service;
    return task;
	}

	Task* Task::Current()
	{
		auto worker = Worker::Instance();
		return worker->GetCurrentTask();
	}

	Task::Task()
	{
		memory_ = new Memory();
	}

	Task::~Task()
	{
		delete memory_;
	}

	void Task::Invoke()
	{
    auto context = memory_->GetContext();
		try {
			context->SetControlCode(CONTROL_NULL);
      context->SetReturnCode(RETURN_NULLENTRY);
      context->SetState(STATE_BUSY);
			if (protect_)
				OnSafeProcess();
			else
				OnProcess();
      context->SetReturnCode(RETURN_NORMAL);
		}
		catch (Error*) {
      context->SetState(STATE_ROLLBACK);
      if (protect_)
				OnSafeRollback();
			else
				OnRollback();
      context->SetReturnCode(RETURN_ERROR);
		}
    context->SetState(STATE_IDLE);
	}

	void Task::OnSafeProcess()
	{
		__try {
			OnProcess();
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
      auto context = memory_->GetContext();
      if (context != nullptr) {
        context->SetReturnCode(RETURN_UNHANDLED);
      }
		}
	}

	void Task::OnSafeRollback()
	{
		__try {
			OnRollback();
		}
    __except (EXCEPTION_EXECUTE_HANDLER) {
      auto context = memory_->GetContext();
      if (context != nullptr) {
        context->SetReturnCode(RETURN_UNHANDLED);
      }
    }
	}

	Memory* Task::GetMemory()
	{
		return memory_;
	}

	void Task::Start()
	{
    auto context = memory_->GetContext();
    context->SetState(STATE_QUEUE);
    auto worker = Worker::Instance();
		worker->StartTask(this);
	}

	void Task::Stop(uint32 wait)
	{
    auto context = memory_->GetContext();
		auto worker = Worker::Instance();
		if (wait != 0)
		{
      context->SetControlCode(CONTROL_CANCEL);
			uint32 time0 = GetTickCount();
			uint32 time1 = time0;
			while (time1 - time0 < wait)
			{
        if (context->GetCurrentState() == STATE_IDLE)
					return;
				Sleep(20);
			}
		}
		worker->StopTask(this);
    context->SetReturnCode(RETURN_TERMINATE);
    context->SetState(STATE_IDLE);
	}

	void Task::Pause(uint32 wait)
	{
    auto context = memory_->GetContext();
		auto worker = Worker::Instance();
		if (wait != 0)
		{
      context->SetControlCode(CONTROL_PAUSE);
			uint32 time0 = GetTickCount();
			uint32 time1 = time0;
			while (time1 - time0 < wait)
			{
        if (context->GetCurrentState() == STATE_PAUSE)
					return;
				Sleep(20);
			}
		}
		worker->PauseTask(this);
    context->SetState(STATE_PAUSE);
    context->SetControlCode(CONTROL_NULL);
	}

	void Task::Resume()
	{
    auto context = memory_->GetContext();
    auto worker = Worker::Instance();
		if (!worker->ResumeTask(this))
      context->SetControlCode(CONTROL_RESUME);
	}

	void Task::Join()
	{
    auto context = memory_->GetContext();
    auto setting = Setting::Instance();
		int span = setting->IsRealTime() ? 0 : 50;
    while (context->GetCurrentState() != STATE_IDLE)
			Sleep(span);
	}

  void Task::TryHold()
  {
    auto context = memory_->GetContext();
    if (context->GetControlCode() == CONTROL_PAUSE) {
      context->SwitchHold();
      while (context->GetControlCode() != CONTROL_RESUME)
        Sleep(50);
      context->SwitchHold();
    }
  }
}