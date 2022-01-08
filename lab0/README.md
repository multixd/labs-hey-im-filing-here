# A Kernel Seedling

Show the number of processes currently running.

## Building

Create the kernel module with module_init() and exit it with module_exit().
Use proc_create_single() to create an instance of proc_directiry_entry, and exit with proc_exit().
Create a show function proc_count_show(), and pass this into proc_create_single().
Use for_each_process() inside show function  to check the number of processes, and seq_printf() to print the number.

## Running

To run the kernel module, go into the directory of lab0 inside cs111. 
Enter the command "ls" and check if the file proc_count.ko pops up.
If not, enter the command "make", and now proc_count.ko should exist.
Enter "sudo insmod proc_count.ko" in order to insert the kernel module so that we can use it.
Enter "cat /proc/count" to show how many processes are currently running.



## Cleaning Up

To remove the kernel module after inserting it, enter "sudo rmmod proc_count"
We can check if the module is removed using "lsmod | grep proc_count"
If proc_count does not exit, nothing should show up.
## Testing

Kernel release 5.14.8-arch1-1

