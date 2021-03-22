

/****************************************************************************
 * vts-v2f401rc/src/vts_loudhorn.c
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
#include <nuttx/vts/loudhorn.h>
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


struct vts_loudhorn_lower
{
    FAR const struct loudhorn_ops* ops;
};

static int loudhorn_config(FAR struct loudhorn_lower *lower);
static int loudhorn_on(FAR struct loudhorn_lower *lower);
static int loudhorn_off(FAR struct loudhorn_lower *lower);
static int loudhorn_ioctl(FAR struct loudhorn_lower *lower, int cmd, unsigned long arg);

static struct vts_loudhorn_lower loudhorn_lower;

static const struct loudhorn_ops vts_loudhorn_ops =
{
    .config = loudhorn_config,
    .ioctl = loudhorn_ioctl,
    .on = loudhorn_on,
    .off = loudhorn_off
};

static int loudhorn_config(FAR struct loudhorn_lower* lower)
{
    (void) lower;

    stm32_configgpio(LOUDHORN_CONTROL);

    return OK;
}

static int loudhorn_ioctl(FAR struct loudhorn_lower* lower, int cmd, unsigned long arg)
{
    return -ENOSYS;
}

static int loudhorn_on(FAR struct loudhorn_lower* lower)
{
    (void) lower;
    stm32_gpiowrite(LOUDHORN_CONTROL,1);
    return OK;
}

static int loudhorn_off(FAR struct loudhorn_lower* lower)
{
    (void) lower;
    stm32_gpiowrite(LOUDHORN_CONTROL,0);
    return OK;
}

void vts_loudhorn_init()
{
    FAR struct vts_loudhorn_lower * priv = &loudhorn_lower;

    priv->ops = &vts_loudhorn_ops;

    (void) loudhorn_register("/dev/loudhorn",(FAR struct loudhorn_lower*)priv);
}
