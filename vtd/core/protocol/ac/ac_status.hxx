

#ifndef _AC_INCLUDE_H_
#define _AC_INCLUDE_H_


#include <commands.hxx>
#include <parser_registry.hxx>
#include <ac_event.hpp>

namespace vts
{
    namespace protocol
    {
        class AcStatusCmd : public command::CommandBase
        {
            int unix_time;
            uint8_t length;
            event::AcState state;


            public: 
            void SetTime(int time)
            {
                unix_time = time;
            }


        };

        Core::unique_ptr<command::CommandBase> AcStatusParser(const char * cmd_data, unsigned int length)
        {
            AcStatusCmd * p_data = new AcStatusCmd();

            

            union  
            {
                struct  
                {
                    int time;
                    event::AcState state; 
                };

                uint8_t raw[10];
            }local;

            memcpy(local.raw, cmd_data, length);
            p_data->SetTime(local.time);
            Core::unique_ptr<command::CommandBase> p_base(p_data);
            return p_base;
        }


        
    }
}


#endif