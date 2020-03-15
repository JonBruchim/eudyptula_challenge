#include "linux/unistd.h"


asmlinkage long sys_eudyptula(unsigned int low_id ,unsigned int high_id);

#define __NR_sys_eudyptula (__NR_syscalls)
__SYSCALL(__NR_sys_eudyptula, sys_eudyptula)

long do_eudyptula(unsigned int low_id ,unsigned int high_id)
{
	return 0;
}

SYSCALL_DEFINE1(unsigned int low_id ,unsigned int high_id)
{
	return do_eudyptula(fildes, 0);
}