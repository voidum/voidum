#ifndef _VOIDUM_DATASET_
#define _VOIDUM_DATASET_

#include "base.h"
#include "field.h"
#include <list>

namespace voidum
{
	//dataset
	class VOIDUM_API Dataset
	{
	public:
		static Dataset* Parse(const text& define);

	private:
		std::list<Field*> _Fields;

	private:
		Dataset();

	public:
		~Dataset();

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

		//clear dataset
		void Clear();
	};
}

#endif