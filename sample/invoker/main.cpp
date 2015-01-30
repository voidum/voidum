#include "spiritium.h"
//#include "spiritium_ex.h"

using namespace spiritium;

int main()
{
	auto engine = Engine::Instance();
	auto worker = engine->GetWorker();
	//engine->SetWorker(new UserDefinedWorker());
	
	Driver::Load("mscpp11")->Enable();
	//auto driver_dummy = new DummyDriver();
	//auto driver_remote = new RemoteDriver();

	auto package = Package::Load("local;");
	auto service = package->GetService("");

	auto task = service->CreateTask();
	auto memory = task->GetMemory();
	task->Start();
	task->Join();

	//driver_dummy->Disable();
	return 0;
}