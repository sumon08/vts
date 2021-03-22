
/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <poll.h>
#include <errno.h>
#include <unistd.h>

#include <nuttx/irq.h>
#include <nuttx/kmalloc.h>
#include <nuttx/signal.h>
#include <nuttx/i2c/i2c_master.h>
#include <nuttx/power/battery_charger.h>
#include <arch/board/board.h>
#include "stm32_gpio.h"
#include "vts-v2f401rc.h"
#include "up_arch.h"
#include "chip.h"
#include "stm32.h"


#if defined(CONFIG_STM32_I2C1)

/************************************************************************************
 * Public Data
 ************************************************************************************/

#ifdef CONFIG_STM32_I2C1
struct i2c_master_s *g_i2c1_dev;
#endif


/************************************************************************************
 * Public Functions
 ************************************************************************************/

/************************************************************************************
 * Name: stm32_i2cdev_initialize
 *
 * Description:
 *   Called to configure I2C
 *
 ************************************************************************************/


int stm32_i2cdev_initialize(void)
{
    int ret = OK;
   
    g_i2c1_dev = stm32_i2cbus_initialize(1);
    if(g_i2c1_dev == NULL)
    {
        printf("stm32_i2cbus_initialize() failed %d\n",errno);
        ret = -ENODEV;
    }
    //ret = i2c_register(g_i2c1_dev,1);

    return ret;
}
#endif /* CONFIG_STM32_I2C1 */


#if defined(CONFIG_BATTERY_CHARGER)

struct battery_charger_dev_s *battery_charger;

int stm32_battery_charger_initialize(void)
{
    int ret = 1;

    ret = stm32_i2cdev_initialize();

    if(ret < 0){
        syslog(LOG_ERR, "Error: stm32_i2cbus_initialize(1) failed %d\n",ret);
        ret = -ENODEV;
        return ret;
    }
    
    else{
        battery_charger = bq2429x_initialize(g_i2c1_dev,0x6B,400000,2000);
        if(battery_charger == NULL){
            syslog(LOG_ERR, "Error: bq2429x_initialize() failed %d\n",ret);
            ret = -ENODEV;
            return -1;
        }
        else{
            battery_charger_register("/dev/bat0",battery_charger);
            return 111;
        }
        
    }
}
#endif /* CONFIG_BATTERY_CHARGER */