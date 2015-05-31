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
    static Engine* instance_;

  public:
    //get engine instance
    //start engine first
    static Engine* Instance();

    //start engine
    static Engine* Start();

    //stop engine
    static void Stop();

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
    friend class Getter::Engine;
  };
}

#endif