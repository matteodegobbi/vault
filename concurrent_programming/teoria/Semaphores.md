#todo 
#crtp 
Binary semaphores unlike [[Race conditions - Mutual exclusion#Naive lock|mutexes]] can be signaled from any thread while mutexes can only be released by a thread that acquired it. This makes binary semaphores more suitable for some synchronization problems like [[Producer Consumer]]

