obj-m += startstop.o
startstop-objs := start.o one.o stop.o

PWD := $(CURDIR)

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	

fall: all
	@rm -rf build
	@mkdir build
	@mv -f *.o *.ko *.mod.c *.*.cmd *.symvers *.mod *.order build/

clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

fclean: clean
	@rm build/

re: clean all

fre: fclean fall

.PHONY: all fall clean fclean re fre