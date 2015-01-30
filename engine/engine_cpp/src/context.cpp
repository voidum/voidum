#include "context.h"
#include "memory.h"

namespace spiritium
{
	Context::Context() 
	{
		_LastState = STATE_IDLE;
		_CurrentState = STATE_IDLE;
		_ReturnCode = RETURN_NORMAL;
		_ControlCode = CONTROL_NULL;
		_Progress = 0;
	}

	Context::~Context() { }

	void Context::SetState(uint8 value)
	{
		_SyncRoot.lock();
		_LastState = _CurrentState;
		_CurrentState = value;
		_SyncRoot.unlock();
	}

	uint8 Context::GetCurrentState()
	{
		_SyncRoot.lock();
		uint8 value = _CurrentState;
		_SyncRoot.unlock();
		return value;
	}

	uint8 Context::GetLastState()
	{
		_SyncRoot.lock();
		uint8 value = _LastState;
		_SyncRoot.unlock();
		return value;
	}

	void Context::SetReturnCode(uint8 value)
	{
		_SyncRoot.lock();
		_ReturnCode = value;
		_SyncRoot.unlock();
	}

	uint8 Context::GetReturnCode()
	{
		_SyncRoot.lock();
		uint8 value = _ReturnCode;
		_SyncRoot.unlock();
		return value;
	}

	void Context::SetControlCode(uint8 value)
	{
		_SyncRoot.lock();
		_ControlCode = value;
		_SyncRoot.unlock();
	}

	uint8 Context::GetControlCode()
	{
		_SyncRoot.lock();
		uint8 value = _ControlCode;
		_SyncRoot.lock();
		return value;
	}

	void Context::SwitchHold()
	{
		_SyncRoot.lock();
		if (_ControlCode == CONTROL_PAUSE)
		{
			_LastState = _CurrentState;
			_CurrentState = STATE_PAUSE;
		}
		else if (_ControlCode == CONTROL_RESUME)
		{
			_CurrentState = _LastState;
			_LastState = STATE_PAUSE;
		}
		_ControlCode = CONTROL_NULL;
		_SyncRoot.unlock();
	}

	float Context::GetProgress()
	{
		_SyncRoot.lock();
		float value = _Progress;
		_SyncRoot.unlock();
		return value;
	}

	void Context::SetProgress(float value)
	{
		_SyncRoot.lock();
		_Progress = value;
		_SyncRoot.unlock();
	}

	const text& Context::GetKeyFrame()
	{
		_SyncRoot.lock();
		const text& value = _KeyFrame;
		_SyncRoot.unlock();
		return value;
	}

	void Context::SetKeyFrame(const text& value)
	{
		_SyncRoot.lock();
		_KeyFrame = value;
		_SyncRoot.unlock();
	}
}