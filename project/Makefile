obj-m += otp.o

BUILD_DIR := build/

SRC_DIR := sources/

SRC_FILES := main.o \
			params.o \
			device.o \
			otp_sysfs.o

otp-objs := $(addprefix $(SRC_DIR), $(SRC_FILES))

PWD := $(CURDIR)

#INC_DIR := includes/
#EXTRA_CFLAGS += -I $(PWD)/$(INC_DIR)
#KCFLAGS += -I$(PWD)/$(INC_DIR)

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules	

clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	@rm -f otp_client

fall: all
	@rm -rf $(BUILD_DIR)
	@mkdir $(BUILD_DIR)
	@mv -f $(SRC_DIR)*.*.cmd $(CURDIR)
	@mv -f *.o *.ko *.mod.c *.symvers *.mod *.order $(BUILD_DIR) # *.*.cmd

fclean: clean
	@rm $(BUILD_DIR)

re: clean all

fre: fclean fall

client:
	$(CC) -o otp_client sources/otp_client.c

.PHONY: all fall clean fclean re fre client