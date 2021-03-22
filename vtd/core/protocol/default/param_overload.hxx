

#ifndef _PARAM_OVERLOAD_INCLUDE_H_
#define _PARAM_OVERLOAD_INCLUDE_H_


#include <commands.hxx>

namespace vts 
{
    namespace protocol
    {
        class ParamOverloadReply: public command::ErrorBase
        {
            const uint8_t error_id = CONFIG_PARAM_OVERLOADED_ERROR_ID;
            uint16_t required;
            uint16_t have;
            public: 
            ParamOverloadReply(command::CommandId cmd_id, command::ChannelId channel_id)
            {
                Result(command::ExecutionResult::PARSING_ERROR);
                Cmd(cmd_id & ~ (0x80));
                Channel(channel_id);
            }

           uint16_t MakePacket(uint8_t * buffer, uint16_t length)
            {
                uint16_t index_counter = 0;
                if(length > 0)
                {
                    buffer[index_counter++] = error_id;
                    buffer[index_counter++] = (uint8_t)(required & 0xFF); 
                    buffer[index_counter++] = (uint8_t)((required >> 8) & 0xFF);
                    buffer[index_counter++] = (uint8_t)(have & 0xFF); 
                    buffer[index_counter++] = (uint8_t)((have >> 8) & 0xFF);
                    return index_counter;
                }
                return CONFIG_MAKE_PACKET_BUFFER_OVERFLOW_RETURN_VALUE;
            }

            void Required(uint16_t length)
            {
                required = length;
            }

            const uint16_t Required() const
            {
                return required;
            }

            void Provided(uint16_t length)
            {
                have = length;
            }

            const uint16_t Provided() const 
            {
                return have;
            }




        };
    }
}


#endif     //_SUCCESS_INCLUDE_H_