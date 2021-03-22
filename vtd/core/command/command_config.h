

#ifndef _COMMAND_CONFIG_INCLUDE_H_
#define _COMMAND_CONFIG_INCLUDE_H_
/** CONTROL CHANNEL (0X00) CONSTANTS **/
#define CONFIG_CMD_OPEN_CHANNEL			            0x81
#define CONFIG_ACK_OPEN_CHANNEL			            0x01
#define CONFIG_CMD_CLOSE_CHANNEL		            0x82
#define CONFIG_ACK_CLOSE_CHANNEL		            0x02
#define CONFIG_CMD_SEND_VTS_ID			            0x83
#define CONFIG_ACK_SEND_VTS_ID			            0x03
#define CONFIG_CMD_REQUEST_VTS_ID		            0x84
#define CONFIG_ACK_REQUEST_VTS_ID		            0x04
#define CONFIG_CMD_PAUSE_TRANSACTION	            0x85
#define CONFIG_ACK_PAUSE_TRANSACTION	            0x05
#define CONFIG_CMD_RESUME_TRANSACTION	            0x86
#define CONFIG_ACK_RESUME_TRANSACTION	            0x06
#define CONFIG_CMD_PUT_DEVICE_IN_SLEEP	            0x87
#define CONFIG_ACK_PUT_DEVICE_IN_SLEEP	            0x07
#define CONFIG_CMD_SET_GPSRESET_HOT		            0X8B
#define CONFIG_ACK_SET_GPSRESET_HOT           		0X0B
#define CONFIG_CMD_SET_GPSRESET_WARM		        0X8C
#define CONFIG_ACK_SET_GPSRESET_WARM           		0X0C
#define CONFIG_CMD_SET_GPSRESET_COLD		        0X8D
#define CONFIG_ACK_SET_GPSRESET_COLD           		0X0D
#define CONFIG_CMD_SET_GPSRESET_FULLCOLD		    0X8E
#define CONFIG_ACK_SET_GPSRESET_FULLCOLD            0X0E
#define CONFIG_CMD_SET_GPS_ACCURACY		            0X8F
#define CONFIG_ACK_SET_GPS_ACCURACY		            0X0F
#define CONFIG_CMD_REBOOT_DEVICE			        0x88
#define CONFIG_ACK_REBOOT_DEVICE			        0x08
#define CONFIG_CMD_REBOOT_MODEM			            0x89
#define CONFIG_ACK_REBOOT_MODEM			            0x09
#define CONFIG_CMD_REQUEST_VERSION_INFO             0x8A
#define CONFIG_ACK_REQUEST_VERSION_INFO             0x0A
#define CONFIG_CMD_REQUEST_INTERVAL_INFO            0x8B
#define CONFIG_ACK_REQUEST_INTERVAL_INFO            0x0B
#define CONFIG_CMD_REQUEST_GSMSTRENGTH_INFO         0x8C
#define CONFIG_ACK_REQUEST_GSMSTRENGTH_INFO         0x0C
#define CONFIG_CMD_REQUEST_TEMPERATURE_INFO         0x8D
#define CONFIG_ACK_REQUEST_TEMPERATURE_INFO         0x0D
#define CONFIG_CMD_SET_USSD_CONTROL         		0x9F
#define CONFIG_ACK_SET_USSD_CONTROL         		0x1F
#define CONFIG_CMD_REQUEST_USSD_COMMAND         	0x90
#define CONFIG_ACK_REQUEST_USSD_COMMAND         	0x10
#define CONFIG_CMD_SET_DOMAIN       				0x91
#define CONFIG_ACK_SET_DOMAIN		         		0x11
#define CONFIG_CMD_SET_IP_PORT         				0x92
#define CONFIG_ACK_SET_IP_PORT         				0x12

/** LOCATION CHANNEL (0X01) CONSTANTS **/
#define CONFIG_CMD_SEND_GPS_INFO                    0x81
#define CONFIG_ACK_SEND_GPS_INFO                    0x01
#define CONFIG_CMD_REQUEST_GPS_INFO		            0x82
#define CONFIG_ACK_REQUEST_GPS_INFO                 0x02
#define CONFIG_CMD_SET_RUNNING_INTERVAL             0x83
#define CONFIG_ACK_SET_RUNNING_INTERVAL             0x03
#define CONFIG_CMD_READ_RUNNING_INTERVAL            0X84
#define CONFIG_ACK_READ_RUNNING_INTERVAL            0X04
#define CONFIG_CMD_SET_IDLE_INTERVAL                0X85
#define CONFIG_ACK_SET_IDLE_INTERVAL                0X05
#define CONFIG_CMD_READ_IDLE_INTERVAL               0X86
#define CONFIG_ACK_READ_IDLE_INTERVAL               0X06
#define CONFIG_CMD_SET_RUNNING_AND_IDLE_INTERVAL    0X87
#define CONFIG_ACK_SET_RUNNING_AND_IDLE_INTERVAL    0X07
#define CONFIG_CMD_SEND_RUNNING_AND_IDLE_INTERVAL   0X88
#define CONFIG_ACK_SEND_RUNNING_AND_IDLE_INTERVAL   0X08
#define CONFIG_CMD_SEND_IDLE_INTERVAL               0X89
#define CONFIG_ACK_SEND_IDLE_INTERVAL               0X09
#define CONFIG_CMD_SEND_RUNNING_INTERVAL            0X8A
#define CONFIG_ACK_SEND_RUNNING_INTERVAL            0X0A

/** ENGINE CHANNEL (0X02) CONSTANTS **/

#define CONFIG_CMD_ENGINE_STATUS                    0x81
#define CONFIG_ACK_ENGINE_STATUS                    0x01
#define CONFIG_CMD_ENGINE_STATUS_SEND_SMS           0x82
#define CONFIG_ACK_ENGINE_STATUS_SEND_SMS           0x02
#define CONFIG_CMD_QUERY_ENGINE_STATUS              0X83
#define CONFIG_ACK_QUERY_ENGINE_STATUS              0X03
#define CONFIG_CMD_LOCK_ENGINE                      0x84
#define CONFIG_ACK_LOCK_ENGINE                      0x04
#define CONFIG_CMD_UNLOCK_ENGINE                    0x85
#define CONFIG_ACK_UNLOCK_ENGINE                    0x05
#define CONFIG_CMD_ENABLE_ENGINE_SERVICE            0x86
#define CONFIG_ACK_ENABLE_ENGINE_SERVICE            0x06
#define CONFIG_CMD_DISABLE_ENGINE_SERVICE           0x87
#define CONFIG_ACK_DISABLE_ENGINE_SERVICE           0x07

/** AC CHANNEL (0X03) CONSTANTS **/

#define CONFIG_CMD_AC_STATUS                        0x81
#define CONFIG_ACK_AC_STATUS                        0x01
#define CONFIG_CMD_AC_STATUS_SEND_SMS               0x82
#define CONFIG_ACK_AC_STATUS_SEND_SMS               0x02
#define CONFIG_CMD_QUERY_AC_STATUS                  0x83
#define CONFIG_ACK_QUERY_AC_STATUS                  0x03
#define CONFIG_CMD_ENABLE_AC_SERVICE                0x84
#define CONFIG_ACK_ENABLE_AC_SERVICE                0x04
#define CONFIG_CMD_DISABLE_AC_SERVICE               0x85
#define CONFIG_ACK_DISABLE_AC_SERVICE               0x05
#define CONFIG_CMD_SET_AC_LOWON				        0x86
#define CONFIG_ACK_SET_AC_LOWON        				0x06
#define CONFIG_CMD_SET_AC_HIGHON				    0x87
#define CONFIG_ACK_SET_AC_HIGHON        		    0x07
#define CONFIG_CMD_SET_AC_OFF					    0x88
#define CONFIG_ACK_SET_AC_OFF       		 		0x08

/** DOOR CHANNEL (0X04) CONSTANTS **/

#define CONFIG_CMD_DOOR_STATUS                      0x81
#define CONFIG_ACK_DOOR_STATUS                      0x01
#define CONFIG_CMD_DOOR_STATUS_SEND_SMS             0x82
#define CONFIG_ACK_DOOR_STATUS_SEND_SMS             0x02
#define CONFIG_CMD_QUERY_DOOR_STATUS                0x83
#define CONFIG_ACK_QUERY_DOOR_STATUS                0x03
#define CONFIG_CMD_ENABLE_DOOR_SERVICE              0x84
#define CONFIG_ACK_ENABLE_DOOR_SERVICE              0x04
#define CONFIG_CMD_DISABLE_DOOR_SERVICE             0x85
#define CONFIG_ACK_DISABLE_DOOR_SERVICE             0x05
#define CONFIG_CMD_SET_DOOR_POLARITY			    0x86
#define CONFIG_ACK_SET_DOOR_POLARITY		      	0x06

/** PANIC CHANNEL (0X05) CONSTANTS **/

#define CONFIG_CMD_SEND_PANIC_STATUS                0x81
#define CONFIG_ACK_SEND_PANIC_STATUS                0x01
#define CONFIG_CMD_ENABLE_PANIC_SERVICE             0x82
#define CONFIG_ACK_ENABLE_PANIC_SERVICE             0x02
#define CONFIG_CMD_DISABLE_PANIC_SERVICE            0x83
#define CONFIG_ACK_DISABLE_PANIC_SERVICE            0x03

/** OVER_SPEED CHANNEL (0X06) CONSTANTS **/
#define CONFIG_CMD_OVERSPEED_VIOLATION_STATUS       0x81
#define CONFIG_ACK_OVERSPEED_VIOLATION_STATUS       0x01
#define CONFIG_CMD_ENABLE_OVERSPEED_SERVICE         0x82
#define CONFIG_ACK_ENABLE_OVERSPEED_SERVICE         0x02
#define CONFIG_CMD_DISABLE_OVERSPEED_SERVICE        0x83
#define CONFIG_ACK_DISABLE_OVERSPEED_SERVICE        0x03
#define CONFIG_CMD_SET_OVERSPEED_THRESHOLD          0x84
#define CONFIG_ACK_SET_OVERSPEED_THRESHOLD          0x04
#define CONFIG_CMD_SET_SPEED_VIOLATION_INTERVAL		0x85
#define CONFIG_ACK_SET_SPEED_VIOLATION_INTERVAL		0x05
#define CONFIG_CMD_SET_SPEED_FORMAT					0x86
#define CONFIG_ACK_SET_SPEED_FORMAT					0x06

/** GEO_FENCE CHANNEL (0X07) CONSTANTS **/
#define CONFIG_CMD_SEND_GEOFENCE_ALERT              0x81
#define CONFIG_ACK_SEND_GEOFENCE_ALERT              0x01
#define CONFIG_CMD_ENABLE_GEOFENCE_ALERT_SERVICE    0x82
#define CONFIG_ACK_ENABLE_GEOFENCE_ALERT_SERVICE    0x02
#define CONFIG_CMD_DISABLE_GEOFENCE_ALERT_SERVICE   0x82
#define CONFIG_ACK_DISABLE_GEOFENCE_ALERT_SERVICE   0x02
#define CONFIG_CMD_SET_GEOFENCE_AREA_DEFINITION     0x84
#define CONFIG_ACK_SET_GEOFENCE_AREA_DEFINITION     0x04
#define CONFIG_CMD_SEND_GEOFENCE_AREA_DEFINITION    0x85
#define CONFIG_ACK_SEND_GEOFENCE_AREA_DEFINITION    0x05
#define CONFIG_CMD_READ_GEOFENCE_AREA_DEFINITION    0x86
#define CONFIG_ACK_READ_GEOFENCE_AREA_DEFINITION    0x06
#define CONFIG_CMD_ACTIVATE_GEOFENCE_AREA           0x87
#define CONFIG_ACK_ACTIVATE_GEOFENCE_AREA           0x07
#define CONFIG_CMD_DEACTIVATE_GEOFENCE_AREA         0x88
#define CONFIG_ACK_DEACTIVATE_GEOFENCE_AREA         0x08
#define CONFIG_CMD_ACTIVATE_ALL_GEOFENCE_AREA       0x89
#define CONFIG_ACK_ACTIVATE_ALL_GEOFENCE_AREA       0x09
#define CONFIG_CMD_DEACTIVATE_ALL_GEOFENCE_AREA     0x8A
#define CONFIG_ACK_DEACTIVATE_ALL_GEOFENCE_AREA     0x0A


/** AUDIO_SPY CHANNEL (0x08) CONSTANTS **/
// nothing to define, feature for future version

/** IMAGE CHANNEL (0x08) CONSTANTS **/
//for future use

/** FUEL CHANNEL (0x0A)	 CONSTANTS **/
#define CONFIG_CMD_SET_FUEL_SYSTEM					0x81
#define CONFIG_ACK_SET_FUEL_SYSTEM					0x01
#define CONFIG_CMD_SET_FUEL_CALIBRATION				0x82
#define CONFIG_ACK_SET_FUEL_CALIBRATION				0x02
#define CONFIG_CMD_SET_BATTERY_CALIBRATION			0x83
#define CONFIG_ACK_SET_BATTERY_CALIBRATION			0x03
#define CONFIG_CMD_SET_FUEL_STABILITY				0x84
#define CONFIG_ACK_SET_FUEL_STABILITY				0x04
#define CONFIG_CMD_SET_FUEL_RCDELAY					0x85
#define CONFIG_ACK_SET_FUEL_RCDELAY					0x05


/** LOUD_HORN CHANNEL 0x0B) CONSTANTS **/

#define CONFIG_CMD_ENABLE_LOUD_HORN_SERVICE         0x81
#define CONFIG_ACK_ENABLE_LOUD_HORN_SERVICE         0x01
#define CONFIG_CMD_DISABLE_LOUD_HORN_SERVICE        0x82
#define CONFIG_ACK_DISABLE_LOUD_HORN_SERVICE        0x02
#define CONFIG_CMD_SET_LOUD_HORN_USER_ACCESS        0x83
#define CONFIG_ACK_SET_LOUD_HORN_USER_ACCESS        0x03
#define CONFIG_CMD_READ_LOUD_HORN_USER_ACCESS       0x84
#define CONFIG_ACK_READ_LOUD_HORN_USER_ACCESS       0x04
#define CONFIG_CMD_SET_LOUD_RING_POLICY             0x85
#define CONFIG_ACK_SET_LOUD_RING_POLICY             0x05



/** BATTERY CHANNEL (0x0C) CONSTANTS **/

#define CONFIG_CMD_ENABLE_BATTERY_SERVICE           0x81
#define CONFIG_ACK_ENABLE_BATTERY_SERVICE           0x01
#define CONFIG_CMD_DISABLE_BATTERY_SERVICE          0x82
#define CONFIG_ACK_DISABLE_BATTERY_SERVICE          0x02
#define CONFIG_CMD_SET_BATTERY_USER_ACCESS          0x83
#define CONFIG_ACK_SET_BATTERY_USER_ACCESS          0x03
#define CONFIG_CMD_READ_BATTERY_USER_ACCESS         0x84
#define CONFIG_ACK_READ_BATTERY_USER_ACCESS         0x04
#define CONFIG_CMD_SEND_BATTERY_REMOVAL_ALERT       0x85
#define CONFIG_ACK_SEND_BATTERY_REMOVAL_ALERT       0x05



/** USER_MANAGEMENT CHANNEL (0x0D) CONSTANTS **/

#define CONFIG_CMD_CREATE_USER                      0x81
#define CONFIG_ACK_CREATE_USER                      0x01
#define CONFIG_CMD_DELETE_USER                      0x82
#define CONFIG_ACK_DELETE_USER                      0x02
#define CONFIG_CMD_ENABLE_USER_SUBSCRIPTION         0x83
#define CONFIG_ACK_ENABLE_USER_SUBSCRIPTION         0x03
#define CONFIG_CMD_DISABLE_USER_SUBSCRIPTION        0x84
#define CONFIG_ACK_DISABLE_USER_SUBSCRIPTION        0x04

/** FOTA CHANNEL (0x0D) CONSTANTS **/

#define CONFIG_CMD_QUERY_FIRMWARE_VERSION           0x81
#define CONFIG_ACK_QUERY_FIRMWARE_VERSION           0x01
#define CONFIG_CMD_SEND_FIRMWARE_INFO               0x82
#define CONFIG_ACK_SEND_FIRMWARE_INFO               0x02
#define CONFIG_CMD_QUERY_HARDWARE_VERSION           0x83
#define CONFIG_ACK_QUERY_HARDWARE_VERSION           0x03
#define CONFIG_CMD_SEND_HARDWARE_INFO               0x84
#define CONFIG_ACK_SEND_HARDWARE_INFO               0x04
#define CONFIG_CMD_SEND_FIRMWARE_SEGMENT            0x85
#define CONFIG_ACK_SEND_FIRMWARE_SEGMENT            0x05


/******* CMD STRINGS ********/
extern const char engine_cmd_string                 [];
extern const char engine_lock_string                [];
extern const char engine_unlock_string              [];
extern const char enable_engine_service_string      [];
extern const char disable_engine_service_string     [];
extern const char ac_status_string                  [];
extern const char enable_ac_service_string          [];
extern const char disable_ac_service_string         [];
extern const char ac_low_on_string                  [];
extern const char ac_high_on_string                 [];
extern const char ac_set_off_string                 [];
extern const char door_status_string                [];
extern const char enable_door_sevice_string         [];
extern const char disable_door_sevice_string        [];
extern const char set_door_polarity_string          [];
extern const char panic_status_string               [];
extern const char enable_panic_service_string       [];
extern const char disable_panic_service_String      [];
extern const char over_speed_violation_string       [];
extern const char enable_overspeed_service_string   [];
extern const char disable_overspeed_service_string  [];

#endif 