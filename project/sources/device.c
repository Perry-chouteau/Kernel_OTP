/**
 * @file device.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-02-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <linux/atomic.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h> /* for sprintf() */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/uaccess.h> /* for get_user and put_user */
#include <linux/version.h>
#include <linux/time.h>
#include <linux/major.h>
#include <linux/mount.h>

#include <asm/errno.h>

#include "../includes/params.h"

/*  Prototypes - this would normally go in a .h file */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char __user *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "otp"   /* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80          /* Max length of the message from the device */
#define SECOND 1000000000LL // Define 1 second in nanoseconds

/* Global variables are declared as static, so are global within the file. */
static int major; /* major number assigned to our device driver */

enum
{
    CDEV_NOT_USED,
    CDEV_EXCLUSIVE_OPEN,
};

/* Is device open? Used to prevent multiple access to device */
static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED);

static char msg[BUF_LEN + 1]; /* The msg the device will give when asked */

static struct class *cls = NULL;

struct file_operations chardev_fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
};

int dev_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &chardev_fops);

    if (major < 0)
    {
        pr_alert("Registering char device failed with %d\n", major);
        return major;
    }

    pr_info("I was assigned major number %d.\n", major);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    cls = class_create(DEVICE_NAME);
#else
    cls = class_create(THIS_MODULE, DEVICE_NAME);
#endif
    device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

    pr_info("Device created on /dev/%s\n", DEVICE_NAME);

    return SUCCESS;
}

void dev_exit(void)
{
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);

    /* Unregister the device */
    unregister_chrdev(major, DEVICE_NAME);
}

/* Methods */

/**
 * @brief Sanitize the client key by removing newline characters.
 *
 * @param key The original client key.
 * @param sanitized_key The buffer to store the sanitized key.
 * @param len The length of the buffer.
 */
void sanitize_client_key(const char *key, char *sanitized_key, size_t len)
{
    size_t i, j = 0;
    for (i = 0; i < len && key[i] != '\0'; i++)
    {
        if (key[i] != '\n')
        {
            sanitized_key[j++] = key[i];
        }
    }
    sanitized_key[j] = '\0';
}

static int device_open(struct inode *inode, struct file *file)
{
    ktime_t kt;
    long long tmp;
    static long long nanoseconds = 0;
    static int counter = 0;

    // Prevent multiple simultaneous opens
    if (atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN))
        return -EBUSY;

    // Get the current time in nanoseconds since boot (not affected by system clock changes)
    kt = ktime_get();
    tmp = ktime_to_ns(kt);

    if (otp_type == false)
    {
        // Give Code
        // Update timeout only if the time has exceeded the previous timeout window
        if (tmp >= nanoseconds)
        {
            nanoseconds = tmp + (timeout * SECOND);
            counter++;
        }
        if (code_array[counter] == NULL)
        {
            counter = 0;
        }
        sprintf(msg, "%s\n", code_array[counter]);
    }
    else
    {
        // Generate Code
        char client_key_usable[BUF_LEN + 1];

        // Update timeout only if the time has exceeded the previous timeout window
        if (tmp >= nanoseconds)
        {
            nanoseconds = tmp + (timeout * SECOND);
        }
        sanitize_client_key(client_key, client_key_usable, strlen(client_key));
        sprintf(msg, "%s%lld\n", client_key_usable, nanoseconds % SECOND);
        memset(client_key_usable, 0, BUF_LEN + 1);
    }
    try_module_get(THIS_MODULE);

    return SUCCESS;
}

/* Called when a process closes the device file. */
static int device_release(struct inode *inode, struct file *file)
{
    /* Zero out the message buffer, to prevent sensitive data from being leaked !! */
    memset(msg, 0, sizeof(msg));

    /* We're now ready for our next caller */
    atomic_set(&already_open, CDEV_NOT_USED);

    /* Decrement the usage count, or else once you opened the file, you will
     * never get rid of the module.
     */
    module_put(THIS_MODULE);

    return SUCCESS;
}

/* Called when a process, which already opened the dev file, attempts to
 * read from it.
 */
static ssize_t device_read(struct file *filp,   /* see include/linux/fs.h   */
                           char __user *buffer, /* buffer to fill with data */
                           size_t length,       /* length of the buffer     */
                           loff_t *offset)
{
    /* Number of bytes actually written to the buffer */
    int bytes_read = 0;
    const char *msg_ptr = msg;

    if (!*(msg_ptr + *offset))
    {                /* we are at the end of message */
        *offset = 0; /* reset the offset */
        return 0;    /* signify end of file */
    }

    msg_ptr += *offset;

    /* Actually put the data into the buffer */
    while (length && *msg_ptr)
    {
        /* The buffer is in the user data segment, not the kernel
         * segment so "*" assignment won't work.  We have to use
         * put_user which copies data from the kernel data segment to
         * the user data segment.
         */
        put_user(*(msg_ptr++), buffer++);
        length--;
        bytes_read++;
    }

    *offset += bytes_read;

    /* Most read functions return the number of bytes put into the buffer. */
    return bytes_read;
}

/* Called when a process writes to dev file: echo "hi" > /dev/hello */
static ssize_t device_write(struct file *filp, const char __user *buff, size_t len, loff_t *off)
{
    pr_alert("Sorry, this operation is not supported.\n");
    if (buff != NULL)
    {
        pr_info("not null: %s", buff);
    }
    else
    {
        pr_info("is null");
    }
    return -EINVAL;
}

MODULE_AUTHOR("Perry Chouteau perry.chouteau@outlook.com");
MODULE_AUTHOR("Erwan Cariou");
MODULE_AUTHOR("Vincent Mardirossian");
MODULE_LICENSE("GPL");