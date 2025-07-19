#crtp 
# Real time systems
In concurrent programs we have non-determinism in terms of the interleaving of the processes execution. We need to avoid some of these interleavings if they lead to wrong results of the program. 
If we have a real time system with tight deadlines we need to disallow some interleavings that don't respect these deadlines.
We need to allow only interleavings that are acceptable from both the program correctness point of view and the real time point of view. 

General purpose schedulers emphasize:
1. Fairness: Each process gets a fair share of processor time
2. Efficiency: e.g. O(1) scheduling
3. Throughput: e.g. number of jobs completed on average

To define a scheduling model for RTOS we need two components:
1. Scheduling algorithm: set of rules to use the system resources
2. Analytical means to analyze the system to prove that in worst-case behaviour the system still respects the timing constraints.
## Basic process model
This simplified model is necessary in order to be able to conduct analysis on it.
It makes some strong assumption:
1. Number of process is fixed and known in advance
2. Processes are periodic with known fixed period, every period an instance of the process is issued
3. Processes are independent
4. Timing constraint are deadlines, the deadline of a process is equal to its period
5. The fixed worst case timing of a process can be computed offline
6. System overheads like context switch is negligible
This assumptions are strong: 3. excludes sempahores and mutexes, 2. excludes sporadic processes, 4. often deadlines are shorter than period, 5. is hard to compute or to have a tight bound, 6. may not be true

## Terminology

![[Pasted image 20250717122332.png]]

![[Pasted image 20250717122428.png]]
# Cyclic executive

With this method we use a static schedule computed offline. It needs to run all tasks at their correct rate and always finish before their deadline.

We divide the execution into major cycles made up each of a fixed number of minor cycles of fixed and equal length.
We loop through a table of procedure calls, one major cycle is a full traversal of the table.  Minor cycle boundaries are synchronization points that wait on a interrupt that is raised with a fixed period.

![[Pasted image 20250717195948.png]]

We define the minor cycle length to be the Greatest Common Divisor of the periods of the task to be scheduled, this is because we want the task periods to be an integer multiple of the minor cycle in order to be able to execute at their proper rate, but we also want the minor cycle to be as long as possible for reducing synchronizations and accomodate tasks with long execution time.

For the major cycle we want it to be as small as possible (to avoid unnecessary table length) but we also need it to be big enough to be a integer multiple of all task periods so we can choose the Least Common Multiple of the task lengths.

We may have to split some tasks in different minor cycles in order to fit.
With cyclic executive unless there are splitting tasks we dont have to worry about race conditions since all task instances in this case will terminate before another one begins. This is not true if there is splitting as there will be context switches while a task instance has not terminated yet.


