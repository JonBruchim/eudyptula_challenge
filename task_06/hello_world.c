#include <linux/module.h>
#include <linux/kernel.h>

#include "eudyptula_misc_drive.h"

static int __init helloworld_init(void)
{
	pr_info("helloworld_init\n");
	misc_register(&eudyptula_misc_dev);

	return 0;
}

static void  __exit helloworld_exit(void)
{
	pr_info("helloworld_exit\n");
	misc_deregister(&eudyptula_misc_dev);
}

module_init(helloworld_init);
module_exit(helloworld_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonbru");
MODULE_DESCRIPTION("hello world module");
