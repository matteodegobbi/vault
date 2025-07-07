#crtp 

A process is a running instance of a computer program
A running program brings a set of information that change over time
   
A snapshot of the associated information must be saved by the OS when the program loses processor ownership. Process context include:
- The program and the other memory contents managed by the program, in particular the program stack and the global variables
- The current values of the processor registers, including the PC that holds the address of the next instruction to execute.
- The OS resources currently used by the process (e.g. open files)
 Process context must not be confused with the interrupt context: [[Context Switch VS Hardware Interrupt]].

![[pcb]]

 The OS has a list of PCBs (Process Control Block) to store this necessary info for all the processes, it would be necessary to copy all of the processes memory content when the process is switched but this is impossible for performance reasons, this is another reason for using [[Virtual Memory|virtual memory]], this way the actual content of the physical memory doesn't move and we just store the [[Virtual Memory|page table entries]] used by the process in the PCB (or a pointer to the page table like in the figure above).
The pages that are referenced in the page table in the PCB contain:
 - Program code (actually the PC and PID)
 - Program stack for local variables 
 - Static memory for global and static variables 
 - Heap memory
If the memory used by the process is large the context switch can take a long time.

The [[Cache, TLB, Pipelining|TLB]] must be flushed on context switch, this can be a problem for performance, as for the next process the TLB will be cold and all the first accesses will be misses.

Also the fact that we have virtual memory ensures us that an incorrect access in a process does not modify pages used by other processes, if this happens an exception occurs, stopping the process. If an incorrect access is done inside the correct page no exception occurs and we may not notice the bug.

---

# Process states

![[Pasted image 20241021171818.png]]

Ready: a process is able to execute instructions (not waiting for I/O etc)
Running: the scheduler has assigned a processor to this task and the task has total control of the processor
Wait: the task has requested an OS function and is waiting for the termination of the action and could not use the processor, while a process is waiting the OS will assign the processor another task.

A running process may be yielded by the OS which takes control of the processor to assign it to another task, this is done through an interrupt.

In general we can have tasks that we can run concurrently but need to share information with each other because they are related. 
In this case instead of using processes it may make sense to use [[Threads]].


