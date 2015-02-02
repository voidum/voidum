#ifndef _VOIDUM_SETTING_
#define _VOIDUM_SETTING_

#include "base.h"

namespace voidum
{
	//engine setting
	class VOIDUM_API Setting
	{
	public:
		static Setting* Instance();

	private:
		bool _IsSilent;
		bool _IsRealTime;

	public:
		Setting();
		~Setting();

	public:
		bool IsSilent();
		void IsSilent(bool value);

	public:
		bool IsRealTime();
		void IsRealTime(bool value);
	};
}

#endif