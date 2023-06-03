#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init helloworld_init(void) {
    pr_info("Hello world !\n");
    return 0;
}
module_init(helloworld_init);

static void __exit helloworld_exit(void) {
    pr_info("End of the world !\n");
    return;
}
module_exit(helloworld_exit);

MODULE_AUTHOR("Max D");
MODULE_DESCRIPTION("helloworld module test");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");