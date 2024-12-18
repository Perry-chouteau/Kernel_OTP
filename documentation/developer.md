# Docs

https://sysprog21.github.io/lkmpg/
https://www.kernel.org
https://kernelnewbies.org/Module

other:
https://tldp.org/LDP/lkmpg/2.6/html/x121.html

#  Unblock your coding day

Vscode, etc sudo mode from terminal:  `sudo chown -R k /home/k/` (used to create file, folder etc..)


# Start Developping a module

>Cmd to handle kernel modules: `apt install build-essential kmod`

• modprobe : charger / décharger un module
• insmod : charger un module
• rmmod : décharger un module
• modinfo : affiche les informations

**Install:**

- `apt install gcc make linux-headers-<uname -r>` get uname -r version before
- `apt install linux-source`

**Move:**

- `cp /usr/src/linux-source-<uname -r #only version number>/linux-source-<uname -r #only version number>.tar.bz2 /tmp`
- `cd /tmp && tar xvf linux-source-<uname -r #only version number>.tar.bz2`

# Compile

**Makefile**

```sh
obj-m += hello-0.o
PWD := $(CURDIR)

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

`make`

# Load / Unload

- `insmod main.ko`
- `rmmod main.ko`

- kprintf is always to the kernel log. read kernel log with: `dmesg` vs `cat /var/log/syslog` 

- `modinfo main.ko`

- `lsmod | grep main`. Warning: `hello-1.ko` write ***modules*** as `hello_1`.

- `ls -l /sys/module/<module_name>` //