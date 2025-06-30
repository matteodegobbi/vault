#crtp
It's the component of the OS that takes care of deciding when and for how much to run a certain task ([[Threads]] or [[Processes]]) this selection is based on the priority of the task.

The ready task with the highest priority will be selected.

The scheduler has to make an action when:
1.  An interrupt occurs (e.g. I/O operation has ended, a task goes wait->ready)
2. A task makes an OS call going from running->wait (e.g. task initiates an I/O) 


In the first case a common source of interrupts is the Timer Interrupt which is issued at 60Hz for updating dynamic priorities and to update time-slices.

In this second case the involved OS code shall make a call to schedule() at the end of the corresponding action, this means that after the OS call is done the process that was in wait state might not be running immediately but be made ready.

# Scheduler data structures
![[Screenshot from 2025-06-30 12-37-45.png]]

The scheduler organizes ready tasks in queues based on their priority.
(except FIFO tasks, which have priorities from 1 to 99 so they run before every normal task, FIFO tasks run until they voluntarily yield, block for I/O or gets preempted by another real-time task with more priority). 

Every task is assigned a time slice to assure fairness among tasks of the same priority.
The function scheduler_tick() is called at every timer interrupt. It decreases the current time slice of the currently running task.
Whenever time time slice reaches zero, the task is moved to the expired queue and the processor will be assigned to the next task in the active queue (via a call to schedule())

###### CONTROLLA CHIEDI SE LO SWAP AVVIENE SOLO QUANDO TUTTE LE PRIORITA SONO VUOTE O SOLO LA PIU ALTA
If the active queue is empty for a given priority?????non ha senso fa starvation?????, it shall be swapped with the corresponding expired queue. 

Selection of the highest priority queue is performed in O(1) time using a bitmap.

Summarizing the scheduler works like this:
- start from the highest priority queue in the active queue and go through all the processes in that queue running them for their time-slice
- for each of them when they ends their time-slice, move them to the expired queue
- go to a lower priority (the new highest one) and repeat the same process
- when all the queue is empty swap it with the expired queue.

# Task priority
In Linux priorities go from 0 to 140 with lower being more important.
From 0 to 100 the priorities are static from 100 to 140 dynamic and can be changed by the OS.
Dynamic priority adjustment aims at providing improved fairness, in practice, a more fluid user interaction.

Priority adjustment is carried out during Timer interrupts, decreasing a counter associated with the currently running task, when the counter reaches 0 the priority of the task is lowered.
With a similar mechanism the priority of the waiting tasks is increased.
The rationale behind is to let tasks that tend to use less CPU should be given a higher priority.
In this way the computer shall not be blocked even if the highest priority task is running an infinite loop.

The advantage of dynamic task priority is that it allows for a better user interaction (CPU intensive high priority tasks don't stall other tasks) but it has some drawbacks:
Since we cannot guarantee that an important task will retain its priority we can get an increase in latency.

Latency of a task is the time between when the task becomes ready (some event has made it ready, e.g.  I/O terminated, interrupt etc) and when it starts running.

Task latency is affected by:
- The presence of tasks at higher or equal priority
- The number of available cores
- The OS latency
