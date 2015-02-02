#include "memory.h"
#include "task.h"
#include "context.h"
#include "dataset.h"
#include "error.h"

namespace voidum
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
		ClearObject(_Dataset);
		ClearObject(_Error);
	}

	Context* Memory::GetContext()
	{
		return _Context;
	}

	void Memory::SetContext(Context* context)
	{
		_Context = context;
	}

	Dataset* Memory::GetDataset()
	{
		return _Dataset;
	}

	void Memory::SetDataset(Dataset* dataset)
	{
		_Dataset = dataset;
	}

	Error* Memory::GetError()
	{
		return _Error;
	}

	void Memory::SetError(Error* error)
	{
		_Error = error;
	}
}