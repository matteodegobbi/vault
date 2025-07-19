#crtp #todo 
In [[Scheduler#Task priority]] its explained how dynamic and static priority work and their pros and cons, in real-time systems both can be used but usually static priorities are easier to implement.


# Critical instant theorem:

## Informal definition:
**Critical instant**: the worst situation in a set of periodic tasks wrt when periodic tasks get scheduled.
Task jobs can be scheduled at arbitrary instants within their period, the time between start of period and job release is called phase.
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
(Maybe explanation in the image should say "if we anticipate the release of $\tau_i$ with $i<m$" like in the book) 
check the book for better explanation
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
