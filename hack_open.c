#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alan <ex0dus@codemuch.tech>");
MODULE_VERSION("0.0.1");
MODULE_DESCRIPTION("We hack the kernel");

extern void *sys_call_table[];
old_open = sys_call_table[__NR_open];
sys_call_table[__NR_open] = new_open;

static int __init
init_module(void)
{
    printk(KERN_INFO "Welcome to Kernel Town!\n");
    return 0;
}

asmlinkage int new_open(const char *filename, int flags, int mode)
{
    /* do some malicious stuff here */
    printk(KERN_INFO "Hackering open()\n");

    /* hey, let's pretend nothing happened */
    ret = (*old_open)(filename, flags, mode);

    return ret;
}

static void __exit
cleanup_module(void)
{
    printk(KERN_INFO "We are now leaving Kernel Town! Thanks for the stay!\n");
    return;
}

module_init(init_module);
module_exit(cleanup_module);
