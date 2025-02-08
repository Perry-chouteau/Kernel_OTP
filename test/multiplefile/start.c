/* 
 * start.c - Illustration of multi filed modules 
 */ 
 
#include <linux/kernel.h> /* We are doing kernel work */ 
#include <linux/module.h> /* Specifically, a module */ 
#include "one.h"

int init_module(void) 
{ 
    pr_info("Hello, world - this is the kernel speaking\n"); 
    printer();
    return 0; 
} 
 
MODULE_LICENSE("GPL");