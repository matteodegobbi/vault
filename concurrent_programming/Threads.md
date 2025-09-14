#crtp 
Sometimes we may want to share resources (memory, open files etc) between multiple tasks.
This can be difficult to do with multiple processes since they are independent and don't share memory.
This means we have distinct concurrent activities but we want them to share resources. 
For this we can use threads and manage all these activities as a group and share system resources, such as files, devices, and network connections.

We use a single process but multiple threads.

Threads inside the same process have some shared information and some private information, they share the page table and open files (since they have the same virtual address space). They also share global and static variables and the code of the program. Also the heap is in general shared.
The thread specific info is:
- processor registers, including PC
- Local program variables which are held in a per-thread stack, this means that multiple threads can be running the same routine without one affecting the values of the variables in the routine of the other.

**Summarizing:**
Shared across threads:
* Global vars
* Static vars
* Heap
* Program Code
* Page table
* File descriptors (in general OS resources)
NOT shared:
* Processor registers (like PC and others)
* Stack allocated vars

---

Using threads instead of processes makes it easy to communicate across tasks using shared memory.
The shared memory though is not enough to ensure correct communication and synchronization among threads (we need some kind of locking or synchronizing mechanism).

Both [[Threads|threads]] and [[Processes|processes]] are managed by the OS [[Scheduler|scheduler]]. 

With context switches between threads the page table will stay the same so the TLB does not need to be flushed, making the switch lighter.