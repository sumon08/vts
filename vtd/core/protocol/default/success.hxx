

#ifndef _SUCCESS_INCLUDE_H_
#define _SUCCESS_INCLUDE_H_


#include <commands.hxx>

namespace vts 
{
    namespace protocol
    {
        class SuccessReply: public command::ReplyBase
        {
            public: 
            SuccessReply(command::CommandId cmd_id, command::ChannelId channel_id)
            {
                Result(command::ExecutionResult::SUCCESS);
                Cmd(cmd_id & ~ (0x80));
                Channel(channel_id);
            }

        };
    }
}


#endif     //_SUCCESS_INCLUDE_H_