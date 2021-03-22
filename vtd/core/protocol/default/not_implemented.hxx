#ifndef _NOT_IMPLEMENTED_INCLUDE_H_
#define _NOT_IMPLEMENTED_INCLUDE_H_


#include <commands.hxx>

namespace vts 
{
    namespace protocol
    {
        class NotImplementedReply: public command::ErrorBase
        {
            const uint8_t error_id = CONFIG_NOT_IMPLEMENTED_ERROR_ID;
            public: 
            NotImplementedReply(command::CommandId cmd_id, command::ChannelId channel_id)
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


#endif     //_NOT_IMPLEMENTED_INCLUDE_H_