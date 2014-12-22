#pragma once

#include "base.h"

namespace spiritium
{
	class Library;
	class Task;

	//driver {base}
	class SPIRITIUM_API Driver
	{
	public:
		Driver();
		virtual ~Driver();

	public:
		//load driver by path
		static Driver* Load(std::string path);
		static Driver* Load(std::wstring path);

	public:
		//get runtime id
		virtual std::string GetRuntimeId() = 0;

	public:
		//create library
		virtual Library* CreateLibrary() = 0;

		//create task
		virtual Task* CreateTask() = 0;
	};
}