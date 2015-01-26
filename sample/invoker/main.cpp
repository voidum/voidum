#include "spiritium.h"
//#include "spiritium_ex.h"

using namespace spiritium;

int main()
{
	Engine* engine = Engine::Instance();
	//engine->SetWorker(new UserDefinedWorker());
	engine->Online();
	
	Driver* driver1 = Driver::Load("mscpp11");
	//Driver* driver2 = new HostDriver();
	//Driver* driver3 = new RemoteDriver();
	engine->Drive(driver1);
	//engine->Drive(driver2);
	//engine->Drive(driver3);

	Locator locator("local", "test/test", "package");
	Package* package = Package::Load(locator);
	Service* service = package->GetService("");

	Task* task = service->CreateTask();
	Storage* storage = task->GetStorage();
	task->Start();
	task->Join();

	engine->Drive(driver1, false);
	//engine->Driver(driver2, false);
	//engine->Driver(driver3, false);

	engine->Offline();
	delete engine;
	return 0;
}