#crtp 

Deadlock happens when a set of processes is waiting on an event that can be triggered only by a process in the same set.
The system hangs forever and no progress can happen, also any resource already locked by a process cannot be used by the system anymore.
There are 4 necessary conditions to obtain a deadlock:
1. Mutual exclusion: each resouce can only be assigned to one task at a time, if a task tries to access a resource already locked by another task it needs to wait  
2. Hold and wait: the tasks need to have obtained a resource and keep holding it while they wait for another resource
3. Nonpreemption: the resources involved in the deadlock cannot be taken away from the task holding them other than the task itself relinquishing them
4. Circular wait: the processes and resources involved in the deadlock form a circular chain where 1st process waits on a resource held by the 2nd ... until the last process wait for a resource held by the 1st

We'll see how we can solve the problem of deadlocks by attacking at least one of the 4 conditions.

# Resource allocation graph
We can represent processes and resources in a graph with 2 different kind of nodes and edges.
Nodes are either a resource or a process, an edge `resource->process` means that the process hold the resource, an edge `process->resource` means that the process is waiting for the resource. If there's a cycle in the graph we have a deadlock. This information can be used to perform [[#Deadlock detection and recovery]] 
# Deadlock prevention
We can attack at least one of the four conditions to prevent deadlocks:
1. Mutual exclusion: we allow more than one task to use the resource simultaneously, this is feasible for devices like printers, not for crititical sections.
2. Hold and wait: we can either remove the hold by making it so previously obtained resources are released every time we need to request new ones , we can re-request all the old ones if necessary, or we can attack the wait by making it so all resources are requested together at the beginning of the procedure.
3. Nonpreemption: add a way to remove forcefully resources from tasks. Like mutex it only works for some resources for other it's difficult to implement.
4. Circular wait: we can make up a total order on the resources and force the tasks to aquire them following the total order. We define an integer function, $f(R_{i})\rightarrow\mathbb Z$  that maps resource classes into an integer. A process that owns resource $R_j$ can only request $R_i$, iff $f(R_i)>f(R_j)$.
# Deadlock avoidance
Deadlock prevention can add complications to the code so in this section we see a different approach that introduces overhead in order to determine whether granting a resource to a process is safe or not, if it's safe we allow it otherwise we make the process wait even though in principle it could acquire the resource.
This method works during runtime so there's overhead on performance, also it requires preliminary info about processes' behavior.
## Banker's algo
Implements deadlock avoidance.
We define:
* $n$: the number of processes
* $m$: the number of resource classes
* $\vec t=[t_1,\dots,t_m]^T$: number of initially available resources for each class
* $C=[c]_{ij}$ an $m\times n$ matrix containing current resource allocation state
* $X=[x]_{ij}$ an $m\times n$ matrix containing maximum number of resources each process could need during its lifetime (worst case)
* $N=X-C$ worst case future resources needed by processes
* $\vec r=[r_1,\dots,r_m]^T$ remaining resources in the system at a given time
* $\vec q_j=[q_{1j},\dots,q_{mj}]^T$ requested resources by the j-th process

The algo works as follows:
Step 1: When a request for a resource is issued the banker needs to determine whether there are the available resources to even try to give them to the process, it tests this with the condition $q_{j}\le r$, if it's false the process has to wait, if it's true we can proceed by checking whether granting the resources is safe or not.

Step 2: To check safety first we simulate the allocation:

$$\left\{
\begin{array}{l}
c_j' = c_j + q_j \\
n_j' = n_j - q_j \\
r' = r - q_j
\end{array}
\right.$$
-- Note: the second line is just a consequence of the 1st + definition of $N$ matrix.

Step 3: Then we use a conservative approach that tries to find a safe sequence with all $n$ processes that if followed grants the worst case need of resources to all processes.

We use column vector called $\vec w$ to track the currently available resources (initially $\vec w=\vec r$) and a row vector of $n$ elements called $\vec f$ which has 0's for processes not yet in the safe seq. and 1's for processes in the safe seq. already (initially $\vec f=\vec 0$).

The algo tries to find a new candidate $P_j$ process to append to the safe seq. it needs to have $f_j=0$ so not in the seq. yet and it needs to be able to reach it's worst case number of resources so $\vec n_{j}<\vec w$ (meaning future worst case resources need to be less than currently available ones). If no suitable candidate the algo terminates (down below), otherwise we set $f_j=1$ and $\vec w = \vec w + \vec c_j$ since it will release its resources upon finishing.

Finally if not terminated the algorithm repeats to Step 3 to try to extend the safe seq. as much as possible.

If $\vec f = \vec 1$ we have a complete safe seq. and there will be no deadlock otherwise the move is not safe.

# Deadlock detection and recovery

Deadlock prevention and avoidance have some drawbacks with complexity and overhead also banker's can't always be applied since it requires prior knowledge on process resources worst case.
We can use a different approach even lazier than the previous, we let the system reach deadlock and periodically check and recover from it.
As specified [[#Resource allocation graph|previously]] we can look for cycles and detect deadlocks.
If there's one we use a recovery procedure.
If multiple resources of the same class are available we cannot use this detection method and we need to use a more complex one.
# Starvation
Deadlock are a specific case of starvation, a more general phenomenon where one or more tasks are never able to access a resource because everytime they try to access it another comepting task wins.

[[Race conditions - Mutual exclusion#Software lock Peterson|Peterson's algorithm]] guarantees that eventually all tasks will gain access to the critical section alternatively, ensuring fairness. There are other fair algorithms.