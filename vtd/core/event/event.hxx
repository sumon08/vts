



#ifndef EVENT_INCLUDE_H
#define EVENT_INCLUDE_H


#include <config.hxx>
#include <msg.hxx>






namespace vts
{
    namespace event
    {
        #ifndef CONFIG_MAXIMUM_NUMBER_OF_EVENT
            #define CONFIG_MAXIMUM_NUMBER_OF_EVENT      20
        #endif // DEBUG

        #ifndef CONFIG_EVENT_REGISTRY_AT_FLASH
            #warning "CONFIG_EVENT_REGISTRY_AT_FLASH is not set. Default to 1."
            #define CONFIG_EVENT_REGISTRY_AT_FLASH  1
        #endif  //CONFIG_EVENT_REGISTRY_AT_FLASH




        class EventManager: public MessageManager<EventBase>
        {

            private:

            

            static EventManager manager;



            public:
            static EventManager & GetInstance();
            bool CheckRegistryEntry(module::ModuleId m_id, EventId ev_id);
            static void * EventThreadRunner(void * arg);
            EventManager();

            #if 0
            bool Register(module::ModuleId & m_id, EventId & ev_id);
            #endif //
        };
    }

}



#endif // EVENT_INCLUDE_H
