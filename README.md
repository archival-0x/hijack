# hijack

System call hijacking using loadable kernel modules

## Introduction

This is an example of how we hijack the `open()` system call using loadable kernel modules. By overriding the functionality of `open` within kernel-space, we are able to manipulate execution throughout the entirety of the system, hence making this a _rootkit_.

## Compiling and Installing

The routine for overriding `open()`, `new_open()`, found within the `hack_open.c` file, is generic. The code only simply prints the contents of the arguments passed, but could definitely be modified for much more malicious purposes.

### 1. Set address of system call table

```
$ sudo cat /boot/System.map-`uname -r` | grep sys_call_table
```

Store the output of that into the `unsigned long * sys_call_table` variable in `hack_open.c` as a hexadecimal value type-coerced to `unsigned long`.


### 2. Compilation & Installation

```
make all
# Install kernel module
sudo insmod hack_open.ko
# Remove kernel module
rmmod hack_open
```

### 3. Test Example

```
make example
./example
```
