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
    std::mutex* sync_root_;
    std::list<T*>* data_;

  public:
    List()
    {
      sync_root_ = new std::mutex();
      data_ = new std::list<T*>();
    }

    ~List()
    {
      RemoveAll(true);
      delete data_;
      delete sync_root_;
    }

  public:
    bool Contains(const T* item)
    {
      if (item == nullptr)
        return false;
      std::lock_guard<std::mutex> lock(*sync_root_);
      for (iterator_t i = data_->begin(); i != data_->end(); i++) {
        if (*i == item)
          return true;
      }
      return false;
    }

    bool Contains(const predicate_t& predicate) 
    {
      std::lock_guard<std::mutex> lock(*sync_root_);
      for (iterator_t i = data_->begin(); i != data_->end(); i++) {
        if (predicate(*i))
          return true;
      }
      return false;
    }

    //get item:T by predicate
    T* Find(const predicate_t& predicate)
    {
      std::lock_guard<std::mutex> lock(*sync_root_);
      for (iterator_t i = data_->begin(); i != data_->end(); i++) {
        auto temp = *i;
        if (predicate(temp))
          return temp;
      }
      return nullptr;
    }

    //add item
    void Add(T* item)
    {
      if (item == nullptr)
        return;
      std::lock_guard<std::mutex> lock(*sync_root_);
      data_->push_back(item);
    }

    //remove item
    void Remove(T* item, bool clear = false)
    {
      if (item == nullptr)
        return;
      std::lock_guard<std::mutex> lock(*sync_root_);
      for (iterator_t i = data_->begin(); i != data_->end(); i++) {
        auto temp = *i;
        if (temp == item) {
          if (clear)
            ClearObject(temp);
          data_->erase(i);
          break;
        }
      }
    }

    //remove item at
    void RemoveAt(const predicate_t& predicate, bool clear = false)
    {
      std::lock_guard<std::mutex> lock(*sync_root_);
      for (iterator_t i = data_->begin(); i != data_->end(); i++) {
        auto temp = *i;
        if (predicate(temp)) {
          if (clear)
            ClearObject(temp);
          data_->erase(i);
          break;
        }
      }
    }

    //remove all items
    void RemoveAll(bool clear = false)
    {
      std::lock_guard<std::mutex> lock(*sync_root_);
      if (clear) {
        for (iterator_t i = data_->begin(); i != data_->end(); i++)
          ClearObject(*i);
      }
      data_->clear();
    }
  };
}

#endif