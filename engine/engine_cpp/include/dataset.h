#ifndef _SPIRITIUM_DATASET_
#define _SPIRITIUM_DATASET_

#include "base.h"
#include "field.h"
#include <list>

namespace spiritium
{
	//dataset
	class SPIRITIUM_API Dataset
	{
	private:
		std::list<Field*> _Fields;

	private:
		Dataset();

	public:
		~Dataset();

	public:
		//parse dataset from define
		static Dataset* Parse(const text& define);

	public:
		//get field count
		int Count();

	public:
		//get field by index
		Field* GetField(int index);

		//get field by index
		Field* operator [] (int index);

	public:
		//copy dataset
		Dataset* Copy();
	};
}

#endif