//Zixin Luo, Emily Hao
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <asm/current.h>
#include <linux/pid.h>

unsigned long **sys_call_table;

/* Structure Ancestor */
struct ancestry
{
	pid_t ancestor[10];
	pid_t siblings[100];
	pid_t children[100];
};

asmlinkage long (*ref_sys_cs3013_syscall1)(void);
/* Modify syscall2 so it can take parameter */
asmlinkage long (*ref_sys_cs3013_syscall2)(unsigned short *target_pid, struct ancestry *response);

asmlinkage long new_sys_cs3013_syscall1(void) {
  printk(KERN_INFO "\"'Hello world?!' More like 'Goodbye, world!' EXTERMINATE!\" -- Dalek");
  return 0;
}

/* Create new  syscall2 */
asmlinkage long new_sys_cs3013_syscall2(unsigned short *target_pid, struct ancestry *response) {
	
	//struct task_struct *child;//Record child process
	struct task_struct *task = pid_task(find_vpid(*target_pid), PIDTYPE_PID) ;//Record child process
	///struct task_struct *parent;	/* Obtain the process descriptor of its parent */
	//unsigned short *user =target_pid; 
	//if(copy-from-user(user, target_pid, sizeof(unsigned short)){
	//	return -EFAULT;
	//}
	
	//parent
	if(task->parent->pid!=1){
	int i = 0; 
	struct task_struct *ancestor; 
	for(ancestor = task; ancestor !=&init_task; ancestor = ancestor->parent){
		response->ancestor[i] = ancestor->pid;
		printk(KERN_INFO "the parent pid is %d\n", ancestor->pid); 
		}
	}else{
		response->ancestor[0] = -1; 
		printk(KERN_INFO "There is no ancestor"); 
	}
	
	//children 
	if(list_empty(&task->children)){
		int i = 0;
		struct task_struct *children;
		struct list_head *list; //List of all structure 
		list_for_each(list, &task->children) {
       			children = list_entry(list, struct task_struct, sibling);
        		response->children[i]= children->pid; 
			printk(KERN_INFO "The children pid is %d\n", &children->pid); 
			i++;
		}
	}else{
		response->children[0] = -1; 
		printk(KERN_INFO "There is no children in this %d\n", &task->parent->pid); 
	}
	//sibling
	if(list_empty(&task->sibling)){
		int i = 0; 
		struct task_struct *siblings; 
		struct list_head *listnd; //List of all structure
		list_for_each(listnd, &task->sibling){
			siblings = list_entry(listnd, struct task_struct, sibling);
			response->siblings[i] = siblings->pid; 
			printk(KERN_INFO "The children pid is %d\n", &siblings->pid);
			i++;
		}
	}else{
		response->siblings[0] = -1; 
		printk(KERN_INFO "There is no siblings in this %d\n", &task->parent->pid);
	}
	
	

  //printk(KERN_INFO "The target pid is %h", &target_pid);
  return 0;
}

static unsigned long **find_sys_call_table(void) {
  unsigned long int offset = PAGE_OFFSET;
  unsigned long **sct;
  
  while (offset < ULLONG_MAX) {
    sct = (unsigned long **)offset;

    if (sct[__NR_close] == (unsigned long *) sys_close) {
      printk(KERN_INFO "Interceptor: Found syscall table at address: 0x%02lX",
	     (unsigned long) sct);
      return sct;
    }
    
    offset += sizeof(void *);
  }
  
  return NULL;
}

static void disable_page_protection(void) {
  /*
    Control Register 0 (cr0) governs how the CPU operates.

    Bit #16, if set, prevents the CPU from writing to memory marked as
    read only. Well, our system call table meets that description.
    But, we can simply turn off this bit in cr0 to allow us to make
    changes. We read in the current value of the register (32 or 64
    bits wide), and AND that with a value where all bits are 0 except
    the 16th bit (using a negation operation), causing the write_cr0
    value to have the 16th bit cleared (with all other bits staying
    the same. We will thus be able to write to the protected memory.

    It's good to be the kernel!
  */
  write_cr0 (read_cr0 () & (~ 0x10000));
}

static void enable_page_protection(void) {
  /*
   See the above description for cr0. Here, we use an OR to set the 
   16th bit to re-enable write protection on the CPU.
  */
  write_cr0 (read_cr0 () | 0x10000);
}

static int __init interceptor_start(void) {
  /* Find the system call table */
  if(!(sys_call_table = find_sys_call_table())) {
    /* Well, that didn't work. 
       Cancel the module loading step. */
    return -1;
  }
  
  /* Store a copy of all the existing functions */
  ref_sys_cs3013_syscall1 = (void *)sys_call_table[__NR_cs3013_syscall1];
  ref_sys_cs3013_syscall2 = (void *)sys_call_table[__NR_cs3013_syscall2];

  


  /* Replace the existing system calls */
  disable_page_protection();

  sys_call_table[__NR_cs3013_syscall1] = (unsigned long *)new_sys_cs3013_syscall1;
  sys_call_table[__NR_cs3013_syscall2] = (unsigned long *)new_sys_cs3013_syscall2;

  

  
  enable_page_protection();
  
  /* And indicate the load was successful */
  printk(KERN_INFO "Loaded interceptor!");

  return 0;
}

static void __exit interceptor_end(void) {
  /* If we don't know what the syscall table is, don't bother. */
  if(!sys_call_table)
    return;
  
  /* Revert all system calls to what they were before we began. */
  disable_page_protection();
  sys_call_table[__NR_cs3013_syscall1] = (unsigned long *)ref_sys_cs3013_syscall1;
  sys_call_table[__NR_cs3013_syscall2] = (unsigned long *)ref_sys_cs3013_syscall2;

  

  enable_page_protection();

  printk(KERN_INFO "Unloaded interceptor!");
}

MODULE_LICENSE("GPL");
module_init(interceptor_start);
module_exit(interceptor_end);
