

obj-m += misc_drive.o
misc_drive-objs := eudyptula_misc_drive.o hello_world.o 

.PHONY: all clean

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
