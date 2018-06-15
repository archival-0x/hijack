obj-m := name_of_the_module.o
KDIR := /lib/modules/`uname -r`/build
PWD := `pwd`
default:
		make -C $(KDIR) M=$(PWD) modules
