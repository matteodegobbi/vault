#crtp 
For I/O in computers we need to use a communication bus, they include:
* data line: to carry the data
* address line: where to read or write data from/to
* handshaking lines: to know when to read, to coordinate

## Memory mapped I/O 
Uses the same bus for memory and I/O and devices are seen as a set of registers. The address range of devices must be different from memory address and other devices.
Devices will define:
- status registers, current device status, e.g. READY/ERROR
- command registers, to write commands in (different for every device type)
- config regs.
- data regs.
Instead of memory mapped I/O we could use a separate I/O bus.

In modern computers we use a version of memory mapped with bridges that translate from/to its original range to/from another link.

This bridge recognizes its range and translates the address to the connected bus in a new bus cycle (= whole transaction).
(A bridge allows for **buffering and clock domain crossing**, enabling the slower I/O devices to operate asynchronously without stalling the main bus, there are other advantages like using different protocols in the different buses with a bridge operating as a translator to the main bus)

## Synchronizing I/O
Computer needs to know when the device is ready to provide/consume new data.  
(we can use a bit in the status register to store this info)  

### Polling  
In polling the computer repeatedly reads the status register until device is ready.

This method (polling) can be really wasteful on CPU time %. We can use different methods that allow the CPU to do different work while device is "working" I/O.  
To do this we need handshaking lines in the bus and functionalities in CPU and OS.

Example of wasted CPU time% in PDF.
### Interrupt  
The device raises an interrupt line in the bus (usually different priorities have different separate lines). Interrupts with higher priority can interrupt ones with lower priority.

Once the CPU recognizes the interrupt it will reply with a IACK (Interrupt Acknowledge Cycle), in this special BUS cycle the CPU is requesting the IVN (Interrupt Vector Number)

The CPU will use the IVN to index into a IVN table which for each entry contains the ISR (Interrupt Service Routine) starting instruction address.

Before handling the interrupt the CPU saves the current execution context to be able to resume after the interrupt.
The context includes the PC (Program Counter), and SR (Status Register)

The ISR is responsible to save and restore any register data if it's going to write to it.

The device driver needs to plugged within the OS, during the boot the driver will update the IVN table (vector table) by inserting the ISR address and communicating to the device the ISR number to be returned when a IACK is issued during interrupt
During an ISR no other activities can take place. (Unless a higher priority interrupt is raised)

Example of wasted CPU time% in case of high throughput device in PDF.
## Direct Memory Access (DMA)

If we have a high throughput device using interrupts is inefficient as they will a high percentage of CPU time. In this case we can use DMA.

In DMA the device will be responsible to transfer data to memory, the device must become the owner of the BUS to initiate a data transfer cycle, first the device needs to issue a BUS ownership transfer cycle.

Before the data transfer, start address of target data in memory and number of data items to transfer must be communicated by the device driver. Memory Address (MAR) and Word Count (WC) device registers are used for this operation, these registers belong to the device itself not the CPU.

Whenever a data block is available the device shall take bus ownership and transfer the block. During overall transfer the bus ownership will likely be exchanged many times between the processor and the devices. There are different types of DMA that use the BUS differently (cycle stealing, burst, etc NOT IN THE COURSE).
In the meantime, the processor will operate independently, and the only interference is the possible request for bus ownership for memory access (normally negligible). 

When DMA terminates, the CPU will be informed via an interrupt by the device.

## User and Kernel Mode

For security reasons in OSes two modes exist. User mode runs user programs and some parts of the OS.
Other parts of the OS that need it are run in privileged Kernel mode. The CPU switches to Kernel mode only with an interrupt, the CPU ISA includes a Software Interrupt to let the OS switch to Kernel mode, the behavior is the same as an hardware interrupt other than the IACK cycle that's not needed.
The vector number associated with the software interrupt is passed as argument in the ISA instruction.





