#ifndef _SPIRITIUM_SETTING_
#define _SPIRITIUM_SETTING_

#include "base.h"

namespace spiritium
{
	//engine setting
	class SPIRITIUM_API Setting
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