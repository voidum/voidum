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
}