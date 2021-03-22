



#ifndef _AC_EVENT_INCLUDE_H_
#define _AC_EVENT_INCLUDE_H_

#include <config.hxx>
#include <events.hxx>
#include <memory.hxx>

namespace vts
{
    namespace event 
    {
        
        


        #define AC_STATE_CHANGED_EVENT_ID    MAKE_EVENT_ID(CONFIG_AC_EVENT_OFFSET)
        #define AC_EVENT_NAME               "Ac Event"


       

        class EventAcStateChanged: public EventBase
        {
            
            AcState _state; 


            public: 

            EventAcStateChanged() : _state(AcState::OFF)
            {
                Name(AC_EVENT_NAME);
                Id(AC_STATE_CHANGED_EVENT_ID);
            }
            EventAcStateChanged(AcState & state, int event_time) : _state(state)
            {
                Time(event_time);
                Name(AC_EVENT_NAME);
                Id(AC_STATE_CHANGED_EVENT_ID);
            }


            bool Post()
            {
                EventAcStateChanged * ac_state = new EventAcStateChanged();

                *ac_state = *this;
                //Core::unique_ptr<EventBase> base(ac_state);
                return EventBase::Post(ac_state);
            }
            
            bool Post(AcState state, int event_time)
            {
                Time(event_time);
                _state = state;
                return Post();
            }

            void State(AcState state)
            {
                _state = state;
            }

            const AcState State() const
            {
                return _state;
            }
        };


        
    }
}




#endif      //_ENGINE_EVENT_INCLUDE_H_