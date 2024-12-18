/* 
 * hello-5.c - Illustrating the __init, __initdata and __exit macros. 
 */ 
#include <linux/init.h> /* Needed for the macros */ 
#include <linux/kernel.h> /* Array Size*/
#include <linux/module.h> /* Needed by all modules */ 
#include <linux/moduleparam.h> /* moduleparam */
#include <linux/printk.h> /* Needed for pr_info() */ 
#include <linux/stat.h> 

MODULE_AUTHOR("LKMPG"); 
MODULE_DESCRIPTION("A sample driver");

static int num __initdata = 3;

static int int_array[4] = {1, 2, 3, 4};
int count = 0;

static char *string = "PERRY";

/* module_param_array(name, type, num, perm); 
 * The first param is the parameter's (in this case the array's) name. 
 * The second param is the data type of the elements of the array. 
 * The third argument is a pointer to the variable that will store the number 
 * of elements of the array initialized by the user at module loading time. 
 * The fourth argument is the permission bits. 
 */
module_param_array(int_array, int, &count, 0000); /* put count into "count" variable */
MODULE_PARM_DESC(int_array, "int array");
module_param(string, charp, 0000);
MODULE_PARM_DESC(string, "A character string");

static int __init hello_5_init(void) 
{
    int i;

    pr_info("num: %d\n", num);
    pr_info("params array: %s\n", string);

    pr_info("int_array:\n");
    for (i = 0; i < ARRAY_SIZE(int_array); ++i) {
        pr_info("\t%d\n", int_array[i]);
    }
    if (count == ARRAY_SIZE(int_array)) {
        count = 0;
    }
    pr_info("got %d arguments for myintarray.\n", int_array[count]);
    return 0;
}
 
static void __exit hello_5_exit(void) 
{ 
    pr_info("Goodbye, %s 3\n", string); 
}
 
module_init(hello_5_init); 
module_exit(hello_5_exit); 
 
MODULE_LICENSE("GPL");