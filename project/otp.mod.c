#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0x8e6a4c12, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x1fdc7df2, "_mcount" },
	{ 0x8da495af, "param_ops_int" },
	{ 0xb43f9365, "ktime_get" },
	{ 0xa9de6a9e, "device_destroy" },
	{ 0x8b4bb3fd, "__register_chrdev" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xda568a3d, "param_ops_charp" },
	{ 0xc5850110, "printk" },
	{ 0x76f5a439, "device_create" },
	{ 0x52a3a04d, "module_put" },
	{ 0x712f55fe, "cpu_hwcaps" },
	{ 0xb38ad4b, "cpu_hwcap_keys" },
	{ 0xa7a5f96c, "param_array_ops" },
	{ 0x37456636, "class_destroy" },
	{ 0x14b89635, "arm64_const_caps_ready" },
	{ 0x1cfca29, "__class_create" },
	{ 0x664d39db, "try_module_get" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1EC6D9CA897BE2913170934");
