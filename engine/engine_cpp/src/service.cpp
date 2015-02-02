#include "service.h"

namespace voidum
{
	Service* Service::Parse(const text& define)
	{
		define.size();
		return nullptr;
	}

	Service::Service()
	{
	}

	Service::~Service()
	{
	}

	const text& Service::GetName()
	{
		return _Name;
	}

	const text& Service::GetProcessSym()
	{
		return _ProcessSym;
	}

	const text& Service::GetRollbackSym()
	{
		return _RollbackSym;
	}

	bool Service::HasProtect()
	{
		return _Protect;
	}

	Dataset* Service::CreateDataset()
	{
		return nullptr;
	}

	Task* Service::CreateTask()
	{
		return nullptr;
	}
}