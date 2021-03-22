




#ifndef _UNKNOWN_COMMAND_INCLUDE_H_
#define _UNKNOWN_COMMAND_INCLUDE_H_


#include <commands.hxx>

namespace vts 
{
    namespace protocol
    {
        class UnknownCommandReply: public command::ErrorBase
        {
            const uint8_t error_id = CONFIG_UNKNOWN_COMMAND_ERROR_ID;
            public: 
            UnknownCommandReply(command::CommandId cmd_id, command::ChannelId channel_id)
            {
                Result(command::ExecutionResult::PARSING_ERROR);
                Cmd(cmd_id & ~ (0x80));
                Channel(channel_id);
            }

            uint16_t MakePacket(uint8_t * buffer, uint16_t length)
            {
                if(length > 0)
                {
                    buffer[0] = error_id;
                    return 1;
                }
                return CONFIG_MAKE_PACKET_BUFFER_OVERFLOW_RETURN_VALUE;
            }
        };
    }
}


#endif     //_UNKNOWN_COMMAND_INCLUDE_H_