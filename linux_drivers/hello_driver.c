#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int __init hello_driver_init(void) {
    printk("oh my god i built a linux driver\n");
    return 0;
}

static void __exit hello_driver_exit(void) {
    printk("goodbye driver...\n");
    return;
}

module_init(hello_driver_init);
module_exit(hello_driver_exit);

MODULE_AUTHOR("Luís Cruz");
MODULE_DESCRIPTION("Testing Linux Drivers.");
MODULE_LICENSE("GPL");