#ifndef _VOIDUM_SERVICE_
#define _VOIDUM_SERVICE_

#include "base.h"

namespace voidum
{
	class Dataset;
	class Package;
	class Task;

	//service
	class VOIDUM_API Service
	{
	public:
		static Service* Parse(const text& define);

	protected:
		//service name
		std::string _Name;

		//entry symbol
		std::string _RollbackSym;

		//process symbol
		std::string _ProcessSym;

	protected:
		//container
		Package* _Package;

	protected:
		Service();

	public:
		~Service();

	public:
		//get package
		Package* GetPackage();

	public:
		//get service name
		const text& GetName();

		//get process symbol
		const text& GetProcessSym();

		//get rollback symbol
		const text& GetRollbackSym();
	};
}

#endif