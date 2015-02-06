#include "voidum.h"
//#include "voidum_ex.h"

using namespace voidum;

Engine* engine = nullptr;

int main()
{
	engine = Engine::Instance();
	//engine->SetWorker(new UserDefinedWorker());

	Driver::Load("mscpp11")->Enable();

	auto bridge1 = new LocalBridge("local1");
	bridge1->Connect("E:\\");
	bridge1->Enable();
	//auto bridge2 = new DummyBridge();
	//bridge2->Enable();
	//auto bridge3 = new RemoteBridge();
	//bridge3->Enable();

	auto package = Package::Load(bridge1, "sample");
	auto service = package->GetService("");

	auto task = Task::Create(service);
	auto memory = task->GetMemory();
	auto dataset = memory->GetDataset();
	dataset->Count();
	task->Start();
	task->Join();

	//bridge2->Disable();
	//bridge3->Disable();
	delete engine;
	return 0;
}