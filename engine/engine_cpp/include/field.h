#ifndef _VOIDUM_FIELD_
#define _VOIDUM_FIELD_

#include "base.h"

namespace voidum
{
	class VOIDUM_API Field
	{
	public:
		static Field* Parse(const text& define);

	private:
		int _Index;

		int _Length;

		int _MaxLength;

		raw _Data;

	public:
		Field();
		~Field();

	public:
		int GetIndex();

	public:
		raw GetValue();
		
		void SetValue(raw data);
	};
}

#endif