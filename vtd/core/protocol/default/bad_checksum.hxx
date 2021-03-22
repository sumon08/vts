


#ifndef _BAD_CHECKSUM_INCLUDE_H_
#define _BAD_CHECKSUM_INCLUDE_H_

#include <config.hxx>
#include <commands.hxx>

namespace vts
{
    namespace protocol 
    {
        class BadChecksumReply : public command::ErrorBase
        {
            uint8_t packet_checksum; //Checksum from packet
            uint8_t calculated_checksum;
            const uint8_t error_id = CONFIG_BAD_CHECKSUM_ERROR_ID;

            uint16_t GetError(uint8_t * buffer, unsigned int length)
            {
                uint16_t index_counter = 0;
                if(length > 2)
                {
                    buffer[index_counter++] = error_id;
                    buffer[index_counter++] = packet_checksum;
                    buffer[index_counter++] = calculated_checksum;
                    return index_counter;
                }
                return CONFIG_MAKE_PACKET_BUFFER_OVERFLOW_RETURN_VALUE;
            }


            public:
            BadChecksumReply(command::CommandId cmd_id, command::ChannelId channel_id)
            {
                Result(command::ExecutionResult::PARSING_ERROR);
                Cmd(cmd_id);
                Channel(channel_id);
            }

            

            void PacketChecksum(uint8_t checksum)
            {
                packet_checksum = checksum;
            }

            void CalculatedChecksum(uint8_t checksum)
            {
                calculated_checksum = checksum;
            }

            uint16_t MakePacket(uint8_t * buffer, uint16_t length)
            {
                return GetError(buffer, length);
            }

        };
    }
}



#endif //_BAD_CHECKSUM_INCLUDE_H_