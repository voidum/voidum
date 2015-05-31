#ifndef _VOIDUM_MEMORY_
#define _VOIDUM_MEMORY_

#include "base.h"

namespace voidum
{
  class Error;
  class Context;
  class Message;

	class VOIDUM_API Memory
	{
	public:
		//get current memory
		static Memory* Current();

	private:
    Context* context_;
    Message* message_;
    Error* error_;

	public:
		Memory();
		~Memory();

  public:
    Context* GetContext();

    Message* GetMessage();

  public:
    Error* GetError();

    void SetError(Error* error);
	};
}

#endif