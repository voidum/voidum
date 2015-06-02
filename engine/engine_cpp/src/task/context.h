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
		std::mutex sync_root_;

	private:
		uint8 last_state_;
		uint8 current_state_;
		uint8 return_code_;
		uint8 control_code_;

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