


#ifndef _BAD_FORMAT_INCLUDE_H_
#define _BAD_FORMAT_INCLUDE_H_

#include <config.hxx>
#include <commands.hxx>

namespace vts
{
    namespace protocol 
    {
        class BadFormatedReply : public command::ErrorBase
        {
            const uint8_t error_id = CONFIG_BAD_FORMAT_ERROR_ID; 
            public: 
            BadFormatedReply(command::CommandId cmd_id, command::ChannelId channel_id)
            {
                Result(command::ExecutionResult::PARSING_ERROR);
                Cmd(cmd_id & ~0x80);
                Channel(channel_id);
            }

            uint16_t MakePacket(uint8_t * buffer, uint16_t length)
            {
                uint16_t index_counter = 0;
                if(length > 2)
                {
                    buffer[index_counter++] = error_id;
                    return index_counter;
                }
                return CONFIG_MAKE_PACKET_BUFFER_OVERFLOW_RETURN_VALUE;
            }
        };
    }
}


#endif 