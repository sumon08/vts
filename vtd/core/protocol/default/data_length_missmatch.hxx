

#ifndef _DATA_LENGTH_MISSMATCH_REPLY_INCLUDE_H_
#define _DATA_LENGTH_MISSMATCH_REPLY_INCLUDE_H_


#include <commands.hxx>


namespace vts
{
    namespace protocol
    {




        class DataLengthMissmatchReply : public command::ErrorBase
        {
            uint16_t provided_length;
            uint16_t actual_length;
            const uint8_t error_id = CONFIG_DATA_LENGTH_MISSMATCH_ERROR_ID;



            uint16_t GetError(uint8_t * buffer, unsigned int length)
            {
                uint16_t index_counter = 0;
                if(length > 4)
                {
                    buffer[index_counter++] = error_id;
                    buffer[index_counter++] = (uint8_t)(actual_length & 0xFF); 
                    buffer[index_counter++] = (uint8_t)((actual_length >> 8) & 0xFF);
                    buffer[index_counter++] = (uint8_t)(provided_length & 0xFF); 
                    buffer[index_counter++] = (uint8_t)((provided_length >> 8) & 0xFF);
                    return index_counter;
                }
                return CONFIG_MAKE_PACKET_BUFFER_OVERFLOW_RETURN_VALUE;
            }

            public: 
            DataLengthMissmatchReply(command::CommandId cmd_id, command::ChannelId channel_id)
            {
                Result(command::ExecutionResult::PARSING_ERROR);
                Cmd(cmd_id & ~0x80);
                Channel(channel_id);
            }

            

            uint16_t MakePacket(uint8_t * buffer, uint16_t length)
            {
                std::printf("Data length missmatch.\n");
                return GetError(buffer, length);
            }

            void ActualLength(uint16_t length)
            {
                actual_length = length;
            }


            const uint16_t ActualLength() const
            {
                return actual_length;
            }



            void ProvidedLength(uint16_t length)
            {
                provided_length = length;
            }


            const uint16_t ProvidedLength() const
            {
                return provided_length;
            }
        };
    }
}




#endif //_DATA_LENGTH_MISSMATCH_REPLY_INCLUDE_H_
