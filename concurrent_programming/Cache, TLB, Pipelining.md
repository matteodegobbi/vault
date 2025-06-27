#crtp 
# Cache
![[Pasted image 20250618124714.png]]
Memory that is accessed often is stored in memory that is faster than RAM, called cache.
If the processor tries to access some memory that is not in cache (cache miss) the process load a chunk memory around the accesse address into a cache line (cache line could be e..g 64 bytes). The idea is that recently used memory and the memory near it will be used again in the near future (e.g. updating a variable in a loop accesses the same memory, looping over an array uses sequential memory).
As with Pages there are multiple replacement strategies, not in this course.
e.g. in this code inverting `i` with `j` even though the results is the same is can change the performance by a lot depending if the matrix is stored row or column major.
```cpp
#define MATRIX_SIZE 10000

int matrixSum(int m[][MATRIX_SIZE]){
	int i, j, sum = 0;
	for(i = 0; i < MATRIX_SIZE; i++){
		for(j = 0; j < MATRIX_SIZE; j++){
		sum += m[i][j];
		}
	}
	return sum;
}
```
# TLB (Translation Lookaside Buffer)
It's the same idea as the cache but for the Page Table, since the Page Table is stored in memory (RAM) we pay the price of going to RAM everytime we need to access a PTE. For improving this we can use a cache in the MMU that stores recently used PTEs.
During access we search (in parallel) in the TLB for the virtual page number:
* If we have a TLB hit we obtain the physical page address and can just concatenate the offset to obtain the PTE entry without going to RAM
* If we have a TLB miss we need to access the PTE in RAM and possibly update the TLB

In total an access to memory becomes:
- **CPU** generates **Virtual Address**.
- **MMU** handles translation.
- **TLB** is checked for address translation.
- If TLB miss, **Page Table** is accessed for translation.
- **Cache** (L1, L2, L3) is checked for data using the **Physical Address**.
- If Cache miss, **Main Memory (RAM)** is accessed for data.
- Data is returned to CPU.
# Pipelining

The execution of a machine instruction is composed of several stages:
* Instruction Fetch
* Instruction Decode
* Arguments readout
* Execution
* Output write
 When a given stage has finished execution, it is ready to process the next instruction, while the former one is being processed
 For N stages, the ideal speedup is N, if always the pipeline receives all the necessary data from the previous step.

## Pipeline Hazards: 
There are conditions preventing the ideal pipeline execution
1. Data Hazard: when an instruction depends on the instruction just preceding it in the program. 

	For example:
	```armasm
	ADD #2, R1, MEM1
	
	SUB MEM1, R2, R4
	```
	
	In this case the result of the ADD instruction must be stored on memory before the following instruction can read arguments.

2. Branch Hazard: the address of the next instruction after a conditional branch is not known until the branch condition has been evaluated

3. Cache misses: may suspend an instruction for several clock cycles

Some techniques can be used to try to avoid hazards, for data hazards --> OOE, for branch hazards --> branch prediction.

### OOE:

```armasm
MOVE #2, R1;

ADD R2, R3, MEM1;

SUB MEM1, R2, R3;
```
can be rearranged as:
```armasm
ADD R2, R3, MEM1;

MOVE #2, R1;

SUB MEM1, R2, R3;
```

which allows to issue the `ADD` and then instead of having  the `SUB` that waits for the value to be stored in memory we can already issue the `MOVE` "hiding" this latency. OOE to be valid needs to keep the same results in computation.

### Branch prediction:
After fetching a conditional branch instruction, the next instruction could be one of two options, branch prediction can apply a strategy that remembers the last time we encountered this branch what was the next instruction, and already fetch it.
If the prediction was not correct, we revert the pipeline and fetch the correct instruction.
This operation is entirely done in HW with a cache-like table.

---
Code optimizations are described in PDF2.