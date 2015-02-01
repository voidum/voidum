#include "dataset.h"

namespace spiritium
{
	Dataset* Dataset::Parse(const text& define)
	{
		define.size();
		return nullptr;
	}

	Dataset::Dataset() { }

	Dataset::~Dataset() 
	{
	}

	Field* Dataset::GetField(int index)
	{
		using iter = std::list<Field*>::iterator;
		for (iter i = _Fields.begin(); i != _Fields.end(); i++) {
			auto temp = *i;
			if (temp->GetIndex() == index)
				return temp;
		}
		return nullptr;
	}

	Field* Dataset::operator[](int index)
	{
		return GetField(index);
	}

	int Dataset::Count()
	{
		return _Fields.size();
	}

	Dataset* Dataset::Copy()
	{
		return nullptr;
	}
}