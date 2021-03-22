


#include <ac.hxx>
#include <command_config.h>
#include <core.hxx>

namespace vts 
{
    Ac Ac::ac_instance;

    bool InitAcInstance()
    {
        Ac & ac_man = Ac::GetInstance();
        return ac_man.Run(2048, 100);
    }



    volatile const command::CommandRegistry ac_status CMD_REGISTRY =
    {
        .module_id = CONFIG_AC_MODULE_ID,
        .channel_id = CONFIG_AC_CHANNEL_ID,
        .cmd = CONFIG_CMD_AC_STATUS,
        .cmd_string = ac_status_string
    };

    volatile const command::CommandRegistry query_ac_status CMD_REGISTRY =
    {
        .module_id = CONFIG_AC_MODULE_ID,
        .channel_id = CONFIG_AC_CHANNEL_ID,
        .cmd = CONFIG_CMD_QUERY_AC_STATUS,
        .cmd_string = ac_status_string
    };

    volatile const command::CommandRegistry enable_ac_service CMD_REGISTRY = 
    {
        .module_id = CONFIG_AC_MODULE_ID,
        .channel_id = CONFIG_AC_CHANNEL_ID,
        .cmd = CONFIG_CMD_ENABLE_AC_SERVICE,
        .cmd_string = enable_ac_service_string
    };

    volatile const command::CommandRegistry disable_ac_service CMD_REGISTRY =
    {
        .module_id = CONFIG_AC_MODULE_ID,
        .channel_id = CONFIG_AC_CHANNEL_ID,
        .cmd = CONFIG_CMD_DISABLE_AC_SERVICE,
        .cmd_string = disable_ac_service_string
    };

    volatile const command::CommandRegistry set_ac_lowon CMD_REGISTRY =
    {
        .module_id = CONFIG_AC_MODULE_ID,
        .channel_id = CONFIG_AC_CHANNEL_ID,
        .cmd = CONFIG_CMD_SET_AC_LOWON,
        .cmd_string = ac_low_on_string
    };

    volatile const command::CommandRegistry set_ac_highon CMD_REGISTRY = 
    {
        .module_id = CONFIG_AC_MODULE_ID,
        .channel_id = CONFIG_AC_CHANNEL_ID,
        .cmd = CONFIG_CMD_SET_AC_HIGHON,
        .cmd_string = ac_high_on_string
    };

    volatile const command::CommandRegistry set_ac_off CMD_REGISTRY = 
    {
        .module_id = CONFIG_AC_MODULE_ID,
        .channel_id = CONFIG_AC_CHANNEL_ID,
        .cmd = CONFIG_CMD_SET_AC_OFF ,
        .cmd_string = ac_set_off_string,
    };
}