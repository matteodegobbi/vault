#crtp 
Virtual memory is a concept used by most OSes that makes is so the addresses used by programs do not correspond with physical addresses, to be able to do this we need someone to perform an address translation when accessing the physical memory

The address translation is performed by the MMU (Memory Managment Unit), 
A virtual address of N bits is split like this:

- the N-K MSBs of the virtual address are used as an index in the Page Table
- the K LSBs of the virtual address are used as a page offset
![[Pasted image 20241018140232.png]]

The Page Table is an array of numbers each L bits long, it contains physical addresses of pages corresponding to the virtual pages.

## Reasons for virtual memory
One simple reason is that if we have to processes running the same program in one computer we want the two processes to not interfere with each other by using the same memory, virtual memory allows.

Another reason is that virtual memory makes it so a process with a memory error will not corrupt memory used by other processes, this is good for both stability and security.

In any case memory access bugs that are still inside the page of the process will NOT be detected and stopped by the OS

# Shared memory
We can still share memory across processes when using virtual memory..... continua