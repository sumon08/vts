/****************************************************************************
 * drivers/vts_sensors/loudhorn.c
 *
 *   Copyright (C) Pi Labs Bangladesh Ltd
 *
 *
 ****************************************************************************/


#include <nuttx/config.h>

#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <poll.h>
#include <errno.h>

#include <nuttx/fs/fs.h>
#include <nuttx/fs/ioctl.h>
#include <nuttx/irq.h>
#include <nuttx/kmalloc.h>
#include <nuttx/vts/loudhorn.h>


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Debug ********************************************************************/
/* Non-standard debug that may be enabled just for testing the modem driver */

#ifdef CONFIG_SENSORS_DEBUG
#  define m_err     _err
#  define m_info    _info
#else
#  define m_err(x...)
#  define m_info(x...)
#endif

struct loudhorn_upper
{
    FAR char* path;
    FAR struct loudhorn_lower* lower;
};

static ssize_t loudhorn_read (FAR struct file* filep, FAR char *buffer, size_t bufflen);
static ssize_t loudhorn_write(FAR struct file* filep, FAR const char* buffer, size_t buflen);
static int     loudhorn_ioctl(FAR struct file* filep, int cmd, unsigned long arg);

static const struct file_operations loudhorn_fops =
{
    0,            /* open */
    0,            /* close */
    loudhorn_read,  /* read */
    loudhorn_write ,/* write */
    0,            /* seek */
    loudhorn_ioctl  /* ioctl */
};

static ssize_t loudhorn_read (FAR struct file* filep, FAR char *buffer, size_t len)
{
    return 0;
}
static ssize_t loudhorn_write(FAR struct file* filep, FAR const char* buffer, size_t len)
{
    return len;
}

static int loudhorn_ioctl(FAR struct file* filep, int cmd, unsigned long arg)
{

    FAR struct inode*             inode = filep->f_inode;
    FAR struct loudhorn_upper*    upper ;
    FAR struct loudhorn_lower*    lower;
    int                           ret ;
    //FAR struct loudhorn_status*   status;

    m_info("cmd %d arg: %ld\n", cmd, arg);

    upper = inode->i_private;
    DEBUGASSERT(upper != NULL);
    lower = upper->lower;
    DEBUGASSERT(lower != NULL);

    switch (cmd)
    {

        case LOUDHORN_IOC_INIT:
            if(lower->ops->config)
            {
                ret = lower->ops->config(lower);
            }
            else
            {
                ret = -ENOSYS;
            }
            break;

        case LOUDHORN_IOC_ON:
            if(lower->ops->on)
            {
                ret = lower->ops->on(lower);
            }
            else
            {
                ret = -ENOSYS;
            }
            break;

        case LOUDHORN_IOC_OFF:
            if(lower->ops->off)
            {
                ret = lower->ops->off(lower);
            }
            else
            {
                ret = -ENOSYS;
            }

        default:
            m_info("Forwarding unrecognized cmd: %d arg: %ld\n", cmd, arg);
            if (lower->ops->ioctl)
                {
                ret = lower->ops->ioctl(lower, cmd, arg);
                }
            else
                {
                ret = -ENOSYS;
                }
            break;
    }

    return ret;
}

FAR void *loudhorn_register(FAR const char *path, FAR struct loudhorn_lower *lower)
{
    FAR struct loudhorn_upper *upper;
    int ret;

    DEBUGASSERT(path && lower);

    upper = (FAR struct loudhorn_upper*)  kmm_zalloc(sizeof(struct loudhorn_upper));

    if (!upper)
    {
      m_err("ERROR: Upper half allocation failed\n");
      goto errout;
    }

    upper->lower = lower;
    upper->path = strdup(path);
    if (!upper->path)
        {
        m_err("ERROR: Path allocation failed\n");
        goto errout_with_upper;
        }

    ret = register_driver(path, &loudhorn_fops, 0666, upper);
    if (ret < 0)
        {
        m_err("ERROR: register_driver failed: %d\n", ret);
        goto errout_with_path;
        }

    return (FAR void*) upper;

    errout_with_path:
    kmm_free(upper->path);

    errout_with_upper:
    kmm_free(upper);

    errout:
    return NULL;
}

void loudhorn_unregister(FAR void *handle)
{
  FAR struct loudhorn_upper *upper;
  FAR struct loudhorn_lower *lower;

  upper = (FAR struct loudhorn_upper*) handle;
  DEBUGASSERT(upper != NULL);
  lower = upper->lower;
  DEBUGASSERT(lower != NULL);

  m_info("Unregistering: %s\n", upper->path);


  (void) unregister_driver(upper->path);

  kmm_free(upper->path);
  kmm_free(upper);
}
