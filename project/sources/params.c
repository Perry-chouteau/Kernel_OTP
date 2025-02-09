/**
 * @file device.c
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <linux/kernel.h> /* We are doing kernel work */ 
#include <linux/module.h> /* Specifically, a module  */ 
 
/**
 * @brief client key
 */
char *client_key = "changeme";
module_param(client_key, charp, 0664);
MODULE_PARM_DESC(client_key, "client key is used to make code unique for each client");

/**
 * @brief timeout in seconds
 */
int timeout = 10;
module_param(timeout, int, 0664);
MODULE_PARM_DESC(timeout, "Interger define when to load a new code in second");

/**
 * @brief otp_type LOOP: loop over a list of string. GEN: generate a code with client key.
 */
enum type_t {
    LOOP = 0,
    GEN = 1,
};

int otp_type = LOOP;
module_param(otp_type, int, 0664);
MODULE_PARM_DESC(otp_type, "OTP type: 0=loop over a list of code,1=gen a code using a key and time");

/**
 * @brief Loop
 * 
 */
char *code_array[] = { 
    "toto", 
    "tata", 
    "titi",
    "tete",
    "tutu", 
    NULL
};

module_param_array(code_array, charp, NULL, 0000);
MODULE_PARM_DESC(code_array, "An array of codes");
