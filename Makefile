obj-m = hack_open.o
KERNEL = $(shell uname -r)
PWD = $(shell pwd)

all:
	make -C /lib/modules/$(KERNEL)/build M=$(PWD) modules

example:
	gcc -Wall -g example.c -o example

clean:
	make -C /lib/modules/$(KERNEL)/build M=$(PWD) clean
