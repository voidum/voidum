#include "worker.h"
#include "engine.h"

namespace spiritium
{
	Worker* Worker::Instance()
	{
		auto engine = Engine::Instance();
		return engine->GetWorker();
	}

	Worker::Worker() { }

	Worker::~Worker() { }
}