


#ifndef _GPS_INCLUDE_H_
#define _GPS_INCLUDE_H_

#include <config.hxx>
#include <module.hxx>

namespace vts
{
    class GpsModule : public module::Module
    {
        private: 

        static GpsModule gps_instance;

        GpsModule() : Module(CONFIG_GPS_MODULE_ID) 
        {
            Register(EventCallback);
            Register(CommandCallback);
        }



        static bool EventCallback(const event::EventBase & event_data)
        {
            switch(event_data.Id())
            {
                case CONFIG_LOCATION_EVENT_OFFSET:
                break;
            }
            return true;
        }

        static command::ExecutionResult CommandCallback(const command::CommandBase * cmd, Core::unique_ptr<command::ReplyBase> & reply)
        {
            switch(cmd->Cmd())
            {
                //case

                default: 
                    return command::ExecutionResult::NOT_HANDLED;
                break;
            }
            return command::ExecutionResult::UNKNOWN_FAILURE;
        }


    };
}

#endif //_GPS_INCLUDE_H_