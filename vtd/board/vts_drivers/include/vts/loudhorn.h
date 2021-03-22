/*
Author: Munna
Date: 10-Oct-2018
*/

#ifndef __INCLUDE_NUTTX_LOUD_HORN_SENSOR_H
#define __INCLUDE_NUTTX_LOUD_HORN_SENSOR_H





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

struct loudhorn_regval
{
  FAR char name[3];
  bool val;
};

struct loudhorn_status
{
  bool on;
  int register_values_size;
  FAR struct loudhorn_regval* register_values;
};

struct loudhorn_lower;

struct loudhorn_ops
{
  CODE int (*config)            (FAR struct loudhorn_lower* lower);
  CODE int (*on)                (FAR struct loudhorn_lower* lower);
  CODE int (*off)               (FAR struct loudhorn_lower* lower);
  CODE int (*ioctl)             (FAR struct loudhorn_lower* lower, int cmd, unsigned long arg);
};

struct loudhorn_lower
{
  FAR const struct loudhorn_ops *ops;
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
 * "Upper-Half" loudhorn Driver Interfaces
 ****************************************************************************/

FAR void *loudhorn_register(FAR const char *path, FAR struct loudhorn_lower *lower);

void loudhorn_unregister(FAR void *handle);

#undef EXTERN
#if defined(__cplusplus)
}
#endif






#endif /* __INCLUDE_NUTTX_LOUD_HORN_SENSOR_H */
