#  PDF 2
[[Hardware, PCIe, Bus, Interrupts, DMA]]
[[Virtual Memory]]
[[Cache, TLB, Pipelining]]
# PDF 3
[[Processes]]
[[Context Switch VS Hardware Interrupt]]
[[Threads]]
[[Scheduler]]
# PDF 4
[[Race conditions - Mutual exclusion]]
[[Semaphores and passive wait]]
[[Producer Consumer]]
[[Monitors]]
[[Message passing]]
# PDF 5
[[Deadlocks]]
# PDF 6
[[Real-Time and Cyclic Executive]]
# PDF 7
[[Task based scheduling]]
# PDF 8
- Schedulability conditions for RM and EDF
- RTA
only on PDF
# PDF 9
* Aperiodic and sporadic tasks, minimum interarrival time
* Deadline shorter than period, RTA
* DMPO
* Task interaction and independence hypothesis of basic process model
* Priority inversion and priority inheritance
* Bounded wait time with inheritance
* Priority ceiling and its properties
* RTA with blocking

# PDF 10
[[Real-Time Linux]]

---

# Lab topics
1. Spectre
2. I/O, OS, drivers
3. V4L
4. Compilers, optimization
5. Processes, fork, threads, pthreads
6. Semaphores, deadlocks, synchronization, condition variables
7. TCP sockets
8. UDP sockets
9. Synchronization, producer consumer, buffer size
10. Real time Linux


--- 
NOTE on RTA

The previous chapter introduced an approach to schedulability analysis based on a single quantity, the utilization factor U, which is very easy to compute even for large task sets. 
The drawback of this simple approach is a limit in the accuracy of the analysis, which provides only necessary or sufficient conditions for fixed-priority schedulability. Moreover, utilization-based analysis cannot be extended to more general process models, for example, when the relative deadline Di of task τi is lower than its period Ti. In this chapter, a more sophisticated approach to schedulability analysis will be presented, which will allow coping with the above limitations. This new method for analysis will then be used to analyze the impact in the system of sporadic tasks, that is, tasks that are not periodic but for which it is possible to state a minimum interarrival time. Such tasks typically model the reaction of the system to external events, and their schedulability analysis is therefore important in determining overall real-time performance.