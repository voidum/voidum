#ifndef _VOIDUM_ENGINE_
#define _VOIDUM_ENGINE_

#include "base.h"
#include "list.h"
#include "getter.h"

namespace voidum
{
  class Host;
  class Driver;
  class Setting;
  class Worker;

  //engine
  //todo: consider thread safe ctor/dtor
  class VOIDUM_API Engine : Uncopiable
  {
  private:
    static std::once_flag* once_flag_;
    static Engine* instance_;

  public:
    //get engine instance
    static Engine* Instance();

  private:
    List<Host>* hosts_;
    List<Driver>* drivers_;
    Worker* worker_;
    Setting* setting_;

  private:
    Engine();

  public:
    ~Engine();

  public:
    //get worker
    Worker* GetWorker();

    //set worker
    void SetWorker(Worker* worker);

    //get setting
    Setting* GetSetting();

  public:
    //start engine
    void Start();

    //stop engine
    void Stop();

  public:
    friend class Getter::Engine;
  };
}

#endif