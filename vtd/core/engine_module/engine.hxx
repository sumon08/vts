


#ifndef _ENGINE_INCLUDE_H_
#define _ENGINE_INCLUDE_H_

#include <config.hxx>
#include <module.hxx>
#include <engine_sensor.hxx>
#include <engine_event.hxx>
#include <engine_status.hxx>
#ifdef __LINUX__
#include <cstdio>
#else 
#include <cxx/cstdio>
#endif

namespace vts
{

//    #define CONFIG_ENGINE_MODULE_ID    0x01

    #define CONFIG_ENGINE_SENSOR_TIMER_ID 11




    class Engine : public module::Module
    {
        private: 
        adapter::EngineSensor sensor; 
        static Engine engine_instance;
        event::EngineState previous_state = event::EngineState::OFF;


        adapter::Thread pin_monitor_thread;




        static void *  SensorMonitor(void * param)
        {
            static int count = 0;
            while(1)
            {
                if(engine_instance.sensor.IsOn() && engine_instance.previous_state == event::EngineState::OFF)
                {                
                    count++;
                    if(count == 10)
                    {
                        count = 0;
                        engine_instance.previous_state = event::EngineState::ON;
                        event::EventEngineStateChanged ev;
                        ev.State(event::EngineState::ON);
                        struct timespec tim;
                        clock_gettime(CLOCK_REALTIME, &tim);
                        ev.Time(tim.tv_sec);
                        if(!ev.Post())
                        {
                            //std::printf("Failled..\n");
                        }
                    }
                }
                
                else if((!engine_instance.sensor.IsOn()) && (engine_instance.previous_state == event::EngineState::ON))
                {
                    count++;
                
                    if(count == 10)
                    {
                        count = 0;
                        engine_instance.previous_state = event::EngineState::OFF;
                        event::EventEngineStateChanged ev;
                        ev.State(event::EngineState::OFF);
                        struct timespec tim;
                        clock_gettime(CLOCK_REALTIME, &tim);
                        ev.Time(tim.tv_sec);
                        if(!ev.Post())
                        {
                            //std::printf("Failled..\n");
                        }
                    }
                }

                else 
                {
                    //std::printf("Engine OFF\n");

                    count = 0;
                }

                sleep(1);
            }
            
        }

        Engine() : Module(CONFIG_ENGINE_MODULE_ID)
        {
            if(!sensor.IsOpen() )
                std::printf("Opening engine sensor failed.\n");
            else
            {
                pin_monitor_thread.SetStartRoutine(SensorMonitor);
                pin_monitor_thread.Run();
            }
        }
        public: 

        

        static Engine & GetInstance()
        {
            // open engine related device here. 


            
            engine_instance.Register(EventCallback);
            engine_instance.Register(CommandCallback);

            return engine_instance;
        }


        static bool EventCallback(const event::EventBase & ev_base)
        {
            switch(ev_base.Id())
            {
                case ENGINE_STATE_CHANGED_EVENT_ID: 
                {
                    //std::printf("Engine State event received.\n");
                    event::EventEngineStateChanged & actual_event = (event::EventEngineStateChanged &) ev_base;
                    protocol::EngineStatusCmd * status_cmd;
                    #if (CONFIG_REPORT_DEVICE_COMMAND_TO_TCP)
                    //status_cmd = new protocol::EngineStatusCmd(); // this allocation will delete later using unique pointer
                    //status_cmd->State(actual_event.State());
                    //status_cmd->Time(actual_event.Time());
                    //status_cmd->Port(command::PortType::PORT_TCP);
                    //status_cmd->Post(status_cmd);
                    #endif
                    #if (CONFIG_REPORT_DEVICE_COMMAND_TO_CONSOLE)
                    status_cmd = new protocol::EngineStatusCmd(); // this allocation will delete later using unique pointer
                    status_cmd->State(actual_event.State());
                    status_cmd->Time(actual_event.Time());
                    status_cmd->CommandFlow(command::CommandFlowType::OUTGOING);
                    status_cmd->Port(command::PortType::PORT_SERIAL);
                    status_cmd->Post(status_cmd);
                    #endif
                }
                break;
                default:
                    // nothing;
                break;
            }
            return true;
        }


        static command::ExecutionResult CommandCallback(const command::CommandBase * cmd_base, Core::unique_ptr<command::ReplyBase> & reply_buffer)
        {
            //std::printf("Engin module callback called.\n");
            switch(cmd_base->Cmd())
            {
                case 0x81: 
                {
                    //protocol::EngineStatusCmd * cmd = (protocol::EngineStatusCmd *)cmd_base;
                    //std::printf("Time: %u State: %d\n", cmd->Time(), cmd->State());

                    
                    return command::ExecutionResult::SUCCESS;
                    
                }
                break;
                //case CONFIG_COM
                default:
                    return command::ExecutionResult::NOT_HANDLED;
                break;
            }

            return command::ExecutionResult::UNKNOWN_FAILURE;
        }        

    };


    volatile const event::EventRegistry eng_status_event EVENT_REGISTRY = 
    {
        .module_id = CONFIG_ENGINE_MODULE_ID,
        .event_id = ENGINE_STATE_CHANGED_EVENT_ID
    };

}

#endif      // _ENGINE_INCLUDE_H_ 