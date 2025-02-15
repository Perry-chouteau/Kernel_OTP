/**
 * @file main.c
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
#include<linux/time.h>

#include <asm/errno.h> 

// Reference the parameter defined in params.c
#include "../includes/params.h"
#include "../includes/device.h"
#include "../includes/otp_sysfs.h"

MODULE_AUTHOR("OTP");
MODULE_DESCRIPTION("An otp");

static int __init otp_init(void)
{
    static int i = 0;

    pr_info("otp_init\n");
    printk(KERN_INFO "timeout: %s\n", client_key);
    printk(KERN_INFO "timeout: %d\n", timeout);
    printk(KERN_INFO "ot_type: %s\n", (otp_type)? "true": "false");
    printk(KERN_INFO "code:\n");
    while (code_array[i] != NULL) {
        printk(KERN_INFO "\t- %s\n", code_array[i]);
        ++i;
    }
    if (code_array[i] == NULL) {
        i = 0;
    }

    dev_init();
    otp_sysfs_init();
    return 0;
}

static void __exit otp_exit(void)
{
    otp_sysfs_exit();
    dev_exit();
}

module_init(otp_init); 
module_exit(otp_exit); 
 
MODULE_LICENSE("GPL");