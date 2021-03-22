/*
Author: Munna
Date: 10-Oct-2018
*/

#ifndef __INCLUDE_NUTTX_AC_SENSOR_H
#define __INCLUDE_NUTTX_AC_SENSOR_H





/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <stdbool.h>
#include <nuttx/vts/ioctl.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* See IOCTL definitions in include/nuttx/vts_sensors/ioctl.h */

/****************************************************************************
 * Public Types
 ****************************************************************************/

struct ac_regval
{
  FAR char name[3];
  bool val;
};

struct ac_status
{
  bool on;
  int register_values_size;
  FAR struct ac_regval* register_values;
};

struct ac_lower;

struct ac_ops
{
  CODE int (*config)            (FAR struct ac_lower* lower);
  CODE int (*getstatus)         (FAR struct ac_lower* lower, FAR struct ac_status* status);
  CODE int (*ioctl)             (FAR struct ac_lower* lower, int cmd, unsigned long arg);
};

struct ac_lower
{
  FAR const struct ac_ops *ops;
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * "Upper-Half" ac Driver Interfaces
 ****************************************************************************/

FAR void *ac_register(FAR const char *path, FAR struct ac_lower *lower);

void ac_unregister(FAR void *handle);

#undef EXTERN
#if defined(__cplusplus)
}
#endif






#endif /* __INCLUDE_NUTTX_AC_SENSOR_H */
