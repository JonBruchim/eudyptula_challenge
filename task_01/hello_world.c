#include <linux/module.h>
#include <linux/kernel.h>

static int __init helloworld_init(void)
{
	printk("helloworld_init");

	return 0;
}

static void  __exit helloworld_exit(void)
{
	printk(KERN_DEBUG "helloworld_exit");
}

module_init(helloworld_init);
module_exit(helloworld_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonbru");
MODULE_DESCRIPTION("hello world module");