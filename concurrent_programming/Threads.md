#crtp 
Sometimes we may want to share resources (memory, open files etc) between multiple tasks.
This can be difficult to do with multiple processes since they are independent and don't share memory.
This means we have distinct concurrent activities but we want them to share resources for this we can use threads and manage all these activities as a group and share system resources, such as files, devices, and network connections.

We use a single process but multiple threads.

Threads inside the same process have some shared information and some private information, they share the page table and open files (since they have the same virtual address space). They also share global and static variables and the code of the program.
The thread specific info is:
- processor register, including PC
- Local program variables which are held in a per-thread stack, this means that multiple threads can be running the same routine without one affecting the values of the variables in the routine of the other.

Using threads instead of processes makes it easy to communicate across tasks using shared memory.
The shared memory though is not enough to ensure correct communication and synchronization among threads.

Both [[Threads|threads]] and [[Processes|processes]] are managed by the OS scheduler.