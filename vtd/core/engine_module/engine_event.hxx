



#ifndef _ENGINE_EVENT_INCLUDE_H_
#define _ENGINE_EVENT_INCLUDE_H_



#include <events.hxx>
#include <core.hxx>

namespace vts
{
    namespace event 
    {
        
        


        #define ENGINE_STATE_CHANGED_EVENT_ID   MAKE_EVENT_ID(CONFIG_ENGINE_EVENT_OFFSET)
        #define ENGINE_EVENT_NAME               "Engine Event"


       

        class EventEngineStateChanged: public EventBase
        {
            
            EngineState _state; 


            public: 

            EventEngineStateChanged() : _state(EngineState::OFF)
            {
                Name(ENGINE_EVENT_NAME);
                Id(ENGINE_STATE_CHANGED_EVENT_ID);
            }
            EventEngineStateChanged(EngineState & state, int event_time) : _state(state)
            {
                Time(event_time);
                Name(ENGINE_EVENT_NAME);
                Id(ENGINE_STATE_CHANGED_EVENT_ID);
            }


            bool Post()
            {
                EventEngineStateChanged * ev = new EventEngineStateChanged();
                ev->_state = this->_state;
                ev->Time(this->Time());
                ev->Id(this->Id());
                return EventBase::Post(ev);          
            }
            
            bool Post(EngineState & state, int event_time)
            {
                Time(event_time);
                _state = state;
                return Post();
            }


            void State(EngineState state)
            {
                _state = state;
            }

            const EngineState State() const 
            {
                return _state;
            }
        };
    }
}




#endif      //_ENGINE_EVENT_INCLUDE_H_