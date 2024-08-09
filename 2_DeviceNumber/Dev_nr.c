#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachana K Kulkarni");
MODULE_DESCRIPTION("Registers a device number and implements some callback functions");


/** Function is called when the device file is opened **/
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("dev_nr - open was called!\n");
	return 0;
}

/** Function is called when the device file is closed **/
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("dev_nr - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close
};

#define MYMAJOR 90

/**
 * Function called when module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	int retval;
	printk("Hello, Kernel!\n");
	/* register device nr. */
	retval = register_chrdev(MYMAJOR, "my_dev_nr", &fops);
	if(retval == 0) {
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
	}
	else if(retval > 0) {
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", retval>>20, retval&0xfffff);
	}
	else {
		printk("Could not register device number!\n");
		return -1;
	}
	return 0;
}

/**
 * Function called when module is unloaded from the kernel
 */
static void __exit ModuleExit(void) {
	unregister_chrdev(MYMAJOR, "my_dev_nr");
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
