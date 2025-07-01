#crtp 
We want tasks to be able to cooperate, for this objective they need to be able to share resources like memory, files, etc.
As we have seen when talking about [[Threads|threads]], they allow us to share these resources but they don't ensure that we have correct communication and synchronization among threads.The same for processes and functions like `mmap` that map a part of the address space of two processes refer to the same memory.

For instance, they must not try to use a certain data item if it has not been set up properly. Otherwise inconsistent data may be accessed, e.g a linked list in shared memory requires proper link setting that may be corrupted when the two tasks try to concatenate a new element concurrently.
Errors due to the unexpected interleaving of actions over shared data structures are often referred to as race conditions.

An example of race condition is: two threads try to increment variable x but one thread reads the value of x before the value incremented by the other thread is stored: what happens is we would expect x to be incremented by 2 but is only incremented by 1.

We call sections of code that access shared information `critical sections` and to ensure correctness we protect these sections with locks that allow only one task at a time to execute that code.
In this way every time a task wants to access a shared object it must:
1. Acquire the lock of the shared object (and wait if it's not available)
2. Use the shared object
3. Release the lock so that other tasks can use the object in the future

In any case, four conditions must be satisfied in order to have an acceptable solution:
1. It must really work, that is, it must prevent any two processes from simultaneously executing code within critical regions pertaining to the same shared object.
2. Any process that is busy doing internal operations, that is, is not currently executing within a critical region, must not prevent other processes from entering their critical regions, if they so decide.
3. If a process wants to enter a critical region, it must not have to wait forever to do so. This condition guarantees that the process will eventually make progress in its execution.
4. It must work regardless of any low-level details about the hardware or software architecture. For example, the correctness of the solution must not depend on the number of processes in the system, the number of physical processors, or their relative speed.

# How to implement locks

## Naive lock
A naive solution would be to use a shared int as a lock, this does not work because the shared int would have the same problem as any other shared variable. This can cause race conditions on the lock itself.

Also in this solution the process must keep checking the variable, this is called busy-waiting and is very wasteful.

## Hardware assisted locks 
A lock can be implemented by using the `test_and_set(int *p)` function provided by CPUs, which takes and address of a word and atomically:
1. reads the value v of the word referenced by the pointer p
2. sets the word pointed by p to 1
3. puts v into a register
This instruction ensures atomicity also in multicore environments because it locks the memory bus.

(an alternative is XCHNG which exchanges memory/register with register)

Still the task busy-waits for the lock even with this method. Also this method does not guarantee fairness, a faster task can always steal the lock.

## Software lock: Peterson
In the slides in PDF. Forse errore che dice condition = false dovrebbe essere true
```cpp
//Global Variables
int flag[2] = {0, 0};
int turn=0;
//Enter critical section
void entry(int pid) {
	int other = 1-pid;
	flag[pid] = 1;
	turn = pid;
	while(flag[other] == 1 && turn == pid);
}
//Exit critical section
void exit(int pid) {
	flag[pid] = 0;
}
```