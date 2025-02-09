# OTP Kernel Module

## Description

OTP stands for One Time password
OTP will use linux kernel module I'm currently using ubuntu version 

## Developers

Perry Chouteau perry.chouteau@outlook.com
Erwan Cariou

If you have any problems don't hesitate to create an issue or email here: perry.chouteau@outlook.com.

## Usage

### Insert module

```sh
cd project/

make

sudo rmmod otp.ko

sudo insmod otp.ko
```

### Get a code

sudo cat /dev/otp

### Edit params

```sh
#edit timeout
sudo sh -c "echo 5 > /sys/module/otp/parameters/timeout"
#edit otp_type 0=loopcode 1=gencodewith clientkey
sudo sh -c "echo 0 > /sys/module/otp/parameters/otp_type"
#edit  
sudo sh -c "echo 0 > /sys/module/otp/parameters/otp_type"
sudo sh -c "echo 0 > /sys/module/otp/parameters/otp_type"
```