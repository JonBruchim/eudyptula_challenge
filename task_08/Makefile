

obj-m += hello_world.o
misc_drive-objs := hello_world.o 

.PHONY: all clean

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
