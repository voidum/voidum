#ifndef _SPIRITIUM_TRAITS_
#define _SPIRITIUM_TRAITS_

#include "driver.h"
#include "package.h"
#include "task.h"

namespace spiritium
{
	template<typename T>
	class Traits {	};

	template<>
	class Traits<Driver>
	{
	public:
		typedef const std::string& Key;

		static inline Key KeyOf(Driver* element) {
			return element->GetRuntime();
		}

		static inline bool Equals(Key key1, Key key2) {
			return key1 == key2;
		}
	};

	template<>
	class Traits<Package>
	{
	public:
		typedef const std::string& Key;

		static inline Key KeyOf(Package* element) {
			return element->GetName();
		}

		static inline bool Equals(Key key1, Key key2) {
			return key1 == key2;
		}
	};

	template<>
	class Traits<Task>
	{
	public:
		typedef const int& Key;

		static inline Key KeyOf(Task* element) {
			return element->GetIndex();
		}

		static inline bool Equals(Key key1, Key key2) {
			return key1 == key2;
		}
	};
}

#endif