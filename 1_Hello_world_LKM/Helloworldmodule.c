#include <linux/module.h>
#include <linux/init.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachana K Kulkarni");
MODULE_DESCRIPTION("A hello world LKM following Johannes's tutorial");

/**
 *Function called when module is loaded into the kernel
 */
static int __init my_init(void) {
	printk("Hello, Kernel!\n");
	return 0;
}

/**
 *Function called when module is removed from the kernel
 */
static void __exit my_exit(void) {
	printk("Goodbye, Kernel\n");
}

module_init(my_init);
module_exit(my_exit);
