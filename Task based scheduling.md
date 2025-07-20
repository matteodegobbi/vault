#crtp
In [[Scheduler#Task priority]] its explained how dynamic and static priority work and their pros and cons, in real-time systems both can be used but usually static priorities are easier to implement.

---
# Critical instant theorem:

## Informal definition:
**Critical instant**: the worst situation in a set of periodic tasks wrt when periodic tasks get scheduled.
Task jobs can be scheduled at arbitrary instants within their period, the time between start of period and job release is called **phase**.
If we prove that the system is schedulable under this critical instant condition proves that it will be schedulable for any task phase.

## Assumptions and definitions
As specified in [[Real-Time and Cyclic Executive]] the relative deadline of all tasks is assumed to be the same as the period: $\forall i\,\,\, D_i=T_i$.
This implies that the absolute deadline is the time of the next release, $d_{i,j}=r_{i,j+1}$.

We shall say that there is an **overflow** at time t if t is the deadline for a job that misses the deadline. 
A scheduling algorithm is **feasible** for a given set of task if they are scheduled so that no overflows ever occur.

A **critical instant** for a task is an instant at which the release of the task will produce the largest response time.
A **critical time zone** for a task is the interval between a critical instant and the end of the task response.

The critical instant theorem states that: A critical instant for any task occurs whenever it is released simultaneously with the release of all higher-priority tasks.
Meaning that the worst situation will occur when all the jobs are initially released at the same time (e.g. all at phase 0)

This theorem is valid for all fixed priority assignments.

Proof: Lets order tasks for decreasing priority $\tau_1,\dots,\tau_m$
![[Pasted image 20250718230714.png]]
(Maybe explanation in the image should say "if we anticipate the release of $\tau_i$ with $i<m$ the interference can only increase or stay the same" like in the book) maybe they are equivalent
$\triangle$ Check the book for a better explanation.

---
# Rate monotonic priority assignment
It's a policy for fixed priority assignment in period tasks. It assigns a priority inversely proportional to the task period.

Assumptions: 
- Every task is periodic with fixed period $T_i$. 
- The relative deadline $D_i$ for every task $\tau_i$ is equal to its period $T_i$.
- Tasks are scheduled preemptively and according to their priority.
- There is only one processor

RM is the optimal priority assignment policy, i.e. every system that is schedulable using fixed priorities is schedulable using RM policy.
In other words, if a system is not schedulable under RM policy, then it will remain not schedulable under any other fixed priority assignment
Proof in the pdf [[Lecture 7-Task Based Scheduling.pdf]] for 2 tasks, can be generalized to n tasks.

To generalize RM to n tasks we can consider a fixed priority assignment that is schedulable.

We can construct an assignment that follows RM by looking repeatedly at tasks adjacent in priority in which the higher priority task has a longer period (violating the RM property).
Then we can swap the priority of the two tasks making this pair consistent with RM and we observe that the system is still schedulable since both the tasks are still interrupted by higher priority ones and are unaffected by lower priority ones. 

From this previous consideration we can see how if we start from an arbitrary schedulable fixed priority assignment we can always reach a schedulable RM assignment in a finite number of priority swaps between adjacent pairs.

Proving this means that RM is optimal for fixed priority assignments for a generic number of tasks.

---
# Earliest Deadline First
Selects tasks to run based on their absolute deadlines. The idea is that urgent tasks for which the deadline is approaching should be finished earlier.
For task $\tau_i$  the absolute deadline is $d_{i,j}=\phi_i+j\cdot T_i +D_i$, computed as the phase (time from beginning of period to release of task i) plus the j past periods of task i plus the relative deadline

With EDF tasks with earlier deadlines will receive higher priorities. The priority of each task is assigned dynamically, because it depends on the current deadlines of the active task instances. 

Task priorities need to be updated only when a new task instance is released since the relative order remains unchanged.

EDF is optimal, meaning that if a set of tasks is schedulable by any algorithm then it's also schedulable by EDF. 
The assumption is that tasks can be preempted and there's only one processor, this is more general than RM since it's a dynamic scheduling, not a static one.

More difficult to implement than RM since it also requires additional information about the task deadlines.