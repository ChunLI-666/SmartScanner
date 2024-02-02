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
	{ 0xdd8f8694, "module_layout" },
	{ 0x7e322334, "alloc_pages_current" },
	{ 0x4ddb27b7, "cdev_alloc" },
	{ 0x22b90774, "cdev_del" },
	{ 0x428db41d, "kmalloc_caches" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x2064fa56, "cdev_init" },
	{ 0xf9a482f9, "msleep" },
	{ 0x948ed22b, "__put_devmap_managed_page" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0xb3635b01, "_raw_spin_lock_bh" },
	{ 0x87cdb6e0, "skb_copy" },
	{ 0x22e92418, "device_destroy" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x999e8297, "vfree" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0x5ab904eb, "pv_ops" },
	{ 0xa6521794, "kthread_create_on_node" },
	{ 0xb31c1837, "kthread_bind" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x356461c8, "rtc_time64_to_tm" },
	{ 0xfb578fc5, "memset" },
	{ 0xd38cd261, "__default_kernel_pte_mask" },
	{ 0x56b1771b, "current_task" },
	{ 0xc5850110, "printk" },
	{ 0x87d7b3f5, "kthread_stop" },
	{ 0x9ec6ca96, "ktime_get_real_ts64" },
	{ 0xacf3ff14, "vmap" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xf1969a8e, "__usecs_to_jiffies" },
	{ 0x7749276a, "device_create" },
	{ 0x30cb0399, "init_net" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x62a38e34, "nf_register_net_hook" },
	{ 0xc7fbe83a, "vm_insert_page" },
	{ 0xfe5d4bb2, "sys_tz" },
	{ 0xbbea7e99, "nf_unregister_net_hook" },
	{ 0xc4952f09, "cdev_add" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0xb1058e35, "__free_pages" },
	{ 0xb601be4c, "__x86_indirect_thunk_rdx" },
	{ 0x49c41a57, "_raw_spin_unlock_bh" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x1000e51, "schedule" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0x7e736549, "kfree_skb" },
	{ 0x47941711, "_raw_spin_lock_irq" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0x6bb70076, "wake_up_process" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0xca7a3159, "kmem_cache_alloc_trace" },
	{ 0xdbf17652, "_raw_spin_lock" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x37a0cba, "kfree" },
	{ 0x94961283, "vunmap" },
	{ 0x69acdf38, "memcpy" },
	{ 0xb65e5a32, "class_destroy" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0xf4ba80ad, "skb_copy_bits" },
	{ 0x2871e975, "__class_create" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x428e81bf, "__put_page" },
	{ 0xfb8ca8d6, "get_user_pages_fast" },
	{ 0x587f22d7, "devmap_managed_key" },
	{ 0x8a35b432, "sme_me_mask" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A6475F10784541B5D25C930");
