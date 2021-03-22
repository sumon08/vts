

/****************************************************************************
 * vts-v2f401rc/src/vts_engine.c
 *
 *   Copyright (C) Pi Labs Bangladesh Ltd
 *   Author: Omar Faruk
 *   Date: 08/10/2018
 ****************************************************************************/


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
#include <nuttx/vts/engine.h>
#include <arch/board/board.h>
#include "stm32_gpio.h"
#include "vts-v2f401rc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifdef CONFIG_SENSORS_DEBUG
#  define m_err     _err
#  define m_info    _info
#else
#  define m_err(x...)
#  define m_info(x...)
#endif


struct vts_engine_lower
{
    FAR const struct engine_ops* ops;
};

static int engine_config(FAR struct engine_lower *lower);
static int engine_lock(FAR struct engine_lower *lower);
static int engine_unlock(FAR struct engine_lower *lower);
static int engine_getstatus(FAR struct engine_lower *lower,FAR struct engine_status* status);
static int engine_ioctl(FAR struct engine_lower *lower, int cmd, unsigned long arg);

static struct vts_engine_lower engine_lower;

static const struct engine_ops vts_engine_ops =
{
    .config = engine_config,
    .lock = engine_lock,
    .unlock = engine_unlock,
    .ioctl = engine_ioctl,
    .getstatus = engine_getstatus,
};

static int engine_config(FAR struct engine_lower* lower)
{
    (void) lower;

    stm32_configgpio(ENGINE_MONITOR);
    stm32_configgpio(ENGINE_CONTROL);

    return OK;
}

static int engine_lock(FAR struct engine_lower* lower)
{
    (void) lower;
    stm32_gpiowrite(ENGINE_CONTROL,1);
    nxsig_usleep(10000);

    return OK;
}

static int engine_unlock(FAR struct engine_lower* lower)
{
    (void) lower;
    stm32_gpiowrite(ENGINE_CONTROL,0);
    nxsig_usleep(10000);

    return OK;
}

static int engine_getstatus(FAR struct engine_lower* lower, FAR struct engine_status* status)
{
    (void) lower;

    status->on = stm32_gpioread(ENGINE_MONITOR);

    return OK;
}

static int engine_ioctl(FAR struct engine_lower* lower, int cmd, unsigned long arg)
{
    return -ENOSYS;
}

void vts_engine_init()
{
    FAR struct vts_engine_lower * priv = &engine_lower;

    priv->ops = &vts_engine_ops;

    (void) engine_register("/dev/engine",(FAR struct engine_lower*)priv);
}
