#include "context.h"
#include "memory.h"

namespace voidum
{
	Context::Context()
	{
		last_state_ = STATE_IDLE;
		current_state_ = STATE_IDLE;
		return_code_ = RETURN_NORMAL;
    control_code_ = CONTROL_NULL;
	}

	Context::~Context() { }

	uint8 Context::GetCurrentState()
	{
		sync_root_.lock();
    uint8 value = current_state_;
    sync_root_.unlock();
		return value;
	}

	uint8 Context::GetLastState()
	{
    sync_root_.lock();
    uint8 value = last_state_;
    sync_root_.unlock();
		return value;
	}

	void Context::SetState(uint8 value)
	{
    sync_root_.lock();
    last_state_ = current_state_;
    current_state_ = value;
    sync_root_.unlock();
	}

	uint8 Context::GetControlCode()
	{
    sync_root_.lock();
    uint8 value = control_code_;
    sync_root_.lock();
		return value;
	}

	void Context::SetControlCode(uint8 value)
	{
    sync_root_.lock();
    control_code_ = value;
    sync_root_.unlock();
	}

	uint8 Context::GetReturnCode()
	{
    sync_root_.lock();
    uint8 value = return_code_;
    sync_root_.unlock();
		return value;
	}

	void Context::SetReturnCode(uint8 value)
	{
    sync_root_.lock();
    return_code_ = value;
    sync_root_.unlock();
	}

	void Context::SwitchHold()
	{
    sync_root_.lock();
		if (control_code_ == CONTROL_PAUSE)
		{
      last_state_ = current_state_;
			current_state_ = STATE_PAUSE;
      control_code_ = CONTROL_NULL;
		}
    else if (control_code_ == CONTROL_RESUME)
		{
      current_state_ = last_state_;
      last_state_ = STATE_PAUSE;
      control_code_ = CONTROL_NULL;
		}
    sync_root_.unlock();
	}

	void Context::TryHold()
	{
		if (GetControlCode() == CONTROL_PAUSE)
		{
			SwitchHold();
			while (GetControlCode() != CONTROL_RESUME)
				Sleep(50);
			SwitchHold();
		}
	}
}