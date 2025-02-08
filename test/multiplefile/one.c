/* 
 * stop.c - Illustration of multi filed modules 
 */ 
 
#include <linux/kernel.h> /* We are doing kernel work */ 
#include <linux/module.h> /* Specifically, a module  */ 

void printer(void)
{ 
    printk(KERN_INFO "hello\n");
}

MODULE_LICENSE("GPL");