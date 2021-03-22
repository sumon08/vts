

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
#include <nuttx/fs/fs.h>
#include <nuttx/gps/sim68.h>

#include <arch/board/board.h>
#include "stm32_gpio.h"
#include "vts-v2f401rc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/* Debug ********************************************************************/
/* Non-standard debug that may be enabled just for testing the modem driver */

/****************************************************************************
 * Private Types
 ****************************************************************************/


/* This structure type provides the private representation of the "lower-half"
 * driver state.  This type must be coercible to type 'ubxmdm_lower'.
 */


struct vts_sim68_lower
{
  FAR const struct sim68_ops* ops;  // Lower half operations 
};


/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* "Lower half" driver methods **********************************************/
static int sim68_config(FAR struct sim68_lower* lower);
static int sim68_poweron  (FAR struct sim68_lower* lower);
static int sim68_poweroff (FAR struct sim68_lower* lower);
static int sim68_reset    (FAR struct sim68_lower* lower);
static int sim68_ioctl    (FAR struct sim68_lower* lower,
                           int cmd,
                           unsigned long arg);

/* "Lower half" driver state */

static struct vts_sim68_lower vts_gps_lower;

/****************************************************************************
 * Private Data
 ****************************************************************************/
/* "Lower half" driver methods */

static const struct sim68_ops vts_sim68_ops =
{
  .gps_open 	= sim68_config,
  .poweron      = sim68_poweron,
  .poweroff     = sim68_poweroff,
  .reset        = sim68_reset,
  .ioctl        = sim68_ioctl,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int sim68_config(FAR struct sim68_lower* lower)
{
	(void) lower;

	stm32_configgpio(GPS_ENABLE);
	stm32_configgpio(GPS_RESET);

	return OK;
}


static int sim68_poweron(FAR struct sim68_lower* lower)
{
   (void) lower;
  //puts("board/src/sim68.c -> power_on()");
    printf("GPS Powering on.....\n");
	stm32_gpiowrite(GPS_RESET, 1);
	nxsig_usleep(1000*1000);
	stm32_gpiowrite(GPS_ENABLE, 1);
  return OK;
}

static int sim68_poweroff(FAR struct sim68_lower* lower)
{
  //puts("board/src/sim68.c -> power_off()");
    printf("GPS Powering off.....\n");
    (void) lower;
    stm32_gpiowrite(GPS_RESET, 0);
    stm32_gpiowrite(GPS_ENABLE, 0);
    
  return OK;
}

static int sim68_reset(FAR struct sim68_lower* lower)
{
  (void) lower;

  printf("GPS Reseting .....\n");
  stm32_gpiowrite(GPS_ENABLE,0);
  stm32_gpiowrite(GPS_RESET,0);
  nxsig_usleep(1000*1000);
  stm32_gpiowrite(GPS_RESET,1);
  stm32_gpiowrite(GPS_ENABLE,1);
  return OK;
}


static int sim68_ioctl(FAR struct sim68_lower* lower,
                       int cmd,
                       unsigned long arg)
{
  /* No platform-specific IOCTL at the moment. */

  return -ENOSYS;
}



void sim68_init()
{
  FAR struct vts_sim68_lower * priv = &vts_gps_lower;

  //DEBUGASSERT(priv->ops == NULL && priv->pins == NULL);

  /* Initialize the driver state structure.  Here we assume: (1) the state
   * structure lies in .bss and was zeroed at reset time.  (2) This function
   * is only called once so it is never necessary to re-zero the structure.
   */

  priv->ops      = &vts_sim68_ops;

  (void) sim68_register("/dev/sim68", (FAR struct sim68_lower*) priv);
}
