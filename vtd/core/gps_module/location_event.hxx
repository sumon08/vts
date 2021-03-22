


#ifndef _LOCATION_EVENT_INCLUDE_H_
#define _LOCATION_EVENT_INCLUDE_H_

#include <config.hxx>
#include <events.hxx>

namespace vts
{
    namespace event 
    {


        #define GPS_EVENT_ID        MAKE_EVENT_ID(CONFIG_LOCATION_EVENT_OFFSET)
        #define GP


        class LocationEvent : public EventBase
        {
             
        };
    }
}

#endif  //_LOCATION_EVENT_INCLUDE_H_