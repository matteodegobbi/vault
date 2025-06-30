#crtp
Both **context switches** done by the **OS scheduler** and **hardware interrupts** involve switching the CPU's focus, but they differ in their triggers, purpose, and how they're handled.

### **Context Switch (OS Scheduler)**
A **context switch** occurs when the operating system (OS) scheduler decides to switch from running one process (or thread) to another. This is a key part of multitasking, allowing the OS to give the appearance of running multiple programs at the same time.

- **Trigger:** 
  The OS scheduler initiates a context switch based on specific conditions like:
  - **Time slices (preemption):** When a process has used up its allocated CPU time (as in preemptive multitasking).
  - **Process blocking:** When a process becomes blocked (e.g., waiting for I/O).
  - **Priority:** A higher-priority process needs to run.
  - **Process termination:** When a process finishes, the scheduler picks a new one.
  
- **What happens:**
  - The state (context) of the current process (e.g., register contents, program counter, stack pointer) is saved in the **Process Control Block (PCB)**.
  - The OS loads the state of the next process from its PCB and resumes execution.
  
- **Time overhead:** 
  Context switches are relatively costly in terms of performance because they involve saving/restoring state and possibly invalidating caches and flushing the TLB.

- **Goal:** 
  The primary goal of a context switch is to ensure fair sharing of CPU resources and handle multitasking efficiently.

### **Hardware Interrupt**
A **hardware interrupt** is an external event (usually triggered by hardware) that temporarily halts the current CPU execution to deal with an urgent task. Once the interrupt is handled, the CPU resumes the original task.

- **Trigger:**
  Hardware interrupts are triggered by external devices or components, such as:
  - **I/O devices:** Like a keyboard press, mouse movement, or network card receiving data.
  - **Timers:** System timers triggering regular interrupts e.g. 60Hz (e.g., for timekeeping or process scheduling).
  - **Other hardware events:** Like power management or a hard drive needing attention.
  
- **What happens:**
  - The CPU detects an interrupt request and saves the current state (usually a subset of registers) to handle it.
  - The CPU stops executing the current task and jumps to a special routine called an **Interrupt Service Routine (ISR)** or **Interrupt Handler**, which is predefined by the OS.
  - After the interrupt is handled, the CPU restores the saved state and resumes the interrupted task.
  
- **Time overhead:**
  Hardware interrupts are generally faster to handle than context switches, but still involve some overhead in saving/restoring state and jumping to an ISR. They are faster because:
	  - risposta gpt #################################   

- **Goal:**
  The purpose of hardware interrupts is to deal with time-sensitive events that need immediate attention from the CPU (like responding to user input or managing I/O).

### Key Differences:

| **Aspect**        | **Context Switch (OS Scheduler)**                                   | **Hardware Interrupt**                                           |
| ----------------- | ------------------------------------------------------------------- | ---------------------------------------------------------------- |
| **Trigger**       | Initiated by OS scheduler (time slice, blocking, priority)          | Triggered by external hardware events (I/O, timers, etc.)        |
| **Purpose**       | Switch between processes/threads for multitasking                   | Handle urgent external events (e.g., I/O, timer)                 |
| **Frequency**     | Happens relatively infrequently (depending on OS scheduling policy) | Happens frequently and irregularly, depending on hardware events |
| **What happens**  | Full process state is saved and restored                            | Minimal state is saved, ISR is executed                          |
| **Handling time** | More costly, as full process state is swapped                       | Less costly, faster to handle                                    |
| **Controlled by** | OS Scheduler                                                        | Hardware and Interrupt Controller                                |
| **Goal**          | Manage CPU time between tasks                                       | Handle immediate hardware requests                               |

### Example:
- **Context switch:** The OS switches from a web browser to a word processor because the web browser used up its CPU time slice.
- **Hardware interrupt:** While you're typing in the word processor, a key press generates a hardware interrupt that tells the CPU to immediately read the keystroke from the keyboard.

In summary, **context switches** are controlled by the OS to manage multitasking, while **hardware interrupts** are triggered by external hardware to handle immediate events. Both involve saving and restoring CPU state, but hardware interrupts are usually much quicker and handle different types of events.


---

Furthermore the [[Cache, TLB, Pipelining|TLB]] is only impacted by context switches and not by hardware interrupts.
When issuing interrupts the OS will run the ISR in kernel mode, the kernel address space is shared across all processes this means that these records in the TLB are still valid even when running ISRs.
This is different from context switches where the TLB is often flushed because the records become invalid (unless ASIDs are used).