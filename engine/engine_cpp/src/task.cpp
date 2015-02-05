#include "task.h"
#include "memory.h"
#include "dataset.h"
#include "context.h"
#include "locator.h"
#include "bridge.h"
#include "package.h"
#include "service.h"
#include "setting.h"
#include "worker.h"

namespace voidum
{
	Task* Task::Current()
	{
		auto worker = Worker::Instance();
		return worker->CurrentTask();
	}

	Task::Task()
	{
		_Memory = nullptr;
	}

	Task::~Task()
	{
		ClearObject(_Memory);
	}

	bool Task::Bind(Service* service)
	{
		_Service = service;
		_HasProtect = service->HasProtect();
		_Memory = new Memory();
		_Memory->SetContext(new Context());
		_Memory->SetDataset(
			Dataset::Parse(service->GetContract()));
		return true;
	}

	void Task::Invoke()
	{
		auto context = _Memory->GetContext();
		try {
			context->SetControlCode(CONTROL_NULL);
			context->SetReturnCode(RETURN_NULLENTRY);
			context->SetState(STATE_BUSY);
			if (_HasProtect)
				OnSafeProcess();
			else
				OnProcess();
			context->SetReturnCode(RETURN_NORMAL);
		}
		catch (Error*) {
			context->SetState(STATE_ROLLBACK);
			if (_HasProtect)
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
			if (_Memory != nullptr) {
				auto context = _Memory->GetContext();
				if (context != nullptr) {
					context->SetReturnCode(RETURN_UNHANDLED);
				}
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
			if (_Memory != nullptr) {
				auto context = _Memory->GetContext();
				if (context != nullptr) {
					context->SetReturnCode(RETURN_UNHANDLED);
				}
			}
			//todo: broadcast
		}
	}

	Memory* Task::GetMemory()
	{
		return _Memory;
	}

	void Task::Start()
	{
		auto bridge = Bridge::Find(_Service->GetPackage()->GetHostMode());
		auto locator = bridge->GetLocator(TARGET_TASK, _Index);
		locator->Request("start");

		auto worker = Worker::Instance();
		auto context = _Memory->GetContext();
		context->SetState(STATE_QUEUE);
		worker->StartTask(this);
	}

	void Task::Stop(uint32 wait)
	{
		auto bridge = Bridge::Find(_Service->GetPackage()->GetHostMode());
		auto locator = bridge->GetLocator(TARGET_TASK, _Index);
		locator->Request("stop");

		auto worker = Worker::Instance();
		auto context = _Memory->GetContext();
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
		auto bridge = Bridge::Find(_Service->GetPackage()->GetHostMode());
		auto locator = bridge->GetLocator(TARGET_TASK, _Index);
		locator->Request("pause");

		auto worker = Worker::Instance();
		auto context = _Memory->GetContext();
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
		auto bridge = Bridge::Find(_Service->GetPackage()->GetHostMode());
		auto locator = bridge->GetLocator(TARGET_TASK, _Index);
		locator->Request("resume");

		auto worker = Worker::Instance();
		if (!worker->ResumeTask(this))
		{
			auto context = _Memory->GetContext();
			context->SetControlCode(CONTROL_RESUME);
		}
	}

	void Task::Join()
	{
		auto bridge = Bridge::Find(_Service->GetPackage()->GetHostMode());
		auto locator = bridge->GetLocator(TARGET_TASK, _Index);
		locator->Request("join");

		auto setting = Setting::Instance();
		int span = setting->IsRealTime() ? 0 : 50;
		auto context = _Memory->GetContext();
		while (context->GetCurrentState() != STATE_IDLE)
			Sleep(span);
	}

	void Task::Sync()
	{
	}
}