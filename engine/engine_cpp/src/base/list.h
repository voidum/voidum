#ifndef _VOIDUM_LIST_
#define _VOIDUM_LIST_

#include <functional>
#include <list>
#include <mutex>

#include "base.h"

namespace voidum
{
  template<typename T>
  class List
  {
  private:
    typedef typename std::list<T*>::iterator iterator_t;
    typedef typename std::function<bool(T*)> predicate_t;

  private:
    std::mutex sync_root_;
    std::list<T*> data_;

  public:
    List() { }

    ~List()
    {
      Clear(true);
    }

  public:
    int Count()
    {
      std::lock_guard<std::mutex> lock(sync_root_);
      return data_.size();
    }

    bool Contains(const T& item)
    {
      std::lock_guard<std::mutex> lock(sync_root_);
      for (iterator_t i = data_.begin(); i != data_.end(); i++) {
        if (*i == &item)
          return true;
      }
      return false;
    }

    bool Exists(const predicate_t& predicate) 
    {
      std::lock_guard<std::mutex> lock(sync_root_);
      for (iterator_t i = data_.begin(); i != data_.end(); i++) {
        if (predicate(*i))
          return true;
      }
      return false;
    }

    //get item:T by predicate
    T* Find(const predicate_t& predicate)
    {
      std::lock_guard<std::mutex> lock(sync_root_);
      for (iterator_t i = data_.begin(); i != data_.end(); i++) {
        auto temp = *i;
        if (predicate(temp))
          return temp;
      }
      return nullptr;
    }

    //add item
    void Add(const T& item)
    {
      std::lock_guard<std::mutex> lock(sync_root_);
      auto target = const_cast<T*>(&item);
      data_.push_back(target);
    }

    //remove item
    void Remove(const T& item, bool clear = false)
    {
      std::lock_guard<std::mutex> lock(sync_root_);
      for (iterator_t i = data_.begin(); i != data_.end(); i++) {
        auto temp = *i;
        if (temp == &item) {
          if (clear)
            delete temp;
          data_.erase(i);
          break;
        }
      }
    }

    //remove all items
    void Clear(bool clear = false)
    {
      std::lock_guard<std::mutex> lock(sync_root_);
      if (clear) {
        for (iterator_t i = data_.begin(); i != data_.end(); i++)
          delete *i;
      }
      data_.clear();
    }
  };
}

#endif