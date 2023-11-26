
CONFIG_MODULE_SIG=n

PWD = `pwd`
KERNEL_FOLDER := /lib/modules/$(shell uname -r)/build

PLATFORM := $(shell uname -m)

ifeq ($(XOF_SUPPORTED), Yes)
KBUILD_CFLAGS_MODULE += -D_XOF
lib_NAME := libXofFrameGrabber.a
MODULE_NAME := xofframegrabber
else
lib_NAME := libCxpFrameGrabber.a
MODULE_NAME := cxpframegrabber
endif

ifeq ($(PLATFORM), x86_64)
HAS_ENTRY = $(shell grep "CONFIG_HAVE_FENTRY=y" /boot/config-`uname -r`)
ifneq ($(HAS_ENTRY), )
GCC_VERSION = gcc4_8
else
GCC_VERSION = gcc4_4
endif
endif

EXTRA_CFLAGS += -D_UNIX_ -D_PT_KERNEL_ 

INCLUDE_DIR = -I$(src)/./inc
ccflags-y := $(INCLUDE_DIR)

obj-m += ${MODULE_NAME}.o 
${MODULE_NAME}-y := 			\
	mv_atomic.o 		\
	mv_device.o			\
	mv_event.o 			\
	mv_kthread.o 		\
	mv_lock.o 			\
	mv_memory.o 		\
	mv_memorymap.o 		\
	mv_misc.o 			\
	mv_time.o 			\
	mv_io.o 			\
	mv_workqueue.o 		\
	mv_module.o 		\
	mv_dma.o			\
	mv_socket.o			\
    drvmodlib.o

all:
ifeq ($(PLATFORM), x86_64)
	ar -x $(PLATFORM)/$(GCC_VERSION)/$(lib_NAME)
else ifeq ($(PLATFORM), i686)
	ar -x i386/$(lib_NAME)
else
	ar -x $(PLATFORM)/$(lib_NAME)
endif
	@make -C $(KERNEL_FOLDER) M=$(PWD) modules

clean:
	@rm -rf *.o *.o.* .??* ${MODULE_NAME}.mod.c Module.markers Module.symvers modules.order *.ko
install:
	/sbin/insmod ${MODULE_NAME}.ko
remove:
	/sbin/rmmod ${MODULE_NAME}
