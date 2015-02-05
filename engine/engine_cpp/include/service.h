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

		//data contract
		std::string _Contract;

		//protect flag
		bool _Protect;

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

		//set package
		void SetPackage(Package* package);

	public:
		//get service name
		const text& GetName();

		//get process symbol
		const text& GetProcessSym();

		//get rollback symbol
		const text& GetRollbackSym();

		//get dataset contract
		const text& GetContract();

		//get protect flag
		bool HasProtect();

	public:
		//create task
		Task* CreateTask();
	};
}

#endif