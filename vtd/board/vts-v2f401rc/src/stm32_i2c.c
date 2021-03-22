
#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/i2c/i2c_master.h>
#include <arch/board/board.h>

#include "up_arch.h"
#include "chip.h"
#include "stm32.h"

#include "vts-v2f401rc.h"


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
        syslog(LOG_ERR, "Error: stm32_i2cbus_initialize(1) failed %d\n",ret);
        ret = -ENODEV;
    }
    else{
        ret = i2c_register(g_i2c1_dev,1);
    }
    return ret;
}
#endif /* CONFIG_STM32_I2C1 */