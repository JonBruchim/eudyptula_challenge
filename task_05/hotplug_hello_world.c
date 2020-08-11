#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/hid.h>

#define RAZER_VENDOR_ID 0x1532
#define DEATHADDER_PRODUCT_ID 0x005c

int my_usb_probe(struct usb_interface *intf,
		      const struct usb_device_id *id);
void my_usb_disconnect(struct usb_interface *intf);

/* just as shown in hid/usbhid/usbkbd.c */
static const struct usb_device_id usb_kbd_id_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_KEYBOARD) },
	{ }						/* Terminating entry */
};

MODULE_DEVICE_TABLE(usb, usb_kbd_id_table);

struct usb_driver my_usb = {
	.name = "my_usb",
	.probe = my_usb_probe,
	.disconnect = my_usb_disconnect,
	.id_table = usb_kbd_id_table,
};

int my_usb_probe(struct usb_interface *intf,
		      const struct usb_device_id *id)
{
	pr_info("keyboard connected\n");

	return 0;
}

void my_usb_disconnect(struct usb_interface *intf)
{
	pr_info("keyboard disconnected\n");
}

static int __init helloworld_init(void)
{
	int err = 0;
	pr_info("helloworld_init\n");

	err = usb_register(&my_usb);

	if (err)
		pr_err("usb registration failed\n");

	return err;
}

static void  __exit helloworld_exit(void)
{
	pr_info("helloworld_exit\n");

	usb_deregister(&my_usb);
}

module_init(helloworld_init);
module_exit(helloworld_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonbru");
MODULE_DESCRIPTION("hello world module");
