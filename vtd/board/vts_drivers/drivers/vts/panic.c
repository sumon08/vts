/****************************************************************************
 * drivers/vts_sensors/panic.c
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
#include <nuttx/vts/panic.h>


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

struct panic_upper
{
    FAR char* path;
    FAR struct panic_lower* lower;
};

static ssize_t panic_read (FAR struct file* filep, FAR char *buffer, size_t bufflen);
static ssize_t panic_write(FAR struct file* filep, FAR const char* buffer, size_t buflen);
static int     panic_ioctl(FAR struct file* filep, int cmd, unsigned long arg);

static const struct file_operations panic_fops =
{
    0,            /* open */
    0,            /* close */
    panic_read,  /* read */
    panic_write ,/* write */
    0,            /* seek */
    panic_ioctl  /* ioctl */
};

static ssize_t panic_read (FAR struct file* filep, FAR char *buffer, size_t len)
{
    return 0;
}
static ssize_t panic_write(FAR struct file* filep, FAR const char* buffer, size_t len)
{
    return len;
}

static int panic_ioctl(FAR struct file* filep, int cmd, unsigned long arg)
{

    FAR struct inode*           inode = filep->f_inode;
    FAR struct panic_upper*    upper ;
    FAR struct panic_lower*    lower;
    int                         ret ;
    FAR struct panic_status*   status;

    m_info("cmd %d arg: %ld\n", cmd, arg);

    upper = inode->i_private;
    DEBUGASSERT(upper != NULL);
    lower = upper->lower;
    DEBUGASSERT(lower != NULL);

    switch (cmd)
    {


        case PANIC_IOC_INIT:
            if(lower->ops->config)
            {
                ret = lower->ops->config(lower);
            }
            else
            {
                ret = -ENOSYS;
            }
            break;

        case PANIC_IOC_STATUS:
            if(lower->ops->getstatus)
            {
                status = (FAR struct panic_status*) ((uintptr_t) arg);
                if(status)
                {
                    ret = lower->ops->getstatus(lower,status);
                }
                else
                {
                  ret = -EINVAL;
                }
            }
            else
            {
                ret = -ENOSYS;
            }
            break;

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

FAR void *panic_register(FAR const char *path, FAR struct panic_lower *lower)
{
    FAR struct panic_upper *upper;
    int ret;

    DEBUGASSERT(path && lower);

    upper = (FAR struct panic_upper*)  kmm_zalloc(sizeof(struct panic_upper));

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

    ret = register_driver(path, &panic_fops, 0666, upper);
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

void panic_unregister(FAR void *handle)
{
    FAR struct panic_upper *upper;
  FAR struct panic_lower *lower;

  upper = (FAR struct panic_upper*) handle;
  DEBUGASSERT(upper != NULL);
  lower = upper->lower;
  DEBUGASSERT(lower != NULL);

  m_info("Unregistering: %s\n", upper->path);


  (void) unregister_driver(upper->path);

  kmm_free(upper->path);
  kmm_free(upper);
}
