
#ifndef _EVENT_MANAGER_INTERNAL_H_
#define _EVENT_MANAGER_INTERNAL_H_



#include <events.hxx>
#include <msg.hxx>
#include <module.hxx>
#include<cstdint>



extern "C"{
	extern uint32_t _sevent_registry, _eevent_registry;
	}




namespace vts
{
    namespace event 
    {



        #ifndef CONFIG_MAXIMUM_NUMBER_OF_EVENT
            #define CONFIG_MAXIMUM_NUMBER_OF_EVENT      20
        #endif // DEBUG

        #ifndef CONFIG_EVENT_REGISTRY_AT_FLASH
            #define CONFIG_EVENT_REGISTRY_AT_FLASH  1
        #endif  //CONFIG_EVENT_REGISTRY_AT_FLASH








        class EventInternal : public MessageManager<EventBase>
        {
            private:

            #if 0
            Core::List<module::ModuleId> event_subscriber_list[CONFIG_MAXIMUM_NUMBER_OF_EVENT];
            #elif (CONFIG_EVENT_REGISTRY_AT_FLASH)
            const EventRegistry * ev_registry = (EventRegistry *) &_sevent_registry;
            int registry_count = ((int)_eevent_registry - (int)&_sevent_registry)/EVENT_REGISTRY_SIZE;
            #endif

            






            public:
            bool CheckRegistryEntry(module::ModuleId m_id, EventId ev_id);
            static void * EventThreadRunner(void * arg);
            EventInternal();



        };
    }
}







#endif