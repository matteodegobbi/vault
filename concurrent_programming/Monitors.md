#crtp 
Monitors provide a higher level abstraction to guarantee synchronization between tasks.
A monitor is a composite object and contains:
- a set of shared data
- a set of methods that operate on them.
The shared data is hidden from the outside like in OOP, and can only be modified through the methods.
The monitor also guarantees mutual exclusion between its methods, only one task at a time can be inside one of the monitor's methods at the same time.

Other than mutual exclusion we can achieve task synchronization like in [[Semaphores and passive wait|semaphores]] with monitors, for this we can use condition variables.

Condition variables are variables that are hidden like the shared data and can only be modified by the monitor's methods, we define two primitives on condition variable `c`:
1. `wait(c)`: blocks the invoking process and releases the monitor in a single, atomic action
2. `signal(c)`: wakes up one of the processes blocked on `c`; it has no effect if no processes are blocked on `c`
The informal reasoning behind the primitives is that, if a process starts executing a monitor method and then discovers that it cannot finish its work immediately, it invokes wait on a certain condition variable. In this way, it blocks and allows other processes to enter the monitor and perform their job.
When one of those processes, usually by inspecting the monitor’s shared data, detects that the first process can eventually continue, it calls signal on the same condition variable.

Though we have to be careful with this to avoid ruining the mutual exclusion property by waking up a waiting process from inside the monitor, because this way we will have two tasks running inside the monitor at the same time.
1. One solution can be seen in the figure below and it that if `signal` is ever called from within a monitor method it must be the last instruction:
	![[Pasted image 20250703223044.png]]
2. A second solution is the one used in pthreads (POSIX) and consists in making the task awakened by a `signal` after it was in `wait` state get the lock before proceeding. This means that if task A calls `wait` on the condition variable, B sends `signal` to wake up A, B will proceed anyway but A will try to get the monitor lock before proceeding, this way if the lock is already taken by task B no race condition happens.
	 ![[Pasted image 20250703223733.png]]
There exist a 3rd approach (defined by Hoare) that consists of making `signal` block the calling process if it wakes up a waiting process. This is similar to solution 2 but it block the caller of signal instead of the woken process. 