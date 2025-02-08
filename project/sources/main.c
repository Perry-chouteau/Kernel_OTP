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
extern char *client_key;
extern int timeout;
extern int otp_type;
extern char *code_array[];

MODULE_AUTHOR("OTP");
MODULE_DESCRIPTION("An otp");

static int __init otp_init(void)
{
    static int i = 0;

    pr_info("otp_init\n");
    printk(KERN_INFO "timeout: %s\n", client_key);
    printk(KERN_INFO "timeout: %d\n", timeout);
    printk(KERN_INFO "ot_type: %s\n", (otp_type)? "true": "false");
    
    while (code_array[i] != NULL) {
        printk(KERN_INFO "%i: %s\n", i, code_array[i]);
        ++i;
//        if (code_array[i] == NULL) {
//            i = 0;
//        }
    }

    return 0;
}

static void __exit otp_exit(void)
{
    pr_info("otp_exit\n");
}

module_init(otp_init); 
module_exit(otp_exit); 
 
MODULE_LICENSE("GPL");