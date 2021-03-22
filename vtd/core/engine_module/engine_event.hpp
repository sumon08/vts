



#ifndef _ENGINE_EVENT_INCLUDE_H_
#define _ENGINE_EVENT_INCLUDE_H_



#include <events.hxx>
#include <memory.hxx>

namespace vts
{
    namespace event 
    {
        
        


        #define ENGINE_STATE_CHANGED_EVENT_ID   MakeEventId<CONFIG_ENGINE_EVENT_OFFSET>::value
        #define ENGINE_EVENT_NAME               "Engine Event"


       

        class EventEngineStateChanged: public EventBase
        {
            
            EngineState _state; 


            public: 

            EventEngineStateChanged() : _state(EngineState::OFF)
            {
                SetName(ENGINE_EVENT_NAME);
                SetId(ENGINE_STATE_CHANGED_EVENT_ID);
            }
            EventEngineStateChanged(EngineState & state, int event_time) : _state(state)
            {
                SetTime(event_time);
                SetName(ENGINE_EVENT_NAME);
                SetId(ENGINE_STATE_CHANGED_EVENT_ID);
            }


            bool Post()
            {
                Core::SmartPtr<EventEngineStateChanged> actual_ev_ptr = *this;;

                Core::SmartPtr<EventBase> base_ptr = Core::ConvertPointer<EventEngineStateChanged, EventBase>(actual_ev_ptr);

                EventManager & evman = EventManager::GetInstance();

                return evman.Post(base_ptr);
            }
            
            bool Post(EngineState & state, int event_time)
            {
                SetTime(event_time);
                _state = state;
                Post();
            }

            EngineState GetState()
            {
                return _state;
            }
        };


        
    }
}




#endif      //_ENGINE_EVENT_INCLUDE_H_