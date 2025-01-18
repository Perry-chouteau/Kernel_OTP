# GenCode

## Description

create device /dev/gencode

## Setup

move to the `readme`'s folder/

```sh
make

insmod gencode.ko
```

## Usage


```sh
cat /dev/gencode
```

## shut down
```sh
rmmod gencode.ko

make clean
```
