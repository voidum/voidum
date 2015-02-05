#include "voidum.h"
//#include "voidum_ex.h"

using namespace voidum;

Engine* engine = nullptr;

int main()
{
	engine = Engine::Instance();
	//engine->SetWorker(new UserDefinedWorker());

	Driver::Load("mscpp11")->Enable();

	auto local_bridge = new LocalBridge();
	local_bridge->Connect("E:\\");
	local_bridge->Enable();
	//auto dummy_bridge = new DummyBridge();
	//dummy_bridge->Enable();
	//auto dummy_bridge = new RemoteBridge();
	//remote_bridge->Enable();

	auto package = Package::Load(local_bridge, "sample");
	auto service = package->GetService("");

	auto task = service->CreateTask();
	auto memory = task->GetMemory();
	auto dataset = memory->GetDataset();
	dataset->Count();
	task->Start();
	task->Join();

	//dummy_bridge->Disable();
	//dummy_bridge->Disable();
	delete engine;
	return 0;
}