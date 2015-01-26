#ifndef _SPIRITIUM_LIST_
#define _SPIRITIUM_LIST_

#include "base.h"
#include "traits.h"
#include <list>

namespace spiritium
{
	template<typename T, typename TraitsT = Traits<T>>
	class List
	{
	public:
		typedef typename TraitsT::Key Key;
		typedef typename std::list<T*>::iterator Iterator;

	private:
		std::mutex _SyncRoot;
		std::list<T*> _Data;

	public:
		List() { }

		~List() 
		{
			RemoveAll();
		}

	public:
		T* Find(Key key)
		{
			std::lock_guard<std::mutex> lock(_SyncRoot);
			for (Iterator i = _Data.begin(); i != _Data.end(); i++)
			{
				T* temp = *i;
				if (TraitsT::Equals(TraitsT::KeyOf(temp), key))
					return temp;
			}
			return null;
		}

		int Count()
		{
			std::lock_guard<std::mutex> lock(_SyncRoot);
			return _Data.size();
		}

	public:
		void Add(T* element)
		{
			std::lock_guard<std::mutex> lock(_SyncRoot);
			for (Iterator i = _Data.begin(); i != _Data.end(); i++)
				if (TraitsT::Equals(
					TraitsT::KeyOf(temp), TraitsT::KeyOf(element)))
					return;
			_Data.push_back(element);
		}

		void Remove(T* element)
		{
			std::lock_guard<std::mutex> lock(_SyncRoot);
			for (Iterator i = _Data.begin(); i != _Data.end(); i++)
			{
				T* temp = *i;
				if (TraitsT::Equals(
					TraitsT::KeyOf(temp), TraitsT::KeyOf(element)))
				{
					Clear(temp);
					_Data.erase(i);
					return;
				}
			}
		}

		void RemoveAll()
		{
			std::lock_guard<std::mutex> lock(_SyncRoot);
			for (Iterator i = _Data.begin(); i != _Data.end(); i++)
				Clear(*i);
			_Data.clear();
		}
	};
}

#endif