
CONFIG_MODULE_SIG=n

PWD = `pwd`
KERNEL_FOLDER := /lib/modules/$(shell uname -r)/build

PLATFORM := $(shell uname -m)

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

obj-m += cmlframegrabber.o 
cmlframegrabber-y := 			\
	mv_atomic.o 		\
	mv_device.o			\
	mv_event.o 			\
	mv_kthread.o 		\
	mv_lock.o 			\
	mv_memory.o 		\
	mv_memorymap.o 		\
	mv_misc.o 			\
	mv_time.o 			\
	mv_timer.o			\
	mv_io.o 			\
	mv_workqueue.o 		\
	mv_module.o 		\
	mv_dma.o			\
	mv_socket.o			\
	mv_platform.o		\
    drvmodlib.o

all:
ifeq ($(PLATFORM), x86_64)
	ar -x $(PLATFORM)/$(GCC_VERSION)/libCmlFrameGrabber.a
else ifeq ($(PLATFORM), i686)
	ar -x i386/libCmlFrameGrabber.a
else
	ar -x $(PLATFORM)/libCmlFrameGrabber.a
endif
	@make -C $(KERNEL_FOLDER) M=$(PWD) modules

clean:
	@rm -rf *.o *.o.* .??* cmlframegrabber.mod.c Module.markers Module.symvers modules.order *.ko
install:
	/sbin/insmod cmlframegrabber.ko
remove:
	/sbin/rmmod cmlframegrabber
