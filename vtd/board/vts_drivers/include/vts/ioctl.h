

#ifndef __INCLUDE_NUTTX_VTS_SENSORS_IOCTL_H
#define __INCLUDE_NUTTX_VTS_SENSORS_IOCTL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/fs/ioctl.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* All Sensor-related IOCTL commands are defined here to assure that they are
 * globally unique.
 */

/* List of  IOCTL commands */

#define ENGINE_IOC_STATUS       _VTSIOC(1)
#define ENGINE_IOC_LOCK         _VTSIOC(2)
#define ENGINE_IOC_UNLOCK       _VTSIOC(3)
#define ENGINE_IOC_INIT  	    _VTSIOC(4)
#define ENGINE_IOC_LOCK_STATUS  _VTSIOC(5)

#define AC_IOC_STATUS		    _VTSIOC(6)
#define AC_IOC_INIT			    _VTSIOC(7)

#define PANIC_IOC_STATUS	    _VTSIOC(8)
#define PANIC_IOC_INIT		    _VTSIOC(9)

#define LOUDHORN_IOC_ON         _VTSIOC(10)
#define LOUDHORN_IOC_OFF        _VTSIOC(11)
#define LOUDHORN_IOC_INIT       _VTSIOC(12)

#define BATTERY_IOC_INIT        _VTSIOC(13)
#define BATTER_IOC_READ         _VTSIOC(14)

#endif /* __INCLUDE_NUTTX_VTS_SENSORS_IOCTL_H */
