obj-m += loopcode.o
#main-objs := chardev.o
#ccflags-objs := -I $(PWD)
PWD := $(CURDIR)

#CFLAGS=-std=c99

all:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
