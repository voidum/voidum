#ifndef _SPIRITIUM_FIELD_
#define _SPIRITIUM_FIELD_

#include "base.h"

namespace spiritium
{
	class SPIRITIUM_API Field
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