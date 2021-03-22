/*
Author: Munna
Date: 08-Oct-2018
*/

#ifndef __INCLUDE_NUTTX_ENGINE_SENSOR_H
#define __INCLUDE_NUTTX_ENGINE_SENSOR_H

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

struct engine_regval
{
  FAR char name[3];
  bool val;
};

struct engine_status
{
  bool on;
  int register_values_size;
  FAR struct engine_regval* register_values;
};

struct engine_lower;

struct engine_ops
{
  CODE int (*config)            (FAR struct engine_lower* lower);
  CODE int (*lock)              (FAR struct engine_lower* lower);
  CODE int (*unlock)            (FAR struct engine_lower* lower);
  CODE int (*getstatus)         (FAR struct engine_lower* lower, FAR struct engine_status* status);
  CODE int (*ioctl)             (FAR struct engine_lower* lower, int cmd, unsigned long arg);
};

struct engine_lower
{
  FAR const struct engine_ops *ops;
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
 * "Upper-Half" engine Driver Interfaces
 ****************************************************************************/

FAR void *engine_register(FAR const char *path, FAR struct engine_lower *lower);

void engine_unregister(FAR void *handle);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __INCLUDE_NUTTX_ENGINE_SENSOR_H */
