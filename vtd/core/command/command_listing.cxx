


#include <default.hxx>
#include <parser_registry.hxx>
#include <command_config.h>

namespace vts
{
    namespace protocol 
    {

        class TestCommand: public command::CommandBase
        {
            public: 
            TestCommand()
            {
                //Channel()
            }
        };        

        Core::unique_ptr<command::CommandBase> TestParser(const uint8_t * cmd_data, uint16_t length)
        {
            //if(length < 5)
            //{
            //    InsufficientParamReply * ins = new InsufficientParamReply(CONFIG_COMMAND_ENGINE_STATUS_ID, CONFIG_ENGINE_CHANNEL_ID);
            //    ins->Provided(length);
            //    ins->Required(5);
            //    Core::unique_ptr<command::CommandBase> p_base(ins);
            //    return p_base;
            //}
            //else if(length > 5)
            //{
            //    ParamOverloadReply * param = new ParamOverloadReply(CONFIG_COMMAND_ENGINE_STATUS_ID, CONFIG_ENGINE_CHANNEL_ID);
            //    param->Provided(length);
            //    param->Required(5);
            //    Core::unique_ptr<command::CommandBase> p_base(param);
            //    return p_base;
            //}
            Core::unique_ptr<command::CommandBase> new_command;
            return new_command;
        }

        volatile const ParserRegistry test_cmd_parser PARSER_REGISTRY = 
        {
            .channel = 1,
            .cmd = 1,
            .protocol = 1,
            .callback = TestParser
        };
        
    }
}

/******* CMD STRINGS ********/
const char engine_cmd_string                        []= "engine";
const char engine_lock_string                       []= "elock";
const char engine_unlock_string                     []= "eunlock";
const char enable_engine_service_string             []= "en_engine_ser";
const char disable_engine_service_string            []= "dis_engine_ser";                                                                
const char ac_status_string                         []= "ac";
const char enable_ac_service_string                 []= "en_ac_ser";
const char disable_ac_service_string                []= "dis_ac_ser";
const char ac_low_on_string                         []= "ac_low_on";
const char ac_high_on_string                        []= "ac_high_on";
const char ac_set_off_string                        []= "ac_set_off";
const char door_status_string                       []= "door";
const char enable_door_sevice_string                []= "en_door_ser";
const char disable_door_sevice_string               []= "dis_door_ser";
const char set_door_polarity_string                 []= "door_pol";
const char panic_status_string                      []= "panic";
const char enable_panic_service_string              []= "en_panic_ser";
const char disable_panic_service_String             []= "dis_panic_ser";                                                            
const char over_speed_violation_string              []= "overspeed";
const char enable_overspeed_service_string          []= "en_overspeed_ser";
const char disable_overspeed_service_string         []= "dis_overspeed_ser";