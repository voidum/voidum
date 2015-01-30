#ifndef _SPIRITIUM_MEMORY_
#define _SPIRITIUM_MEMORY_

#include "base.h"

namespace spiritium
{
	class Context;
	class Dataset;
	class Error;
	class Service;

	class SPIRITIUM_API Memory
	{
	public:
		//get current memory
		static Memory* Current();

	public:
		Memory();
		~Memory();

	private:
		bool _HasProtect;
		Context* _Context;
		Dataset* _Dataset;
		Error* _Error;
		Service* _Service;

	public:
		//get protect flag
		bool HasProtect();

		//get context
		Context* GetContext();

		//get dataset
		Dataset* GetDataset();

		//get error
		Error* GetError();

	public:
		//set protect flag
		void SetProtect(bool protect);

		//set context
		void SetContext(Context* context);

		//set dataset
		void SetDataset(Dataset* dataset);

		//set error
		void SetError(Error* error);

		//set service
		void SetService(Service* service);
	};
}

#endif