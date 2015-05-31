#include "voidum.h"
//#include "voidum_ex.h"

using namespace voidum;

int main()
{
  auto engine = Engine::Start();
  //engine->SetWorker(new UserDefinedWorker());

  auto driver1 = Driver::Load("mscpp11");
  driver1->Enable();

  auto host1 = new LocalHost("local1");
  //auto host2 = new DummyHost();
  //auto host3 = new RemoteHost();
  host1->Enable();
  host1->Connect("E:\\");

  auto package = host1::GetPackage("sample");
  auto service = package->GetService("test1");

  auto task = Task::Create(service);
  auto memory = task->GetMemory();
  memory->Write(raw_data, raw_data_size);
  task->Start();
  task->Join();

  host1->Disable();

  driver1->Disable();
  Engine::Stop();
  return 0;
}