

/****************************************************************************
 * vts-v2f401rc/src/vts_panic.c
 *
 *   Copyright (C) Pi Labs Bangladesh Ltd
 *   Author: Omar Faruk
 *   Date: 09/10/2018
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
#include <nuttx/vts/panic.h>
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


struct vts_panic_lower
{
    FAR const struct panic_ops* ops;
};

static int panic_config(FAR struct panic_lower *lower);
static int panic_getstatus(FAR struct panic_lower *lower,FAR struct panic_status* status);
static int panic_ioctl(FAR struct panic_lower *lower, int cmd, unsigned long arg);

static struct vts_panic_lower panic_lower;

static const struct panic_ops vts_panic_ops =
{
    .config = panic_config,
    .ioctl = panic_ioctl,
    .getstatus = panic_getstatus,
};

static int panic_config(FAR struct panic_lower* lower)
{
    (void) lower;

    stm32_configgpio(PANIC_MONITOR);

    return OK;
}

static int panic_getstatus(FAR struct panic_lower* lower, FAR struct panic_status* status)
{
    (void) lower;

    status->on = stm32_gpioread(PANIC_MONITOR);

    return OK;
}

static int panic_ioctl(FAR struct panic_lower* lower, int cmd, unsigned long arg)
{
    return -ENOSYS;
}

void vts_panic_init()
{
    FAR struct vts_panic_lower * priv = &panic_lower;

    priv->ops = &vts_panic_ops;

    (void) panic_register("/dev/panic",(FAR struct panic_lower*)priv);
}
