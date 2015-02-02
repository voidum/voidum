#include "worker.h"
#include "engine.h"

namespace voidum
{
	Worker* Worker::Instance()
	{
		auto engine = Engine::Instance();
		return engine->GetWorker();
	}

	Worker::Worker() { }

	Worker::~Worker() { }
}