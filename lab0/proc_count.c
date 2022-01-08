#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>


/*static const struct file_operations proc_count_fops {
	.owner = THIS_MODULE,
};*/
static struct proc_dir_entry *proc_count_dir;
static int proc_count_show( struct seq_file *m, void *v) {
	int i = 0;
	struct task_struct *p = NULL;
	for_each_process(p) {
		++i;
		//pr_info("increment\n");
	}
	seq_printf(m, "%d\n",i);
	//seq_printf(m, "Does this work?");
	return 0;
}

static int __init proc_count_init(void)
{
	proc_count_dir = proc_create_single("count", 0, NULL, proc_count_show);
	
	pr_info("proc_count: init\n");
	return 0;
}

static void __exit proc_count_exit(void)
{
	proc_remove(proc_count_dir);
	pr_info("proc_count: exit\n");
}


module_init(proc_count_init);
module_exit(proc_count_exit);

MODULE_AUTHOR("Vincent Liang");
MODULE_DESCRIPTION("Show the number of current running processes.");
MODULE_LICENSE("GPL");
