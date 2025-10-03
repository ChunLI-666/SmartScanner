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
	{ 0x2f2c95c4, "flush_work" },
	{ 0x7e322334, "alloc_pages_current" },
	{ 0x2d3385d3, "system_wq" },
	{ 0x31e2d6ad, "dma_direct_unmap_sg" },
	{ 0x22b90774, "cdev_del" },
	{ 0x428db41d, "kmalloc_caches" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x2064fa56, "cdev_init" },
	{ 0xf9a482f9, "msleep" },
	{ 0x8f2c9fb7, "kernel_sendmsg" },
	{ 0x948ed22b, "__put_devmap_managed_page" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x1b0687ff, "uart_add_one_port" },
	{ 0x754d539c, "strlen" },
	{ 0x6565e06e, "sock_release" },
	{ 0xb3635b01, "_raw_spin_lock_bh" },
	{ 0xdf566a59, "__x86_indirect_thunk_r9" },
	{ 0x22e92418, "device_destroy" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x6e038551, "uart_unregister_driver" },
	{ 0x5bf5839c, "sock_create_kern" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x999e8297, "vfree" },
	{ 0xa89e9bec, "uart_update_timeout" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x5ab904eb, "pv_ops" },
	{ 0xa6521794, "kthread_create_on_node" },
	{ 0x6f638b55, "__platform_driver_register" },
	{ 0x6ca42632, "uart_remove_one_port" },
	{ 0xb31c1837, "kthread_bind" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x356461c8, "rtc_time64_to_tm" },
	{ 0xfb578fc5, "memset" },
	{ 0xbc47cbcd, "__tty_insert_flip_char" },
	{ 0xd38cd261, "__default_kernel_pte_mask" },
	{ 0x56b1771b, "current_task" },
	{ 0xc5850110, "printk" },
	{ 0x87d7b3f5, "kthread_stop" },
	{ 0x9ec6ca96, "ktime_get_real_ts64" },
	{ 0xacf3ff14, "vmap" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xfb481954, "vprintk" },
	{ 0xf1969a8e, "__usecs_to_jiffies" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0x7749276a, "device_create" },
	{ 0xf28d7f7b, "platform_device_unregister" },
	{ 0x2072ee9b, "request_threaded_irq" },
	{ 0x30cb0399, "init_net" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0xfe5d4bb2, "sys_tz" },
	{ 0x82072614, "tasklet_kill" },
	{ 0xc4952f09, "cdev_add" },
	{ 0x3a2f6702, "sg_alloc_table" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x9f984513, "strrchr" },
	{ 0xb1058e35, "__free_pages" },
	{ 0x2bf07e6f, "platform_device_register" },
	{ 0x49c41a57, "_raw_spin_unlock_bh" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x1000e51, "schedule" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0x47941711, "_raw_spin_lock_irq" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0x6bb70076, "wake_up_process" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0xca7a3159, "kmem_cache_alloc_trace" },
	{ 0xdbf17652, "_raw_spin_lock" },
	{ 0x9ea53d7f, "vsnprintf" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x37a0cba, "kfree" },
	{ 0x94961283, "vunmap" },
	{ 0x20d8bf1e, "dma_direct_map_sg" },
	{ 0x69acdf38, "memcpy" },
	{ 0x6a0dcd63, "kernel_bind" },
	{ 0xe9d397a0, "uart_register_driver" },
	{ 0xb65e5a32, "class_destroy" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x228eecdc, "tty_flip_buffer_push" },
	{ 0x7f5b4fe4, "sg_free_table" },
	{ 0xc5b6f236, "queue_work_on" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x9e7dd428, "platform_driver_unregister" },
	{ 0x4a453f53, "iowrite32" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x2871e975, "__class_create" },
	{ 0x25cf773d, "uart_get_baud_rate" },
	{ 0x74c9b7b5, "dma_ops" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x428e81bf, "__put_page" },
	{ 0xe484e35f, "ioread32" },
	{ 0xfb8ca8d6, "get_user_pages_fast" },
	{ 0xc1514a3b, "free_irq" },
	{ 0x587f22d7, "devmap_managed_key" },
	{ 0x8a35b432, "sme_me_mask" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "FED410E2324C7057119D720");
