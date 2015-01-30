#ifndef _SPIRITIUM_SERVICE_
#define _SPIRITIUM_SERVICE_

#include "base.h"

namespace spiritium
{
	class Dataset;
	class Package;
	class Task;

	//service
	class SPIRITIUM_API Service
	{
	public:
		static Service* Parse(const text& json);

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
		//parent
		Package* _Package;

	protected:
		Service();

	public:
		virtual ~Service();

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

		//create dataset
		Dataset* CreateDataset();

		//get protect flag
		bool HasProtect();

	public:
		//create task
		Task* CreateTask();
	};
}

#endif