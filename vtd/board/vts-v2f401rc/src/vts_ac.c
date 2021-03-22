

/****************************************************************************
 * vts-v2f401rc/src/vts_ac.c
 *
 *   Copyright (C) Pi Labs Bangladesh Ltd
 *   Author: Omar Faruk
 *   Date: 10/10/2018
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
#include <nuttx/vts/ac.h>
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


struct vts_ac_lower
{
    FAR const struct ac_ops* ops;
};

static int ac_config(FAR struct ac_lower *lower);
static int ac_getstatus(FAR struct ac_lower *lower,FAR struct ac_status* status);
static int ac_ioctl(FAR struct ac_lower *lower, int cmd, unsigned long arg);

static struct vts_ac_lower ac_lower;

static const struct ac_ops vts_ac_ops =
{
    .config = ac_config,
    .ioctl = ac_ioctl,
    .getstatus = ac_getstatus,
};

static int ac_config(FAR struct ac_lower* lower)
{
    (void) lower;

    stm32_configgpio(AC_MONITOR);

    return OK;
}

static int ac_getstatus(FAR struct ac_lower* lower, FAR struct ac_status* status)
{
    (void) lower;

    status->on = stm32_gpioread(AC_MONITOR);

    return OK;
}

static int ac_ioctl(FAR struct ac_lower* lower, int cmd, unsigned long arg)
{
    return -ENOSYS;
}

void vts_ac_init()
{
    FAR struct vts_ac_lower * priv = &ac_lower;

    priv->ops = &vts_ac_ops;

    (void) ac_register("/dev/ac",(FAR struct ac_lower*)priv);
}
