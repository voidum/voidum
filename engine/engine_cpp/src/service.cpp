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

	Package* Service::GetPackage()
	{
		return _Package;
	}

	void Service::SetPackage(Package* package)
	{
		_Package = package;
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

	const text& Service::GetContract()
	{
		return _Contract;
	}

	bool Service::HasProtect()
	{
		return _Protect;
	}

	Task* Service::CreateTask()
	{
		return nullptr;
	}
}