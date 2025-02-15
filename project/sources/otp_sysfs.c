#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h> // For kmalloc and kfree

#define KEY_SIZE 80

extern char *client_key;
extern int timeout;
extern int otp_type;
extern char *code_array[];

static struct kobject *otp_kobj;

static ssize_t client_key_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%s\n", client_key);
}

static ssize_t client_key_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    size_t len;

    pr_info("client_key_store called with buf: %s, count: %zu\n", buf, count);

    // Ensure the input is not too long
    if (count > KEY_SIZE) {
        pr_err("client_key_store: input too long\n");
        return -EINVAL;
    }

    // Ensure client_key is not NULL
    if (!client_key) {
        pr_err("client_key_store: client_key is NULL\n");
        return -ENOMEM;
    }

    // Copy the input buffer to client_key, removing any newline character
    strncpy(client_key, buf, count);
    client_key[count - 1] = '\0'; // Null-terminate the string

    // Remove any trailing newline character
    len = strlen(client_key);
    if (len > 0 && client_key[len - 1] == '\n') {
        client_key[len - 1] = '\0';
    }

    pr_info("client_key updated to: %s\n", client_key);
    return count;
}

static ssize_t timeout_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", timeout);
}

static ssize_t timeout_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    sscanf(buf, "%d", &timeout);
    return count;
}

static ssize_t otp_type_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", otp_type);
}

static ssize_t otp_type_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    sscanf(buf, "%d", &otp_type);
    return count;
}

static struct kobj_attribute client_key_attribute = __ATTR(client_key, 0664, client_key_show, client_key_store);
static struct kobj_attribute timeout_attribute = __ATTR(timeout, 0664, timeout_show, timeout_store);
static struct kobj_attribute otp_type_attribute = __ATTR(otp_type, 0664, otp_type_show, otp_type_store);

static struct attribute *otp_attrs[] = {
    &client_key_attribute.attr,
    &timeout_attribute.attr,
    &otp_type_attribute.attr,
    NULL,
};

static struct attribute_group otp_attr_group = {
    .attrs = otp_attrs,
};

int otp_sysfs_init(void)
{
    int retval;

    // Allocate memory for client_key
    client_key = kmalloc(KEY_SIZE, GFP_KERNEL);
    if (!client_key) {
        pr_err("Failed to allocate memory for client_key\n");
        return -ENOMEM;
    }

    otp_kobj = kobject_create_and_add("otp", kernel_kobj);
    if (!otp_kobj) {
        kfree(client_key); // Free allocated memory if kobject creation fails
        return -ENOMEM;
    }

    retval = sysfs_create_group(otp_kobj, &otp_attr_group);
    if (retval) {
        kobject_put(otp_kobj);
        kfree(client_key); // Free allocated memory if sysfs group creation fails
    }

    return retval;
}

void otp_sysfs_exit(void)
{
    if (otp_kobj) {
        sysfs_remove_group(otp_kobj, &otp_attr_group);
        kobject_put(otp_kobj);
        otp_kobj = NULL;
    }

    // Free memory allocated for client_key
    if (client_key) {
        kfree(client_key);
        client_key = NULL;
    }
}

MODULE_LICENSE("GPL");