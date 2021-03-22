

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
#include <nuttx/modem/sim868.h>

#include <arch/board/board.h>
#include "stm32_gpio.h"
#include "vts-v2f401rc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/* Debug ********************************************************************/
/* Non-standard debug that may be enabled just for testing the modem driver */

#ifdef CONFIG_MODEM_U_BLOX_DEBUG
#  define m_err     _err
#  define m_info    _info
#else
#  define m_err(x...)
#  define m_info(x...)
#endif

/*#define UBXMDM_REGISTER_COUNT                           \
  (sizeof(lpc17_ubxmdm_name_pins) /                     \
   sizeof(struct lpc17_name_pin))
*/
/****************************************************************************
 * Private Types
 ****************************************************************************/


/* This structure type provides the private representation of the "lower-half"
 * driver state.  This type must be coercible to type 'ubxmdm_lower'.
 */

struct vts_sim868_lower
{
  FAR const struct sim868_ops* ops;  /* Lower half operations */
};


/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* "Lower half" driver methods **********************************************/
static int sim868_config(FAR struct sim868_lower* lower);
static int sim868_poweron  (FAR struct sim868_lower* lower);
static int sim868_poweroff (FAR struct sim868_lower* lower);
static int sim868_reset    (FAR struct sim868_lower* lower);
static int sim868_getstatus(FAR struct sim868_lower* lower,
                           FAR struct sim868_status* status);
static int sim868_ioctl    (FAR struct sim868_lower* lower,
                           int cmd,
                           unsigned long arg);

/* "Lower half" driver state */

static struct vts_sim868_lower vts_lower;

/****************************************************************************
 * Private Data
 ****************************************************************************/
/* "Lower half" driver methods */

static const struct sim868_ops vts_sim868_ops =
{
  .mdm_open 	  = sim868_config,
  .poweron      = sim868_poweron,
  .poweroff     = sim868_poweroff,
  .reset        = sim868_reset,
  .getstatus    = sim868_getstatus,
  .ioctl        = sim868_ioctl,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int sim868_config(FAR struct sim868_lower* lower)
{
	(void) lower;

	stm32_configgpio(VTS_MDM_PWR);
	stm32_configgpio(VTS_MDM_VLE);
	stm32_configgpio(VTS_STATUS);

	return OK;
}


static int sim868_poweron(FAR struct sim868_lower* lower)
{
   (void) lower;
  //puts("board/src/sim868.c -> power_on()");
	//printf("Powering on.....\n");
	stm32_gpiowrite(VTS_MDM_VLE, 1);
	nxsig_usleep(2000*1000);



	stm32_gpiowrite(VTS_MDM_PWR, 1);
	nxsig_usleep(2000*1000);
	stm32_gpiowrite(VTS_MDM_PWR, 0);
	nxsig_usleep(5000*1000);


  return OK;
}

static int sim868_poweroff(FAR struct sim868_lower* lower)
{
  //puts("board/src/sim868.c -> power_off()");

  (void) lower;
  stm32_gpiowrite(VTS_MDM_VLE, 0);
	nxsig_usleep(2000*1000);
  return OK;
}

static int sim868_reset(FAR struct sim868_lower* lower)
{
  (void) lower;

	//printf("Reseting on.....\n");
	stm32_gpiowrite(VTS_MDM_VLE, 0);
	nxsig_usleep(2000*1000);

	stm32_gpiowrite(VTS_MDM_VLE, 1);
	nxsig_usleep(2000*1000);

	stm32_gpiowrite(VTS_MDM_PWR, 1);
	nxsig_usleep(2000*1000);
	stm32_gpiowrite(VTS_MDM_PWR, 0);
	nxsig_usleep(5000*1000);
  return OK;
}

static int sim868_getstatus(FAR struct sim868_lower* lower,
                           FAR struct sim868_status* status)
{
  (void) lower;
  //puts("board/src/sim868.c -> get_status()");
  bool result = stm32_gpioread(VTS_STATUS);

  status->on = result;

  return OK;
}

static int sim868_ioctl(FAR struct sim868_lower* lower,
                       int cmd,
                       unsigned long arg)
{
  /* No platform-specific IOCTL at the moment. */

  return -ENOSYS;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: lpc17_ubxmdm_init
 *
 * Description:
 *   Initialize the modem.  The modem is initialized and
 *   registered at '/dev/ubxmdm'.
 *
 * Input Parameters:
 *   usb_used - enables the USB sense pin if 'true'
 *
 * Returned Values:
 *   None
 *
 ****************************************************************************/

void vts_sim868_init()
{
  FAR struct vts_sim868_lower * priv = &vts_lower;

  //DEBUGASSERT(priv->ops == NULL && priv->pins == NULL);

  /* Initialize the driver state structure.  Here we assume: (1) the state
   * structure lies in .bss and was zeroed at reset time.  (2) This function
   * is only called once so it is never necessary to re-zero the structure.
   */

  priv->ops      = &vts_sim868_ops;

  (void) sim868_register("/dev/sim868", (FAR struct sim868_lower*) priv);
}
