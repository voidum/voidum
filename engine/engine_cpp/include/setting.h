#ifndef _SPIRITIUM_SETTING_
#define _SPIRITIUM_SETTING_

#include "base.h"

namespace spiritium
{
	//engine setting
	class SPIRITIUM_API Setting
	{
		friend class Engine;

	public:
		static Setting* Instance();

	private:
		bool _IsSilent;
		bool _IsRealTime;

	private:
		Setting();

	public:
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