#include "error.h"
#include "memory.h"

namespace spiritium
{
	Error::Error(int what)
	{
		_What = what;
	}

	Error::~Error() { }

	int Error::What()
	{
		return _What;
	}

	void Error::Throw(int what)
	{
		auto error = new Error(what);
		auto memory = Memory::Current();
		if (memory != nullptr)
			memory->SetError(error);
		throw error;
	}
}