#include "voidum.h"
//#include "voidum_ex.h"

using namespace voidum;

int main()
{
	auto engine = Engine::Instance();

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