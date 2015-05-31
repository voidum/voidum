#ifndef _VOIDUM_GETTER_
#define _VOIDUM_GETTER_

#include "list.h"

namespace voidum 
{
  class Getter
  {
  public:
    class Engine
    {
    public:
      class GetHosts
      {
        friend class Host;
      private:
        List<Host>* operator () ();
      };

      class GetDrivers
      {
        friend class Driver;
      private:
        List<Driver>* operator () ();
      };
    };
  };
}

#endif