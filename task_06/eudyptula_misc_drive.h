#ifndef __EUDYPTULA_MISC_DRIVE_H__
#define __EUDYPTULA_MISC_DRIVE_H__

#include <linux/miscdevice.h>
#include "linux/fs.h"

#define MISC_DEV_NAME "eudyptula_misc"

extern struct file_operations fops;
extern struct miscdevice eudyptula_misc_dev;

ssize_t device_read(struct file *file, char *buf, size_t len, loff_t *offset);
ssize_t device_write(struct file *file, const char *buf, size_t len, loff_t *offset);

#endif /* __EUDYPTULA_MISC_DRIVE_H__ */		