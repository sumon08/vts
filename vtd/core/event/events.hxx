

#ifndef _EVENTS_INCLUDE_H
#define _EVENTS_INCLUDE_H



#include <cstring>
#include <msg.hxx>

namespace vts
{

   namespace event
   {

        #ifndef CONFIG_EVENT_NAME_LENGTH
            #warning "CONFIG_EVENT_NAME_LENGTH is not set. Default to 16."
            #define CONFIG_EVENT_NAME_LENGTH    16
        #endif


        #define MAKE_EVENT_ID(x)        (CONFIG_EVENT_ID_BASE  + x)


        #define EVENT_REGISTRY          __attribute__((section(".event_registry")))
        #define EVENT_REGISTRY_SIZE     4

        struct EventRegistry
        {
            uint8_t module_id;
            uint16_t event_id;
        } __attribute__((aligned(EVENT_REGISTRY_SIZE)));





        typedef int EventId;


        #define NO_EVENT 0x00;



         enum class EngineState
        {
            ON,
            OFF
        };

        enum class AcState
        {
            ON,
            OFF
        };

        enum class PanicState
        {
            DEACTIVE,
            ACTIVE
        };

        enum class BatteryState
        {
            DISCONNECTED,
            CONNECTED
        };
        enum class OverSpeedState
        {
            NOTVIOLATED,
            VIOLATED
        };








        
        class EventBase: public MessageBase
        {
            private:
            EventId _id;
            int event_time;
            char _name[CONFIG_EVENT_NAME_LENGTH];


            protected: 

            static bool Post(EventBase * ev);
            
            EventBase();

            EventBase(EventId id, const char * name);

            public: 


            ~EventBase();


            void Name(const char * name);

            void Id(EventId id);

            const EventId Id() const; 

            void Name(char * buffer, int len);

            void Time(int time);

            const int Time() const;
        };


   }

}



#endif  //_EVENTS_INCLUDE_H