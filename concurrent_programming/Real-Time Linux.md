#crtp
There are propietary RTOSes that can be used to obtain hard real-time properties but it can be useful to have an open source version using a common OS like Linux. 

The linux kernel was not preemptible before 2.6, meaning that kernel operations had to finish before a task can resume.
Interrupts occur but the call to `schedule()` is deferred until the kernel operation is done.

This is not good for real time systems as some kernel operations are very slow and can block high priority tasks for a long time.

Since version 2.6 though we can have a soft Real-Time system because it has been changed to allow high priority tasks to interrupt kernel ops when they become ready.

It used to be that kernel operations are all done in interrupt context that cannot be preempted, only interrupt by higher interrupts.

To make the kernel preemptible we carry out most of the kernel ops in kernel threads instead of in interrupt context.

If we use these kernel threads though we need to protect critical sections, if we have a uniprocessor system we can block interrupts while in the critical section so we know we cannot lose control of the CPU while in it.
This doesn't work for multiprocessor so in that case we can use test&set spinlocks directly in the code.

Still this solution has some problems, the latency in this kernel is mainly due to:
- ISRs that are blocking the scheduler
- Critical sections that disable preemption making other tasks wait 

	So a patch called PREEMPT_RT Linux has been created that makes it more like hard real-time OS by adding:
- preempitble critical sections
- priority inheritance for spinlocks (the in-kernel ones) and semaphores in the kernel
- preemptible interrupt handlers

The locking in this patch when supported by HW uses a better rt-semaphore (if not supported it uses an internal spinlock)
in both cases tasks entering critical sections can be interrupted (the spinlock is not directly in the task but is carried out by the kernel maybe ????)

For semaphores priority inheritance is used (not necessary for spinlocks as they block all other tasks since they block interrupts --> preemption doesnt happen, meaning they effectively become the highest priority task in the system)

(ISRs still need to use spinlocks as they arent in the kernel thread context)

Drivers should but the smallest amount of code in ISR and all the not necessary in IST one should be put in kernel threads.

SA NODELAY forces interrupts handlers to run in interrupt context but by default Linux PREEMPT_RT forces all non NODELAY handlers to run in task context.

---


