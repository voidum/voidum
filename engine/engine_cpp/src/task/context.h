#ifndef _VOIDUM_CONTEXT_
#define _VOIDUM_CONTEXT_

#include "base.h"

namespace voidum
{
	class Task;

	//context for task
	class VOIDUM_API Context
	{
	private:
		std::mutex _SyncRoot;

	private:
		uint8 _LastState;
		uint8 _CurrentState;
		uint8 _ReturnCode;
		uint8 _ControlCode;

	public:
		Context();
		~Context();

	public:
		//get current state
		uint8 GetCurrentState();

		//get last state
		uint8 GetLastState();

		//set state
		void SetState(uint8 value);

	public:
		//get control code
		uint8 GetControlCode();

		//set control code
		void SetControlCode(uint8 value);

	public:
		//get return code
		uint8 GetReturnCode();

		//set return code
		void SetReturnCode(uint8 value);

	public:
		//switch pause and resume
		void SwitchHold();

		//try to pause and wait for resume
		void TryHold();
	};
}

#endif