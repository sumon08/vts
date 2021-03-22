

#include <config.hxx>
#include <engine_status.hxx>
#include <protocol.hxx>
#include <default.hxx>
#include <utility.hxx>


namespace vts 
{
    namespace protocol 
    {

        

        Core::unique_ptr< command::CommandBase> ESparser(const uint8_t * cmd_data, uint16_t length)
        {
            if(length < 5)
            {
                InsufficientParamReply * ins = new InsufficientParamReply(CONFIG_COMMAND_ENGINE_STATUS_ID, CONFIG_ENGINE_CHANNEL_ID);
                ins->Provided(length);
                ins->Required(5);
                Core::unique_ptr<command::CommandBase> p_base(ins);
                return p_base;
            }
            else if(length > 5)
            {
                ParamOverloadReply * param = new ParamOverloadReply(CONFIG_COMMAND_ENGINE_STATUS_ID, CONFIG_ENGINE_CHANNEL_ID);
                param->Provided(length);
                param->Required(5);
                Core::unique_ptr<command::CommandBase> p_base(param);
                return p_base;
            }
            EngineStatusCmd * p_data = new EngineStatusCmd();

            

            union  
            {
                struct  
                {
                    unsigned int time;
                    uint8_t state; 
                };
                uint8_t raw[5];
            }local;


            memcpy(local.raw, cmd_data, length);

            //std::printf("Local TIme: %08X, %08X", local.time, Core::ByteSwap(local.time));
            p_data->Time(Core::ByteSwap(local.time));
            p_data->State(static_cast<event::EngineState>(local.state));
            Core::unique_ptr<command::CommandBase> p_base(p_data);
            return p_base;
        }






        Core::unique_ptr<command::CommandBase> EngQueryCmdParser(const uint8_t * buffer, uint16_t length)
        {
            EngineStateQueryCommand * query = new EngineStateQueryCommand();
            Core::unique_ptr<command::CommandBase> retptr(query);
            return retptr;
        }




        volatile const ParserRegistry en_status_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x81,
            .protocol = 1,
            .callback = ESparser
        };
        volatile const ParserRegistry engine_status_ack_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x01,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry engine_status_query_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x83,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry engine_status_query_ack_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x03,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry engine_lock_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x84,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry engine_lock_ack_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x04,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry engine_unlock_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x85,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry engine_unlock_ack_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x05,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry engine_enable_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x86,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry engine_enable_ack_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x06,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry engine_disable_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x87,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry engine_disable_ack_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x07,
            .protocol = 1,
            .callback = NULL
        };


        volatile const ParserRegistry query_status_parser PARSER_REGISTRY = 
        {
            .channel = 0x02,
            .cmd = 0x82,
            .protocol = 1,
            .callback = EngQueryCmdParser
        };

        
        
    }
}





uint32_t Core::ByteSwap(uint32_t target)
{
    uint32_t y = (target >> 24) & 0xff;
    y |= (target >> 8)  & 0xff00;
    y |= (target << 8)  & 0xff0000;
    y |= (target << 24) & 0xff000000u;
    return y;
}