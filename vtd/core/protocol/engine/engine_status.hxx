

#ifndef _ENGINE_STATUS_INCLUDE_H_
#define _ENGINE_STATUS_INCLUDE_H_

#include <config.hxx>
#include <commands.hxx>
#include <parser_registry.hxx>
#include <engine_event.hxx>

namespace vts
{
    namespace protocol
    {
        class EngineStatusCmd : public command::CommandBase
        {
            int unix_time;
            uint8_t length;
            event::EngineState state;


            public: 

            EngineStatusCmd()
            {
            }


            void Time(int time)
            {
                unix_time = time;
            }

            const int Time() const
            {
                return unix_time;
            }


            void State(event::EngineState _state)
            {
                state = _state;
            }

            const event::EngineState State() const
            {
                return state;
            }

            uint16_t MakePacket(uint8_t * buffer, uint16_t length)
            {
                uint16_t index_counter = 0;
                if(length > 4)
                {
                    
                    buffer[index_counter++] = (uint8_t)Time() & 0xFF;
                    buffer[index_counter++] = (uint8_t)(Time() >> 8) & 0xFF;
                    buffer[index_counter++] = (uint8_t)(Time() >> 16) & 0xFF;
                    buffer[index_counter++] = (uint8_t)(Time() >> 24) & 0xFF;
                    buffer[index_counter++] = static_cast<uint8_t>(State());
                    return index_counter;
                }
                return CONFIG_MAKE_PACKET_BUFFER_OVERFLOW_RETURN_VALUE;
            }


        };

        class CommandWithNoData;
        using EngineStateQueryCommand = CommandWithNoData;
        
    }
}


#endif      // _ENGINE_STATUS_INCLUDE_H_