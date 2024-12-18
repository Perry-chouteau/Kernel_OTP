6.5 chardev.c

The next code sample creates a char driver named chardev. You can dump its device file.

```sh
cat /proc/devices
```

(or open the file with a program) and the driver will put the number of times the device file has been read from into the file. We do not support writing to the file (like echo "hi" > /dev/hello ), but catch these attempts and tell the user that the operation is not supported. Don’t worry if you don’t see what we do with the data we read into the buffer; we don’t do much with it. We simply read in the data and print a message acknowledging that we received it.
In the multiple-threaded environment, without any protection, concurrent access to the same memory may lead to the race condition, and will not preserve the performance. In the kernel module, this problem may happen due to multiple instances accessing the shared resources. Therefore, a solution is to enforce the exclusive access. We use atomic Compare-And-Swap (CAS) to maintain the states, CDEV_NOT_USED and CDEV_EXCLUSIVE_OPEN , to determine whether the file is currently opened by someone or not. CAS compares the contents of a memory location with the expected value and, only if they are the same, modifies the contents of that memory location to the desired value. See more concurrency details in the 12 section.