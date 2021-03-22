/*
Author: Munna
Date: 08-Oct-2018
*/

#ifndef __INCLUDE_NUTTX_PANIC_SENSOR_H
#define __INCLUDE_NUTTX_PANIC_SENSOR_H





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

struct panic_regval
{
  FAR char name[3];
  bool val;
};

struct panic_status
{
  bool on;
  int register_values_size;
  FAR struct panic_regval* register_values;
};

struct panic_lower;

struct panic_ops
{
  CODE int (*config)            (FAR struct panic_lower* lower);
  CODE int (*getstatus)         (FAR struct panic_lower* lower, FAR struct panic_status* status);
  CODE int (*ioctl)             (FAR struct panic_lower* lower, int cmd, unsigned long arg);
};

struct panic_lower
{
  FAR const struct panic_ops *ops;
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
 * "Upper-Half" panic Driver Interfaces
 ****************************************************************************/

FAR void *panic_register(FAR const char *path, FAR struct panic_lower *lower);

void panic_unregister(FAR void *handle);

#undef EXTERN
#if defined(__cplusplus)
}
#endif






#endif /* __INCLUDE_NUTTX_PANIC_SENSOR_H */
