#include "linux/uaccess.h"

#include "eudyptula_misc_drive.h"

struct file_operations fops = {
       .read = device_read,
       .write = device_write,
 };

struct miscdevice eudyptula_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
    .name = MISC_DEV_NAME,
    .fops = &fops,
};

char input_buf[20];
char *output_msg = "testing";

ssize_t device_read(struct file *file, char *buf, size_t len, loff_t *offset)
{
	int error = 0;

	pr_info("writing %s to user\n", output_msg);

	error = copy_to_user(buf, output_msg, strlen(output_msg));
	if (error)
		return 0;

	return strlen(output_msg);
}

ssize_t device_write(struct file *file, const char *buf, size_t len, loff_t *offset)
{
	int error = 0;

	error = copy_from_user(input_buf, buf, len);
	if (error)
		return 0;

	pr_info("read: %s",input_buf);

	return len;
}