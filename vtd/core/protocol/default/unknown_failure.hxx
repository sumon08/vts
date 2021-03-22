








#ifndef _UNKNOWN_FAILURE_INCLUDE_H_
#define _UNKNOWN_FAILURE_INCLUDE_H_


#include <commands.hxx>

namespace vts 
{
    namespace protocol
    {
        class UnknownFailureReply: public command::ReplyBase
        {
            public: 
            UnknownFailureReply(command::CommandId cmd_id, command::ChannelId channel_id)
            {
                Result(command::ExecutionResult::UNKNOWN_FAILURE);
                Cmd(cmd_id & ~ (0x80));
            }
        };
    }
}


#endif     //_UNKNOWN_FAILURE_INCLUDE_H_