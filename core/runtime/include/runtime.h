#pragma once

#include "base.h"

namespace spiritium
{
	class DriverHub;

	//runtime
	class SPIRITIUM_API Runtime : Uncopiable
	{
	private:
		Runtime();
	public:
		~Runtime();

	private:
		static std::atomic<Runtime*> _Instance;
		static std::mutex _SyncRoot;

	public:
		static Runtime* Instance();

	private:
		DriverHub* _DriverHub;

	public:
		//online runtime
		void Online();

		//offline runtime
		void Offline();

	public:
		//get spiritium runtime version
		std::string GetVersion();
	};
}