

/************************************************************************************/

#ifndef __CONFIGS_VTSV2_F401RC_SRC_VTSV2_F401RC_H
#define __CONFIGS_VTSV2_F401RC_SRC_VTSV2_F401RC_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <stdint.h>

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/
/* Configuration ********************************************************************/


/* STM32F401RC USER GPIOs **************************************************/

#define BOARD_NGPIOIN     1 /* Amount of GPIO Input pins */
#define BOARD_NGPIOOUT    1 /* Amount of GPIO Output pins */
#define BOARD_NGPIOINT    1 /* Amount of GPIO Input w/ Interruption pins */
/* VTS Modem gpio pin***************************************************/


#define VTS_MDM_VLE		(GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|\
                         GPIO_OUTPUT_CLEAR|GPIO_PORTB|GPIO_PIN5)

#define VTS_MDM_PWR	(GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|\
                         GPIO_OUTPUT_CLEAR|GPIO_PORTB|GPIO_PIN15)

#define VTS_STATUS		(GPIO_INPUT|GPIO_FLOAT|GPIO_PORTC|GPIO_PIN4)


#define HAVE_MODEM_SIM868

/*SPI Chip selects */

#define GPIO_CS_FLASH   (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN15)
#define GPIO_SCK_FLASH  (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_SET|GPIO_PORTC|GPIO_PIN11)
#define GPIO_MISO_FLASH (GPIO_INPUT|GPIO_FLOAT|GPIO_PORTC|GPIO_PIN12)
#define GPIO_MOSI_FLASH (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_SET|GPIO_PORTC|GPIO_PIN13)

/* GPS GPIO */

#define GPS_ENABLE  (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTC|GPIO_PIN8)
#define GPS_RESET   (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTC|GPIO_PIN9)

/* Charge Controller GPIO */

#define UC_CE		(GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTB|GPIO_PIN10)


/* ENGINE Monitor and Control Pins */
#define ENGINE_CONTROL      (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTC|GPIO_PIN2)
#define ENGINE_MONITOR      (GPIO_INPUT|GPIO_FLOAT|GPIO_PORTC|GPIO_PIN0)

#define PANIC_MONITOR       (GPIO_INPUT|GPIO_FLOAT|GPIO_PORTC|GPIO_PIN1)

#define AC_MONITOR          (GPIO_INPUT|GPIO_FLOAT|GPIO_PORTB|GPIO_PIN0)

#define LOUDHORN_CONTROL    (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTC|GPIO_PIN3)
/************************************************************************************
 * Public Data
 ************************************************************************************/

/* Global driver instances */


#if defined(CONFIG_MODEM) && defined(CONFIG_MODEM_SIM868)
    void vts_sim868_init(void);
#endif

#if defined(CONFIG_GPS_SIM68)
    void sim68_init(void);
#endif

#if defined(CONFIG_DEV_GPIO)
int stm32_gpio_initialize(void);
#endif
#if defined(CONFIG_STM32_I2C1)
int stm32_i2cdev_initialize(void);
#endif

#if defined(CONFIG_BATTERY_CHARGER)
    int stm32_battery_charger_initialize(void);
#endif

#if defined(CONFIG_ENGINE_SENSOR)
	void vts_engine_init(void);
#endif

#if defined(CONFIG_PANIC_SENSOR)
    void vts_panic_init(void);
#endif

#if defined(CONFIG_AC_SENSOR)
    void vts_ac_init(void);
#endif

#if defined(CONFIG_LOUDHORN)
    void vts_loudhorn_init(void);
#endif

#ifdef CONFIG_BATTERY_SENSOR
   int vts_battery_init(void);
#endif 

#endif /*__CONFIGS_VTSV2_F401RC_SRC_VTSV2_F401RC_H */
