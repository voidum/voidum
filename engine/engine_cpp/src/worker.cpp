#include "worker.h"
#include "engine.h"

namespace spiritium
{
	Worker* Worker::Instance()
	{
		auto engine = Engine::Instance();
		return engine->_Worker;
	}

	Worker::Worker() { }

	Worker::~Worker()
	{
		Stop();
	}
}