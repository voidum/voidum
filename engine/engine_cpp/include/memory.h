#ifndef _SPIRITIUM_MEMORY_
#define _SPIRITIUM_MEMORY_

#include "base.h"

namespace spiritium
{
	class Context;
	class Dataset;
	class Error;

	class SPIRITIUM_API Memory
	{
	public:
		//get current memory
		static Memory* Current();

	private:
		Context* _Context;
		Dataset* _Dataset;
		Error* _Error;

	public:
		Memory();
		~Memory();

	public:
		//get context
		Context* GetContext();

		//set context
		void SetContext(Context* context);

	public:
		//get dataset
		Dataset* GetDataset();

		//set dataset
		void SetDataset(Dataset* dataset);

	public:
		//get error
		Error* GetError();

		//set error
		void SetError(Error* error);
	};
}

#endif