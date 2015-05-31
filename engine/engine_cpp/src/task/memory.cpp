#include "memory.h"
#include "task.h"
#include "context.h"
#include "message.h"
#include "error.h"

namespace voidum
{
	Memory* Memory::Current()
	{
		Task* task = Task::Current();
		if (task != nullptr)
			return task->GetMemory();
		return nullptr;
	}

	Memory::Memory()
	{
    context_ = new Context();
    message_ = new Message();
    error_ = nullptr;
	}

	Memory::~Memory()
	{
    delete context_;
    delete message_;
    if (error_ != nullptr)
      delete error_;
	}

  Context* Memory::GetContext() 
  {
    return context_;
  }

  Message* Memory::GetMessage() 
  {
    return message_;
  }

  Error* Memory::GetError() 
  {
    return error_;
  }

  void Memory::SetError(Error* error) 
  {
    if (error_ != nullptr)
      delete error_;
    error_ = error;
  }
}