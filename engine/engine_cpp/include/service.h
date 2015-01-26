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
	protected:
		Service();
	public:
		virtual ~Service();

	public:
		static Service* Parse(std::string json);

	protected:
		Package* _Package;

		//service id
		std::string _Id;

		//protect flag
		bool _HasProtect;

		//entry symbol
		std::string _RollbackSym;

		//process symbol
		std::string _ProcessSym;

		//data contract
		std::string _Contract;

	public:
		//get package
		Package* GetPackage();

		//set package
		void SetPackage(Package* package);

		//get service id
		std::string GetServiceId();

		//get protect flag
		bool HasProtect();

		//get process symbol
		std::string GetProcessSym();

		//get rollback symbol
		std::string GetRollbackSym();

		//get dataset
		Dataset* CreateDataset();

	public:
		//create task
		Task* CreateTask();
	};
}

#endif