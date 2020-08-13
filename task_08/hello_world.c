#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include "linux/uaccess.h"
#include "linux/mutex.h"
#include "linux/jiffies.h"

struct dentry *parent_dentry;
int16_t id;
int8_t debugfs_buf[PAGE_SIZE];

DEFINE_MUTEX(debugfs_hello_mutex);

ssize_t debugfs_file_read(struct file *file, char *buf, size_t len, loff_t *offset);
ssize_t debugfs_file_write(struct file *file, const char *buf, size_t len, loff_t *offset);

struct file_operations fops = {
	.read = debugfs_file_read,
	.write = debugfs_file_write,
};

ssize_t debugfs_file_read(struct file *file, char *buf, size_t len, loff_t *offset)
{
	int error = 0;
	ssize_t read_len = 0;

	mutex_lock(&debugfs_hello_mutex);

	error = copy_to_user(buf, debugfs_buf, strlen(debugfs_buf));
	if (error)
		goto out;
	read_len = strlen(debugfs_buf);

out:
	mutex_unlock(&debugfs_hello_mutex);

	return read_len;
}

ssize_t debugfs_file_write(struct file *file, const char *buf, size_t len, loff_t *offset)
{
	int error = 0;
	ssize_t write_len = 0;

	mutex_lock(&debugfs_hello_mutex);

	error = copy_from_user(debugfs_buf, buf, len);
	if (error) {
		len = 0;
		goto out;
	}

	pr_info("read: %s", debugfs_buf);

	mutex_unlock(&debugfs_hello_mutex);

	return len;
}

static int __init helloworld_init(void)
{
	pr_info("init ma nigga\n");

	parent_dentry = debugfs_create_dir("eudyptula", NULL);

    debugfs_create_u16("id", S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH,
				      parent_dentry, &id);
	debugfs_create_u64("jiffies", S_IRUSR | S_IRGRP | S_IROTH,
				   parent_dentry, &jiffies);
	debugfs_create_file_size("foo",  S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR,
				parent_dentry, NULL,
				&fops,
				PAGE_SIZE);

	return 0;
}

static void  __exit helloworld_exit(void)
{
	pr_info("helloworld_exit\n");

	debugfs_remove_recursive(parent_dentry);
}

module_init(helloworld_init);
module_exit(helloworld_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonbru");
MODULE_DESCRIPTION("hello world module");
