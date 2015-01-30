#include "memory.h"
#include "engine.h"
#include "task.h"
#include "context.h"
//#include "dataset.h"
#include "error.h"

namespace spiritium
{
	Memory* Memory::Current()
	{
		Task* task = Task::Current();
		if (task != nullptr)
			return task->GetMemory();
		return nullptr;
	}

	Memory::Memory()
	{
	}

	Memory::~Memory()
	{
		ClearObject(_Context);
		//ClearObject(_Dataset);
		ClearObject(_Error);
	}

	bool Memory::HasProtect()
	{
		return _HasProtect;
	}

	Context* Memory::GetContext()
	{
		return _Context;
	}

	Dataset* Memory::GetDataset()
	{
		return _Dataset;
	}

	Error* Memory::GetError()
	{
		return _Error;
	}

	void Memory::SetProtect(bool protect)
	{
		_HasProtect = protect;
	}

	void Memory::SetContext(Context* context)
	{
		_Context = context;
	}

	void Memory::SetDataset(Dataset* dataset)
	{
		_Dataset = dataset;
	}

	void Memory::SetError(Error* error)
	{
		_Error = error;
	}

	void Memory::SetService(Service* service)
	{
		_Service = service;
	}
}