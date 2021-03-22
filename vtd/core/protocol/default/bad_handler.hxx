



#ifndef _BAD_HANDLER_INCLUDE_H_
#define _BAD_HANDLER_INCLUDE_H_


#include <commands.hxx>

namespace vts 
{
    namespace protocol
    {
        class BadHandlerReply: public command::ErrorBase
        {
            //const uint8_t error_id = CONFIG_BAD;
            public: 
            BadHandlerReply(command::CommandId cmd_id, command::ChannelId channel_id)
            {
                Result(command::ExecutionResult::BAD_HANDLER);
                Cmd(cmd_id & ~ (0x80));
            }
        };
    }
}


#endif     //_BAD_HANDLER_INCLUDE_H_