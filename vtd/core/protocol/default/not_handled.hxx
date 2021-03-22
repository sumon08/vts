

#ifndef _NOT_HANDLED_INCLUDE_H_
#define _NOT_HANDLED_INCLUDE_H_


#include <commands.hxx>

namespace vts
{
    namespace protocol
    {
        class NotHandledReply : public command::ErrorBase 
        {
            public: 
            NotHandledReply(command::CommandId cmd_id, command::ChannelId channel_id)
            {
                Result(command::ExecutionResult::NOT_HANDLED);
                Cmd(cmd_id & ~0x80);
                Channel(channel_id);
            }
        };
    }
}


#endif