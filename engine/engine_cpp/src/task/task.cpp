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
		return worker->CurrentTask();
	}

	Task::Task()
	{
		memory_ = new Memory();
	}

	Task::~Task()
	{
		ClearObject(memory_);
	}

	void Task::Invoke()
	{
		try {
			context_->SetControlCode(CONTROL_NULL);
      context_->SetReturnCode(RETURN_NULLENTRY);
      context_->SetState(STATE_BUSY);
			if (protect_)
				OnSafeProcess();
			else
				OnProcess();
      context_->SetReturnCode(RETURN_NORMAL);
		}
		catch (Error*) {
      context_->SetState(STATE_ROLLBACK);
      if (protect_)
				OnSafeRollback();
			else
				OnRollback();
      context_->SetReturnCode(RETURN_ERROR);
		}
    context_->SetState(STATE_IDLE);
	}

	void Task::OnSafeProcess()
	{
		__try {
			OnProcess();
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
      if (context_ != nullptr) {
        context_->SetReturnCode(RETURN_UNHANDLED);
      }
			//todo: broadcast
		}
	}

	void Task::OnSafeRollback()
	{
		__try {
			OnRollback();
		}
    __except (EXCEPTION_EXECUTE_HANDLER) {
      if (context_ != nullptr) {
        context_->SetReturnCode(RETURN_UNHANDLED);
      }
      //todo: broadcast
    }
	}

	Memory* Task::GetMemory()
	{
		return memory_;
	}

	void Task::Start()
	{
		auto worker = Worker::Instance();
    context_->SetState(STATE_QUEUE);
		worker->StartTask(this);
	}

	void Task::Stop(uint32 wait)
	{
		auto worker = Worker::Instance();
		if (wait != 0)
		{
      context_->SetControlCode(CONTROL_CANCEL);
			uint32 time0 = GetTickCount();
			uint32 time1 = time0;
			while (time1 - time0 < wait)
			{
        if (context_->GetCurrentState() == STATE_IDLE)
					return;
				Sleep(20);
			}
		}
		worker->StopTask(this);
    context_->SetReturnCode(RETURN_TERMINATE);
    context_->SetState(STATE_IDLE);
	}

	void Task::Pause(uint32 wait)
	{
		auto worker = Worker::Instance();
		if (wait != 0)
		{
      context_->SetControlCode(CONTROL_PAUSE);
			uint32 time0 = GetTickCount();
			uint32 time1 = time0;
			while (time1 - time0 < wait)
			{
        if (context_->GetCurrentState() == STATE_PAUSE)
					return;
				Sleep(20);
			}
		}
		worker->PauseTask(this);
    context_->SetState(STATE_PAUSE);
    context_->SetControlCode(CONTROL_NULL);
	}

	void Task::Resume()
	{
		auto worker = Worker::Instance();
		if (!worker->ResumeTask(this))
      context_->SetControlCode(CONTROL_RESUME);
	}

	void Task::Join()
	{
		auto setting = Setting::Instance();
		int span = setting->IsRealTime() ? 0 : 50;
    while (context_->GetCurrentState() != STATE_IDLE)
			Sleep(span);
	}
}