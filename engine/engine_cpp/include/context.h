#ifndef _SPIRITIUM_CONTEXT_
#define _SPIRITIUM_CONTEXT_

#include "base.h"

namespace spiritium
{
	class Task;

	//routine context
	class SPIRITIUM_API Context
	{
	private:
		std::mutex _SyncRoot;

	private:
		uint8 _LastState;
		uint8 _CurrentState;
		uint8 _ReturnCode;
		uint8 _ControlCode;
		text _KeyFrame;
		float _Progress; // [0,100]

	public:
		Context();
		~Context();

	public:
		//set state
		void SetState(uint8 value);

		//set return code
		void SetReturnCode(uint8 value);

		//set control code
		void SetControlCode(uint8 value);

		//set progress
		void SetProgress(float value);

		//set key frame
		void SetKeyFrame(const text& value);

		//switch between pause and resume
		void SwitchHold();

		//switch between front and back
		void SwitchBusy();

	public:
		//get current state
		uint8 GetCurrentState();

		//get last state
		uint8 GetLastState();

		//get return code
		uint8 GetReturnCode();

		//get control code
		uint8 GetControlCode();

		//get progress
		float GetProgress();

		//get key frame
		const text& GetKeyFrame();
	};
}

#endif