


#ifndef _AC_INCLUDE_H_
#define _AC_INCLUDE_H_


#include <adapter.hxx>
#include <module.hxx>
#include <ac_sensor.hxx>
#include <engine_event.hxx>
#include <filter.hxx>
#include <ac_event.hxx>
#include <wdtimer.hxx>
#include <commands.hxx>
#ifdef __LINUX__
#include <cstring>
#include <cstdio>
#else 
#include <cxx/cstdio>
#include <cxx/cstring>
#endif

namespace vts
{

    //#define CONFIG_AC_MODULE_ID    0x02
    #define AC_SAMPLE_TIMER_INTERVAL 5


    class Ac : public module::Module
    {
        private:       
        int adc_value1, adc_value2, adc_off, on_off_reference,type;
        adapter::AcSensor sensor; 
        event::EngineState eng_state;
        event::EventAcStateChanged ac_state;
        int ac_type;

        static Ac ac_instance;
        filter ac_filter;
        adapter::Thread pin_monitor_thread;
        
        
        float ac_adc;
        

        public: 
        Ac() : Module(CONFIG_AC_MODULE_ID), ac_filter(1.0, 10.0, 60000.0, 0.0005), pin_monitor_thread(AcPinMonitor)
        {
            Register(EventCallback);
            Register(CommandCallback);
            pin_monitor_thread.SetAttribute(1000, 100);
            if(pin_monitor_thread.Run() < 0)
            {
                //std::printf("Ac monitor thread running failed. Do something or restart.\n");
            }
        }

        static void * AcPinMonitor(void *)
        {
            
            timespec time; // import time from time module

            while(1)
            {
                ac_instance.ac_adc = ac_instance.ac_filter.GetShortFiltered(ac_instance.sensor.ReadAdc(), ac_instance.ac_adc);

                //lambda function.
                auto State = [](int _v)->event::AcState{
                    event::AcState state = event::AcState::OFF;
                    switch(_v)
                    {
                        case 1:
                            state = event::AcState::ON;
                        break;
                        default: 
                            state = event::AcState::OFF;
                        break;
                    }
                    return state;
                };
                clock_gettime(CLOCK_REALTIME, &time);
                if((( ac_instance.ac_adc > ac_instance.on_off_reference) && (ac_instance.ac_type == 0)) && (ac_instance.eng_state == event::EngineState::ON))
                {                    
                    ac_instance.ac_state.Post(State(1),time.tv_sec); 
                }
                else if(((ac_instance.ac_adc < ac_instance.on_off_reference) && (ac_instance.ac_type == 1)) && (ac_instance.eng_state == event::EngineState::ON))
                {
                    ac_instance.ac_state.Post(State(1),time.tv_sec); 
                }
                else
                {
                    ac_instance.ac_state.Post(State(0),time.tv_sec); 
                }
            }
            return 0;
        }

        static Ac & GetInstance()
        {
            // open engine related device here. 
            
            return ac_instance;
        }


        static bool EventCallback(const event::EventBase & ev_base)
        {
            switch(ev_base.Id())
            {
                case ENGINE_STATE_CHANGED_EVENT_ID:
                {
                    event::EventEngineStateChanged & temp = (event::EventEngineStateChanged &) ev_base;
                    ac_instance.eng_state = temp.State();
                    std::printf("Ac module received Engine On event.\n");
                }
                break;
                default:
                    // nothing;
                break;
            }
            return true;
        }


        static command::ExecutionResult CommandCallback(const command::CommandBase * cmd_base, Core::unique_ptr<command::ReplyBase> & reply)
        {
            switch(cmd_base->Cmd())
            {
                case CONFIG_CMD_AC_STATUS: 
                {                    
                    //CommandBase reply_command;
                    //reply
                }
                break;
                case CONFIG_CMD_QUERY_AC_STATUS: 
                {
                    //CommandBase reply_command;
                    //reply
                }
                break;
                case CONFIG_CMD_ENABLE_AC_SERVICE: 
                {
                    //CommandBase reply_command;
                    //reply
                }
                break;
                case CONFIG_CMD_DISABLE_AC_SERVICE: 
                {
                    //CommandBase reply_command;
                    //reply
                }
                break;
                case CONFIG_CMD_SET_AC_LOWON: 
                {
                    //adc_value1 = ac_adc;
                    //softprint_P("setting.ac_sensor_data.Value1 : %f\r\n",adc_value1);
                    //UpdateMemory(MEMLOCATION0);

                    //CommandBase reply_command;
                    //reply
                }
                break;
                case CONFIG_CMD_SET_AC_HIGHON: 
                {
                    //CommandBase reply_command;
                    //reply
                }
                break;
                case CONFIG_CMD_SET_AC_OFF: 
                {
                    //CommandBase reply_command;
                    //reply
                }
                break;
            }
            return command::ExecutionResult::UNKNOWN_FAILURE;
        } 
    };
}

#endif      // _ENGINE_INCLUDE_H_ 