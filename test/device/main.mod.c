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
	{ 0xa7a5f96c, "param_array_ops" },
	{ 0xda568a3d, "param_ops_charp" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x37456636, "class_destroy" },
	{ 0xa9de6a9e, "device_destroy" },
	{ 0x76f5a439, "device_create" },
	{ 0x1cfca29, "__class_create" },
	{ 0x8b4bb3fd, "__register_chrdev" },
	{ 0x712f55fe, "cpu_hwcaps" },
	{ 0x664d39db, "try_module_get" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xb38ad4b, "cpu_hwcap_keys" },
	{ 0x14b89635, "arm64_const_caps_ready" },
	{ 0x52a3a04d, "module_put" },
	{ 0xc5850110, "printk" },
	{ 0x1fdc7df2, "_mcount" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "BD0B9C36022E801AAA12F5A");
