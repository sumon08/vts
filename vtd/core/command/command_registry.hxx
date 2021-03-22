#ifndef __INCLUDE_COMMAND_REGISTRY_H
#define __INCLUDE_COMMAND_REGISTRY_H



#include "config.hxx"
#include "commands.hxx"
#include <command_config.h>
#include <cstdint>

namespace vts
{
    namespace command
    {
        volatile const CommandRegistry query_engine_status CMD_REGISTRY =
        {
            .module_id = CONFIG_ENGINE_MODULE_ID,
            .channel_id = CONFIG_ENGINE_CHANNEL_ID,
            .cmd = CONFIG_CMD_QUERY_ENGINE_STATUS,
            .cmd_string = engine_cmd_string
        };

        volatile const CommandRegistry engine_status_sms CMD_REGISTRY =
        {
            .module_id = CONFIG_ENGINE_MODULE_ID,
            .channel_id = CONFIG_ENGINE_CHANNEL_ID,
            .cmd = CONFIG_CMD_ENGINE_STATUS_SEND_SMS,
            .cmd_string = engine_cmd_string
        };

        volatile const CommandRegistry engine_lock CMD_REGISTRY = 
        {
            .module_id = CONFIG_ENGINE_MODULE_ID,
            .channel_id = CONFIG_ENGINE_CHANNEL_ID,
            .cmd = CONFIG_CMD_LOCK_ENGINE,
            .cmd_string = engine_lock_string
        };

         volatile const CommandRegistry engine_unlock CMD_REGISTRY = 
        {
            .module_id = CONFIG_ENGINE_MODULE_ID,
            .channel_id = CONFIG_ENGINE_CHANNEL_ID,
            .cmd = CONFIG_CMD_UNLOCK_ENGINE,
            .cmd_string = engine_unlock_string
        };

        volatile const CommandRegistry enable_engine_service CMD_REGISTRY = 
        {
            .module_id = CONFIG_ENGINE_MODULE_ID,
            .channel_id = CONFIG_ENGINE_CHANNEL_ID,
            .cmd = CONFIG_CMD_ENABLE_ENGINE_SERVICE,
            .cmd_string = enable_engine_service_string
        };

        volatile const CommandRegistry disable_engine_service CMD_REGISTRY = 
        {
            .module_id = CONFIG_ENGINE_MODULE_ID,
            .channel_id = CONFIG_ENGINE_CHANNEL_ID,
            .cmd = CONFIG_CMD_DISABLE_ENGINE_SERVICE,
            .cmd_string = disable_engine_service_string
        };

        volatile const CommandRegistry ac_status CMD_REGISTRY =
        {
            .module_id = CONFIG_AC_MODULE_ID,
            .channel_id = CONFIG_AC_CHANNEL_ID,
            .cmd = CONFIG_CMD_AC_STATUS,
            .cmd_string = ac_status_string
        };

        volatile const CommandRegistry query_ac_status CMD_REGISTRY =
        {
            .module_id = CONFIG_AC_MODULE_ID,
            .channel_id = CONFIG_AC_CHANNEL_ID,
            .cmd = CONFIG_CMD_QUERY_AC_STATUS,
            .cmd_string = ac_status_string
        };

        volatile const CommandRegistry enable_ac_service CMD_REGISTRY = 
        {
            .module_id = CONFIG_AC_MODULE_ID,
            .channel_id = CONFIG_AC_CHANNEL_ID,
            .cmd = CONFIG_CMD_ENABLE_AC_SERVICE,
            .cmd_string = enable_ac_service_string
        };

        volatile const CommandRegistry disable_ac_service CMD_REGISTRY =
        {
            .module_id = CONFIG_AC_MODULE_ID,
            .channel_id = CONFIG_AC_CHANNEL_ID,
            .cmd = CONFIG_CMD_DISABLE_AC_SERVICE,
            .cmd_string = disable_ac_service_string
        };

        volatile const CommandRegistry set_ac_lowon CMD_REGISTRY =
        {
            .module_id = CONFIG_AC_MODULE_ID,
            .channel_id = CONFIG_AC_CHANNEL_ID,
            .cmd = CONFIG_CMD_SET_AC_LOWON,
            .cmd_string = ac_low_on_string
        };

        volatile const CommandRegistry set_ac_highon CMD_REGISTRY = 
        {
            .module_id = CONFIG_AC_MODULE_ID,
            .channel_id = CONFIG_AC_CHANNEL_ID,
            .cmd = CONFIG_CMD_SET_AC_HIGHON,
            .cmd_string = ac_high_on_string
        };

        volatile const CommandRegistry set_ac_off CMD_REGISTRY = 
        {
            .module_id = CONFIG_AC_MODULE_ID,
            .channel_id = CONFIG_AC_CHANNEL_ID,
            .cmd = CONFIG_CMD_SET_AC_OFF ,
            .cmd_string = ac_set_off_string,
        };

        volatile const CommandRegistry door_status_cmd CMD_REGISTRY = 
        {
            .module_id = CONFIG_DOOR_MODULE_ID,
            .channel_id = CONFIG_DOOR_CHANNEL_ID,
            .cmd = CONFIG_CMD_DOOR_STATUS,
            .cmd_string = door_status_string
        };

        volatile const CommandRegistry query_door_status CMD_REGISTRY=
        {
            .module_id = CONFIG_DOOR_MODULE_ID,
            .channel_id = CONFIG_DOOR_CHANNEL_ID,
            .cmd = CONFIG_CMD_QUERY_DOOR_STATUS,
            .cmd_string = door_status_string
        };

        volatile const CommandRegistry enable_door_service CMD_REGISTRY=
        {
            .module_id = CONFIG_DOOR_MODULE_ID,
            .channel_id = CONFIG_DOOR_CHANNEL_ID,
            .cmd = CONFIG_CMD_ENABLE_DOOR_SERVICE,
            .cmd_string = enable_door_sevice_string
        };

        volatile const CommandRegistry disable_door_service CMD_REGISTRY=
        {
            .module_id = CONFIG_DOOR_MODULE_ID,
            .channel_id = CONFIG_DOOR_CHANNEL_ID,
            .cmd = CONFIG_CMD_DISABLE_DOOR_SERVICE,
            .cmd_string = disable_door_sevice_string
        };

        volatile const CommandRegistry set_door_polarity CMD_REGISTRY=
        {
            .module_id = CONFIG_DOOR_MODULE_ID,
            .channel_id = CONFIG_DOOR_CHANNEL_ID,
            .cmd = CONFIG_CMD_SET_DOOR_POLARITY,
            .cmd_string = set_door_polarity_string
        };

        volatile const CommandRegistry panic_status CMD_REGISTRY =
        {
            .module_id = CONFIG_PANIC_MODULE_ID,
            .channel_id = CONFIG_PANIC_CHANNEL_ID,
            .cmd = CONFIG_CMD_SEND_PANIC_STATUS,
            .cmd_string = panic_status_string
        };


        volatile const CommandRegistry enable_panic_service CMD_REGISTRY=
        {
            .module_id = CONFIG_PANIC_MODULE_ID,
            .channel_id = CONFIG_PANIC_CHANNEL_ID,
            .cmd = CONFIG_CMD_ENABLE_PANIC_SERVICE,
            .cmd_string = enable_panic_service_string
        };


        volatile const CommandRegistry overspeed_violation CMD_REGISTRY=
        {
            .module_id = CONFIG_OVERSPEED_MODULE_ID,
            .channel_id = CONFIG_OVERSPEED_CHANNEL_ID,
            .cmd = CONFIG_CMD_OVERSPEED_VIOLATION_STATUS,
            .cmd_string = over_speed_violation_string
        };

        volatile const CommandRegistry enable_overspeed_service CMD_REGISTRY =
        {
            .module_id =CONFIG_OVERSPEED_MODULE_ID,
            .channel_id =CONFIG_OVERSPEED_CHANNEL_ID,
            .cmd = CONFIG_CMD_ENABLE_OVERSPEED_SERVICE,
            .cmd_string = enable_overspeed_service_string
        };

        volatile const CommandRegistry disable_overspeed_service CMD_REGISTRY =
        {
            .module_id =CONFIG_OVERSPEED_MODULE_ID,
            .channel_id =CONFIG_OVERSPEED_CHANNEL_ID,
            .cmd = CONFIG_CMD_DISABLE_OVERSPEED_SERVICE,
            .cmd_string = enable_overspeed_service_string
        };

        /*
        volatile const CommandRegistry set_overspeed_thershold CMD_REGISTRY=
        {
            .module_id = ,
            .channel_id = ,
            .cmd = ,
            .cmd_string =
        };
        */
        /*** template ***

        volatile const CommandRegistry CMD_REGISTRY=
        {
            .module_id = ,
            .channel_id = ,
            .cmd = ,
            .cmd_string =
        };

        ****/

    }
}


#endif //__INCLUDE_COMMAND_REGISTRY_H